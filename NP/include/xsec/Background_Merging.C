TH1F* BDT::Background_Merging(TCut cut, int bin)
{
  int NBinsPhi = Nphibins[bin - 1];  
  TChain *tree1 = new TChain("pDVCS");
  TChain *tree2 = new TChain("pDVCS");
  tree1->Add(Form("%s%s../TDVCS_nABkg.root", dir.Data(), Folder.Data()));
  tree2->Add(Form("%s%s../TDVCS_noBkg.root", dir.Data(), Folder.Data()));
  TH1F *DVCS_1 = new TH1F("DVCS_1", "", NBinsPhi, 0, 360);
  TH1F *DVCS_2 = new TH1F("DVCS_2", "", NBinsPhi, 0, 360);
  TH1F *ratio = new TH1F("ratio", "", NBinsPhi, 0, 360);
  DVCS_1->Sumw2();
  DVCS_2->Sumw2();
  tree1->Project("DVCS_1", "Phi_Ph", cut);
  tree2->Project("DVCS_2", "Phi_Ph", cut);

  std::cout<<"\nBackground merging"<<endl;
  for (int i = 1; i <= NBinsPhi; i++)
  {
    ratio->SetBinContent(i, 1. + (Ieff/45.0)*(-1.0 + DVCS_1->GetBinContent(i)/DVCS_2->GetBinContent(i)));
    ratio->SetBinError(i, (Ieff/45.0)*DVCS_1->GetBinContent(i)/DVCS_2->GetBinContent(i)*sqrt(pow(DVCS_1->GetBinError(i)/DVCS_1->GetBinContent(i), 2) + pow(DVCS_2->GetBinError(i)/DVCS_2->GetBinContent(i), 2)));
    std::cout<<" "<<ratio->GetBinContent(i)<<" "<<ratio->GetBinError(i)*100/ratio->GetBinContent(i)<<"%"<<endl;
  }
  delete tree1;
  delete tree2;
  delete DVCS_1;
  delete DVCS_2;

  return ratio;
}
