int BDT::get_index(double t, double Q, double x, double p)
{
  for(int k=0; k<Nbins; k++)
    {
      if(t >= bins[k][0] && t <= bins[k][1] && Q >= bins[k][2] && Q <= bins[k][3] && x >= bins[k][4] && x <= bins[k][5])
      {
        return k;
      }
    }
  //std::cout<<"Error "<<t<<" "<<Q<<" "<<x<<" "<<p<<endl;
  return -1;
}


void BDT::Compute_BM_Matrix() 
{
  // Enable ROOT implicit multi-threading for parallel processing where possible
  ROOT::EnableImplicitMT();

  std::cout<<"Number of bins "<<Nbins<<endl;
  //for(int i=1; i<=Nbins;i++)
  //{
  //  bdts.at(i-1) = Best_BDT(i);
  //}

  //Load merged file. Adding all files to a TChain makes TFormula to crash
  TChain *MCData_temp= new TChain("pDVCS");
  //MCData_temp->Add(TString("Analysis/Merged_DVCS.root"));
  MCData_temp->Add(TString("Analysis/wfMerged_DVCS.root"));
  
    // Save the chained tree into a new ROOT file
    //TFile *mergedFile_MC = TFile::Open("Analysis/Merged_DVCS_3D.root", "READ");  
    TFile *mergedFile_MC = TFile::Open("Analysis/wfMerged_DVCS_3D.root", "READ");  
    TTree* MCData;
    if(mergedFile_MC && mergedFile_MC->IsOpen())
      {
        MCData = (TTree*)mergedFile_MC->Get("pDVCS");
        std::cout << "Merged MC opened successfully." << std::endl;
      }
    else
      {
        delete mergedFile_MC;
        //mergedFile_MC = new TFile("Analysis/Merged_DVCS_3D.root", "RECREATE");
        mergedFile_MC = new TFile("Analysis/wfMerged_DVCS_3D.root", "RECREATE");
        MCData = MCData_temp->CopyTree(TCut("bestCandidateFlag==1 && t_Ph<-0.005 && strip_Xbj>0.062 && strip_Xbj<0.581"));//  && t_Ph>-0.04 && strip_Xbj>0.062 && strip_Xbj<0.581");
        mergedFile_MC->cd();
        MCData->Write("pDVCS");
        std::cout << "Merged file created successfully." << std::endl;
      }
    delete MCData_temp;
        

  TChain *Data_temp= new TChain("pDVCS");
  Data_temp->Add(TString("Analysis/Merged_Data.root"));

    // Save the chained tree into a new ROOT file
    TFile *mergedFile_Data = TFile::Open("Analysis/Merged_Data_3D.root", "READ");
    TTree* Data;
    if(mergedFile_Data && mergedFile_Data->IsOpen())
      {
        Data = (TTree*)mergedFile_Data->Get("pDVCS");
        std::cout << "Merged Data opened successfully." << std::endl;
      }
    else
      {
      delete mergedFile_Data;
      mergedFile_Data = new TFile("Analysis/Merged_Data_3D.root", "RECREATE");
      Data = Data_temp->CopyTree(TCut("bestCandidateFlag==1 && t_Ph<-0.005 && strip_Xbj>0.062 && strip_Xbj<0.581"));// && t_Ph>-0.04 && strip_Xbj>0.062 && strip_Xbj<0.581");
      mergedFile_Data->cd();
      Data->Write("pDVCS");
      std::cout << "Merged file created successfully." << std::endl;
      }
    delete Data_temp;


  int Hel;
  static vector<double> *t;
  static vector<double> *Q;
  static vector<double> *x;
  static vector<double> *p;

  static vector<double> *t_MC;
  static vector<double> *Q_MC;
  static vector<double> *x_MC;
  static vector<double> *p_MC;

  static vector<int> *flag;
  static double BDTvar;
  static double rWeight;
  //To do without weight set rWeight=1;

  MCData->SetBranchAddress("t_Ph",&t);
  MCData->SetBranchAddress("strip_Q2",&Q);
  MCData->SetBranchAddress("strip_Xbj",&x);
  MCData->SetBranchAddress("Phi_Ph",&p);

  MCData->SetBranchAddress("t_Ph_MC",&t_MC);
  MCData->SetBranchAddress("strip_Q2_MC",&Q_MC);
  MCData->SetBranchAddress("strip_Xbj_MC",&x_MC);
  MCData->SetBranchAddress("Phi_Ph_MC",&p_MC);

  MCData->SetBranchAddress("Helicity",&Hel);
  MCData->SetBranchAddress("bestCandidateFlag",&flag);
  MCData->SetBranchAddress("_strip_Nuc_BDT",&BDTvar);  
  MCData->SetBranchAddress("rWeight", &rWeight);

  TH1D* input = new TH1D("input", "input", Nbins, 0, Nbins);
  TH1D* input_true_MC = new TH1D("input_true_MC", "input_true_MC", Nbins, 0, Nbins);
  TH1D* input_reco_MC = new TH1D("input_reco_MC", "input_reco_MC", Nbins, 0, Nbins);

  input->Sumw2();
  input_true_MC->Sumw2();
  input_reco_MC->Sumw2();
  
  TCut cut_kin_mc=TCut("strip_Ph_mc_P>2 && strip_Q2_MC>1.0 && Phi_Ph_MC<360 && t_Ph_MC>-1.0"); //W does not exist in MC but it is generated from 2
  TCut cut_kin = TCut("strip_Ph_P>2 && strip_Q2>1.0 && strip_W>2 && Phi_Ph<360 && t_Ph>-1.0");
  TCut cut_sel = TCut("abs(t_Ph/strip_Q2)<1");
  TCut cut_sel_mc = TCut("abs(t_Ph_MC/strip_Q2_MC)<1");
  
  cout << "\n==================================== Fill input ===================================" << endl;
  
  TString var = TString("Phi_Ph");
  TString var_MC = TString("Phi_Ph_MC");
  for(int i=1; i<=Nbins; i++)
  {
    printProgress(i*1.0/Nbins);
    TChain *Data_bin= new TChain("pDVCS");
    Data_bin->Add(TString(Form("Analysis/bin_%i/Tested_Quality_Data.root", i)));

    TH1F* temp_data = new TH1F("temp_data", "temp_data", 24, 0, 360);
    Data_bin->Project("temp_data", var, cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT > %f",bdts.at(i-1))));

    double data_int = temp_data->Integral();
    input->SetBinContent(i, data_int);
    input->SetBinError(i, sqrt(data_int)); 
    delete temp_data;
    delete Data_bin;
}
  
  cout << "\n==================================== Fill Matrix ===================================" << endl;

  TTreeFormula* formula = new TTreeFormula("cutFormula", (cut_ref + TCut("_strip_Nuc_BDT > GetBDTCut(strip_Xbj, strip_Q2, t_Ph)")).GetTitle(), MCData);
  TTreeFormula* KinWindow = new TTreeFormula("KinWindow", (cut_kin + cut_sel).GetTitle(), MCData);
  TTreeFormula* KinWindow_MC = new TTreeFormula("KinWindow_MC", (cut_kin_mc + cut_sel_mc).GetTitle(), MCData);

  //Define response matrix
  RooUnfoldResponse response (Nbins, 0, Nbins);  
  int col, row;
 
  int entries=MCData->GetEntries();
  for(int i=0; i<entries; i++)
    {
      printProgress(i*1.0/entries);
      MCData->GetEntry(i);
    for(int j=0; j<flag->size(); j++)
	  {
	    if(flag->at(j)==1)
	    { 
        if(KinWindow->EvalInstance() && KinWindow_MC->EvalInstance())  
        {
  	      row=get_index(t->at(j), Q->at(j), x->at(j), p->at(j));
	        col=get_index(t_MC->at(j), Q_MC->at(j), x_MC->at(j), p_MC->at(j));
         	if(formula->EvalInstance() && row>=0 && col>=0)
          {
            response.Fill(row, col, rWeight); //With weight
            input_true_MC->SetBinContent(col+1, input_true_MC->GetBinContent(col+1)+1);
            input_true_MC->SetBinError(col+1, sqrt(input_true_MC->GetBinContent(col+1)));
            input_reco_MC->SetBinContent(row+1, input_reco_MC->GetBinContent(row+1)+rWeight);
            input_reco_MC->SetBinError(row+1, sqrt(input_reco_MC->GetBinContent(row+1)));

          }/*
          else
          { 
            if(row<0 && col<0) std::cout<<"Error: row and col are negative. This should not happen."<<endl;
            if(col<0 && row>=0) response.Fake(row);
            if(row<0 && col>=0) response.Miss(col);
            if(row>=0 && col>=0) 
            {
              response.Miss(col);
              if(row>=0)
              {
              input_true_MC->SetBinContent(row+1, input_true_MC->GetBinContent(row+1)+1);
              input_true_MC->SetBinError(row+1, sqrt(input_true_MC->GetBinContent(row+1)));
              }
              if(col>=0)
              {
              input_reco_MC->SetBinContent(col+1, input_reco_MC->GetBinContent(col+1)+1);
              input_reco_MC->SetBinError(col+1, sqrt(input_reco_MC->GetBinContent(col+1)));
              }
            }
          }*/
        }/*
        else if(KinWindow->EvalInstance() && !KinWindow_MC->EvalInstance())
        {
          response.Fake(row); //No weight
          input_true_MC->SetBinContent(row+1, input_true_MC->GetBinContent(row+1)+1);
          input_true_MC->SetBinError(row+1, sqrt(input_true_MC->GetBinContent(row+1)));
        }
        else if(!KinWindow->EvalInstance() && KinWindow_MC->EvalInstance())
        {
          response.Miss(col);
          input_reco_MC->SetBinContent(col+1, input_reco_MC->GetBinContent(col+1)+1);
          input_reco_MC->SetBinError(col+1, sqrt(input_reco_MC->GetBinContent(col+1)));
        }
        else //Generated and recontructed in a bin outside this analysis
        {
          continue;
        }*/
      }
    }
    }
  delete formula;
  delete KinWindow;
  delete KinWindow_MC;


  TH2* R1 = response.Hresponse();

  cout << "\n==================================== UNFOLD ===================================" << endl;

  //MC test. Replace input by input_reco_MC
  RooUnfoldBayes   unfold (&response, input, 5);
  TH1D* output= (TH1D*) unfold.Hunfold();

  RooUnfoldSvd   unfold_sys (&response, input);
  TH1D* output_sys= (TH1D*) unfold_sys.Hunfold();

  auto* R = response.HresponseNoOverflow();
  auto* c1 = new TCanvas();
  R->SetStats(0);
  //gPad->SetLogz();
  R->Scale(R->Integral());
  R->Draw("colz");
  c1->Draw();

  c1->SaveAs("response.png");
  
  //Write output
  cout << "==================================== Write output ===================================" << endl;
  std::ofstream outFile3;
  std::ofstream outFile4;

  std::cout<<"Bin | input_reco_MC input_true_MC input_Data| output output_sys | Output_sys/Input Recon/True Output_sys/True"<<endl;
  for(int i=1; i<=Nbins; i++)
    {
      printf("%3.i | %4.2e %4.2e %4.2e | %4.2e %4.2e | %4.2f %4.2f %4.2f \n", i\
        , input_reco_MC->GetBinContent(i), input_true_MC->GetBinContent(i), input->GetBinContent(i)\
        , output->GetBinContent(i), output_sys->GetBinContent(i)\
        , output_sys->GetBinContent(i)/input->GetBinContent(i) \
        , input_reco_MC->GetBinContent(i)/input_true_MC->GetBinContent(i) \
        , output_sys->GetBinContent(i)/input_true_MC->GetBinContent(i) \
      );
    }
  
  delete input;
  delete input_reco_MC;
  delete input_true_MC;
  delete output;
  delete output_sys;

  delete Data;
  delete MCData;
}
