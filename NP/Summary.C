TCut cut_P=TCut("bestCandidateFlag==1 && strip_Q2>0 && strip_Xbj >0 && strip_Xbj < 1 && t_Ph <0");
TCut cut_NP=TCut("bestCandidateFlag==1 && mm2_eg>0 && N_Ph<3 && mm2_eg<3 && abs(t_Ph/strip_Q2)<1 && t_Ph>-1");

double BDT_cut_P = 0.0;
double BDT_cut_NP= 0.08;
double BDT_cut_SIDIS=0.1;
int NBins=94;

TString DVCS=TString("Analysis/Merged_DVCS.root");
TString Pi0=TString("Analysis/Merged_Pi0.root");
TString DATA=TString("Analysis/Merged_Data.root");
TString SIDIS=TString("Analysis/Tsidis.root");

TCut Mbins[94];
TCut BDT_bin_cut;

std::vector<double> bdts;

double get_bdt_event(double strip_Xbj, double strip_Q2, double t_Ph)
{
  for (int i = 0; i < 94; ++i)
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



void Apply_conf(TH2F*& hist)
{
  hist->GetXaxis()->SetTitle("BDT Score");

  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.05);

  hist->GetYaxis()->SetTitleOffset(0.9);
  hist->GetXaxis()->SetTitleOffset(0.7);

  hist->GetXaxis()->SetLabelSize(0.04);
  hist->GetYaxis()->SetLabelSize(0.04);

  }

void Apply_conf(TH1F*& hist)
{
  hist->GetYaxis()->SetTitle("Counts");
  hist->GetXaxis()->SetTitle(hist->GetTitle());

  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.06);

  hist->GetYaxis()->SetTitleOffset(0.7);
  hist->GetXaxis()->SetTitleOffset(0.75);

  hist->GetXaxis()->SetLabelSize(0.04);
  hist->GetYaxis()->SetLabelSize(0.04);

  hist->SetMinimum(1.0);
  hist->GetXaxis()->SetNdivisions(4);
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

void TrainVars_BDT_single(TTree* pDVCS, TCut cut_ref, string sufix, string prefix){
  TCanvas *c1 =new  TCanvas("h1","Histograms",1500,500);
  c1->Divide(3,1);
  gStyle->SetOptStat(0);

  TH2F *histeT = new TH2F("histeT", "",100,-0.4, 0.4,100, 4, 18);
  TH2F *histgT = new TH2F("histgT", "",100,-0.4, 0.4,100, 0, 3);
  TH2F *histNT = new TH2F("histNT", "",100,-0.4, 0.4,100, -1, 0);
  
  pDVCS->Project("histeT", "mm2_e:_strip_Nuc_BDT",cut_NP + cut_ref);
  pDVCS->Project("histgT", "mm2_eg:_strip_Nuc_BDT",cut_NP + cut_ref);
  pDVCS->Project("histNT", "t_Ph:_strip_Nuc_BDT",cut_NP + cut_ref);

  Apply_conf(histeT);
  Apply_conf(histgT);
  Apply_conf(histNT);
  
  std::cout<<histeT->Integral()<<" "<<histgT->Integral()<<" "<<histNT->Integral()<<endl;

  c1->cd(1);
  histeT->Draw("COLZ");
  histeT->GetYaxis()->SetTitle("M_{eX}^{2} (GeV)^{2}");
 
  c1->cd(2);
  histgT->Draw("COLZ");
  histgT->GetYaxis()->SetTitle("M_{e#gamma X}^{2} (GeV)^{2}");
  
  c1->cd(3);
  histNT->Draw("COLZ");
  histNT->GetYaxis()->SetTitle("t (GeV)^{2}");


  c1->Print(Form("Summary_Plots/%sTrainVars_BDT%s.pdf",prefix.c_str(),sufix.c_str()));
  
  delete c1;
  delete histeT;
  delete histgT;
  delete histNT;
}

void TrainVars_BDT(TTree* pDVCS, string prefix)
{
TrainVars_BDT_single(pDVCS, "", "", prefix);
TrainVars_BDT_single(pDVCS, "strip_Ph_status<2000","_FT", prefix);
TrainVars_BDT_single(pDVCS, "strip_Ph_status>2000","_FD", prefix);
}


#ifdef __CLING__
#pragma cling optimize(0)
#endif
void Get_BDT_Score(TTree* signal, TTree* background, TTree* pDVCS)
{
//=========Macro generated from canvas: canvas1/TMVA comparison BDT
//=========  (Thu Jan  5 15:05:52 2023) by ROOT version 6.26/10
   TCanvas *canvas1 = new TCanvas("canvas1", "TMVA comparison BDT",200,37,600,468);
   gStyle->SetOptStat(0);
   canvas1->Range(-0.4349485,-0.9997183,0.4052419,7.331268);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#f0f0f0");
   canvas1->SetFillColor(ci);
   canvas1->SetBorderMode(0);
   canvas1->SetBorderSize(2);
   canvas1->SetTickx(1);
   canvas1->SetTicky(1);
   canvas1->SetRightMargin(0.05);
   canvas1->SetBottomMargin(0.12);

   ci = TColor::GetColor("#fffffd");
   canvas1->SetFrameFillColor(ci);
   canvas1->SetFrameBorderMode(0);

   ci = TColor::GetColor("#fffffd");
   canvas1->SetFrameFillColor(ci);
   canvas1->SetFrameBorderMode(0);

   TH2F *frameBDT__1 = new TH2F("frameBDT__1","Classifier output",500,-0.3467285,0.3632324,500,0,0.06);
   frameBDT__1->SetStats(0);
   frameBDT__1->SetLineWidth(2);
   frameBDT__1->SetMarkerStyle(21);
   frameBDT__1->SetMarkerSize(0.3);
   frameBDT__1->GetXaxis()->SetTitle("BDT response");
   frameBDT__1->GetXaxis()->SetLabelOffset(0.012);
   frameBDT__1->GetXaxis()->SetLabelSize(0.04);
   frameBDT__1->GetXaxis()->SetTitleSize(0.045);
   frameBDT__1->GetXaxis()->SetTitleOffset(1.25);
   frameBDT__1->GetYaxis()->SetLabelOffset(0.012);
   frameBDT__1->GetYaxis()->SetLabelSize(0.04);
   frameBDT__1->GetYaxis()->SetTitleSize(0.045);
   frameBDT__1->GetYaxis()->SetTitleOffset(1.2);
   frameBDT__1->GetZaxis()->SetLabelSize(0.04);
   frameBDT__1->GetZaxis()->SetTitleSize(0.04);
   frameBDT__1->GetZaxis()->SetTitleOffset(1);
   frameBDT__1->Draw("");
   
   TLegend *leg = new TLegend(0.105,0.78,0.505,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);

   ci = TColor::GetColor("#7d8b9d");
   leg->SetLineColor(ci);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1);
   TLegendEntry *entry=leg->AddEntry("MVA_BDT_S","Signal","F");
   entry->SetFillColor(38);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#0000ee");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("MVA_BDT_B","Background","F");
   entry->SetFillColor(2);
   entry->SetFillStyle(1001);
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Data","Data","F");
   entry->SetFillColor(kBlack);
   entry->SetFillStyle(1001);
   entry->SetLineColor(kBlack);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(kBlack);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();

   TH1D *MVA_BDT_Train_S__4 = new TH1D("MVA_BDT_Train_S__4","MVA_BDT_Train_S",100,-0.4,0.4);
   signal->Project("MVA_BDT_Train_S__4", "_strip_Nuc_BDT", cut_NP);
   MVA_BDT_Train_S__4->Scale(1.0/MVA_BDT_Train_S__4->Integral());


   ci = TColor::GetColor("#0000ee");
   MVA_BDT_Train_S__4->SetLineColor(ci);

   ci = TColor::GetColor("#0000ee");
   MVA_BDT_Train_S__4->SetMarkerColor(ci);
   MVA_BDT_Train_S__4->SetMarkerStyle(20);
   MVA_BDT_Train_S__4->SetMarkerSize(0.7);
   MVA_BDT_Train_S__4->GetXaxis()->SetLabelFont(42);
   MVA_BDT_Train_S__4->GetXaxis()->SetTitleOffset(1);
   MVA_BDT_Train_S__4->GetXaxis()->SetTitleFont(42);
   MVA_BDT_Train_S__4->GetYaxis()->SetLabelFont(42);
   MVA_BDT_Train_S__4->GetYaxis()->SetTitleFont(42);
   MVA_BDT_Train_S__4->GetZaxis()->SetLabelFont(42);
   MVA_BDT_Train_S__4->GetZaxis()->SetTitleOffset(1);
   MVA_BDT_Train_S__4->GetZaxis()->SetTitleFont(42);
   MVA_BDT_Train_S__4->Draw("e1same");
   
   TH1D *MVA_BDT_Train_B__5 = new TH1D("MVA_BDT_Train_B__5","MVA_BDT_Train_B",100,-0.4,0.4);
   background->Project("MVA_BDT_Train_B__5", "_strip_Nuc_BDT", cut_NP);
   //MVA_BDT_Train_B__5->Scale(1.0/MVA_BDT_Train_B__5->Integral());
   //MVA_BDT_Train_B__5->Add(MVA_BDT_Train_S__4);
   MVA_BDT_Train_B__5->Scale(1.0/MVA_BDT_Train_B__5->Integral());

   //MVA_BDT_Train_B__5->Add(MVA_BDT_Train_B__5, MVA_BDT_Train_S__4, 0.25, 0.75);
   //MVA_BDT_Train_B__5->Scale(1.0/MVA_BDT_Train_B__5->Integral());

   MVA_BDT_Train_B__5->SetLineColor(2);
   MVA_BDT_Train_B__5->SetMarkerColor(2);
   MVA_BDT_Train_B__5->SetMarkerStyle(20);
   MVA_BDT_Train_B__5->SetMarkerSize(0.7);
   MVA_BDT_Train_B__5->GetXaxis()->SetLabelFont(42);
   MVA_BDT_Train_B__5->GetXaxis()->SetTitleOffset(1);
   MVA_BDT_Train_B__5->GetXaxis()->SetTitleFont(42);
   MVA_BDT_Train_B__5->GetYaxis()->SetLabelFont(42);
   MVA_BDT_Train_B__5->GetYaxis()->SetTitleFont(42);
   MVA_BDT_Train_B__5->GetZaxis()->SetLabelFont(42);
   MVA_BDT_Train_B__5->GetZaxis()->SetTitleOffset(1);
   MVA_BDT_Train_B__5->GetZaxis()->SetTitleFont(42);
   MVA_BDT_Train_B__5->Draw("e1same");


   //**************************************************************

   TH1D *hData = new TH1D("hData","Data",100,-0.4,0.4);
   pDVCS->Project("hData", "_strip_Nuc_BDT", cut_NP);

   hData->Scale(1.0/hData->Integral());
   hData->SetLineColor(kBlack);
   hData->SetFillColor(kBlack);
   hData->SetFillStyle(3554);

   hData->SetMarkerColor(kBlack);
   hData->SetMarkerStyle(20);
   hData->SetMarkerSize(0.7);
   hData->GetXaxis()->SetLabelFont(42);
   hData->GetXaxis()->SetTitleOffset(1);
   hData->GetXaxis()->SetTitleFont(42);
   hData->GetYaxis()->SetLabelFont(42);
   hData->GetYaxis()->SetTitleFont(42);
   hData->GetZaxis()->SetLabelFont(42);
   hData->GetZaxis()->SetTitleOffset(1);
   hData->GetZaxis()->SetTitleFont(42);
   hData->Draw("histsame");

   //****************************************************
   
   TH2F *frameBDT__6 = new TH2F("frameBDT__6","Classifier output",500,-0.3467285,0.3632324,500,0,0.06);
   frameBDT__6->SetStats(0);
   frameBDT__6->SetLineWidth(2);
   frameBDT__6->SetMarkerStyle(21);
   frameBDT__6->SetMarkerSize(0.3);
   frameBDT__6->GetXaxis()->SetTitle("BDT response");
   frameBDT__6->GetXaxis()->SetLabelOffset(0.012);
   frameBDT__6->GetXaxis()->SetLabelSize(0.04);
   frameBDT__6->GetXaxis()->SetTitleSize(0.045);
   frameBDT__6->GetXaxis()->SetTitleOffset(1.25);
   frameBDT__6->GetYaxis()->SetTitle("(1/N) dN^{ }/^{ }dx");
   frameBDT__6->GetYaxis()->SetLabelOffset(0.012);
   frameBDT__6->GetYaxis()->SetLabelSize(0.04);
   frameBDT__6->GetYaxis()->SetTitleSize(0.045);
   frameBDT__6->GetYaxis()->SetTitleOffset(1.2);
   frameBDT__6->GetZaxis()->SetLabelSize(0.04);
   frameBDT__6->GetZaxis()->SetTitleSize(0.04);
   frameBDT__6->GetZaxis()->SetTitleOffset(1);
   frameBDT__6->Draw("sameaxis");

  
   TPaveText *pt = new TPaveText(0.01,0.9355405,0.71,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);

   ci = TColor::GetColor("#5d6b7d");
   pt->SetFillColor(ci);

   ci = TColor::GetColor("#7d8b9d");
   pt->SetLineColor(ci);
   pt->SetTextColor(0);


   //pt->Draw();
   canvas1->Modified();
   canvas1->cd();
   canvas1->SetSelected(canvas1);
   canvas1->Print("Summary_Plots/BDT_Score_P.pdf");

   delete canvas1;
   delete frameBDT__1; 
   delete leg;
   delete MVA_BDT_Train_S__4; 
   delete MVA_BDT_Train_B__5; 
   delete hData;
   delete frameBDT__6; 
   delete pt;
}


void Get_BDT_Score_single(TTree* pDVCS)
{
//=========Macro generated from canvas: canvas1/TMVA comparison BDT
//=========  (Thu Jan  5 15:05:52 2023) by ROOT version 6.26/10
   TCanvas *canvas1 = new TCanvas("canvas1", "TMVA comparison BDT",200,37,600,468);
   gStyle->SetOptStat(0);
   canvas1->Range(-0.4349485,-0.9997183,0.4052419,7.331268);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#f0f0f0");
   canvas1->SetFillColor(ci);
   canvas1->SetBorderMode(0);
   canvas1->SetBorderSize(2);
   canvas1->SetTickx(1);
   canvas1->SetTicky(1);
   canvas1->SetRightMargin(0.05);
   canvas1->SetBottomMargin(0.12);

   ci = TColor::GetColor("#fffffd");
   canvas1->SetFrameFillColor(ci);
   canvas1->SetFrameBorderMode(0);

   ci = TColor::GetColor("#fffffd");
   canvas1->SetFrameFillColor(ci);
   canvas1->SetFrameBorderMode(0);
   
   TH2F *frameBDT__1 = new TH2F("frameBDT__1","Classifier output",500,-0.3467285,0.3632324,500,0,0.2);
   frameBDT__1->SetStats(0);
   frameBDT__1->SetLineWidth(2);
   frameBDT__1->SetMarkerStyle(21);
   frameBDT__1->SetMarkerSize(0.3);
   frameBDT__1->GetXaxis()->SetTitle("BDT response");
   frameBDT__1->GetXaxis()->SetLabelOffset(0.012);
   frameBDT__1->GetXaxis()->SetLabelSize(0.04);
   frameBDT__1->GetXaxis()->SetTitleSize(0.045);
   frameBDT__1->GetXaxis()->SetTitleOffset(1.25);
   frameBDT__1->GetYaxis()->SetLabelOffset(0.012);
   frameBDT__1->GetYaxis()->SetLabelSize(0.04);
   frameBDT__1->GetYaxis()->SetTitleSize(0.045);
   frameBDT__1->GetYaxis()->SetTitleOffset(1.2);
   frameBDT__1->GetZaxis()->SetLabelSize(0.04);
   frameBDT__1->GetZaxis()->SetTitleSize(0.04);
   frameBDT__1->GetZaxis()->SetTitleOffset(1);
   frameBDT__1->Draw("");
   
   TLegend *leg = new TLegend(0.105,0.78,0.505,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);

   ci = TColor::GetColor("#7d8b9d");
   leg->SetLineColor(ci);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1);
   TLegendEntry *entry=leg->AddEntry("MVA_BDT_S","Signal","F");
   entry->SetFillColor(38);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#0000ee");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("MVA_BDT_B","Background","F");
   entry->SetFillColor(2);
   entry->SetFillStyle(1001);
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Data","Data","F");
   entry->SetFillColor(kBlack);
   entry->SetFillStyle(1001);
   entry->SetLineColor(kBlack);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(kBlack);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();


     
   TFile *File = new TFile("Analysis/TMVA.root");   
   TTree *training = (TTree *)(File->Get("dataset/TrainTree"));

   TH1D *MVA_BDT_Train_S__4 = new TH1D("MVA_BDT_Train_S__4","MVA_BDT_Train_S",40,-0.3467285,0.3632324);
   training->Project("MVA_BDT_Train_S__4", "BDT","classID==0");
   MVA_BDT_Train_S__4->Scale(1.0/MVA_BDT_Train_S__4->Integral());


   ci = TColor::GetColor("#0000ee");
   MVA_BDT_Train_S__4->SetLineColor(ci);

   ci = TColor::GetColor("#0000ee");
   MVA_BDT_Train_S__4->SetMarkerColor(ci);
   MVA_BDT_Train_S__4->SetMarkerStyle(20);
   MVA_BDT_Train_S__4->SetMarkerSize(0.7);
   MVA_BDT_Train_S__4->GetXaxis()->SetLabelFont(42);
   MVA_BDT_Train_S__4->GetXaxis()->SetTitleOffset(1);
   MVA_BDT_Train_S__4->GetXaxis()->SetTitleFont(42);
   MVA_BDT_Train_S__4->GetYaxis()->SetLabelFont(42);
   MVA_BDT_Train_S__4->GetYaxis()->SetTitleFont(42);
   MVA_BDT_Train_S__4->GetZaxis()->SetLabelFont(42);
   MVA_BDT_Train_S__4->GetZaxis()->SetTitleOffset(1);
   MVA_BDT_Train_S__4->GetZaxis()->SetTitleFont(42);
   MVA_BDT_Train_S__4->Draw("e1same");
   
   TH1D *MVA_BDT_Train_B__5 = new TH1D("MVA_BDT_Train_B__5","MVA_BDT_Train_B",40,-0.3467285,0.3632324);
   training->Project("MVA_BDT_Train_B__5", "BDT","classID==1");
   //MVA_BDT_Train_B__5->Scale(1.0/MVA_BDT_Train_B__5->Integral());
   //MVA_BDT_Train_B__5->Add(MVA_BDT_Train_S__4);
   MVA_BDT_Train_B__5->Scale(1.0/MVA_BDT_Train_B__5->Integral());

   MVA_BDT_Train_B__5->SetLineColor(2);
   MVA_BDT_Train_B__5->SetMarkerColor(2);
   MVA_BDT_Train_B__5->SetMarkerStyle(20);
   MVA_BDT_Train_B__5->SetMarkerSize(0.7);
   MVA_BDT_Train_B__5->GetXaxis()->SetLabelFont(42);
   MVA_BDT_Train_B__5->GetXaxis()->SetTitleOffset(1);
   MVA_BDT_Train_B__5->GetXaxis()->SetTitleFont(42);
   MVA_BDT_Train_B__5->GetYaxis()->SetLabelFont(42);
   MVA_BDT_Train_B__5->GetYaxis()->SetTitleFont(42);
   MVA_BDT_Train_B__5->GetZaxis()->SetLabelFont(42);
   MVA_BDT_Train_B__5->GetZaxis()->SetTitleOffset(1);
   MVA_BDT_Train_B__5->GetZaxis()->SetTitleFont(42);
   MVA_BDT_Train_B__5->Draw("e1same");


   //**************************************************************

   TH1D *hData = new TH1D("hData","Data",40,-0.3467285,0.3632324);
   pDVCS->Project("hData", "_strip_Nuc_BDT", cut_NP);

   hData->Scale(1.0/hData->Integral());
   hData->SetLineColor(kBlack);
   hData->SetFillColor(kBlack);
   hData->SetFillStyle(3554);

   hData->SetMarkerColor(kBlack);
   hData->SetMarkerStyle(20);
   hData->SetMarkerSize(0.7);
   hData->GetXaxis()->SetLabelFont(42);
   hData->GetXaxis()->SetTitleOffset(1);
   hData->GetXaxis()->SetTitleFont(42);
   hData->GetYaxis()->SetLabelFont(42);
   hData->GetYaxis()->SetTitleFont(42);
   hData->GetZaxis()->SetLabelFont(42);
   hData->GetZaxis()->SetTitleOffset(1);
   hData->GetZaxis()->SetTitleFont(42);
   hData->Draw("histsame");

   //****************************************************
   
   TH2F *frameBDT__6 = new TH2F("frameBDT__6","Classifier output",500,-0.3467285,0.3632324,500,0,0.2);
   frameBDT__6->SetStats(0);
   frameBDT__6->SetLineWidth(2);
   frameBDT__6->SetMarkerStyle(21);
   frameBDT__6->SetMarkerSize(0.3);
   frameBDT__6->GetXaxis()->SetTitle("BDT response");
   frameBDT__6->GetXaxis()->SetLabelOffset(0.012);
   frameBDT__6->GetXaxis()->SetLabelSize(0.04);
   frameBDT__6->GetXaxis()->SetTitleSize(0.045);
   frameBDT__6->GetXaxis()->SetTitleOffset(1.25);
   frameBDT__6->GetYaxis()->SetTitle("(1/N) dN^{ }/^{ }dx");
   frameBDT__6->GetYaxis()->SetLabelOffset(0.012);
   frameBDT__6->GetYaxis()->SetLabelSize(0.04);
   frameBDT__6->GetYaxis()->SetTitleSize(0.045);
   frameBDT__6->GetYaxis()->SetTitleOffset(1.2);
   frameBDT__6->GetZaxis()->SetLabelSize(0.04);
   frameBDT__6->GetZaxis()->SetTitleSize(0.04);
   frameBDT__6->GetZaxis()->SetTitleOffset(1);
   frameBDT__6->Draw("sameaxis");

   
   TPaveText *pt = new TPaveText(0.01,0.9355405,0.71,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);

   ci = TColor::GetColor("#5d6b7d");
   pt->SetFillColor(ci);

   ci = TColor::GetColor("#7d8b9d");
   pt->SetLineColor(ci);
   pt->SetTextColor(0);


   //pt->Draw();
   canvas1->Modified();
   canvas1->cd();
   canvas1->SetSelected(canvas1);
   canvas1->Print("Summary_Plots/BDT_Score_P_single.pdf");

   delete canvas1;
   delete frameBDT__1; 
   delete leg;
   delete MVA_BDT_Train_S__4; 
   delete MVA_BDT_Train_B__5; 
   delete hData;
   delete frameBDT__6; 
   delete pt;

  }



void Comparison_2(TTree* pDVCS_NP, TTree* pDVCS_NP_bkg){
  TCanvas *c1 = new TCanvas("c1","Histograms",1000,1000);
  c1->Divide(2,2);
  gStyle->SetOptStat(0);

  TChain *pDVCS_P= new TChain("pDVCS");
  TChain *pDVCS_P_bkg= new TChain("pDVCS");
  TChain *pDVCS_Sim= new TChain("pDVCS");

  pDVCS_P->Add("/work/clas12/jsalvg/pass2_RGA-Analysis/inb/P_BSA/Analysis/Merged_Data.root");
  pDVCS_Sim->Add("/work/clas12/jsalvg/pass2_RGA-Analysis/inb/P_BSA/Analysis/Merged_DVCS.root");
  
  for(int i=1; i<=NBins; i++)
  {
  	pDVCS_P_bkg->Add(Form("/work/clas12/jsalvg/pass2_RGA-Analysis/inb/P_BSA/Analysis/bin_%i/TMostafa_pi0.root",i));
  }

  double factor=1;
  
  TH1F *hist1c_P = new TH1F("hist1c_P","Q^{2} (GeV^{2})",50,0,8);
  TH1F *hist2c_P = new TH1F("hist2c_P","x_{B}",50,0,1);
  TH1F *hist3c_P = new TH1F("hist3c_P","t (GeV^{2})",30,-1.0,0);
  TH1F *hist4c_P = new TH1F("hist4c_P","M_{e#gamma}^{2} (GeV)",100,0,3);
  TH1F *hist4c_Sim = new TH1F("hist4c_Sim","M_{e#gamma}^{2} (GeV)",100,0,3);
  
  TH1F *hist1c_P_bkg = new TH1F("hist1c_P_bkg","Q^{2} (GeV^{2})",50,0,8);
  TH1F *hist2c_P_bkg = new TH1F("hist2c_P_bkg","x_{B}",50,0,1);
  TH1F *hist3c_P_bkg = new TH1F("hist3c_P_bkg","t (GeV^{2})",30,-1.0,0);
  TH1F *hist4c_P_bkg = new TH1F("hist4c_P_bkg","M_{e#gamma}^{2} (GeV)",100,0,3);

  TH1F *hist1c_NP = new TH1F("hist1c_NP","Q^{2} (GeV^{2})",50,0,8);
  TH1F *hist2c_NP = new TH1F("hist2c_NP","x_{B}",50,0,1);
  TH1F *hist3c_NP = new TH1F("hist3c_NP","t (GeV^{2})",30,-1.0,0);
  TH1F *hist4c_NP = new TH1F("hist4c_NP","M_{e#gamma}^{2} (GeV)",100,0,3);
  
  TH1F *hist1c_NP_bkg = new TH1F("hist1c_NP_bkg","Q^{2} (GeV^{2})",50,0,8);
  TH1F *hist2c_NP_bkg = new TH1F("hist2c_NP_bkg","x_{B}",50,0,1);
  TH1F *hist3c_NP_bkg = new TH1F("hist3c_NP_bkg","t (GeV^{2})",30,-1.0,0);
  TH1F *hist4c_NP_bkg = new TH1F("hist4c_NP_bkg","M_{e#gamma}^{2} (GeV)",100,0,3);
  
  //Variables to plot

  const char *p1="strip_Q2";
  const char *p2="strip_Xbj";
  const char *p3="t_Ph";
  const char *p4="mm2_eg";
  const char *p5="strip_Xbj:strip_Q2";
  
  pDVCS_P->Project("hist1c_P", p1, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist2c_P", p2, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist3c_P", p3, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist4c_P", p4, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_Sim->Project("hist4c_Sim", p4, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  
  pDVCS_P_bkg->Project("hist1c_P_bkg", p1, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist2c_P_bkg", p2, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist3c_P_bkg", p3, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist4c_P_bkg", p4, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));

  std::cout<<"Number of entries Data/bkg "<<hist1c_P->Integral()<<" "<<hist1c_P_bkg->Integral()<<endl;
  
  pDVCS_NP->Project("hist1c_NP", p1, cut_NP + TCut(Form("abs(t_Ph/strip_Q2)<1 && N_Ph<3 && _strip_Nuc_BDT_SIDIS > %f", BDT_cut_SIDIS)) + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));
  pDVCS_NP->Project("hist2c_NP", p2, cut_NP + TCut(Form("abs(t_Ph/strip_Q2)<1 && N_Ph<3 && _strip_Nuc_BDT_SIDIS > %f", BDT_cut_SIDIS)) + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));
  pDVCS_NP->Project("hist3c_NP", p3, cut_NP + TCut(Form("abs(t_Ph/strip_Q2)<1 && N_Ph<3 && _strip_Nuc_BDT_SIDIS > %f", BDT_cut_SIDIS)) + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));
  pDVCS_NP->Project("hist4c_NP", p4, cut_NP + TCut(Form("abs(t_Ph/strip_Q2)<1 && N_Ph<3 && _strip_Nuc_BDT_SIDIS > %f", BDT_cut_SIDIS)) + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));

  pDVCS_NP_bkg->Project("hist1c_NP_bkg", p1, (cut_NP + TCut(Form("abs(t_Ph/strip_Q2)<1 && N_Ph<3 && _strip_Nuc_BDT_SIDIS > %f", BDT_cut_SIDIS)) + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02")) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist2c_NP_bkg", p2, (cut_NP + TCut(Form("abs(t_Ph/strip_Q2)<1 && N_Ph<3 && _strip_Nuc_BDT_SIDIS > %f", BDT_cut_SIDIS)) + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02")) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist3c_NP_bkg", p3, (cut_NP + TCut(Form("abs(t_Ph/strip_Q2)<1 && N_Ph<3 && _strip_Nuc_BDT_SIDIS > %f", BDT_cut_SIDIS)) + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02")) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist4c_NP_bkg", p4, (cut_NP + TCut(Form("abs(t_Ph/strip_Q2)<1 && N_Ph<3 && _strip_Nuc_BDT_SIDIS > %f", BDT_cut_SIDIS)) + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02")) * TCut("Weight"));

  std::cout<<"Number of entries Data/bkg NP "<<hist4c_NP->Integral()<<" "<<hist4c_NP_bkg->Integral()<<endl;

  Apply_conf(hist1c_P);
  Apply_conf(hist2c_P);
  Apply_conf(hist3c_P);
  Apply_conf(hist4c_P);

  Apply_conf(hist1c_NP);
  Apply_conf(hist2c_NP);
  Apply_conf(hist3c_NP);
  Apply_conf(hist4c_NP);

  Apply_conf(hist1c_P_bkg);
  Apply_conf(hist2c_P_bkg);
  Apply_conf(hist3c_P_bkg);
  Apply_conf(hist4c_P_bkg);

  Apply_conf(hist1c_NP_bkg);
  Apply_conf(hist2c_NP_bkg);
  Apply_conf(hist3c_NP_bkg);
  Apply_conf(hist4c_NP_bkg);


  c1->cd(1);
  //gPad->SetLogy();
  hist1c_NP->SetLineColor(kBlue);
  hist1c_NP->Draw("HIST");
  hist1c_P->SetLineColor(kRed);
  hist1c_P->Draw("HIST, SAME");

  auto legend = new TLegend(0.6,0.6,0.9,0.9);
  legend->AddEntry(hist4c_P,"with proton","lp");
  legend->AddEntry(hist4c_Sim,"DVCS MC","lp");
  legend->AddEntry(hist4c_NP,"without proton","lp");
  legend->Draw();

  
  c1->cd(2);
  //gPad->SetLogy();
  hist2c_NP->SetLineColor(kBlue);
  hist2c_NP->Draw("HIST");
  hist2c_P->SetLineColor(kRed);
  hist2c_P->Draw("HIST,SAME");


  c1->cd(3);
  //gPad->SetLogy();
  hist3c_NP->SetLineColor(kBlue);
  hist3c_NP->Draw("HIST");
  hist3c_P->SetLineColor(kRed);
  hist3c_P->Draw("HIST,SAME");

    
  c1->cd(4);
  hist4c_P->SetLineColor(kRed);
  hist4c_NP->SetLineColor(kBlue);
  //hist4c_P->Scale(1.0/hist4c_P->Integral());
  //hist4c_NP->Scale(1.0/hist4c_NP->Integral());
  hist4c_P->Draw("HIST");
  hist4c_NP->Draw("HIST,SAME");
  
  // input->Close();
  
  c1->Print("Summary_Plots/Comparison_before_bkg.pdf");


  hist1c_P->Add(hist1c_P, hist1c_P_bkg, 1.0, -1.0);
  hist2c_P->Add(hist2c_P, hist2c_P_bkg, 1.0, -1.0);
  hist3c_P->Add(hist3c_P, hist3c_P_bkg, 1.0, -1.0);
  hist4c_P->Add(hist4c_P, hist4c_P_bkg, 1.0, -1.0);

  hist1c_NP->Add(hist1c_NP, hist1c_NP_bkg, 1.0, -1.0);
  hist2c_NP->Add(hist2c_NP, hist2c_NP_bkg, 1.0, -1.0);
  hist3c_NP->Add(hist3c_NP, hist3c_NP_bkg, 1.0, -1.0);
  hist4c_NP->Add(hist4c_NP, hist4c_NP_bkg, 1.0, -1.0);

  hist1c_NP->SetMinimum(0);
  hist2c_NP->SetMinimum(0);
  hist3c_NP->SetMinimum(0);
  hist4c_NP->SetMinimum(0);

  hist1c_P->SetMinimum(0);
  hist2c_P->SetMinimum(0);
  hist3c_P->SetMinimum(0);
  hist4c_P->SetMinimum(0);

  c1->cd(1);
  c1->cd(1)->SetLeftMargin(0.15);
  c1->cd(1)->SetBottomMargin(0.15);
  //gPad->SetLogy();
  hist1c_NP->SetLineColor(kBlue);
  hist1c_NP->Draw("HIST");
  hist1c_P->SetLineColor(kRed);
  hist1c_P->Draw("HIST, SAME");
  legend->Draw();
  
  c1->cd(2);
  c1->cd(2)->SetLeftMargin(0.15);
  c1->cd(2)->SetBottomMargin(0.15);
  //gPad->SetLogy();
  hist2c_NP->SetLineColor(kBlue);
  hist2c_NP->Draw("HIST");
  hist2c_P->SetLineColor(kRed);
  hist2c_P->Draw("HIST,SAME");


  c1->cd(3);
  c1->cd(3)->SetLeftMargin(0.15);
  c1->cd(3)->SetBottomMargin(0.15);
  //gPad->SetLogy();
  hist3c_NP->SetLineColor(kBlue);
  hist3c_NP->Draw("HIST");
  hist3c_P->SetLineColor(kRed);
  hist3c_P->Draw("HIST,SAME");

    
  c1->cd(4);
  c1->cd(4)->SetLeftMargin(0.15);
  c1->cd(4)->SetBottomMargin(0.15);
  hist4c_P->SetLineColor(kRed);
  hist4c_NP->SetLineColor(kBlue);
  hist4c_P->Scale(1.0/hist4c_P->Integral());
  hist4c_Sim->Scale(1.0/hist4c_Sim->Integral());
  hist4c_NP->Scale(1.0/hist4c_NP->Integral());
  hist4c_NP->Draw("HIST");
  hist4c_P->Draw("HIST,SAME");
  hist4c_Sim->Draw("HIST,SAME");
  
  // input->Close();
  
  c1->Print("Summary_Plots/Comparison_aft_bkg.pdf");

  delete c1;
  delete pDVCS_P;
  delete pDVCS_P_bkg;
  delete hist1c_P;
  delete hist2c_P;
  delete hist3c_P;
  delete hist4c_P;
  delete hist1c_P_bkg;
  delete hist2c_P_bkg;
  delete hist3c_P_bkg;
  delete hist4c_P_bkg;
  delete hist1c_NP;
  delete hist2c_NP;
  delete hist3c_NP;
  delete hist4c_NP;
  delete hist1c_NP_bkg;
  delete hist2c_NP_bkg;
  delete hist3c_NP_bkg;
  delete hist4c_NP_bkg;
  delete legend;
}
    

void Kinematics(TTree* pDVCS, TTree* pDVCS_bkg){
  TCanvas *c1 =new  TCanvas("h1","Histograms",1500,1000);
  c1->Divide(3,2);
  gStyle->SetOptStat(0);

  TH2F *histeT = new TH2F("histeT", "Electron",100,0,40,100,0,8.5);
  TH2F *histgT = new TH2F("histgT", "Photon",100,0,35,100,0,10);
  TH2F *histNT = new TH2F("histNT", "Proton",100,0,120,100,0,4.5);
  TH2F *histeP = new TH2F("histeP", "Electron",100,-200,200,100,0,8.5);
  TH2F *histgP = new TH2F("histgP", "Photon",100,-200,200,100,0,10);
  TH2F *histNP = new TH2F("histNP", "Proton",100,-200,200,100,0,4.5);

  TH2F *histeT_bkg = new TH2F("histeT_bkg", "Electron",100,0,40,100,0,8.5);
  TH2F *histgT_bkg = new TH2F("histgT_bkg", "Photon",100,0,35,100,0,10);
  TH2F *histNT_bkg = new TH2F("histNT_bkg", "Proton",100,0,120,100,0,4.5);
  TH2F *histeP_bkg = new TH2F("histeP_bkg", "Electron",100,-200,200,100,0,8.5);
  TH2F *histgP_bkg = new TH2F("histgP_bkg", "Photon",100,-200,200,100,0,10);
  TH2F *histNP_bkg = new TH2F("histNP_bkg", "Proton",100,-200,200,100,0,4.5);

  pDVCS->Project("histeT", "strip_El_P:strip_El_Theta",cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));
  pDVCS->Project("histgT", "strip_Ph_P:strip_Ph_Theta",cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));
  pDVCS->Project("histNT", "strip_Nuc_P:strip_Nuc_Theta",cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));
  pDVCS->Project("histeP", "strip_El_P:strip_El_Phi",cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));
  pDVCS->Project("histgP", "strip_Ph_P:strip_Ph_Phi",cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));
  pDVCS->Project("histNP", "strip_Nuc_P:strip_Nuc_Phi",cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"));

  pDVCS_bkg->Project("histeT_bkg", "strip_El_P:strip_El_Theta",(cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"))*TCut("Weight"));
  pDVCS_bkg->Project("histgT_bkg", "strip_Ph_P:strip_Ph_Theta",(cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"))*TCut("Weight"));
  pDVCS_bkg->Project("histNT_bkg", "strip_Nuc_P:strip_Nuc_Theta",(cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"))*TCut("Weight"));
  pDVCS_bkg->Project("histeP_bkg", "strip_El_P:strip_El_Phi",(cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"))*TCut("Weight"));
  pDVCS_bkg->Project("histgP_bkg", "strip_Ph_P:strip_Ph_Phi",(cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"))*TCut("Weight"));
  pDVCS_bkg->Project("histNP_bkg", "strip_Nuc_P:strip_Nuc_Phi",(cut_NP + TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02"))*TCut("Weight"));

  
  histeT->Add(histeT, histeT_bkg, 1.0, -1.0);
  histgT->Add(histgT, histgT_bkg, 1.0, -1.0);
  histNT->Add(histNT, histNT_bkg, 1.0, -1.0);
  histeP->Add(histeP, histeP_bkg, 1.0, -1.0);
  histgP->Add(histgP, histgP_bkg, 1.0, -1.0);
  histNP->Add(histNP, histNP_bkg, 1.0, -1.0);
  
  Apply_conf(histeT);
  Apply_conf(histgT);
  Apply_conf(histNT);
  Apply_conf(histeP);
  Apply_conf(histgP);
  Apply_conf(histNP);

  c1->cd(1);
  gPad->SetLogz();
  histeT->Draw("COLZ");
  histeT->GetXaxis()->SetTitle("Polar angle (deg)");
  //histeT->GetXaxis()->SetTitle("#theta (deg)");
  //histeT->GetYaxis()->SetTitle("#bf{k}'(GeV)");
 
  c1->cd(2);
  gPad->SetLogz();
  histgT->Draw("COLZ");
  histgT->GetXaxis()->SetTitle("Polar angle (deg)");
  //histgT->GetXaxis()->SetTitle("#theta (deg)");
  //histgT->GetYaxis()->SetTitle("#bf{q}'(GeV)");
  
  c1->cd(3);
  gPad->SetLogz();
  histNT->Draw("COLZ");
  histNT->GetXaxis()->SetTitle("Polar angle (deg)");
  //histNT->GetXaxis()->SetTitle("#theta (deg)");
  //histNT->GetYaxis()->SetTitle("#bf{p}'(GeV)");

  c1->cd(4);
  gPad->SetLogz();
  histeP->Draw("COLZ");
  histeP->GetXaxis()->SetTitle("Azimuthal angle (deg)");
  //histeP->GetXaxis()->SetTitle("#phi (deg)");
  //histeP->GetYaxis()->SetTitle("#bf{k}'(GeV)");

  c1->cd(5);
  gPad->SetLogz();
  histgP->Draw("COLZ");
  histgP->GetXaxis()->SetTitle("Azimuthal angle (deg)");
  //histgP->GetXaxis()->SetTitle("#phi (deg)");
  //histgP->GetYaxis()->SetTitle("#bf{q}'(GeV)");
 
  c1->cd(6);
  gPad->SetLogz();
  histNP->Draw("COLZ");
  histNP->GetXaxis()->SetTitle("Azimuthal angle (deg)");
  //histNP->GetXaxis()->SetTitle("#phi (deg)");
  //histNP->GetYaxis()->SetTitle("#bf{p}'(GeV)");
  //input->Close();

  c1->Print("Summary_Plots/Kinematics.pdf");

  delete c1;
  delete histeT;
  delete histgT;
  delete histNT;
  delete histeP;
  delete histgP;
  delete histNP;
  delete histeT_bkg;
  delete histgT_bkg;
  delete histNT_bkg;
  delete histeP_bkg;
  delete histgP_bkg;
  delete histNP_bkg;
}


void Kinematics_2_single(TTree* pDVCS, std::string set, int topology)
{
  TCanvas *c1 =new  TCanvas("h1","Histograms",1500,1000);
  c1->Divide(3,2);
  gStyle->SetOptStat(0);
    
  //TFile *input = new TFile("Raw_Data_Sample.root", "read");

  TH2F *histeT = new TH2F("histeT", "Electron",100,-0.4, 0.4,100, 0, 40);
  TH2F *histgT = new TH2F("histgT", "Photon",100,-0.4, 0.4,100, 0, 35);
  TH2F *histNT = new TH2F("histNT", "Proton",100,-0.4, 0.4,100, 0, 120);
  TH2F *histeP = new TH2F("histeP", "Electron",100,-0.4, 0.4,100, -200, 200);
  TH2F *histgP = new TH2F("histgP", "Photon",100,-0.4, 0.4,100, -200, 200);
  TH2F *histNP = new TH2F("histNP", "Proton",100,-0.4, 0.4,100, -200, 200);

  TCut cut_top;
  switch (topology)
  {
  case 1:
    cut_top = TCut("");
    break;
  case 2:
    cut_top = TCut("strip_Ph_status<2000");
    break;
  case 3:
    cut_top = TCut("strip_Ph_status>2000");
    break;
  }
  
  pDVCS->Project("histeT", "strip_El_Theta:_strip_Nuc_BDT",cut_NP + cut_top);
  pDVCS->Project("histgT", "strip_Ph_Theta:_strip_Nuc_BDT",cut_NP + cut_top);
  pDVCS->Project("histNT", "strip_Nuc_Theta:_strip_Nuc_BDT",cut_NP + cut_top);

  pDVCS->Project("histeP", "strip_El_Phi:_strip_Nuc_BDT",cut_NP + cut_top);
  pDVCS->Project("histgP", "strip_Ph_Phi:_strip_Nuc_BDT",cut_NP + cut_top);
  pDVCS->Project("histNP", "strip_Nuc_Phi:_strip_Nuc_BDT",cut_NP + cut_top);

  Apply_conf(histeT);
  Apply_conf(histgT);
  Apply_conf(histNT);
  Apply_conf(histeP);
  Apply_conf(histgP);
  Apply_conf(histNP);

  c1->cd(1);
  histeT->Draw("COLZ");
  histeT->GetYaxis()->SetTitle("Polar angle (deg)");
 
  c1->cd(2);
  histgT->Draw("COLZ");
  histgT->GetYaxis()->SetTitle("Polar angle (deg)");
  
  c1->cd(3);
  histNT->Draw("COLZ");
  histNT->GetYaxis()->SetTitle("Polar angle (deg)");

  c1->cd(4);
  histeP->Draw("COLZ");
  histeP->GetYaxis()->SetTitle("Azimuthal angle (deg)");

  c1->cd(5);
  histgP->Draw("COLZ");
  histgP->GetYaxis()->SetTitle("Azimuthal angle (deg)");
 
  c1->cd(6);
  histNP->Draw("COLZ");
  histNP->GetYaxis()->SetTitle("Azimuthal angle (deg)");
  //input->Close();

  c1->Print(Form("Summary_Plots/Kinematics_BDT_%s_%i.pdf",set.c_str(),topology));

  delete histeT;
  delete histgT;
  delete histNT;
  delete histeP;
  delete histgP;
  delete histNP;
  delete c1;
}

void Kinematics_2(TTree* Data, TTree* DVCS, TTree* Pi0)
{
Kinematics_2_single(Data, "Quality_Data",1);
Kinematics_2_single(Data, "Quality_Data",2);
Kinematics_2_single(Data, "Quality_Data",3);

Kinematics_2_single(DVCS, "DVCS",1);
Kinematics_2_single(DVCS, "DVCS",2);
Kinematics_2_single(DVCS, "DVCS",3);

Kinematics_2_single(Pi0, "Pi0",1);
Kinematics_2_single(Pi0, "Pi0",2);
Kinematics_2_single(Pi0, "Pi0",3);
}


void Kin_Comparison_2(TTree* pDVCS_NP, TTree* pDVCS_NP_bkg)
{
  TCanvas *c1 = new TCanvas("c1","Histograms",1000,1000);
  c1->Divide(3,3);
  gStyle->SetOptStat(0);

  TChain *pDVCS_P= new TChain("pDVCS");
  TChain *pDVCS_P_bkg= new TChain("pDVCS");
  
  for(int i=1; i<=96; i++)
  {
  	pDVCS_P->Add(Form("/work/clas12/jsalvg/pass2_RGA-Analysis/inb/P_BSA/Analysis/bin_%i/Tested_Quality_Data.root",i));
  	pDVCS_P_bkg->Add(Form("/work/clas12/jsalvg/pass2_RGA-Analysis/inb/P_BSA/Analysis/bin_%i/TMostafa_pi0.root",i));
}

double factor=1;
  
  TH1F *hist1c_P = new TH1F("hist1c_P","Electron",50,0,10);
  TH1F *hist2c_P = new TH1F("hist2c_P","Photon",50,0,10);
  TH1F *hist3c_P = new TH1F("hist3c_P","Proton",50,0, 2.0);
  TH1F *hist4c_P = new TH1F("hist4c_P","Electron",50,5,40);
  TH1F *hist5c_P = new TH1F("hist5c_P","Photon",50,0,35);
  TH1F *hist6c_P = new TH1F("hist6c_P","Proton",50, 5, 150);
  TH1F *hist7c_P = new TH1F("hist7c_P","Electron",50,-180,180);
  TH1F *hist8c_P = new TH1F("hist8c_P","Photon",50,-180,180);
  TH1F *hist9c_P = new TH1F("hist9c_P","Proton",50,-180,180);
  
  TH1F *hist1c_P_bkg = new TH1F("hist1c_P_bkg","",50,0,10);
  TH1F *hist2c_P_bkg = new TH1F("hist2c_P_bkg","",50,0,10);
  TH1F *hist3c_P_bkg = new TH1F("hist3c_P_bkg","",50,0, 2.0);
  TH1F *hist4c_P_bkg = new TH1F("hist4c_P_bkg","",50,5,40);
  TH1F *hist5c_P_bkg = new TH1F("hist5c_P_bkg","",50,0,35);
  TH1F *hist6c_P_bkg = new TH1F("hist6c_P_bkg","",50, 5, 150);
  TH1F *hist7c_P_bkg = new TH1F("hist7c_P_bkg","",50,-180,180);
  TH1F *hist8c_P_bkg = new TH1F("hist8c_P_bkg","",50,-180,180);
  TH1F *hist9c_P_bkg = new TH1F("hist9c_P_bkg","",50,-180,180);

  TH1F *hist1c_NP = new TH1F("hist1c_NP","Electron",50,0,10);
  TH1F *hist2c_NP = new TH1F("hist2c_NP","Photon",50,0,10);
  TH1F *hist3c_NP = new TH1F("hist3c_NP","Proton",50,0, 2.0);
  TH1F *hist4c_NP = new TH1F("hist4c_NP","Electron",50,5,40);
  TH1F *hist5c_NP = new TH1F("hist5c_NP","Photon",50,0,35);
  TH1F *hist6c_NP = new TH1F("hist6c_NP","Proton",50, 5, 150);
  TH1F *hist7c_NP = new TH1F("hist7c_NP","Electron",50,-180,180);
  TH1F *hist8c_NP = new TH1F("hist8c_NP","Photon",50,-180,180);
  TH1F *hist9c_NP = new TH1F("hist9c_NP","Proton",50,-180,180);
  
  TH1F *hist1c_NP_bkg = new TH1F("hist1c_NP_bkg","",50,0,10);
  TH1F *hist2c_NP_bkg = new TH1F("hist2c_NP_bkg","",50,0,10);
  TH1F *hist3c_NP_bkg = new TH1F("hist3c_NP_bkg","",50,0, 2.0);
  TH1F *hist4c_NP_bkg = new TH1F("hist4c_NP_bkg","",50,5,40);
  TH1F *hist5c_NP_bkg = new TH1F("hist5c_NP_bkg","",50,0,35);
  TH1F *hist6c_NP_bkg = new TH1F("hist6c_NP_bkg","",50, 5, 150);
  TH1F *hist7c_NP_bkg = new TH1F("hist7c_NP_bkg","",50,-180,180);
  TH1F *hist8c_NP_bkg = new TH1F("hist8c_NP_bkg","",50,-180,180);
  TH1F *hist9c_NP_bkg = new TH1F("hist9c_NP_bkg","",50,-180,180);
    
  //Variables to plot

  const char *p1="strip_El_P";
  const char *p2="strip_Ph_P";
  const char *p3="strip_Nuc_P";
  const char *p4="strip_El_Theta";
  const char *p5="strip_Ph_Theta";
  const char *p6="strip_Nuc_Theta";
  const char *p7="strip_El_Phi";
  const char *p8="strip_Ph_Phi";
  const char *p9="strip_Nuc_Phi";
  
  pDVCS_P->Project("hist1c_P", p1, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist2c_P", p2, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist3c_P", p3, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist4c_P", p4, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist5c_P", p5, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist6c_P", p6, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist7c_P", p7, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist8c_P", p8, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  pDVCS_P->Project("hist9c_P", p9, cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P)));
  
  pDVCS_P_bkg->Project("hist1c_P_bkg", p1, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist2c_P_bkg", p2, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist3c_P_bkg", p3, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist4c_P_bkg", p4, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist5c_P_bkg", p5, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist6c_P_bkg", p6, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist7c_P_bkg", p7, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist8c_P_bkg", p8, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));
  pDVCS_P_bkg->Project("hist9c_P_bkg", p9, (cut_P + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut_P))) * TCut("Weight"));

  hist1c_P->Add(hist1c_P, hist1c_P_bkg, 1.0, -1.0);
  hist2c_P->Add(hist2c_P, hist2c_P_bkg, 1.0, -1.0);
  hist3c_P->Add(hist3c_P, hist3c_P_bkg, 1.0, -1.0);
  hist4c_P->Add(hist4c_P, hist4c_P_bkg, 1.0, -1.0);
  hist5c_P->Add(hist5c_P, hist5c_P_bkg, 1.0, -1.0);
  hist6c_P->Add(hist6c_P, hist6c_P_bkg, 1.0, -1.0);
  hist7c_P->Add(hist7c_P, hist7c_P_bkg, 1.0, -1.0);
  hist8c_P->Add(hist8c_P, hist8c_P_bkg, 1.0, -1.0);
  hist9c_P->Add(hist9c_P, hist9c_P_bkg, 1.0, -1.0);
  
  pDVCS_NP->Project("hist1c_NP", p1, cut_NP && Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));
  pDVCS_NP->Project("hist2c_NP", p2, cut_NP && Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));
  pDVCS_NP->Project("hist3c_NP", p3, cut_NP && Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));
  pDVCS_NP->Project("hist4c_NP", p4, cut_NP && Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));
  pDVCS_NP->Project("hist5c_NP", p5, cut_NP && Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));
  pDVCS_NP->Project("hist6c_NP", p6, cut_NP && Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));
  pDVCS_NP->Project("hist7c_NP", p7, cut_NP && Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));
  pDVCS_NP->Project("hist8c_NP", p8, cut_NP && Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));
  pDVCS_NP->Project("hist9c_NP", p9, cut_NP && Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));

  pDVCS_NP_bkg->Project("hist1c_NP_bkg", p1, (cut_NP + TCut(Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS))) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist2c_NP_bkg", p2, (cut_NP + TCut(Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS))) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist3c_NP_bkg", p3, (cut_NP + TCut(Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS))) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist4c_NP_bkg", p4, (cut_NP + TCut(Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS))) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist5c_NP_bkg", p5, (cut_NP + TCut(Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS))) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist6c_NP_bkg", p6, (cut_NP + TCut(Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS))) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist7c_NP_bkg", p7, (cut_NP + TCut(Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS))) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist8c_NP_bkg", p8, (cut_NP + TCut(Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS))) * TCut("Weight"));
  pDVCS_NP_bkg->Project("hist9c_NP_bkg", p9, (cut_NP + TCut(Form("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02 && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS))) * TCut("Weight"));

  hist1c_NP->Add(hist1c_NP, hist1c_NP_bkg, 1.0, -1.0);
  hist2c_NP->Add(hist2c_NP, hist2c_NP_bkg, 1.0, -1.0);
  hist3c_NP->Add(hist3c_NP, hist3c_NP_bkg, 1.0, -1.0);
  hist4c_NP->Add(hist4c_NP, hist4c_NP_bkg, 1.0, -1.0);
  hist5c_NP->Add(hist5c_NP, hist5c_NP_bkg, 1.0, -1.0);
  hist6c_NP->Add(hist6c_NP, hist6c_NP_bkg, 1.0, -1.0);
  hist7c_NP->Add(hist7c_NP, hist7c_NP_bkg, 1.0, -1.0);
  hist8c_NP->Add(hist8c_NP, hist8c_NP_bkg, 1.0, -1.0);
  hist9c_NP->Add(hist9c_NP, hist9c_NP_bkg, 1.0, -1.0);

  Apply_conf(hist1c_P);
  Apply_conf(hist2c_P);
  Apply_conf(hist3c_P);
  Apply_conf(hist4c_P);
  Apply_conf(hist5c_P);
  Apply_conf(hist6c_P);
  Apply_conf(hist7c_P);
  Apply_conf(hist8c_P);
  Apply_conf(hist9c_P);

  Apply_conf(hist1c_NP);
  Apply_conf(hist2c_NP);
  Apply_conf(hist3c_NP);
  Apply_conf(hist4c_NP);
  Apply_conf(hist5c_NP);
  Apply_conf(hist6c_NP);
  Apply_conf(hist7c_NP);
  Apply_conf(hist8c_NP);
  Apply_conf(hist9c_NP);

  Apply_conf(hist1c_P_bkg);
  Apply_conf(hist2c_P_bkg);
  Apply_conf(hist3c_P_bkg);
  Apply_conf(hist4c_P_bkg);
  Apply_conf(hist5c_P_bkg);
  Apply_conf(hist6c_P_bkg);
  Apply_conf(hist7c_P_bkg);
  Apply_conf(hist8c_P_bkg);
  Apply_conf(hist9c_P_bkg);

  Apply_conf(hist1c_NP_bkg);
  Apply_conf(hist2c_NP_bkg);
  Apply_conf(hist3c_NP_bkg);
  Apply_conf(hist4c_NP_bkg);
  Apply_conf(hist5c_NP_bkg);
  Apply_conf(hist6c_NP_bkg);
  Apply_conf(hist7c_NP_bkg);
  Apply_conf(hist8c_NP_bkg);
  Apply_conf(hist9c_NP_bkg);

  hist1c_P->GetXaxis()->SetTitle("Momentum (GeV)");
  hist2c_P->GetXaxis()->SetTitle("Momentum (GeV)");
  hist3c_P->GetXaxis()->SetTitle("Momentum (GeV)");
  hist4c_P->GetXaxis()->SetTitle("Polar angle (deg)");
  hist5c_P->GetXaxis()->SetTitle("Polar angle (deg)");
  hist6c_P->GetXaxis()->SetTitle("Polar angle (deg)");
  hist7c_P->GetXaxis()->SetTitle("Azimuthal angle (deg)");
  hist8c_P->GetXaxis()->SetTitle("Azimuthal angle (deg)");
  hist9c_P->GetXaxis()->SetTitle("Azimuthal angle (deg)");

  hist1c_NP->GetXaxis()->SetTitle("Momentum (GeV)");
  hist2c_NP->GetXaxis()->SetTitle("Momentum (GeV)");
  hist3c_NP->GetXaxis()->SetTitle("Momentum (GeV)");
  hist4c_NP->GetXaxis()->SetTitle("Polar angle (deg)");
  hist5c_NP->GetXaxis()->SetTitle("Polar angle (deg)");
  hist6c_NP->GetXaxis()->SetTitle("Polar angle (deg)");
  hist7c_NP->GetXaxis()->SetTitle("Azimuthal angle (deg)");
  hist8c_NP->GetXaxis()->SetTitle("Azimuthal angle (deg)");
  hist9c_NP->GetXaxis()->SetTitle("Azimuthal angle (deg)");


  c1->cd(1);
  hist1c_NP->SetLineColor(kBlue);
  hist1c_NP->Draw("HIST");
  hist1c_P->SetLineColor(kRed);
  hist1c_P->Draw("HIST, SAME");

  auto legend = new TLegend(0.6,0.6,0.9,0.9);
  legend->AddEntry(hist1c_P,"with proton","lp");
  legend->AddEntry(hist1c_NP,"without proton","lp");
  legend->Draw();

  
  c1->cd(2);
  hist2c_NP->SetLineColor(kBlue);
  hist2c_NP->Draw("HIST");
  hist2c_P->SetLineColor(kRed);
  hist2c_P->Draw("HIST,SAME");


  c1->cd(3);
  hist3c_NP->SetLineColor(kBlue);
  hist3c_NP->Draw("HIST");
  hist3c_P->SetLineColor(kRed);
  hist3c_P->Draw("HIST,SAME");

    
  c1->cd(4);
  hist4c_P->SetLineColor(kRed);
  hist4c_NP->SetLineColor(kBlue);
  hist4c_NP->Draw("HIST");
  hist4c_P->Draw("HIST,SAME");
  
  c1->cd(5);
  hist5c_P->SetLineColor(kRed);
  hist5c_NP->SetLineColor(kBlue);
  hist5c_NP->Draw("HIST");
  hist5c_P->Draw("HIST,SAME");

  c1->cd(6);
  hist6c_P->SetLineColor(kRed);
  hist6c_NP->SetLineColor(kBlue);
  hist6c_P->Draw("HIST");
  hist6c_NP->Draw("HIST,SAME");

  c1->cd(7);
  hist7c_P->SetLineColor(kRed);
  hist7c_NP->SetLineColor(kBlue);
  hist7c_NP->Draw("HIST");
  hist7c_P->Draw("HIST,SAME");

  c1->cd(8);
  hist8c_P->SetLineColor(kRed);
  hist8c_NP->SetLineColor(kBlue);
  hist8c_NP->Draw("HIST");
  hist8c_P->Draw("HIST,SAME");

  c1->cd(9);
  hist9c_P->SetLineColor(kRed);
  hist9c_NP->SetLineColor(kBlue);
  hist9c_NP->Draw("HIST");
  hist9c_P->Draw("HIST,SAME");
  
  c1->Print("Summary_Plots/Kin_Comparison_after_bkg.pdf");
  
  delete c1;
  delete hist1c_P;
  delete hist2c_P;
  delete hist3c_P;
  delete hist4c_P;
  delete hist5c_P;
  delete hist6c_P;
  delete hist7c_P;
  delete hist8c_P;
  delete hist9c_P;
  delete hist1c_P_bkg;
  delete hist2c_P_bkg;
  delete hist3c_P_bkg;
  delete hist4c_P_bkg;
  delete hist5c_P_bkg;
  delete hist6c_P_bkg;
  delete hist7c_P_bkg;
  delete hist8c_P_bkg;
  delete hist9c_P_bkg;
  delete hist1c_NP;
  delete hist2c_NP;
  delete hist3c_NP;
  delete hist4c_NP;
  delete hist5c_NP;
  delete hist6c_NP;
  delete hist7c_NP;
  delete hist8c_NP;
  delete hist9c_NP;
  delete hist1c_NP_bkg;
  delete hist2c_NP_bkg;
  delete hist3c_NP_bkg;
  delete hist4c_NP_bkg;
  delete hist5c_NP_bkg;
  delete hist6c_NP_bkg;
  delete hist7c_NP_bkg;
  delete hist8c_NP_bkg;
  delete hist9c_NP_bkg;
  delete pDVCS_P;
  delete pDVCS_P_bkg;
    }


    //Phase Space Plots
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
 
  return bins;  
}
void Line_conf(TLine*& line)
{
  line->SetLineWidth(2);
  line->SetLineColor(kBlack); 
  }
  
  
void Phase_Space(TTree* pDVCS, TTree* pDVCS_bkg)
{
  gStyle->SetOptStat(0);

  //TCut TheCut = cut_NP + TCut(Form("_strip_Nuc_BDT > %f && _strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1",BDT_cut_NP, BDT_cut_SIDIS));
  TCut TheCut = TCut("_strip_Nuc_BDT>get_bdt_event(strip_Xbj, strip_Q2, t_Ph) + 0.02") + cut_NP + TCut(Form("_strip_Nuc_BDT_SIDIS > %f && abs(t_Ph/strip_Q2)<1 && N_Ph<3 && t_Ph>-1", BDT_cut_SIDIS));

  // -----------------------------------------------------------------------------------------------
  //  Check data existence
  // -----------------------------------------------------------------------------------------------

  const int NBINSt=7;
  const int NBINSQ=5;
  const int NBINSx=5;

  std::vector<double> bins_t = Binning_1D(pDVCS, "t",NBINSt);
  std::vector<double> bins_Q = Binning_1D(pDVCS, "Q",NBINSQ);
  std::vector<double> bins_x = Binning_1D(pDVCS, "x",NBINSx);

  std::cout<<bins_t.size()-1<<" "<<bins_x.size()-1<<" "<<bins_Q.size()-1<<endl;

  // ---------------------------------------------------------------------------------------------
  // Create phase space plots
  // -----------------------------------------------------------------------------------------------

  TLine* line_t[NBINSt];
  TLine* line_Q[NBINSQ];
  TLine* line_xt[NBINSx];
  TLine* line_xQ[NBINSx];

  TH2F *Q2xB = new TH2F("Q2xB", "Q2xB", 100,0,1,100,0,13);
  TH2F *Q2xB_bkg = new TH2F("Q2xB_bkg", "Q2xB_bkg", 100,0,1,100,0,13);
  TH2F *mtxB = new TH2F("mtxB", "mtxB", 100,0,1,100,0,1);
  TH2F *mtxB_bkg = new TH2F("mtxB_bkg", "mtxB_bkg", 100,0,1,100,0,1);
 
  pDVCS->Project("Q2xB", "strip_Q2:strip_Xbj", TheCut);
  pDVCS->Project("mtxB", "-t_Ph:strip_Xbj", TheCut);
  pDVCS_bkg->Project("Q2xB_bkg", "strip_Q2:strip_Xbj", TheCut*TCut("Weight"));
  pDVCS_bkg->Project("mtxB_bkg", "-t_Ph:strip_Xbj", TheCut*TCut("Weight"));
  
  Q2xB->Add(Q2xB, Q2xB_bkg, 1.0, -1.0);
  mtxB->Add(mtxB, mtxB_bkg, 1.0, -1.0);

  Q2xB->SetTitle("; xB; Q^{2} (GeV^{2})");
  mtxB->SetTitle("; xB; -t (GeV^{2})");

  apply_conf2(Q2xB);
  apply_conf2(mtxB);
  Q2xB->SetMaximum(1e5);
  mtxB->SetMaximum(1e5);


  TCanvas* c2 = new TCanvas("c2", "c2",1000,700);
  gPad->SetLogz();

  mtxB->Draw("COLZ");
  for (UInt_t i = 0; i < NBINSt; ++i)
  {
    line_t[i] = new TLine(0,-1.0*bins_t.at(i),1,-1.0*bins_t.at(i));
    line_t[i]->SetLineColor(kBlack);
    line_t[i]->Draw("same");
  }
  for (UInt_t i = 0; i < NBINSx; ++i)
  {
    line_xt[i] = new TLine(bins_x.at(i),0,bins_x.at(i),1);
    line_xt[i]->SetLineColor(kBlack);
    line_xt[i]->Draw("same");
  }
  c2->Print("Summary_Plots/mtxB.pdf");

  Q2xB->Draw("COLZ");
  TF1* fa1[3];
  TLatex *th_edge[2];
  gPad->SetLogz();
  double xmax;
  double Q2inter;
  double theta;


  theta=40*TMath::Pi()/180;
  xmax=(378.92 * sin(theta/2)*sin(theta/2))/(227.84 - 224.72*cos(theta));
  fa1[0] = new TF1("fa1","4*0.938*10.6*10.6*x*sin([0]/2)*sin([0]/2)/(0.938*x + 2*10.6*sin([0]/2)*sin([0]/2))",0,xmax);
  fa1[0]->SetParameter(0,40*TMath::Pi()/180);
  fa1[0]->SetLineColor(kBlack);
  fa1[0]->SetLineWidth(2);
  fa1[0]->Draw("same");

  fa1[1] = new TF1("fa1","(4-0.938*0.938)/(1/x -1)",0,xmax);
  fa1[1]->SetLineColor(kBlack);
  fa1[1]->SetLineWidth(2);
  fa1[1]->Draw("same");

  Q2inter= fa1[0]->Eval(xmax);
  th_edge[0] = new TLatex(xmax+0.02,Q2inter,Form("#theta_{e}=%.2f#circ",40.));
  th_edge[0]->SetTextSize(0.04);
  th_edge[0]->Draw("same");

  fa1[2] = new TF1("fa1","4*0.938*10.6*10.6*x*sin([0]/2)*sin([0]/2)/(0.938*x + 2*10.6*sin([0]/2)*sin([0]/2))",0,xmax);
  fa1[2]->SetParameter(0,30*TMath::Pi()/180);
  theta=30*TMath::Pi()/180;
  xmax=(378.92 * sin(theta/2)*sin(theta/2))/(227.84 - 224.72*cos(theta));
  Q2inter= fa1[2]->Eval(xmax);
  th_edge[1] = new TLatex(xmax+0.02,Q2inter,"W=2 GeV");
  th_edge[1]->SetTextSize(0.04);
  th_edge[1]->Draw("same");
  

  for (UInt_t i = 0; i < NBINSQ; ++i)
  {
    line_Q[i] = new TLine(fa1[0]->GetX(bins_Q.at(i)), bins_Q.at(i), fa1[1]->GetX(bins_Q.at(i)),bins_Q.at(i));
    line_Q[i]->SetLineColor(kBlack);
    line_Q[i]->Draw("same");
  }
  for (UInt_t i = 0; i < NBINSx; ++i)
  {
    line_xQ[i] = new TLine(bins_x.at(i), fa1[1]->Eval(bins_x.at(i)), bins_x.at(i),fa1[0]->Eval(bins_x.at(i)));
    line_xQ[i]->SetLineColor(kBlack);
    line_xQ[i]->Draw("same");
  }

  TText* text1 = new TText(0.07,1.1,"1-7");
  TText* text2 = new TText(0.12,1.1,"8-14");
  TText* text3 = new TText(0.2 ,1.1,"15-21");
  TText* text4 = new TText(0.32,1.1,"22-26");

  TText* text5 = new TText(0.04,1.9,"27-33");
  TText* text6 = new TText(0.12,1.9,"34-40");
  TText* text7 = new TText(0.2 ,1.9,"41-47");
  TText* text8 = new TText(0.3 ,1.9,"48-52");

  TText* text9 = new TText(0.08 ,2.5,"53-59");
  TText* text10 = new TText(0.2,2.5,"60-66");
  TText* text11 = new TText(0.3,2.5,"67-71");
  TText* text12 = new TText(0.48,2.5,"72-73");

  TText* text13 = new TText(0.2 ,3.3,"74-80");
  TText* text14 = new TText(0.3 ,3.3,"81-85");
  TText* text15 = new TText(0.47,3.3,"86-87");

  TText* text16 = new TText(0.3,5.1,"88-92");
  TText* text17 = new TText(0.47,5.1,"93-94");

  text1->SetTextSize(0.025);
  text2->SetTextSize(0.025);
  text3->SetTextSize(0.025);
  text4->SetTextSize(0.025);
  text5->SetTextSize(0.025);
  text6->SetTextSize(0.025);
  text7->SetTextSize(0.025);
  text8->SetTextSize(0.025);
  text9->SetTextSize(0.025);
  text10->SetTextSize(0.025);
  text11->SetTextSize(0.025);
  text12->SetTextSize(0.025);
  text13->SetTextSize(0.025);
  text14->SetTextSize(0.025);
  text15->SetTextSize(0.025);
  text16->SetTextSize(0.025);
  text17->SetTextSize(0.025);

  text1->Draw("same");
  text2->Draw("same");
  text3->Draw("same");
  text4->Draw("same");
  text5->Draw("same");
  text6->Draw("same");
  text7->Draw("same");
  text8->Draw("same");
  text9->Draw("same");
  text10->Draw("same");
  text11->Draw("same");
  text12->Draw("same");
  text13->Draw("same");
  text14->Draw("same");
  text15->Draw("same");
  text16->Draw("same");
  text17->Draw("same");

  c2->Print("Summary_Plots/Q2xB.pdf");


  delete c2;
  delete Q2xB;
  delete mtxB;
  delete Q2xB_bkg;
  delete mtxB_bkg;
  for (UInt_t i = 0; i < NBINSt; ++i)
  {
    delete line_t[i];
  }
  for (UInt_t i = 0; i < NBINSQ; ++i)
  {
    delete line_Q[i];
  }
  for (UInt_t i = 0; i < NBINSx; ++i)
  {
    delete line_xt[i];
    delete line_xQ[i];
  }
  for (UInt_t i = 0; i < 3; ++i)
  {
    delete fa1[i];
  }
  for (UInt_t i = 0; i < 2; ++i)
  {
    delete th_edge[i];
  }
  delete text1;
  delete text2;
  delete text3;
  delete text4;
  delete text5;
  delete text6;
  delete text7;
  delete text8;
  delete text9;
  delete text10;
  delete text11;
  delete text12;
  delete text13;
  delete text14;
  delete text15;
  delete text16;
  
}


/************************************************/
/************************************************/
/***************** MAIN FUNCTION ****************/
/************************************************/
/************************************************/

void Summary()
{

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


for(int i=1; i<=94; i++)
{
  bdts.push_back(Best_BDT(i));
}
/*
BDT_bin_cut = "";
for (int i = 0; i < NBins; ++i) {
  TString binCut = Mbins[i].GetTitle();
  TString bdtCut = Form("_strip_Nuc_BDT > %f", bdts[i]);
  TString combined = "(" + binCut + " && " + bdtCut + ")";
  if (i == 0)
    BDT_bin_cut = TCut(combined);
  else
    BDT_bin_cut = BDT_bin_cut || TCut(combined);
}
    */

//Create folder for summary plots
  gSystem->Exec("mkdir -p Summary_Plots");

  //Initialize trees
  TChain *Data_Tree= new TChain("pDVCS");
  Data_Tree->Add(DATA);

  TChain *DVCS_Tree= new TChain("pDVCS");
  DVCS_Tree->Add(DVCS);

  TChain *Pi0_Tree= new TChain("pDVCS");
  Pi0_Tree->Add(Pi0);

  TChain *SIDIS_Tree= new TChain("pDVCS");
  SIDIS_Tree->Add(SIDIS);

  TChain *Data_bkg= new TChain("pDVCS");
  for(int i=1; i<=NBins; i++)
  {
  	Data_bkg->Add(Form("Analysis/bin_%i/TMaxime_pi0.root",i));
  }


  //2D final state kinematics
  std::cout<<"2D final state kinematics"<<std::endl;
  Kinematics(Data_Tree, Data_bkg);
  std::cout<<"\n"<<std::endl;

  //1D final state kinematics after bkg subtraction
  std::cout<<"1D final state kinematics after bkg subtraction"<<std::endl;
  Kin_Comparison_2(Data_Tree, Data_bkg);
  std::cout<<"\n"<<std::endl;

  /*
  //Q2, xB, t and mm2_eg P vs NP before and after BDT
  std::cout<<"Q2, xB, t and mm2_eg P vs NP before and after BDT"<<std::endl;
  Comparison_2(Data_Tree, Data_bkg);
  std::cout<<"\n"<<std::endl;

  //Q2xB and mtxB Phase Space plots
  std::cout<<"Q2xB and mtxB Phase Space plots"<<std::endl;
  Phase_Space(Data_Tree, Data_bkg);
  std::cout<<"\n"<<std::endl;

  //Training variables vs BDT score on Data
  std::cout<<"Training variables vs BDT score on Data"<<std::endl;
  TrainVars_BDT(Data_Tree, "");
  std::cout<<"\n"<<std::endl;

  //Training variables vs BDT score on SIDIS
  std::cout<<"Training variables vs BDT score on SIDIS"<<std::endl;
  TrainVars_BDT(SIDIS_Tree, "sidis_");
  std::cout<<"\n"<<std::endl;

  //BDT score single training
  std::cout<<"BDT score for Data, DVCS and Pi0 single training"<<std::endl;
  //Get_BDT_Score_single(Data_Tree);
  std::cout<<"\n"<<std::endl;
 
  //Angles vs BDT in topologies for Data, DVCS and Pi0
  std::cout<<"Angles vs BDT in topologies for Data, DVCS and Pi0"<<std::endl;
  Kinematics_2(Data_Tree, DVCS_Tree, Pi0_Tree);
  std::cout<<"\n"<<std::endl;

    //Integrated Excl. Variables
  std::cout<<"Integrated Excl. Variables"<<std::endl;
  Excl_vars_aft_BDT(Data_Tree, DVCS_Tree, Data_bkg);
  std::cout<<"\n"<<std::endl;

  */
}
