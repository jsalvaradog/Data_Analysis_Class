TH1F* BDT::Lepton_Propagator(int bin)
{
  TRandom3 rng(0);                 // 0 = seed from system time
  int seed = rng.Integer(1000000); // random integer in [0, 99]
  int NBinsPhi = Nphibins[bin - 1];  
  
  gSystem->Exec(Form("cd %s%s && \
    dvcsgen --seed %i --trig 100000 --nmax 100000 --gpd 101 --ycol 0.005 --t %f %f --q2 %f %f --x %f %f --y 0.05 0.92 --beam 10.604 --globalfit --zpos -3 --zwidth 2.5 --raster 0.025 --weight >> /dev/null \
    && cp %sinclude/xsec/lund2root_LP.C . \
    && clas12root -l -b -q lund2root_LP.C && mv dvcsgen_test.root dvcsgen_1.root \
    && rm lund2root_LP.C && rm dvcsgen1.dat && cd -", dir.Data(), Folder.Data(), seed\
    , -1.0 * boundaries.at(1), -1.0 * boundaries.at(0), boundaries.at(2), boundaries.at(3), boundaries.at(4), boundaries.at(5)\
    , dir.Data()));

  gSystem->Exec(Form("cd %s%s && \
    dvcsgen --seed %i --trig 100000 --nmax 100000 --gpd 101 --ycol 0.00005 --t %f %f --q2 %f %f --x %f %f --y 0.05 0.92 --beam 10.604 --globalfit --zpos -3 --zwidth 2.5 --raster 0.025 --weight >> /dev/null \
    && cp %sinclude/xsec/lund2root_LP.C . \
    && clas12root -l -b -q lund2root_LP.C && mv dvcsgen_test.root dvcsgen_2.root \
    && rm lund2root_LP.C && rm dvcsgen1.dat && cd -", dir.Data(), Folder.Data(), seed\
    , -1.0 * boundaries.at(1), -1.0 * boundaries.at(0), boundaries.at(2), boundaries.at(3), boundaries.at(4), boundaries.at(5)\
    , dir.Data()));

  TString String_cut = (cut_bin + cut_kin + cut_sel + cut_ref).GetTitle();
  String_cut.ReplaceAll("bestCandidateFlag==1 && ", "");
  String_cut.ReplaceAll("_strip_Nuc_BDT_SIDIS", "Q2");
  String_cut.ReplaceAll("strip_Q2", "Q2");
  String_cut.ReplaceAll("strip_Xbj", "xB");
  String_cut.ReplaceAll("t_Ph", "t");
  String_cut.ReplaceAll("strip_El_P", "El_E");
  String_cut.ReplaceAll("strip_Ph_P", "Ph_E");
  String_cut.ReplaceAll("strip_El_Theta", "El_Theta");
  String_cut.ReplaceAll("strip_Ph_Theta", "Ph_Theta");
  TCut cut0 = TCut(String_cut);

  TChain *tree1 = new TChain("tree");
  TChain *tree2 = new TChain("tree");
  tree1->Add(Form("%s%s/dvcsgen_1.root", dir.Data(), Folder.Data()));
  tree2->Add(Form("%s%s/dvcsgen_2.root", dir.Data(), Folder.Data()));
  TH1F *DVCS_1 = new TH1F("DVCS_1", "", NBinsPhi, 0, 360);
  TH1F *DVCS_2 = new TH1F("DVCS_2", "", NBinsPhi, 0, 360);
  TH1F *ratio = new TH1F("ratio", "", NBinsPhi, 0, 360);
  DVCS_1->Sumw2();
  DVCS_2->Sumw2();
  tree1->Project("DVCS_1", "phi", (cut0 + TCut("Q2>1")));
  tree2->Project("DVCS_2", "phi", (cut0 + TCut("Q2>1")));
  ratio->Divide(DVCS_1, DVCS_2, 1, 1);

  std::cout<<"\nLepton Propagator cut"<<endl;
  for (int i = 1; i <= NBinsPhi; i++)
  {
    std::cout<<" "<<ratio->GetBinContent(i)<<endl;
    if(ratio->GetBinContent(i)<0.7)
      ratio->SetBinContent(i, 0.0);
    else
      ratio->SetBinContent(i, 1.0);
  }
  gSystem->Exec(Form("rm %s%sdvcsgen_1.root", dir.Data(), Folder.Data()));
  gSystem->Exec(Form("rm %s%sdvcsgen_2.root", dir.Data(), Folder.Data()));
  delete tree1;
  delete tree2;
  delete DVCS_1;
  delete DVCS_2;

  return ratio;
}
