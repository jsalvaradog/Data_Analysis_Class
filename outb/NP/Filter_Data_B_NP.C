
#include <sstream>
//#include "Data_P.C"
void Filter_Data_B_NP(){
    
  TChain *chain= new TChain("pDVCS");
  chain->AddFile(std::string("../Quality3_Data_NP.root").c_str());

  
  TTree* Tree = chain ;
  TCut TheCut =TCut("bestCandidateFlag==1 && strip_Xbj <1 && strip_Xbj >0 && t_Ph <0 && strip_Q2 > 1.0 && strip_W > 2 && strip_Nuc_P > 0.35 && strip_El_P > 1.0 && strip_Ph_P>2  && strip_El_vz < 10 && strip_El_vz > -12 && TMath::Abs(Phi_Nuc - Phi_Ph) < 2 && TMath::Abs(t_Nuc - t_Ph) < 2 && TMath::Sqrt(Xbal * Xbal + Ybal*Ybal + Zbal*Zbal) <1  && abs(mm2_eg - 0.88) > 0.9");
    
  TFile f0("Training_data_Pi0_temp.root","RECREATE");
  TTree* sTree = Tree->CopyTree(TheCut);
  sTree->SetMaxTreeSize(40000000000LL);
  sTree->SetBranchStatus("_strip_Nuc_BDT",0);

  TFile f("Training_data_Pi0_NP.root","RECREATE");
  printf("... copying tree\n");
  TTree* sTree2 = sTree->CopyTree("bestCandidateFlag==1");
  sTree2->SetMaxTreeSize(40000000000LL);
    
  printf("... tree copied ... \n");
  sTree2->Write();
  f0.Close();
  f.Close();

  gSystem->Exec("rm Training_data_Pi0_temp.root");
  return;
}




