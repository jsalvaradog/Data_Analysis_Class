void BDT::Get_excl_vars(TCut cut)
{
   TCanvas *canvas2 = new TCanvas("canvas2", "Exclusivity variables");
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);

  TChain *pDVCS= new TChain("pDVCS");
  pDVCS->Add(Folder + TData);

  TChain *cont= new TChain("pDVCS");
  cont->Add(Folder + TString("TMaxime_pi0.root"));

  TChain *simu= new TChain("pDVCS");
  //simu->Add(Folder + TDVCS);
  simu->Add(Folder + TString("wf")+ TBM_Sim);

  auto hs2 = new THStack("hs2","M^{2}_{e#gamma X} (GeV^{2})");
  TH1F *hist2c_Data = new TH1F("hist2c_Data","Data",100,0.0, 2.0);
  TH1F *hist2c_Cont = new TH1F("hist2c_Cont","",100, 0.0, 2.0);
  TH1F *hist2c_Sim = new TH1F("hist2c_Sim","MC",100,0.0, 2.0);

  //Variables to plot
  const char *p2="mm2_eg";
  double x0, a, b, c, d;
/*
  //El_P correction
  x0= 0.981341;
a=  -0.14361;
b=  0.156291;
c=  -0.0536955;
d=  0.00571549;
  TString deltaP = Form("(%f + %f*(strip_El_P - %f) + %f*pow(strip_El_P - %f,2) + %f*pow(strip_El_P - %f,3))",a,b,x0,c,x0,d,x0);
*/
/*  
  //Nuc_Theta correction
x0= 5.33532;
a=  -0.24018;
b=  0.00269173;
c=  6.45732e-05;
d=  -5.50649e-07;
  TString deltaP = Form("(%f + %f*(strip_Nuc_Theta - %f) + %f*pow(strip_Nuc_Theta - %f,2) + %f*pow(strip_Nuc_Theta - %f,3))",a,b,x0,c,x0,d,x0);
*/


//El Theta
x0= -0.982124;
a=  0.00675549;
b=  0.00135486;
c=  -0.000293689;
d=  5.75993e-06;
  TString deltaP = Form("(%f + %f*(strip_El_Theta - %f) + %f*pow(strip_El_Theta - %f,2) + %f*pow(strip_El_Theta - %f,3))",a,b,x0,c,x0,d,x0);
  TString deltaMM2 = TString("(-10.6 - 0.938 + strip_Ph_P + 10.6*cos(strip_El_Theta * TMath::Pi()/180) - strip_Ph_P*cos(strip_El_Theta * TMath::Pi()/180)*cos(strip_Ph_Theta * TMath::Pi()/180) - strip_Ph_P*cos(strip_El_Phi * TMath::Pi()/180 - strip_Ph_Phi * TMath::Pi()/180)*sin(strip_El_Theta * TMath::Pi()/180)*sin(strip_Ph_Theta * TMath::Pi()/180))");


  //TString delta = TString("mm2_eg -") + deltaMM2 + TString(" * ") + deltaP;
  TString delta = TString("mm2_eg");
  
  cont->Project("hist2c_Cont", delta, (cut + TCut(Form("_strip_Nuc_BDT > %f", BDT_value))) * TCut("Weight"));
  pDVCS->Project("hist2c_Data", delta, (cut + TCut(Form("_strip_Nuc_BDT > %f", BDT_value))));
  simu->Project("hist2c_Sim", p2, (cut + TCut(Form("_strip_Nuc_BDT > %f", BDT_value)))*TCut("rWeight"));
  
  hist2c_Data->Add(hist2c_Data, hist2c_Cont, 1, -1);
  hist2c_Sim->Scale(hist2c_Data->Integral()/hist2c_Sim->Integral());
  hist2c_Sim->Add(hist2c_Sim, hist2c_Cont, 1, -1);

  hist2c_Sim->SetLineColor(kBlack);
  hist2c_Data->SetLineColor(kRed);
  hist2c_Cont->SetLineColor(kMagenta);

  hs2->Add(hist2c_Sim,"hist");
  hs2->Add(hist2c_Data,"HIST");
  hs2->Add(hist2c_Cont,"HIST");

  hs2->SetHistogram(new TH1F("hstot2","",100,0,2));
  hs2->GetHistogram()->GetXaxis()->SetTitle(hs2->GetTitle());
  hs2->GetHistogram()->GetYaxis()->SetTitle("Counts");
  hs2->GetHistogram()->SetTitle("");
  hs2->GetHistogram()->GetXaxis()->SetTitleSize(0.06);
  hs2->GetHistogram()->GetYaxis()->SetTitleSize(0.06);
  hs2->GetHistogram()->GetXaxis()->SetLabelSize(0.04);
  hs2->GetHistogram()->GetYaxis()->SetLabelSize(0.04);
  hs2->GetHistogram()->GetYaxis()->SetTitleOffset(0.85);
  hs2->GetHistogram()->GetXaxis()->SetTitleOffset(0.7);
  hs2->GetHistogram()->GetYaxis()->SetNdivisions(8);
  hs2->GetHistogram()->GetXaxis()->SetNdivisions(8);
  hs2->GetHistogram()->GetYaxis()->SetMaxDigits(2);
  
  hs2->Draw("nostack");

  double proton_mass = 0.938272; // GeV
  double m2_proton = proton_mass * proton_mass;
  TLine *line = new TLine(m2_proton, 0, m2_proton, max(hist2c_Data->GetMaximum(), hist2c_Sim->GetMaximum())*1.05);
  line->SetLineColor(kBlue+2);
  line->SetLineWidth(2);
  line->SetLineStyle(2);
  line->Draw("same");

  //canvas2->BuildLegend();
  canvas2->Print(Folder + TString("Excl_vars.pdf"));
  
  
  delete hist2c_Sim;
  delete hist2c_Data;
  delete hist2c_Cont;

  delete canvas2;
  delete hs2;

  delete pDVCS;
  delete simu;
  delete cont;
}
