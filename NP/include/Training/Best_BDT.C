#include <vector>

double BDT::Best_BDT(int bin=0)
{
  TString bin_dir = (bin==0) ? TString("") : Form("bin_%i/", bin);
  TFile *file = TFile::Open(Folder + bin_dir + TString("TMVACC.root"));
  if (!file || file->IsZombie()) {
    std::cerr << "Error opening TMVACC.root" << std::endl;
    return BDT_value;
  }

  TTree *tree = dynamic_cast<TTree*>(file->Get("dataset/TestTree"));
  if (!tree) {
    std::cerr << "Error: TestTree not found in TMVACC.root" << std::endl;
    file->Close();
    return BDT_value;
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


double BDT::get_bdt_event(double strip_Xbj, double strip_Q2, double t_Ph)
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

