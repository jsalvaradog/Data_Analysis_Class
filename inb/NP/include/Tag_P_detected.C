void BDT::Tag_P_Detected(TString Data_name_P, TString Data_name_NP){

  static vector<int> *Flag1;

  static int Ev1;
  static int Ev2;
  
  TString tree1;
  TString tree2;

  TFile *input = new TFile(TString("../") + Data_name_P,"READ");
  if( input->GetListOfKeys()->Contains("pDVCS") )
    tree1="pDVCS";
  else
    tree1="eppi0";
  TTree *pDVCS = (TTree*)input->Get(tree1);

  TFile *input2 = new TFile(Folder + Data_name_NP,"READ");
  if( input2->GetListOfKeys()->Contains("pDVCS") )
    tree2="pDVCS";
  else
    tree2="eppi0";
  TTree *pDVCS_NP = (TTree*)input2->Get(tree2);


  pDVCS->SetBranchStatus("*", 0); // disable all branches
  pDVCS->SetBranchStatus("EventNumber", 1); 
  pDVCS->SetBranchStatus("bestCandidateFlag", 1); 

  pDVCS->SetBranchAddress("EventNumber",&Ev1);  
  pDVCS->SetBranchAddress("bestCandidateFlag",&Flag1);

  std::unordered_set<int> PdetectedEventNumbers;
  for(int m=0; m<pDVCS->GetEntries();m++)
    {     
      pDVCS->GetEntry(m);
      //std::cout<<m<<" "<<Flag1->size()<<endl;
      for(int i=0; i<Flag1->size();i++)
	{
	  if(Flag1->at(i)==1)
	    {
	      //myfile<<Ev1<<endl;
	      PdetectedEventNumbers.insert(Ev1);	
            }
	}
    }

 
    // Create a new output file
    TFile* outFile = new TFile(Folder + TString("Tagged_") + Data_name_NP, "RECREATE");
    TTree* filteredTree = pDVCS_NP->CopyTree("bestCandidateFlag==1"); 
    filteredTree->SetMaxTreeSize(100000000000LL);
    
    filteredTree->SetBranchAddress("EventNumber",&Ev2);

    static int Tag;
    TBranch* P_Tag = filteredTree->Branch("P_Tag", &Tag, "P_Tag/I");


    // Loop over the events in the input tree
    for (Long64_t iEntry = 0; iEntry < filteredTree->GetEntries(); ++iEntry) 
    	{
        filteredTree->GetEntry(iEntry);
        printProgress(iEntry*1.0/filteredTree->GetEntries());

        // Check if the EventNumber is in the list
        if (PdetectedEventNumbers.find(Ev2) != PdetectedEventNumbers.end()) 
        	Tag=1;
	else
		Tag=0;
	
	P_Tag->Fill();
	}

  filteredTree->Write();

  printf("\n ... tree copied ... \n");  

  
  delete filteredTree;
  outFile->Close();
  delete outFile;  

  delete pDVCS;
  input->Close();
  delete input;
  
  delete pDVCS_NP;
  input2->Close();
  delete input2;  
  
  
}
