TCut Mbins[259];
TCut cut_bin;
std::vector<double> bdts;

TCut cut0 = "bestCandidateFlag==1 &&\
    strip_Xbj <1 && strip_Xbj >0 && t_Ph <0 && strip_Q2 > 1.0 && \
    strip_W > 2 && strip_El_P > 1.0 && strip_Ph_P>2 && t_Ph>-1 && Phi_Ph<360 && \
    theta_gamma_e > 5 && abs(t_Ph/strip_Q2)<1 && mm2_eg > 0 && mm2_eg<3 && N_Ph<3";

TChain* signal_tree = new TChain("pDVCS"); 

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


double get_bdt_event(double strip_Xbj, double strip_Q2, double t_Ph)
{
  for (int i = 0; i < 259; ++i)
  {
    // Parse the cut string for this bin
    TString cutStr = Mbins[i].GetTitle();

    // Extract ranges from the cut string
    double t_min, t_max, Q2_min, Q2_max, xbj_min, xbj_max;
    int found = sscanf(cutStr.Data(),
      "bestCandidateFlag==1 && t_Ph>%lf && t_Ph<%lf && strip_Q2>%lf && strip_Q2<%lf && strip_Xbj>%lf   && strip_Xbj<%lf",
      &t_min, &t_max, &Q2_min, &Q2_max, &xbj_min, &xbj_max);

    if (found == 6)
    {
      if (t_Ph > t_min && t_Ph < t_max &&
        strip_Q2 > Q2_min && strip_Q2 < Q2_max &&
        strip_Xbj > xbj_min && strip_Xbj < xbj_max)
      {
        return bdts.at(i);
      }
    }
  }

  return -1.0; // Not found
}


std::vector<double> xcheck_bin(int bin)
{
TCut cut_bin = Mbins[bin-1];

TString cut_str = cut_bin.GetTitle();
cut_str.ReplaceAll("strip_Q2", "strip_Q2_MC");
cut_str.ReplaceAll("strip_Xbj", "strip_Xbj_MC");
cut_str.ReplaceAll("t_Ph", "t_Ph_MC");
TCut cut_bin_gen = TCut(cut_str);

TH1F* h_diag = new TH1F("h_diag","h_diag",16,0,360);
TH1F* h_rec_i = new TH1F("h_rec_i","h_rec_i",16,0,360);
TH1F* h_gen_i = new TH1F("h_gen_i","h_gen_i",16,0,360);

signal_tree->Draw("Phi_Ph>>h_diag", cut0 + cut_bin + cut_bin_gen + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"), "goff");
signal_tree->Draw("Phi_Ph>>h_rec_i", cut0 + cut_bin + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"), "goff");
signal_tree->Draw("Phi_Ph>>h_gen_i", cut0 + cut_bin_gen + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"), "goff");

//Save bin purity and stability
std::vector<double> fraction = {h_diag->Integral()*1.0 / h_rec_i->Integral(), h_diag->Integral()*1.0 / h_gen_i->Integral()};
delete h_diag;
delete h_rec_i;
delete h_gen_i;
return fraction;
}

std::vector<double> RMS_bin(int bin)
{
TCut cut_bin = Mbins[bin-1];

TString cut_str = cut_bin.GetTitle();
cut_str.ReplaceAll("strip_Q2", "strip_Q2_MC");
cut_str.ReplaceAll("strip_Xbj", "strip_Xbj_MC");
cut_str.ReplaceAll("t_Ph", "t_Ph_MC");
TCut cut_bin_gen = TCut(cut_str);

TPRegexp re_t("t_Ph>([-+]?[0-9]*\\.?[0-9]+).*t_Ph<([-+]?[0-9]*\\.?[0-9]+)");
TPRegexp re_Q2("strip_Q2>([-+]?[0-9]*\\.?[0-9]+).*strip_Q2<([-+]?[0-9]*\\.?[0-9]+)");
TPRegexp re_xB("strip_Xbj>([-+]?[0-9]*\\.?[0-9]+).*strip_Xbj<([-+]?[0-9]*\\.?[0-9]+)");

auto m = re_t.MatchS(cut_bin.GetTitle());
double t_min = ((TObjString*)m->At(1))->GetString().Atof();
double t_max = ((TObjString*)m->At(2))->GetString().Atof();

m = re_Q2.MatchS(cut_bin.GetTitle());
double Q2_min = ((TObjString*)m->At(1))->GetString().Atof();
double Q2_max = ((TObjString*)m->At(2))->GetString().Atof();

m = re_xB.MatchS(cut_bin.GetTitle());
double xB_min = ((TObjString*)m->At(1))->GetString().Atof();
double xB_max = ((TObjString*)m->At(2))->GetString().Atof();

std::cout<<"\nBin "<<bin<<": t_Ph in ["<<t_min<<","<<t_max<<"], strip_Q2 in ["<<Q2_min<<","<<Q2_max<<"], strip_Xbj in ["<<xB_min<<","<<xB_max<<"]"<<std::endl;
double bin_width_t = t_max - t_min;
double bin_width_Q2 = Q2_max - Q2_min;
double bin_width_xB = xB_max - xB_min;


TH1F* h_Q = new TH1F("h_Q","h_Q",100,0,0);
TH1F* h_x = new TH1F("h_x","h_x",100,0,0);
TH1F* h_t = new TH1F("h_t","h_t",100,0,0);

signal_tree->Draw("strip_Q2 - strip_Q2_MC>>h_Q", cut0 + cut_bin + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"), "goff");
signal_tree->Draw("strip_Xbj - strip_Xbj_MC>>h_x", cut0 + cut_bin + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"), "goff");
signal_tree->Draw("t_Ph - t_Ph_MC>>h_t", cut0 + cut_bin + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"), "goff");

double sigma_Q = h_Q->GetStdDev();
double sigma_x = h_x->GetStdDev();
double sigma_t = h_t->GetStdDev();

std::vector<double> fractions = {
    sigma_t / bin_width_t,
    sigma_Q / bin_width_Q2,
    sigma_x / bin_width_xB
};

TCanvas* cRMS = new TCanvas("cRMS", "RMS Resolutions", 1200, 300);
cRMS->Divide(3,1);
cRMS->cd(1);
h_t->SetTitle(Form("t Resolution Bin %d; t_Ph - t_Ph_MC; Counts", bin));
h_t->Draw();
cRMS->cd(2);
h_Q->SetTitle(Form("Q2 Resolution Bin %d; strip_Q2 - strip_Q2_MC; Counts", bin));
h_Q->Draw();
cRMS->cd(3);
h_x->SetTitle(Form("xB Resolution Bin %d; strip_Xbj - strip_Xbj_MC; Counts", bin));
h_x->Draw();
cRMS->Print(Form("BM_xcheck/RMS_Bin_%d.png", bin));

delete h_Q;
delete h_x;
delete h_t;
delete cRMS;
return fractions;
}

void BM_xcheck()
{
std::vector<double> bdts;
//signal_tree->Add("/volatile/clas12/jsalvg/xsec_NP_SIDIS_BSA_inb/Analysis/Tested_DVCS.root");
//gStyle->SetOptStat(0);
for(int i=1; i<=259; i++)
{
bdts.push_back(Best_BDT(i));
}

gSystem->Exec("mkdir -p BM_xcheck");

Mbins[0]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[1]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[2]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[3]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[4]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[5]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[6]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[7]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[8]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");

Mbins[9]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[10]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[11]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[12]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[13]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[14]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");

Mbins[15]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[16]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[17]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[18]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[19]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[20]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[21]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[22]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[23]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");

Mbins[24]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[25]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[26]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[27]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[28]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[29]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[30]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[31]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[32]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");

Mbins[33]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[34]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[35]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[36]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[37]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[38]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[39]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[40]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[41]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");

Mbins[42]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[43]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[44]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[45]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[46]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[47]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[48]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[49]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[50]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");

Mbins[51]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[52]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[53]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[54]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[55]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[56]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[57]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[58]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[59]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");

Mbins[60]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[61]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[62]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[63]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[64]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[65]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[66]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[67]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[68]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");

Mbins[69]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[70]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[71]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[72]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[73]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[74]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[75]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[76]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[77]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");

Mbins[78]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[79]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[80]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[81]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[82]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[83]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[84]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[85]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[86]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");

Mbins[87]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[88]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[89]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[90]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[91]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[92]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[93]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[94]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");

Mbins[95]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[96]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[97]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[98]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[99]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[100]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[101]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");

Mbins[102]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[103]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[104]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[105]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[106]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[107]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[108]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[109]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[110]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");

Mbins[111]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[112]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[113]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[114]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[115]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[116]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[117]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[118]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[119]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");

Mbins[120]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[121]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[122]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[123]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[124]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[125]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[126]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[127]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[128]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");

Mbins[129]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[130]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[131]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[132]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[133]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[134]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[135]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[136]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");

Mbins[137]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[138]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[139]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[140]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[141]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[142]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[143]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");

Mbins[144]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[145]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[146]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[147]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[148]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");

Mbins[149]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[150]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[151]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[152]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[153]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[154]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[155]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[156]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[157]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");

Mbins[158]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[159]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[160]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[161]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[162]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[163]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[164]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[165]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[166]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<-0.005000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");

Mbins[167]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[168]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[169]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[170]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[171]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[172]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[173]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[174]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");

Mbins[175]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[176]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[177]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[178]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[179]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[180]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[181]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");

Mbins[182]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[183]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[184]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[185]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[186]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[187]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[188]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[189]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");

Mbins[190]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[191]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[192]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[193]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[194]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[195]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[196]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[197]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");

Mbins[198]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[199]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[200]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[201]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[202]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[203]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[204]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[205]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");

Mbins[206]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[207]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[208]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[209]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[210]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[211]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[212]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");

Mbins[213]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[214]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[215]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[216]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[217]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");

Mbins[218]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[219]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[220]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[221]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.295000 && strip_Q2<4.326000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");

Mbins[222]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[223]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[224]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[225]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[226]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[227]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");
Mbins[228]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.204000   && strip_Xbj<0.268000");

Mbins[229]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[230]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[231]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[232]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[233]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[234]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[235]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");

Mbins[236]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[237]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[238]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[239]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[240]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");

Mbins[241]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[242]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[243]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[244]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>4.326000 && strip_Q2<5.761000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");

Mbins[245]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[246]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[247]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[248]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");
Mbins[249]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.268000   && strip_Xbj<0.357000");

Mbins[250]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[251]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[252]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[253]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");
Mbins[254]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.357000   && strip_Xbj<0.446000");

Mbins[255]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[256]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[257]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");
Mbins[258]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>5.761000 && strip_Q2<7.000000 && strip_Xbj>0.446000   && strip_Xbj<0.581000");


std::vector<int> skip_bins = {};//8,15,16,21,22,23,24,25,26,41,48,49,53,67,68,72,73,80,86,87,92}; 
TGraph* g_purity = new TGraph();
g_purity->SetTitle("Bin purity;Bin Number;n(rec_{i} | gen_{i}) / n(rec_{i})");
g_purity->SetMarkerStyle(20);
g_purity->SetMarkerSize(1.2);
g_purity->SetMarkerColor(kBlue+1);
g_purity->GetXaxis()->SetTitleSize(0.07);
g_purity->GetXaxis()->SetTitleOffset(0.6);
g_purity->GetYaxis()->SetTitleSize(0.07);
g_purity->GetYaxis()->SetTitleOffset(1.0);

TGraph* g_stability = new TGraph();
g_stability->SetTitle("Bin stability;Bin Number;n(rec_{i} | gen_{i}) / n(gen_{i})");
g_stability->SetMarkerStyle(20);
g_stability->SetMarkerSize(1.2);
g_stability->SetMarkerColor(kBlue+1);
g_stability->GetXaxis()->SetTitleSize(0.07);
g_stability->GetXaxis()->SetTitleOffset(0.6);
g_stability->GetYaxis()->SetTitleSize(0.07);
g_stability->GetYaxis()->SetTitleOffset(1.0);

TGraph* g_fraction_t = new TGraph();
g_fraction_t->SetTitle("Resolution:bin width ratio for t;Bin Number;#sigma(t_{rec} - t_{gen})/width");
g_fraction_t->SetMarkerStyle(20);
g_fraction_t->SetMarkerSize(1.2);
g_fraction_t->SetMarkerColor(kBlue+1);
g_fraction_t->GetXaxis()->SetTitleSize(0.07);
g_fraction_t->GetXaxis()->SetTitleOffset(0.6);
g_fraction_t->GetYaxis()->SetTitleSize(0.07);
g_fraction_t->GetYaxis()->SetTitleOffset(1.0);


TGraph* g_fraction_Q = new TGraph();
g_fraction_Q->SetTitle("Resolution:bin width ratio for Q^{2};Bin Number;#sigma(Q^{2}_{rec} - Q^{2}_{gen})/width");
g_fraction_Q->SetMarkerStyle(20);
g_fraction_Q->SetMarkerSize(1.2);
g_fraction_Q->SetMarkerColor(kBlue+1);
g_fraction_Q->GetXaxis()->SetTitleSize(0.07);
g_fraction_Q->GetXaxis()->SetTitleOffset(0.6);
g_fraction_Q->GetYaxis()->SetTitleSize(0.07);
g_fraction_Q->GetYaxis()->SetTitleOffset(1.0);

TGraph* g_fraction_x = new TGraph();
g_fraction_x->SetTitle("Resolution:bin width ratio for x_{B};Bin Number;#sigma(x_{rec} - x_{gen})/width");
g_fraction_x->SetMarkerStyle(20);
g_fraction_x->SetMarkerSize(1.2);
g_fraction_x->SetMarkerColor(kBlue+1);
g_fraction_x->GetXaxis()->SetTitleSize(0.07);
g_fraction_x->GetXaxis()->SetTitleOffset(0.6);
g_fraction_x->GetYaxis()->SetTitleSize(0.07);
g_fraction_x->GetYaxis()->SetTitleOffset(1.0);

ofstream output_file("BM_xcheck/Summary.log");
for(int i=1; i<=259; i++) //LALALA
{ 
  if(std::find(skip_bins.begin(), skip_bins.end(), i) == skip_bins.end())
  {
  std::vector<double> fraction = xcheck_bin(i);
  std::vector<double> rms_fractions = RMS_bin(i);

  g_purity->SetPoint(g_purity->GetN(), i, fraction[0]);
  g_stability->SetPoint(g_stability->GetN(), i, fraction[1]);
  g_fraction_t->SetPoint(g_fraction_t->GetN(), i, rms_fractions[0]);
  g_fraction_Q->SetPoint(g_fraction_Q->GetN(), i, rms_fractions[1]);
  g_fraction_x->SetPoint(g_fraction_x->GetN(), i, rms_fractions[2]);
  std::cout << "Bin " << i << ": Purity = " << fraction[0] 
            << ", Stability = " << fraction[1] 
            << ", RMS_t/bin_width_t = " << rms_fractions[0]
            << ", RMS_Q2/bin_width_Q2 = " << rms_fractions[1]
            << ", RMS_x/bin_width_x = " << rms_fractions[2] << std::endl;

  output_file << "Bin " << i << ": Purity = " << fraction[0] 
              << ", Stability = " << fraction[1] 
              << ", RMS_t/bin_width_t = " << rms_fractions[0]
              << ", RMS_Q2/bin_width_Q2 = " << rms_fractions[1]
              << ", RMS_x/bin_width_x = " << rms_fractions[2] << std::endl;
}
}
output_file.close();
g_purity->SetMinimum(0);
g_stability->SetMinimum(0);
g_fraction_t->SetMinimum(0);
g_fraction_Q->SetMinimum(0);
g_fraction_x->SetMinimum(0);    
TCanvas* c1 = new TCanvas("c1","c1",1700,1000);
c1->Divide(3,2);

c1->cd(1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.01);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.1);
g_purity->Draw("AP");

c1->cd(2);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.01);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.1);
g_stability->Draw("AP");

c1->cd(4);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.01);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.1);
g_fraction_t->Draw("AP");

c1->cd(5);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.01);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.1);
g_fraction_Q->Draw("AP");

c1->cd(6);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.01);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.1);
g_fraction_x->Draw("AP");

c1->SaveAs("BM_xcheck.png");
}
