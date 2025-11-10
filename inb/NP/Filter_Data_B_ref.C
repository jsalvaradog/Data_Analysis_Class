
#include <sstream>
//#include "Data_P.C"
void Filter_Data_B_ref(){
    
  TChain *chain= new TChain("pDVCS");
  for(int i=1; i<=64; i++)
  	chain->AddFile(Form("/work/clas12/jsalvg/RGA-Analysis/inb/P/Analysis/bin_%i/Tested_Quality_Data.root",i));

  
  TTree* Tree = chain ;
  TCut TheCut =TCut("bestCandidateFlag==1 && strip_Xbj <1 && strip_Xbj >0 && t_Ph <0 && strip_Q2 > 1.0 && strip_W > 2 && strip_Nuc_P > 0.35 && strip_El_P > 1.0 && strip_Ph_P>2  && strip_El_vz < 10 && strip_El_vz > -12 && TMath::Abs(Phi_Nuc - Phi_Ph) < 2 && TMath::Abs(t_Nuc - t_Ph) < 2 && TMath::Sqrt(Xbal * Xbal + Ybal*Ybal + Zbal*Zbal) <1  && _strip_Nuc_BDT < 0.0");
    
  TFile f0("Training_data_Pi0_temp.root","RECREATE");
  TTree* sTree = Tree->CopyTree(TheCut);
  sTree->SetMaxTreeSize(4000000000LL);
  sTree->SetBranchStatus("_strip_Nuc_BDT",0);

  TFile f("Training_data_Pi0_ref.root","RECREATE");
  printf("... copying tree\n");
  TTree* sTree2 = sTree->CopyTree("bestCandidateFlag==1");
  sTree2->SetMaxTreeSize(4000000000LL);
    
  printf("... tree copied ... \n");
  sTree2->Write();
  f0.Close();
  f.Close();

  gSystem->Exec("rm Training_data_Pi0_temp.root");
  return;
}




