void BDT::Get_excl_vars(TCut cut)
{
   TCanvas *canvas2 = new TCanvas("canvas2", "Exclusivity variables");
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);

  TChain *pDVCS= new TChain("pDVCS");
  pDVCS->Add(Folder + TData);

  TChain *cont= new TChain("pDVCS");
  cont->Add(Folder + TString("TMaxime_pi0.root"));

  TChain *simu= new TChain("pDVCS");
  simu->Add(Folder + TDVCS);

  auto hs2 = new THStack("hs2","M^{2}_{e#gamma X} (GeV^{2})");
  TH1F *hist2c_Data = new TH1F("hist2c_Data","",100,0,2);
  TH1F *hist2c_Cont = new TH1F("hist2c_Cont","",100, 0,2);
  TH1F *hist2c_Sim = new TH1F("hist2c_Sim","",100,0,2);

  //Variables to plot
  const char *p2="mm2_eg";

  cont->Project("hist2c_Cont", p2, (cut + TCut(Form("_strip_Nuc_BDT > %f", BDT_value))) * TCut("Weight"));
  pDVCS->Project("hist2c_Data", p2, (cut + TCut(Form("_strip_Nuc_BDT > %f", BDT_value))));
  simu->Project("hist2c_Sim", p2, (cut + TCut(Form("_strip_Nuc_BDT > %f", BDT_value))));
  hist2c_Data->Add(hist2c_Data, hist2c_Cont, 1, -1);


  hist2c_Sim->Scale(hist2c_Data->GetEntries()/hist2c_Sim->GetEntries());
  hist2c_Sim->SetLineColor(kBlack);
  hist2c_Data->SetLineColor(kRed);

  hs2->Add(hist2c_Sim);
  hs2->Add(hist2c_Data);

  hs2->SetHistogram(new TH1F("hstot2","",100,0,2));
  hs2->GetHistogram()->GetXaxis()->SetTitle(hs2->GetTitle());
  hs2->GetHistogram()->GetYaxis()->SetTitle("counts/total events");
  hs2->GetHistogram()->SetTitle("");
  hs2->GetHistogram()->GetXaxis()->SetTitleSize(0.06);
  hs2->GetHistogram()->GetYaxis()->SetTitleSize(0.06);
  hs2->GetHistogram()->GetXaxis()->SetLabelSize(0.04);
  hs2->GetHistogram()->GetYaxis()->SetLabelSize(0.04);
  hs2->GetHistogram()->GetYaxis()->SetTitleOffset(0.85);
  hs2->GetHistogram()->GetXaxis()->SetTitleOffset(0.7);
  hs2->GetHistogram()->GetYaxis()->SetNdivisions(8);
  hs2->GetHistogram()->GetXaxis()->SetNdivisions(8);
  hs2->GetHistogram()->GetYaxis()->SetMaxDigits(2);
  
  hs2->Draw("nostack,hist");


  canvas2->Print(Folder + TString("Excl_vars.pdf"));
  
  
  delete hist2c_Sim;
  delete hist2c_Data;
  delete hist2c_Cont;

  delete canvas2;
  delete hs2;

  delete pDVCS;
  delete simu;
  delete cont;
}
