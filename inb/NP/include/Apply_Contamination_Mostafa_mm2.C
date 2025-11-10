
TH1F* BDT::Apply_Contamination_Mostafa_mm2(TCut cut)
{
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  TChain *Data= new TChain("pDVCS");
  Data->Add(Folder + TString("Data_NP_Theta_g_5.root"));

  TChain *Pi0= new TChain("pDVCS");
  Data->Add(Folder + TString("TMostafa_pi0.root"));

  TH1F *Pi01g_p_BDT = new TH1F("Pi01g_p_BDT","",100,0.0,5.0);
  TH1F *Data_p_BDT2 = new TH1F("Data_p_BDT2","",100,0.0,5.0);

  Pi01g_p_BDT->Sumw2();
  Data_p_BDT2->Sumw2();
  
  Pi0->Project("Pi01g_p_BDT", "mm2_eg", cut*TCut("Weight"));
  Data->Project("Data_p_BDT2", "mm2_eg", cut);

  Pi01g_p_BDT->Scale(-1.0);
  Data_p_BDT2->Add(Pi01g_p_BDT);
  Data_p_BDT2->SetLineColor(kBlue);

  delete Pi0;
  delete Data;

  delete Pi01g_p_BDT;

  return Data_p_BDT2;

}
