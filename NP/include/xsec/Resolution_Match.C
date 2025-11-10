void BDT::Resolution_Match(TCut cut, TString Data, TString Sim){
  cout << "Computing matching weights..." << endl;
  //Run Python script
  gSystem->Exec(TString("rm -rf ") + Folder + TString("Reweighting_Plots_BM"));
  gSystem->Exec(TString("mkdir -p ") + Folder + TString("Reweighting_Plots"));
  gSystem->Exec(TString("cp include/xsec/get_weights.py ") + Folder);
  gSystem->Exec(TString("cd ") + Folder + TString(" && python3 get_weights.py ") + Sim + TString(" ") + Data + TString(" && cd - && pwd"));
  
  std::ifstream inputFile0(Folder + TString("rWeights0.dat"));
  if (!inputFile0.is_open()) {
    std::cerr << "Error: Unable to open weight0 file"<< std::endl;
  }

  std::ifstream inputFile(Folder + TString("rWeights.dat"));
  if (!inputFile.is_open()) {
    std::cerr << "Error: Unable to open weight file"<< std::endl;
  }

  double rw;
  
  TFile *input = new TFile(Folder + Sim,"READ");
  TTree *signal = (TTree*)input->Get("pDVCS");

  signal->SetBranchStatus("*", 1); // enable all branches  
  TFile f(Folder + TString("w") + Sim, "RECREATE");
  TTree *Tree = signal->CopyTree(cut);

  double rWeight;
  double rWeight0;
  TBranch *newBranch1 = Tree->Branch("rWeight", &rWeight, "rWeight/D");
  TBranch *newBranch2 = Tree->Branch("rWeight0", &rWeight0, "rWeight/D");

  double wTotal0 = 0;
  double wTotal = 0;
  double nEntries = Tree->GetEntries();
  for (Long64_t ievt = 0; ievt < Tree->GetEntries(); ievt++)
  {
    inputFile0 >> rw;
    wTotal0 += rw;
    
    inputFile >> rw;
    wTotal += rw;
  }

  inputFile0.seekg(0, inputFile0.beg);
  inputFile.seekg(0, inputFile.beg);

  for (Long64_t ievt = 0; ievt < nEntries; ievt++)
  {
    Tree->GetEntry(ievt);
    printProgress(ievt*1.0/nEntries);

    inputFile0 >> rw;
    rWeight0 = rw*nEntries/wTotal0;
    
    inputFile >> rw;
    rWeight = rw*nEntries/wTotal;
    //std::cout<<rw<<endl;

    newBranch1->Fill();
    newBranch2->Fill();
  }
  cout << "Writing file" << endl;
  Tree->Write();
  cout << "closing file" << endl;
  cout << "Added resolution matching weights" << endl;
  inputFile0.close();
  inputFile.close();

  TH1D *h_phi = new TH1D("h_phi", "phi;phi;Events", 100, 0, 360);
  TH1D *h_phi_rw = new TH1D("h_phi_rw", "phi (weighted);phi;Events", 100, 0, 360);

  Tree->Project("h_phi", "Phi_Ph", cut);
  Tree->Project("h_phi_rw", "Phi_Ph", cut*TCut("rWeight"));

  std::cout << "Integral (unweighted): " << h_phi->Integral() << std::endl;
  std::cout << "Integral (weighted): " << h_phi_rw->Integral() << std::endl;

  delete h_phi;
  delete h_phi_rw;

  //gSystem->Exec(TString("rm ") + Folder + Sim );
  gSystem->Exec(TString("rm ") + Folder + TString("rWeights0.dat") );
  gSystem->Exec(TString("rm ") + Folder + TString("rWeights.dat") );
}
