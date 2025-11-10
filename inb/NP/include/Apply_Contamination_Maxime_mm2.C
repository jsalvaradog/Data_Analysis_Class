
TH1F* BDT::Apply_Contamination_Maxime_mm2(TCut cut)
{
  TChain *Data= new TChain("pDVCS");
  Data->Add(Folder + "Data_NP_Theta_g_5.root");

  TChain *bkg= new TChain("pDVCS");
  bkg->Add(Folder + TString("TMaxime_pi0.root"));

  TH1F *Data_p_BDT = new TH1F("Data_p_BDT","",100,0.0,5.0);
  TH1F *Phi_p_BDT = new TH1F("Phi_p_BDT","",100,0.0,5.0);

  Data_p_BDT->Sumw2();
  Phi_p_BDT->Sumw2();

  Data->Project("Data_p_BDT", "mm2_eg", cut);
  bkg->Project("Phi_p_BDT", "mm2_eg", TCut("Weight")*(cut));

  Phi_p_BDT->Scale(-1.0);
  Data_p_BDT->Add(Phi_p_BDT);
  Data_p_BDT->SetLineColor(kRed);
  delete Phi_p_BDT;
  delete Data;
  delete bkg;
  
  return Data_p_BDT;

}
