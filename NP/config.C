void BDT::config()
{
    Nbins=94;

    //Working directory
    dir="/work/clas12/jsalvg/pass2_RGA-Analysis/inb/NP_BSA/";
    //External BSA from analysis note -> To compare with a previous analysis
    extBSA="/work/clas12/jsalvg/pass2_RGA-Analysis/Maxime_BSA/"; 
    //External xsec from analysis note -> To compare with a previous analysis
    extXSEC="/work/clas12/jsalvg/pass2_RGA-Analysis/inb/NP_BSA/Theory_xsec/";
    //Folder to store the results
    Folder="Analysis/";
    gSystem->Exec(TString("mkdir -p ") + Folder);

    //Compute Q2, t and xB on each phi bin ?
    means_most=false;
    means_maxi=false;
    means_fit=false;

    //To generate the contamination files.
    //Only one of these can be set to true.
    //Thus, you need to run the script 3 times before being able to get any physics results
    generate=false;	 //Generate pi0 decays
    recast=false;   	 //Recombine 1-gamma pi0 events into files for each bin
    add_BDT_Max=false;  //Add BDT variable to the contamination files.

    //Estimate contamination from method 1 ? It is not needed to be computed everytime
    generate_most=false;
    generate_fit=true;

    //Get Excl tagged from the P detected case
    tag=false;

    //Compute cross-section?
    xsection=true;

    //Data samples for training and experimental data
    DVCS="/volatile/clas12/jsalvg/NP_SIDIS_BSA_inb/Analysis/Tested_DVCS.root";
    Pi0 ="/volatile/clas12/jsalvg/NP_SIDIS_BSA_inb/Analysis/Tested_Pi0.root"; //From excl-pi0
    //Pi0 ="/lustre24/expphy/volatile/clas12/jsalvg/simulation/clasdis/inb/1gamma/Quality_Pi_as_DVCS_NP.root"; //from sidis
    SIDIS = "/volatile/clas12/jsalvg/NP_SIDIS_BSA_inb/Analysis/Tsidis.root"; //from sidis
    Data_name="Tested1_Quality_Data.root";
    Data="/volatile/clas12/jsalvg/NP_SIDIS_BSA_inb/Analysis/" + Data_name; //For technical reasons I needed to split this variable in the NP case
    TData="Tested_Quality_Data.root";
    TDVCS="Tested_DVCS.root";
    TPi0="Tested_Pi0.root";

    //If you train with exp data. You might need a dvcs_MC sample eventually
    DVCS_MC=DVCS; //"/work/clas12/jsalvg/RGA-Simulation/pass2_inb/pDVCS_no_rad/Quality_DVCS_NP_Train.root";
    TDVCS_MC="Tested_DVCS_MC.root";

    //For eta Background estimation
    epeta = "/work/clas12/jsalvg/Data/eta/pass2_RGA/inb/Quality_Data_epeta_NP.root";	
    sim_eta_as_dvcs = "/volatile/clas12/jsalvg/NP_SIDIS_BSA_inb/Analysis/Tested_1gamma_eta.root";
    sim_epeta="/work/clas12/jsalvg/RGA-Simulation/inb/eta/NP/Quality_Sim_epeta_NP.root";

    //For Pi0 Background subtraction
    //eppi0_name = "Quality_Data_eppi0_NP.root";	
    //eppi0 = "/work/clas12/jsalvg/Data/DVMP/pass2_RGA/inb/NP/" + eppi0_name;	
    eppi0_name = "Quality3_Data_eppi0_NP.root";	
    eppi0 = "../" + eppi0_name;	
    maps_path = "../../maps/";
    //From excl-pi0
    sim_eppi0="/lustre24/expphy/volatile/clas12/jsalvg/simulation/aaogen/NP/inb/bkg_sub/2gamma/Quality_Sim_eppi0_NP.root";
    sim_eppi0_1="/lustre24/expphy/volatile/clas12/jsalvg/simulation/aaogen/NP/inb/bkg_sub/2gamma/Quality_Sim_eppi0_NP.root";
    sim_pi_as_dvcs = "/volatile/clas12/jsalvg/NP_SIDIS_BSA_inb/Analysis/Tested_1gamma.root";
    sim_pi_as_dvcs_1 = "/volatile/clas12/jsalvg/NP_SIDIS_BSA_inb/Analysis/Tested_1gamma_1.root";
    //From sidis
    //sim_eppi0="/lustre24/expphy/volatile/clas12/jsalvg/simulation/clasdis/inb/2gamma/Quality_Sim_eppi0_NP.root";
    //sim_eppi0_1="/lustre24/expphy/volatile/clas12/jsalvg/simulation/clasdis/inb/2gamma/Quality_Sim_eppi0_NP.root";
    //sim_pi_as_dvcs = "/lustre24/expphy/volatile/clas12/jsalvg/simulation/clasdis/inb/1gamma/Quality_Pi_as_DVCS_NP.root";
    //sim_pi_as_dvcs_1 = "/lustre24/expphy/volatile/clas12/jsalvg/simulation/clasdis/inb/1gamma/Quality_Pi_as_DVCS_NP.root";

    //Acc and BM corrections. Need a dvcs sample with RC effects. 
    //RC_can be used if it has enough statistics in all bins.
    BM_Sim="/volatile/clas12/jsalvg/NP_SIDIS_BSA_inb/Analysis/Tested_BM_Sim.root";
    //BM_Sim="/lustre24/expphy/volatile/clas12/jsalvg/genepi_DVCS/Quality_DVCS_Train_NP.root";
    TBM_Sim="Tested_BM_Sim.root";
    //The MC version of the BM sample
    MC_BM_Sim="/volatile/clas12/jsalvg/simulation/dvcsgen/inb/withRC/MCgen/Quality_MC_DVCS_NP.root";


    //Need a dvcs sample with RC effects
    RC_Sim=BM_Sim; //"/volatile/clas12/jsalvg/simulation/dvcsgen/inb/withRC/Quality_BM_DVCS_NP.root"; 
    TRC_Sim="Tested_RC_Sim.root";
    //The MC version of the RC sample
    MC_RC_Sim="/volatile/clas12/jsalvg/simulation/dvcsgen/inb/withRC/MCgen/Quality_MC_DVCS.root"; 
	
    
    //Direct output from dvcsgen to compute the RC correction factor. It is the same for the proton and no-proton cases
    MC_DVCS_RC="/work/clas12/jsalvg/RGA-Simulation/dvcsgen_DVCS_gen.root";
    MC_DVCS_RC_BH="/work/clas12/jsalvg/RGA-Simulation/dvcsgen_BH_gen.root";

    //Directory to temporaly store the contamination files from method 2 
    //(Only makes sence if I am generating the contamination files)
    Maxime_bkg = "/lustre24/expphy/volatile/clas12/jsalvg/DVCS_analysis/inb/NP_BSA/";

    //Used in xsec analysis.
    cut_kin = TCut("strip_El_P>1.8 && strip_Ph_P<8.5 && strip_Ph_P>2 && strip_Q2>1.0 && strip_W>2 && Phi_Ph<360 && t_Ph>-1.0");
    cut_sel = TCut("abs(t_Ph/strip_Q2)<1 && theta_gamma_e>5");

    //Basic selection/exclusivity cuts
    //Not the same as in xsec because I can keep strip_Ph_P>8.5 and strip_El_P<2 for BSA
    cut="bestCandidateFlag==1 &&\
    strip_Xbj <1 && strip_Xbj >0 && t_Ph <0 && strip_Q2 > 1.0 && \
    strip_W > 2 && strip_El_P > 1.0 && strip_Ph_P>2 && t_Ph>-1 && Phi_Ph<360 && \
    theta_gamma_e > 5 && abs(t_Ph/strip_Q2)<1 && mm2_eg > 0 && mm2_eg<3 && N_Ph<3";

    cut_ref="bestCandidateFlag==1 && _strip_Nuc_BDT_SIDIS>0.1 && strip_El_P>2 && strip_Ph_P<8.5 ";
    //cut_ref="bestCandidateFlag==1 && t_Ph>-1 && ((strip_Ph_Theta<5 &&strip_Nuc_P<0.8) || strip_Ph_Theta>5) ";
    //cut_ref=" delta_t>-0.1 && t_Ph>-1";// && t_Ph<-0.17";

    //No systematics due to cuts in the no-proton case
    //---

    //Cut to estimate systematic error due pid selection    
    cut_pid="strip_El_vz > -8 && strip_El_vz<5 && \
    strip_Ph_beta>0.9 && strip_Ph_beta<1.1 && \
    (strip_El_P<4.5 || (strip_El_P>4.5 && strip_El_ECin_energy/strip_El_P > 0.2 - strip_El_PCAL_energy/strip_El_P))";
   
    //Training variables
    Vars.push_back(TString("abs(mm2_eg-0.88)"));
    Vars.push_back(TString("mm2_e"));
    Vars.push_back(TString("t_Ph"));

    //Beam polarization
    Bpol=0.8592;
    Lumi=36.45*1e6; //40.971576; //40.09*1e6 ; fb-1 in nb-1
    torus="inb"; //magnetic field setting
    itorus=-1;
    //BDT cut
    BDT_value=0.08;
    //BDT cut for systematic error
    BDT_value_sys=0.1;

    beam->SetXYZT(0.0, 0.0, 10.6, 10.6);
    target->SetXYZT(0.0, 0.0, 0.0, 0.938);

    //|t|>|tmin| cut. It is good to have it coded
    //(t_Ph<-(strip_Q2*0.938 + (strip_Q2/strip_Xbj)*( (strip_Q2/(2*0.938*strip_Xbj)) - sqrt(strip_Q2 + pow((strip_Q2/(2*0.938*strip_Xbj)),2))))/(0.938 + (strip_Q2/(2*0.938*strip_Xbj)) - sqrt(strip_Q2 + pow((strip_Q2/(2*0.938*strip_Xbj)),2))))

    //(t_Ph<-(strip_Q2*0.938 + (strip_Q2/strip_Xbj)*( (strip_Q2/(2*0.938*strip_Xbj)) + sqrt(strip_Q2 + pow((strip_Q2/(2*0.938*strip_Xbj)),2))))/(0.938 + (strip_Q2/(2*0.938*strip_Xbj)) + sqrt(strip_Q2 + pow((strip_Q2/(2*0.938*strip_Xbj)),2))))


Mbins[0]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[1]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[2]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[3]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[4]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[5]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[6]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");

Mbins[7]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[8]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[9]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[10]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[11]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[12]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[13]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");

Mbins[14]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[15]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[16]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[17]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[18]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[19]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[20]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");

Mbins[21]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[22]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[23]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[24]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[25]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[26]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[27]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[28]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[29]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[30]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[31]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[32]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");

Mbins[33]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[34]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[35]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[36]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[37]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[38]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[39]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");

Mbins[40]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[41]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[42]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[43]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[44]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[45]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[46]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");

Mbins[47]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[48]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[49]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[50]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[51]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[52]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[53]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[54]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[55]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[56]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[57]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[58]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");

Mbins[59]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[60]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[61]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[62]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[63]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[64]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[65]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");

Mbins[66]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[67]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[68]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[69]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[70]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[71]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.450000   && strip_Xbj<0.6");
Mbins[72]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.450000   && strip_Xbj<0.6");

Mbins[73]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[74]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[75]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[76]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[77]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[78]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[79]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");

Mbins[80]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[81]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[82]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[83]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[84]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[85]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.450000   && strip_Xbj<0.6");
Mbins[86]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.450000   && strip_Xbj<0.6");

Mbins[87]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[88]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[89]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[90]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[91]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[92]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.450000   && strip_Xbj<0.6");
Mbins[93]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.450000   && strip_Xbj<0.6");
      
        bins ={{
{-1.000000, -0.400000, 1.000000, 1.600000, 0.0512, 0.120000},
{-0.400000, -0.250000, 1.000000, 1.600000, 0.0512, 0.120000},
{-0.250000, -0.170000, 1.000000, 1.600000, 0.0512, 0.120000},
{-0.170000, -0.120000, 1.000000, 1.600000, 0.0512, 0.120000},
{-0.120000, -0.070000, 1.000000, 1.600000, 0.0512, 0.120000},
{-0.070000, -0.040000, 1.000000, 1.600000, 0.0512, 0.120000},
{-0.040000, 0.000000, 1.000000, 1.600000, 0.0512, 0.120000},
{-1.000000, -0.400000, 1.000000, 1.600000, 0.120000, 0.170000},
{-0.400000, -0.250000, 1.000000, 1.600000, 0.120000, 0.170000},
{-0.250000, -0.170000, 1.000000, 1.600000, 0.120000, 0.170000},
{-0.170000, -0.120000, 1.000000, 1.600000, 0.120000, 0.170000},
{-0.120000, -0.070000, 1.000000, 1.600000, 0.120000, 0.170000},
{-0.070000, -0.040000, 1.000000, 1.600000, 0.120000, 0.170000},
{-0.040000, 0.000000, 1.000000, 1.600000, 0.120000, 0.170000},
{-1.000000, -0.400000, 1.000000, 1.600000, 0.170000, 0.270000},
{-0.400000, -0.250000, 1.000000, 1.600000, 0.170000, 0.270000},
{-0.250000, -0.170000, 1.000000, 1.600000, 0.170000, 0.270000},
{-0.170000, -0.120000, 1.000000, 1.600000, 0.170000, 0.270000},
{-0.120000, -0.070000, 1.000000, 1.600000, 0.170000, 0.270000},
{-0.070000, -0.040000, 1.000000, 1.600000, 0.170000, 0.270000},
{-0.040000, 0.000000, 1.000000, 1.600000, 0.170000, 0.270000},
{-1.000000, -0.400000, 1.000000, 1.600000, 0.270000, 0.450000},
{-0.400000, -0.250000, 1.000000, 1.600000, 0.270000, 0.450000},
{-0.250000, -0.170000, 1.000000, 1.600000, 0.270000, 0.450000},
{-0.170000, -0.120000, 1.000000, 1.600000, 0.270000, 0.450000},
{-0.120000, -0.070000, 1.000000, 1.600000, 0.270000, 0.450000},
{-1.000000, -0.400000, 1.600000, 2.400000, 0.0512, 0.120000},
{-0.400000, -0.250000, 1.600000, 2.400000, 0.0512, 0.120000},
{-0.250000, -0.170000, 1.600000, 2.400000, 0.0512, 0.120000},
{-0.170000, -0.120000, 1.600000, 2.400000, 0.0512, 0.120000},
{-0.120000, -0.070000, 1.600000, 2.400000, 0.0512, 0.120000},
{-0.070000, -0.040000, 1.600000, 2.400000, 0.0512, 0.120000},
{-0.040000, 0.000000, 1.600000, 2.400000, 0.0512, 0.120000},
{-1.000000, -0.400000, 1.600000, 2.400000, 0.120000, 0.170000},
{-0.400000, -0.250000, 1.600000, 2.400000, 0.120000, 0.170000},
{-0.250000, -0.170000, 1.600000, 2.400000, 0.120000, 0.170000},
{-0.170000, -0.120000, 1.600000, 2.400000, 0.120000, 0.170000},
{-0.120000, -0.070000, 1.600000, 2.400000, 0.120000, 0.170000},
{-0.070000, -0.040000, 1.600000, 2.400000, 0.120000, 0.170000},
{-0.040000, 0.000000, 1.600000, 2.400000, 0.120000, 0.170000},
{-1.000000, -0.400000, 1.600000, 2.400000, 0.170000, 0.270000},
{-0.400000, -0.250000, 1.600000, 2.400000, 0.170000, 0.270000},
{-0.250000, -0.170000, 1.600000, 2.400000, 0.170000, 0.270000},
{-0.170000, -0.120000, 1.600000, 2.400000, 0.170000, 0.270000},
{-0.120000, -0.070000, 1.600000, 2.400000, 0.170000, 0.270000},
{-0.070000, -0.040000, 1.600000, 2.400000, 0.170000, 0.270000},
{-0.040000, 0.000000, 1.600000, 2.400000, 0.170000, 0.270000},
{-1.000000, -0.400000, 1.600000, 2.400000, 0.270000, 0.450000},
{-0.400000, -0.250000, 1.600000, 2.400000, 0.270000, 0.450000},
{-0.250000, -0.170000, 1.600000, 2.400000, 0.270000, 0.450000},
{-0.170000, -0.120000, 1.600000, 2.400000, 0.270000, 0.450000},
{-0.120000, -0.070000, 1.600000, 2.400000, 0.270000, 0.450000},
{-1.000000, -0.400000, 2.400000, 3.250000, 0.120000, 0.170000},
{-0.400000, -0.250000, 2.400000, 3.250000, 0.120000, 0.170000},
{-0.250000, -0.170000, 2.400000, 3.250000, 0.120000, 0.170000},
{-0.170000, -0.120000, 2.400000, 3.250000, 0.120000, 0.170000},
{-0.120000, -0.070000, 2.400000, 3.250000, 0.120000, 0.170000},
{-0.070000, -0.040000, 2.400000, 3.250000, 0.120000, 0.170000},
{-0.040000, 0.000000, 2.400000, 3.250000, 0.120000, 0.170000},
{-1.000000, -0.400000, 2.400000, 3.250000, 0.170000, 0.270000},
{-0.400000, -0.250000, 2.400000, 3.250000, 0.170000, 0.270000},
{-0.250000, -0.170000, 2.400000, 3.250000, 0.170000, 0.270000},
{-0.170000, -0.120000, 2.400000, 3.250000, 0.170000, 0.270000},
{-0.120000, -0.070000, 2.400000, 3.250000, 0.170000, 0.270000},
{-0.070000, -0.040000, 2.400000, 3.250000, 0.170000, 0.270000},
{-0.040000, 0.000000, 2.400000, 3.250000, 0.170000, 0.270000},
{-1.000000, -0.400000, 2.400000, 3.250000, 0.270000, 0.450000},
{-0.400000, -0.250000, 2.400000, 3.250000, 0.270000, 0.450000},
{-0.250000, -0.170000, 2.400000, 3.250000, 0.270000, 0.450000},
{-0.170000, -0.120000, 2.400000, 3.250000, 0.270000, 0.450000},
{-0.120000, -0.070000, 2.400000, 3.250000, 0.270000, 0.450000},
{-1.000000, -0.400000, 2.400000, 3.250000, 0.450000, 0.600000},
{-0.400000, -0.250000, 2.400000, 3.250000, 0.450000, 0.600000},
{-1.000000, -0.400000, 3.250000, 5.000000, 0.170000, 0.270000},
{-0.400000, -0.250000, 3.250000, 5.000000, 0.170000, 0.270000},
{-0.250000, -0.170000, 3.250000, 5.000000, 0.170000, 0.270000},
{-0.170000, -0.120000, 3.250000, 5.000000, 0.170000, 0.270000},
{-0.120000, -0.070000, 3.250000, 5.000000, 0.170000, 0.270000},
{-0.070000, -0.040000, 3.250000, 5.000000, 0.170000, 0.270000},
{-0.040000, 0.000000, 3.250000, 5.000000, 0.170000, 0.270000},
{-1.000000, -0.400000, 3.250000, 5.000000, 0.270000, 0.450000},
{-0.400000, -0.250000, 3.250000, 5.000000, 0.270000, 0.450000},
{-0.250000, -0.170000, 3.250000, 5.000000, 0.270000, 0.450000},
{-0.170000, -0.120000, 3.250000, 5.000000, 0.270000, 0.450000},
{-0.120000, -0.070000, 3.250000, 5.000000, 0.270000, 0.450000},
{-1.000000, -0.400000, 3.250000, 5.000000, 0.450000, 0.600000},
{-0.400000, -0.250000, 3.250000, 5.000000, 0.450000, 0.600000},
{-1.000000, -0.400000, 5.000000, 9.0000000, 0.270000, 0.450000},
{-0.400000, -0.250000, 5.000000, 9.0000000, 0.270000, 0.450000},
{-0.250000, -0.170000, 5.000000, 9.0000000, 0.270000, 0.450000},
{-0.170000, -0.120000, 5.000000, 9.0000000, 0.270000, 0.450000},
{-0.120000, -0.070000, 5.000000, 9.0000000, 0.270000, 0.450000},
{-1.000000, -0.400000, 5.000000, 9.0000000, 0.450000, 0.600000},
{-0.400000, -0.250000, 5.000000, 9.0000000, 0.450000, 0.600000}
          }};  


      Nphibins.fill(16);  

  std::cout<<"Configuration loaded !"<<endl;		      
		      
}

