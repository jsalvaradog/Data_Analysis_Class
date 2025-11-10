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

  double factor=1;
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
  TH1F *hist2c_Sim = new TH1F("hist2c_Sim","",100, 0., 5);
  TH1F *hist3c_Sim = new TH1F("hist3c_Sim","",100, -1, 0.);

  TH1F *hist4c_Sim = new TH1F("hist4c_Sim","",100,-2,2);
  TH1F *hist5c_Sim = new TH1F("hist5c_Sim","",100, 0,4);
  TH1F *hist6c_Sim = new TH1F("hist6c_Sim","#Delta t (GeV^{2})",100,-0.2,0.4);  
  TH1F *hist7c_Sim = new TH1F("hist7c_Sim","#theta_{e} (deg)",100,0,100);
  TH1F *hist8c_Sim = new TH1F("hist8c_Sim","#theta_{#gamma X} (deg)",100,0,2);
  TH1F *hist9c_Sim = new TH1F("hist9c_Sim","#theta_{#gamma} (deg)",100,0,100);
  
  TH1F *hist1c_Data = new TH1F("hist1c_Data","",100, 0., 18.);
  TH1F *hist2c_Data = new TH1F("hist2c_Data","",100, 0., 5);
  TH1F *hist3c_Data = new TH1F("hist3c_Data","",100, -1., 0.);

  TH1F *hist4c_Data = new TH1F("hist4c_Data","",100,-2,2);
  TH1F *hist5c_Data = new TH1F("hist5c_Data","",100, 0,4);
  TH1F *hist6c_Data = new TH1F("hist6c_Data","#Delta t (GeV^{2})",100,-0.2,0.4);  
  TH1F *hist7c_Data = new TH1F("hist7c_Data","#theta_{#e} (deg)",100,0,100);
  TH1F *hist8c_Data = new TH1F("hist8c_Data","#theta_{#gamma X} (deg)",100,0,2);
  TH1F *hist9c_Data = new TH1F("hist9c_Data","#theta_{#gamma} (deg)",100,0,100);

  TH1F *hist1c_Pi0 = new TH1F("hist1c_Pi0","",100, 0., 18.);
  TH1F *hist2c_Pi0 = new TH1F("hist2c_Pi0","",100, 0, 5);
  TH1F *hist3c_Pi0 = new TH1F("hist3c_Pi0","",100, -1., 0.);
  
  TH1F *hist4c_Pi0 = new TH1F("hist4c_Pi0","",100,-2,2);
  TH1F *hist5c_Pi0 = new TH1F("hist5c_Pi0","",100, 0,4);
  TH1F *hist6c_Pi0 = new TH1F("hist6c_Pi0","#Delta t (GeV^{2})",100,-0.2,0.4);  
  TH1F *hist7c_Pi0 = new TH1F("hist7c_Pi0","#theta_{#e} (deg)",100,0,100);
  TH1F *hist8c_Pi0 = new TH1F("hist8c_Pi0","#theta_{#gamma X} (deg)",100,0,2);
  TH1F *hist9c_Pi0 = new TH1F("hist9c_Pi0","#theta_{#gamma} (deg)",100,0,100);

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

  pDVCS_Pi0->Project("hist1c_Pi0", p1, cut);
  pDVCS_Pi0->Project("hist2c_Pi0", p2, cut);
  pDVCS_Pi0->Project("hist3c_Pi0", p3, cut);
  //pDVCS_Pi0->Project("hist4c_Pi0", p4, cut);
  //pDVCS_Pi0->Project("hist5c_Pi0", p5, cut);
  //pDVCS_Pi0->Project("hist6c_Pi0", p6, cut);
  //pDVCS_Pi0->Project("hist7c_Pi0", p7, cut);
  //pDVCS_Pi0->Project("hist8c_Pi0", p8, cut);
  //pDVCS_Pi0->Project("hist9c_Pi0", p9, cut);



  c1->cd(1);
  hist1c_Sim->Scale(factor/hist1c_Sim->GetEntries());
  hist1c_Sim->SetLineColor(kBlack);
  hist1c_Data->Scale(factor/hist1c_Data->GetEntries());
  hist1c_Data->SetLineColor(kRed);
  hist1c_Pi0->Scale(factor/hist1c_Pi0->GetEntries());
  hist1c_Pi0->SetLineColor(kBlue);

  hs1->Add(hist1c_Sim);
  hs1->Add(hist1c_Data);
  hs1->Add(hist1c_Pi0);
  hs1->Draw("nostack,hist");
    
  c1->cd(2);
  hist2c_Sim->Scale(factor/hist2c_Sim->GetEntries());
  hist2c_Sim->SetLineColor(kBlack);
  hist2c_Data->Scale(factor/hist2c_Data->GetEntries());
  hist2c_Data->SetLineColor(kRed);
  hist2c_Pi0->Scale(factor/hist2c_Pi0->GetEntries());
  hist2c_Pi0->SetLineColor(kBlue);

  hs2->Add(hist2c_Sim);
  hs2->Add(hist2c_Data);
  hs2->Add(hist2c_Pi0);
  hs2->Draw("nostack,hist");


  c1->cd(3);
  hist3c_Sim->Scale(factor/hist3c_Sim->GetEntries());
  hist3c_Sim->SetLineColor(kBlack);
  hist3c_Data->Scale(factor/hist3c_Data->GetEntries());
  hist3c_Data->SetLineColor(kRed);
  hist3c_Pi0->Scale(factor/hist3c_Pi0->GetEntries());
  hist3c_Pi0->SetLineColor(kBlue);

  hs3->Add(hist3c_Sim);
  hs3->Add(hist3c_Data);
  hs3->Add(hist3c_Pi0);
  hs3->Draw("nostack,hist");

  double axtit_size = 0.06;
  double axlab_size = 0.04;
  double axXtit_offs = 0.7;
  double axYtit_offs = -0.4;
  
  TString t1="M^{2}_{e X} (GeV^{2})";
  TString t2="M^{2}_{e#gamma X} (GeV^{2})";
  TString t3="t (GeV^{2})";
  
  hs1->GetXaxis()->SetTitle(t1);
  hs1->GetYaxis()->SetTitle("counts/total events");
  hs1->GetXaxis()->SetTitleSize(axtit_size);
  hs1->GetYaxis()->SetTitleSize(axtit_size);
  hs1->GetXaxis()->SetTitleOffset(axXtit_offs);
  hs1->GetYaxis()->SetTitleOffset(axYtit_offs);
  hs1->GetXaxis()->SetLabelSize(axlab_size);
  hs1->GetYaxis()->SetLabelSize(axlab_size);

  hs2->GetXaxis()->SetTitle(t2);
  hs2->GetYaxis()->SetTitle("counts/total events");
  hs2->GetXaxis()->SetTitleSize(axtit_size);
  hs2->GetYaxis()->SetTitleSize(axtit_size);
  hs2->GetXaxis()->SetTitleOffset(axXtit_offs);
  hs2->GetYaxis()->SetTitleOffset(axYtit_offs);
  hs2->GetXaxis()->SetLabelSize(axlab_size);
  hs2->GetYaxis()->SetLabelSize(axlab_size);

  hs3->GetXaxis()->SetTitle(t3);
  hs3->GetYaxis()->SetTitle("counts/total events");
  hs3->GetXaxis()->SetTitleSize(axtit_size);
  hs3->GetYaxis()->SetTitleSize(axtit_size);
  hs3->GetXaxis()->SetTitleOffset(axXtit_offs);
  hs3->GetYaxis()->SetTitleOffset(axYtit_offs);
  hs3->GetXaxis()->SetLabelSize(axlab_size);
  hs3->GetYaxis()->SetLabelSize(axlab_size);
   
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

