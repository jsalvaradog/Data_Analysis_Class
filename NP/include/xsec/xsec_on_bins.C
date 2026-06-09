
void BDT::xsec_on_bins(int bin, int NBinsPhi = 0)
{
  //////////////////////////////////////////////////////////////
  // Initial declarations and pre-processing
  //////////////////////////////////////////////////////////////
  gStyle->SetOptFit(0);
  gStyle->SetOptTitle(0);

  if (NBinsPhi == 0)
    NBinsPhi = Nphibins[bin - 1];

  double x, y, aux, yErr;
  int numPoints;

  boundaries.clear();
  boundaries.push_back(bins[bin - 1][0]);
  boundaries.push_back(bins[bin - 1][1]);
  boundaries.push_back(bins[bin - 1][2]);
  boundaries.push_back(bins[bin - 1][3]);
  boundaries.push_back(bins[bin - 1][4]);
  boundaries.push_back(bins[bin - 1][5]);

  cut_bin = Mbins[bin - 1];
  cut = cut + cut_pid;
  std::cout << cut_bin.GetTitle() << endl;
  TString Folder_old = Folder;
  Folder = Folder_old + TString("bin_") + Form("%i/", bin);
  gSystem->Exec(TString("mkdir -p ") + Folder);

  //Flag for training category or normal      
  //Check if there is enough background in the FT. At least 100 events
  TChain *background= new TChain("pDVCS");
  background->Add(Pi0);
  
  TH1F *hist1 = new TH1F("hist1","",100,0,1);
  TH1F *hist2 = new TH1F("hist2","",100,0,1);
  background->Project("hist1","strip_Xbj",cut + cut_bin + TCut("strip_Ph_Theta < 5"));
  background->Project("hist2","strip_Xbj",cut + cut_bin);
  nft=hist1->GetEntries()/hist2->GetEntries();
  categories=(nft>0.05 && hist1->GetEntries()>50) ? true: false ;
  int nev_bkg = hist2->GetEntries();
  delete hist1;
  delete hist2;
  delete background;
  //categories=false;          
  
  std::ifstream nodataInp(Folder + TString("nodata.conf"));
  if (nodataInp)
    nodata = true;
  nodataInp.close();

  double bdt = Best_BDT();
  std::cout << Form("\n Best BDT cut found at: %f", bdt) << endl;
  // To improve mm2_eg matching
  BDT_value = bdt + 0.02;
  if (bdt_sys)
    BDT_value = BDT_value + 0.02;
  
  //////////////////////////////////////////////////////////////
  // bkg merging datasets //
  //////////////////////////////////////////////////////////////
  //Add_BDT_var_Formula(cut + cut_bin, DVCS_nABkg, "TDVCS_nABkg.root", Vars);
  //Add_BDT_var_Formula(cut + cut_bin, DVCS_noBkg, "TDVCS_noBkg.root", Vars);
  //////////////////////////////////////////////////////////////
  // hep_ml distribution matching //
  //////////////////////////////////////////////////////////////
  /*
  Add_PhEff_var(cut + cut_bin, BM_Sim, TString("Ph_eff_") + TBM_Sim);
  Add_BDT_var_Formula(cut + cut_bin, Folder + TString("Ph_eff_") + TBM_Sim, TBM_Sim, Vars);
  gSystem->Exec(TString("rm -r ") + Folder + TString("Reweighting_Plots_BM"));
  Filter(Folder + TBM_Sim, cut + cut_bin + cut_ref + TCut(Form("_strip_Nuc_BDT > %f", BDT_value)), TString("f") + TBM_Sim);
  Filter(Folder + TData, cut + cut_bin + cut_ref + TCut(Form("_strip_Nuc_BDT > %f", BDT_value)), TString("Data_NP_Theta_g_5.root"));
  Resolution_Match(cut + cut_bin + cut_ref, TString("Data_NP_Theta_g_5.root"), TString("f") + TBM_Sim);
  gSystem->Exec(TString("mv ") + Folder + TString("Reweighting_Plots ") + Folder + TString("Reweighting_Plots_BM"));
  gSystem->Exec(TString("rm ") + Folder + TString("f") + TBM_Sim);
  gSystem->Exec(TString("rm ") + Folder + TString("Ph_eff_") + TBM_Sim);
  */
  //Plot missing proton mass
  Get_excl_vars(cut + cut_bin + cut_ref);
  

  //////////////////////////////////////////////////////////////
  /* Computing contamination */
  //////////////////////////////////////////////////////////////
  std::cout << "\n Getting Contamination Mostafa way..." << endl;
  auto Most = Get_Contamination_Mostafa(cut + cut_bin + cut_kin + cut_sel + cut_ref, BDT_value, NBinsPhi, false);
  std::cout << "\n Gettting Contamination Maxime way" << endl;
  auto Maxi = Get_Contamination_Maxime(cut + cut_bin + cut_kin + cut_sel + cut_ref, BDT_value, bin, NBinsPhi);
  // std::cout<<"\n Getting Contamination Fitting way..."<<endl;
  // auto Fitt=Get_Contamination_Fit(cut + cut_bin, BDT_value,NBinsPhi);

  Folder = Folder + TString("xsec/");
  gSystem->Exec(TString("mkdir -p ") + Folder + TString("xsec/"));

  std::vector<vector<double>> means1, means2;
  means1 = ReadMeansFile(Folder + TString("../means_most.txt"));
  means2 = ReadMeansFile(Folder + TString("../means_maxi.txt"));

  // Get shift of kinematics
  // It was used for the 4to3 correction. Now it is irrelevant
  // I keep it just in case
  kin_shift_factor(means1, means2, NBinsPhi);

  ///////////////////////////////
  // Retrieve event yield
  ///////////////////////////////
  TChain *chainData = new TChain("pDVCS");
  TChain *chainBkg1 = new TChain("pDVCS");
  TChain *chainBkg2 = new TChain("pDVCS");

  chainData->Add(Folder + TString("../") + TData); // Data
  // chainData->Add(Folder + TString("../") + TBM_Sim); // MC test
  // chainData->Add(Folder + TString("../wf") + TBM_Sim); // MC wtest
  chainBkg1->Add(Folder + TString("../") + "TMostafa_pi0.root");
  chainBkg2->Add(Folder + TString("../") + "TMaxime_pi0.root");

  TH1* NOrig = new TH1F("NOrig", "Original Data", NBinsPhi, 0, 360);
  TH1* NOrig_0 = new TH1F("NOrig_0", "Original Data 0", NBinsPhi, 0, 360);
  TH1* eff_ratio = new TH1F("eff_ratio", "eff ratio", NBinsPhi, 0, 360);
  TH1 *NBkg1 = new TH1F("NBkg1", "Background 1", NBinsPhi, 0, 360);
  TH1 *NBkg2 = new TH1F("NBkg2", "Background 2", NBinsPhi, 0, 360);
  NOrig->Sumw2();
  NBkg1->Sumw2();
  NBkg2->Sumw2();

  TCut weight = TCut("1.0");
  //TCut weight = TCut("1.0/GetBkgMergEff(RunNumber)");
  //TCut weight = TCut("1.0/GetPhotonEff(det_Ph_x, det_Ph_y)");

  TTreeFormula* formula = new TTreeFormula("cutFormula", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))).GetTitle(), chainData);
  static std::vector<int>* flag;
  static std::vector<double>* El_x;
  static std::vector<double>* El_y;
  static std::vector<double>* Ph_x;
  static std::vector<double>* Ph_y;
  static std::vector<double>* Phi;
  static int RunNumber;
  
  chainData->SetBranchAddress("bestCandidateFlag",&flag);
  chainData->SetBranchAddress("RunNumber",&RunNumber);
  chainData->SetBranchAddress("det_El_x",&El_x);
  chainData->SetBranchAddress("det_El_y",&El_y);
  chainData->SetBranchAddress("det_Ph_x",&Ph_x);
  chainData->SetBranchAddress("det_Ph_y",&Ph_y);
  chainData->SetBranchAddress("Phi_Ph",&Phi);

  for(int i=0; i<chainData->GetEntries(); i++)
    {
      chainData->GetEntry(i);
    for(int j=0; j<flag->size(); j++)
	  {
	    if(flag->at(j)==1)
	    {
        	if(formula->EvalInstance())  
        	{
          //if(Ph_x->at(j)*Ph_x->at(j)+Ph_y->at(j)*Ph_y->at(j)<20.*20.)
          //  NOrig->Fill(Phi->at(j), 1.0/GetBkgMergEff(RunNumber));
          //else
        	  NOrig->Fill(Phi->at(j), 1.0/GetBkgMergEff(RunNumber) );
		}
	    }
     	  }
     }   

  //chainData->Project("NOrig", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * weight);
  chainData->Project("NOrig_0", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))));  
  chainBkg1->Project("NBkg1", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * weight * TCut("Weight"));
  chainBkg2->Project("NBkg2", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * weight * TCut("Weight"));
  boundaries.push_back(NOrig->Integral());   

  eff_ratio->Divide(NOrig, NOrig_0,1,1);
  NBkg1->Multiply(eff_ratio);
  NBkg2->Multiply(eff_ratio);
  
  //std::cout<<"lala "<<NOrig->Integral()<<" "<<NOrig_0->Integral()<<endl;

  ///////////////////////////////
  // Background subtracted yield and systematics
  ///////////////////////////////
  TH1F *NMost = new TH1F("NMost", "Method 1", NBinsPhi, 0, 360);
  TH1F *NMaxi = new TH1F("NMaxi", "Method 2", NBinsPhi, 0, 360);
  NMost->Sumw2();
  NMaxi->Sumw2();

  NMost->Add(NOrig, NBkg1, 1, -1);
  NMaxi->Add(NOrig, NBkg2, 1, -1);

  NOrig->SetMarkerColor(kBlack);
  NOrig->SetLineColor(kBlack);

  NMost->SetMarkerColor(kBlue);
  NMost->SetLineColor(kBlue);

  NMaxi->SetMarkerColor(kRed);
  NMaxi->SetLineColor(kRed);

  NMost->SetTitle("Method 1");
  NMaxi->SetTitle("Method 2");

  NOrig->SetName("Before");
  NMost->SetName("Method 1");
  NMaxi->SetName("Method 2");

  /// Selection systematics
  TH1F *Systematics = new TH1F("Systematics", "Systematics", NBinsPhi, 0, 360);
  for (int r = 0; r <= NBinsPhi; r++)
  {
    Systematics->SetBinContent(r, 0.0);
    Systematics->SetBinError(r, 0.0);
  }

  TH1 *NSys_BDT = new TH1F("NSys_BDT", "", NBinsPhi, 0, 360);
  TH1 *NSys_pid = new TH1F("NSys_pid", "", NBinsPhi, 0, 360);
  NSys_BDT->Sumw2();
  NSys_pid->Sumw2();

  TTreeFormula* formula_BDT = new TTreeFormula("cutFormula_BDT", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value + 0.04*0.1))).GetTitle(), chainData);
  TTreeFormula* formula_PID = new TTreeFormula("cutFormula_PID", (cut + cut_bin + cut_kin + cut_sel + cut_ref + cut_pid + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))).GetTitle(), chainData);
  for(int i=0; i<chainData->GetEntries(); i++)
  {
    chainData->GetEntry(i);
    for(int j=0; j<flag->size(); j++)
	  {
	    if(flag->at(j)==1)
	    {
        if(formula_BDT->EvalInstance())  
        {
          //if(Ph_x->at(j)*Ph_x->at(j)+Ph_y->at(j)*Ph_y->at(j)<20.*20.)
          //  NSys_BDT->Fill(Phi->at(j), 1.0/GetBkgMergEff(RunNumber));
          //else
        	  NSys_BDT->Fill(Phi->at(j), 1.0/GetBkgMergEff(RunNumber) );
        }
  
        if(formula_PID->EvalInstance())  
        {
          //if(Ph_x->at(j)*Ph_x->at(j)+Ph_y->at(j)*Ph_y->at(j)<20.*20.)
          //  NSys_pid->Fill(Phi->at(j), 1.0/GetBkgMergEff(RunNumber));
          //else
            NSys_pid->Fill(Phi->at(j), 1.0/GetBkgMergEff(RunNumber) );
        }
	    }
    }
  }

  //chainData->Project("NSys_BDT", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value + 0.04*0.1))) * weight);
  //chainData->Project("NSys_pid", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * weight);

  // Selection systematics
  NSys_BDT->Add(NOrig, NSys_BDT, 1, -1);
  NSys_pid->Add(NOrig, NSys_pid, 1, -1);
  NSys_BDT->Divide(NMaxi);
  NSys_pid->Divide(NMaxi);
  NSys_BDT->Multiply(NSys_BDT);
  NSys_pid->Multiply(NSys_pid);
  //Systematics->Add(NSys_BDT);
  Systematics->Add(NSys_pid);

  // Bkg systematics
  NBkg1->Add(NBkg1, NBkg2, 1, -1);
  NBkg1->Divide(NMaxi);
  NBkg1->Multiply(NBkg1);
  Systematics->Add(NBkg1);
  std::cout << "\nSelection Systematics (BDT/PID/Bkg)" << endl;
  for (int r = 0; r <= NBinsPhi; r++)
  {
    Systematics->SetBinError(r, Systematics->GetBinContent(r));
    Systematics->SetBinContent(r, 1.0);
    std::cout << " " << sqrt(NSys_BDT->GetBinContent(r)) * 100 << "%, " << sqrt(NSys_pid->GetBinContent(r)) * 100 << "%, " << sqrt(NBkg1->GetBinContent(r)) * 100 << "%" << endl;
  }

  ///////////////////////////////
  // Error computation of yields
  ///////////////////////////////

  TH1F *OrigErr1 = new TH1F("OrigErr1", "OrigErr1", NBinsPhi, 0, 360);
  TH1F *OrigErr2 = new TH1F("OrigErr2", "OrigErr2", NBinsPhi, 0, 360);
  std::ifstream StatFile;
    std::string line;

  StatFile.open(Folder + TString("../Bkg_Most_stats.txt")); // Replace with the name of the block file you want to read
  double n1g_p, n1g_m, n2g_p, n2g_m, n2gD_p, n2gD_m, nData_p, nData_m;
  double n1g, n2g, n2gD;

  std::cout << "\nRaw entries/err for Orig, Most and Maxi: " << endl;
  for (int t = 1; t <= NBinsPhi; t++)
  {
    std::getline(StatFile, line);
    std::istringstream iss(line);
    iss >> n1g_p >> n1g_m >> n2g_p >> n2g_m >> n2gD_p >> n2gD_m >> nData_p >> nData_m;
    n1g = (n1g_p + n1g_m);
    n2g = (n2g_p + n2g_m);
    n2gD = (n2gD_p + n2gD_m);

    if (NMost->GetBinContent(t) > 1 && NOrig->GetBinContent(t) > 1 && n1g > 1 && n2g > 1 && n2gD > 1)
    {
      OrigErr1->SetBinContent(t, 1.0);
      OrigErr1->SetBinError(t, NOrig->GetBinContent(t) * sqrt(1.0 / (NOrig->GetBinContent(t) * pow(NMost->GetBinContent(t) / NOrig->GetBinContent(t), 2))));
      NMost->SetBinError(t, NMost->GetBinContent(t) * sqrt(pow(NOrig->GetBinContent(t) / NMost->GetBinContent(t) - 1, 2) * (1. / n1g + 1. / n2g + 1. / n2gD)));
    }
    else
    {
      OrigErr1->SetBinContent(t, 1.0);
      OrigErr1->SetBinError(t, sqrt(NOrig->GetBinContent(t)));
      NMost->SetBinError(t, 0.0);
    }
    if (NMaxi->GetBinContent(t) > 1 && NOrig->GetBinContent(t) > 1 && n2gD > 1)
    {
      OrigErr2->SetBinContent(t, 1.0);
      OrigErr2->SetBinError(t, NOrig->GetBinContent(t) * sqrt(1.0 / (NOrig->GetBinContent(t) * pow(NMaxi->GetBinContent(t) / NOrig->GetBinContent(t), 2))));
      NMaxi->SetBinError(t, NMaxi->GetBinContent(t) * sqrt(pow(NOrig->GetBinContent(t) / NMaxi->GetBinContent(t) - 1, 2) * (1. / NMaxi->GetBinContent(t) + 1. / n2gD)));
    }
    else
    {
      OrigErr2->SetBinContent(t, 1.0);
      OrigErr2->SetBinError(t, sqrt(NOrig->GetBinContent(t)));
      NMaxi->SetBinError(t, 0.0);
    }
    std::cout << " " << NOrig->GetBinContent(t) << " " << OrigErr1->GetBinError(t) << " " << NMost->GetBinContent(t) << " " << NMost->GetBinError(t) << " " << NMaxi->GetBinContent(t) << " " << NMaxi->GetBinError(t) << endl;
  }
  StatFile.close();

  TCanvas* canvas = new TCanvas("canvas","canvas",700,500);
  NOrig->Draw();
  NMost->Draw("SAME");
  NMaxi->Draw("SAME");
  canvas->BuildLegend();
  canvas->Print(Folder + TString("Background_subtraction.pdf"));
  delete canvas;

  ///////////////////////////////
  // Phase Space Volume
  ///////////////////////////////
  
  TH1F *PS_factor = Phase_Space_Factor(NBinsPhi, bin);             // Phase Space volume
  // Phase_Space_Factor1(NBinsPhi, bin); // Phase Space volume
  PS_factor->SetName("PS_factor");

  //Theory_point(1, bin, xmean2, Qmean2, tmean2, NBinsPhi); // BH
  //Theory_point(2, bin, xmean2, Qmean2, tmean2, NBinsPhi); // VGG
  //Theory_point(3, bin, xmean2, Qmean2, tmean2, NBinsPhi); // KM15
  //Theory_integral(1, bin, xmean2, Qmean2, tmean2, NBinsPhi); // BH
  //Theory_integral(2, bin, xmean2, Qmean2, tmean2, NBinsPhi); // VGG
  //Theory_integral(3, bin, xmean2, Qmean2, tmean2, NBinsPhi); // KM15
  auto graph_BH = Theory_integral_generator(1, bin); // BH
  auto graph_VGG= Theory_integral_generator(2, bin); // VGG
  auto graph_KM = Theory_integral_generator(3, bin); // KM15

  ///////////////////////////////
  // Corrections to the event yield
  // Extraction of Exp xsec
  ///////////////////////////////

  gStyle->SetOptTitle(1);
  TH1F* F_LP = Lepton_Propagator(bin);
  F_LP->SetName("F_LP");

  //TH1F* F_BM = Background_Merging(cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT > %f", BDT_value)), bin);
  //F_BM->SetName("F_BM");

  TH1F *F_rad = F_RC(NBinsPhi, Systematics); // Radiative corrections
  F_rad->SetName("F_RC");

  /*
  //TH1F *F_bin1 = F_Bin(bin, tmean2, Qmean2, xmean2, 1, PS_factor); // Bin centering correction. From integrated xsec to xsec@3D_means
  //TH1F* F_bin1 =  F_Bin( bin, tmean2, Qmean2, xmean2, 1, PS_factor); //Bin centering correction. From integrated xsec to xsec@3D_means
  //TH1F* F_bin1 = F_bin_KM_model(bin, tmean2, Qmean2, xmean2);
  //F_bin1->SetName("F_Bin_Michel_Model");
  //TH1F* F_bin2 =  F_bin1;
  //F_bin2->SetName("F_Bin_Michel_Model");
  
  for(int r=0; r<=NBinsPhi; r++)
  {
    Systematics->SetBinError(r, Systematics->GetBinError(r) + pow(F_bin1->GetBinError(r), 2));  //Add systematics of F_bin to the total
  }
  */

  TH1F *F_noRec = No_Rec_correction(Folder + TString("../wf") + TBM_Sim, MC_BM_Sim, BDT_value, NBinsPhi, Systematics); // Acceptance~rec_eff correction
  F_noRec->SetName("F_noRec");                                                                                         // I am using the weighted file (ResMatching)

  TH1F *xsec1 = new TH1F("xsec1", "xsec1", NBinsPhi, 0, 360);
  TH1F *xsec2 = new TH1F("xsec2", "xsec2", NBinsPhi, 0, 360);

  xsec1->Divide(NMost, F_noRec, 1, 1);
  xsec2->Divide(NMaxi, F_noRec, 1, 1);

  xsec1->Divide(xsec1, F_rad, 1, 1);
  xsec2->Divide(xsec2, F_rad, 1, 1);

  xsec1->Divide(xsec1, F_LP, 1, 1);
  xsec2->Divide(xsec2, F_LP, 1, 1);

  //xsec1->Divide(xsec1, F_BM, 1, 1);
  //xsec2->Divide(xsec2, F_BM, 1, 1);

  xsec1->Divide(xsec1, PS_factor, 1, 1);
  xsec2->Divide(xsec2, PS_factor, 1, 1);

  xsec1->Scale(1.0 / (Lumi));
  xsec2->Scale(1.0 / (Lumi));

  std::cout << "\nRough Normalization factor" << endl;
  double F_eff1 = 0.0;
  double F_eff2 = 0.0;
  int counter = 0;
  for (int t = 0; t < NBinsPhi; t++)
  {
    if (xsec1->GetBinCenter(t + 1) < 30 || xsec1->GetBinCenter(t + 1) > 330) // exclude bins around 180 deg where the BH cross-section is very small and can create large fluctuations
    {
      F_eff1 += xsec1->GetBinContent(t + 1) / graph_BH->Eval(xsec1->GetBinCenter(t + 1));
      F_eff2 += xsec2->GetBinContent(t + 1) / graph_BH->Eval(xsec2->GetBinCenter(t + 1));
      counter++;
    }
    std::cout << " " << xsec1->GetBinContent(t + 1) << " " << xsec2->GetBinContent(t + 1) << " " << graph_BH->Eval(xsec1->GetBinCenter(t + 1)) << endl;
  }
  F_eff1 = F_eff1 / counter;
  F_eff2 = F_eff2 / counter;
  std::cout << "\nRough Global normalization factor " << F_eff1 << " " << F_eff2 << endl;
  // xsec1->Scale(1.0/F_eff1);
  // xsec2->Scale(1.0/F_eff2);
  // xsec2->Scale(1.0/(xsec2->GetBinContent(1)/graph_BH->GetPointY(0))); //For the test

  ///////////////////////////////
  // Remove zero points on graphs for better visualization
  ///////////////////////////////
  for(int i=graph_BH->GetN()-1; i>=0; i--)
  {
    if(graph_BH->GetPointY(i)==0)
    {
      graph_BH->RemovePoint(i);
      graph_VGG->RemovePoint(i);
      graph_KM->RemovePoint(i);
    }
  }
  
  xsec1->SetTitle("Cross-section (nb); #phi (deg); #sigma (nb)");
  xsec2->SetTitle("Cross-section (nb); #phi (deg); #sigma (nb)");
  xsec1->SetLineColor(kBlack);
  xsec2->SetLineColor(kBlue);
  xsec1->SetMarkerColor(kBlack);
  xsec2->SetMarkerColor(kBlue);

  ///////////////////////////////
  // Final xsec as TGraph
  ///////////////////////////////
  TGraphErrors *xsec1gr = new TGraphErrors();
  TGraphErrors *xsec2gr = new TGraphErrors();
  TGraphErrors *xsec1gr_Sys = new TGraphErrors();
  TGraphErrors *xsec2gr_Sys = new TGraphErrors();
  double err1 = 0, err2 = 0;
  double err1_Sys = 0, err2_Sys = 0;

  for (int t = 1; t <= NBinsPhi; t++)
  {
    // NOMINAL ERROR COMPUTATION
    err1 = 0;
    err2 = 0;
    if (NOrig->GetBinContent(t) != 0)
      err1 += pow(OrigErr1->GetBinError(t) / NOrig->GetBinContent(t), 2);
    if (NMost->GetBinContent(t) != 0)
      err1 += pow(NMost->GetBinError(t) / NMost->GetBinContent(t), 2);
    if (F_noRec->GetBinContent(t) != 0)
      err1 += pow(F_noRec->GetBinError(t) / F_noRec->GetBinContent(t), 2);
    if (F_rad->GetBinContent(t) != 0)
      err1 += pow(F_rad->GetBinError(t) / F_rad->GetBinContent(t), 2);

    if (NOrig->GetBinContent(t) != 0)
      err2 += pow(OrigErr2->GetBinError(t) / NOrig->GetBinContent(t), 2);
    if (NMaxi->GetBinContent(t) != 0)
      err2 += pow(NMaxi->GetBinError(t) / NMaxi->GetBinContent(t), 2);
    if (F_noRec->GetBinContent(t) != 0)
      err2 += pow(F_noRec->GetBinError(t) / F_noRec->GetBinContent(t), 2);
    if (F_rad->GetBinContent(t) != 0)
      err2 += pow(F_rad->GetBinError(t) / F_rad->GetBinContent(t), 2);

    err1 = sqrt(err1) * xsec1->GetBinContent(t);
    err2 = sqrt(err2) * xsec2->GetBinContent(t);
    err1_Sys = sqrt(Systematics->GetBinError(t)) * xsec1->GetBinContent(t);
    err2_Sys = sqrt(Systematics->GetBinError(t)) * xsec2->GetBinContent(t);

    xsec1->SetBinError(t, err1);
    xsec2->SetBinError(t, err2);

    printf(" phi %6.2f %6.2f, xsection %6.2f %6.2f, Stat errors %4.2f %4.2f (%4.2f%%), sys error %4.2f (%4.2f%%)\n", means1.at(t - 1).at(0), means2.at(t - 1).at(0), xsec1->GetBinContent(t), xsec2->GetBinContent(t), err1, err2, err2 * 100 / xsec2->GetBinContent(t), err2_Sys, err2_Sys * 100 / xsec2->GetBinContent(t));
    // std::cout<<" phi "<<means1.at(t-1).at(0)<<" "<<means2.at(t-1).at(0)<<" xsection "<<xsec1->GetBinContent(t)<<" "<<xsec2->GetBinContent(t)<<" Stat errors "<<err1<<" "<<err2<<" ("<<err2*100/xsec2->GetBinContent(t)<<" %)"<<" Sys error "<<err2_Sys<<" ("<<err2_Sys*100/xsec2->GetBinContent(t)<<"%)"<<endl;
    if(abs(err1_Sys/xsec1->GetBinContent(t))<1.0)
    {
      if (means1.at(t - 1).at(0) > 1) // To remove outliers due to poor PS evaluation or stats
      {
        xsec1gr->SetPoint(xsec1gr->GetN(), means1.at(t - 1).at(0), xsec1->GetBinContent(t));
        xsec1gr_Sys->SetPoint(xsec1gr_Sys->GetN(), means1.at(t - 1).at(0), xsec1->GetBinContent(t));
        xsec1gr->SetPointError(xsec1gr->GetN() - 1, means1.at(t - 1).at(1), err1);
        xsec1gr_Sys->SetPointError(xsec1gr_Sys->GetN() - 1, means1.at(t - 1).at(1), err1_Sys);
      }
    }
    if(abs(err2_Sys/xsec2->GetBinContent(t))<1.0)
    {
      if (means2.at(t - 1).at(0) > 1) // To remove outliers due to poor PS evaluation or stats
      {
        xsec2gr->SetPoint(xsec2gr->GetN(), means2.at(t - 1).at(0), xsec2->GetBinContent(t));
        xsec2gr_Sys->SetPoint(xsec2gr_Sys->GetN(), means2.at(t - 1).at(0), xsec2->GetBinContent(t));
        xsec2gr->SetPointError(xsec2gr->GetN() - 1, means2.at(t - 1).at(1), err2);
        xsec2gr_Sys->SetPointError(xsec2gr_Sys->GetN() - 1, means2.at(t - 1).at(1), err2_Sys);
      }
    }
  }
  xsec1gr->SetTitle("Cross-section (nb); #phi (deg); #sigma (nb)");
  xsec2gr->SetTitle("Cross-section (nb); #phi (deg); #sigma (nb)");
  xsec1gr->SetName("xsec1gr");
  xsec2gr->SetName("xsec2gr");
  xsec1gr_Sys->SetName("xsec1gr_Sys");
  xsec2gr_Sys->SetName("xsec2gr_Sys");

  ///////////////////////////////
  // Save all corrections to an output file
  ///////////////////////////////
  TFile *outputFile = new TFile(Folder + TString("xsec_dists.root"), "RECREATE");
  NMost->Write();
  NMaxi->Write();
  NOrig->Write();
  PS_factor->Write();
  F_noRec->Write();
  F_rad->Write();
  F_LP->Write();
  //F_BM->Write();
  Systematics->Write();

  xsec1->Write();
  xsec2->Write();
  xsec1gr->Write();
  xsec2gr->Write();
  xsec1gr_Sys->Write();
  xsec2gr_Sys->Write();
  graph_KM->Write();
  graph_VGG->Write();
  graph_BH->Write();

  ///////////////////////////////
  // Final result plot
  ///////////////////////////////
  xsec1gr->SetMarkerStyle(20);
  xsec2gr->SetMarkerStyle(20);
  xsec1gr->SetLineColor(kBlack);
  xsec2gr->SetLineColor(kBlue);
  xsec1gr->SetMarkerColor(kBlack);
  xsec1gr_Sys->SetMarkerColor(kBlack);
  xsec2gr->SetMarkerColor(kBlue);
  xsec2gr_Sys->SetMarkerColor(kBlue);
  xsec1gr_Sys->SetFillColorAlpha(kBlack - 10, 0.6);
  xsec2gr_Sys->SetFillColorAlpha(kBlue - 10, 0.6);
  xsec1gr->SetMarkerSize(0.5);
  xsec2gr->SetMarkerSize(0.5);
  xsec1gr->SetMarkerSize(0.5);
  xsec2gr->SetMarkerSize(0.5);
  xsec1gr->SetLineWidth(2);
  xsec2gr->SetLineWidth(2);

  xsec1gr->GetXaxis()->SetLimits(0, 360);
  xsec2gr->GetXaxis()->SetLimits(0, 360);

  TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 700, 500);
  TMultiGraph *mg = new TMultiGraph();
  //gPad->SetLogy();
  // mg->Add(xsec1gr_Sys,"3");
  // mg->Add(xsec1gr,"P");
  mg->Add(xsec2gr_Sys, "2");
  mg->Add(xsec2gr, "P");
  mg->Add(graph_KM, "l");
  mg->Add(graph_VGG, "l");
  mg->Add(graph_BH, "l");
  mg->Draw("A");

  mg->SetTitle(Form("%.2f<Q^{2}(GeV^{2})<%.2f, %.2f<x_{B}<%.2f, %.2f<t(GeV^{2})<%.2f; #phi (deg); Unnormalized #sigma (nb)", boundaries.at(2), boundaries.at(3), boundaries.at(4), boundaries.at(5), boundaries.at(0), boundaries.at(1)));
  mg->GetXaxis()->SetTitleSize(0.06);
  mg->GetYaxis()->SetTitleSize(0.06);
  mg->GetXaxis()->SetLabelSize(0.05);
  mg->GetYaxis()->SetLabelSize(0.05);
  mg->GetYaxis()->SetTitleOffset(0.7);
  mg->GetXaxis()->SetTitleOffset(0.5);
  mg->GetYaxis()->SetNdivisions(6);
  mg->GetXaxis()->SetNdivisions(4);

  TLegend *legend = new TLegend(); // 0.3,0.6,0.6,0.88);
  // legend->AddEntry(xsec1gr,"Method 1","lep");
  legend->AddEntry(xsec2gr, "e#gamma CLAS12", "lep");
  legend->AddEntry(graph_KM, "KM15", "l");
  legend->AddEntry(graph_VGG, "VGG", "l");
  legend->AddEntry(graph_BH, "BH", "l");
  // legend->Draw();

  ///////////////////////////////
  // xsec at generator level (for curiosity/cross-check purposes)
  ///////////////////////////////
  /*
  TH1F *NDVCS = nullptr;
  TH1F *NDVCS_w = nullptr;
  TH1F *NDVCS_0 = nullptr;
  if (outputFile->Get("NDVCS") && false)
  {
    NDVCS = dynamic_cast<TH1F *>(outputFile->Get("NDVCS"));
  }
  else
  {
    // gSystem->Exec(Form("rm -rf %s%sNDVCS_hist.root",dir.Data(), Folder.Data()));
    NDVCS = new TH1F("NDVCS", "Original Data", NBinsPhi, 0, 360);
    NDVCS_w = new TH1F("NDVCS_w", "Original Data", NBinsPhi, 0, 360);
    NDVCS_0 = new TH1F("NDVCS_0", "Original Data", NBinsPhi, 0, 360);
    TChain *DVCSTreeMC = new TChain("pDVCS");
    DVCSTreeMC->Add(MC_BM_Sim);
  TString String_cut_mc = cut.GetTitle();
  String_cut_mc.ReplaceAll( cut_pid.GetTitle(), "bestCandidateFlag==1");
  TCut cut_MC = TCut(String_cut_mc);

    DVCSTreeMC->Project("NDVCS_w", "Phi_Nuc", (cut_MC + cut_bin + cut_kin + cut_sel) * TCut("(xsec_rad*2*TMath::Pi()/1000)")); // Phi_Nuc is the generated Phi in the bin
    DVCSTreeMC->Project("NDVCS_0", "Phi_Nuc", (cut_MC + cut_bin + cut_kin + cut_sel));                                         // Phi_Nuc is the generated Phi in the bin
    NDVCS->Divide(NDVCS_w, NDVCS_0, 1., 1.);
    NDVCS->SetMarkerStyle(20);
    NDVCS->SetMarkerColor(kRed);
    NDVCS->Write("NDVCS");
  }
  NDVCS->Draw("E0 SAME"); //For the Test

  std::cout << "\nGenerated events dvcsgen" << endl;
  for (int i = 1; i <= NBinsPhi; i++)
  {
    std::cout << " " << NDVCS->GetBinContent(i) << endl;
  }
  */
  ///////////////////////////////
  // Sangbaek xsec
  ///////////////////////////////

  std::ifstream inputPass1(Form("/work/clas12/jsalvg/pass2_RGA-Analysis/Sangbaek_Results/bin_%i.txt", bin));
  TGraphErrors *gr_SB = new TGraphErrors();

  if (!inputPass1)
  {
    std::cerr << "No Sangbaek data available." << std::endl;
  }
  while (std::getline(inputPass1, line))
  {

    std::vector<std::string> columns;
    columns.clear();
    std::string token;
    std::istringstream tokenStream(line);
    while (std::getline(tokenStream, token, '\t'))
    {
      columns.push_back(token);
    }

    double x = std::stod(columns[10]);
    double y = std::stod(columns[11]) * std::stod(columns[14]);
    double yErr = std::stod(columns[12]);
    gr_SB->SetPoint(gr_SB->GetN(), x, y);
    gr_SB->SetPointError(gr_SB->GetN() - 1, 0, yErr);
  }

  gr_SB->SetTitle("pass1");
  gr_SB->SetMarkerStyle(20); // circular markers
  gr_SB->SetMarkerColor(kCyan);
  gr_SB->SetLineColor(kCyan);
  gr_SB->SetLineWidth(2);
  gr_SB->SetName("pass1");
  gr_SB->SetTitle("pass1");

  gr_SB->Draw("PE0");

  canvas2->Print(Folder + TString("RGA_vs_This_xsec.pdf"));

  // Close the output file
  outputFile->Close();
  std::cout << "\nplots saved succesfully !" << endl;

  delete gr_SB;

  delete xsec1;
  delete xsec2;
  delete xsec1gr;
  delete xsec1gr_Sys;
  delete xsec2gr;
  delete xsec2gr_Sys;

  delete PS_factor;
  delete F_noRec;
  delete F_rad;

  delete NOrig;
  delete NMost;
  delete NMaxi;
  delete OrigErr1;
  delete OrigErr2;

  delete canvas2;
  Folder = Folder_old;

  return;
}
