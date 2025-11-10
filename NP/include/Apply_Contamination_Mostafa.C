
TH1* BDT::Apply_Contamination_Mostafa(TCut cut)
{
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  TChain *Data= new TChain("pDVCS");
  Data->Add(Folder + TString("Data_NP_Theta_g_5.root"));

  TChain *Pi0= new TChain("pDVCS");
  Data->Add(Folder + TString("TMostafa_pi0.root"));

  int N_Phi=12;

  TH1F *Pi01g_p_BDT = new TH1F("Pi01g_p_BDT","",N_Phi,0,360);
  TH1F *Pi01g_m_BDT = new TH1F("Pi01g_m_BDT","",N_Phi,0,360);

  TH1F *Data_p_BDT = new TH1F("Data_p_BDT","",N_Phi,0,360);
  TH1F *Data_m_BDT = new TH1F("Data_m_BDT","",N_Phi,0,360);

  Pi01g_p_BDT->Sumw2();
  Pi01g_m_BDT->Sumw2();
  Data_p_BDT->Sumw2();
  Data_m_BDT->Sumw2();
  
  Pi0->Project("Pi01g_p_BDT", "Phi_Ph", cut*TCut("Weight"));
  Pi0->Project("Pi01g_m_BDT", "Phi_Ph", cut*TCut("Weight"));

  Data->Project("Data_p_BDT", "Phi_Ph", cut + TCut("Helicity>0"));
  Data->Project("Data_m_BDT", "Phi_Ph", cut + TCut("Helicity<0"));

  Pi01g_p_BDT->Scale(-1.0);
  Pi01g_m_BDT->Scale(-1.0);

  Data_p_BDT->Add(Pi01g_p_BDT);
  Data_m_BDT->Add(Pi01g_m_BDT);


  TH1 *BA= Data_m_BDT->GetAsymmetry(Data_p_BDT);
  TCanvas* c2 = new TCanvas("c2","Histograms");

  
  //The fit gets attached to BA, so if BA is deleted, everything is deleted
  //That is why I plot a new "fit" function
  TF1 *fitf = new TF1("fitf","[0]*sin(x*TMath::Pi()/180)/(1+[1]*cos(x*TMath::Pi()/180))",0,360);
  fitf->SetParameter(0,0.1);
  fitf->SetParameter(1,-0.3);
  fitf->SetParLimits(0,0,0.3);
  fitf->SetParLimits(1,-1.,1.);
  fitf->SetLineColor(kBlue);
	  
  BA->Scale(1.0/Bpol);
  BA->Fit("fitf","Q");
  BA->SetTitle("Hall B method");
  BA->SetLineColor(kBlue);
  BA->SetMarkerColor(kBlue);
  BA->SetAxisRange(-0.3, 0.3,"Y");
  BA->SetAxisRange( 0. ,360.,"X");
  BA->GetXaxis()->SetTitle("#phi (deg)");
  BA->Draw();

  // Create an output file to save the histogram
  TFile *outputFile = new TFile(Folder + TString("Mostafa_Clean.root"), "RECREATE");
  fitf->SetLineColor(kBlack);
  BA->SetLineColor(kBlack);
  BA->SetMarkerColor(kBlack);

  // Write the histogram to the output file
  BA->Write();

  // Close the output file
  outputFile->Close();

  c2->Print(Folder + TString("Mostafa.pdf"));

  delete Pi0;
  delete Data;

  delete Pi01g_p_BDT;
  delete Pi01g_m_BDT;
  delete Data_p_BDT;
  delete Data_m_BDT;
  delete c2;

  return BA;

}
