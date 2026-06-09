TGraph* BDT::Theory_integral_generator(int model, int bin)
{
  TString model_str;
  int model_val;
  int NBinsPhi = Nphibins[bin - 1];
  TGraph *graph = new TGraph(NBinsPhi);
  switch (model)
  {
  case 1:
    model_str = TString("BH");
    model_val = 35;
    graph->SetMarkerColor(kRed);
    graph->SetLineColor(kRed);
    break;
  case 2:
    model_str = TString("VGG");
    model_val = 35;
    graph->SetMarkerColor(kOrange);
    graph->SetLineColor(kOrange);
    break;
  case 3:
    model_str = TString("KM");
    model_val = 63;
    graph->SetMarkerColor(kCyan);
    graph->SetLineColor(kCyan);

    break;
  case 4:
    model_str = TString("GK");
    model_val = 99;
    graph->SetMarkerColor(kGreen + 2);
    graph->SetLineColor(kGreen + 2);
    break;
  }

  TString filename = Form("%sxsec_km15gen_output_%s/%s/bin_%i.root", dir.Data(), torus.Data(), model_str.Data(), bin);
  std::ifstream file(filename);

  TRandom3 rng(0);                 // 0 = seed from system time
  int seed = rng.Integer(1000000); // random integer in [0, 99]

  if (file.good() && false)
  {
    std::cerr << "Theory files exist for " << model_str << std::endl;
  }
  else
  {
    std::cout << "Creating theory prediction through event generator " << model_str << endl;
    gSystem->Exec(Form("rm -rf %s%s/VGG && cp -r %sinclude/xsec/VGG %s%s", dir.Data(), Folder.Data(), dir.Data(), dir.Data(), Folder.Data()));
    if (model == 1)
    {
      // BH computation
      std::cout << "Generating BH events" << endl;
      gSystem->Exec(Form("cp -rf /work/clas12/jsalvg/km15gen/ %s%s && cd %s%skm15gen && python3 main.py -trig 100000 -model km15_bh -tmin %f -tmax %f -Q2min %f -Q2max %f -xBmin %f -xBmax %f -ymax 0.92 >> /dev/null && mv km15gen.dat %sxsec_km15gen_output_%s/BH/bin_%i.dat && clas12root -l -b -q lund2root_Sangbaek_bins.C\\(%i,1,%i\\) && cd - && rm -rf %s%skm15gen ", dir.Data(), Folder.Data(), dir.Data(), Folder.Data(), -1.0 * boundaries.at(1), -1.0 * boundaries.at(0), boundaries.at(2), boundaries.at(3), boundaries.at(4), boundaries.at(5), dir.Data(), torus.Data(), bin, bin, itorus, dir.Data(), Folder.Data()));
    }
    else if (model == 2)
    {
      // VGG computation
      std::cout << "Generating VGG events" << endl;
      gSystem->Exec(Form("cp -rf /work/clas12/jsalvg/km15gen/ %s%s && cd %s%skm15gen && python3 main.py -seed %i -trig 100000 -model vgg -tmin %f -tmax %f -Q2min %f -Q2max %f -xBmin %f -xBmax %f -ymax 0.92>> /dev/null && mv dvcsgen.dat %sxsec_km15gen_output_%s/VGG/bin_%i.dat && clas12root -l -b -q lund2root_Sangbaek_bins.C\\(%i,2,%i\\) && cd - && rm -rf %s%skm15gen ", dir.Data(), Folder.Data(), dir.Data(), Folder.Data(), seed, -1.0 * boundaries.at(1), -1.0 * boundaries.at(0), boundaries.at(2), boundaries.at(3), boundaries.at(4), boundaries.at(5), dir.Data(), torus.Data(), bin, bin, itorus, dir.Data(), Folder.Data()));
    }
    else if (model == 3 || model == 4)
    {
      // KM computation
      std::cout << "Generating KM events" << endl;
      gSystem->Exec(Form("cp -rf /work/clas12/jsalvg/km15gen/ %s%s && cd %s%skm15gen && python3 main.py -trig 10000 -model km15 -tmin %f -tmax %f -Q2min %f -Q2max %f -xBmin %f -xBmax %f -ymax 0.92 >> /dev/null && mv km15gen.dat %sxsec_km15gen_output_%s/KM/bin_%i.dat && clas12root -l -b -q lund2root_Sangbaek_bins.C\\(%i,3,%i\\) && cd - && rm -rf %s%skm15gen ", dir.Data(), Folder.Data(), dir.Data(), Folder.Data(), -1.0 * boundaries.at(1), -1.0 * boundaries.at(0), boundaries.at(2), boundaries.at(3), boundaries.at(4), boundaries.at(5), dir.Data(), torus.Data(), bin, bin, itorus, dir.Data(), Folder.Data()));
    }
    else
    {
      std::cout << "Model not implemented" << endl;
      return nullptr;
    }
  }

  TString String_cut = (cut_bin + cut_kin + cut_sel + cut_ref).GetTitle();
  String_cut.ReplaceAll("bestCandidateFlag==1 && ", "");
  String_cut.ReplaceAll("_strip_Nuc_BDT_SIDIS", "Q2_meas");
  String_cut.ReplaceAll("strip_Q2", "Q2_meas");
  String_cut.ReplaceAll("strip_Xbj", "xB_meas");
  String_cut.ReplaceAll("t_Ph", "t_meas");
  String_cut.ReplaceAll("strip_El_P", "El_E");
  String_cut.ReplaceAll("strip_Ph_P", "Ph_E");
  String_cut.ReplaceAll("strip_Ph_Theta", "Ph_Theta");
  String_cut.ReplaceAll("strip_El_Theta", "El_Theta");
  TCut cut0 = TCut(String_cut);

  TFile *acc_file = TFile::Open(Folder + TString("acc.root"), "READ");
  TH3F *Volume3D = nullptr;
  if (acc_file && !acc_file->IsZombie())
  {
    Volume3D = dynamic_cast<TH3F *>(acc_file->Get("Volume3D"));
    if (!Volume3D)
      std::cerr << "Could not find TH3F 'Volume3D' in acc.root" << std::endl;
  }
  else
  {
    std::cerr << "Could not open acc.root" << std::endl;
  }

  TChain *tree1 = new TChain("tree");
  tree1->Add(Form("%sxsec_km15gen_output_%s/%s/bin_%i.root", dir.Data(), torus.Data(), model_str.Data(), bin));
  TH1F *DVCS_bh = new TH1F("DVCS_bh", "", NBinsPhi, 0, 360);
  TH1F *DVCS_bh1 = new TH1F("DVCS_bh1", "", NBinsPhi, 0, 360);
  TH1F *DVCS_bh2 = new TH1F("DVCS_bh2", "", NBinsPhi, 0, 360);
  DVCS_bh1->Sumw2();
  DVCS_bh2->Sumw2();
  TCut wCut = (model==2) ? TCut("(xsec_born*2*TMath::Pi()/1000)") : TCut("xsec_born");
  //tree1->Project("DVCS_bh1", "phi_meas", (cut0 + TCut("Q2_meas>1")) * wCut);
  //tree1->Project("DVCS_bh2", "phi_meas", (cut0 + TCut("Q2_meas>1"))"));
  static Float_t Q2_meas, xB_meas, t_meas, phi_meas, xsec_born;
  tree1->SetBranchAddress("Q2_meas", &Q2_meas);
  tree1->SetBranchAddress("xB_meas", &xB_meas);
  tree1->SetBranchAddress("t_meas", &t_meas);
  tree1->SetBranchAddress("phi_meas", &phi_meas);
  tree1->SetBranchAddress("xsec_born", &xsec_born);
  for(int i=0; i<tree1->GetEntries(); i++)
  {
    tree1->GetEntry(i);
    double acceptance = Volume3D->GetBinContent(Volume3D->FindBin(Q2_meas, xB_meas, abs(t_meas)));
    double weight = (model==2) ? (xsec_born*2*TMath::Pi()/1000) : xsec_born;
    DVCS_bh1->Fill(phi_meas, weight * acceptance);
    DVCS_bh2->Fill(phi_meas, acceptance);
  }
  DVCS_bh->Divide(DVCS_bh1, DVCS_bh2, 1, 1);


  for (int i = 1; i <= NBinsPhi; ++i)
  {
    double x = DVCS_bh->GetBinCenter(i);
    double y = DVCS_bh->GetBinContent(i);
    graph->SetPoint(graph->GetN(), x, y);
  }
  graph->SetMarkerStyle(20); // circular markers
  graph->SetLineWidth(2);
  graph->SetLineStyle(kDashed); // dashed line
  graph->SetName(model_str);
  graph->SetTitle(model_str);

  delete DVCS_bh;
  delete DVCS_bh1;
  delete DVCS_bh2;
  delete Volume3D;
  delete acc_file;
  delete tree1;

  return graph;
}


TGraph* BDT::Theory_integral(int model, int bin, int Nphi)
{
  TString model_str;
  int model_val;
  TGraph* graph = new TGraph();
  switch (model)
  {
  case 1:
    model_str = TString("BH");
    model_val = 35;
    graph->SetMarkerColor(kRed);
    graph->SetLineColor(kRed);
    break;
  case 2:
    model_str = TString("VGG");
    model_val = 35;
    graph->SetMarkerColor(kOrange);
    graph->SetLineColor(kOrange);
    break;
  case 3:
    model_str = TString("KM");
    model_val = 63;
    graph->SetMarkerColor(kCyan);
    graph->SetLineColor(kCyan);
    break;
  case 4:
    model_str = TString("GK");
    model_val = 99;
    graph->SetMarkerColor(kRed);
    graph->SetLineColor(kRed);
    break;
  }

  TString filename = extXSEC + model_str + Form("/bin_%i.txt", bin);
  std::ifstream file(filename);

  if (file.good() && false)
  {
    std::cerr << "Theory files exist for " << model_str << std::endl;
  }
  else
  {
    std::cout << "Creating theory prediction for " << model_str << endl;
    gSystem->Exec(Form("rm -rf %s%s/VGG && cp -r %sinclude/xsec/VGG %s%s", dir.Data(), Folder.Data(), dir.Data(), dir.Data(), Folder.Data()));
    if (model == 1)
    {
      // BH computation
      std::cout << "Computing BH integral" << endl;
      gSystem->Exec(Form("cp -r %sinclude/xsec/VGG/* %s%s && cp %sinclude/xsec/VGG/F_bin.sh %s%s && cd %s%s && ./F_bin.sh %f %f %f %f %f %f %f >> /dev/null && cat int.dat > int_BH.dat && tac int.dat >> int_BH.dat && rm int.dat && mv int_BH.dat VGG/phi.dat && cd -", dir.Data(), dir.Data(), Folder.Data(), dir.Data(), dir.Data(), Folder.Data(), dir.Data(), Folder.Data(), boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0 * boundaries.at(1), -1.0 * boundaries.at(0), (360. / Nphi)));
    }
    else if (model == 2)
    {
      // VGG computation
      std::cout << "Computing VGG integral" << endl;
      gSystem->Exec(Form("cp -r %sinclude/xsec/VGG/* %s%s && cp %sinclude/xsec/VGG/F_bin_VGG.sh %s%s && cd %s%s && ./F_bin_VGG.sh %f %f %f %f %f %f %f >> /dev/null && cat int.dat > int_VGG.dat && tac int.dat >> int_VGG.dat && rm int.dat && mv int_VGG.dat VGG/phi.dat && cd -", dir.Data(), dir.Data(), Folder.Data(), dir.Data(), dir.Data(), Folder.Data(), dir.Data(), Folder.Data(), boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0 * boundaries.at(1), -1.0 * boundaries.at(0), (360. / Nphi)));
    }
    else if (model == 3 || model == 4)
    {
      // KM computation
      std::cout << "Computing KM integral" << endl;
      gSystem->Exec(Form("cp -r %sinclude/xsec/VGG/* %s%s && cp %sinclude/xsec/VGG/F_bin_KM.sh %s%s && cd %s%s && ./F_bin_KM.sh %f %f %f %f %f %f %f >> /dev/null && cat int.dat > int_KM.dat && tac int.dat >> int_KM.dat && rm int.dat && mv int_KM.dat VGG/phi.dat && cd -", dir.Data(), dir.Data(), Folder.Data(), dir.Data(), dir.Data(), Folder.Data(), dir.Data(), Folder.Data(), boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0 * boundaries.at(1), -1.0 * boundaries.at(0), (360. / Nphi)));
    }
    else
    {
      std::cout << "Model not implemented" << endl;
      return nullptr;
    }
    gSystem->Exec(TString("cp ") + Folder + TString("VGG/phi.dat ") + extXSEC + model_str + Form("/bin_%i.txt", bin));
    gSystem->Exec("rm -r " + Folder + TString("VGG"));
  }

  std::ifstream inputFile;
  std::string line;
  double x1, x2, aux, y;
  int ibh = 0;
  inputFile.open(extXSEC + Form("%s/bin_%i.txt", model_str.Data(), bin)); // Replace with the name of the block file you want to read
  while (std::getline(inputFile, line))
  {
    std::istringstream iss(line);
    iss >> x1 >> x2 >> aux >> aux >> aux >> aux >> aux >> aux >> y;
    graph->AddPoint((x2 - x1) * (ibh + 0.5), y);
    ibh++;
  }
  inputFile.close();
  
  graph->SetLineWidth(2);
  graph->SetLineStyle(kDashed);
  graph->SetTitle(model_str);
  graph->SetName(model_str);

  return graph;
}

TGraph* BDT::Theory_point(int model, int bin, double xmean, double Qmean, double tmean, int Nphi)
{
  TString model_str;
  int model_val;
  TGraph* graph = new TGraph();
  switch (model)
  {
  case 1:
    model_str = TString("BH");
    model_val = 35;
    graph->SetMarkerColor(kRed);
    graph->SetLineColor(kRed);
    break;
  case 2:
    model_str = TString("VGG");
    model_val = 35;
    graph->SetMarkerColor(kOrange);
    graph->SetLineColor(kOrange);
    break;
  case 3:
    model_str = TString("KM");
    model_val = 63;
    graph->SetMarkerColor(kCyan);
    graph->SetLineColor(kCyan);
    break;
  case 4:
    model_str = TString("GK");
    model_val = 99;
    graph->SetMarkerColor(kRed);
    graph->SetLineColor(kRed);
    break;
  }

  TString filename = extXSEC + model_str + Form("/bin_%i.txt", bin);
  std::ifstream file(filename);

  if (file.good() && false)
  {
    std::cerr << "Theory files exist for " << model_str << std::endl;
  }
  else
  {
    std::cout << "Creating theory prediction for " << model_str << endl;
    gSystem->Exec(Form("rm -rf %s%s/VGG && cp -r %sinclude/xsec/VGG %s%s", dir.Data(), Folder.Data(), dir.Data(), dir.Data(), Folder.Data()));
    if (model == 1)
    {
    gSystem->Exec(TString("cd ") + Folder + Form("VGG && ( \
        echo 3 && \
        echo 4 && \
        echo 1 && \
        echo 1 && \
        echo 3 && \
        echo 1 && \
        echo 10.6 && \
        echo 3 && \
        echo %f && \
        echo %f && \
        echo 0 && \
        echo %f && \
        echo %f && \
        echo %f && \
        echo 360) | ./dvcs >> /dev/null && \
        mv dvcs_* phi.dat && cd -", Qmean, xmean, -1.0*tmean, 360.*0.5/Nphi, 360./60));        
    }
    else if (model == 2)
    {
      gSystem->Exec(TString("cd ") + Folder + Form("VGG && ( \
    echo 3 && \
    echo 4 && \
    echo 3 && \
    echo 1 && \
    echo %i && \
    echo 1 && \
    echo 5 && \
    echo 8 && \
    echo 1.098 && \
    echo 2 && \
    echo 2 && \
    echo 2 && \
    echo 0.3 && \
    echo 0.3 && \
    echo 1 && \
    echo 1 && \
    echo 1 && \
    echo 3 && \
    echo 1 && \
    echo 10.6 && \
    echo 3 && \
    echo %f && \
    echo %f && \
    echo 0 && \
    echo %f && \
    echo %f && \
    echo %f && \
    echo 360) | ./dvcs >> /dev/null && \
    mv dvcs_* phi.dat && cd -",
                                                   model_val, Qmean, xmean, -1.0 * tmean, 360. * 0.5 / Nphi, 360. / Nphi));
    }
    else if (model == 3 || model == 4)
    {
      gSystem->Exec(TString("cd ") + Folder + Form("VGG && ( \
    echo 3 && \
    echo 4 && \
    echo 3 && \
    echo 1 && \
    echo %i && \
    echo 2 && \
    echo 2 && \
    echo 1 && \
    echo 1 && \
    echo 1 && \
    echo 3 && \
    echo 1 && \
    echo 10.6 && \
    echo 3 && \
    echo %f && \
    echo %f && \
    echo 0 && \
    echo %f && \
    echo %f && \
    echo %f && \
    echo 360) | ./dvcs >> /dev/null && \
    mv dvcs_* phi.dat && cd -",
                                                   model_val, Qmean, xmean, -1.0 * tmean, 360. * 0.5 / Nphi, 360. / Nphi));
    }
    else
    {
      std::cout << "Model not implemented" << endl;
      return nullptr;
    }
    gSystem->Exec(TString("cp ") + Folder + TString("VGG/phi.dat ") + extXSEC + model_str + Form("/bin_%i.txt", bin));
    gSystem->Exec("rm -r " + Folder + TString("VGG"));
  }

  std::ifstream inputFile;
  std::string line;
  double x, x1, x2, aux, y;
  int ibh = 0;
  inputFile.open(extXSEC + Form("%s/bin_%i.txt", model_str.Data(), bin)); // Replace with the name of the block file you want to read
  while (std::getline(inputFile, line))
  {
    std::istringstream iss(line);
    iss >> x >> aux >> aux >> aux >> aux >> y;
    graph->AddPoint(x, y);
  }
  inputFile.close();
  
  graph->SetLineWidth(2);
  graph->SetLineStyle(kDashed);
  graph->SetTitle(model_str);
  graph->SetName(model_str);

  return graph;
}
