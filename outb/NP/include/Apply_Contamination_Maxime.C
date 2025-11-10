
TH1* BDT::Apply_Contamination_Maxime(TCut cut)
{
  TChain *Data= new TChain("pDVCS");
  Data->Add(Folder + "Data_NP_Theta_g_5.root");

  TChain *bkg= new TChain("pDVCS");
  bkg->Add(Folder + TString("TMaxime_pi0.root"));
  int N_Phi=12;

  TH1F *Data_p_BDT = new TH1F("Data_p_BDT","",N_Phi,0,360);
  TH1F *Data_m_BDT = new TH1F("Data_m_BDT","",N_Phi,0,360);

  Data_p_BDT->Sumw2();
  Data_m_BDT->Sumw2();

  Data->Project("Data_p_BDT", "Phi_Ph", cut + TCut("Helicity>0"));
  Data->Project("Data_m_BDT", "Phi_Ph", cut + TCut("Helicity<0"));

  TH1F *Phi_p_BDT = new TH1F("Phi_p_BDT","",N_Phi,0,360);
  TH1F *Phi_m_BDT = new TH1F("Phi_m_BDT","",N_Phi,0,360);

  Phi_p_BDT->Sumw2();
  Phi_m_BDT->Sumw2();

  bkg->Project("Phi_p_BDT", "Phi_Ph", TCut("Weight")*(cut + TCut("Helicity>0")));
  bkg->Project("Phi_m_BDT", "Phi_Ph", TCut("Weight")*(cut + TCut("Helicity<0")));

  Phi_p_BDT->Scale(-1.0);
  Phi_m_BDT->Scale(-1.0);

  Data_p_BDT->Add(Phi_p_BDT);
  Data_m_BDT->Add(Phi_m_BDT);

  
  TH1 *BA= Data_m_BDT->GetAsymmetry(Data_p_BDT);
  //The fit gets attached to BA, so if BA is deleted, everything is deleted
  //That is why I plot a new "fit" function
  TF1 *fitf = new TF1("fitf","[0]*sin(x*TMath::Pi()/180)/(1+[1]*cos(x*TMath::Pi()/180))",0,360);
  fitf->SetParameter(0,0.1);
  fitf->SetParameter(1,-0.3);
  fitf->SetParLimits(0,0,0.3);
  fitf->SetParLimits(1,-1.,1.);
  fitf->SetLineColor(kRed);
	  
  TCanvas* c2 = new TCanvas("c2","Histograms");
  BA->Scale(1.0/Bpol);
  BA->Fit("fitf","Q");
  BA->SetTitle("RG-A note");
  BA->SetLineColor(kRed);
  BA->SetMarkerColor(kRed);
  BA->SetAxisRange(-0.3, 0.3,"Y");
  BA->SetAxisRange( 0. ,360.,"X");
  BA->GetXaxis()->SetTitle("#phi (deg)");
  BA->Draw();
  
  // Create an output file to save the histogram
  TFile *outputFile = new TFile(Folder + TString("Maxime_Clean.root"), "RECREATE");
  fitf->SetLineColor(kBlack);
  BA->SetLineColor(kBlack);
  BA->SetMarkerColor(kBlack);

  // Write the histogram to the output file
  BA->Write();

  // Close the output file
  outputFile->Close();


  c2->Print(Folder + TString("Maxime.pdf"));

  delete c2;
  delete Phi_p_BDT;
  delete Phi_m_BDT;
  delete Data_p_BDT;
  delete Data_m_BDT;
  delete Data;
  delete bkg;
  
  return BA;

}
