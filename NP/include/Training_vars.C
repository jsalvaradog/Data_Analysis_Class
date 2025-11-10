void BDT::Training_vars(TString Data, TString MC_DVCS, TString MC_Pi0, TCut cut){
  gStyle->SetOptStat(0);
  
  TCanvas *c1 = new TCanvas("c1","Histograms",1500,500);
  c1->Divide(3,1);

  TFile *input2 = new TFile(Data,"READ");
  TTree *pDVCS_Data = (TTree*)input2->Get("pDVCS");
  
  TFile *input3 = new TFile(MC_DVCS,"READ");
  TTree *pDVCS_Sim = (TTree*)input3->Get("pDVCS");

  TFile *input4 = new TFile(MC_Pi0,"READ");
  TTree *pDVCS_Pi0;
  if( input4->GetListOfKeys()->Contains("pDVCS") )
    pDVCS_Pi0     = (TTree*)input4->Get("pDVCS");
  else
    pDVCS_Pi0     = (TTree*)input4->Get("eppi0");

  TFile *input5 = new TFile("/lustre24/expphy/volatile/clas12/jsalvg/simulation/clasdis/inb/1gamma/Quality_Pi_as_DVCS_NP.root","READ");
  TTree *pDVCS_Pi0_2 = (TTree*)input5->Get("pDVCS");

  auto hs1 = new THStack("hs1","M^{2}_{eX} (GeV^{2})");
  auto hs2 = new THStack("hs2","M^{2}_{e#gamma X} (GeV^{2})");
  auto hs3 = new THStack("hs3","t (GeV^{2})");

  auto hs4 = new THStack("hs4","#Delta #phi");
  auto hs5 = new THStack("hs5","#theta_{#gamma X} (deg)");
  auto hs6 = new THStack("hs6","");
  auto hs7 = new THStack("hs7","");
  auto hs8 = new THStack("hs8","");
  auto hs9 = new THStack("hs9","");

  TH1F *hist1c_Sim = new TH1F("hist1c_Sim","",100, 0., 18.);
  TH1F *hist2c_Sim = new TH1F("hist2c_Sim","",100, 0., 3);
  TH1F *hist3c_Sim = new TH1F("hist3c_Sim","",100, -1, 0.);

  TH1F *hist4c_Sim = new TH1F("hist4c_Sim","",100,-2,2);
  TH1F *hist5c_Sim = new TH1F("hist5c_Sim","",100, 0,4);
  TH1F *hist6c_Sim = new TH1F("hist6c_Sim","#Delta t (GeV^{2})",100,-0.2,0.4);  
  TH1F *hist7c_Sim = new TH1F("hist7c_Sim","#theta_{e} (deg)",100,0,100);
  TH1F *hist8c_Sim = new TH1F("hist8c_Sim","#theta_{#gamma X} (deg)",100,0,2);
  TH1F *hist9c_Sim = new TH1F("hist9c_Sim","#theta_{#gamma} (deg)",100,0,100);
  
  TH1F *hist1c_Data = new TH1F("hist1c_Data","",100, 0., 18.);
  TH1F *hist2c_Data = new TH1F("hist2c_Data","",100, 0., 3);
  TH1F *hist3c_Data = new TH1F("hist3c_Data","",100, -1., 0.);

  TH1F *hist4c_Data = new TH1F("hist4c_Data","",100,-2,2);
  TH1F *hist5c_Data = new TH1F("hist5c_Data","",100, 0,4);
  TH1F *hist6c_Data = new TH1F("hist6c_Data","#Delta t (GeV^{2})",100,-0.2,0.4);  
  TH1F *hist7c_Data = new TH1F("hist7c_Data","#theta_{#e} (deg)",100,0,100);
  TH1F *hist8c_Data = new TH1F("hist8c_Data","#theta_{#gamma X} (deg)",100,0,2);
  TH1F *hist9c_Data = new TH1F("hist9c_Data","#theta_{#gamma} (deg)",100,0,100);

  TH1F *hist1c_Pi0 = new TH1F("hist1c_Pi0","",100, 0., 18.);
  TH1F *hist2c_Pi0 = new TH1F("hist2c_Pi0","",100, 0, 3);
  TH1F *hist3c_Pi0 = new TH1F("hist3c_Pi0","",100, -1., 0.);
  
  TH1F *hist4c_Pi0 = new TH1F("hist4c_Pi0","",100,-2,2);
  TH1F *hist5c_Pi0 = new TH1F("hist5c_Pi0","",100, 0,4);
  TH1F *hist6c_Pi0 = new TH1F("hist6c_Pi0","#Delta t (GeV^{2})",100,-0.2,0.4);  
  TH1F *hist7c_Pi0 = new TH1F("hist7c_Pi0","#theta_{#e} (deg)",100,0,100);
  TH1F *hist8c_Pi0 = new TH1F("hist8c_Pi0","#theta_{#gamma X} (deg)",100,0,2);
  TH1F *hist9c_Pi0 = new TH1F("hist9c_Pi0","#theta_{#gamma} (deg)",100,0,100);

  TH1F *hist1c_Pi0_2 = new TH1F("hist1c_Pi0_2","",100, 0., 18.);
  TH1F *hist2c_Pi0_2 = new TH1F("hist2c_Pi0_2","",100, 0, 3);
  TH1F *hist3c_Pi0_2 = new TH1F("hist3c_Pi0_2","",100, -1., 0.);

  TH1F *hist1c_SimAdd = new TH1F("hist1c_SimAdd","DVCS + #pi^{0}",100, 0., 18.);
  TH1F *hist2c_SimAdd = new TH1F("hist2c_SimAdd","DVCS + #pi^{0}",100, 0., 3);
  TH1F *hist3c_SimAdd = new TH1F("hist3c_SimAdd","DVCS + #pi^{0}",100, -1, 0.);

  //Variables to plot
  const char *p1="mm2_e";
  const char *p2="mm2_eg";
  const char *p3="t_Ph";

  const char *p4="delta_Phi";
  const char *p5="theta_gamma_X";
  const char *p6="delta_t";
  const char *p7="strip_El_Theta";
  const char *p8="theta_gamma_X";
  const char *p9="strip_Ph_Theta";
  
  pDVCS_Sim->Project("hist1c_Sim", p1, cut);
  pDVCS_Sim->Project("hist2c_Sim", p2, cut);
  pDVCS_Sim->Project("hist3c_Sim", p3, cut);
  //pDVCS_Sim->Project("hist1c_Sim", p1, cut*TCut("40.09*1e3*xsec_born/99580000"));
  //pDVCS_Sim->Project("hist2c_Sim", p2, cut*TCut("40.09*1e3*xsec_born/99580000"));
  //pDVCS_Sim->Project("hist3c_Sim", p3, cut*TCut("40.09*1e3*xsec_born/99580000"));
  
  //pDVCS_Sim->Project("hist4c_Sim", p4, cut);
  //pDVCS_Sim->Project("hist5c_Sim", p5, cut);
  //pDVCS_Sim->Project("hist6c_Sim", p6, cut);
  //pDVCS_Sim->Project("hist7c_Sim", p7, cut);
  //pDVCS_Sim->Project("hist8c_Sim", p8, cut);
  //pDVCS_Sim->Project("hist9c_Sim", p9, cut);

  pDVCS_Data->Project("hist1c_Data", p1, cut);
  pDVCS_Data->Project("hist2c_Data", p2, cut);
  pDVCS_Data->Project("hist3c_Data", p3, cut);
  //pDVCS_Data->Project("hist4c_Data", p4, cut);
  //pDVCS_Data->Project("hist5c_Data", p5, cut);
  //pDVCS_Data->Project("hist6c_Data", p6, cut);
  //pDVCS_Data->Project("hist7c_Data", p7, cut);
  //pDVCS_Data->Project("hist8c_Data", p8, cut);
  //pDVCS_Data->Project("hist9c_Data", p9, cut);

  pDVCS_Pi0->Project("hist1c_Pi0", p1, cut*TCut("40.09*1e6*xsec_born/(10000*10000)"));
  pDVCS_Pi0->Project("hist2c_Pi0", p2, cut*TCut("40.09*1e6*xsec_born/(10000*10000)"));
  pDVCS_Pi0->Project("hist3c_Pi0", p3, cut*TCut("40.09*1e6*xsec_born/(10000*10000)"));
  //pDVCS_Pi0->Project("hist4c_Pi0", p4, cut);
  //pDVCS_Pi0->Project("hist5c_Pi0", p5, cut);
  //pDVCS_Pi0->Project("hist6c_Pi0", p6, cut);
  //pDVCS_Pi0->Project("hist7c_Pi0", p7, cut);
  //pDVCS_Pi0->Project("hist8c_Pi0", p8, cut);
  //pDVCS_Pi0->Project("hist9c_Pi0", p9, cut);

  pDVCS_Pi0_2->Project("hist1c_Pi0_2", p1, (cut + TCut("strip_Ph_Theta>5"))*TCut("40.09*1e3*xsec_born/(999900000)"));
  pDVCS_Pi0_2->Project("hist2c_Pi0_2", p2, (cut + TCut("strip_Ph_Theta>5"))*TCut("40.09*1e3*xsec_born/(999900000)"));
  pDVCS_Pi0_2->Project("hist3c_Pi0_2", p3, (cut + TCut("strip_Ph_Theta>5"))*TCut("40.09*1e3*xsec_born/(999900000)"));
  
  double factor=1, factor_pi0=1, factor_sidis=1;

  //factor=0.25; //Bin 8 //SIDIS only on FD. Add cut by hand
  //factor_pi0=1.6;
  //factor_sidis=1.0;

  //factor=0.45; //Bin 9
  //factor_pi0=1.5;
  //factor_sidis=0.2;

  //factor=0.5; //Bin 10
  //factor_pi0=1.5;
  //factor_sidis=0.2;

  //factor=0.6; //Bin 11 & 12
  //factor_pi0=1.2;
  //factor_sidis=0.2;

  //factor=0.55; //Bin 13
  //factor_pi0=1.3;
  //factor_sidis=0.2;

  //factor=0.5; //Bin 14
  //factor_pi0=2.0;
  //factor_sidis=0.2;

  factor=0.41; //Global
  factor_pi0=0.25;
  factor_sidis=1.0;

  //factor=0.65; //FT photons
  //factor_pi0=1.2; //FT photons
  //factor_sidis=1.0; //FT photons

  //factor=0.12; //FD photons
  //factor_pi0=0.08; //FD photons
  //factor_sidis=1.0; //FD photons

  hist1c_Sim->Scale(factor*hist1c_Data->GetEntries()/hist1c_Sim->GetEntries());
  hist2c_Sim->Scale(factor*hist2c_Data->GetEntries()/hist2c_Sim->GetEntries());
  hist3c_Sim->Scale(factor*hist3c_Data->GetEntries()/hist3c_Sim->GetEntries());

  hist1c_Pi0->Scale(factor_pi0);
  hist2c_Pi0->Scale(factor_pi0);
  hist3c_Pi0->Scale(factor_pi0);

  hist1c_Pi0_2->Scale(factor_sidis);
  hist2c_Pi0_2->Scale(factor_sidis);
  hist3c_Pi0_2->Scale(factor_sidis);

  hist1c_SimAdd->Add(hist1c_Sim, hist1c_Pi0,1,1);
  hist2c_SimAdd->Add(hist2c_Sim, hist2c_Pi0,1,1);
  hist3c_SimAdd->Add(hist3c_Sim, hist3c_Pi0,1,1);

  hist1c_SimAdd->Add(hist1c_SimAdd, hist1c_Pi0_2,1,1);
  hist2c_SimAdd->Add(hist2c_SimAdd, hist2c_Pi0_2,1,1);
  hist3c_SimAdd->Add(hist3c_SimAdd, hist3c_Pi0_2,1,1);

  hist1c_SimAdd->SetLineColor(kCyan);
  hist2c_SimAdd->SetLineColor(kCyan);
  hist3c_SimAdd->SetLineColor(kCyan);

  hist1c_Pi0_2->SetLineColor(kGreen);
  hist2c_Pi0_2->SetLineColor(kGreen);
  hist3c_Pi0_2->SetLineColor(kGreen);

  c1->cd(1);
  hist1c_Sim->SetLineColor(kBlack);
  hist1c_Data->SetLineColor(kRed);
  hist1c_Pi0->SetLineColor(kBlue);

  hs1->Add(hist1c_Sim);
  hs1->Add(hist1c_Data);
  hs1->Add(hist1c_Pi0);
  hs1->Add(hist1c_Pi0_2);
  //hs1->Add(hist1c_SimAdd);
  hs1->Draw("nostack,hist");
    
  c1->cd(2);
  hist2c_Sim->SetLineColor(kBlack);
  hist2c_Data->SetLineColor(kRed);
  hist2c_Pi0->SetLineColor(kBlue);

  hs2->Add(hist2c_Sim);
  hs2->Add(hist2c_Data);
  hs2->Add(hist2c_Pi0);
  hs2->Add(hist2c_Pi0_2);
  //hs2->Add(hist2c_SimAdd);
  hs2->Draw("nostack,hist");


  c1->cd(3);
  hist3c_Sim->SetLineColor(kBlack);
  hist3c_Data->SetLineColor(kRed);
  hist3c_Pi0->SetLineColor(kBlue);

  hs3->Add(hist3c_Sim);
  hs3->Add(hist3c_Data);
  hs3->Add(hist3c_Pi0);
  hs3->Add(hist3c_Pi0_2);
  //hs3->Add(hist3c_SimAdd);
  hs3->Draw("nostack,hist");

  TLegend *legend = new TLegend(0.1, 0.6, 0.5, 0.9); // Position of the legend
  legend->AddEntry(hist1c_Data, "Data", "l");
  legend->AddEntry(hist1c_Sim, "DVCS MC", "l");
  legend->AddEntry(hist1c_Pi0, "#pi^{0} MC", "l");
  legend->AddEntry(hist1c_Pi0_2, "Sidis MC", "l");
  //legend->AddEntry(hist1c_SimAdd, "Total MC", "l");
  legend->Draw();
   

  /*  c1->cd(4);
  hist4c_Sim->Scale(factor/hist4c_Sim->GetEntries());
  hist4c_Sim->SetLineColor(kBlack);
  hist4c_Data->Scale(factor/hist4c_Data->GetEntries());
  hist4c_Data->SetLineColor(kRed);
  hist4c_Pi0->Scale(factor/hist4c_Pi0->GetEntries());
  hist4c_Pi0->SetLineColor(kBlue);

  hs4->Add(hist4c_Sim);
  hs4->Add(hist4c_Data);
  hs4->Add(hist4c_Pi0);
  hs4->Draw("nostack,hist");

  
  c1->cd(5);
  hist5c_Data->Scale(factor/hist5c_Data->GetEntries());
  hist5c_Data->SetLineColor(kRed);
  hist5c_Sim->Scale(factor/hist5c_Sim->GetEntries());
  hist5c_Sim->SetLineColor(kBlack);
  hist5c_Pi0->Scale(factor/hist5c_Pi0->GetEntries());
  hist5c_Pi0->SetLineColor(kBlue);

  hs5->Add(hist5c_Sim);
  hs5->Add(hist5c_Data);
  hs5->Add(hist5c_Pi0);
  hs5->Draw("nostack,hist");
  
  
  c1->cd(6);
  hist6c_Sim->Scale(factor/hist6c_Sim->GetEntries());
  hist6c_Sim->SetLineColor(kBlack);
  hist6c_Data->Scale(factor/hist6c_Data->GetEntries());
  hist6c_Data->SetLineColor(kRed);
  hist6c_Pi0->Scale(factor/hist6c_Pi0->GetEntries());
  hist6c_Pi0->SetLineColor(kBlue);

  hs6->Add(hist6c_Sim);
  hs6->Add(hist6c_Data);
  hs6->Add(hist6c_Pi0);
  hs6->Draw("nostack,hist");
  
  c1->cd(7);
  hist7c_Sim->Scale(factor/hist7c_Sim->GetEntries());
  hist7c_Sim->SetLineColor(kBlack);
  hist7c_Data->Scale(factor/hist7c_Data->GetEntries());
  hist7c_Data->SetLineColor(kRed);
  hist7c_Pi0->Scale(factor/hist7c_Pi0->GetEntries());
  hist7c_Pi0->SetLineColor(kBlue);

  hs7->Add(hist7c_Sim);
  hs7->Add(hist7c_Data);
  hs7->Add(hist7c_Pi0);
  hs7->Draw("nostack,hist");

  c1->cd(8);
  hist8c_Sim->Scale(factor/hist8c_Sim->GetEntries());
  hist8c_Sim->SetLineColor(kBlack);
  hist8c_Data->Scale(factor/hist8c_Data->GetEntries());
  hist8c_Data->SetLineColor(kRed);
  hist8c_Pi0->Scale(factor/hist8c_Pi0->GetEntries());
  hist8c_Pi0->SetLineColor(kBlue);

  hs8->Add(hist8c_Sim);
  hs8->Add(hist8c_Data);
  hs8->Add(hist8c_Pi0);
  hs8->Draw("nostack,hist");

  c1->cd(9);
  hist9c_Sim->Scale(factor/hist9c_Sim->GetEntries());
  hist9c_Sim->SetLineColor(kBlack);
  hist9c_Data->Scale(factor/hist9c_Data->GetEntries());
  hist9c_Data->SetLineColor(kRed);
  hist9c_Pi0->Scale(factor/hist9c_Pi0->GetEntries());
  hist9c_Pi0->SetLineColor(kBlue);

  hs9->Add(hist9c_Sim);
  hs9->Add(hist9c_Data);
  hs9->Add(hist9c_Pi0);
  hs9->Draw("nostack,hist");
  
  
  // input->Close();
  */
  c1->Print(Folder + TString("Training_vars.pdf"));
  
  delete hist1c_Sim;
  delete hist1c_Data;
  delete hist1c_Pi0;
  delete hist2c_Sim;
  delete hist2c_Data;
  delete hist2c_Pi0;
  delete hist3c_Sim;
  delete hist3c_Data;
  delete hist3c_Pi0;
  delete hist4c_Sim;
  delete hist4c_Data;
  delete hist4c_Pi0;
  delete hist5c_Sim;
  delete hist5c_Data;
  delete hist5c_Pi0;
  delete hist6c_Sim;
  delete hist6c_Data;
  delete hist6c_Pi0;
  delete hist7c_Sim;
  delete hist7c_Data;
  delete hist7c_Pi0;
  delete hist8c_Sim;
  delete hist8c_Data;
  delete hist8c_Pi0;
  delete hist9c_Sim;
  delete hist9c_Data;
  delete hist9c_Pi0;

  delete hist1c_SimAdd;
  delete hist2c_SimAdd;
  delete hist3c_SimAdd;

  delete c1;
  delete hs1;
  delete hs2;
  delete hs3;
  delete hs4;
  delete hs5;
  delete hs6;
  delete hs7;
  delete hs8;
  delete hs9;

  delete pDVCS_Data;
  delete pDVCS_Sim;
  delete pDVCS_Pi0;

  input2->Close();
  input3->Close();
  input4->Close();

  delete input2;
  delete input3;
  delete input4;

}

