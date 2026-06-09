#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TThread.h"
//#include "include/TUnfold_V17.9/TUnfold.h"
//#include "RooUnfoldTUnfold.h
//#include "include/RooUnfold/build/RooUnfoldTUnfold.h"
#include "include/RooUnfold/build/RooUnfoldResponse.h"
#include "include/RooUnfold/build/RooUnfoldBayes.h"
#include "include/RooUnfold/build/RooUnfoldSvd.h"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

class BDT
{
public:
  TH1F* hDATA;
  TH1F* hDVCS;
  TH1F* hPI0;
  TH1F* hSIDIS;

  TH2F *h_ef_FD;
  TH2F *h_ef_FT;
  TH2F *h_ef_FD_Err;
  TH2F *h_ef_FT_Err;

  TString dir;
  TString extBSA;
  TString extXSEC;
  TString Folder;
  TString DVCS;
  TString DVCS_nABkg;
  TString DVCS_noBkg;
  TString DVCS_MC;
  TString Pi0;
  TString SIDIS;
  TString Data_name;
  TString Data;
  TString TDVCS;
  TString TDVCS_MC;
  TString TPi0;
  TString TData;
  TString eppi0_name;
  TString eppi0;
  TString epeta;
  TString maps_path;
  TString sim_eppi0;
  TString sim_eppi0_1;
  TString sim_epeta;
  TString sim_pi_as_dvcs;
  TString sim_pi_as_dvcs_1;
  TString sim_eta_as_dvcs;

  TString BM_Sim;
  TString TBM_Sim;
  TString MC_BM_Sim;

  TString RC_Sim;
  TString TRC_Sim;
  TString MC_RC_Sim;

  TString MC_DVCS_RC;
  TString MC_DVCS_RC_BH;

  TString Maxime_bkg;

  TCut cut;
  TCut cut2g;
  TCut cut_bin;
  TCut cut_sys;
  TCut cut_pid;
  TCut cut_ref = TCut("bestCandidateFlag==1");
  TCut cut_kin;
  TCut cut_sel; 
  TCut runCut;
  
  
  bool means_most;
  bool means_maxi;
  bool means_fit;
  bool generate;
  bool recast;
  bool add_BDT_Max;
  bool generate_most;
  bool generate_fit;
  bool tag;
  bool categories;
  bool nodata=false;
  bool cut_sys_=false;  
  bool pid_sys=false;
  bool bdt_sys=false;
  bool xsection;
  
  int entries_bef_BDT;
  int entries_bef_BDT_FT;
  int entries_bef_BDT_FD;
  int entries_bef_most;
  int entries_bef_most_FT;
  int entries_bef_most_FD;
  int entries_aft_most;
  int entries_aft_most_FT;
  int entries_aft_most_FD;
  int entries_bef_maxi;
  int entries_bef_maxi_FT;
  int entries_bef_maxi_FD;
  int entries_aft_maxi;
  int entries_aft_maxi_FT;
  int entries_aft_maxi_FD;
  int entries_bef_Fit;
  int entries_bef_Fit_FT;
  int entries_bef_Fit_FD;
  int entries_aft_Fit;
  int entries_aft_Fit_FT;
  int entries_aft_Fit_FD;

  int N_Phi;
  int Nbins;

  double nft;
  double BSA_Amplitude;
  double BSA_Amplitude_most;
  double BSA_Amplitude_maxi;
  double BSA_Amplitude_Fit;
  double BSA_Amplitude_fit;
  double BSA_Amplitude_most_fit;
  double BSA_Amplitude_Fit_fit;
  double BSA_Amplitude_maxi_fit;
  double BSA_Error_fit;
  double BSA_Error_most_fit;
  double BSA_Error_Fit_fit;
  double BSA_Error_maxi_fit;
  double BDT_value;
  double BDT_value_sys;
  double Bpol;
  double Lumi;
  double Ieff;
  TString torus;
  int itorus;

  double xmean1, Qmean1, tmean1;
  double xmean2, Qmean2, tmean2;

  vector<TString> Vars; 
  vector<int> list_5nA = {5616}; 
  vector<int> list_40nA = {5335, 5339, 5341, 5423, 5424, 5425, 5426, 5428, 5429, 5430, 5432, 5434, 5435, 5436, 5437, 5438, 5440, 5441, 5442, 5445, 5447, 5449, 5450, 5451, 5452, 5453, 5454, 5455, 5460, 5464, 5465, 5466, 5467, 5468, 5469, 5470, 5471, 5472, 5473, 5474, 5475, 5476, 5478, 5479, 5480, 5481, 5482, 5483, 5485, 5486, 5487, 5497, 5498, 5499, 5500, 5504}; 
  vector<int> list_45nA = {5032, 5036, 5038, 5039, 5040, 5041, 5043, 5045, 5052, 5053, 5116, 5117, 5119, 5120, 5124, 5125, 5126, 5127, 5139, 5153, 5158, 5162, 5163, 5164, 5181, 5191, 5193, 5195, 5196, 5197, 5198, 5199, 5200, 5201, 5202, 5203, 5204, 5205, 5206, 5208, 5211, 5212, 5215, 5216, 5219, 5220, 5221, 5222, 5223, 5230, 5231, 5232, 5233, 5234, 5235, 5237, 5238, 5247, 5248, 5249, 5252, 5253, 5257, 5258, 5259, 5261, 5262, 5303, 5304, 5305, 5306, 5307, 5310, 5311, 5315, 5317, 5318, 5319, 5320, 5323, 5324, 5333, 5334, 5346, 5347, 5349, 5351, 5354, 5355, 5367}; 
  vector<int> list_50nA = {5340, 5342, 5343, 5344, 5345, 5356, 5357, 5358, 5359, 5360, 5361, 5362, 5366, 5507, 5516, 5517, 5518, 5519, 5520, 5521, 5522, 5523, 5524, 5525, 5526, 5527, 5528, 5530, 5532, 5533, 5534, 5535, 5536, 5537, 5538, 5540, 5541, 5543, 5544, 5545, 5546, 5547, 5548, 5549, 5550, 5551, 5552, 5555, 5556, 5557, 5558, 5559, 5562, 5569, 5570, 5571, 5572, 5573, 5574, 5577, 5578, 5591, 5592, 5594, 5597, 5598, 5600, 5601, 5602, 5603, 5604, 5606, 5607, 5611, 5612, 5613, 5614, 5616, 5618, 5619, 5624, 5625, 5626, 5627, 5628, 5629, 5630, 5631, 5632, 5633, 5635, 5637, 5638, 5639, 5641, 5643, 5644, 5645, 5646, 5647, 5648, 5649, 5650, 5651, 5652, 5654, 5655, 5656, 5662, 5663, 5664, 5665, 5666}; 
  vector<int> list_55nA = {5368, 5369, 5372, 5373, 5374, 5375, 5376, 5377, 5378, 5379, 5380, 5381, 5382, 5383, 5386, 5390, 5391, 5392, 5393, 5398, 5401, 5403, 5404, 5406, 5407}; 
  //Boundaries and contamination
  vector<double> boundaries;


  TLorentzVector *beam = new TLorentzVector();
  TLorentzVector *target = new TLorentzVector();
  
  //parameters for Local to Lab frame
  Double_t xO=294.9;//cm
  Double_t yO=0;//cm
  Double_t zO=632.4;//cm
  Double_t beta=25*TMath::DegToRad();//Angle between z-axis of sector and beam
  
  //parameters for sector geometry
  double b=394.2;//cm
  double h=385.2;//cm
  double alpha=62.9*TMath::DegToRad();
  double width=4.51;//cm
  double xr=-b/2.;
  double xl=b/2.;
  double yh=94.4;//cm
  double yl=-290.8;//cm
  double yoU=yh-84*width;
  double xoV=xl-77*width/TMath::Sin(alpha);
  double xoW=xr+77*width/TMath::Sin(alpha);
  
  //FTCal distance
  double z_FTCAL=194.3;//cm

  //Acceptance maps
  TH2F* MapSector[7][71];

  int RunNumber;
  int EventNumber;
  int Helicity;

  double strip_Q2;
  double strip_W;
  double strip_Xbj;

  double strip_El_px;
  double strip_El_py;
  double strip_El_pz;
  double strip_El_E;
  double strip_El_P;
  double strip_El_Theta;
  double strip_El_Phi;
  double strip_El_vz;
  double strip_El_PCAL_energy;
  double strip_El_ECin_energy;
  double strip_El_ECout_energy;

  double strip_Ph_px;
  double strip_Ph_py;
  double strip_Ph_pz;
  double strip_Ph_E;
  double strip_Ph_P;
  double strip_Ph_Theta;
  double strip_Ph_Phi;

  double strip_Nuc_px;
  double strip_Nuc_py;
  double strip_Nuc_pz;
  double strip_Nuc_E;
  double strip_Nuc_P;
  double strip_Nuc_Theta;
  double strip_Nuc_Phi;
  
  TVector3 VelectronIn;
  TVector3 VelectronOut;
  TVector3 VnucleonOut;
  TVector3 VphotonOut;
  TVector3 Vvirtualphoton;
  TVector3 Vlepto;
  TVector3 Vhadro;
  TVector3 VhadroPP;
  TLorentzVector PhV_Vec;
  double pp2;
  double cos2theta;
  double cos2theta_exp;
  double dcos2theta;
  double Ph_E_Th;
  double deltaE;

 
  double Phi_Nuc;
  double Phi_Ph;
  double delta_Phi;

  double t_Nuc;
  double t_Ph;
  double delta_t;

  TLorentzVector BalV;
  double miss_mom_eNg;
  double Xbal;
  double Ybal;
  double Zbal;
  double Ebal;
  double p_perp;
  int bestCandidateFlag;
  double weight;
  
  int N_Ph;
  double mm2_eNg;
  double mm2_eNg_N;
  double mm2_eg;
  double mm2_ep;
  double mm2_gp;
  double mm2_e;
  double mm2_g;
  double mm2_p;

  double theta_gamma_X;
  double theta_gamma_e;
  double theta_N_e;

  TCut Mbins[259];  
  TCut Rcuts[259];  
  std::array<std::array<double, 6>, 259> bins;
  std::array<int, 259> Nphibins;
  std::array<double, 259> bdts;

  BDT()
  { 
    //gSystem->AddDynamicPath("include/RooUnfold/src/");   
    //gSystem->Load("include/RooUnfold/libRooUnfold");
    
    gROOT->ProcessLine(".L config.C");

    gROOT->ProcessLine(".L include/Training/Training.C");
    gROOT->ProcessLine(".L include/Training/Training_Category.C");
    gROOT->ProcessLine(".L include/Training/Training_on_bins.C");
    gROOT->ProcessLine(".L include/Training/Add_BDT_var.C");
    gROOT->ProcessLine(".L include/Training/Add_BDT_var_float.C");
    gROOT->ProcessLine(".L include/Training/Add_BDT_var_Formula.C");
    gROOT->ProcessLine(".L include/Training/Add_BDT_var_float_Formula.C");
    gROOT->ProcessLine(".L include/Training/Best_BDT.C");

    gROOT->ProcessLine(".L include/Plotting/Exploration.C");
    gROOT->ProcessLine(".L include/Plotting/Stack.C");
    gROOT->ProcessLine(".L include/Plotting/Training_vars.C");
    gROOT->ProcessLine(".L include/Plotting/Single_BSA.C");
    gROOT->ProcessLine(".L include/Plotting/Single_BSA_2.C");
    gROOT->ProcessLine(".L include/Plotting/Single_BSA_3.C");
    gROOT->ProcessLine(".L include/Plotting/Single_BSA_Fit.C");
    gROOT->ProcessLine(".L include/Plotting/Get_BDT_Score.C");
    gROOT->ProcessLine(".L include/Plotting/Get_excl_vars.C");
    gROOT->ProcessLine(".L include/Plotting/Get_excl_vars_tagged.C");
    gROOT->ProcessLine(".L include/Plotting/eppi0_hists.C");
    gROOT->ProcessLine(".L include/Plotting/Compare_three.C");
    gROOT->ProcessLine(".L include/Plotting/Kin_vars.C");
    gROOT->ProcessLine(".L include/Plotting/To_bin_or_not_to_bin.C");
    
    gROOT->ProcessLine(".L include/Bkg_subtraction/Get_Contamination.C");
    gROOT->ProcessLine(".L include/Bkg_subtraction/Get_Contamination_Mostafa.C");
    gROOT->ProcessLine(".L include/Bkg_subtraction/Get_Contamination_Maxime.C");
    gROOT->ProcessLine(".L include/Bkg_subtraction/Fiducial_cuts.C");
    gROOT->ProcessLine(".L include/Bkg_subtraction/Build_DVCS_Tree.C");
    gROOT->ProcessLine(".L include/Bkg_subtraction/Get_Contamination_Fit.C");

    gROOT->ProcessLine(".L include/xsec/Resolution_Match.C");
    gROOT->ProcessLine(".L include/xsec/BM_correction.C");
    gROOT->ProcessLine(".L include/xsec/No_Rec_correction.C");
    gROOT->ProcessLine(".L include/xsec/BDTEff_Corr.C");
    gROOT->ProcessLine(".L include/xsec/RC_correction.C");
    gROOT->ProcessLine(".L include/xsec/BSA2Nev.C");
    gROOT->ProcessLine(".L include/xsec/xsec_on_bins.C");
    gROOT->ProcessLine(".L include/xsec/Theory.C");
    gROOT->ProcessLine(".L include/xsec/Phase_Space_Factor.C");
    gROOT->ProcessLine(".L include/xsec/Kin_shift_factor.C");
    gROOT->ProcessLine(".L include/xsec/Bin_Centering.C");
    gROOT->ProcessLine(".L include/xsec/Lepton_Propagator.C");
    gROOT->ProcessLine(".L include/xsec/Background_Merging.C");

    gROOT->ProcessLine(".L include/CUDA_bins/Grid_Bins.C");
    gROOT->ProcessLine(".L include/CUDA_bins/Bin_View.C");

    gROOT->ProcessLine(".L include/Add_PhEff_var.C");
    gROOT->ProcessLine(".L include/Write_Null.C");
    gROOT->ProcessLine(".L include/Merge_Bins.C");
    gROOT->ProcessLine(".L include/Tag_P_detected.C");
    gROOT->ProcessLine(".L include/Filter.C");
    gROOT->ProcessLine(".L include/Filter_Pi0.C");
    gROOT->ProcessLine(".L include/Fitting_on_bins.C");
    gROOT->ProcessLine(".L include/Is_Pi0.C");
    gROOT->ProcessLine(".L include/Check_GPU.C");
    gROOT->ProcessLine(".L include/Compute_BM_Matrix.C");


  }

  void config();
  /* Training */
  int Training(TCut cutSB, TString MC_DVCS, TString MC_Pi0, vector<TString> vars);
  int TrainingCategory(TCut cutSB, TString MC_DVCS, TString MC_Pi0, vector<TString> vars);
  void Training_on_bins(TString Data, int NBinsPhi=0, int bin=0, bool build=true, bool eta=false);
  void Add_BDT_var(TCut cutSB, TString Data, TString filename, vector<TString> vars);
  void Add_BDT_var_float(TCut cutSB, TString Data, TString output);
  void Add_BDT_var_Formula(TCut cutSB, TString Data, TString filename, vector<TString> vars);
  void Add_BDT_var_float_Formula(TCut cutSB, TString Data, TString output);
  double Best_BDT(int bin=0);
  double get_bdt_event(double strip_Xbj, double strip_Q2, double t_Ph);

  /* Plotting */
  void Explore(TString TData, TString TSim, TCut cutSB);
  void Exploration_k(int k, TString TData, TString TSim, TCut cutSB, TString extension);
  void Stack(TCut cut, TCut cut_add);
  void Training_vars(TString Data, TString MC_DVCS, TString MC_Pi0, TCut cut);
  TH1* Single_BSA(TString Data, int P_bins=12);
  void Single_BSA_2(TString BDT_Data, TString Bin_Data, vector<double> boundaries, int P_bins=12);
  void Single_BSA_3(TString BDT_Data, TString Bin_Data, vector<double> boundaries, int P_bins=12);
  void Single_BSA_Fit(TString BDT_Data, TString Fit_Data, vector<double> boundaries, int P_bins=12);
  void Get_BDT_Score();
  void Get_excl_vars(TCut cut);
  void Get_excl_vars_tagged(TCut cut);
  void eppi0_hists();
  void Compare_three(TCut cut, TString Data1, TString Data2);
  void Kin_vars(TString Data, TString MC_DVCS, TString MC_Pi0, TCut cut);
  void To_bin_or_not_to_bin(TString Data, int NumEv);
 
  /* Bkg subtraction*/
  void Get_Contamination(TCut cut,double BDT_cut);
  TH1* Get_Contamination_Mostafa(TCut cut,double BDT_cut, int Nphi, bool eta=false);
  TH1* Get_Contamination_Maxime(TCut cut, double BDT_cut, int bin_number, int Nphi);
  TH1* Get_Contamination_Fit(TCut cut,double BDT_cut, int Nphi);

  /* xsec */
  void Resolution_Match(TCut cut, TString Data, TString Sim);
  TH1F* BM_correction(TH1F*& Orig, int bin, int select);
  TH1F* No_Rec_correction(TString Data, TString MCData, double BDT_cut, int Nphi, TH1F*& Systematics);
  TH1F* BDTEff_Corr(TCut cut, TString Data, TString MCData, double BDT_cut, int Nphi);
  TH1F* F_RC(int Nphi, TH1F*& Systematics);
  TH1* BSA2Nev(TH1* BSA);
  void xsec_on_bins(int bin, int NBinsPhi=0);
  TGraph* Theory_point(int model, int bin, double xmean, double Qmean, double tmean, int Nphi);
  TGraph* Theory_integral(int model, int bin, int Nphi);
  TGraph* Theory_integral_generator(int model, int bin);
  TH1F* Phase_Space_Factor(int NBinsPhi, int bin);
  TH1F* Lepton_Propagator(int bin);
  TH1F* Background_Merging(TCut cut, int bin);

  /* Bin Migration */
  int get_index(double t, double q, double x, double p);
  void Compute_BM_Matrix();

  /* Internal function of Get_Contamination Maxime*/
  void Build_DVCS_Tree(TTree*& pDVCS_tree, TLorentzVector*& electron, TLorentzVector*& photon, TLorentzVector*& Nuc);
  TVector3 PCAL_PointFromLabToLocal(TVector3 Lab, int nsector);
  TVector3 PCAL_VectorFromLabToLocal(TVector3 Lab, int nsector);
  TVector3 FromLocalXYZtoUVW(TVector3 XYZ);
  void GetIntersectionUVW(TVector3 vertex,TVector3 gamma, TLorentzVector& intersection);
  bool EC_hit_position_fiducial_cut_homogeneous(TLorentzVector uvw);
  bool Fiducial_cut(TVector3 vertex,TVector3 gamma);
  double GetPhiDistance(TLorentzVector& gamma);
  double CheckPi0Thr(TLorentzVector photon);
  vector<double> bin_C(int select, int NBINS, TTree*& ch1 );
  vector<double> bin_C2(int select, int NBINS, TTree*& ch1 );
  void GeneratePhotonMomentum(TLorentzVector& pionMomentum, TLorentzVector& photon1, TLorentzVector& photon2);
  bool Is_DVMP(TVector3*& vertex, TLorentzVector*& photon1, TLorentzVector*& photon2);  
  bool Check_DVCS_cuts(TLorentzVector*& electron, TLorentzVector*& photon, TLorentzVector*& Nuc);
  int Is_DVCS(TTree*& pDVCS_tree, TVector3*& vertex, TLorentzVector*& electron, TLorentzVector*& photon1, TLorentzVector*& photon2, TLorentzVector*& Nuc);
  void fill_DVCS_histograms(TLorentzVector*& electron, TLorentzVector*& photon, TLorentzVector*& Nuc, TH1F*& mm2_eg, TH1F*& Phi_Ph);

  /* Internal/Alternative functions of xsec*/
  std::vector<vector<double>> ReadMeansFile(TString file); 
  TH1F* compute_kin_shift_factor(int Nphi, TString var);
  TH1F* compute_kin_shift_factor(TString var);
  void kin_shift_factor(std::vector<vector<double>> means1,std::vector<vector<double>> means2, int NbinsPhi);
  TH1F* F_bin_KM_model(int bin, double mean3d_t, double mean3d_Q, double mean3d_x);
  TH1F* F_Bin(int bin, double mean3d_t, double mean3d_Q, double mean3d_x, int select, TH1F* PS_factor);
  //TH1F* F_Bin(int bin, TH1F* factor_t, TH1F* factor_Q, TH1F* factor_x, int select);

  /*Miscellaneous*/
  void printProgress(double percentage);
  void Write_Null(int bin_number);
  double GetPhotonEff(double x, double y);
  double GetBkgMergEff(int RunNumber);
  void Add_PhEff_var(TCut cutSB, TString Data, TString output);
  void Estimate_DVCS(TString TData, TCut cutP, TCut cutNP);
  void Estimate_Pi0(TString TData, TCut cutP, TCut cutNP);  
  void Filter(TString TData, TCut TheCut, TString output);
  void Filter_Pi0(TString TData, TCut TheCut, TString output);
  void Check_GPU(bool Pi0_flag=false);
  void Bin_View(TString Data, double *bins_t, TTree*& ch1, int NumEv=29000);
  vector<vector<double>> Grid_Bins(int ii, double *bins_t, int NBINS_t, int NumEv, int NBINS_x, TTree*& Tree);
  void Fitting_on_bins(TString Data, int NumEv);
  Double_t modelFunction(Double_t *x, Double_t *params);
  void init_tree(TTree*& pDVCS_tree);
  void Is_Pi0();
  void Tag_P_Detected(TString Data_name_P, TString Data_name_NP);
  void Merge_Bins(TString data, TString output="");    
  void Compute_Systematics(int bin=0);

};



void BDT::Explore(TString Data, TString Sim, TCut cutSB){
  gSystem->Exec(TString("mkdir -p ") + Folder +TString("Exploration"));
  gSystem->Exec(TString("rm ") + Folder +TString("Exploration/*"));

  for(int k=0; k<20;k++)
    {
      Exploration_k(k, Data, Sim, cutSB,".png");
    }
}

void BDT::Estimate_DVCS(TString TData, TCut cutP, TCut cutNP){
  //Filter(cutP); //Modify filter so it filters P case
  Filter(TData, cutNP, TString("Data_NP_Theta_g_5.root"));
  Check_GPU();
}

void BDT::Estimate_Pi0(TString TData, TCut cutP, TCut cutNP){
  Filter_Pi0("~/Quality_Data_eppi0_P.root",cutP,"Data_P_Theta_g_5.root"); //Filter P
  Filter(TData, cutNP, "Data_NP_Theta_g_5.root"); //Filter NP
  Check_GPU(true);
}


void BDT::printProgress(double percentage) {
  int val = (int) (percentage * 100);
  int lpad = (int) (percentage * PBWIDTH);
  int rpad = PBWIDTH - lpad;
  printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
  fflush(stdout);
}


void BDT::init_tree(TTree*& pDVCS_tree){

  pDVCS_tree->Branch("RunNumber", &RunNumber);
  pDVCS_tree->Branch("EventNumber", &EventNumber);
  pDVCS_tree->Branch("Helicity", &Helicity);

  pDVCS_tree->Branch("strip_Q2", &strip_Q2);
  pDVCS_tree->Branch("strip_W", &strip_W);
  pDVCS_tree->Branch("strip_Xbj", &strip_Xbj);

  pDVCS_tree->Branch("strip_El_px", &strip_El_px);
  pDVCS_tree->Branch("strip_El_py", &strip_El_py);
  pDVCS_tree->Branch("strip_El_pz", &strip_El_pz);
  pDVCS_tree->Branch("strip_El_E", &strip_El_E);
  pDVCS_tree->Branch("strip_El_P", &strip_El_P);
  pDVCS_tree->Branch("strip_El_Theta", &strip_El_Theta);
  pDVCS_tree->Branch("strip_El_Phi", &strip_El_Phi);
  pDVCS_tree->Branch("strip_El_vz", &strip_El_vz);

  pDVCS_tree->Branch("strip_El_PCAL_energy", &strip_El_PCAL_energy);
  pDVCS_tree->Branch("strip_El_ECin_energy", &strip_El_ECin_energy);
  pDVCS_tree->Branch("strip_El_ECout_energy", &strip_El_ECout_energy);

  pDVCS_tree->Branch("strip_Ph_px", &strip_Ph_px);
  pDVCS_tree->Branch("strip_Ph_py", &strip_Ph_py);
  pDVCS_tree->Branch("strip_Ph_pz", &strip_Ph_pz);
  pDVCS_tree->Branch("strip_Ph_E", &strip_Ph_E);
  pDVCS_tree->Branch("strip_Ph_P", &strip_Ph_P);
  pDVCS_tree->Branch("strip_Ph_Theta", &strip_Ph_Theta);
  pDVCS_tree->Branch("strip_Ph_Phi", &strip_Ph_Phi);
    
  pDVCS_tree->Branch("strip_Nuc_px", &strip_Nuc_px);
  pDVCS_tree->Branch("strip_Nuc_py", &strip_Nuc_py);
  pDVCS_tree->Branch("strip_Nuc_pz", &strip_Nuc_pz);
  pDVCS_tree->Branch("strip_Nuc_E", &strip_Nuc_E);
  pDVCS_tree->Branch("strip_Nuc_P", &strip_Nuc_P);
  pDVCS_tree->Branch("strip_Nuc_Theta", &strip_Nuc_Theta);
  pDVCS_tree->Branch("strip_Nuc_Phi", &strip_Nuc_Phi);

  pDVCS_tree->Branch("Phi_Nuc", &Phi_Nuc);
  pDVCS_tree->Branch("Phi_Ph", &Phi_Ph);
  pDVCS_tree->Branch("delta_Phi", &delta_Phi);

  pDVCS_tree->Branch("t_Nuc", &t_Nuc);
  pDVCS_tree->Branch("t_Ph", &t_Ph);
  pDVCS_tree->Branch("delta_t", &delta_t);
  pDVCS_tree->Branch("cos2theta", &cos2theta);
  pDVCS_tree->Branch("dcos2theta", &dcos2theta);
  pDVCS_tree->Branch("Ph_E_pDVCS", &Ph_E_Th);
  pDVCS_tree->Branch("delta_E", &deltaE);

  pDVCS_tree->Branch("N_Ph", &N_Ph);
  pDVCS_tree->Branch("mm2_eNg", &mm2_eNg);
  pDVCS_tree->Branch("mm2_eNg_N", &mm2_eNg_N);
  pDVCS_tree->Branch("mm2_eg", &mm2_eg);
  pDVCS_tree->Branch("mm2_ep", &mm2_ep);
  pDVCS_tree->Branch("mm2_gp", &mm2_gp);
  pDVCS_tree->Branch("mm2_e", &mm2_e);
  pDVCS_tree->Branch("mm2_g", &mm2_g);
  pDVCS_tree->Branch("mm2_p", &mm2_p);


  pDVCS_tree->Branch("Xbal", &Xbal);
  pDVCS_tree->Branch("Ybal", &Ybal);
  pDVCS_tree->Branch("Zbal", &Zbal);
  pDVCS_tree->Branch("Ebal", &Ebal);
  pDVCS_tree->Branch("miss_mom_eNg", &miss_mom_eNg);
  pDVCS_tree->Branch("p_perp", &p_perp);
  pDVCS_tree->Branch("theta_gamma_e", &theta_gamma_e);
  pDVCS_tree->Branch("theta_gamma_X", &theta_gamma_X);
  pDVCS_tree->Branch("theta_N_e", &theta_N_e);
  pDVCS_tree->Branch("bestCandidateFlag", &bestCandidateFlag);
}

double BDT::GetPhotonEff(double x, double y)
{
/*
    if (!h_ef_FT || !h_ef_FD) return -1; // safety

    if (x < 20 && y < 20)
        return h_ef_FT->GetBinContent(h_ef_FT->FindBin(x, y));
    else
        return h_ef_FD->GetBinContent(h_ef_FD->FindBin(x, y));
*/
double sector1, sector2, sector3, sector4, sector5, sector6;
double FT_eff;

if (torus=="inb")
{
sector1=	0.809699	;
sector2=	0.785553	;
sector3=	0.781175	;
sector4=	0.76761	;
sector5=	0.824153	;
sector6=	0.791097	;
FT_eff=	1.14874	;
}
else
{
sector1=	0.771001	;
sector2=	0.771312	;
sector3=	0.780929	;
sector4=	0.744726	;
sector5=	0.809393	;
sector6=	0.756319	;
FT_eff=	1.26698	;
}
/*
sector1=	0.7904	;
sector2=	0.7784	;
sector3=	0.7811	;
sector4=	0.7562	;
sector5=	0.8168	;
sector6=	0.7737	;
FT_eff=	1.2079	;
*/

  if(x*x+y*y<20.*20.)
  {
  return FT_eff;
  }
  else
  {
  double phi = std::atan2(y, x) * 180.0 / M_PI;

  if (phi < 30 && phi >= -30)
    {
      return sector1;
    }
  else if (phi < 90 && phi >= 30)
    {
      return sector2;
    }
  else if (phi < 150 && phi >= 90)
    {
      return sector3;
    }
  else if (phi >= 150 || phi < -150)
    {
      return sector4;
    }
  else if (phi < -90 && phi >= -150)
    {
      return sector5;
    }
  else if (phi < -30 && phi >= -90)
    {
      return sector6;
    }
  else
  	return 0.0;
   }
}


double BDT::GetBkgMergEff(int RunNumber)
{
  double m, b, x, eff;
  auto it5 = std::find(list_5nA.begin(), list_5nA.end(), RunNumber);
  if (it5 != list_5nA.end())
    x=5.0;
  auto it40 = std::find(list_40nA.begin(), list_40nA.end(), RunNumber);
  if (it40 != list_40nA.end())
    x=40.0;
  auto it45 = std::find(list_45nA.begin(), list_45nA.end(), RunNumber);
  if (it45 != list_45nA.end())
    x=45.0;
  auto it50 = std::find(list_50nA.begin(), list_50nA.end(), RunNumber);
  if (it50 != list_50nA.end())
    x=50.0;
  auto it55 = std::find(list_55nA.begin(), list_55nA.end(), RunNumber);
  if (it55 != list_55nA.end())
    x=55.0;
  
  if (torus=="inb")
    m=-0.25377;
  else
    m=-0.33145;


  eff=100. + m*x;
  return eff/100.;
}


void BDT::Compute_Systematics(int bin=0){
	TCut cut_0= cut;
	double BDT_value_0=BDT_value;
 	TString Folder_0=Folder;	
 	BDT_value_sys=BDT_value + 0.02;
			
	BDT_value=BDT_value_sys;
  gSystem->Exec(TString("mkdir -p ") + TString("Systematics_BDT/"));	
	Folder = TString("Systematics_BDT/");
  bdt_sys=true;
	gSystem->Exec(TString("cp -u ") + Folder_0 + TString("Data_NP_Theta_g_5.root ") + Folder) ;
	gSystem->Exec(TString("rm -r ") + Folder + Form("bin_%i",bin));
	gSystem->Exec(TString("cp -r ") + Folder_0 + Form("bin_%i",bin) + TString(" ") + Folder + Form("bin_%i",bin)) ;
	Training_on_bins(Data, 0, bin, false);
	BDT_value=BDT_value_0;
  bdt_sys=false;
	gSystem->Exec(TString("find ") + Folder + Form("bin_%i/",bin) +TString(" -type f ! -name '*.txt' -exec rm -r -f {} \\;"));
	gSystem->Exec(TString("rm -r ") + Folder + Form("bin_%i/dataset",bin));
	gSystem->Exec(TString("rm -r ") + Folder + Form("bin_%i/Exploration",bin));

  gSystem->Exec(TString("mkdir -p ") + Folder_0 + TString("Systematics_pid/"));	
	Folder = TString("Systematics_pid/");
	pid_sys=true;
	generate_most=true;	
	gSystem->Exec(TString("cp -u ") + Folder_0 + TString("Data_NP_Theta_g_5.root ") + Folder) ;
	gSystem->Exec(TString("rm -rf ") + Folder + Form("bin_%i",bin));
	gSystem->Exec(TString("cp -r ") + Folder_0 + Form("bin_%i",bin) + TString(" ") + Folder + Form("bin_%i",bin)) ;
	Training_on_bins(Data, 0, bin, false);
	pid_sys=false;
	generate_most=false;
	cut = cut_0;
	gSystem->Exec(TString("find ") + Folder + Form("bin_%i/",bin) +TString(" -type f ! -name '*.txt' -exec rm -r -f {} \\;"));
	gSystem->Exec(TString("rm -rf ") + Folder + Form("bin_%i/dataset",bin));
	gSystem->Exec(TString("rm -rf ") + Folder + Form("bin_%i/Exploration",bin));

	Folder = Folder_0;
	
}

BDT *gBDT = nullptr;

double GetBDTCut(double xB, double Q2, double t)
{
return gBDT->get_bdt_event(xB, Q2, t);
}


