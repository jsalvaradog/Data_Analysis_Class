int BDT::get_index(double t, double Q, double x, double p)
{
  int index = 0;
  for (int k = 0; k < Nbins; k++)
  {
    if (k > 0)
      index += Nphibins[k - 1];

    if (t >= bins[k][0] && t <= bins[k][1] && Q >= bins[k][2] && Q <= bins[k][3] && x >= bins[k][4] && x <= bins[k][5])
    {
      for (int l = 0; l < Nphibins[k]; l++)
      {
        if (p >= (360. / Nphibins[k]) * l && p <= (360. / Nphibins[k]) * (l + 1))
        {
          index = index + l;
          return index;
        }
      }
    }
  }
  std::cout << "Error " << t << " " << Q << " " << x << " " << p << endl;
  return -1;
}


void BDT::Compute_BM_Matrix()
{
  int Nbins = 9;
  std::vector<double> BM_Factors;

  // for(int i=1; i<=259;i++)
  //{
  //   bdts.at(i-1) = Best_BDT(i);
  // }

  TCut cut_Qx_arr[35];
  cut_Qx_arr[0] = TCut("bestCandidateFlag==1 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
  cut_Qx_arr[1] = TCut("bestCandidateFlag==1 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
  cut_Qx_arr[2] = TCut("bestCandidateFlag==1 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
  cut_Qx_arr[3] = TCut("bestCandidateFlag==1 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
  cut_Qx_arr[4] = TCut("bestCandidateFlag==1 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
  cut_Qx_arr[5] = TCut("bestCandidateFlag==1 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
  cut_Qx_arr[6] = TCut("bestCandidateFlag==1 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
  cut_Qx_arr[7] = TCut("bestCandidateFlag==1 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
  cut_Qx_arr[8] = TCut("bestCandidateFlag==1 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
  cut_Qx_arr[9] = TCut("bestCandidateFlag==1 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
  cut_Qx_arr[10] = TCut("bestCandidateFlag==1 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
  cut_Qx_arr[11] = TCut("bestCandidateFlag==1 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
  cut_Qx_arr[12] = TCut("bestCandidateFlag==1 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
  cut_Qx_arr[13] = TCut("bestCandidateFlag==1 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
  cut_Qx_arr[14] = TCut("bestCandidateFlag==1 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
  cut_Qx_arr[15] = TCut("bestCandidateFlag==1 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
  cut_Qx_arr[16] = TCut("bestCandidateFlag==1 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
  cut_Qx_arr[17] = TCut("bestCandidateFlag==1 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
  cut_Qx_arr[18] = TCut("bestCandidateFlag==1 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
  cut_Qx_arr[19] = TCut("bestCandidateFlag==1 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
  cut_Qx_arr[20] = TCut("bestCandidateFlag==1 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
  cut_Qx_arr[21] = TCut("bestCandidateFlag==1 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
  cut_Qx_arr[22] = TCut("bestCandidateFlag==1 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
  cut_Qx_arr[23] = TCut("bestCandidateFlag==1 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
  cut_Qx_arr[24] = TCut("bestCandidateFlag==1 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
  cut_Qx_arr[25] = TCut("bestCandidateFlag==1 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
  cut_Qx_arr[26] = TCut("bestCandidateFlag==1 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
  cut_Qx_arr[27] = TCut("bestCandidateFlag==1 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
  cut_Qx_arr[28] = TCut("bestCandidateFlag==1 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
  cut_Qx_arr[29] = TCut("bestCandidateFlag==1 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
  cut_Qx_arr[30] = TCut("bestCandidateFlag==1 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
  cut_Qx_arr[31] = TCut("bestCandidateFlag==1 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
  cut_Qx_arr[32] = TCut("bestCandidateFlag==1 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
  cut_Qx_arr[33] = TCut("bestCandidateFlag==1 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
  cut_Qx_arr[34] = TCut("bestCandidateFlag==1 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");

  std::vector<double> bins_t = {-1.0, -0.8, -0.6, -0.4, -0.25, -0.15, -0.11, -0.07, -0.04, 0.0};
  std::vector<double> bins_Q = {1.0, 1.2, 1.456, 1.912, 2.510, 3.295, 4.326, 5.761, 7.0};
  std::vector<double> bins_x = {0.062, 0.090, 0.118, 0.155, 0.204, 0.268, 0.357, 0.446, 0.581, 1.000};
  std::vector<double> bins_phi = {0., 15., 30., 45., 60., 75., 90., 105., 120., 135., 150., 165., 180., 195., 210., 225., 240., 255., 270., 285., 300., 315., 330., 345., 360.};

  auto bins = bins_t.data();
  int N = bins_t.size() - 1;
  TString var = TString("t_Ph");
  TString var_MC = TString("t_Ph_MC");

  // auto bins = bins_Q.data();
  // int N = bins_Q.size() - 1;
  // TString var = TString("strip_Q2");
  // TString var_MC = TString("strip_Q2_MC");

  // auto bins = bins_x.data();
  // int N = bins_x.size() - 1;
  // TString var = TString("strip_Xbj");
  // TString var_MC = TString("strip_Xbj_MC");

  // test bin is l=3, for bin 24.
  TChain *MCData_temp = new TChain("pDVCS");
  MCData_temp->Add(TString("Analysis/wfMerged_DVCS.root"));

  TChain *Data_temp = new TChain("pDVCS");
  Data_temp->Add(TString("Analysis/Merged_Data.root"));

  TCut cut_kin_mc = TCut("strip_Ph_mc_P>2 && strip_Q2_MC>1.0 && Phi_Ph_MC<360 && t_Ph_MC>-1.0"); // W does not exist in MC but it is generated from 2
  TCut cut_kin = TCut("strip_Ph_P>2 && strip_Q2>1.0 && strip_W>2 && Phi_Ph<360 && t_Ph>-1.0");
  TCut cut_sel = TCut("abs(t_Ph/strip_Q2)<1");
  TCut cut_sel_mc = TCut("abs(t_Ph_MC/strip_Q2_MC)<1");

  for (int l = 2; l < 35; l++) //; l<35; l++)
  {
    TCut cut_Qx = cut_Qx_arr[l];
    TString String_cut = cut_Qx.GetTitle();
    String_cut.ReplaceAll("strip_Q2", "strip_Q2");
    String_cut.ReplaceAll("strip_Xbj", "strip_Xbj");
    String_cut.ReplaceAll("t_Ph", "t_Ph");
    TCut cut_Qx_MC = TCut(String_cut);

    // Save the chained tree into a new ROOT file
    TFile *mergedFile = new TFile(Form("Analysis/Merged_DVCS_%i.root", l + 1), "RECREATE");
    TTree* MCData = MCData_temp->CopyTree(TCut("bestCandidateFlag==1 && t_Ph<-0.005 && strip_Xbj>0.062 && strip_Xbj<0.581") + cut_Qx);
    MCData_temp->Write("pDVCS");
    std::cout << "\nMerged file " << mergedFile->GetName() << " created successfully." << std::endl;
        
    // Save the chained tree into a new ROOT file
    TFile *mergedFile2 = new TFile(Form("Analysis/Merged_Data_%i.root", l + 1), "RECREATE");
    TTree* Data = Data_temp->CopyTree(TCut("bestCandidateFlag==1 && t_Ph<-0.005 && strip_Xbj>0.062 && strip_Xbj<0.581") + cut_Qx);
    Data_temp->Write("pDVCS");
    std::cout << "Merged file " << mergedFile2->GetName() << " created successfully." << std::endl;

    int entries = MCData->GetEntries();

    TH1D *input = new TH1D("input", "input", N, bins);
    TH1D *input_true_MC = new TH1D("input_true_MC", "input_true_MC", N, bins);
    TH1D *input_reco_MC = new TH1D("input_reco_MC", "input_reco_MC", N, bins);
    TH2D *response_matrix = new TH2D("response_matrix", "response_matrix", N, bins, N, bins);
    // Define response matrix
    static RooUnfoldResponse response(input_reco_MC, input_true_MC, response_matrix);

    input->Sumw2();
    input_true_MC->Sumw2();
    input_reco_MC->Sumw2();
    response_matrix->Sumw2();

    cout << "\n==================================== Fill input ===================================" << endl;
    Data->Project("input", var, cut + cut_kin + cut_sel + cut_ref + TCut("_strip_Nuc_BDT > GetBDTCut(strip_Xbj, strip_Q2, t_Ph)"));
    MCData->Project("input_reco_MC", var, (cut + cut_kin + cut_sel + cut_ref + TCut("_strip_Nuc_BDT > GetBDTCut(strip_Xbj, strip_Q2, t_Ph)"))*TCut("rWeight"));
    MCData->Project("input_true_MC", var_MC, cut + cut_kin_mc + cut_sel_mc);
    //MCData->Project("response_matrix", var_MC + TString(":") + var, cut + cut_kin + cut_sel + cut_ref + TCut("_strip_Nuc_BDT > GetBDTCut(strip_Xbj, strip_Q2, t_Ph)"));

    std::cout << input_reco_MC->Integral() << " " << input_true_MC->Integral() << " " << response_matrix->GetEntries() << std::endl;

    // Fill Matrix
    cout << "\n==================================== Fill Matrix ===================================" << endl;

    TTreeFormula *formula = new TTreeFormula("cutFormula", (cut_ref + TCut("_strip_Nuc_BDT > GetBDTCut(strip_Xbj, strip_Q2, t_Ph)")).GetTitle(), MCData);
    TTreeFormula *KinWindow = new TTreeFormula("KinWindow", (cut_kin + cut_sel).GetTitle(), MCData);
    TTreeFormula *KinWindow_MC = new TTreeFormula("KinWindow_MC", (cut_kin_mc + cut_sel_mc).GetTitle(), MCData);
    
    static std::vector<double> *var_rec, *var_gen;
    static std::vector<int> *flag;
    double rWeight;

    MCData->SetBranchAddress(var, &var_rec);
    MCData->SetBranchAddress(var_MC, &var_gen);
    MCData->SetBranchAddress("rWeight", &rWeight);
    MCData->SetBranchAddress("bestCandidateFlag", &flag);

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
              if(formula->EvalInstance())
              {
                response.Fill(var_rec->at(j), var_gen->at(j), rWeight); //With weight
              }
              else
              {
                response.Miss(var_gen->at(j)); //No weight
              }
            }/*
            else if(KinWindow->EvalInstance() && !KinWindow_MC->EvalInstance())
            {
              std::cout<<"Fake event"<<endl;
              response.Fake(var_rec->at(j)); //No weight
            }
            else if(!KinWindow->EvalInstance() && KinWindow_MC->EvalInstance())
            {
              std::cout<<"event out of Kin. Window"<<endl;
              response.Miss(var_gen->at(j));
            }
            else //Generated and recontructed in a bin outside this analysis
            {
              continue;
            }*/
          }
        }
        }
    
    
    TH2 *R1 = response.Hresponse();
    std::cout << cut_Qx.GetTitle() << std::endl;
    std::cout << "\n=== X axis (reco) bin edges ===\n";
    for (int i = 1; i <= R1->GetNbinsX() + 1; i++)
    {
      std::cout << R1->GetXaxis()->GetBinLowEdge(i) << " ";
    }
    std::cout << std::endl;

    /*    
    TCanvas* c1 = new TCanvas();
    R1->SetStats(0);
    R1->Scale(R1->Integral());
    R1->Draw("colz");
    c1->Draw();
    c1->SaveAs("response.png");
    delete c1;
    delete R1;
    */

    cout << "\n==================================== UNFOLD ===================================" << endl;

    // MC test. Replace input by input_reco_MC
    RooUnfoldBayes unfold(&response, input_reco_MC, 5);
    TH1D *output = (TH1D *)unfold.Hunfold();

    RooUnfoldSvd unfold_sys(&response, input_reco_MC);
    TH1D *output_sys = (TH1D *)unfold_sys.Hunfold();

    // Write output
    cout << "==================================== Write output ===================================" << endl;
    std::ofstream outFile3;
    std::ofstream outFile4;

    std::cout << "input_reco_MC input_true_MC | output output_sys | Output/Input Recon/True Output/True" << endl;
    for (int i = 1; i <= N; i++)
    {
      printf("%4.2e %4.2e | %4.2e %4.2e | %4.2f %4.2f %4.2f \n", input_reco_MC->GetBinContent(i), input_true_MC->GetBinContent(i), output->GetBinContent(i), output_sys->GetBinContent(i), output->GetBinContent(i) / input->GetBinContent(i), input_reco_MC->GetBinContent(i) / input_true_MC->GetBinContent(i), output->GetBinContent(i) / input_true_MC->GetBinContent(i));
      if (output->GetBinContent(i) != 0 && input->GetBinContent(i) != 0)
        BM_Factors.push_back(output->GetBinContent(i) / input->GetBinContent(i));
    }
    gSystem->Exec(TString(Form("rm -f Analysis/Merged_DVCS_%i.root", l + 1)));
    gSystem->Exec(TString(Form("rm -f Analysis/Merged_Data_%i.root", l + 1)));

    delete input;
    delete input_reco_MC;
    delete input_true_MC;
    delete response_matrix;
    delete output;
    delete output_sys;
    delete formula;
    delete KinWindow;
    delete KinWindow_MC;
    delete MCData;
    delete Data;
    mergedFile->Close();
    mergedFile2->Close();
    delete mergedFile;
    delete mergedFile2; 
  }

  delete MCData_temp;
  delete Data_temp;

  for (int i = 0; i < BM_Factors.size(); i++)
  {
    std::cout << "BM Factor " << i + 1 << " : " << BM_Factors.at(i) << ", " << endl;
  }
}
