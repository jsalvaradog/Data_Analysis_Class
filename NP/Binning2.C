 #define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

TCut TheCut = TCut("bestCandidateFlag==1 && N_Ph<3 && t_Ph>-1");
TCut cut_NP=TCut("bestCandidateFlag==1 && mm2_eg>0 && N_Ph<3 && mm2_eg<3 && abs(t_Ph/strip_Q2)<1 && t_Ph>-1"); 

double BDT_cut_P = 0.0;
double BDT_cut_NP= 0.08;
double BDT_cut_SIDIS=0.1;
int NBins=259;

TCut Mbins[259];
TCut BDT_bin_cut;

std::vector<double> bdts;

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



double Best_BDT(int bin)
{

  TFile *file = TFile::Open(TString(Form("Analysis/bin_%i/TMVACC.root", bin)));
  if (!file || file->IsZombie()) {
    std::cerr << "Error opening TMVACC.root" << std::endl;
    return BDT_cut_NP;
  }

  TTree *tree = dynamic_cast<TTree*>(file->Get("dataset/TestTree"));
  if (!tree) {
    std::cerr << "Error: TestTree not found in TMVACC.root" << std::endl;
    file->Close();
    return BDT_cut_NP;
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


void apply_conf(TH1F*& hist)
{
  hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetTitleOffset(0.6);
  hist->GetYaxis()->SetTitleOffset(0.6);
  hist->GetXaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetXaxis()->SetNdivisions(8);
  hist->GetYaxis()->SetNdivisions(4);
}
 
void apply_conf2(TH2F*& hist)
{
  hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetTitleOffset(0.6);
  hist->GetYaxis()->SetTitleOffset(0.6);
  hist->GetXaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetXaxis()->SetNdivisions(8);
  hist->GetYaxis()->SetNdivisions(8);
  //hist->Setheta_minimum(0.1);
  hist->SetMaximum(1e5);
}
 
void printProgress(double percentage) {
  int val = (int) (percentage * 100);
  int lpad = (int) (percentage * PBWIDTH);
  int rpad = PBWIDTH - lpad;
  printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
  fflush(stdout);
}


std::vector<double> Binning_1D(TTree* pDVCS, string ivar, int Nbins) 
{
  std::vector<vector<double>> binning_edges;
  std::vector<double> bins;
  int counter=0;
  const UInt_t NBINS = Nbins;

  TString branch;
  double dist_min, dist_max;
  if(ivar=="t")
  {
    branch="t_Ph";
    dist_min=-1;
    dist_max=0;
  }
  else if(ivar=="Q")
  {
    branch="strip_Q2";
    dist_min=0;
    dist_max=13;
  }
  else if(ivar=="x")
  {
    branch="strip_Xbj";
    dist_min=0;
    dist_max=1;
  }
  else
    std::cout<<"1D binning Variable error"<<endl;

  //Configuration
  const UInt_t DATADIM = 1;
  double MinEdges[NBINS];
  double MaxEdges[NBINS];

  //Check if binning in t exist. If not, create it

  std::ifstream filet(Form("Binning_%s.dat",ivar.c_str()));
  if (filet) 
  {
    std::cout<<Form("Binning in %s found!",ivar.c_str())<<std::endl;
    double value1, value2;
    int k=0;
    while (filet >> value1 >> value2) 
      {
        MinEdges[k]=value1;
        MaxEdges[k]=value2;
        bins.push_back(value1);
        k++;      
      }
    bins.push_back(value2);
    filet.close();
  }
  else
  {
    std::cout<<Form("Creating binning in %s",ivar.c_str())<<std::endl;
    // -----------------------------------------------------------------------------------------------
    //Load data
    // -----------------------------------------------------------------------------------------------

    static std::vector<int>* flag;
    static std::vector<double>* var;
    static std::vector<double> var_vec;
    int entries=pDVCS->GetEntries();
    var_vec.clear();
    var_vec.reserve(entries);
    pDVCS->ResetBranchAddresses();
    pDVCS->SetBranchAddress(branch,&var);
    pDVCS->SetBranchAddress("bestCandidateFlag",&flag);
  
    for(int i=0; i<entries;i++)
      {
        printProgress(i*1.0/pDVCS->GetEntries());
        pDVCS->GetEntry(i);
	      for(int j=0; j<flag->size();j++)
	        {
            if(flag->at(j)==1)
    	        var_vec.push_back(var->at(j));
	        }   
      }
    // -----------------------------------------------------------------------------------------------
    //Construct binning 1D
    // -----------------------------------------------------------------------------------------------

    const UInt_t DATASZ = var_vec.size();
    std::cout<<var_vec.at(0)<<std::endl;
    TKDTreeBinning* kdBins = new TKDTreeBinning(DATASZ, DATADIM, var_vec, NBINS);
    const Double_t* binsMinEdges = kdBins->GetBinsMinEdges();
    const Double_t* binsMaxEdges = kdBins->GetBinsMaxEdges();

    // Convert to a simple double array and sort
    for (int i = 0; i < NBINS; i++) 
      {
        MinEdges[i] = binsMinEdges[i];  // Dereference each pointer
        MaxEdges[i] = binsMaxEdges[i];
      }

    std::sort(MinEdges, MinEdges + NBINS);
    std::sort(MaxEdges, MaxEdges + NBINS); 

    std::ofstream outFile(Form("Binning_%s.dat",ivar.c_str()));
    for (UInt_t i = 0; i < NBINS; ++i)
      {
        std::cout<<"\nBin boundaries: "<<i+1<<" "<<MinEdges[i]<<" "<<MaxEdges[i]<<endl;
        outFile<<MinEdges[i]<<" "<<MaxEdges[i]<<endl;
        bins.push_back(MinEdges[i]);
      }  
      bins.push_back(MaxEdges[NBINS-1]);
      outFile.close();
  }

  //plot
  TH1F *dist = new TH1F("dist", "dist", 100,dist_min,dist_max);
  pDVCS->Project("dist", branch, TheCut);
  
  dist->SetTitle(Form("%s distribution; %s (GeV^{2}); counts",ivar.c_str(),ivar.c_str()));
  apply_conf(dist);
  
  TCanvas* c1 = new TCanvas("c1", "TH2Poly from a kdTree",1000,700);
  //gPad->SetLogx();
  dist->Draw("hist");

  TLine* line[NBINS];
  for (UInt_t i = 0; i < NBINS; ++i)
  {
    line[i] = new TLine(MinEdges[i],0,MinEdges[i],dist->GetMaximum());
    line[i]->SetLineColor(kRed);
    //std::cout<< MinEdges[i] <<endl;
    line[i]->Draw("same");
  }
  c1->Print(Form("Bins_%s.pdf",ivar.c_str()));
  delete c1;
  delete dist;

  return bins;  
}

void Binning2() 
{

Mbins[0]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[1]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[2]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[3]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[4]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[5]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[6]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[7]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[8]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");

Mbins[9]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[10]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[11]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[12]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[13]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[14]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.000000 && strip_Q2<1.200000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");

Mbins[15]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[16]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[17]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[18]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[19]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[20]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[21]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[22]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[23]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");

Mbins[24]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[25]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[26]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[27]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[28]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[29]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[30]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[31]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[32]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");

Mbins[33]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[34]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[35]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[36]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[37]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[38]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[39]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[40]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[41]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");

Mbins[42]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[43]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[44]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[45]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[46]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[47]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[48]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[49]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[50]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.200000 && strip_Q2<1.456000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");

Mbins[51]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[52]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[53]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[54]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[55]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[56]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[57]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[58]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");
Mbins[59]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.062000   && strip_Xbj<0.090000");

Mbins[60]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[61]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[62]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[63]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[64]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[65]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[66]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[67]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");
Mbins[68]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");

Mbins[69]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[70]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[71]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[72]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[73]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[74]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[75]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[76]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[77]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");

Mbins[78]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[79]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[80]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[81]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[82]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[83]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[84]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[85]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[86]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.456000 && strip_Q2<1.912000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");

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
Mbins[110]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.090000   && strip_Xbj<0.118000");

Mbins[111]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[112]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[113]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[114]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[115]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[116]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[117]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[118]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");
Mbins[119]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");

Mbins[120]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[121]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[122]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[123]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[124]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[125]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[126]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[127]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[128]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.912000 && strip_Q2<2.510000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");

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
Mbins[157]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.118000   && strip_Xbj<0.155000");

Mbins[158]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.800000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[159]= TCut("bestCandidateFlag==1 && t_Ph>-0.800000 && t_Ph<-0.600000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[160]= TCut("bestCandidateFlag==1 && t_Ph>-0.600000 && t_Ph<-0.400000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[161]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[162]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.150000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[163]= TCut("bestCandidateFlag==1 && t_Ph>-0.150000 && t_Ph<-0.110000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[164]= TCut("bestCandidateFlag==1 && t_Ph>-0.110000 && t_Ph<-0.070000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[165]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");
Mbins[166]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>2.510000 && strip_Q2<3.295000 && strip_Xbj>0.155000   && strip_Xbj<0.204000");

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


for(int i=1; i<=259; i++)
{
  bdts.push_back(Best_BDT(i));
}

  gStyle->SetOptStat(0);
  TChain *pDVCS= new TChain("pDVCS");
  pDVCS->Add("Analysis/Merged_Data.root");
  
  
  // -----------------------------------------------------------------------------------------------
  //  Check data existence
  // -----------------------------------------------------------------------------------------------

  const int NBINSt=9;
  const int NBINSQ=8;
  const int NBINSx=9;

  std::vector<double> bins_t = Binning_1D(pDVCS, "t",NBINSt);
  std::vector<double> bins_Q = Binning_1D(pDVCS, "Q",NBINSQ);
  std::vector<double> bins_x = Binning_1D(pDVCS, "x",NBINSx);

  std::cout<<bins_t.size()-1<<" "<<bins_x.size()-1<<" "<<bins_Q.size()-1<<endl;

  // ---------------------------------------------------------------------------------------------
  // Create phase space plots
  // -----------------------------------------------------------------------------------------------

  for(int l=0; l<NBINSt; l++)
  {
  TLine* line_Q[NBINSQ];
  TLine* line_xQ[NBINSx];

  TH2F *Q2xB = new TH2F("Q2xB", "Q2xB", 100,0,0.65,100,0,8);
  pDVCS->Project("Q2xB", "strip_Q2:strip_Xbj", cut_NP + TCut(Form("abs(t_Ph/strip_Q2)<1 && N_Ph<3 && _strip_Nuc_BDT_SIDIS > %f", BDT_cut_SIDIS)) + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02") + TCut(Form("t_Ph>%f && t_Ph<%f",bins_t.at(l),bins_t.at(l+1))));
  Q2xB->SetTitle("; xB; Q^{2} (GeV^{2})");
  apply_conf2(Q2xB);

  std::cout<<Form("t_Ph>%f && t_Ph<%f",bins_t.at(l),bins_t.at(l+1))<<endl;
  TCanvas* c2 = new TCanvas("c2", "c2",1000,700);
  gPad->SetLogz();


  Q2xB->Draw("COLZ");
  TF1* fa1[4];
  TLatex *th_edge[2];
  gPad->SetLogz();
  double xmax;
  double Q2inter;
  double theta;

  theta=37*TMath::Pi()/180;
  xmax=(378.92 * sin(theta/2)*sin(theta/2))/(227.84 - 224.72*cos(theta));
  fa1[0] = new TF1("fa1","4*0.938*10.6*10.6*x*sin([0]/2)*sin([0]/2)/(0.938*x + 2*10.6*sin([0]/2)*sin([0]/2))",0,xmax);
  fa1[0]->SetParameter(0,theta);
  fa1[0]->SetLineColor(kBlack);
  fa1[0]->SetLineWidth(2);
  fa1[0]->Draw("same");

  Q2inter= fa1[0]->Eval(xmax);

  fa1[2] = new TF1("fa1","4*0.938*10.6*10.6*x*sin([0]/2)*sin([0]/2)/(0.938*x + 2*10.6*sin([0]/2)*sin([0]/2))",0,xmax);
  fa1[2]->SetParameter(0,theta);
  Q2inter= fa1[2]->Eval(xmax);
  
  //Lower theta curve
  double theta_0=7.5*TMath::Pi()/180;
  double xmax_0=(378.92 * sin(theta_0/2)*sin(theta_0/2))/(227.84 - 224.72*cos(theta_0));
  fa1[3] = new TF1("fa1","4*0.938*10.6*10.6*x*sin([0]/2)*sin([0]/2)/(0.938*x + 2*10.6*sin([0]/2)*sin([0]/2))",0,xmax_0);
  fa1[3]->SetParameter(0,theta_0);
  fa1[3]->SetLineColor(kBlack);
  fa1[3]->SetLineWidth(2);
  fa1[3]->Draw("same");
  double Q2inter_0= fa1[3]->Eval(xmax_0);

  fa1[1] = new TF1("fa1","(4-0.938*0.938)/(1/x -1)",xmax_0,xmax);
  fa1[1]->SetLineColor(kBlack);
  fa1[1]->SetLineWidth(2);
  fa1[1]->Draw("same");


  for (UInt_t i = 0; i < NBINSQ; ++i)
  {
    line_Q[i] = new TLine(fa1[0]->GetX(bins_Q.at(i)), bins_Q.at(i), (bins_Q.at(i)>Q2inter_0)?fa1[1]->GetX(bins_Q.at(i)):fa1[3]->GetX(bins_Q.at(i)),bins_Q.at(i));
    line_Q[i]->SetLineColor(kBlack);
    line_Q[i]->Draw("same");
  }
  for (UInt_t i = 0; i < NBINSx; ++i)
  {
    line_xQ[i] = new TLine(bins_x.at(i), max(fa1[1]->Eval(bins_x.at(i)), fa1[3]->Eval(bins_x.at(i))), bins_x.at(i),min(fa1[0]->Eval(bins_x.at(i)),8.0));
    line_xQ[i]->SetLineColor(kBlack);
    line_xQ[i]->Draw("same");
  }

  TText* text1[35];
  // Q2 in [1.000; 1.200] GeV^2
  text1[0] = new TText(0.070, 1.0,"1-9");
  text1[1] = new TText(0.095, 1.0,"10-15");

  // Q2 in [1.200; 1.456] GeV^2
  text1[2] = new TText(0.070 ,1.2,"16-24");
  text1[3] = new TText(0.095,1.2,"25-33");
  text1[4] = new TText(0.125,1.2,"34-42");
  text1[5] = new TText(0.170,1.2,"43-51");

  // Q2 in [1.456; 1.912] GeV^2
  text1[6] = new TText(0.070 ,1.456,"52-60");
  text1[7] = new TText(0.095 ,1.456,"61-69");
  text1[8] = new TText(0.125 ,1.456,"70-78");
  text1[9] = new TText(0.17, 1.456,"79-87");
  text1[10]= new TText(0.24, 1.456,"88-95");
  text1[11]= new TText(0.30, 1.456,"96-102");

  // Q2 in [1.912; 2.510] GeV^2
  text1[12] = new TText(0.095, 1.912,"103-111");
  text1[13] = new TText(0.125, 1.912,"112-120");
  text1[14] = new TText(0.170, 1.912,"121-129");
  text1[15] = new TText(0.240, 1.912,"130-137");
  text1[16] = new TText(0.300, 1.912,"138-144");
  text1[17] = new TText(0.400, 1.912,"145-149");

  // Q2 in [2.510; 3.295] GeV^2
  text1[18] = new TText(0.17, 2.510,"150-158");
  text1[19] = new TText(0.24, 2.510,"159-167");
  text1[20] = new TText(0.30, 2.510,"168-175");
  text1[21] = new TText(0.40, 2.510,"176-182");
  text1[22] = new TText(0.50, 2.510,"183-190");

  // Q2 in [3.295; 4.326] GeV^2
  text1[23] = new TText(0.17, 3.295,"191-198");
  text1[24] = new TText(0.24, 3.295,"199-206");
  text1[25] = new TText(0.30, 3.295,"207-213");
  text1[26] = new TText(0.40, 3.295,"214-218");
  text1[27] = new TText(0.50, 3.295,"219-222");

  // Q2 in [4.326; 5.761] GeV^2
  text1[28] = new TText(0.24, 4.326,"223-229");
  text1[29] = new TText(0.30, 4.326,"230-236");
  text1[30] = new TText(0.40, 4.326,"237-241");
  text1[31] = new TText(0.50, 4.326,"242-245");

  // Q2 in [5.761; 7.000] GeV^2
  text1[32] = new TText(0.30, 5.761,"246-250");
  text1[33] = new TText(0.40, 5.761,"251-255");
  text1[34] = new TText(0.50, 5.761,"256-259");

  for(int i=0; i<35; i++)
    {
      text1[i]->SetTextColor(kBlack);
      text1[i]->SetTextSize(0.015);
      text1[i]->Draw("same");
    }



  c2->Print(Form("Summary_Plots/Q2xB_%i.png",l));
  delete c2;
  delete Q2xB;
}    
}
