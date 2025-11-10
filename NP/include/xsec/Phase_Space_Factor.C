
TH1F* BDT::Phase_Space_Factor1(int NBinsPhi, int bin)
{
  TChain* chain = new TChain("pDVCS");
  chain->Add(Folder + TString("../") + TDVCS);
  std::vector<TH2F*> Q2xB_Arr(NBinsPhi);
  std::vector<TH2F*> tphi_Arr(NBinsPhi);
  TH1F* PS = new TH1F("PS", "Phase Space Factor", NBinsPhi, 0, 360);
  double phi1, phi2;
  double eff_Qx, eff_tphi, eff, PS_Factor;

  int nsample=15;
  int lmax=10;
  for(int l=lmax;l<=lmax;l++)
  {
  PS_Factor = (boundaries.at(1) - boundaries.at(0))*(boundaries.at(3) - boundaries.at(2))*(boundaries.at(5) - boundaries.at(4))*(2*TMath::Pi()/NBinsPhi);  
  std::cout<<l<<"\nPhase space factor: "<< PS_Factor<<endl;
  for (int i = 0; i < NBinsPhi; ++i) 
  {
  phi1 = (2*TMath::Pi()/NBinsPhi)*i;
  phi2 = (2*TMath::Pi()/NBinsPhi)*(i + 1);


  Q2xB_Arr[i] = new TH2F(Form("Q2xB_%i",i), Form("Q2 vs Xbj %i",i), nsample, boundaries.at(4), boundaries.at(5), nsample, boundaries.at(2), boundaries.at(3));
  chain->Project(Form("Q2xB_%i",i), "strip_Q2:strip_Xbj",Form("EventNumber<%f",1000.*l));
  tphi_Arr[i] = new TH2F(Form("tphi_%i",i), Form("t_Ph vs Phi_Ph %i",i), nsample, boundaries.at(0), boundaries.at(1), nsample, phi1, phi2);
  chain->Project(Form("tphi_%i",i), "Phi_Ph:t_Ph",Form("EventNumber<%f",1000.*l));

  for (int ix = 1; ix <= Q2xB_Arr[i]->GetNbinsX(); ++ix) {
    for (int iy = 1; iy <= Q2xB_Arr[i]->GetNbinsY(); ++iy) {
      if (Q2xB_Arr[i]->GetBinContent(ix, iy) != 0) {
        Q2xB_Arr[i]->SetBinContent(ix, iy, 1);
      }
    }
  }

  for (int ix = 1; ix <= tphi_Arr[i]->GetNbinsX(); ++ix) {
    for (int iy = 1; iy <= tphi_Arr[i]->GetNbinsY(); ++iy) {
      if (tphi_Arr[i]->GetBinContent(ix, iy) != 0) {
        tphi_Arr[i]->SetBinContent(ix, iy, 1);
      }
    }
  }

  Q2xB_Arr[i]->Scale(1.0 / ((boundaries.at(3) - boundaries.at(2))*(boundaries.at(5) - boundaries.at(4))) );
  tphi_Arr[i]->Scale(1.0 / ((boundaries.at(1) - boundaries.at(0)) * (2 * TMath::Pi()/NBinsPhi)));

  eff_Qx = Q2xB_Arr[i]->Integral("width");
  eff_tphi = tphi_Arr[i]->Integral("width");
  eff = eff_Qx * eff_tphi;
  /*
  ///////////////////////////////
  //numerical area
  ///////////////////////////////

  if(bin>=1 && bin<=7)
  	eff_Qx = 0.7694;
  else if(bin>=27 && bin<=33)
  	eff_Qx = 0.2306;
  else if(bin>=8 && bin<=14)
  	eff_Qx = 1;
  else if(bin>=37 && bin<=40)
  	eff_Qx = 0.9905;
  else if(bin>=53 && bin<=59)
  	eff_Qx = 0.4247;
  else if(bin>=15 && bin<=21)
  	eff_Qx = 0.9654;
  else if(bin>=41 && bin<=47)
  	eff_Qx = 1;
  else if(bin>=60 && bin<=66)
  	eff_Qx = 0.9998;
  else if(bin>=74 && bin<=80)
  	eff_Qx = 0.4632;
  else if(bin>=22 && bin<=26)
  	eff_Qx = 0.1471;
  else if(bin>=48 && bin<=52)
  	eff_Qx = 0.6632;
  else if(bin>=67 && bin<=71)
  	eff_Qx = 0.9920;
  else if(bin>=81 && bin<=85)
  	eff_Qx = 0.9984;
  else if(bin>=88 && bin<=92)
  	eff_Qx = 0.3225;
  else if(bin>=72 && bin<=73)
  	eff_Qx = 0.1573;
  else if(bin>=86 && bin<=87)
  	eff_Qx = 0.7612;
  else if(bin>=93 && bin<=94)
  	eff_Qx = 0.8928;
  else
  	std::cout<<"Wrong bin"<<endl;

  eff = eff_Qx ;
  */
  PS_Factor = (boundaries.at(1) - boundaries.at(0))*(boundaries.at(3) - boundaries.at(2))*(boundaries.at(5) - boundaries.at(4))*(2*TMath::Pi()/NBinsPhi) * eff;  
  PS->SetBinContent(i + 1, PS_Factor);
  PS->SetBinError(i + 1, 0.0);
  
  std::cout <<" "<< PS_Factor << std::endl;
    
    if(l!=lmax)
    {
    delete Q2xB_Arr[i];
    delete tphi_Arr[i];
    }
  }
}
  TFile *outputFile = new TFile(Folder + TString("acc.root"), "RECREATE");
  // Close the output file
  for (int i = 0; i < NBinsPhi; ++i) {
    Q2xB_Arr[i]->Write();
    tphi_Arr[i]->Write();
  }
  outputFile->Close();
  std::cout<<"plots saved succesfully !"<<endl;
  delete outputFile;
  for (int i = 0; i < NBinsPhi; ++i) {
    delete Q2xB_Arr[i];
    delete tphi_Arr[i];
  }

  delete chain;
  return PS;
}



TH1F* BDT::Phase_Space_Factor(int NBinsPhi, int bin)
{
  //VGG computation
  std::cout<<"\nComputing VGG integral"<<endl;
  std::ifstream infile_vgg(Folder + TString("int_VGG.dat"));
    if (!infile_vgg.is_open()) 
  {
  //std::cout<<Form("./F_bin_VGG.sh %f %f %f %f %f %f %f ", boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0*boundaries.at(1), -1.0*boundaries.at(0), (360./NBinsPhi))<<endl;
   gSystem->Exec(Form("cp %sinclude/xsec/VGG/dvcs %s%s && cp %sinclude/xsec/VGG/F_bin_VGG.sh %s%s && cd %s%s && ./F_bin_VGG.sh %f %f %f %f %f %f %f && cat int.dat > int_VGG.dat && tac int.dat >> int_VGG.dat && rm int.dat && cd -",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0*boundaries.at(1), -1.0*boundaries.at(0), (360./NBinsPhi)));
	}
  infile_vgg.close();
  
  //KM computation
  std::cout<<"\nComputing KM integral"<<endl;
  std::ifstream infile_km(Folder + TString("int_KM.dat"));
    if (!infile_km.is_open() && false) 
  {
  //std::cout<<Form("./F_bin_KM.sh %f %f %f %f %f %f %f ", boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0*boundaries.at(1), -1.0*boundaries.at(0), (360./NBinsPhi))<<endl;
   gSystem->Exec(Form("cp -r %sinclude/xsec/VGG/* %s%s && cd %s%s && ./F_bin_KM.sh %f %f %f %f %f %f %f && cat int.dat > int_KM.dat && tac int.dat >> int_KM.dat && cd -",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0*boundaries.at(1), -1.0*boundaries.at(0), (360./NBinsPhi)));
	}
  infile_km.close();
  
  //BH computation
  std::cout<<"\nComputing BH integral"<<endl;
  gSystem->Exec(Form("cp -r %sinclude/xsec/VGG/* %s%s && cp %sinclude/xsec/VGG/F_bin.sh %s%s && cd %s%s && ./F_bin.sh %f %f %f %f %f %f %f >> /dev/null && cat int.dat > int_BH.dat && tac int.dat >> int_BH.dat && rm int.dat && cd -",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0*boundaries.at(1), -1.0*boundaries.at(0), (360./NBinsPhi)));
  std::ifstream infile(Folder + TString("int_BH.dat"));

  TH1F* PS = new TH1F("PS", "Phase Space Volume", NBinsPhi, 0., 360.);
  std::cout<<"\nPhase space factor: "<<endl;
  double col1, col2, col3, col4, col5, col6, col7, col8, col9;
  int binIdx = 1;
  while (binIdx <= NBinsPhi && infile >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8 >> col9) {
    PS->SetBinContent(binIdx, col4);
    PS->SetBinError(binIdx, 0.0); // Assuming no error information is provided
    std::cout<<" "<<col4<<" "<<col4*100/col3<<"%"<<endl;
    ++binIdx;
  }

  infile.close();
  return PS;
}
