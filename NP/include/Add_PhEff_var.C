void BDT::Add_PhEff_var(TCut cutSB, TString Data, TString output)
{
  TString var = "Ph_eff";
  cout << "\nAdding " << var << " into " << Data << endl;
  TFile *input4 = new TFile(Data,"READ");
  TTree *signal     = (TTree*)input4->Get("pDVCS");
  int nentries = signal->GetEntries();
  cout << "Reading File with " << nentries << " to Add MVA response" << endl;
  cout << "Writing into " << Folder + output <<endl;
  TFile f(Folder + output, "RECREATE");
  if(nentries == 0)
  {
    signal->Write();
    f.Close();
    return;
  }

  double _var;
  static std::vector<int>* flag;
  static std::vector<double>* Ph_x;
  static std::vector<double>* Ph_y;

  TTree *Tree = signal->CopyTree(cutSB);
  Tree->SetBranchStatus("*", 1); // enable all branches
  Tree->SetBranchAddress("bestCandidateFlag", &flag);
  Tree->SetBranchAddress("det_Ph_x", &Ph_x);
  Tree->SetBranchAddress("det_Ph_y", &Ph_y);

  TBranch *newBranch = Tree->Branch(var, &_var, var+TString("/D"));

  for (Long64_t ievt = 0; ievt < Tree->GetEntries(); ievt++)
  {
    Tree->GetEntry(ievt);
    printProgress(ievt*1.0/Tree->GetEntries());
    for(int i=0; i<flag->size();i++)
      {
	if(flag->at(i)==1)
	  {
      _var = 1.0/GetPhotonEff(Ph_x->at(i), Ph_y->at(i));
	    newBranch->Fill();
	  }
      }
  }
  cout << "Writing file" << endl;
  Tree->Write();
  cout << "closing file" << endl;
  cout << "Added " << var << " variable\n" << endl;

  delete signal;
  input4->Close();
  delete input4;
  
  delete Tree;
  f.Close();
}
