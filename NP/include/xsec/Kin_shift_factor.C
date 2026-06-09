void BDT::kin_shift_factor(std::vector<vector<double>> means1,std::vector<vector<double>> means2, int NBinsPhi)
{
  ///////////////////////////////
  // Get shift of kinematics
  // It was used for the 4to3 correction. Now it is irrelevant
  // I keep it just in case
  ///////////////////////////////
  TGraphErrors *t_bef1 = new TGraphErrors();
  TGraphErrors *Q_bef1 = new TGraphErrors();
  TGraphErrors *x_bef1 = new TGraphErrors();
  TGraphErrors *t_aft1 = new TGraphErrors();
  TGraphErrors *Q_aft1 = new TGraphErrors();
  TGraphErrors *x_aft1 = new TGraphErrors();

  TGraphErrors *t_bef2 = new TGraphErrors();
  TGraphErrors *Q_bef2 = new TGraphErrors();
  TGraphErrors *x_bef2 = new TGraphErrors();
  TGraphErrors *t_aft2 = new TGraphErrors();
  TGraphErrors *Q_aft2 = new TGraphErrors();
  TGraphErrors *x_aft2 = new TGraphErrors();

  TH1F *factor_t = compute_kin_shift_factor(NBinsPhi, "t_Ph");
  TH1F *factor_Q = compute_kin_shift_factor(NBinsPhi, "strip_Q2");
  TH1F *factor_x = compute_kin_shift_factor(NBinsPhi, "strip_Xbj");
  TH1F *factor_p = compute_kin_shift_factor(NBinsPhi, "Phi_Ph");

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
  for (int k = 0; k < NBinsPhi; k++)
  {
    t_bef1->SetPoint(k, means1.at(k).at(0), means1.at(k).at(2));
    t_bef1->SetPointError(k, means1.at(k).at(1), means1.at(k).at(3));
    Q_bef1->SetPoint(k, means1.at(k).at(0), means1.at(k).at(4));
    Q_bef1->SetPointError(k, means1.at(k).at(1), means1.at(k).at(5));
    x_bef1->SetPoint(k, means1.at(k).at(0), means1.at(k).at(6));
    x_bef1->SetPointError(k, means1.at(k).at(1), means1.at(k).at(7));

    t_bef2->SetPoint(k, means2.at(k).at(0), means2.at(k).at(2));
    t_bef2->SetPointError(k, means2.at(k).at(1), means2.at(k).at(3));
    Q_bef2->SetPoint(k, means2.at(k).at(0), means2.at(k).at(4));
    Q_bef2->SetPointError(k, means2.at(k).at(1), means2.at(k).at(5));
    x_bef2->SetPoint(k, means2.at(k).at(0), means2.at(k).at(6));
    x_bef2->SetPointError(k, means2.at(k).at(1), means2.at(k).at(7));

    t_aft1->SetPoint(k, means1.at(k).at(0) * factor_p->GetBinContent(k + 1), means1.at(k).at(2) * factor_t->GetBinContent(k + 1));
    t_aft1->SetPointError(k, means1.at(k).at(1) * factor_p->GetBinContent(k + 1), means1.at(k).at(3) * factor_t->GetBinContent(k + 1));
    Q_aft1->SetPoint(k, means1.at(k).at(0) * factor_p->GetBinContent(k + 1), means1.at(k).at(4) * factor_Q->GetBinContent(k + 1));
    Q_aft1->SetPointError(k, means1.at(k).at(1) * factor_p->GetBinContent(k + 1), means1.at(k).at(5) * factor_Q->GetBinContent(k + 1));
    x_aft1->SetPoint(k, means1.at(k).at(0) * factor_p->GetBinContent(k + 1), means1.at(k).at(6) * factor_x->GetBinContent(k + 1));
    x_aft1->SetPointError(k, means1.at(k).at(1) * factor_p->GetBinContent(k + 1), means1.at(k).at(7) * factor_x->GetBinContent(k + 1));

    t_aft2->SetPoint(k, means2.at(k).at(0) * factor_p->GetBinContent(k + 1), means2.at(k).at(2) * factor_t->GetBinContent(k + 1));
    t_aft2->SetPointError(k, means2.at(k).at(1) * factor_p->GetBinContent(k + 1), means2.at(k).at(3) * factor_t->GetBinContent(k + 1));
    Q_aft2->SetPoint(k, means2.at(k).at(0) * factor_p->GetBinContent(k + 1), means2.at(k).at(4) * factor_Q->GetBinContent(k + 1));
    Q_aft2->SetPointError(k, means2.at(k).at(1) * factor_p->GetBinContent(k + 1), means2.at(k).at(5) * factor_Q->GetBinContent(k + 1));
    x_aft2->SetPoint(k, means2.at(k).at(0) * factor_p->GetBinContent(k + 1), means2.at(k).at(6) * factor_x->GetBinContent(k + 1));
    x_aft2->SetPointError(k, means2.at(k).at(1) * factor_p->GetBinContent(k + 1), means2.at(k).at(7) * factor_x->GetBinContent(k + 1));
  }

  TH1F *factor3D_t = compute_kin_shift_factor("t_Ph");
  TH1F *factor3D_Q = compute_kin_shift_factor("strip_Q2");
  TH1F *factor3D_x = compute_kin_shift_factor("strip_Xbj");

  TCanvas *canvas = new TCanvas("canvas", "canvas", 700, 500);
  t_bef1->Draw("ap");
  t_aft1->Draw("p");
  TLegend *legend1 = new TLegend(0.6, 0.6, 0.88, 0.88);
  legend1->AddEntry(t_bef1, "Before", "l");
  legend1->AddEntry(t_aft1, "After", "l");
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

  // root output
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
}

TH1F* BDT::compute_kin_shift_factor(int Nphi, TString var)
{
  std::cout<<"\nComputing kinematic correction of "<<var<<endl;
  
  TH1F *ratio = new TH1F("ratio_"+var,"ratio"+var,Nphi,0,360);
  for(int i=1; i<=Nphi; i++)
  {
    ratio->SetBinContent(i,1);
    ratio->SetBinError(i,0);    
  }
  return ratio; 

  TChain *Data_Tree= new TChain("pDVCS");
  Data_Tree->Add(Folder + TString("../../") + TRC_Sim); 
  
  TChain *MCData_Tree= new TChain("pDVCS");
  MCData_Tree->Add(MC_RC_Sim);

  for(int i=0; i<Nphi;i++)
  {
    printProgress(i*1.0/Nphi);

    TH1F *hvar = new TH1F("hvar","",100,0,0);
    TH1F *hvar_meas  = new TH1F("hvar_meas","",100,0,0);

    MCData_Tree->Project("hvar" , var, cut_bin  + TCut(Form("Phi_Ph>%f && Phi_Ph<%f",360.*i/Nphi,360.*(i+1)/Nphi)));
    Data_Tree->Project("hvar_meas" , var, cut + cut_bin + cut_ref + TCut(Form("_strip_Nuc_BDT > %f",BDT_value)) + TCut(Form("Phi_Ph>%f && Phi_Ph<%f",360.*i/Nphi,360.*(i+1)/Nphi)));  
    
    ratio->SetBinContent(i+1,hvar->GetMean()/hvar_meas->GetMean());
    ratio->SetBinError(i+1,ratio->GetBinContent(i+1)*sqrt(pow(hvar->GetMeanError()/hvar->GetMean(),2) + pow(hvar_meas->GetMeanError()/hvar_meas->GetMean(),2)));

    delete hvar;
    delete hvar_meas;
    }

  delete Data_Tree;
  delete MCData_Tree;

  return ratio;
}


TH1F* BDT::compute_kin_shift_factor(TString var)
{
  std::cout<<"Computing kinematic correction (3D) of "<<var<<endl;

  TH1F *ratio = new TH1F("ratio3D_"+var,"ratio"+var,1,0,360);
  ratio->SetBinContent(1,1);
  ratio->SetBinError(1,0);
  return ratio;

  TChain *Data_Tree= new TChain("pDVCS");
  Data_Tree->Add(Folder + TString("../../") + TRC_Sim); 
  
  TChain *MCData_Tree= new TChain("pDVCS");
  MCData_Tree->Add(MC_RC_Sim);

  TH1F *hvar = new TH1F("hvar","",100,0,0);
  TH1F *hvar_meas  = new TH1F("hvar_meas","",100,0,0);

  MCData_Tree->Project("hvar" , var, cut_bin );
  Data_Tree->Project("hvar_meas" , var, cut + cut_bin + cut_ref + TCut(Form("_strip_Nuc_BDT > %f",BDT_value)) );  
    
  ratio->SetBinContent(1,hvar->GetMean()/hvar_meas->GetMean());
  ratio->SetBinError(1,ratio->GetBinContent(1)*sqrt(pow(hvar->GetMeanError()/hvar->GetMean(),2) + pow(hvar_meas->GetMeanError()/hvar_meas->GetMean(),2)));

  delete hvar;
  delete hvar_meas;

  delete Data_Tree;
  delete MCData_Tree;

  return ratio;
}
