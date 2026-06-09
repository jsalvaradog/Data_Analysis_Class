
TH1F* BDT::Phase_Space_Factor(int NBinsPhi, int bin)
{
  //VGG computation
  //std::cout<<"\nComputing VGG integral"<<endl;
  //std::ifstream infile_vgg(Folder + TString("int_VGG.dat"));  
  //BH computation
  std::cout<<"\nComputing PS factor from BH integral"<<endl;
  gSystem->Exec(Form("cp -r %sinclude/xsec/VGG/* %s%s && cp %sinclude/xsec/VGG/F_bin.sh %s%s && cd %s%s && ./F_bin.sh %f %f %f %f %f %f %f >> /dev/null && cat int.dat > int_BH.dat && tac int.dat >> int_BH.dat && rm int.dat && sed -i 's/nan/0/g' int_BH.dat && cd -",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0*boundaries.at(1), -1.0*boundaries.at(0), (360./NBinsPhi)));
  std::ifstream infile(Folder + TString("int_BH.dat"));

  TH1F* PS = new TH1F("PS", "Phase Space Volume", NBinsPhi, 0., 360.);
  std::cout<<"\nPhase space factor: "<<endl;
  double col1, col2, col3, col4, col5, col6, col7, col8, col9;
  int binIdx = 1;
  double maxPS=0;
  while (binIdx <= NBinsPhi && infile >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8 >> col9) {
    if(col4/col3>0.1)
    {
    PS->SetBinContent(binIdx, col4);
    PS->SetBinError(binIdx, 0.0); // Assuming no error information is provided
    }
    else
    {
    PS->SetBinContent(binIdx, 0);
    PS->SetBinError(binIdx, 0.0); // Assuming no error information is provided
    }
    if(col4>maxPS)
    	maxPS=col4;
    std::cout<<" "<<col4<<" "<<col4*100/col3<<"%"<<endl;
    ++binIdx;
  }
  //some points are underestimated.
  //for(int i=1; i<=NBinsPhi; i++)
  //{
  //    PS->SetBinContent(i, maxPS);
  //}

  infile.close();
  //return PS;

  double tmin = boundaries.at(0);
  double tmax = boundaries.at(1);
  double Q2min = boundaries.at(2);
  double Q2max = boundaries.at(3);
  double xBmin = boundaries.at(4);
  double xBmax = boundaries.at(5);

  double PS_Rectangle = (Q2max - Q2min) * (xBmax - xBmin) * (tmax - tmin) * (2.*TMath::Pi()/NBinsPhi);

  std::cout<<"\nComputing PS factor from MC events | "<<PS_Rectangle<<" "<<col4<<" "<<col3<<endl;

  TChain *DVCSTreeMC = new TChain("pDVCS");
  //DVCSTreeMC->Add(Folder + TString("../") + TDVCS);
  //DVCSTreeMC->Add(Folder + TString("../TDVCS_nABkg.root"));
  //DVCSTreeMC->Add(Folder + TString("../TDVCS_noBkg.root"));
  //DVCSTreeMC->Add(Folder + TString("../wf") + TBM_Sim);
  DVCSTreeMC->Add(Folder + TString("../") + TData);
  /*
  DVCSTreeMC->Add(Form("/volatile/clas12/jsalvg/simulation/dvcsgen/%s/withRC/Quality_DVCS_Train_NP.root", torus.Data()));
  DVCSTreeMC->Add(Form("/volatile/clas12/jsalvg/simulation/dvcsgen/%s/Quality_DVCS_NP_cache.root", torus.Data()));
  DVCSTreeMC->Add(Form("/volatile/clas12/jsalvg/simulation/dvcsgen/%s/Quality_DVCS_NP_nABkg.root", torus.Data()));
  DVCSTreeMC->Add(Form("/volatile/clas12/jsalvg/simulation/dvcsgen/%s/Quality_DVCS_NP_noBkg.root", torus.Data()));
  */
  Long64_t nentries = DVCSTreeMC->GetEntries();

  //TCut TheCut = "bestCandidateFlag==1";
  TString String_cut = cut_bin.GetTitle();
  String_cut.ReplaceAll("strip_Q2", "strip_Q2");
  String_cut.ReplaceAll("strip_Xbj", "strip_Xbj");
  String_cut.ReplaceAll("t_Ph", "t_Ph");
  TCut cut_bin_gen = TCut(String_cut);

  TCut TheCut = cut + cut_bin_gen + cut_kin + cut_sel;

  TH1F* PS_Factor = new TH1F("PS_Factor", "Phase Space Factor", NBinsPhi, 0., 360.);
  TH1F* h_choice = new TH1F("h_choice", "Choice", NBinsPhi, 0., 360.);

  int N_Q2 = 20; // Number of bins in Q^2
  int N_xb = 20; // Number of bins in x_B
  int N_t = 20; // Number of bins in t

  TH3F* Volume3D = new TH3F("Volume3D", "Phase Space Volume", N_Q2, Q2min, Q2max, N_xb, xBmin, xBmax, N_t, -tmax, -tmin);
  DVCSTreeMC->Project("Volume3D", "abs(t_Ph):strip_Xbj:strip_Q2", TheCut);// + CutPhi);
  // Set bins with content < 10 to zero
  for(int i=1; i<=N_Q2; i++) {
    for(int j=1; j<=N_xb; j++) {
      for(int k=1; k<=N_t; k++) {
        if(Volume3D->GetBinContent(i, j, k) < 1) {
          Volume3D->SetBinContent(i, j, k, 0);
        }
      }
    }
  }
  Volume3D->Divide(Volume3D);
  

  double Occupied=Volume3D->Integral()/(N_Q2*N_xb*N_t);  
  double err = 1.0/sqrt(Volume3D->Integral()); // Statistical error based on the number of entries in the histogram
  double Volume = Occupied*PS_Rectangle;

  for(int m=0; m<NBinsPhi; m++)
  {    
    double PhiCorr = PS->GetBinContent(m+1)*1.0/PS->GetBinContent(NBinsPhi/2);
    int choice=0;
    if(Occupied * PhiCorr > 0.1)
    {
      if(Volume * PhiCorr < PS->GetBinContent(m+1))
      {
        PS_Factor->SetBinContent(m+1, PS->GetBinContent(m+1));
        PS_Factor->SetBinError(m+1, PS->GetBinError(m+1)); // Assuming no error information is provided
        h_choice->SetBinContent(m+1, 1);
      }
      else
      {
        PS_Factor->SetBinContent(m+1, Volume * PhiCorr);
        PS_Factor->SetBinError(m+1, err*Volume * PhiCorr); // Assuming no error information is provided
        h_choice->SetBinContent(m+1, 2);
      }

    std::cout<<" "<<Volume * PhiCorr<<" "<<Occupied * PhiCorr * 100.0<<"% (vol), "<<Volume/PS->GetBinContent(m+1)*100<<"% (vol_fid) "<<err*100<<"% (stat) "<<" | Entries: "<<nentries<<endl;
    }
    else
    {
    PS_Factor->SetBinContent(m+1, 0.0);
    PS_Factor->SetBinError(m+1, 0.0); // Assuming no error information is provided
    }
  }
  std::cout<<"\nFinal PS Factor & choice (max)"<<endl;
  for(int m=0; m<NBinsPhi; m++)
  {
    std::cout<<" "<<PS_Factor->GetBinContent(m+1)<<" "<<PS_Factor->GetBinError(m+1)<<" "<<h_choice->GetBinContent(m+1)<<endl;
  }
  
  // save PS_Factor to acc.root
  TFile *f_acc = new TFile(Folder + TString("acc.root"), "RECREATE");
  Volume3D->Write("Volume3D");
  f_acc->Close();
  delete f_acc;

  delete Volume3D;
  delete PS;
  delete h_choice;


  return PS_Factor;

}


/*
TH1F* BDT::Phase_Space_Factor(int NBinsPhi, int bin)
{
  std::cout<<"\nComputing PS factor from MC events"<<endl;

  TChain *DVCSTreeMC = new TChain("pDVCS");
  DVCSTreeMC->Add(Folder + TString("../") + TDVCS);
  DVCSTreeMC->Add(Folder + TString("../TDVCS_nABkg.root"));
  DVCSTreeMC->Add(Folder + TString("../TDVCS_noBkg.root"));
  Long64_t nentries = DVCSTreeMC->GetEntries();

  //TCut TheCut = "bestCandidateFlag==1";
  TString String_cut = cut_bin.GetTitle();
  String_cut.ReplaceAll("strip_Q2", "strip_Q2");
  String_cut.ReplaceAll("strip_Xbj", "strip_Xbj");
  String_cut.ReplaceAll("t_Ph", "t_Ph");
  TCut cut_bin_gen = TCut(String_cut);

  TCut TheCut = cut + cut_bin_gen + cut_kin + cut_sel;

  TH1F* PS_Factor = new TH1F("PS_Factor", "Phase Space Factor", NBinsPhi, 0., 360.);

  int N_Q2 = 20; // Number of bins in Q^2
  int N_xb = 20; // Number of bins in x_B
  int N_t = 20; // Number of bins in t

  double tmin = boundaries.at(0);
  double tmax = boundaries.at(1);
  double Q2min = boundaries.at(2);
  double Q2max = boundaries.at(3);
  double xBmin = boundaries.at(4);
  double xBmax = boundaries.at(5);

  for(int m=0; m<NBinsPhi; m++)
    {
      double PS_Rectangle = (Q2max - Q2min) * (xBmax - xBmin) * (tmax - tmin) * (2.*TMath::Pi()/NBinsPhi);
      double phi_min = m*360./NBinsPhi;
      double phi_max = (m+1)*360./NBinsPhi;

      TCut CutPhi = TCut(Form("Phi_Ph>%f && Phi_Ph<%f", phi_min, phi_max));
      TH3F* Volume3D = new TH3F("Volume3D", "Phase Space Volume", N_Q2, Q2min, Q2max, N_xb, xBmin, xBmax, N_t, tmin, tmax);
      DVCSTreeMC->Project("Volume3D", "t_Ph:strip_Xbj:strip_Q2", TheCut);// + CutPhi);
      Volume3D->Divide(Volume3D);

      double Occupied=Volume3D->Integral()/(N_Q2*N_xb*N_t);  
      double err = 1.0/sqrt(Volume3D->Integral()); // Statistical error based on the number of entries in the histogram
      double Volume = Occupied*PS_Rectangle;
      
      PS_Factor->SetBinContent(m+1, Volume);
      PS_Factor->SetBinError(m+1, err*Volume); // Assuming no error information is provided
      std::cout<<" "<<Volume<<" "<<Occupied*100.0<<"% (vol), "<<err*100<<"% (stat) "<<" | Entries: "<<nentries<<endl;
      delete Volume3D;
    }

  return PS_Factor;
}
*/