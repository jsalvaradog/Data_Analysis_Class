#include <vector>

void BDT::Add_BDT_var_float_Formula(TCut cutSB, TString Data, TString output)
{

  cout << "\n-Start TMVA-" << endl;

  cout << " Adding Variables to Reader" << endl;
  // --- Create the Reader object
  TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");
  
  // Create a set of variables and declare them to the reader
  // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
  TChain *signal= new TChain("pDVCS");
  signal->Add(Data);


  static Float_t _mm2_eg1;
  static Float_t _mm2_e1;
  static Float_t _t_Ph1;
  static Float_t Ph_Th;
  static Float_t Nuc_Th;
  
  static Double_t _mm2_eg;
  static Double_t _mm2_e;
  static Double_t _t_Ph;
  static Double_t Ph_Th_V;
  static Double_t Nuc_Th_V;

  reader->AddVariable("abs(mm2_eg-0.88)", &_mm2_eg1);
  reader->AddVariable("mm2_e", &_mm2_e1);
  reader->AddVariable("t_Ph", &_t_Ph1);

  reader->AddSpectator( "strip_Ph_Theta", &Ph_Th);
  reader->AddSpectator( "strip_Nuc_Theta", &Nuc_Th);
  
  cout << " Booking Method" << endl;

  if(!nodata)
  {
  if(categories)
  	reader->BookMVA("BDT method", Folder + TString("dataset/weights/TMVAClassificationCategory_Ph_Topology.weights.xml"));
  else
	  reader->BookMVA("BDT method", Folder + TString("dataset/weights/TMVAClassificationCategory_BDT.weights.xml"));
  }
  
  int nentries = signal->GetEntries();
  cout << "Reading File with " << nentries << " to Add MVA response" << endl;
  cout << " Reading Variables" << endl;

  //========================================
  //signal->SetBranchStatus("*", 1); // enable all branches
  
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

  cout << " Loop on all events " << Tree->GetEntries() << " to compute MVA output" << endl;
  
  double _strip_Nuc_BDT;
  

  TBranch *newBranch = Tree->Branch("_strip_Nuc_BDT", &_strip_Nuc_BDT, "_strip_Nuc_BDT/D");

  ////////////////////////////


  for (Long64_t ievt = 0; ievt < Tree->GetEntries(); ievt++)
  {
    Tree->GetEntry(ievt);
    printProgress(ievt*1.0/signal->GetEntries());
	    _mm2_eg1 = abs(_mm2_eg - 0.88);
	    _mm2_e1 = _mm2_e;
	    _t_Ph1 = _t_Ph;
      Ph_Th = Ph_Th_V;
      Nuc_Th = Nuc_Th_V;
    
    // Get TMVA output
	    // Get TMVA output
      if( (categories || (!categories && Ph_Th > 5)) && !nodata )
      {
	    _strip_Nuc_BDT = reader->EvaluateMVA("BDT method");
      }
      else
      {
        _strip_Nuc_BDT = 2;
      }
    
    newBranch->Fill();
  }
  cout << "Writing file" << endl;
  Tree->Write();
  cout << "closing file" << endl;

  cout << "Added " << Tree->GetEntries() << " MVA variables to file\n" << endl;

  delete reader;
  delete signal;
  delete Tree;
  f.Close();
  
}
