#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TThread.h"
//#include "include/TUnfold_V17.9/TUnfold.h"
#include "include/RooUnfold/build/RooUnfoldResponse.h"
#include "include/RooUnfold/build/RooUnfoldBayes.h"
#include "include/RooUnfold/build/RooUnfoldSvd.h"
//#include "RooUnfoldTUnfold.h

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60


class BDT
{
public:
  TString dir;
  TString extBSA;
  TString Folder;
  TString DVCS;
  TString Pi0;
  TString Data;
  TString TDVCS;
  TString TPi0;
  TString TData;
  TString eppi0;
  TString eppi0_name;
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
   
  TCut cut;
  TCut cut2g;
  TCut cut_bin;
  TCut cut_sys;
  TCut cut_pid;
  TCut cut_ref;
  
  bool means_most;
  bool means_maxi;
  bool generate;
  bool recast;
  bool add_BDT_Max;
  bool generate_most;
  bool categories;
  bool pid_sys=false;

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

  double nft;
  double BSA_Amplitude;
  double BSA_Amplitude_most;
  double BSA_Amplitude_maxi;
  double BSA_Amplitude_fit;
  double BSA_Amplitude_most_fit;
  double BSA_Amplitude_maxi_fit;
  double BSA_Error_fit;
  double BSA_Error_most_fit;
  double BSA_Error_maxi_fit;
  int N_Phi;
  double BDT_value;
  double BDT_value_sys;
  double Bpol;
  
  vector<TString> Vars;

  //Boundaries and contamination
  vector<double> boundaries;

  
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

  TCut Mbins[64];  
  TCut Rcuts[64];  

  double bins[64][6] = {
			{-0.2, 0, 1, 1.4, 0, 0.13},
			{-0.2, 0, 1, 1.4, 0.13, 0.21},
			{-0.2, 0, 1, 1.4, 0.21, 1},
			{-0.4, -0.2, 1, 1.4, 0, 0.13},
			{-0.4, -0.2, 1, 1.4, 0.13, 0.21},
			{-0.4, -0.2, 1, 1.4, 0.21, 1},
			{-0.8, -0.4, 1, 1.4, 0, 0.13},
			{-0.8, -0.4, 1, 1.4, 0.13, 0.21},
			{-0.8, -0.4, 1, 1.4, 0.21, 1},
			{-100, -0.8, 1, 1.4, 0, 0.13},
			{-100, -0.8, 1, 1.4, 0.13, 0.21},
			{-100, -0.8, 1, 1.4, 0.21, 1},

			{-0.2, 0, 1.4, 1.8, 0, 0.13},
			{-0.2, 0, 1.4, 1.8, 0.13, 0.21},
			{-0.2, 0, 1.4, 1.8, 0.21, 1},
			{-0.4, -0.2, 1.4, 1.8, 0, 0.13},
			{-0.4, -0.2, 1.4, 1.8, 0.13, 0.21},
			{-0.4, -0.2, 1.4, 1.8, 0.21, 1},
			{-0.8, -0.4, 1.4, 1.8, 0, 0.13},
			{-0.8, -0.4, 1.4, 1.8, 0.13, 0.21},
			{-0.8, -0.4, 1.4, 1.8, 0.21, 1},
			{-100, -0.8, 1.4, 1.8, 0, 0.13},
			{-100, -0.8, 1.4, 1.8, 0.13, 0.21},
			{-100, -0.8, 1.4, 1.8, 0.21, 1},

			{-0.2, 0, 1.8, 2.4, 0, 0.16},
			{-0.2, 0, 1.8, 2.4, 0.16, 0.26},
			{-0.2, 0, 1.8, 2.4, 0.26, 1},
			{-0.4, -0.2, 1.8, 2.4, 0, 0.16},
			{-0.4, -0.2, 1.8, 2.4, 0.16, 0.26},
			{-0.4, -0.2, 1.8, 2.4, 0.26, 1},
			{-0.8, -0.4, 1.8, 2.4, 0, 0.16},
			{-0.8, -0.4, 1.8, 2.4, 0.16, 0.26},
			{-0.8, -0.4, 1.8, 2.4, 0.26, 1},
			{-100, -0.8, 1.8, 2.4, 0, 0.16},
			{-100, -0.8, 1.8, 2.4, 0.16, 0.26},
			{-100, -0.8, 1.8, 2.4, 0.26, 1},

			{-0.2, 0, 2.4, 3.25, 0, 0.21},
			{-0.2, 0, 2.4, 3.25, 0.21, 0.33},
			{-0.2, 0, 2.4, 3.25, 0.33, 1},
			{-0.4, -0.2, 2.4, 3.25, 0, 0.21},
			{-0.4, -0.2, 2.4, 3.25, 0.21, 0.33},
			{-0.4, -0.2, 2.4, 3.25, 0.33, 1},
			{-0.8, -0.4, 2.4, 3.25, 0, 0.21},
			{-0.8, -0.4, 2.4, 3.25, 0.21, 0.33},
			{-0.8, -0.4, 2.4, 3.25, 0.33, 1},
			{-100, -0.8, 2.4, 3.25, 0, 0.21},
			{-100, -0.8, 2.4, 3.25, 0.21, 0.33},
			{-100, -0.8, 2.4, 3.25, 0.33, 1},

			{-0.2, 0, 3.25, 5, 0, 0.33},
			{-0.2, 0, 3.25, 5, 0.33, 1},
			{-0.4, -0.2, 3.25, 5, 0, 0.33},
			{-0.4, -0.2, 3.25, 5, 0.33, 1},			
			{-0.8, -0.4, 3.25, 5, 0, 0.33},
			{-0.8, -0.4, 3.25, 5, 0.33, 1},
			{-100, -0.8, 3.25, 5, 0, 0.33},
			{-100, -0.8, 3.25, 5, 0.33, 1},
			{-0.2, 0, 5, 15, 0, 0.55},
			{-0.2, 0, 5, 15, 0.55, 1},
			{-0.4, -0.2, 5, 15, 0, 0.55},
			{-0.4, -0.2, 5, 15, 0.55, 1},
			{-0.8, -0.4, 5, 15, 0, 0.55},
			{-0.8, -0.4, 5, 15, 0.55, 1},
			{-100, -0.8, 5, 15, 0, 0.55},
			{-100, -0.8, 5, 15, 0.55, 1}
  };

  int Nphibins[64] = {
		      29,
		      22,
		      18,
		      30,
		      23,
		      13,
		      27,
		      26,
		      9,
		      14,
		      12,
		      12,
		      23,
		      24,
		      21,
		      24,
		      23,
		      15,
		      17,
		      22,
		      11,
		      18,
		      14,
		      23,
		      24,
		      25,
		      23,
		      24,
		      28,
		      15,
		      19,
		      27,
		      12,
		      27,
		      17,
		      10,
		      21,
		      21,
		      18,
		      23,
		      25,
		      15,
		      19,
		      22,
		      12,
		      13,
		      16,
		      10,
		      19,
		      19,
		      23,
		      18,
		      21,
		      17,
		      15,
		      13,
		      12,
		      12,
		      13,
		      12,
		      13,
		      12,
		      13,
		      18};

  BDT()
  {
  Mbins[0]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0    && strip_Xbj <= 0.13");
  Mbins[1]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0.13 && strip_Xbj <= 0.21");
  Mbins[2]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0.21 && strip_Xbj <= 1.0 ");
  Mbins[3]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0    && strip_Xbj <= 0.13");
  Mbins[4]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0.13 && strip_Xbj <= 0.21");
  Mbins[5]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0.21 && strip_Xbj <= 1.0 ");
  Mbins[6]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0    && strip_Xbj <= 0.13");
  Mbins[7]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0.13 && strip_Xbj <= 0.21");
  Mbins[8]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0.21 && strip_Xbj <= 1.0 ");
  Mbins[9]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0    && strip_Xbj <= 0.13");
  Mbins[10]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0.13 && strip_Xbj <= 0.21");
  Mbins[11]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 1 && strip_Q2 <= 1.4 && strip_Xbj > 0.21 && strip_Xbj <= 1.0 ");

  Mbins[12]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0    && strip_Xbj <= 0.13");
  Mbins[13]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0.13 && strip_Xbj <= 0.21");
  Mbins[14]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0.21 && strip_Xbj <= 1.0 ");
  Mbins[15]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0    && strip_Xbj <= 0.13");
  Mbins[16]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0.13 && strip_Xbj <= 0.21");
  Mbins[17]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0.21 && strip_Xbj <= 1.0 ");
  Mbins[18]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0    && strip_Xbj <= 0.13");
  Mbins[19]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0.13 && strip_Xbj <= 0.21");
  Mbins[20]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0.21 && strip_Xbj <= 1.0 ");
  Mbins[21]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0    && strip_Xbj <= 0.13");
  Mbins[22]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0.13 && strip_Xbj <= 0.21");
  Mbins[23]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 1.4 && strip_Q2 <= 1.8 && strip_Xbj > 0.21 && strip_Xbj <= 1.0 ");

  Mbins[24]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0    && strip_Xbj <= 0.16");
  Mbins[25]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0.16 && strip_Xbj <= 0.26");
  Mbins[26]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0.26 && strip_Xbj <= 1.0 ");
  Mbins[27]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0    && strip_Xbj <= 0.16");
  Mbins[28]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0.16 && strip_Xbj <= 0.26");
  Mbins[29]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0.26 && strip_Xbj <= 1.0 ");
  Mbins[30]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0    && strip_Xbj <= 0.16");
  Mbins[31]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0.16 && strip_Xbj <= 0.26");
  Mbins[32]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0.26 && strip_Xbj <= 1.0 ");
  Mbins[33]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0    && strip_Xbj <= 0.16");
  Mbins[34]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0.16 && strip_Xbj <= 0.26");
  Mbins[35]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 1.8 && strip_Q2 <= 2.4 && strip_Xbj > 0.26 && strip_Xbj <= 1.0 ");

  Mbins[36]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0    && strip_Xbj <= 0.21");
  Mbins[37]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0.21 && strip_Xbj <= 0.33");
  Mbins[38]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0.33 && strip_Xbj <= 1.0 ");
  Mbins[39]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0    && strip_Xbj <= 0.21");
  Mbins[40]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0.21 && strip_Xbj <= 0.33");
  Mbins[41]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0.33 && strip_Xbj <= 1.0 ");
  Mbins[42]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0    && strip_Xbj <= 0.21");
  Mbins[43]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0.21 && strip_Xbj <= 0.33");
  Mbins[44]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0.33 && strip_Xbj <= 1.0 ");
  Mbins[45]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0    && strip_Xbj <= 0.21");
  Mbins[46]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0.21 && strip_Xbj <= 0.33");
  Mbins[47]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 2.4 && strip_Q2 <= 3.25 && strip_Xbj > 0.33 && strip_Xbj <= 1.0 ");

  Mbins[48]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 3.25 && strip_Q2 <= 5.0 && strip_Xbj > 0    && strip_Xbj <= 0.33");
  Mbins[49]= TCut("bestCandidateFlag==1 && t_Ph<=0    && t_Ph>-0.2 && strip_Q2 > 3.25 && strip_Q2 <= 5.0 && strip_Xbj > 0.33 && strip_Xbj <= 1.0 ");
  Mbins[50]= TCut("bestCandidateFlag==1 && t_Ph<=0.2  && t_Ph>-0.4 && strip_Q2 > 3.25 && strip_Q2 <= 5.0 && strip_Xbj > 0    && strip_Xbj <= 0.33 ");
  Mbins[51]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 3.25 && strip_Q2 <= 5.0 && strip_Xbj > 0.33 && strip_Xbj <= 1.0  ");
  Mbins[52]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 3.25 && strip_Q2 <= 5.0 && strip_Xbj > 0.   && strip_Xbj <= 0.33");
  Mbins[53]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 3.25 && strip_Q2 <= 5.0 && strip_Xbj > 0.33 && strip_Xbj <= 1.0 ");
  Mbins[54]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 3.25 && strip_Q2 <= 5.0 && strip_Xbj > 0    && strip_Xbj <= 0.33");
  Mbins[55]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 3.25 && strip_Q2 <= 5.0 && strip_Xbj > 0.33 && strip_Xbj <= 1.0 ");

  Mbins[56]= TCut("bestCandidateFlag==1 && t_Ph<=0 && t_Ph>-0.2 && strip_Q2 > 5.0 && strip_Q2 <= 15.0 && strip_Xbj > 0    && strip_Xbj <= 0.55");
  Mbins[57]= TCut("bestCandidateFlag==1 && t_Ph<=0 && t_Ph>-0.2 && strip_Q2 > 5.0 && strip_Q2 <= 15.0 && strip_Xbj > 0.55 && strip_Xbj <= 1.0 ");
  Mbins[58]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 5.0 && strip_Q2 <= 15.0 && strip_Xbj > 0    && strip_Xbj <= 0.55");
  Mbins[59]= TCut("bestCandidateFlag==1 && t_Ph<=-0.2 && t_Ph>-0.4 && strip_Q2 > 5.0 && strip_Q2 <= 15.0 && strip_Xbj > 0.55 && strip_Xbj <= 1.0 ");
  Mbins[60]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 5.0 && strip_Q2 <= 15.0 && strip_Xbj > 0    && strip_Xbj <= 0.55");
  Mbins[61]= TCut("bestCandidateFlag==1 && t_Ph<=-0.4 && t_Ph>-0.8 && strip_Q2 > 5.0 && strip_Q2 <= 15.0 && strip_Xbj > 0.55 && strip_Xbj <= 1.0 ");
  Mbins[62]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 5.0 && strip_Q2 <= 15.0 && strip_Xbj > 0    && strip_Xbj <= 0.55");
  Mbins[63]= TCut("bestCandidateFlag==1 && t_Ph<=-0.8 && t_Ph>-100 && strip_Q2 > 5.0 && strip_Q2 <= 15.0 && strip_Xbj > 0.55 && strip_Xbj <= 1.0 ");


  Rcuts[0]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[1]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[2]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.3 && theta_gamma_X<0.8");
  Rcuts[3]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");
  Rcuts[4]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");
  Rcuts[5]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<1.0 && abs(mm2_eNg)<0.005");
  Rcuts[6]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");
  Rcuts[7]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.3 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");

  Rcuts[8]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.3 && theta_gamma_X<0.7 && abs(mm2_eNg)<0.005");
  Rcuts[9]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.15 && theta_gamma_X<0.3 && abs(mm2_eNg)<0.002 && delta_t>0");
  Rcuts[10]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005 && delta_t>0");
  Rcuts[11]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.3 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");
  Rcuts[12]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.15 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[13]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");
  Rcuts[14]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[15]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");

  Rcuts[16]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.7 && abs(mm2_eNg)<0.005");
  Rcuts[17]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");
  Rcuts[18]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[19]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");
  Rcuts[20]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");
  Rcuts[21]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[22]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.1 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[23]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");

  Rcuts[24]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.2 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[25]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[26]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.3 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[27]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.3 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[28]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");
  Rcuts[29]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");
  Rcuts[30]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[31]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");

  Rcuts[32]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.7 && abs(mm2_eNg)<0.005");
  Rcuts[33]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[34]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.1 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");
  Rcuts[35]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[36]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[37]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[38]= TCut("bestCandidateFlag==1");
  Rcuts[39]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");

  Rcuts[40]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");
  Rcuts[41]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[42]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[43]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");
  Rcuts[44]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");
  Rcuts[45]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[46]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[47]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.3 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");

  Rcuts[48]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");
  Rcuts[49]= TCut("bestCandidateFlag==1");
  Rcuts[50]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.5 && abs(mm2_eNg)<0.005");
  Rcuts[51]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[52]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[53]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.8 && abs(mm2_eNg)<0.005");
  Rcuts[54]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[55]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");

  Rcuts[56]= TCut("bestCandidateFlag==1");
  Rcuts[57]= TCut("bestCandidateFlag==1");
  Rcuts[58]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[59]= TCut("bestCandidateFlag==1");
  Rcuts[60]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.6 && abs(mm2_eNg)<0.005");
  Rcuts[61]= TCut("bestCandidateFlag==1");
  Rcuts[62]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");
  Rcuts[63]= TCut("bestCandidateFlag==1 && miss_mom_eNg<0.4 && theta_gamma_X<0.4 && abs(mm2_eNg)<0.005");


    gROOT->ProcessLine(".L include/Training.C");
    gROOT->ProcessLine(".L include/Training_Category.C");
    gROOT->ProcessLine(".L include/Add_BDT_var.C");
    gROOT->ProcessLine(".L include/Add_BDT_var2.C");
    gROOT->ProcessLine(".L include/Add_BDT_var_float.C");
    gROOT->ProcessLine(".L include/Add_BDT_var_Formula.C");
    gROOT->ProcessLine(".L include/Add_BDT_var_float_Formula.C");
    gROOT->ProcessLine(".L include/Exploration.C");
    gROOT->ProcessLine(".L include/FilterP.C");
    gROOT->ProcessLine(".L include/Filter.C");
    gROOT->ProcessLine(".L include/Filter_Pi0.C");
    gROOT->ProcessLine(".L include/Check_GPU.C");
    gROOT->ProcessLine(".L include/Stack.C");
    gROOT->ProcessLine(".L include/Training_vars.C");
    gROOT->ProcessLine(".L include/Kin_vars.C");
    gROOT->ProcessLine(".L include/Bin_View.C");
    gROOT->ProcessLine(".L include/Grid_Bins.C");
    gROOT->ProcessLine(".L include/Training_on_bins.C");
    gROOT->ProcessLine(".L include/Training_on_Maxime_bins.C");
    gROOT->ProcessLine(".L include/Single_BSA.C");
    gROOT->ProcessLine(".L include/Single_BSA_Maxime.C");
    gROOT->ProcessLine(".L include/Fitting_on_bins.C");
    gROOT->ProcessLine(".L include/Single_BSA_Fit.C");
    gROOT->ProcessLine(".L include/To_bin_or_not_to_bin.C");
    gROOT->ProcessLine(".L include/Single_BSA_2.C");
    gROOT->ProcessLine(".L include/Single_BSA_3.C");
    gROOT->ProcessLine(".L include/P_vs_NP.C");
    gROOT->ProcessLine(".L include/Is_Pi0.C");
    gROOT->ProcessLine(".L include/Get_Contamination.C");
    gROOT->ProcessLine(".L include/Get_Contamination_Mostafa.C");
    gROOT->ProcessLine(".L include/Get_Contamination_Mostafa_Maxime.C");
    gROOT->ProcessLine(".L include/Maxime.C");
    gROOT->ProcessLine(".L include/Fiducial_cuts.C");
    gROOT->ProcessLine(".L include/Build_DVCS_Tree.C");
    gROOT->ProcessLine(".L include/Compare_three.C");
    gROOT->ProcessLine(".L include/Compute_BM_Matrix.C");
    gROOT->ProcessLine(".L include/Get_BDT_Score.C");
    gROOT->ProcessLine(".L include/Get_excl_vars.C");
    gROOT->ProcessLine(".L include/eppi0_hists.C");
    gROOT->ProcessLine(".L include/Merge_Bins.C");
    
    dir="/work/clas12/jsalvg/RGA-Analysis/outb/P/";
    extBSA="/work/clas12/jsalvg/RGA-Analysis/outb/P/Maxime_BSA/"; //External BSA, from analysis note
    Folder="Analysis/";
    //Folder="Maxime_bins/";
    gSystem->Exec(TString("mkdir -p ") + Folder);
    
    DVCS="../Sample_Train_Sim_DVCS.root";    
    Pi0 ="../Sample_Pi_as_DVCS.root";
    //Pi0 ="../../RG-A:DVCS/files/Sample_Pi_as_DVCS_Data_P.root";
    //Pi0 ="../../RG-A:DVCS/files/Maxime_pi0.root";
    Data="/work/clas12/jsalvg/Data/DVCS/RGA/outb/Quality2_Data_P_gpcorr.root";
    TData="Tested_Quality_Data.root";
    TDVCS="Tested_DVCS.root";
    TPi0="Tested_Pi0.root";
    
    epeta = "/work/clas12/jsalvg/Data/eta/RGA/outb/Quality_Data_epeta_P.root";	
    sim_eta_as_dvcs = "/work/clas12/jsalvg/RGA-Simulation/outb/eta/P/Quality_eta_as_DVCS_P.root";
    sim_epeta="/work/clas12/jsalvg/RGA-Simulation/outb/eta/P/Quality_Sim_epeta_P.root";

    eppi0_name = "Quality3_Data_eppi0_P.root";	
    eppi0 = "../" + eppi0_name;	
    maps_path = "../maps/";
    sim_eppi0="../Quality_Sim_eppi0_P.root";
    sim_eppi0_1="../Quality_Sim_eppi0_P_1.root";
    sim_pi_as_dvcs = "../Quality_Pi_as_DVCS_P.root";
    sim_pi_as_dvcs_1 = "../Quality_Pi_as_DVCS_P_1.root";
    BM_Sim="../Quality_BM_DVCS.root";
    TBM_Sim="Tested_BM_Sim.root";
    
    cut="bestCandidateFlag==1 && \
    strip_Xbj <1 && strip_Xbj >0 && t_Ph <0 && strip_Q2 > 1.0 && \
    strip_W > 2 && strip_El_P > 1.0 && strip_Ph_P>2  && strip_El_vz < 10 && strip_El_vz > -12 && \
    theta_gamma_e > 8 && abs(delta_t)<2 && abs(delta_Phi)%180 < 2 && TMath::Sqrt(Xbal * Xbal + Ybal*Ybal + Zbal*Zbal) <1 ";
  
    cut_sys="bestCandidateFlag==1 &&\
    strip_Xbj <1 && strip_Xbj >0 && t_Ph <0 && strip_Q2 > 1.0 && \
    strip_W > 2 && strip_El_P > 1.0 && strip_Ph_P>2  && strip_El_vz < 10 && strip_El_vz > -12 && \
    theta_gamma_e > 8 && abs(delta_t)<1.5 && abs(delta_Phi)%180 < 1.5 && TMath::Sqrt(Xbal * Xbal + Ybal*Ybal + Zbal*Zbal) <0.8 ";

    cut_pid="abs(strip_El_vz - strip_Nuc_vz)<20 && \
    (strip_Ph_status <2000 || (strip_Ph_status>=2000 && strip_El_sector!=strip_Ph_sector)) && \
    (strip_El_P<4.5 || (strip_El_P>4.5 && strip_El_ECin_energy/strip_El_P<0.2 - strip_El_PCAL_energy/strip_El_P))";

    //cut_ref="delta_t<0.1 && miss_mom_eNg<0.4 && theta_gamma_X < 0.6";
    cut_ref="bestCandidateFlag==1 && theta_gamma_X<1";

    //Training variables
    Vars.push_back(TString("mm2_eNg"));
    Vars.push_back(TString("mm2_eg"));
    Vars.push_back(TString("delta_Phi"));
    Vars.push_back(TString("delta_t"));
    Vars.push_back(TString("theta_gamma_X"));
    //Vars.push_back(TString("abs(mm2_eg-0.88)"));
    //Vars.push_back(TString("abs(delta_Phi)"));
    //Vars.push_back(TString("abs(delta_t)"));
    //Vars.push_back(TString("theta_gamma_X"));

    Bpol=0.89;
    BDT_value=0.0;
    BDT_value_sys=0.04;
    N_Phi=15;

    means_most=true;
    means_maxi=true;

    generate=false;
    recast=false;
    add_BDT_Max=false;

    generate_most=false;
    

//&&(t_Ph<-(strip_Q2*0.938 + (strip_Q2/strip_Xbj)*( (strip_Q2/(2*0.938*strip_Xbj)) - sqrt(strip_Q2 + pow((strip_Q2/(2*0.938*strip_Xbj)),2))))/(0.938 + (strip_Q2/(2*0.938*strip_Xbj)) - sqrt(strip_Q2 + pow((strip_Q2/(2*0.938*strip_Xbj)),2))))
  }


  int Training(TCut cutSB, TString MC_DVCS, TString MC_Pi0, vector<TString> vars);
  int TrainingCategory(TCut cutSB, TString MC_DVCS, TString MC_Pi0, vector<TString> vars);
  void Training_vars(TString Data, TString MC_DVCS, TString MC_Pi0, TCut cut);
  void Kin_vars(TString Data, TString MC_DVCS, TString MC_Pi0, TCut cut);
  void Add_BDT_var(TCut cutSB, TString Data, TString filename, vector<TString> vars);
  void Add_BDT_var_Formula(TCut cutSB, TString Data, TString filename, vector<TString> vars);
  void Add_BDT_var2(TString filename);
  void Add_BDT_var_float(TCut cutSB, TString Data, TString output);
  void Add_BDT_var_float_Formula(TCut cutSB, TString Data, TString output);
  void Explore(TString TData, TString TSim, TCut cutSB);
  void Exploration_k(int k, TString TData, TString TSim, TCut cutSB, TString extension);
  void Best(int k, TString TData, TString TSim, TCut cutSB);
  void Estimate_DVCS(TString TData, TCut cutP, TCut cutNP);
  void Estimate_Pi0(TString TData, TCut cutP, TCut cutNP);  
  void FilterP(TCut TheCut);
  void Filter_Pi0(TString TData, TCut TheCut, TString output);
  void Filter(TString TData, TCut TheCut, TString output);
  void Check_GPU(bool Pi0_flag=false);
  void Stack(TCut cut, TCut cut_add);
  void printProgress(double percentage);
  void Bin_View(TString Data, double *bins_t, TTree*& ch1, int NumEv=29000);
  vector<vector<double>> Grid_Bins(int ii, double *bins_t, int NBINS_t, int NumEv, int NBINS_x, TTree*& Tree);
  void Training_on_bins(TString Data, int NBinsPhi=0, int bin=0, bool build=true, bool eta=false);
  void Training_on_Maxime_bins(TString Data);
  TH1* Single_BSA(TString Data, int P_bins=12);
  TH1* Single_BSA_Maxime(TString Data, vector<double> Pbins);
  void Fitting_on_bins(TString Data, int NumEv);
  void Single_BSA_Fit(TString BDT_Data, TString Fit_Data, vector<double> boundaries, int P_bins=12);
  void To_bin_or_not_to_bin(TString Data, int NumEv);
  void Single_BSA_2(TString BDT_Data, TString Bin_Data, vector<double> boundaries, int P_bins=12);
  void Single_BSA_3(TString BDT_Data, TString Bin_Data, vector<double> boundaries, int P_bins=12);
  void P_vs_NP(TString Data, int NumEv);
  void Is_Pi0();
  void Get_Contamination(TCut cut,double BDT_cut);
  TH1* Get_Contamination_Mostafa(TCut cut,double BDT_cut, int Nphi, bool eta);
  TH1* Get_Contamination_Mostafa_Maxime(TCut cut, vector<double> Pbins);
  TH1* Maxime(TCut cut, double BDT_cut, int bin_number, int Nphi);
  void init_tree(TTree*& pDVCS_tree);
  void Build_DVCS_Tree(TTree*& pDVCS_tree, TLorentzVector*& electron, TLorentzVector*& photon, TLorentzVector*& Nuc);
  
  vector<double> bin_C(int select, int NBINS, TTree*& ch1 );
  vector<double> bin_C2(int select, int NBINS, TTree*& ch1 );
  void GeneratePhotonMomentum(TLorentzVector& pionMomentum, TLorentzVector& photon1, TLorentzVector& photon2);
  bool Is_DVMP(TVector3*& vertex, TLorentzVector*& photon1, TLorentzVector*& photon2);  
  bool Check_DVCS_cuts(TLorentzVector*& electron, TLorentzVector*& photon, TLorentzVector*& Nuc);
  int Is_DVCS(TTree*& pDVCS_tree, TVector3*& vertex, TLorentzVector*& electron, TLorentzVector*& photon1, TLorentzVector*& photon2, TLorentzVector*& Nuc);
  void fill_DVCS_histograms(TLorentzVector*& electron, TLorentzVector*& photon, TLorentzVector*& Nuc, TH1F*& mm2_eg, TH1F*& Phi_Ph);


  TVector3 PCAL_PointFromLabToLocal(TVector3 Lab, int nsector);
  TVector3 PCAL_VectorFromLabToLocal(TVector3 Lab, int nsector);
  TVector3 FromLocalXYZtoUVW(TVector3 XYZ);
  void GetIntersectionUVW(TVector3 vertex,TVector3 gamma, TLorentzVector& intersection);
  bool EC_hit_position_fiducial_cut_homogeneous(TLorentzVector uvw);
  bool Fiducial_cut(TVector3 vertex,TVector3 gamma);
  double GetPhiDistance(TLorentzVector& gamma);
  double CheckPi0Thr(TLorentzVector photon);
  void Compare_three(TCut cut, TString Data1, TString Data2);
  
  
  void Compute_Systematics(TString Data, int NBinsPhi=0, int bin=0, bool build=true);
  int get_index(double t, double q, double x, double p);
  void Compute_BM_Matrix();
  void Get_BDT_Score();
  void Get_excl_vars(TCut cut);
  void eppi0_hists();

  void Merge_Bins(TString data);    
  };


void BDT::Explore(TString Data, TString Sim, TCut cutSB){
  gSystem->Exec(TString("mkdir -p ") + Folder +TString("Exploration"));
  gSystem->Exec(TString("rm ") + Folder +TString("Exploration/*"));

  for(int k=0; k<20;k++)
    {
      Exploration_k(k, Data, Sim, cutSB,".png");
    }
}

void BDT::Best(int k, TString TData, TString TSim, TCut cutSB){
  Exploration_k(k, TData, TSim, cutSB, ".pdf");
}

void BDT::Estimate_DVCS(TString TData, TCut cutP, TCut cutNP){
  FilterP(cutP);
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


void BDT::Compute_Systematics(TString Data, int NBinsPhi=0, int bin=0, bool build=true){
	//Compute_BM_Matrix();

	TCut cut_0= cut;
	double BDT_value_0=BDT_value;
    TString Folder_0=Folder;	
		
	cut=cut_sys;
	Folder = TString("Systematics_cut/");
	gSystem->Exec(TString("cp -u ") + Folder_0 + TString("Data_NP_Theta_g_5.root ") + Folder) ;
	Training_on_bins(Data, NBinsPhi, bin, build);
	cut=cut_0;
	gSystem->Exec(TString("find ") + Folder + Form("bin_%i/",bin) +TString(" -type f ! -name '*.txt' -exec rm -r -f {} \\;"));
	gSystem->Exec(TString("rm -r ") + Folder + Form("bin_%i/dataset",bin));
	gSystem->Exec(TString("rm -r ") + Folder + Form("bin_%i/Exploration",bin));
	
	Folder = TString("Systematics_pid/");
	pid_sys=true;
	gSystem->Exec(TString("cp -u ") + Folder_0 + TString("Data_NP_Theta_g_5.root ") + Folder) ;
	Training_on_bins(Data, NBinsPhi, bin, build);
	pid_sys=false;

	BDT_value=BDT_value_sys;
    gSystem->Exec(TString("mkdir -p ") + Folder_0 + TString("Systematics_BDT/"));	
	Folder = TString("Systematics_BDT/");
	gSystem->Exec(TString("cp -u ") + Folder_0 + TString("Data_NP_Theta_g_5.root ") + Folder) ;
	gSystem->Exec(TString("rm -r ") + Folder + Form("bin_%i",bin));
	gSystem->Exec(TString("cp -r ") + Folder_0 + Form("bin_%i",bin) + TString(" ") + Folder + Form("bin_%i",bin)) ;
	Training_on_bins(Data, NBinsPhi, bin, false);
	BDT_value=BDT_value_0;
	gSystem->Exec(TString("find ") + Folder + Form("bin_%i/",bin) +TString(" -type f ! -name '*.txt' -exec rm -r -f {} \\;"));
	gSystem->Exec(TString("rm -r ") + Folder + Form("bin_%i/dataset",bin));
	gSystem->Exec(TString("rm -r ") + Folder + Form("bin_%i/Exploration",bin));

	Folder = Folder_0;
}
