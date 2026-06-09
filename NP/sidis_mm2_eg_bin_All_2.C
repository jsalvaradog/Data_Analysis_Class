static TH1F* DATA;
static TH1F* DVCS;
static TH1F* PI0;
static TH1F* SIDIS;
double BDT_cut_NP = 0.08;

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



TTree* Flatten_Tree(TTree* inputTree, TString output) 
{
    //TFile* f = new TFile(output, "RECREATE");  // not required here

    static std::vector<double>* mm2_eg;
    static std::vector<int>* flag;

    inputTree->SetBranchAddress("mm2_eg", &mm2_eg);
    inputTree->SetBranchAddress("bestCandidateFlag", &flag);

    TTree* outputTree = new TTree("pDVCS", "pDVCS");
    double mm2_eg_0;
    outputTree->Branch("mm2_eg", &mm2_eg_0, "mm2_eg/D");

    Long64_t nentries = inputTree->GetEntries();
    for (Long64_t i = 0; i < nentries; ++i) 
    {
        //std::cout<<i<<"/"<<nentries<<endl;
        inputTree->GetEntry(i);
        for(int j=0; j<flag->size(); j++) 
        {
            if (flag->at(j) == 1) 
            {
                mm2_eg_0 = mm2_eg->at(j);
            }
        }
        outputTree->Fill();
    }
    //outputTree->Write();
    //f->Close();

    return outputTree;
}


Double_t modelFunction(Double_t *x, Double_t *params) {
    // x[0] is the bin coordinate (if 1D histogram)
    Double_t a = params[0];
    Double_t b = params[1];
    Double_t c = params[2];

    // Retrieve bin contents from histograms
    //Double_t data = DATA->GetBinContent(DATA->FindBin(x[0]));
    Double_t dvcs = DVCS->GetBinContent(DVCS->FindBin(x[0]));
    Double_t pi0 = PI0->GetBinContent(PI0->FindBin(x[0]));
    Double_t sidis = SIDIS->GetBinContent(SIDIS->FindBin(x[0]));

    // Calculate the model value
    Double_t modelValue = a * dvcs + b * pi0 + c * sidis;

    // Return the difference squared from experimental data
    return modelValue;
    //return (data - modelValue) * (data - modelValue);
}

std::vector<TH1F*> sidis_mm2_eg_bin(int bin)
{
  double BDT_Value = Best_BDT(bin);

  gStyle->SetOptStat(0);
  TCut cut = TCut("bestCandidateFlag==1");
  
  TCanvas *c1 = new TCanvas("c1","Histograms",1200,500);
  c1->Divide(2,1);

  TChain *pDVCS_Data= new TChain("pDVCS");
  pDVCS_Data->Add(Form("Analysis/bin_%i/Tested_Quality_Data.root", bin));

  TChain *pDVCS_Sim= new TChain("pDVCS");
  pDVCS_Sim->Add(Form("Analysis/bin_%i/Tested_DVCS.root", bin));

  TChain *pDVCS_Pi0= new TChain("pDVCS");
  pDVCS_Pi0->Add(Form("Analysis/bin_%i/Tested_Pi0.root", bin));

  TChain *pDVCS_Pi0_2= new TChain("pDVCS");
  pDVCS_Pi0_2->Add(Form("Analysis/bin_%i/Tsidis.root", bin));

  TChain *pDVCS_Data_bkg1= new TChain("pDVCS");
  pDVCS_Data_bkg1->Add(Form("Analysis/bin_%i/TMaxime_pi0.root", bin));
  TChain *pDVCS_Data_bkg2= new TChain("pDVCS");
  pDVCS_Data_bkg2->Add(Form("Analysis/bin_%i/TMostafa_pi0.root", bin));


  auto hs1 = new THStack("hs1","M^{2}_{e#gamma X} (GeV^{2})");
  auto hs2 = new THStack("hs2","M^{2}_{e#gamma X} (GeV^{2})");

  TH1F *hist1c_Sim = new TH1F("hist1c_Sim","",100, 0., 2);
  TH1F *hist2c_Sim = new TH1F("hist2c_Sim","",100, 0., 2);
  
  TH1F *hist1c_Data = new TH1F("hist1c_Data","",100, 0., 2);
  TH1F *hist2c_Data = new TH1F("hist2c_Data","",100, 0., 2);

  TH1F *hist1c_Data_bkg1 = new TH1F("hist1c_Data_bkg1","",100, 0., 2);
  TH1F *hist2c_Data_bkg1 = new TH1F("hist2c_Data_bkg1","",100, 0., 2);

  TH1F *hist1c_Data_bkg2 = new TH1F("hist1c_Data_bkg2","",100, 0., 2);
  TH1F *hist2c_Data_bkg2 = new TH1F("hist2c_Data_bkg2","",100, 0., 2);

  TH1F *hist1c_Pi0 = new TH1F("hist1c_Pi0","",100, 0, 2);
  TH1F *hist2c_Pi0 = new TH1F("hist2c_Pi0","",100, 0, 2);

  TH1F *hist1c_Pi0_2 = new TH1F("hist1c_Pi0_2","",100, 0, 2);
  TH1F *hist2c_Pi0_2 = new TH1F("hist2c_Pi0_2","",100, 0, 2);

  TH1F *hist1c_SimAdd = new TH1F("hist1c_SimAdd","DVCS + #pi^{0}",100, 0., 2);
  TH1F *hist2c_SimAdd = new TH1F("hist2c_SimAdd","DVCS + #pi^{0}",100, 0., 2);

  //Variables to plot
  const char *p2="mm2_eg";
  pDVCS_Data_bkg1->Project("hist1c_Data_bkg1", p2, (cut )*TCut("Weight"));
  pDVCS_Data_bkg1->Project("hist2c_Data_bkg1", p2, (cut + TCut(Form("_strip_Nuc_BDT > %f && _strip_Nuc_BDT_SIDIS>0.1", BDT_Value)))*TCut("Weight"));

  pDVCS_Data_bkg2->Project("hist1c_Data_bkg2", p2, (cut )*TCut("Weight"));
  pDVCS_Data_bkg2->Project("hist2c_Data_bkg2", p2, (cut + TCut(Form("_strip_Nuc_BDT > %f && _strip_Nuc_BDT_SIDIS>0.1", BDT_Value)))*TCut("Weight"));

  pDVCS_Data->Project("hist1c_Data", p2, cut);
  pDVCS_Data->Project("hist2c_Data", p2, cut + TCut(Form("_strip_Nuc_BDT > %f && _strip_Nuc_BDT_SIDIS>0.1", BDT_Value)));

  pDVCS_Sim->Project("hist1c_Sim", p2, cut);
  pDVCS_Sim->Project("hist2c_Sim", p2, cut + TCut(Form("_strip_Nuc_BDT > %f && _strip_Nuc_BDT_SIDIS>0.1", BDT_Value)));

  pDVCS_Pi0->Project("hist1c_Pi0", p2, cut*TCut("40.09*1e6*xsec_born/(10000*10000)"));
  pDVCS_Pi0->Project("hist2c_Pi0", p2, (cut + TCut(Form("_strip_Nuc_BDT > %f && _strip_Nuc_BDT_SIDIS>0.1", BDT_Value)))*TCut("40.09*1e6*xsec_born/(10000*10000)"));

  pDVCS_Pi0_2->Project("hist1c_Pi0_2", p2, (cut ) * TCut("40.09*1e3*xsec_born/(999900000)"));
  pDVCS_Pi0_2->Project("hist2c_Pi0_2", p2, (cut + TCut(Form("N_Ph<3 && _strip_Nuc_BDT > %f && _strip_Nuc_BDT_SIDIS>0.1", BDT_Value)))*TCut("40.09*1e3*xsec_born/(999900000)"));

  double factor, factor_pi0, factor_sidis;

  /*
  //unbinnned fit using RooFit - not doing well
  std::cout<<"Flattening Data..."<<std::endl;
  TTree* pDVCS_Data_flat = Flatten_Tree(pDVCS_Data, "Flat_Data.root");
  std::cout<<"Flattening DVCS..."<<std::endl;
  TTree* pDVCS_Sim_flat = Flatten_Tree(pDVCS_Sim, "Flat_DVCS.root");
  std::cout<<"Flattening Pi0..."<<std::endl;
  TTree* pDVCS_Pi0_flat = Flatten_Tree(pDVCS_Pi0, "Flat_Pi0.root");
  std::cout<<"Flattening SIDIS..."<<std::endl;
  TTree* pDVCS_Pi0_2_flat = Flatten_Tree(pDVCS_Pi0_2, "Flat_SIDIS.root");

  RooRealVar x("mm2_eg", "Observable", 0, 2);  // use appropriate range
  RooDataSet data("data", "Data", pDVCS_Data_flat, x);
  RooDataSet dvcs("dvcs", "DVCS", pDVCS_Sim_flat, x);
  RooDataSet pi0("pi0", "Pi0", pDVCS_Pi0_flat, x);
  RooDataSet sidis("sidis", "SIDIS", pDVCS_Pi0_2_flat, x);

  RooKeysPdf pdf_dvcs("pdf_dvcs", "DVCS PDF", x, dvcs);
  RooKeysPdf pdf_pi0 ("pdf_pi0",  "Pi0 PDF",  x, pi0);
  RooKeysPdf pdf_sidis("pdf_sidis","SIDIS PDF", x, sidis);

  RooRealVar a("a", "DVCS fraction", 0.3, 0.0, 1.0);
  RooRealVar b("b", "Pi0 fraction",  0.3, 0.0, 2.0);
  RooRealVar c("c", "SIDIS fraction", 0.3, 0.0, 1.0);

  RooAddPdf model("model", "a*DVCS + b*Pi0 + c*SIDIS",
                RooArgList(pdf_dvcs, pdf_pi0, pdf_sidis),
                RooArgList(a, b, c)); 

  RooFitResult* result = model.fitTo(data, RooFit::Save());

  TCanvas *c8 = new TCanvas("c8","Histograms");
  RooPlot* frame = x.frame();
data.plotOn(frame);
model.plotOn(frame);
model.plotOn(frame, RooFit::Components("pdf_dvcs"), RooFit::LineColor(kRed));
model.plotOn(frame, RooFit::Components("pdf_pi0"),  RooFit::LineColor(kBlue));
model.plotOn(frame, RooFit::Components("pdf_sidis"),RooFit::LineColor(kGreen));
frame->Draw();
c8->SaveAs("fit_result.png");

  factor = a.getVal();
  factor_pi0 = b.getVal();
  factor_sidis = c.getVal();

  std::cout << "\nFit results: "<<factor << " " << factor_pi0 << " " << factor_sidis << "\n" << std::endl;
  */

  //factor=0.25; //Bin 8 //SIDIS only on FD. Add cut by hand
  //factor_pi0=1.6;
  //factor_sidis=1.0;

  //factor=0.45; //Bin 9
  //factor_pi0=1.5;
  //factor_sidis=0.2;

  //factor=0.5; //Bin 10
  //factor_pi0=1.5;
  //factor_sidis=0.2;

  //factor=0.6; //Bin 11 & 12
  //factor_pi0=1.2;
  //factor_sidis=0.2;

  //factor=0.55; //Bin 13
  //factor_pi0=1.3;
  //factor_sidis=0.2;

  //factor=0.5; //Bin 14
  //factor_pi0=2.0;
  //factor_sidis=0.2;

  //factor=0.41; //Global
  //factor_pi0=0.25;
  //factor_sidis=1.0;

  //factor=0.65; //FT photons
  //factor_pi0=1.2; //FT photons
  //factor_sidis=1.0; //FT photons

  //factor=0.12; //FD photons
  //factor_pi0=0.08; //FD photons
  //factor_sidis=1.0; //FD photons


  c1->cd(1);
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.012);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.1);
  hist1c_Sim->SetLineColor(kBlack);
  hist1c_Data->SetLineColor(kRed);
  hist1c_Pi0->SetLineColor(kBlue);
  hist1c_SimAdd->SetLineColor(kCyan);
  hist1c_Pi0_2->SetLineColor(kGreen);
  hist1c_Data_bkg1->SetLineColor(kMagenta);
  hist1c_Data_bkg2->SetLineColor(kMagenta);

  hist1c_Sim->SetLineWidth(2);
  hist1c_Data->SetLineWidth(2);
  hist1c_Pi0->SetLineWidth(2);
  hist1c_SimAdd->SetLineWidth(2);
  hist1c_Pi0_2->SetLineWidth(2);
  hist1c_Data_bkg1->SetLineWidth(2);
  hist1c_Data_bkg2->SetLineWidth(2);


  //Using a binned fit
  TF1 *fitFunc = new TF1("fitFunc", modelFunction, 0, 2, 3);
  DATA = hist1c_Data;
  DVCS = hist1c_Sim;
  PI0 = hist1c_Pi0;
  SIDIS = hist1c_Pi0_2;

  fitFunc->SetParameter(0, 0.25);
  fitFunc->SetParameter(1, 0.3);
  fitFunc->SetParameter(2, 0.2);

  fitFunc->SetParLimits(0, 0, 2);
  fitFunc->SetParLimits(1, 0, 2);
  fitFunc->SetParLimits(2, 0, 2);

  // Perform the fit
  hist1c_Data->Fit("fitFunc", "QNMR");

  //std::cout << "\nFit results BEFORE BDT: "<<fitFunc->GetParameter(0) << " " << fitFunc->GetParameter(1) << " " << fitFunc->GetParameter(2) << "\n" << std::endl;
  // Retrieve fit results
  factor = fitFunc->GetParameter(0);
  factor_pi0 = fitFunc->GetParameter(1);
  factor_sidis = fitFunc->GetParameter(2);
  
  //plot 
  hist1c_Sim->Scale(factor);
  hist1c_Pi0->Scale(factor_pi0);
  hist1c_Pi0_2->Scale(factor_sidis);

  hist1c_SimAdd->Add(hist1c_Sim, hist1c_Pi0,1,1);
  hist1c_SimAdd->Add(hist1c_SimAdd, hist1c_Pi0_2,1,1);

  //hist1c_SimAdd->Add(hist1c_Sim, hist1c_Data_bkg1,1,1);
  //hist1c_SimAdd->Add(hist1c_SimAdd, hist1c_Data_bkg2,1,1);
  //hist1c_SimAdd->Scale(hist1c_Data->Integral()/hist1c_SimAdd->Integral());
  
  hs1->Add(hist1c_Sim);
  hs1->Add(hist1c_Data);
  hs1->Add(hist1c_Pi0);
  hs1->Add(hist1c_Pi0_2);
  hs1->Add(hist1c_SimAdd);
  //hs1->Add(hist1c_Data_bkg1);
  //hs1->Add(hist1c_Data_bkg2);
  hs1->Draw("nostack,hist");
    
  c1->cd(2);
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.012);
  gPad->SetBottomMargin(0.15);
  gPad->SetTopMargin(0.1);
  hist2c_Sim->SetLineColor(kBlack);
  hist2c_Data->SetLineColor(kRed);
  hist2c_Pi0->SetLineColor(kBlue);
  hist2c_SimAdd->SetLineColor(kCyan);
  hist2c_Pi0_2->SetLineColor(kGreen);
  hist2c_Data_bkg1->SetLineColor(kMagenta);
  hist2c_Data_bkg2->SetLineColor(kMagenta);


  hist2c_Sim->SetLineWidth(2);
  hist2c_Data->SetLineWidth(2);
  hist2c_Pi0->SetLineWidth(2);
  hist2c_SimAdd->SetLineWidth(2);
  hist2c_Pi0_2->SetLineWidth(2);
  hist2c_Data_bkg1->SetLineWidth(2);
  hist2c_Data_bkg2->SetLineWidth(2);


  //Using a binned fit
  DATA = hist2c_Data;
  DVCS = hist2c_Sim;
  PI0 = hist2c_Pi0;
  SIDIS = hist2c_Pi0_2;


  fitFunc->SetParameter(0, 0.25);
  fitFunc->SetParameter(1, 0.3);
  fitFunc->SetParameter(2, 0.2);

  // Perform the fit
  hist2c_Data->Fit("fitFunc", "QNMR");

  //std::cout << "\nFit results AFTER BDT: "<<fitFunc->GetParameter(0) << " " << fitFunc->GetParameter(1) << " " << fitFunc->GetParameter(2) << "\n" << std::endl;
  // Retrieve fit results
  //factor = fitFunc->GetParameter(0);
  //factor_pi0 = fitFunc->GetParameter(1);
  //factor_sidis = fitFunc->GetParameter(2);


  //plot 
  hist2c_Sim->Scale(factor);
  hist2c_Pi0->Scale(factor_pi0);
  hist2c_Pi0_2->Scale(factor_sidis);

  //hist2c_Sim->Scale(2.0);
  //hist2c_Pi0->Scale(1.5);
  hist2c_SimAdd->Add(hist2c_Sim, hist2c_Pi0,1,1);
  hist2c_SimAdd->Add(hist2c_SimAdd, hist2c_Pi0_2,1,1);


  hs2->Add(hist2c_Sim);
  hs2->Add(hist2c_Data);
  hs2->Add(hist2c_Pi0);
  hs2->Add(hist2c_Pi0_2);
  hs2->Add(hist2c_SimAdd);
  //hs2->Add(hist2c_Data_bkg1);
  //hs2->Add(hist2c_Data_bkg2);
  hs2->Draw("nostack,hist");


  TLegend *legend = new TLegend(); // Position of the legend
  legend->AddEntry(hist1c_Data, "Data", "l");
  legend->AddEntry(hist1c_Sim, "DVCS MC", "l");
  legend->AddEntry(hist1c_Pi0, "#pi^{0} MC", "l");
  legend->AddEntry(hist1c_Pi0_2, "Sidis MC", "l");
  legend->AddEntry(hist1c_SimAdd, "Total MC", "l");
  legend->Draw();
  
   
  //std::cout<<"Number of Data events before BDT "<<hist1c_Data->GetEntries()<<endl;
  //std::cout<<"Number of Data events after BDT "<<hist2c_Data->GetEntries()<<"\n"<<endl;

  //std::cout<<"Estimated contamination "<<hist2c_Data_bkg1->Integral()<<" "<<hist2c_Data_bkg2->Integral()<<"\n"<<endl;
  std::cout<<"Fitted contamination "<<hist2c_Pi0->Integral()<<" "<<hist2c_Pi0_2->Integral()<<"\n"<<endl;

  //std::cout<<"Number of Pi0 events after BDT "<<hist2c_Pi0->GetEntries()<<endl;
  //std::cout<<"Number of SIDIS events after BDT "<<hist2c_Pi0_2->GetEntries()<<"\n"<<endl;
 
  //std::cout<<"Pi0 Weighted by luminosity "<<hist2c_Pi0->Integral()<<endl;
  //std::cout<<"SIDIS Weighted by luminosity "<<hist2c_Pi0_2->Integral()<<endl;

  hs1->SetTitle("Before BDT");
  hs1->GetXaxis()->SetTitle("M_{e#gamma X}^{2} (GeV^{2})");
  hs1->GetYaxis()->SetTitle("Counts");
  hs1->GetXaxis()->SetTitleSize(0.07);
  hs1->GetYaxis()->SetTitleSize(0.07);
  hs1->GetXaxis()->SetLabelSize(0.06);
  hs1->GetYaxis()->SetLabelSize(0.06);
  hs1->GetYaxis()->SetTitleOffset(1.1);
  hs1->GetXaxis()->SetTitleOffset(1.0);
  hs1->GetYaxis()->SetNdivisions(6);
  hs1->GetXaxis()->SetNdivisions(8);

  hs2->SetTitle("After BDT");
  hs2->GetXaxis()->SetTitle("M_{e#gamma X}^{2} (GeV^{2})");
  hs2->GetYaxis()->SetTitle("Counts");
  hs2->GetXaxis()->SetTitleSize(0.07);
  hs2->GetYaxis()->SetTitleSize(0.07);
  hs2->GetXaxis()->SetLabelSize(0.06);
  hs2->GetYaxis()->SetLabelSize(0.06);
  hs2->GetYaxis()->SetTitleOffset(1.1);
  hs2->GetXaxis()->SetTitleOffset(1.0);
  hs2->GetYaxis()->SetNdivisions(6);
  hs2->GetXaxis()->SetNdivisions(8);
  
  c1->Print(Form("Summary_Plots/mm2_eg_fits/bin_%i.png", bin));

  static std::vector<TH1F*> result;
  result.push_back(hist2c_Sim);
  result.push_back(hist2c_Pi0);
  result.push_back(hist2c_Pi0_2);

  delete c1;
  delete pDVCS_Data;
  delete pDVCS_Sim;
  delete pDVCS_Pi0;
  delete pDVCS_Pi0_2;
  delete pDVCS_Data_bkg1;
  delete pDVCS_Data_bkg2;
  delete hist1c_Sim;
  delete hist1c_Data;
  delete hist2c_Data;
  delete hist1c_Data_bkg1;
  delete hist2c_Data_bkg1;
  delete hist1c_Data_bkg2;
  delete hist2c_Data_bkg2;
  delete hist1c_Pi0;
  delete hist1c_Pi0_2;
  delete hist1c_SimAdd;
  delete fitFunc;
  delete hs1;
  delete hs2;
  delete legend;


  return result;
}



void sidis_mm2_eg_bin_All_2()
{
    gErrorIgnoreLevel = kFatal;

    TChain *pDVCS_Data= new TChain("pDVCS");
    for(int i=1; i<=259; i++)
    {
    pDVCS_Data->Add(Form("Analysis/bin_%i/Tested_Quality_Data.root",i));
    }

    TH1F *Data = new TH1F("Data","",100, 0., 2);
    TH1F *DVCS = new TH1F("DVCS","",100, 0., 2);
    TH1F *Pi0 = new TH1F("Pi0","",100, 0., 2);
    TH1F *SIDIS = new TH1F("SIDIS","",100, 0., 2);
    TH1F *TOTAL = new TH1F("TOTAL","",100, 0., 2);

    std::vector<TH1F*> mm2_eg_bins;

    for(int i=1; i<=259; i++)
    {
    mm2_eg_bins= sidis_mm2_eg_bin(i);
    DVCS->Add(DVCS, mm2_eg_bins.at(0));
    Pi0->Add(Pi0, mm2_eg_bins.at(1));
    SIDIS->Add(SIDIS, mm2_eg_bins.at(2));
    }

  pDVCS_Data->Project("Data", "mm2_eg", "bestCandidateFlag==1 && _strip_Nuc_BDT > 0.08 && _strip_Nuc_BDT_SIDIS>0.1");

  TCanvas *c1 = new TCanvas("c1","Histograms",700,500);

  Data->SetLineColor(kRed);
  DVCS->SetLineColor(kBlack);
  Pi0->SetLineColor(kBlue);
  SIDIS->SetLineColor(kGreen);
  TOTAL->SetLineColor(kCyan);

  Data->SetLineWidth(2);
  DVCS->SetLineWidth(2);
  Pi0->SetLineWidth(2);
  SIDIS->SetLineWidth(2);
  TOTAL->SetLineWidth(2);

  TOTAL->Add(DVCS, Pi0, 1, 1);
  TOTAL->Add(TOTAL, SIDIS, 1, 1);

  Data->SetTitle("M^{2}_{e#gamma X} (GeV^{2})");
  Data->GetXaxis()->SetTitle("M^{2}_{e#gamma X} (GeV^{2})");
  Data->GetYaxis()->SetTitle("Counts");
  Data->GetXaxis()->SetTitleSize(0.07);
  Data->GetYaxis()->SetTitleSize(0.07);
  Data->GetXaxis()->SetLabelSize(0.06);
  Data->GetYaxis()->SetLabelSize(0.06);
  Data->GetYaxis()->SetTitleOffset(1.1);
  Data->GetXaxis()->SetTitleOffset(1.0);
  Data->GetYaxis()->SetNdivisions(6);
  Data->GetXaxis()->SetNdivisions(8);

  Data->Draw("hist");
  DVCS->Draw("same,hist");
  Pi0->Draw("same,hist");
  SIDIS->Draw("same,hist");
  TOTAL->Draw("same,hist");

  TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.9); // Position of the legend
  legend->AddEntry(Data, "Data", "l");
  legend->AddEntry(DVCS, "DVCS MC", "l");
  legend->AddEntry(Pi0, "#pi^{0} MC", "l");
  legend->AddEntry(SIDIS, "SIDIS MC", "l");
  legend->AddEntry(TOTAL, "Total MC", "l");
  legend->Draw();

  c1->Print("Summary_Plots/mm2_eg_fit_on_bins.pdf");  
}
