TH1F* BDT::BDTEff_Corr(TCut cut, TString Data, TString MCData, double BDT_cut, int Nphi){
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  TChain *Data_Tree= new TChain("pDVCS");
  Data_Tree->Add(Folder + TString("../") + Data);
  
  TChain *MCData_Tree= new TChain("pDVCS");
  MCData_Tree->Add(Folder + TString("../") + MCData);

  TH1F *Phi = new TH1F("Phi","",Nphi,0,360);
  TH1F *Phi_mc = new TH1F("Phi_mc","",Nphi,0,360);
  TH1F *Phi_cutted = new TH1F("Phi_cutted","",Nphi,0,360);
  TH1F *Phi_mc_cutted = new TH1F("Phi_mc_cutted","",Nphi,0,360);
  TH1F *ratio = new TH1F("ratio","ratio",Nphi,0,360);
  TH1F *ratio_mc = new TH1F("ratio_mc","ratio_mc",Nphi,0,360);

  Data_Tree  ->Project("Phi", "Phi_Ph", cut );
  Data_Tree  ->Project("Phi_cutted", "Phi_Ph", (cut + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut))));
  MCData_Tree->Project("Phi_mc" , "Phi_Ph", cut);
  MCData_Tree->Project("Phi_mc_cutted" , "Phi_Ph", (cut + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut))));

  ratio->Divide(Phi_cutted, Phi,1.0,1.0);
  ratio_mc->Divide(Phi_mc_cutted, Phi_mc,1.0,1.0);

  TH1F *F_BDT = new TH1F("F_BDT","F_BDT",Nphi,0,360);
  F_BDT->Sumw2();
  F_BDT->Divide(ratio_mc, ratio,1.0,1.0);

  std::cout<<"\nBDT efficiency correction"<<endl;
  for(int k=1; k<=Nphi; k++)
  {
    ratio->SetBinError(k,0.0);
    ratio_mc->SetBinError(k,0.0);
    F_BDT->SetBinError(k,0.0);
    std::cout<<F_BDT->GetBinContent(k)<<endl;
  }

  

  delete Phi;
  delete Phi_cutted;
  delete Phi_mc;
  delete Phi_mc_cutted;
  delete ratio;
  delete ratio_mc;
  
  delete Data_Tree;
  delete MCData_Tree;

  return F_BDT;
}
