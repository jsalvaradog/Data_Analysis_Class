
void BDT::xsec_on_bins(int bin, int NBinsPhi=0)
{

  ///////////////////////////////
  // Initial declarations
  ///////////////////////////////
  gStyle->SetOptFit(0);
  gStyle->SetOptTitle(0);
  std::cout<<"\n"<<endl;

  if(NBinsPhi==0)
	{
	  NBinsPhi=Nphibins[bin-1];
	}


  std::ifstream inputFile;
  std::string line;
  std::vector<double> xValues;
  std::vector<double> yValues;
  std::vector<double> yErrors;
  std::vector<double> xErrors;
  std::vector<double> phi_bins;

  double x, y, aux, yErr;
  double binWidth;
  double xErr;
  int numPoints;
  
      boundaries.clear();
      boundaries.push_back(bins[bin-1][0]);
      boundaries.push_back(bins[bin-1][1]);
      boundaries.push_back(bins[bin-1][2]);
      boundaries.push_back(bins[bin-1][3]);
      boundaries.push_back(bins[bin-1][4]);
      boundaries.push_back(bins[bin-1][5]);


  cut_bin = Mbins[bin-1];
  TString Folder_old=Folder;
  Folder = Folder_old + TString("bin_")+Form("%i/",bin);
  gSystem->Exec(TString("mkdir -p ") + Folder);

      double bdt = Best_BDT();
      std::cout<<Form("\n Best BDT cut found at: %f",bdt)<<endl;
      //To improve mm2_eg matching
      BDT_value = bdt + 0.02;
       
    if(bdt_sys)
      BDT_value=BDT_value + 0.02;

      std::cout<<"\n Getting Contamination Mostafa way..."<<endl;      
  auto Most=Get_Contamination_Mostafa(cut + cut_bin + cut_ref, BDT_value,NBinsPhi,false);
  std::cout<<"\n Gettting Contamination Maxime way"<<endl;
  auto Maxi=Maxime(cut + cut_bin + cut_ref, BDT_value, bin, NBinsPhi);
  //std::cout<<"\n Getting Contamination Fitting way..."<<endl;      
  //auto Fitt=Get_Contamination_Fit(cut + cut_bin, BDT_value,NBinsPhi);

  Folder = Folder + TString("xsec/");
  gSystem->Exec(TString("mkdir -p ") + Folder + TString("xsec/"));

  std::vector<vector<double>> means1, means2;
  means1 = ReadMeansFile(Folder + TString("../means_most.txt"));
  means2 = ReadMeansFile(Folder + TString("../means_maxi.txt"));

  ///////////////////////////////
  // Get shift of kinematics
  // It was used for the 4to3 correction. Now it is irrelevant
  // I keep it just in case
  ///////////////////////////////
  TGraphErrors* t_bef1 = new TGraphErrors();
  TGraphErrors* Q_bef1 = new TGraphErrors();
  TGraphErrors* x_bef1 = new TGraphErrors();
  TGraphErrors* t_aft1 = new TGraphErrors();
  TGraphErrors* Q_aft1 = new TGraphErrors();
  TGraphErrors* x_aft1 = new TGraphErrors();

  TGraphErrors* t_bef2 = new TGraphErrors();
  TGraphErrors* Q_bef2 = new TGraphErrors();
  TGraphErrors* x_bef2 = new TGraphErrors();
  TGraphErrors* t_aft2 = new TGraphErrors();
  TGraphErrors* Q_aft2 = new TGraphErrors();
  TGraphErrors* x_aft2 = new TGraphErrors();

  TH1F* factor_t = compute_kin_shift_factor(NBinsPhi, "t_Ph");
  TH1F* factor_Q = compute_kin_shift_factor(NBinsPhi, "strip_Q2");
  TH1F* factor_x = compute_kin_shift_factor(NBinsPhi, "strip_Xbj");
  TH1F* factor_p = compute_kin_shift_factor(NBinsPhi, "Phi_Ph");

  t_bef1->SetTitle("Before 1;#phi (deg); t (GeV^{2})");
  Q_bef1->SetTitle("Before 1;#phi (deg); Q (GeV^{2})");
  x_bef1->SetTitle("Before 1;#phi (deg); x_{B}");
  t_aft1->SetTitle("Before 1;#phi (deg); t (GeV^{2})");
  Q_aft1->SetTitle("Before 1;#phi (deg); Q (GeV^{2})");
  x_aft1->SetTitle("Before 1;#phi (deg); x_{B}");
  t_bef2->SetTitle("Before 2;#phi (deg); t (GeV^{2})");
  Q_bef2->SetTitle("Before 2;#phi (deg); Q (GeV^{2})");
  x_bef2->SetTitle("Before 2;#phi (deg); x_{B}");
  t_aft2->SetTitle("Before 2;#phi (deg); t (GeV^{2})");
  Q_aft2->SetTitle("Before 2;#phi (deg); Q (GeV^{2})");
  x_aft2->SetTitle("Before 2;#phi (deg); x_{B}");
  factor_t->SetTitle("Factor t;#phi (deg); Factor");
  factor_Q->SetTitle("Factor Q;#phi (deg); Factor");
  factor_x->SetTitle("Factor x;#phi (deg); Factor");
  factor_p->SetTitle("Factor p;#phi (deg); Factor");

  t_bef1->SetName("t_mean1_bef");
  Q_bef1->SetName("Q_mean1_bef");
  x_bef1->SetName("x_mean1_bef");
  t_aft1->SetName("t_mean1_aft");
  Q_aft1->SetName("Q_mean1_aft");
  x_aft1->SetName("x_mean1_aft");
  t_bef2->SetName("t_mean2_bef");
  Q_bef2->SetName("Q_mean2_bef");
  x_bef2->SetName("x_mean2_bef");
  t_aft2->SetName("t_mean2_aft");
  Q_aft2->SetName("Q_mean2_aft");
  x_aft2->SetName("x_mean2_aft");


  t_bef1->SetLineColor(kBlack);
  Q_bef1->SetLineColor(kBlack);
  x_bef1->SetLineColor(kBlack);
  t_aft1->SetLineColor(kRed);
  Q_aft1->SetLineColor(kRed);
  x_aft1->SetLineColor(kRed);
  t_bef2->SetLineColor(kBlack);
  Q_bef2->SetLineColor(kBlack);
  x_bef2->SetLineColor(kBlack);
  t_aft2->SetLineColor(kRed);
  Q_aft2->SetLineColor(kRed);
  x_aft2->SetLineColor(kRed);

  t_bef1->SetMarkerColor(kBlack);
  Q_bef1->SetMarkerColor(kBlack);
  x_bef1->SetMarkerColor(kBlack);
  t_aft1->SetMarkerColor(kRed);
  Q_aft1->SetMarkerColor(kRed);
  x_aft1->SetMarkerColor(kRed);
  t_bef2->SetMarkerColor(kBlack);
  Q_bef2->SetMarkerColor(kBlack);
  x_bef2->SetMarkerColor(kBlack);
  t_aft2->SetMarkerColor(kRed);
  Q_aft2->SetMarkerColor(kRed);
  x_aft2->SetMarkerColor(kRed);
  for(int k=0; k<NBinsPhi; k++)
  {
    t_bef1->SetPoint(k, means1.at(k).at(0),means1.at(k).at(2));
    t_bef1->SetPointError(k, means1.at(k).at(1),means1.at(k).at(3));
    Q_bef1->SetPoint(k, means1.at(k).at(0),means1.at(k).at(4));
    Q_bef1->SetPointError(k, means1.at(k).at(1),means1.at(k).at(5));
    x_bef1->SetPoint(k, means1.at(k).at(0),means1.at(k).at(6));
    x_bef1->SetPointError(k, means1.at(k).at(1),means1.at(k).at(7));

    t_bef2->SetPoint(k, means2.at(k).at(0),means2.at(k).at(2));
    t_bef2->SetPointError(k, means2.at(k).at(1),means2.at(k).at(3));
    Q_bef2->SetPoint(k, means2.at(k).at(0),means2.at(k).at(4));
    Q_bef2->SetPointError(k, means2.at(k).at(1),means2.at(k).at(5));
    x_bef2->SetPoint(k, means2.at(k).at(0),means2.at(k).at(6));
    x_bef2->SetPointError(k, means2.at(k).at(1),means2.at(k).at(7));

    t_aft1->SetPoint(k, means1.at(k).at(0)*factor_p->GetBinContent(k+1),means1.at(k).at(2)*factor_t->GetBinContent(k+1));
    t_aft1->SetPointError(k, means1.at(k).at(1)*factor_p->GetBinContent(k+1),means1.at(k).at(3)*factor_t->GetBinContent(k+1));
    Q_aft1->SetPoint(k, means1.at(k).at(0)*factor_p->GetBinContent(k+1),means1.at(k).at(4)*factor_Q->GetBinContent(k+1));
    Q_aft1->SetPointError(k, means1.at(k).at(1)*factor_p->GetBinContent(k+1),means1.at(k).at(5)*factor_Q->GetBinContent(k+1));
    x_aft1->SetPoint(k, means1.at(k).at(0)*factor_p->GetBinContent(k+1),means1.at(k).at(6)*factor_x->GetBinContent(k+1));
    x_aft1->SetPointError(k, means1.at(k).at(1)*factor_p->GetBinContent(k+1),means1.at(k).at(7)*factor_x->GetBinContent(k+1));

    t_aft2->SetPoint(k, means2.at(k).at(0)*factor_p->GetBinContent(k+1),means2.at(k).at(2)*factor_t->GetBinContent(k+1));
    t_aft2->SetPointError(k, means2.at(k).at(1)*factor_p->GetBinContent(k+1),means2.at(k).at(3)*factor_t->GetBinContent(k+1));
    Q_aft2->SetPoint(k, means2.at(k).at(0)*factor_p->GetBinContent(k+1),means2.at(k).at(4)*factor_Q->GetBinContent(k+1));
    Q_aft2->SetPointError(k, means2.at(k).at(1)*factor_p->GetBinContent(k+1),means2.at(k).at(5)*factor_Q->GetBinContent(k+1));
    x_aft2->SetPoint(k, means2.at(k).at(0)*factor_p->GetBinContent(k+1),means2.at(k).at(6)*factor_x->GetBinContent(k+1));
    x_aft2->SetPointError(k, means2.at(k).at(1)*factor_p->GetBinContent(k+1),means2.at(k).at(7)*factor_x->GetBinContent(k+1));

  }

  TH1F* factor3D_t = compute_kin_shift_factor("t_Ph");
  TH1F* factor3D_Q = compute_kin_shift_factor("strip_Q2");
  TH1F* factor3D_x = compute_kin_shift_factor("strip_Xbj");

  TCanvas* canvas = new TCanvas("canvas","canvas",700,500);
  t_bef1->Draw("ap");
  t_aft1->Draw("p");
  TLegend* legend1 = new TLegend(0.6,0.6,0.88,0.88);
  legend1->AddEntry(t_bef1,"Before","l");
  legend1->AddEntry(t_aft1,"After","l");
  legend1->Draw();
  canvas->Print(Folder + TString("t_corr1.pdf"));

  Q_bef1->Draw("ap");
  Q_aft1->Draw("p");
  canvas->Print(Folder + TString("Q_corr1.pdf"));

  x_bef1->Draw("ap");
  x_aft1->Draw("p");
  canvas->Print(Folder + TString("x_corr1.pdf"));

  t_bef2->Draw("ap");
  t_aft2->Draw("p");
  canvas->Print(Folder + TString("t_corr2.pdf"));

  Q_bef2->Draw("ap");
  Q_aft2->Draw("p");
  canvas->Print(Folder + TString("Q_corr2.pdf"));

  x_bef2->Draw("ap");
  x_aft2->Draw("p");
  canvas->Print(Folder + TString("x_corr2.pdf"));

  //root output
  TFile *outputFileMeans = new TFile(Folder + TString("means.root"), "RECREATE");
  t_bef1->Write();
  Q_bef1->Write();
  x_bef1->Write();
  t_aft1->Write();
  Q_aft1->Write();
  x_aft1->Write();
  t_bef2->Write();
  Q_bef2->Write();
  x_bef2->Write();
  t_aft2->Write();
  Q_aft2->Write();
  x_aft2->Write();
  factor_t->Write();
  factor_Q->Write();
  factor_x->Write();
  factor_p->Write();
  factor3D_t->Write();
  factor3D_Q->Write();
  factor3D_x->Write();
  outputFileMeans->Close();


  delete t_bef1;
  delete Q_bef1;
  delete x_bef1;
  delete t_aft1;
  delete Q_aft1;
  delete x_aft1;
  delete t_bef2;
  delete Q_bef2;
  delete x_bef2;
  delete t_aft2;
  delete Q_aft2;
  delete x_aft2;

  ///////////////////////////////
  // Retrieve event yield
  ///////////////////////////////
  TChain* chainData = new TChain("pDVCS");
  TChain* chainBkg1 = new TChain("pDVCS");
  TChain* chainBkg2 = new TChain("pDVCS");

  chainData->Add(Folder + TString("../") + TData); // Data
  //chainData->Add(Folder + TString("../") + TBM_Sim); // MC test
  //chainData->Add(Folder + TString("../wf") + TBM_Sim); // MC wtest

  chainBkg1->Add(Folder + TString("../") + "TMostafa_pi0.root");
  chainBkg2->Add(Folder + TString("../") + "TMaxime_pi0.root");

  TH1* NOrig = new TH1F("NOrig", "Original Data", NBinsPhi, 0, 360);
  TH1* NBkg1 = new TH1F("NBkg1", "Background 1", NBinsPhi, 0, 360);
  TH1* NBkg2 = new TH1F("NBkg2", "Background 2", NBinsPhi, 0, 360);
  NOrig->Sumw2();
  NBkg1->Sumw2();
  NBkg2->Sumw2();

  //TCut weight = TCut("(strip_Ph_Theta<5 ? 0.75 : 0.9)*0.75");
  TCut weight = TCut("1");

  chainData->Project("NOrig", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))));
  //chainData->Project("NOrig", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * TCut("rWeight")); //for wTest
  chainBkg1->Project("NBkg1", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * weight * TCut("Weight"));
  chainBkg2->Project("NBkg2", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * weight * TCut("Weight"));

  ///////////////////////////////
  // Background subtracted yield and systematics
  ///////////////////////////////
  TH1F* NMost = new TH1F("NMost", "Method 1", NBinsPhi, 0, 360);
  TH1F* NMaxi = new TH1F("NMaxi", "Method 2", NBinsPhi, 0, 360);
  NMost->Sumw2();
  NMaxi->Sumw2();

  NMost->Add(NOrig, NBkg1, 1, -1);
  NMaxi->Add(NOrig, NBkg2, 1, -1);

  NOrig->SetMarkerColor(kBlack);
  NOrig->SetLineColor(kBlack);

  NMost->SetMarkerColor(kBlue);
  NMost->SetLineColor(kBlue);

  NMaxi->SetMarkerColor(kRed);
  NMaxi->SetLineColor(kRed);

  NMost->SetTitle("Method 1");
  NMaxi->SetTitle("Method 2");
  
  NOrig->Draw();
  NMost->Draw("SAME");
  NMaxi->Draw("SAME");

  NOrig->SetName("Before");
  NMost->SetName("Method 1");
  NMaxi->SetName("Method 2");

  ///Selection systematics
  TH1F* Systematics = new TH1F("Systematics","Systematics",NBinsPhi,0,360);
  for(int r=0; r<=NBinsPhi; r++)
  {
    Systematics->SetBinContent(r, 0.0);
    Systematics->SetBinError(r, 0.0);
  }

  TH1* NSys_BDT = new TH1F("NSys_BDT", "", NBinsPhi, 0, 360);
  TH1* NSys_pid = new TH1F("NSys_pid", "", NBinsPhi, 0, 360);
  NSys_BDT->Sumw2();
  NSys_pid->Sumw2();
  chainData->Project("NSys_BDT", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value + 0.04*0.1))));
  chainData->Project("NSys_pid", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + cut_pid + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))));

  //Selection systematics
  NSys_BDT->Add(NOrig, NSys_BDT, 1, -1);
  NSys_pid->Add(NOrig, NSys_pid, 1, -1);
  NSys_BDT->Divide(NMaxi);
  NSys_pid->Divide(NMaxi);
  NSys_BDT->Multiply(NSys_BDT);
  NSys_pid->Multiply(NSys_pid);
  //Systematics->Add(NSys_BDT);
  Systematics->Add(NSys_pid);

  //Bkg systematics
  NBkg1->Add(NBkg1, NBkg2, 1, -1);
  NBkg1->Divide(NMaxi);
  NBkg1->Multiply(NBkg1);
  Systematics->Add(NBkg1);
  std::cout<<"\nSelection Systematics (BDT/PID/Bkg)"<<endl;
  for(int r=0; r<=NBinsPhi; r++)
  {
    Systematics->SetBinError(r, Systematics->GetBinContent(r));
    Systematics->SetBinContent(r, 1.0);
    std::cout<<" "<<sqrt(NSys_BDT->GetBinContent(r))*100<<"%, "<<sqrt(NSys_pid->GetBinContent(r))*100<<"%, "<<sqrt(NBkg1->GetBinContent(r))*100<<"%"<<endl;
  }

  ///////////////////////////////
  // Error computation of yields
  ///////////////////////////////

  TH1F* OrigErr1 = new TH1F("OrigErr1","OrigErr1",NBinsPhi,0,360);
  TH1F* OrigErr2 = new TH1F("OrigErr2","OrigErr2",NBinsPhi,0,360);
  std::ifstream StatFile;
  StatFile.open(Folder + TString("../Bkg_Most_stats.txt")); // Replace with the name of the block file you want to read
  double n1g_p, n1g_m, n2g_p, n2g_m, n2gD_p, n2gD_m, nData_p, nData_m;
  double n1g, n2g, n2gD;

  std::cout<<"\nRaw entries/err for Orig, Most and Maxi: "<<endl;
  for(int t=1; t<=NBinsPhi; t++)
    {
      std::getline(StatFile, line);
      std::istringstream iss(line);
      iss >> n1g_p >> n1g_m >> n2g_p >> n2g_m >> n2gD_p >> n2gD_m >> nData_p >> nData_m;
      n1g = (n1g_p + n1g_m);
      n2g = (n2g_p + n2g_m);
      n2gD = (n2gD_p + n2gD_m);

      if(NMost->GetBinContent(t)>1 && NOrig->GetBinContent(t)>1 && n1g>1 && n2g>1 && n2gD>1)
      {
        OrigErr1->SetBinContent(t, 1.0);
        OrigErr1->SetBinError(t, NOrig->GetBinContent(t)*sqrt(1.0/(NOrig->GetBinContent(t)*pow(NMost->GetBinContent(t)/NOrig->GetBinContent(t),2)) ));  
        NMost->SetBinError(t, NMost->GetBinContent(t)*sqrt(pow(NOrig->GetBinContent(t)/NMost->GetBinContent(t) - 1,2)*(1./n1g + 1./n2g + 1./n2gD) ));
        }
      else
      {
        OrigErr1->SetBinContent(t, 1.0);
        OrigErr1->SetBinError(t, sqrt(NOrig->GetBinContent(t)));
        NMost->SetBinError(t, 0.0);
      }
      if(NMaxi->GetBinContent(t)>1 && NOrig->GetBinContent(t)>1 && n2gD>1)
      {
        OrigErr2->SetBinContent(t, 1.0);
        OrigErr2->SetBinError(t, NOrig->GetBinContent(t)*sqrt(1.0/(NOrig->GetBinContent(t)*pow(NMaxi->GetBinContent(t)/NOrig->GetBinContent(t),2)) ));
        NMaxi->SetBinError(t, NMaxi->GetBinContent(t)*sqrt(pow(NOrig->GetBinContent(t)/NMaxi->GetBinContent(t) - 1,2)*(1./NMaxi->GetBinContent(t) + 1./n2gD) ));  
      }
      else
      {
        OrigErr2->SetBinContent(t, 1.0);
        OrigErr2->SetBinError(t, sqrt(NOrig->GetBinContent(t)));
        NMaxi->SetBinError(t, 0.0);
      }
      std::cout<<" "<<NOrig->GetBinContent(t)<<" "<<OrigErr1->GetBinError(t)<<" "<<NMost->GetBinContent(t)<<" "<<NMost->GetBinError(t)<<" "<<NMaxi->GetBinContent(t)<<" "<<NMaxi->GetBinError(t)<<endl;
    }
  StatFile.close();
  std::cout<<"\n"<<endl;

  canvas->BuildLegend();
  canvas->Print(Folder + TString("Background_subtraction.pdf"));
  delete canvas;
	  
  ///////////////////////////////
  // Theory xsection 
  // Theory curves computed at 3D mean kinematics
  ///////////////////////////////
  Theory(1,bin, xmean2*factor3D_x->GetBinContent(1), Qmean2*factor3D_Q->GetBinContent(1), tmean2*factor3D_t->GetBinContent(1), NBinsPhi); //BH
  Theory(2,bin, xmean2*factor3D_x->GetBinContent(1), Qmean2*factor3D_Q->GetBinContent(1), tmean2*factor3D_t->GetBinContent(1), NBinsPhi); //VGG
  Theory(3,bin, xmean2*factor3D_x->GetBinContent(1), Qmean2*factor3D_Q->GetBinContent(1), tmean2*factor3D_t->GetBinContent(1), NBinsPhi); //KM15

  // Theory curves computed at bin center
  //Theory(1,bin, 0.5*(bins[bin-1][4]+bins[bin-1][5]), 0.5*(bins[bin-1][2]+bins[bin-1][3]), 0.5*(bins[bin-1][0]+bins[bin-1][1]), NBinsPhi); //BH
  //Theory(2,bin, 0.5*(bins[bin-1][4]+bins[bin-1][5]), 0.5*(bins[bin-1][2]+bins[bin-1][3]), 0.5*(bins[bin-1][0]+bins[bin-1][1]), NBinsPhi); //VGG
  //Theory(3,bin, 0.5*(bins[bin-1][4]+bins[bin-1][5]), 0.5*(bins[bin-1][2]+bins[bin-1][3]), 0.5*(bins[bin-1][0]+bins[bin-1][1]), NBinsPhi); //KM15
  //Theory(4,bin); //GK19

  //Plot KM xsec
  inputFile.open(extXSEC + Form("KM/bin_%i.txt",bin)); // Replace with the name of the block file you want to read
  xValues.clear();
  yValues.clear();
  while (std::getline(inputFile, line)) {
	  std::istringstream iss(line);
	  iss >> x >> aux >> aux >> aux >> aux >> y;
    
	  xValues.push_back(x);
	  yValues.push_back(y);
	  //std::cout<<x<<" "<<y<<endl;
  }
  numPoints = xValues.size();
  inputFile.close();
  TGraph* graph = new TGraph(numPoints, xValues.data(), yValues.data());
  graph->SetTitle("KM15");
  graph->SetMarkerColor(kCyan);
  graph->SetLineColor(kCyan);
  graph->SetLineWidth(2);
  graph->SetTitle("KM15");

  //Plot VGG xsec
  inputFile.open(extXSEC + Form("VGG/bin_%i.txt",bin)); // Replace with the name of the block file you want to read
  xValues.clear();
  yValues.clear();
  while (std::getline(inputFile, line)) {
	  std::istringstream iss(line);
	  iss >> x >> aux >> aux >> aux >> aux >> y;
    
	  xValues.push_back(x);
	  yValues.push_back(y);
  }
  numPoints = xValues.size();
  inputFile.close();
  TGraph* graph2 = new TGraph(numPoints, xValues.data(), yValues.data());
  graph2->SetTitle("VGG");
  graph2->SetMarkerColor(kBlue);
  graph2->SetLineColor(kBlue);
  graph2->SetLineWidth(2);
  graph2->SetTitle("VGG");

  //Plot GK xsec
  inputFile.open(extXSEC + Form("GK/bin_%i.txt",bin)); // Replace with the name of the block file you want to read
  xValues.clear();
  yValues.clear();
  while (std::getline(inputFile, line)) {
	  std::istringstream iss(line);
	  iss >> x >> aux >> aux >> aux >> aux >> y;
    
	  xValues.push_back(x);
	  yValues.push_back(y);
  }
  numPoints = xValues.size();
  inputFile.close();
  TGraph* graph3 = new TGraph(numPoints, xValues.data(), yValues.data());
  graph3->SetTitle("GK19");
  graph3->SetMarkerColor(kRed);
  graph3->SetLineColor(kRed);
  graph3->SetLineWidth(2);
  graph3->SetTitle("GK19");

  //Plot BH xsec
  double x1, x2;
  int ibh=0;
  inputFile.open(extXSEC + Form("BH/bin_%i.txt",bin)); // Replace with the name of the block file you want to read
  xValues.clear();
  yValues.clear();
  while (std::getline(inputFile, line)) {
	  std::istringstream iss(line);
	  //iss >> x >> aux >> aux >> aux >> aux >> y;
    //xValues.push_back(x);

    iss >> x1 >> x2 >> aux >> aux >> aux >> aux >> aux >> aux >> y;  
    xValues.push_back((x2-x1)*(ibh + 0.5));
    
    ibh++;
    yValues.push_back(y);
  }
  numPoints = xValues.size();
  inputFile.close();
/*  
  TGraph* graph4 = new TGraph(numPoints, xValues.data(), yValues.data());
  graph4->SetMarkerColor(kRed);
  graph4->SetLineColor(kRed);
  graph4->SetLineWidth(2);
  graph4->SetLineStyle(kDashed);
  graph4->SetTitle("BH");
*/


///
  TString String_cut = (cut_bin + cut_ref).GetTitle();
  String_cut.ReplaceAll("bestCandidateFlag==1 && ", "");
  String_cut.ReplaceAll("_strip_Nuc_BDT_SIDIS", "Q2_meas");
  String_cut.ReplaceAll("strip_Q2", "Q2_meas");
  String_cut.ReplaceAll("strip_Xbj", "xB_meas");
  String_cut.ReplaceAll("t_Ph", "t_meas");
  String_cut.ReplaceAll("strip_El_P", "El_E");
  String_cut.ReplaceAll("strip_Ph_P", "Ph_E");
        TCut cut0 = TCut(String_cut);


        TChain* tree1 = new TChain("tree");
        tree1->Add(Form("/work/clas12/jsalvg/km15gen_output_%s/BH/bin_%i.root", torus.Data(), bin));
        TH1F *DVCS_bh = new TH1F("DVCS_bh","", NBinsPhi, 0, 360);
        TH1F *DVCS_bh1 = new TH1F("DVCS_bh1","", NBinsPhi, 0, 360);
        TH1F *DVCS_bh2 = new TH1F("DVCS_bh2","", NBinsPhi, 0, 360);
        DVCS_bh1->Sumw2();
        DVCS_bh2->Sumw2();
        tree1->Project("DVCS_bh1", "phi_meas", (cut0 + TCut("Q2_meas>1"))*TCut("xsec_born"));
        tree1->Project("DVCS_bh2", "phi_meas", (cut0 + TCut("Q2_meas>1")));
        DVCS_bh->Divide(DVCS_bh1, DVCS_bh2, 1, 1);

        TGraph* graph4 = new TGraph(NBinsPhi);
        for (int i = 1; i <= NBinsPhi; ++i) {
          double x = DVCS_bh->GetBinCenter(i);
          double y = DVCS_bh->GetBinContent(i);
          graph4->SetPoint(i - 1, x, y);
        }
        graph4->SetTitle("BH");
        graph4->SetMarkerStyle(20); // circular markers
        graph4->SetMarkerColor(kRed);
        graph4->SetLineColor(kRed);
        graph4->SetLineWidth(2);
        graph4->SetLineStyle(kDashed); // dashed line
        graph4->SetName("BH");
        graph4->SetTitle("BH");

///


  gStyle->SetOptTitle(1);

  ///////////////////////////////
  // Corrections to the event yield
  // Extraction of Exp xsec
  ///////////////////////////////

  //MC/DATA efficiency correction
   TChain* TBM_Data = new TChain("pDVCS");
   TBM_Data->Add(Folder + TString("../wf") + TBM_Sim); // Data
   //TBM_Data->Add("/lustre24/expphy/volatile/clas12/jsalvg/genepi_DVCS/Quality_DVCS_Train_NP.root");

   TH1F* Data_eff = new TH1F("Data_eff", "Data_eff", NBinsPhi, 0, 360);
   TH1F* MC_eff = new TH1F("MC_eff", "MC_eff", NBinsPhi, 0, 360);
   TH1F* bkg_eff = new TH1F("bkg_eff", "bkg_eff", NBinsPhi, 0, 360);
   TH1F* ratio_eff = new TH1F("ratio_eff", "ratio_eff", NBinsPhi, 0, 360);

   Data_eff->Sumw2();
   MC_eff->Sumw2();
   ratio_eff->Sumw2();
   bkg_eff->Sumw2();   

   chainData->Project("Data_eff", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))));
   TBM_Data->Project("MC_eff", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))));
   //TBM_Data ->Project("MC_eff", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + TCut(Form("strip_Q2>%f && strip_El_P>2 && strip_Ph_P<8.5", BDT_value))) * TCut(Form("xsec_rad*%f/1e8", Lumi)));
   chainBkg2->Project("bkg_eff", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * TCut("Weight"));
   
   boundaries.push_back(Data_eff->Integral());   
   Data_eff->Add(bkg_eff, -1);
  
   MC_eff->Scale(Lumi*(14.184/1e9)); //14.231, 14.184
   bkg_eff->Scale(MC_eff->Integral()/Data_eff->Integral()); //bkg is normalized to the experimental data
   MC_eff->Add(bkg_eff, -1);
  
   ratio_eff->Divide(Data_eff, MC_eff,1,1);
   ratio_eff->SetName("ratio_eff");

   std::cout<<"\nEfficiency ratio Data/MC"<<endl;
   for(int r=1; r<=NBinsPhi; r++)
   {
    std::cout<<ratio_eff->GetBinContent(r)<<" "<<MC_eff->GetBinContent(r)<<endl;
   } 
   std::cout<<"Overall: "<<Data_eff->Integral()/MC_eff->Integral()<<endl;
   double eff=Data_eff->Integral()/MC_eff->Integral();

   
  delete TBM_Data;
  delete Data_eff;
  delete MC_eff;
  /////////////////////////////

  TH1F* F_BDT = BDTEff_Corr(cut, TData, TDVCS, BDT_value, NBinsPhi);
  F_BDT->SetName("F_BDT");

  TH1F* F_rad = F_RC(NBinsPhi, Systematics); //Radiative corrections
  F_rad->SetName("F_RC");
  
  TH1F* PS_factor = Phase_Space_Factor(NBinsPhi, bin); // Phase Space volume
  //Phase_Space_Factor1(NBinsPhi, bin); // Phase Space volume
  PS_factor->SetName("PS_factor");
  TH1F* F_bin1 =  F_Bin( bin, tmean2, Qmean2, xmean2, 1, PS_factor); //Bin centering correction. From integrated xsec to xsec@3D_means
  ////TH1F* F_bin1 = F_bin_KM_model(bin, tmean2, Qmean2, xmean2);
  //F_bin1->SetName("F_Bin_Michel_Model");
  //TH1F* F_bin2 =  F_bin1;
  //F_bin2->SetName("F_Bin_Michel_Model");

  /*
  for(int r=0; r<=NBinsPhi; r++)
  {
    Systematics->SetBinError(r, Systematics->GetBinError(r) + pow(F_bin1->GetBinError(r), 2));  //Add systematics of F_bin to the total
  }
*/
  TH1F* F_BM1;// = BM_correction(NMost, bin,1); //Bin Migration correction / outdated
  TH1F* F_BM2;// = BM_correction(NMaxi, bin,2); // I saw that RooUnfold was unable to unfold, probably bins are too wide.
  //F_BM1->SetName("F_BM_1");
  //F_BM2->SetName("F_BM_2");


  TH1F* F_noRec = No_Rec_correction(Folder + TString("../wf") + TBM_Sim, MC_BM_Sim, BDT_value, NBinsPhi, Systematics); //Acceptance~rec_eff correction
  F_noRec->SetName("F_noRec"); //I am using the weighted file (ResMatching)

  /*
  TH1F* F_423_1 = F_4Dto3D(xmean2, Qmean2, tmean2,NBinsPhi,1);
  F_423_1->SetName("F_423_1");
  TH1F* F_423_2 = F_4Dto3D(xmean2, Qmean2, tmean2,NBinsPhi,2);
  F_423_2->SetName("F_423_2");

  */

  TH1F *xsec1 = new TH1F("xsec1","xsec1",NBinsPhi,0,360);
  TH1F *xsec2 = new TH1F("xsec2","xsec2",NBinsPhi,0,360);

  xsec1->Divide(NMost, F_noRec,1,1);
  xsec2->Divide(NMaxi, F_noRec,1,1);

  //xsec1->Divide(xsec1, F_BDT,1,1);
  //xsec2->Divide(xsec2, F_BDT,1,1);

  //xsec1->Divide(xsec1, F_bin1,1,1);
  //xsec2->Divide(xsec2, F_bin2,1,1);

  xsec1->Divide(xsec1, F_rad,1,1);
  xsec2->Divide(xsec2, F_rad,1,1);

  xsec1->Divide(xsec1, PS_factor,1,1);
  xsec2->Divide(xsec2, PS_factor,1,1);

  /*
  //xsec1->Divide(NMost, F_BM1,1,1);
  //xsec2->Divide(NMaxi, F_BM2,1,1);

  xsec1->Divide(xsec1, F_423_1,1,1);
  xsec2->Divide(xsec2, F_423_2,1,1);

  xsec1->Scale(1.0/(Lumi*eff));
  xsec2->Scale(1.0/(Lumi*eff));
  */
    
  xsec1->Scale(1.0/(Lumi));
  xsec2->Scale(1.0/(Lumi));

  //xsec1->Divide(xsec1, ratio_eff,1,1);
  //xsec2->Divide(xsec2, ratio_eff,1,1);
  


  double F_eff1 = 0.0;
  double F_eff2 = 0.0;
  int counter=0;
  std::cout<<"\nNormalization factor"<<endl;
  for(int t=0; t<NBinsPhi; t++)
  {
    if(xsec1->GetBinCenter(t+1)<30 || xsec1->GetBinCenter(t+1)>330) //exclude bins around 180 deg where the BH cross-section is very small and can create large fluctuations
    {
      F_eff1+=xsec1->GetBinContent(t+1)/graph4->Eval(xsec1->GetBinCenter(t+1));
      F_eff2+=xsec2->GetBinContent(t+1)/graph4->Eval(xsec2->GetBinCenter(t+1));
      counter++;
    }
    std::cout<<" "<<xsec1->GetBinContent(t+1)<<" "<<xsec2->GetBinContent(t+1)<<" "<<graph4->Eval(xsec1->GetBinCenter(t+1))<<endl;
  }
  F_eff1=F_eff1/counter;
  F_eff2=F_eff2/counter;
  std::cout<<"\nGlobal normalization factor "<<F_eff1<<" "<<F_eff2<<endl;

  //xsec1->Scale(1.0/F_eff1);
  //xsec2->Scale(1.0/F_eff2);
  //xsec2->Scale(1.0/(xsec2->GetBinContent(1)/graph4->GetPointY(0))); //For the test

  xsec1->SetTitle("Cross-section (nb); #phi (deg); #sigma (nb)");
  xsec2->SetTitle("Cross-section (nb); #phi (deg); #sigma (nb)");
  xsec1->SetLineColor(kBlack);
  xsec2->SetLineColor(kBlue);
  xsec1->SetMarkerColor(kBlack);
  xsec2->SetMarkerColor(kBlue);

  ///////////////////////////////
  // Final xsec as TGraph
  ///////////////////////////////
  TGraphErrors* xsec1gr = new TGraphErrors();
  TGraphErrors* xsec2gr = new TGraphErrors();
  TGraphErrors* xsec1gr_Sys = new TGraphErrors();
  TGraphErrors* xsec2gr_Sys = new TGraphErrors();
  double err1=0, err2=0;
  double err1_Sys=0, err2_Sys=0;

  for(int t=1; t<=NBinsPhi; t++)
    {
      //NOMINAL ERROR COMPUTATION
      err1=0;
      err2=0;
      if(NOrig->GetBinContent(t)!=0)
        err1+= pow(OrigErr1->GetBinError(t)/NOrig->GetBinContent(t),2);
      if(NMost->GetBinContent(t)!=0)
        err1+= pow(NMost->GetBinError(t)/NMost->GetBinContent(t),2) ;
      if(F_noRec->GetBinContent(t)!=0)
        err1+= pow(F_noRec->GetBinError(t)/F_noRec->GetBinContent(t),2) ;
      if(F_rad->GetBinContent(t)!=0)
        err1+= pow(F_rad->GetBinError(t)/F_rad->GetBinContent(t),2) ;

      if(NOrig->GetBinContent(t)!=0)
        err2+= pow(OrigErr2->GetBinError(t)/NOrig->GetBinContent(t),2) ;
      if(NMaxi->GetBinContent(t)!=0)
        err2+= pow(NMaxi->GetBinError(t)/NMaxi->GetBinContent(t),2) ;
      if(F_noRec->GetBinContent(t)!=0)
        err2+= pow(F_noRec->GetBinError(t)/F_noRec->GetBinContent(t),2) ;
      if(F_rad->GetBinContent(t)!=0)
        err2+= pow(F_rad->GetBinError(t)/F_rad->GetBinContent(t),2) ;

      err1 = sqrt(err1) * xsec1->GetBinContent(t);
      err2 = sqrt(err2) * xsec2->GetBinContent(t);
      err1_Sys = sqrt(Systematics->GetBinError(t)) * xsec1->GetBinContent(t);
      err2_Sys = sqrt(Systematics->GetBinError(t)) * xsec2->GetBinContent(t);

      xsec1->SetBinError(t,err1);
      xsec2->SetBinError(t,err2);

      printf(" phi %6.2f %6.2f, xsection %6.2f %6.2f, Stat errors %4.2f %4.2f (%4.2f%%), sys error %4.2f (%4.2f%%)\n",means1.at(t-1).at(0),means2.at(t-1).at(0),xsec1->GetBinContent(t),xsec2->GetBinContent(t),err1,err2,err2*100/xsec2->GetBinContent(t),err2_Sys,err2_Sys*100/xsec2->GetBinContent(t));
      //std::cout<<" phi "<<means1.at(t-1).at(0)<<" "<<means2.at(t-1).at(0)<<" xsection "<<xsec1->GetBinContent(t)<<" "<<xsec2->GetBinContent(t)<<" Stat errors "<<err1<<" "<<err2<<" ("<<err2*100/xsec2->GetBinContent(t)<<" %)"<<" Sys error "<<err2_Sys<<" ("<<err2_Sys*100/xsec2->GetBinContent(t)<<"%)"<<endl;
      if(means1.at(t-1).at(0)>1)
      {
        xsec1gr->SetPoint(xsec1gr->GetN(), means1.at(t-1).at(0), xsec1->GetBinContent(t));
        xsec1gr_Sys->SetPoint(xsec1gr_Sys->GetN(), means1.at(t-1).at(0), xsec1->GetBinContent(t));
        xsec1gr->SetPointError(xsec1gr->GetN()-1, means1.at(t-1).at(1), err1);  
        xsec1gr_Sys->SetPointError(xsec1gr_Sys->GetN()-1, means1.at(t-1).at(1), err1_Sys);
      }
      if(means2.at(t-1).at(0)>1)
      {
      xsec2gr->SetPoint(xsec2gr->GetN(), means2.at(t-1).at(0), xsec2->GetBinContent(t));
      xsec2gr_Sys->SetPoint(xsec2gr_Sys->GetN(), means2.at(t-1).at(0), xsec2->GetBinContent(t));
      xsec2gr->SetPointError(xsec2gr->GetN()-1, means2.at(t-1).at(1), err2);
      xsec2gr_Sys->SetPointError(xsec2gr_Sys->GetN()-1, means2.at(t-1).at(1), err2_Sys);
      }
    }
  xsec1gr->SetTitle("Cross-section (nb); #phi (deg); #sigma (nb)");
  xsec2gr->SetTitle("Cross-section (nb); #phi (deg); #sigma (nb)");
  xsec1gr->SetName("xsec1gr");    
  xsec2gr->SetName("xsec2gr");    

  ///////////////////////////////
  // Save all corrections to an output file
  ///////////////////////////////
  TFile *outputFile = new TFile(Folder + TString("xsec_dists.root"), "RECREATE");
  NMost->Write();
  NMaxi->Write();
  NOrig->Write();
  PS_factor->Write();
  F_noRec->Write();
  //F_bin1->Write();
  F_rad->Write();
  //F_BDT->Write();
  Systematics->Write();

  /*
  F_BM1->Write();
  F_BM2->Write();

  F_423_1->Write();
  F_423_2->Write();
  */

  xsec1->Write();
  xsec2->Write();
  xsec1gr->Write();
  xsec2gr->Write();
  xsec1gr_Sys->Write();
  xsec2gr_Sys->Write();
  graph->Write();
  graph2->Write();
  graph3->Write();
  graph4->Write();
  // Close the output file
  outputFile->Close();
  std::cout<<"\nplots saved succesfully !"<<endl;

  ///////////////////////////////
  // Final result plot
  ///////////////////////////////
  xsec1gr->SetMarkerStyle(20);
  xsec2gr->SetMarkerStyle(20);
  xsec1gr->SetLineColor(kBlack);
  xsec2gr->SetLineColor(kBlue);
  xsec1gr->SetMarkerColor(kBlack);
  xsec1gr_Sys->SetMarkerColor(kBlack);
  xsec2gr->SetMarkerColor(kBlue);
  xsec2gr_Sys->SetMarkerColor(kBlue);
  xsec1gr_Sys->SetFillColorAlpha(kBlack-10,0.6);
  xsec2gr_Sys->SetFillColorAlpha(kBlue-10,0.6);
  xsec1gr->SetMarkerSize(0.5);
  xsec2gr->SetMarkerSize(0.5);
  xsec1gr->SetMarkerSize(0.5);
  xsec2gr->SetMarkerSize(0.5);
  xsec1gr->SetLineWidth(2);
  xsec2gr->SetLineWidth(2);

  xsec1gr->GetXaxis()->SetLimits(0,360);
  xsec2gr->GetXaxis()->SetLimits(0,360);

TCanvas *canvas2 = new TCanvas("canvas2","canvas2",700,500);
  TMultiGraph* mg = new TMultiGraph();
  //gPad->SetLogy();
  //mg->Add(xsec1gr_Sys,"3");
  //mg->Add(xsec1gr,"P");
  mg->Add(xsec2gr_Sys,"2");
  mg->Add(xsec2gr,"P");
  //mg->Add(graph,"l");
  //mg->Add(graph2,"l");
  //mg->Add(graph3,"l");
  mg->Add(graph4,"l");
  mg->Draw("A");
 
  mg->SetTitle(Form("%.2f<Q^{2}(GeV^{2})<%.2f, %.2f<x_{B}<%.2f, %.2f<t(GeV^{2})<%.2f; #phi (deg); Unnormalized #sigma (nb)",boundaries.at(2), boundaries.at(3), boundaries.at(4), boundaries.at(5), boundaries.at(0), boundaries.at(1)));
  mg->GetXaxis()->SetTitleSize(0.06);
  mg->GetYaxis()->SetTitleSize(0.06);
  mg->GetXaxis()->SetLabelSize(0.05);
  mg->GetYaxis()->SetLabelSize(0.05);
  mg->GetYaxis()->SetTitleOffset(0.7);
  mg->GetXaxis()->SetTitleOffset(0.5);
  mg->GetYaxis()->SetNdivisions(6);
  mg->GetXaxis()->SetNdivisions(4);

  TLegend* legend = new TLegend();//0.3,0.6,0.6,0.88);
  //legend->AddEntry(xsec1gr,"Method 1","lep");
  legend->AddEntry(xsec2gr,"e#gamma CLAS12","lep");
  legend->AddEntry(graph,"KM15","l");
  legend->AddEntry(graph2,"VGG","l");
  //legend->AddEntry(graph3,"GK19","l");
  legend->AddEntry(graph4,"BH","l");
  //legend->Draw();

  ///////////////////////////////
  // xsec at generator level (for curiosity/cross-check purposes)
  ///////////////////////////////
  TFile *ndvcsFile = new TFile(Folder + TString("NDVCS_hist.root"), "UPDATE");
  TH1F *NDVCS = nullptr;
  if (ndvcsFile->Get("NDVCS")) {
    NDVCS = dynamic_cast<TH1F*>(ndvcsFile->Get("NDVCS"));
  } else {
    //gSystem->Exec(Form("rm -rf %s%sNDVCS_hist.root",dir.Data(), Folder.Data()));
    NDVCS = new TH1F("NDVCS", "Original Data", NBinsPhi, 0, 360);
    TChain* DVCSTreeMC = new TChain("pDVCS");
    DVCSTreeMC->Add(MC_BM_Sim);
    DVCSTreeMC->Project("NDVCS", "Phi_Nuc", cut + cut_bin + cut_kin + cut_sel); //Phi_Nuc is the generated Phi in the bin
    NDVCS->SetMarkerStyle(20);
    NDVCS->SetMarkerColor(kRed);
    //NDVCS->Divide(F_bin1);
    NDVCS->Write("NDVCS");
  }
  //NDVCS->Divide(PS_factor);
  NDVCS->Scale((13.467e3/10e7)*2.*TMath::Pi()/NBinsPhi);
  //NDVCS->Scale(graph4->Eval(NDVCS->GetBinCenter(1))/NDVCS->GetBinContent(1));
  //NDVCS->Draw("E0 SAME"); //For the Test
  std::cout<<"\nGenerated events dvcsgen"<<endl;
  for(int i=1; i<=NBinsPhi; i++)
  {
    std::cout<<" "<<NDVCS->GetBinContent(i)<<endl;
  }
  canvas2->Print(Folder + TString("RGA_vs_This_xsec.pdf"));
  //gSystem->Exec(Form("rm -r %s%sdvcs* %s%sgepard %s%s*.py %s%sF_*",dir.Data(), Folder.Data(),dir.Data(), Folder.Data(),dir.Data(), Folder.Data(),dir.Data(), Folder.Data()));

  ndvcsFile->Close();
  delete ndvcsFile;
  
  delete xsec1;
  delete xsec2;
  delete xsec1gr;
  delete xsec1gr_Sys;
  delete xsec2gr;
  delete xsec2gr_Sys;

  delete PS_factor;
  delete F_noRec;
  //delete F_bin1;
  //delete F_bin2;
  delete F_rad;
  //delete F_BDT;

  /*
  delete F_BM1;
  delete F_BM2;

  delete F_423_1;
  delete F_423_2;
  */
  
  delete NOrig;
  delete NMost;
  delete NMaxi;
  delete OrigErr1;
  delete OrigErr2;

  delete factor_t;
  delete factor_Q;
  delete factor_x;
  delete factor_p;

  delete factor3D_t;
  delete factor3D_Q;
  delete factor3D_x;

  delete canvas2;
  
  Folder = Folder_old;

  return;
}

