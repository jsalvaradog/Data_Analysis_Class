TCut Mbins[94];
TCut cut_bin, cut_bin_2g;
TRandom3 randGen(0);
    
double t_G, xB_G, Q2_G;
double alpha=0.007297;
double M=0.938;
double s=4;
double gamm, y, J, K, eps, eps2, tmin, tmax, xi;
double BDT_Value;

TCut cut0 = TCut("bestCandidateFlag==1 &&\
    strip_Xbj <1 && strip_Xbj >0 && t_Ph <0 && strip_Q2 > 1.0 && \
    strip_W > 2 && strip_El_P > 1.0 && strip_Ph_P>2 && t_Ph>-1 && Phi_Ph<360 && \
    theta_gamma_e > 5 && abs(t_Ph/strip_Q2)<1 && mm2_eg > 0 && mm2_eg<3 && N_Ph<3");

    double Best_BDT(int bin)
{

  TFile *file = TFile::Open(TString(Form("Analysis/bin_%i/TMVACC.root", bin)));
  if (!file || file->IsZombie()) {
    std::cerr << "Error opening TMVACC.root" << std::endl;
    return 0.04;
  }

  TTree *tree = dynamic_cast<TTree*>(file->Get("dataset/TestTree"));
  if (!tree) {
    std::cerr << "Error: TestTree not found in TMVACC.root" << std::endl;
    file->Close();
    return 0.04;
  }

  TObjArray* branches = tree->GetListOfBranches();
  bool hasPhTopologies = branches->FindObject("Ph_Topologies") != nullptr;
  const char* bdtBranch = hasPhTopologies ? "Ph_Topologies" : "BDT";

  TH1F* hSignal = new TH1F("hSignal", "Signal BDT", 100, -1, 1);
  TH1F* hBackground = new TH1F("hBackground", "Background BDT", 100, -1, 1);

  tree->Project("hSignal", bdtBranch, "classID==0");
  tree->Project("hBackground", bdtBranch, "classID==1");
  double nsignal = hSignal->Integral();
  double nbackground = hBackground->Integral();
  
  const int nBins = 100;  
  float minCut = -0.4, maxCut = 0.4;
  float bestCut = minCut, maxSignificance = 0.0;

  for (int i = 0; i < nBins; ++i) {
    float cut = minCut + i * (maxCut - minCut) / nBins;
    double S = 0, B = 0;
    TH1F* hSignalCut = new TH1F("hSignalCut", "Signal BDT Cut", 100, -1, 1);
    TH1F* hBackgroundCut = new TH1F("hBackgroundCut", "Background BDT Cut", 100, -1, 1);
    tree->Project("hSignalCut", bdtBranch, Form("classID==0 && %s>%f", bdtBranch, cut));
    tree->Project("hBackgroundCut", bdtBranch, Form("classID==1 && %s>%f", bdtBranch, cut));

    S = hSignalCut->Integral()*1000/nsignal; //Scale to total events
    B = hBackgroundCut->Integral()*1000/nbackground; //Scale to total events

    double significance = (S + B > 0) ? S / sqrt(S + B) : 0;
    if (significance > maxSignificance) {
      maxSignificance = significance;
      bestCut = cut;
    }
    delete hSignalCut;
    delete hBackgroundCut;
  }

  std::cout << "Best BDT cut: " << bestCut << " with significance: " << maxSignificance << std::endl;
  file->Close();

  return bestCut;
}


struct Coeffs {
    double A, B, C;
};
Coeffs coeffs;

// compute coefficients A,B,C of P1P2(cos(phi))
Coeffs computeP1P2_coeffs(double Q2_G, double xB_G, double t_G) {
    // Step 1: eps, y, xi
    double eps  = 2.0 * xB_G * M / std::sqrt(Q2_G);
    double y    = std::sqrt(Q2_G) / (10.6 * eps);
    double eps2 = eps * eps;

    // Step 2: ratio and tmin/tmax
    double ratio = Q2_G / (2.0 * M * xB_G);
    double sqrt_term = std::sqrt(Q2_G + ratio*ratio);

    double tmin = -(Q2_G*M + (Q2_G/xB_G)*(ratio - sqrt_term))
                  /(M + ratio - sqrt_term);
    double tmax = -(Q2_G*M + (Q2_G/xB_G)*(ratio + sqrt_term))
                  /(M + ratio + sqrt_term);

    // Step 3: K
    double inside = (1. - y - y*y*eps2/4.)
                    * (4.*xB_G*(1.-xB_G) + eps2)
                    * (tmin - t_G) * (t_G - tmax);
    double K = (1.0/(2.0*Q2_G)) * std::sqrt(std::max(0.0, inside));

    // Step 4: kdotdelta in form a + b cos(phi)
    double a_k = (-Q2_G/(2.*y*(1.+eps2))) *
                 (1. + y*eps2/2. - (t_G/Q2_G)*(1.-xB_G*(2.-y) + y*eps2/2.));
    double b_k = (-Q2_G/(2.*y*(1.+eps2))) * (-2.*K);

    // Step 5: P1 = 1 + 2*kdotdelta/Q2
    double a_P1 = 1.0 + 2.0*a_k/Q2_G;
    double b_P1 = 2.0*b_k/Q2_G;

    // Step 6: P2 = (t - 2*kdotdelta)/Q2
    double a_P2 = (t_G - 2.0*a_k)/Q2_G;
    double b_P2 = -2.0*b_k/Q2_G;

    // Step 7: expand (a_P1 + b_P1 c)(a_P2 + b_P2 c)
    double A = a_P1*a_P2;
    double B = a_P1*b_P2 + b_P1*a_P2;
    double C = b_P1*b_P2;

    return {A,B,C};
}


void compute_kinematics()
{
gamm=2*M*xB_G/Q2_G;
eps = 2*xB_G*M/sqrt(Q2_G);
y=sqrt(Q2_G)/(10.6*eps);
eps2 = eps*eps;
xi = xB_G/(2.-xB_G);

double ratio = Q2_G/(2.*M*xB_G);
//Full formula
tmin = -1.0*(Q2_G*M + (Q2_G/xB_G)*(ratio - sqrt(Q2_G + pow(ratio,2))))/(M + ratio - sqrt(Q2_G + pow(ratio,2)));
tmax = -1.0*(Q2_G*M + (Q2_G/xB_G)*(ratio + sqrt(Q2_G + pow(ratio,2))))/(M + ratio + sqrt(Q2_G + pow(ratio,2)));
//SY documentation
J=(1. - y - y*eps2/2.)*(1 + t_G/Q2_G) - (1-xB_G)*(2 - y)*t_G/Q2_G;
//K=sqrt((-t_G/Q2_G)*(1.-xB_G)*(1. - y - y*y*eps2/4.)*(1. - tmin/t_G)*(sqrt(1+eps2) + (t_G-tmin)*(4.*xB_G*(1-xB_G) + eps2)/(4.*Q2_G*(1-xB_G))));
//Full formula
K=(1./(2.*Q2_G))*sqrt((1. - y - y*y*eps2/4.)*(4.*xB_G*(1-xB_G) + eps2)*(tmin-t_G)*(t_G-tmax));
//std::cout<<t_G<<" "<<tmin<<" "<<tmax<<" "<<K<<" "<<2.*(2.-y)*K/(1-y)<<std::endl;

coeffs = computeP1P2_coeffs(Q2_G, xB_G, t_G);
std::cout<<"P1P2 coeffs: "<<coeffs.A/coeffs.A<<" "<<coeffs.B/coeffs.A<<" "<<coeffs.C/coeffs.A<<std::endl;
}

double BraunFunc(double *x, double *par)
{
    double sum, diff;
    double P1, P2, P1P2, P1P2_2;
    /*
    //Belitsky
    //double kdotdelta = (-1./(2.*y*(1+eps2)))*(Q2_G*(1. - 2.*K*cos(x[0]*3.14159265/180.) + y*eps2/2.) - t_G*(1-xB_G*(2.-y) + y*eps2/2.)); //Belitsky
    double kdotdelta=(-Q2_G/(2.*y*(1+eps2)))*( 1. + y*eps2/2. - (t_G/Q2_G)*(1-xB_G*(2.-y) + y*eps2/2.) - 2.*K*cos(x[0]*3.14159265/180.)); //Belitsky rearranged
    P1 = 1 + 2.*kdotdelta/Q2_G; //From SY these
    P2 = (t_G-2.*kdotdelta)/Q2_G; //From SY these
    P1P2 = P1*P2;
    //std::cout<<P1P2<<" "<<coeffs.A + coeffs.B*cos(x[0]*3.14159265/180.) + coeffs.C*pow(cos(x[0]*3.14159265/180.),2)<<std::endl;
    */
   
    //double A=coeffs.A, B=coeffs.B, C=coeffs.C;
    double A=coeffs.A/coeffs.A, B=coeffs.B/coeffs.A, C=coeffs.C/coeffs.A;
    P1P2 = A + B*cos(x[0]*3.14159265/180.) + C*pow(cos(x[0]*3.14159265/180.),2);

    diff = P1P2*(par[0]*P1P2/Q2_G + par[1])*sin(x[0]*3.14159265/180.) + P1P2*par[2]*sin(2*x[0]*3.14159265/180.);
    sum = 1.0 + par[4]*cos(x[0]*3.14159265/180.) + par[5]*cos(2.*x[0]*3.14159265/180.);
    //sum = (par[3] + par[4]*P1P2 + par[5]*cos(x[0]*3.14159265/180.)) + P1P2*bhGraph->Eval(x[0])/(bhGraph->Eval(0.));

    return diff/sum;
}

TH1F* xcheck_hel(int hel, TChain* signal, TChain* pi01g, TChain* pi02g)
{

//bkg is for EventNumber<5000. The rest for the ratio computation

TH1F* h_signal = new TH1F("h_signal","h_signal",16,0,360);
signal->Project("h_signal","Phi_Ph", cut0 + TCut(Form("bestCandidateFlag==1 && Helicity==%i && _strip_Nuc_BDT>%f",hel,BDT_Value)) + cut_bin);
TH1F* h_bkg = new TH1F("h_bkg","h_bkg",16,0,360);
pi01g->Project("h_bkg","Phi_Ph", (cut0 + TCut(Form("bestCandidateFlag==1 && EventNumber>5000 && Helicity==%i && _strip_Nuc_BDT>%f",hel,BDT_Value)) + cut_bin)*TCut("10"));
TH1F* h_pi02g_meas = new TH1F("h_pi02g_meas","h_pi02g_meas",16,0,360);
pi02g->Project("h_pi02g_meas","Phi_Pi0", (TCut(Form("bestCandidateFlag==1 && EventNumber>5000 && Helicity==%i",hel)) + cut_bin_2g)*TCut("10"));

TH1F* h_pi01g = new TH1F("h_pi01g","h_pi01g",16,0,360);
pi01g->Project("h_pi01g","Phi_Ph", (cut0 + TCut(Form("bestCandidateFlag==1 && EventNumber<5000 && Helicity==%i && _strip_Nuc_BDT>%f",hel,BDT_Value)) + cut_bin)*TCut("10"));
TH1F* h_pi02g = new TH1F("h_pi02g","h_pi02g",16,0,360);
pi02g->Project("h_pi02g","Phi_Pi0", (TCut(Form("bestCandidateFlag==1 && EventNumber<5000 && Helicity==%i",hel)) + cut_bin_2g)*TCut("10"));

TH1F* data = new TH1F("data","data",16,0,360);
data->Add(h_signal, h_bkg, 1.0, 1.0);

TH1F* ratio_pi0 = new TH1F("ratio_pi0","ratio_pi0",16,0,360);
ratio_pi0->Divide(h_pi01g, h_pi02g,1.0,1.0);

TH1F* bkg_estimated = new TH1F("bkg_estimated","bkg_estimated",16,0,360);
bkg_estimated->Multiply(h_pi02g_meas, ratio_pi0,1.0,1.0);

TH1F* h_subtracted = new TH1F(Form("h_subtracted_%i", hel), Form("h_subtracted_%i", hel), 16,0,360);
h_subtracted->Add(data, bkg_estimated, 1.0, -1.0);

delete h_signal;
delete h_bkg;
delete h_pi02g_meas;
delete h_pi01g;
delete h_pi02g;
delete data;
delete ratio_pi0;
delete bkg_estimated;

return h_subtracted;
}

TH1* xcheck_bin(int bin)
{
TChain* signal = new TChain("pDVCS"); 
signal->Add(Form("Analysis/bin_%i/Tested_DVCS.root",bin));
//signal->Add(Form("Analysis/bin_%i/Tested_DVCS_2.root",bin));

TChain* pi01g = new TChain("pDVCS");
pi01g->Add(Form("Analysis/bin_%i/Tested_1gamma.root",bin));

TChain* pi02g = new TChain("eppi0");
pi02g->Add(Form("Analysis/bin_%i/sim_Quality_Data_eppi0_NP.root",bin));

TH1F* h_plus = xcheck_hel(1, signal, pi01g, pi02g);
TH1F* h_minus = xcheck_hel(-1, signal, pi01g, pi02g);

TH1* h_asymmetry;
h_asymmetry = h_plus->GetAsymmetry(h_minus);
h_asymmetry->SetTitle(Form("BSA in bin %i. Fit to A*sin(#phi); #phi (deg); Asymmetry",bin));

//Compute mean kinematics
TH1D h_Q2("h_Q2", "Q2", 100, 0, 0);
TH1D h_Xbj("h_Xbj", "Xbj", 100, 0, 0);
TH1D h_t("h_t", "t", 100, 0, 0);

signal->Draw("strip_Q2>>h_Q2", cut_bin + TCut(Form("_strip_Nuc_BDT>%f",BDT_Value)), "goff");
signal->Draw("strip_Xbj>>h_Xbj", cut_bin + TCut(Form("_strip_Nuc_BDT>%f",BDT_Value)), "goff");
signal->Draw("t_Ph>>h_t", cut_bin + TCut(Form("_strip_Nuc_BDT>%f",BDT_Value)), "goff");

Q2_G=h_Q2.GetMean();
xB_G=h_Xbj.GetMean();
t_G=h_t.GetMean();
compute_kinematics();
std::cout<<"Bin "<<bin<<" Mean kinematics aft: Q2="<<Q2_G<<" xB="<<xB_G<<" t="<<t_G<<" -t/Q2="<<-1.0*t_G/Q2_G<<std::endl;
// end of mean kinematics computation

delete h_plus;
delete h_minus;

delete signal;
delete pi01g;
delete pi02g;

return h_asymmetry;
}

TH1* bsa_gen(int bin)
{
TChain* signal = new TChain("pDVCS"); 
signal->Add(Form("Analysis/bin_%i/Tested_DVCS.root",bin));
//signal->Add(Form("Analysis/bin_%i/Tested_DVCS_2.root",bin));

TH1F* h_plus = new TH1F("h_plus","h_plus",16,0,360);
signal->Project("h_plus","Phi_Ph", cut0 + TCut("bestCandidateFlag==1 && Helicity==1 && _strip_Nuc_BDT>-1.0") + cut_bin);
TH1F* h_minus = new TH1F("h_minus","h_minus",16,0,360);
signal->Project("h_minus","Phi_Ph", cut0 + TCut("bestCandidateFlag==1 && Helicity==-1 && _strip_Nuc_BDT>-1.0") + cut_bin);

TH1* h_asymmetry;
h_asymmetry = h_plus->GetAsymmetry(h_minus);
h_asymmetry->SetTitle("Generated BSA; #phi (deg); Asymmetry");

//Compute mean kinematics
TH1D h_Q2("h_Q2", "Q2", 100, 0, 0);
TH1D h_Xbj("h_Xbj", "Xbj", 100, 0, 0);
TH1D h_t("h_t", "t", 100, 0, 0);

signal->Draw("strip_Q2>>h_Q2", cut_bin, "goff");
signal->Draw("strip_Xbj>>h_Xbj", cut_bin, "goff");
signal->Draw("t_Ph>>h_t", cut_bin, "goff");

Q2_G=h_Q2.GetMean();
xB_G=h_Xbj.GetMean();
t_G=h_t.GetMean();
compute_kinematics();
std::cout<<"Bin "<<bin<<" Mean kinematics aft: Q2="<<Q2_G<<" xB="<<xB_G<<" t="<<t_G<<" -t/Q2="<<-1.0*t_G/Q2_G<<std::endl;
// end of mean kinematics computation


delete h_plus;
delete h_minus;
delete signal;

return h_asymmetry;
}



void mc_xcheck()
{
  gStyle->SetOptStat(0);


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


std::vector<double> bin, difference;
std::vector<double> difference_err;
  std::vector<int> skip_bins = {8,15,16,21,22,23,24,25,26,41,48,49,53,67,68,72,73,80,86,87,92}; 
  double amp=0.35;
  double amp_recon, amp_gen;
  double amp_recon_err, amp_gen_err;
  TGraphErrors* gr2 = new TGraphErrors();
  TGraphErrors* gr3 = new TGraphErrors();
  int ibin=1;

  for(int i=1; i<=94; i++)
  {
    BDT_Value = Best_BDT(i);
    if(i == 66)
        BDT_Value = -1;

    cut_bin = Mbins[i-1];
    TString String_cut = cut_bin.GetTitle();
    String_cut.ReplaceAll("t_Ph", "t_Pi0");
    cut_bin_2g = TCut(String_cut);
    const int Npars=6;

    double chi2, ndf, chi2ndf;
    double bestChi2Ndf;
    double bestParams[Npars];

    auto h_recon = xcheck_bin(i);
    //TF1* fit_func = new TF1("fit_func", "[0]*sin(TMath::DegToRad()*x)/(1 + [1]*cos(TMath::DegToRad()*x) + [2]*cos(TMath::DegToRad()*2*x))", 0, 360);
    // Fit reconstructed histogram
    TF1* fit_func;
    if(-1.0*t_G/Q2_G>0.0)
    {
      //fit_func = new TF1("fit_func", "[1]*sin(TMath::DegToRad()*x) + [0]*sin(TMath::DegToRad()*2*x)", 0, 360);
      //fit_func = new TF1("fit_func", "([1]*sin(TMath::DegToRad()*x) )/(1 + [0]*cos(TMath::DegToRad()*x))", 0, 360);
      fit_func = new TF1("fit_func", "([1]*sin(TMath::DegToRad()*x) + [2]*sin(TMath::DegToRad()*2*x))/(1 + [0]*cos(TMath::DegToRad()*x))", 0, 360);
      fit_func->SetParLimits(0, -0.5, 0.5); // Parameter 0 limits
      fit_func->SetParLimits(1, -0.5, 0.5); // Parameter 1 limits
      fit_func->SetParLimits(2, -0.5, 0.5); // Parameter 2 limits
      h_recon->Fit(fit_func, "QRNM");
      std::cout << "aft: p1 = " << fit_func->GetParameter(1) << " +- " << fit_func->GetParError(1) << ", p2 = " << fit_func->GetParameter(2) << " +- " << fit_func->GetParError(2) << std::endl;
      amp_recon=fit_func->GetParameter(1);
      amp_recon_err = fit_func->GetParError(1);
    }
    else
    {
    fit_func = new TF1("fit_func", BraunFunc,0,360,Npars);
    fit_func->FixParameter(0, 0.0);
    fit_func->FixParameter(3, 0.0);
    //fit_func->FixParameter(2, 0.0);
    fit_func->FixParameter(5, 0.0);
    fit_func->SetParLimits(1, 0., 1.);
    fit_func->SetParLimits(4, -1., 1.);
    //fit_func->SetParameter(1, 0.1); // Initial guess for amplitude
    //fit_func->SetParameter(4, 0.1); // Initial guess for amplitude
    //h_recon->Fit(fit_func, "QRN");
    bestChi2Ndf = 1e9;
      
    for (int trial = 0; trial < 1000; ++trial) 
          {
            fit_func->SetParameter(1, randGen.Uniform( 0.0, 0.5));
            fit_func->SetParameter(4, randGen.Uniform(-0.5, 0.5));
            //fit_func->SetParError(1, 0.0001*fit_func->GetParameter(1));
            //fit_func->SetParError(4, 0.0001*fit_func->GetParameter(4));
            h_recon->Fit(fit_func, "QRN");

            chi2 = fit_func->GetChisquare();
            ndf = fit_func->GetNDF();
            chi2ndf = (ndf > 0) ? std::abs(chi2 / ndf) - 1 : 1e9; //chi2/ndf closest to 1

            if (chi2ndf < bestChi2Ndf && fit_func->GetParameter(1)>0) {
                bestChi2Ndf = chi2ndf;
                for (int i = 0; i < Npars; ++i)
                    bestParams[i] = fit_func->GetParameter(i);
            }
          }
        for (int i = 0; i < Npars; ++i)
            fit_func->SetParameter(i, bestParams[i]);

        h_recon->Fit(fit_func, "QRN");
        std::cout << "aft: p1 = " << fit_func->GetParameter(1) << " +- " << fit_func->GetParError(1) << ", p2 = " << fit_func->GetParameter(2) << " +- " << fit_func->GetParError(2) << std::endl;
        amp_recon=(fit_func->GetParameter(1)*(coeffs.A - 0.5*coeffs.C) + 0.5*coeffs.B*fit_func->GetParameter(2))/coeffs.A;
        amp_recon_err = sqrt(pow(fit_func->GetParError(1)*(coeffs.A - 0.5*coeffs.C), 2) + pow(0.5*coeffs.B*fit_func->GetParError(2), 2))/coeffs.A;
    }


    auto h_gen = bsa_gen(i);
    //TF1* fit_func_gen = new TF1("fit_func_gen", "[0]*sin(TMath::DegToRad()*x)/(1 + [1]*cos(TMath::DegToRad()*x) + [2]*cos(TMath::DegToRad()*2*x))", 0, 360);
    // Fit generated histogram
    TF1* fit_func_gen;
    if(-1.0*t_G/Q2_G>0.0)
    {
      //fit_func_gen = new TF1("fit_func_gen", "[1]*sin(TMath::DegToRad()*x) + [0]*sin(TMath::DegToRad()*2*x)", 0, 360);
      //fit_func_gen = new TF1("fit_func_gen", "([1]*sin(TMath::DegToRad()*x) )/(1 + [0]*cos(TMath::DegToRad()*x))", 0, 360);
      fit_func_gen = new TF1("fit_func_gen", "([1]*sin(TMath::DegToRad()*x) + [2]*sin(TMath::DegToRad()*2*x))/(1 + [0]*cos(TMath::DegToRad()*x))", 0, 360);
      fit_func_gen->SetParLimits(0, -0.5, 0.5); // Parameter 0 limits
      fit_func_gen->SetParLimits(1, -0.5, 0.5); // Parameter 1 limits
      fit_func_gen->SetParLimits(2, -0.5, 0.5); // Parameter 2 limits
      h_gen->Fit(fit_func_gen, "QRNM");
      std::cout << "bef: p1 = " << fit_func_gen->GetParameter(1) << " +- " << fit_func_gen->GetParError(1) << ", p2 = " << fit_func_gen->GetParameter(2) << " +- " << fit_func_gen->GetParError(2) << std::endl;
      amp_gen=fit_func_gen->GetParameter(1);
      amp_gen_err = fit_func_gen->GetParError(1);
    }
    else
    {
    fit_func_gen = new TF1("fit_func_gen", BraunFunc,0,360,Npars);
    fit_func_gen->FixParameter(0, 0.0);
    fit_func_gen->FixParameter(3, 0.0);
    //fit_func_gen->FixParameter(2, 0.0);
    fit_func_gen->FixParameter(5, 0.0);
    fit_func_gen->SetParLimits(1, 0., 1.);
    fit_func_gen->SetParLimits(4, -1., 1.);
    //fit_func_gen->SetParameter(1, 0.1); // Initial guess for amplitude
    //fit_func_gen->SetParameter(4, 0.1); // Initial guess for amplitude
    //h_gen->Fit(fit_func_gen, "QRN");
    bestChi2Ndf = 1e9;

    for (int trial = 0; trial < 1000; ++trial) 
          {
            fit_func_gen->SetParameter(1, randGen.Uniform( 0.0, 0.5));
            fit_func_gen->SetParameter(4, randGen.Uniform(-0.5, 0.5));
            //fit_func_gen->SetParError(1, 0.0001*fit_func_gen->GetParameter(1));
            //fit_func_gen->SetParError(4, 0.0001*fit_func_gen->GetParameter(4));
            h_gen->Fit(fit_func_gen, "QRN");

            chi2 = fit_func_gen->GetChisquare();
            ndf = fit_func_gen->GetNDF();
            chi2ndf = (ndf > 0) ? std::abs(chi2 / ndf) - 1 : 1e9; //chi2/ndf closest to 1

            if (chi2ndf < bestChi2Ndf && fit_func_gen->GetParameter(1)>0) {
                bestChi2Ndf = chi2ndf;
                for (int i = 0; i < Npars; ++i)
                    bestParams[i] = fit_func_gen->GetParameter(i);
            }
          }
        for (int i = 0; i < Npars; ++i)
            fit_func_gen->SetParameter(i, bestParams[i]);

        h_gen->Fit(fit_func_gen, "QRN");
        std::cout << "bef: p1 = " << fit_func_gen->GetParameter(1) << " +- " << fit_func_gen->GetParError(1) << ", p2 = " << fit_func_gen->GetParameter(2) << " +- " << fit_func_gen->GetParError(2) << std::endl;
        amp_gen=(fit_func->GetParameter(1)*(coeffs.A - 0.5*coeffs.C) + 0.5*coeffs.B*fit_func->GetParameter(2))/coeffs.A;
        amp_gen_err = sqrt(pow(fit_func->GetParError(1)*(coeffs.A - 0.5*coeffs.C), 2) + pow(0.5*coeffs.B*fit_func->GetParError(2), 2))/coeffs.A;

        for(int j=1; j<=h_gen->GetNbinsX(); j++)
        {
          if(abs(h_recon->GetBinContent(j))<1 && abs(h_gen->GetBinContent(j))<1)
          {
        gr2->SetPoint(gr2->GetN(), ibin*1.0, abs(h_recon->GetBinContent(j) - h_gen->GetBinContent(j)));
        gr2->SetPointError(gr2->GetN()-1, 0, sqrt(h_recon->GetBinError(j)*h_recon->GetBinError(j) + h_gen->GetBinError(j)*h_gen->GetBinError(j)));
        gr3->SetPoint(gr3->GetN(), ibin*1.0, abs((h_recon->GetBinContent(j) - h_gen->GetBinContent(j))/h_gen->GetBinContent(j)));
        gr3->SetPointError(gr3->GetN()-1, 0, sqrt(h_recon->GetBinError(j)*h_recon->GetBinError(j) + h_gen->GetBinError(j)*h_gen->GetBinError(j))/h_gen->GetBinContent(j));
          }
        ibin++;
        }
      }


    TCanvas* c1 = new TCanvas("c1","c1",700,500);    
    h_recon->SetLineColor(kBlack);
    h_gen->SetLineColor(kRed);
    fit_func->SetLineColor(kBlack);
    fit_func_gen->SetLineColor(kRed);
    h_recon->Draw();
    fit_func->Draw("SAME");
    h_gen->Draw("SAME");
    fit_func_gen->Draw("SAME");

    // Get fit parameters
    double diff = amp_recon - amp_gen;

    std::cout << "Bin " << i << ": Before = " << amp_gen << ", After = " << amp_recon << ", Diff = " << diff << std::endl;

    // Create a TPaveText to display the values
    TPaveText* pt = new TPaveText(0.75, 0.75, 0.95, 0.95, "NDC");
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->AddText(Form("Before: %.3f", amp_recon));
    pt->AddText(Form("After: %.3f", amp_gen));
    pt->AddText(Form("Diff: %.3f", diff));
    pt->Draw();

    TLegend* legend = new TLegend();
    legend->AddEntry(h_recon, "After BDT", "l");
    legend->AddEntry(h_gen, "Before BDT", "l");
    legend->SetBorderSize(0);
    legend->Draw();

    c1->SaveAs(Form("mc_xcheck/bin_%i.pdf",i));
    if(std::find(skip_bins.begin(), skip_bins.end(), i) == skip_bins.end())
    {
    bin.push_back(i);
    difference.push_back(abs(diff));
    difference_err.push_back(sqrt(amp_recon_err*amp_recon_err + amp_gen_err*amp_gen_err));
    }
    std::cout<<"\n"<<endl;


    delete c1;
    delete h_recon;
    delete h_gen;
    delete fit_func;
    delete fit_func_gen;
    delete pt;
    delete legend;

  }

  TCanvas* c2 = new TCanvas("c2", "Difference vs Bin", 700, 500);
  TGraphErrors* gr = new TGraphErrors(bin.size());
  for (size_t i = 0; i < bin.size(); ++i) {
    gr->SetPoint(i, bin[i], difference[i]);
    gr->SetPointError(i, 0, difference_err[i]);
  }
  gr->SetTitle("Fitted amplitude difference per Bin;Bin;|A_{LU}^{Before} - A_{LU}^{After}|");
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(kBlue);
  gr->SetLineColor(kBlue);
  gr->SetMarkerSize();
  gr->SetFillColor(kBlue-2);
  gr->GetXaxis()->SetLimits(1, 95);
  gr->GetXaxis()->SetRangeUser(1, 95);
  gr->GetXaxis()->SetNdivisions(94/4, kTRUE);
  gr->GetYaxis()->SetTitleOffset(1.2);
  gr->Draw("AP");
  c2->SaveAs("mc_xcheck/difference_vs_bin.pdf");
  delete gr;
  delete c2;


  TCanvas* c3 = new TCanvas("c3", "Difference vs Bin", 700, 500);
  gr2->SetTitle("BSA Difference vs Bin;Bin;|A_{LU}^{Before} - A_{LU}^{After}|");
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerColor(kBlack);
  gr2->SetMarkerSize(1);
  gr2->Draw("AP");
  c3->SaveAs("mc_xcheck/BSA_difference_vs_bin.pdf");
  delete gr2;
  delete c3;

  TCanvas* c4 = new TCanvas("c4", "Difference vs Bin", 700, 500);
  gr3->SetTitle(";Bin;|A_{LU}^{Before} - A_{LU}^{After}|/A_{LU}^{Before}");
  gr3->SetMarkerStyle(20);
  gr3->SetMarkerColor(kBlack);
  gr3->SetMarkerSize(1);
  gr3->Draw("AP");
  c4->SaveAs("mc_xcheck/BSA_rel_difference_vs_bin.pdf");
  delete gr3;
  delete c4;

}