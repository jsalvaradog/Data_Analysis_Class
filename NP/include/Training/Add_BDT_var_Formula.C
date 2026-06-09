#include <vector>

void BDT::Add_BDT_var_Formula(TCut cutSB, TString Data, TString output, vector<TString> vars)
{

  cout << "\n-Start TMVA-" << endl;

  cout << " Adding Variables to Reader" << endl;
  // --- Create the Reader object
  TMVA::Reader *reader1 = new TMVA::Reader("!Color:!Silent");
  
  // Create a set of variables and declare them to the reader
  // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
  static Float_t _mm2_eg1;
  static Float_t _mm2_e1;
  static Float_t _t_Ph1;
  static Float_t Ph_Th;
  static Float_t Nuc_Th;
  
  static vector<double>* _mm2_eg;
  static vector<double>* _mm2_e;
  static vector<double>* _t_Ph;
  static vector<double>* Ph_Th_V;
  static vector<double>* Nuc_Th_V;
  static vector<int>* flag;


  reader1->AddVariable("abs(mm2_eg-0.88)", &_mm2_eg1);
  reader1->AddVariable("mm2_e", &_mm2_e1);
  reader1->AddVariable("t_Ph", &_t_Ph1);
  
  reader1->AddSpectator( "strip_Ph_Theta", &Ph_Th);
  reader1->AddSpectator( "strip_Nuc_Theta", &Nuc_Th);

  cout << " Booking Method" << endl;
  if(!nodata)
  {
  if(categories)
  	reader1->BookMVA("BDT method", Folder + TString("dataset/weights/TMVAClassificationCategory_Ph_Topology.weights.xml"));
  else
	  reader1->BookMVA("BDT method", Folder + TString("dataset/weights/TMVAClassificationCategory_BDT.weights.xml"));
  }

  TFile *input4 = new TFile(Data,"READ");
  TTree *signal;
  if( input4->GetListOfKeys()->Contains("pDVCS") )
    signal     = (TTree*)input4->Get("pDVCS");
  else
    signal     = (TTree*)input4->Get("eppi0");
 
  int nentries = signal->GetEntries();
  cout << "Reading File with " << nentries << " to Add MVA response" << endl;
  cout << " Reading Variables" << endl;

  TFile f(Folder + output, "RECREATE");

  if(nentries == 0)
  {
    signal->Write();
    f.Close();
    return;
  }

  TTree *Tree = signal->CopyTree(cutSB);

  Tree->SetBranchStatus("*", 1); // enable all branches

  Tree->SetBranchAddress("mm2_eg", &_mm2_eg);
  Tree->SetBranchAddress("mm2_e", &_mm2_e);
  Tree->SetBranchAddress("t_Ph", &_t_Ph);
  Tree->SetBranchAddress("strip_Ph_Theta", &Ph_Th_V);
  Tree->SetBranchAddress("strip_Nuc_Theta", &Nuc_Th_V);
  Tree->SetBranchAddress("bestCandidateFlag", &flag);

  cout << " Loop on all events " << signal->GetEntries() << " to compute MVA output" << endl;
  
  double _strip_Nuc_BDT;

  TBranch *newBranch = Tree->Branch("_strip_Nuc_BDT", &_strip_Nuc_BDT, "_strip_Nuc_BDT/D");

  ////////////////////////////


  for (Long64_t ievt = 0; ievt < Tree->GetEntries(); ievt++)
  {
    Tree->GetEntry(ievt);
    printProgress(ievt*1.0/Tree->GetEntries());
    for(int i=0; i<flag->size();i++)
      {
	if(flag->at(i)==1)
	  {
	    //_strip_Ph_P1=_strip_Ph_P->at(0);
	    //    std::cout<<_strip_Ph_P1<<endl;
	    
	    _mm2_eg1 = abs(_mm2_eg->at(i) - 0.88);
	    //std::cout<<_mm2_eg1<<endl;
	    
	    _mm2_e1 = _mm2_e->at(i);
	    //std::cout<<_mm2_e1<<endl;
	    
	    _t_Ph1 = _t_Ph->at(i);
	    //std::cout<<_t_Ph1<<endl;
	    
      //Spectators
      Ph_Th = Ph_Th_V->at(i);
      Nuc_Th = Nuc_Th_V->at(i);

      // Get TMVA output
      if( (categories || (!categories && Ph_Th > 5)) && !nodata )
      {
	    _strip_Nuc_BDT = reader1->EvaluateMVA("BDT method");
      }
      else
      {
        _strip_Nuc_BDT = 2;
      }
      //std::cout<<_strip_Nuc_BDT<<endl;
	    
	    newBranch->Fill();
	  }
      }
  }
  cout << "Writing file" << endl;
  //Tree->Print();
  Tree->Write();
  cout << "closing file" << endl;

  cout << "Added " << Tree->GetEntries() << " MVA variables to file\n" << endl;
  delete reader1;
  delete signal;
  input4->Close();
  delete input4;
  
  delete Tree;
  f.Close();

 }
