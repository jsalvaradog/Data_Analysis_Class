void BDT::Get_excl_vars_tagged(TCut cut)
{
   TCanvas *canvas1 = new TCanvas("canvas1", "Exclusivity variables");
   gStyle->SetOptStat(0);

  TChain *pDVCS= new TChain("pDVCS");
  pDVCS->Add(Folder + TData);

  TChain *cont= new TChain("pDVCS");
  cont->Add(Folder + TString("TMaxime_pi0.root"));

  auto hs2 = new THStack("hs2","M^{2}_{e#gamma X} (GeV^{2})");
  TH1F *hist2c_Data = new TH1F("hist2c_Data","",100,0,2);
  TH1F *hist2c_Cont = new TH1F("hist2c_Cont","",100, 0,2);
  TH1F *hist2c_Data_tagged = new TH1F("hist2c_Data_tagged","",100,0,2);
  TH1F *hist2c_Cont_tagged = new TH1F("hist2c_Cont_tagged","",100, 0,2);
  TH1F *hist2c_Data_untagged = new TH1F("hist2c_Data_untagged","",100,0,2);
  TH1F *hist2c_Cont_untagged = new TH1F("hist2c_Cont_untagged","",100, 0,2);

  //Variables to plot
  const char *p2="mm2_eg";

  cont->Project("hist2c_Cont", p2, (cut + TCut(Form("_strip_Nuc_BDT > %f", BDT_value))) * TCut("Weight"));
  pDVCS->Project("hist2c_Data", p2, (cut + TCut(Form("_strip_Nuc_BDT > %f", BDT_value))));
  cont->Project("hist2c_Cont_tagged", p2, (cut + TCut(Form("P_Tag==1 && _strip_Nuc_BDT > %f", BDT_value))) * TCut("Weight"));
  pDVCS->Project("hist2c_Data_tagged", p2, (cut + TCut(Form("P_Tag==1 && _strip_Nuc_BDT > %f", BDT_value))));
  cont->Project("hist2c_Cont_untagged", p2, (cut + TCut(Form("P_Tag==0 && _strip_Nuc_BDT > %f", BDT_value))) * TCut("Weight"));
  pDVCS->Project("hist2c_Data_untagged", p2, (cut + TCut(Form("P_Tag==0 && _strip_Nuc_BDT > %f", BDT_value))));

  hist2c_Data->Add(hist2c_Data, hist2c_Cont, 1, -1);
  hist2c_Data_tagged->Add(hist2c_Data_tagged, hist2c_Cont_tagged, 1, -1);
  hist2c_Data_untagged->Add(hist2c_Data_untagged, hist2c_Cont_untagged, 1, -1);


  hist2c_Data->SetLineColor(kBlack);
  hist2c_Data_tagged->SetLineColor(kRed);

  hs2->Add(hist2c_Data);
  hs2->Add(hist2c_Data_tagged);
  
  double chi2pvalue = hist2c_Data_tagged->Chi2Test(hist2c_Data_untagged,"UU CHI2/NDF");
  std::cout<<chi2pvalue<<endl;
  //hs2->SetTitle(Form("M^{2}_{e#gamma X} (GeV^{2}) / #chi^{2} p-value = %f",chi2pvalue));  
  hs2->Draw("nostack,hist");


  canvas1->Print(Folder + TString("Excl_vars_tagged.pdf"));
  
  
  delete hist2c_Data;
  delete hist2c_Cont;
  delete hist2c_Data_tagged;
  delete hist2c_Cont_tagged;

  delete canvas1;
  delete hs2;

  delete pDVCS;
  delete cont;
}
