std::vector<vector<double>> BDT::ReadMeansFile(TString file) {
  // Variables to store the column values
  double col1, col2, col3, col4, col5, col6, col7, col8;
  std::vector<vector<double>> means;
  std::vector<double> line;
  means.clear();

  // Open the input file
  std::ifstream inputFile(file);
  if (!inputFile.is_open()) {
    std::cerr << "Error: Unable to open " << file<< std::endl;
    return means;
  }

    
  // Read and discard the first line (header)
  std::string header;
  std::getline(inputFile, header);

  // Read and process the remaining lines
  while (inputFile >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8) 
    {
      line.clear();
      line.push_back(col1);
      line.push_back(col2);
      line.push_back(col3);
      line.push_back(col4);
      line.push_back(col5);
      line.push_back(col6);
      line.push_back(col7);
      line.push_back(col8);
      means.push_back(line);
    }

  // Close the input file
  inputFile.close();

  return means;

}


TH1F* BDT::F_4Dto3D(double xmean, double Qmean, double tmean, int Nphi, int select) {

  std::vector<vector<double>> means;
  char command[200];
  int n;
  TH1F *ratio_bin = new TH1F("ratio_bin","F_423",Nphi,0,360);
  
  if(select==1)
    means = ReadMeansFile(Folder + TString("../means_most.txt"));
  else
    means = ReadMeansFile(Folder + TString("../means_maxi.txt"));

  for(int m=0; m<Nphi; m++)
    {
      printProgress(m*1.0/Nphi);

      double pm=means.at(m).at(0);
      double tm=means.at(m).at(2);
      double Qm=means.at(m).at(4);
      double xm=means.at(m).at(6);
      
      double Phimean = (360./Nphi)*(m+0.5);
      std::string base_dir(dir.Data());
      n=sprintf (command, "python3 %s/include/xsec/4Dto3D.py %f %f %f %f %f %f %f %f",base_dir.c_str(), xmean, Qmean, tmean, Phimean, xm, Qm, tm, pm);

      //printf ("[%s] is a string %d chars long\n",command,n);
      // Open a pipe and execute the command
      FILE* pipe = popen(command, "r");
      if (!pipe) {
	fprintf(stderr, "Error executing Python script.\n");
	std::cout<<command<<endl;
	return ratio_bin;
      }

      // Read the output from the pipe
      float F_bin;
      int readCount = fscanf(pipe, "%f", &F_bin);

      if (readCount != 1) {
	fprintf(stderr, "Error reading numbers from Python script.\n");
	std::cout<<command<<endl;
      }
      // Close the pipe
      pclose(pipe);
  
  
      //std::cout<<"corr factor "<<m+1<<" "<<F_bin<<endl;
      ratio_bin->SetBinContent(m+1,F_bin);
      ratio_bin->SetBinError(m+1,0.0);
    }
  
  std::cout<<"4D to 3D correction"<<endl;
  for(int k=1; k<=Nphi; k++)
    std::cout<<ratio_bin->GetBinContent(k)<<std::endl;
  
  return ratio_bin;
}

TH1F* BDT::F_bin_KM_model(int bin, double mean3d_t, double mean3d_Q, double mean3d_x) {

  int Nphi=Nphibins[bin-1];
  std::vector<vector<double>> means;
  char command[200];
  int n;
  TH1F *ratio_bin = new TH1F("ratio_bin","F_bin",Nphi,0,360);
  
  std::cout<<"\nBin centering correction"<<endl;
  for(int m=0; m<Nphi; m++)
    {
      printProgress(m*1.0/Nphi);
      means = ReadMeansFile(Folder + TString("../means_maxi.txt"));
      double pm=means.at(m).at(0);
      double tm=means.at(m).at(2);
      double Qm=means.at(m).at(4);
      double xm=means.at(m).at(6);
    
      //n=sprintf (command, "python3 /work/clas12/jsalvg/pass2_RGA-Analysis/inb/NP_SA/include/xsec/KM15.py %f %f %f %f %f %f %f %f %f %f %f %f",bins[bin-1][0],bins[bin-1][1],bins[bin-1][2],bins[bin-1][3],bins[bin-1][4],bins[bin-1][5], (360./Nphi)*m, (360./Nphi)*(m+1), xm, tm, Qm, pm);
      n=sprintf (command, "python3 %sinclude/xsec/KM15.py %f %f %f %f %f %f %f %f %f %f %f %f", dir.Data(),bins[bin-1][0],bins[bin-1][1],bins[bin-1][2],bins[bin-1][3],bins[bin-1][4],bins[bin-1][5], (360./Nphi)*m, (360./Nphi)*(m+1), mean3d_x, mean3d_t, mean3d_Q, 360.*(m+0.5)/Nphi);

      //printf ("[%s] is a string %d chars long\n",command,n);
      // Open a pipe and execute the command
      FILE* pipe = popen(command, "r");
      if (!pipe) {
	fprintf(stderr, "Error executing Python script.\n");
	std::cout<<command<<endl;
	return ratio_bin;
      }

      // Read the output from the pipe
      float F_bin;
      int readCount = fscanf(pipe, "%f", &F_bin);

      if (readCount != 1) {
	fprintf(stderr, "Error reading numbers from Python script.\n");
	std::cout<<command<<endl;
      }
      // Close the pipe
      pclose(pipe);
  
  
      std::cout<<" "<<m+1<<" "<<F_bin<<endl;
      ratio_bin->SetBinContent(m+1,F_bin);
      ratio_bin->SetBinError(m+1,0.0);
    }
  
  return ratio_bin;
}



TH1F* BDT::F_Bin(int bin, double mean3d_t, double mean3d_Q, double mean3d_x, int select, TH1F* PS_factor) {

  int Nphi=Nphibins[bin-1];
  TH1F *ratio_bin1 = new TH1F("ratio_bin1","F_bin1",Nphi,0,360);

  // Check if xsec_dists.root exists and read F_bin1 if available
  TFile *f = TFile::Open(Folder + TString("xsec_dists.root"), "READ");
  if (f && !f->IsZombie() && false) {
      if(select==1)
      {
        ratio_bin1 = dynamic_cast<TH1F*>(f->Get("F_Bin_Michel_Model"));
      }
      else
      {
        ratio_bin1 = dynamic_cast<TH1F*>(f->Get("F_Bin_Michel_Model"));
      }
    //f->Close();
    //delete f;
    std::cout<<"\nF_Bin found on file! "<<endl;
    for(int k=1; k<=Nphi; k++)
      std::cout<<" "<<ratio_bin1->GetBinContent(k)<<" "<<ratio_bin1->GetBinError(k)*100<<"%"<<endl;

      return ratio_bin1;
    }
  else
  {
  cout<<"xsec_dists.root not found or is corrupted. Recalculating F_Bin..."<<endl;
  std::vector<vector<double>> means;
  char command0[500];
  char command1[500];
  char command2[500];
  int n0, n1, n2;
  TH1F *ratio_bin2 = new TH1F("ratio_bin2","F_bin2",Nphi,0,360);
  
  if(select==1)
    means = ReadMeansFile(Folder + TString("../means_most.txt"));
  else
    means = ReadMeansFile(Folder + TString("../means_maxi.txt"));

  double pm, tm, Qm, xm;
        ///////////////////////////////
        //Integration of BH on bins is done on Phase_Space_Factor.C
        ///////////////////////////////

        double col1, col2, col3, col4, col5, col6, col7, col8, col9;
        std::ifstream infile(Folder + TString("int_BH.dat"));
        if (!infile.is_open()) 
        {
          std::cerr << "Error opening file int_BH.dat." << std::endl;
          return nullptr;
        }

        std::ifstream infile_vgg(Folder + TString("int_VGG.dat"));
        if (!infile_vgg.is_open()) 
        {
          std::cerr << "Error opening file int_VGG.dat." << std::endl;
          return nullptr;
        }

        std::ifstream infile_km(Folder + TString("int_VGG.dat"));
        if (!infile_km.is_open()) 
        {
          std::cerr << "Error opening file int_KM.dat." << std::endl;
          return nullptr;
        }

        ///////////////////////////////
        //// Get average cross section from dvcsgen BH events  ////
        ///////////////////////////////
  TString String_cut = (cut_bin + cut_ref).GetTitle();
  String_cut.ReplaceAll("bestCandidateFlag==1 && ", "");
  String_cut.ReplaceAll("_strip_Nuc_BDT_SIDIS", "Q2_meas");
  String_cut.ReplaceAll("strip_Q2", "Q2_meas");
  String_cut.ReplaceAll("strip_Xbj", "xB_meas");
  String_cut.ReplaceAll("t_Ph", "t_meas");
  String_cut.ReplaceAll("strip_El_P", "El_E");
  String_cut.ReplaceAll("strip_Ph_P", "Ph_E");
        TCut cut = TCut(String_cut);

        gSystem->Exec(Form("cp -rf /work/clas12/jsalvg/km15gen/ %s%s && cd %s%skm15gen && python3 main.py -trig 100000 -model km15_bh -bin %i >> /dev/null && mv km15gen.dat /work/clas12/jsalvg/km15gen_output_%s/BH/bin_%i.dat && clas12root -l -b -q lund2root.C\\(%i,1,%i\\) && cd - && rm -rf %s%skm15gen ",dir.Data(), Folder.Data(),dir.Data(), Folder.Data(),bin, torus.Data(),bin,bin,itorus,dir.Data(), Folder.Data()));
        //TCut cut = TCut(String_cut);
        // Read .root and compute number of events in kinematic bin Mbins[bin-1], scale by external weight using Project
        TChain* tree1 = new TChain("tree");
        tree1->Add(Form("/work/clas12/jsalvg/km15gen_output_%s/BH/bin_%i.root", torus.Data(), bin));
        TH1F *DVCS_bh = new TH1F("DVCS_bh","", Nphi, 0, 360);
        TH1F *DVCS_bh1 = new TH1F("DVCS_bh1","", Nphi, 0, 360);
        TH1F *DVCS_bh2 = new TH1F("DVCS_bh2","", Nphi, 0, 360);
        DVCS_bh1->Sumw2();
        DVCS_bh2->Sumw2();
        tree1->Project("DVCS_bh1", "phi_meas", (cut + TCut("Q2_meas>1"))*TCut("(xsec_born)")); //9.803 RC 9.376 noRC
        tree1->Project("DVCS_bh2", "phi_meas", (cut + TCut("Q2_meas>1"))); //9.803 RC 9.376 noRC
        DVCS_bh->Divide(DVCS_bh1, DVCS_bh2, 1, 1);
        //DVCS_bh->Scale(1.0/(2.*TMath::Pi()/16));

        gSystem->Exec(Form("cp -rf /work/clas12/jsalvg/km15gen/ %s%s && cd %s%skm15gen && python3 main.py -trig 100000 -model vgg -bin %i >> /dev/null && mv dvcsgen.dat /work/clas12/jsalvg/km15gen_output_%s/VGG/bin_%i.dat && clas12root -l -b -q lund2root.C\\(%i,2,%i\\) && cd - && rm -rf %s%skm15gen ",dir.Data(), Folder.Data(),dir.Data(), Folder.Data(),bin, torus.Data(),bin,bin,itorus,dir.Data(), Folder.Data()));
        //TCut cut = TCut(String_cut);
        // Read .root and compute number of events in kinematic bin Mbins[bin-1], scale by external weight using Project
        TChain* tree2 = new TChain("tree");
        tree2->Add(Form("/work/clas12/jsalvg/km15gen_output_%s/VGG/bin_%i.root", torus.Data(), bin));
        TH1F *DVCS_dvcsgen = new TH1F("DVCS_dvcsgen","", Nphi, 0, 360);
        TH1F *DVCS_dvcsgen1 = new TH1F("DVCS_dvcsgen1","", Nphi, 0, 360);
        TH1F *DVCS_dvcsgen2 = new TH1F("DVCS_dvcsgen2","", Nphi, 0, 360);
        DVCS_dvcsgen1->Sumw2();
        DVCS_dvcsgen2->Sumw2();
        tree2->Project("DVCS_dvcsgen1", "phi_meas", (cut + TCut("Q2_meas>1"))*TCut("(xsec_born/100)")); //9.803 RC 9.376 noRC
        tree2->Project("DVCS_dvcsgen2", "phi_meas", (cut + TCut("Q2_meas>1"))); //9.803 RC 9.376 noRC
        //DVCS_dvcsgen->Divide(PS_factor);
        //DVCS_dvcsgen->Scale(2.*TMath::Pi()/16);
        DVCS_dvcsgen->Divide(DVCS_dvcsgen1, DVCS_dvcsgen2, 1, 1);
        //DVCS_dvcsgen->Scale(1.0/(2.*TMath::Pi()/16));


        gSystem->Exec(Form("cp -rf /work/clas12/jsalvg/km15gen/ %s%s && cd %s%skm15gen && python3 main.py -trig 10000 -model km15 -bin %i >> /dev/null && mv km15gen.dat /work/clas12/jsalvg/km15gen_output_%s/KM/bin_%i.dat && clas12root -l -b -q lund2root.C\\(%i,3,%i\\) && cd - && rm -rf %s%skm15gen ",dir.Data(), Folder.Data(),dir.Data(), Folder.Data(),bin, torus.Data(),bin,bin,itorus,dir.Data(), Folder.Data()));
        //TCut cut = TCut(String_cut);
        // Read .root and compute number of events in kinematic bin Mbins[bin-1], scale by external weight using Project
        TChain* tree3 = new TChain("tree");
        tree3->Add(Form("/work/clas12/jsalvg/km15gen_output_%s/KM/bin_%i.root", torus.Data(), bin));
        TH1F *DVCS_km15 = new TH1F("DVCS_km15","", Nphi, 0, 360);
        TH1F *DVCS_km151 = new TH1F("DVCS_km151","", Nphi, 0, 360);
        TH1F *DVCS_km152 = new TH1F("DVCS_km152","", Nphi, 0, 360);
        DVCS_km151->Sumw2();
        DVCS_km152->Sumw2();
        tree3->Project("DVCS_km151", "phi_meas", (cut + TCut("Q2_meas>1"))*TCut("(xsec_born)")); 
        tree3->Project("DVCS_km152", "phi_meas", (cut + TCut("Q2_meas>1")));
        DVCS_km15->Divide(DVCS_km151, DVCS_km152, 1, 1);
        //DVCS_km15->Scale(1.0/(2.*TMath::Pi()/16));


        ///////////////////////////////
        //Main Loop to calculate F_Bin
        ///////////////////////////////
        for(int m=0; m<Nphi; m++)
    {    
      pm=means.at(m).at(0);
      tm=means.at(m).at(2);
      Qm=means.at(m).at(4);
      xm=means.at(m).at(6);

      printProgress(m*1.0/Nphi);
      std::string base_dir(dir.Data());

      if(pm==0 || tm==0 || Qm==0 || xm==0)
      {
        ratio_bin1->SetBinContent(m+1,0);
        ratio_bin2->SetBinContent(m+1,0);
        ratio_bin1->SetBinError(m+1,0); 
        ratio_bin2->SetBinError(m+1,0);
   
      }
      else
      {

        ///////////////////////////////
        //// Get average cross section from Michel's code  ////
        ///////////////////////////////
        infile_km >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8 >> col9;
        double xs_bin0 = col9;
        infile >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8 >> col9;
        double xs_bin1 = col9;
        infile_vgg >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7 >> col8 >> col9;
        double xs_bin2 = col9;
    
        ///////////////////// OPTION 2
        ///////////////////// GET IT FROM THE GENERATED SET OF EVENTS
        double xs_bin3 = DVCS_bh->GetBinContent(m+1);
        double xs_bin4 = DVCS_dvcsgen->GetBinContent(m+1);
        double xs_bin5 = DVCS_km15->GetBinContent(m+1);

        double xs_err3 = DVCS_bh->GetBinError(m+1);
        double xs_err4 = DVCS_dvcsgen->GetBinError(m+1);
        double xs_err5 = DVCS_km15->GetBinError(m+1);


        ///////////////////////////////
        /// Get point calculation
        ///////////////////////////////

        n0=sprintf (command0, "cp -r %sinclude/xsec/VGG/* %s%s && cd %s%s && ./F_point_KM.sh %f %f %f %f | tail -1 | awk '{print $(NF-2)}'",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), mean3d_Q, mean3d_x, -1.0*mean3d_t, 360.*(m+0.5)/Nphi);//*TMath::Pi()/180.0);
        FILE* pipe0 = popen(command0, "r");

        //std::cout<<command0<<endl;

        //n1=sprintf (command1, "cd /work/clas12/jsalvg/EpIC/ && ./partonsDVCS %i DVCSCrossSectionUUBHSubProc %f %f %f %f && cd -", 10000*bin + m, xm, Qm, tm, pm);//*TMath::Pi()/180.0);
        //n1=sprintf (command1, "cd /work/clas12/jsalvg/EpIC/ && ./partonsDVCS %i DVCSCrossSectionUUBHSubProc %f %f %f %f && cd -", 10000*bin + m, mean3d_x, mean3d_Q, mean3d_t, 360.*(m+0.5)/Nphi);//*TMath::Pi()/180.0);
        n1=sprintf (command1, "cp -r %sinclude/xsec/VGG/* %s%s && cd %s%s && ./F_point.sh %f %f %f %f | tail -1 | awk '{print $(NF-2)}'",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), mean3d_Q, mean3d_x, -1.0*mean3d_t, 360.*(m+0.5)/Nphi);//*TMath::Pi()/180.0);
        //n1=sprintf (command1, "cp %sinclude/xsec/VGG/dvcs %s%s && cp %sinclude/xsec/VGG/F_point.sh %s%s && cd %s%s && ./F_point.sh %f %f %f %f | tail -1 | awk '{print $(NF-2)}'",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), Qm, xm, -1.0*tm, pm);//*TMath::Pi()/180.0);
        //printf ("[%s] is a string %d chars long\n",command,n);
        // Open a pipe and execute the command
        FILE* pipe1 = popen(command1, "r");

        //n2=sprintf (command2, "cd /work/clas12/jsalvg/EpIC/ && ./partonsDVCS %i DVCSCrossSectionUUMinus %f %f %f %f && cd -", 100*bin + m, xm, Qm, tm, pm);//*TMath::Pi()/180.0);
        //n2=sprintf (command2, "cd /work/clas12/jsalvg/EpIC/ && ./partonsDVCS %i DVCSCrossSectionUUMinus %f %f %f %f && cd -", 100*bin + m, mean3d_x, mean3d_Q, mean3d_t, 360.*(m+0.5)/Nphi);//*TMath::Pi()/180.0);
        n2=sprintf (command2, "cp -r %sinclude/xsec/VGG/* %s%s && cd %s%s && ./F_point_VGG.sh %f %f %f %f | tail -1 | awk '{print $(NF-2)}'",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), mean3d_Q, mean3d_x, -1.0*mean3d_t, 360.*(m+0.5)/Nphi);//*TMath::Pi()/180.0);
        //n2=sprintf (command2, "cp %sinclude/xsec/VGG/dvcs %s%s && cp %sinclude/xsec/VGG/F_point_VGG.sh %s%s && cd %s%s && ./F_point_VGG.sh %f %f %f %f | tail -1 | awk '{print $(NF-2)}'",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), Qm, xm, -1.0*tm, pm);//*TMath::Pi()/180.0);
        // Open a pipe and execute the command
        FILE* pipe2 = popen(command2, "r");

        if (!pipe1 || !pipe2 || !pipe0) 
        {
	        fprintf(stderr, "Error executing PARTONS script.\n");
	        std::cout<<command1<<" "<<command2<<endl;
	        return ratio_bin1;
        }

        // Read the output from the pipe
        float xs_means0;
        float xs_means1;
        float xs_means2;
        int readCount0 = fscanf(pipe0, "%f", &xs_means0);
        int readCount1 = fscanf(pipe1, "%f", &xs_means1);
        int readCount2 = fscanf(pipe2, "%f", &xs_means2);

        if (readCount1 != 1 || readCount2 != 1 || readCount0 != 1) 
        {
	        fprintf(stderr, "Error reading numbers from PARTONS script.\n");
	        std::cout<<command1<<" "<<command2<<endl;
        }
        // Close the pipe
        pclose(pipe0);
        pclose(pipe1);
        pclose(pipe2);

        ///////////////////////////////
        /// Compute the correction factor  ///
        ///////////////////////////////

        double F_bin1 = xs_bin5 / xs_means0;
        double F_bin2 = xs_bin3 / xs_means1;
        std::cout<<"lala "<<" "<<xs_bin1<<" "<<xs_bin2<<" "<<xs_bin0<<" |"<<xs_bin3<<"+-"<<xs_err3<<" "<<xs_bin4<<"+-"<<xs_err4<<" "<<xs_bin5<<"+-"<<xs_err5<<"| "<<xs_means1<<" "<<xs_means2<<" "<<xs_means0<<endl;

        //std::cout<<"corr factor "<<m+1<<" "<<F_bin<<endl;
        ratio_bin1->SetBinContent(m+1,F_bin1);
        ratio_bin2->SetBinContent(m+1,F_bin2);
        ratio_bin1->SetBinError(m+1,abs(F_bin1-F_bin2)/F_bin1); //delta_F_bin/F_bin //This is a systematic error
        ratio_bin2->SetBinError(m+1,0.0);
      }
    }
    delete DVCS_bh;
    delete DVCS_bh1;
    delete DVCS_bh2;
    delete DVCS_dvcsgen;
    delete DVCS_dvcsgen1;
    delete DVCS_dvcsgen2;
    delete DVCS_km15;
    delete DVCS_km151;
    delete DVCS_km152;

    infile.close();
    infile_vgg.close();

    delete tree1;
    delete tree2;

    std::cout<<"\nBin correction"<<endl;
    for(int k=1; k<=Nphi; k++)
    {
      printf(" %4.2f %4.2f%%\n",ratio_bin1->GetBinContent(k),abs(ratio_bin1->GetBinError(k)*100.));
      //std::cout<<" "<<ratio_bin1->GetBinContent(k)<<" "<<ratio_bin1->GetBinError(k)*100<<"%"<<endl;
    }

  delete ratio_bin2;
  return ratio_bin1;
  }
}


TH1F* BDT::F_RC(int Nphi, TH1F*& Systematics) {
  gSystem->Exec(Form("cd %s%s && /work/clas12/jsalvg/RGA-Simulation/dvcsgen/dvcsgen --trig 1000000 --gpd 101 --nmax 1000000 --beam 10.6 --zpos -3.0 --zwidth 2.5 --radgen --writef 2 --radstable --y 0.01 0.97 --th 0.03 1 --ycol 0.0005 --weight --t %f %f --q2 %f %f --x %f %f >> /dev/null && cd -",dir.Data(), Folder.Data(),-1.0*boundaries.at(1),-1.0*boundaries.at(0),boundaries.at(2),boundaries.at(3),boundaries.at(4),boundaries.at(5)));
  gSystem->Exec(Form("cd %s%s && cp /work/clas12/jsalvg/RGA-Simulation/lund2root_test.C . && clas12root -l -b -q lund2root_test.C && mv dvcsgen_test.root dvcsgen_DVCS_gen.root && rm -rf dvcsgen1.dat lund2root_test.C && cd -",dir.Data(), Folder.Data()));

  gSystem->Exec(Form("cd %s%s && /work/clas12/jsalvg/RGA-Simulation/dvcsgen/dvcsgen --trig 1000000 --gpd 101 --nmax 1000000 --beam 10.6 --zpos -3.0 --zwidth 2.5 --radgen --writef 2 --radstable --y 0.01 0.97 --th 0.03 1 --ycol 0.0005 --weight --t %f %f --q2 %f %f --x %f %f --bh 1 >> /dev/null && cd -",dir.Data(), Folder.Data(),-1.0*boundaries.at(1),-1.0*boundaries.at(0),boundaries.at(2),boundaries.at(3),boundaries.at(4),boundaries.at(5)));
  gSystem->Exec(Form("cd %s%s && cp /work/clas12/jsalvg/RGA-Simulation/lund2root_test.C . && clas12root -l -b -q lund2root_test.C && mv dvcsgen_test.root dvcsgen_BH_gen.root && rm -rf dvcsgen1.dat lund2root_test.C && cd -",dir.Data(), Folder.Data()));

  //Dataset for the nominal computation
  TChain *Data_Tree= new TChain("tree");
  //Data_Tree->Add(MC_DVCS_RC);
  Data_Tree->Add(Folder + TString("dvcsgen_DVCS_gen.root"));
  
  TH1F *xborn = new TH1F("xborn","",Nphi,0,360);
  TH1F *xrad  = new TH1F("xrad","",Nphi,0,360);

  TH1F *nevs = new TH1F("nevs","",Nphi,0,360);
  TH1F *nevs_born  = new TH1F("nevs_born","",Nphi,0,360);
  TH1F *nevs_rad  = new TH1F("nevs_rad","",Nphi,0,360);

  xborn->Sumw2();
  xrad->Sumw2();
  nevs->Sumw2();
  nevs_born->Sumw2();
  nevs_rad->Sumw2();

  TH1F *ratio_rad = new TH1F("ratio_rad","F_rad",Nphi,0,360);
  ratio_rad->Sumw2();

  //Dataset for the systematics
  TChain *Data_Tree_Sys= new TChain("tree");
  //Data_Tree_Sys->Add(MC_DVCS_RC_BH);
  Data_Tree_Sys->Add(Folder + TString("dvcsgen_BH_gen.root"));

  TH1F *xborn_Sys = new TH1F("xborn_Sys","",Nphi,0,360);
  TH1F *xrad_Sys  = new TH1F("xrad_Sys","",Nphi,0,360);

  TH1F *nevs_Sys = new TH1F("nevs_Sys","",Nphi,0,360);
  TH1F *nevs_born_Sys  = new TH1F("nevs_born_Sys","",Nphi,0,360);
  TH1F *nevs_rad_Sys  = new TH1F("nevs_rad_Sys","",Nphi,0,360);

  xborn_Sys->Sumw2();
  xrad_Sys->Sumw2();
  nevs_Sys->Sumw2();
  nevs_born_Sys->Sumw2();
  nevs_rad_Sys->Sumw2();

  TH1F *ratio_rad_Sys = new TH1F("ratio_rad_Sys","F_rad",Nphi,0,360);
  ratio_rad_Sys->Sumw2();

  //Cut 
  TString String_cut = (cut_bin + cut_ref).GetTitle();
  String_cut.ReplaceAll("bestCandidateFlag==1 && ", "");
  String_cut.ReplaceAll("_strip_Nuc_BDT_SIDIS", "Q2_meas");
  String_cut.ReplaceAll("strip_Q2", "Q2_meas");
  String_cut.ReplaceAll("strip_Xbj", "xB_meas");
  String_cut.ReplaceAll("t_Ph", "t_meas");
  String_cut.ReplaceAll("strip_El_P", "El_E");
  String_cut.ReplaceAll("strip_Ph_P", "Ph_E");
  TCut cut = TCut(String_cut) + TCut("xsec_born>0 && xsec_rad>0"); //NaN events are those of xsec_rad=0

  //Unweighted Nominal
  Data_Tree->Project("xborn", "phi_meas", cut * TCut("xsec_born"));
  Data_Tree->Project("xrad" , "phi_meas", cut * TCut("xsec_rad") );

  //Data_Tree->Project("nevs" , "phi", cut );
  //Here I do not divide by the number of events on each bin as it cancels in the ratio.  
  ratio_rad->Divide(xrad,xborn,1,1);
  
 
  //Unweighted Systematics
  Data_Tree_Sys->Project("xborn_Sys", "phi_meas", cut * TCut("xsec_born")); //I do not need to weight the events as the distribution is not flat
  Data_Tree_Sys->Project("xrad_Sys" , "phi_meas", cut * TCut("xsec_rad"));

  //Data_Tree_Sys->Project("nevs" , "phi", cut );
  //Here I do not divide by the number of events on each bin as it cancels in the ratio.  
  ratio_rad_Sys->Divide(xrad_Sys, xborn_Sys,1,1);

  
  /*
  //Weighted
  Data_Tree->Project("xborn", "phi_meas", cut * TCut("1.0/xsec_born"));
  Data_Tree->Project("xrad" , "phi_meas", cut * TCut("1.0/xsec_rad") );

  Data_Tree->Project("nevs_born" , "phi_meas", cut * TCut("xsec_born"));
  Data_Tree->Project("nevs_rad" , "phi_meas", cut * TCut("xsec_rad"));

  xborn->Divide(xborn,nevs_born);
  xrad->Divide(xrad,nevs_rad);
  //Here I do not divide by the number of events on each bin as it cancels in the ratio.  
  ratio_rad->Divide(xborn, xrad,1,1);
  */

  std::cout<<"\nRC correction"<<endl;
  double ratio_Sys;
  for(int k=1; k<=Nphi; k++)
  {
    if(ratio_rad->GetBinContent(k)==0)
    {
      ratio_rad->SetBinError(k,0);
    }
    else
    {
      ratio_rad->SetBinError( k,ratio_rad->GetBinContent(k)*sqrt(pow(xborn->GetBinError(k)/xborn->GetBinContent(k),2) + pow(xrad->GetBinError(k)/xrad->GetBinContent(k),2)) );
      ratio_Sys = (ratio_rad->GetBinContent(k)-ratio_rad_Sys->GetBinContent(k))/ratio_rad->GetBinContent(k); 
      Systematics->SetBinError( k, Systematics->GetBinError(k) + pow(ratio_Sys,2) );
    }
    printf(" %4.2f %4.2f%%\n",ratio_rad->GetBinContent(k),abs(ratio_Sys*100.));
    //std::cout<<" "<<ratio_rad->GetBinContent(k)<<" "<<ratio_rad->GetBinError(k)<<" "<<ratio_Sys*100<<"%"<<std::endl;
  }

  delete nevs_born;
  delete nevs_rad;
  delete nevs;
      
  delete xborn;
  delete xrad;
  delete Data_Tree;

  delete nevs_born_Sys;
  delete nevs_rad_Sys;
  delete nevs_Sys;

  delete xborn_Sys;
  delete xrad_Sys;
  delete Data_Tree_Sys;
  delete ratio_rad_Sys;

  return ratio_rad;
}


TH1F* BDT::compute_kin_shift_factor(int Nphi, TString var)
{
  std::cout<<"Computing kinematic correction of "<<var<<endl;
  
  TH1F *ratio = new TH1F("ratio_"+var,"ratio"+var,Nphi,0,360);
  for(int i=1; i<=Nphi; i++)
  {
    ratio->SetBinContent(i,1);
    ratio->SetBinError(i,0);    
  }
  return ratio; 

  TChain *Data_Tree= new TChain("pDVCS");
  Data_Tree->Add(Folder + TString("../../") + TRC_Sim); 
  
  TChain *MCData_Tree= new TChain("pDVCS");
  MCData_Tree->Add(MC_RC_Sim);

  for(int i=0; i<Nphi;i++)
  {
    printProgress(i*1.0/Nphi);

    TH1F *hvar = new TH1F("hvar","",100,0,0);
    TH1F *hvar_meas  = new TH1F("hvar_meas","",100,0,0);

    MCData_Tree->Project("hvar" , var, cut_bin  + TCut(Form("Phi_Ph>%f && Phi_Ph<%f",360.*i/Nphi,360.*(i+1)/Nphi)));
    Data_Tree->Project("hvar_meas" , var, cut + cut_bin + cut_ref + TCut(Form("_strip_Nuc_BDT > %f",BDT_value)) + TCut(Form("Phi_Ph>%f && Phi_Ph<%f",360.*i/Nphi,360.*(i+1)/Nphi)));  
    
    ratio->SetBinContent(i+1,hvar->GetMean()/hvar_meas->GetMean());
    ratio->SetBinError(i+1,ratio->GetBinContent(i+1)*sqrt(pow(hvar->GetMeanError()/hvar->GetMean(),2) + pow(hvar_meas->GetMeanError()/hvar_meas->GetMean(),2)));

    delete hvar;
    delete hvar_meas;
    }

  delete Data_Tree;
  delete MCData_Tree;

  return ratio;
}


TH1F* BDT::compute_kin_shift_factor(TString var)
{
  std::cout<<"Computing kinematic correction (3D) of "<<var<<endl;

  TH1F *ratio = new TH1F("ratio3D_"+var,"ratio"+var,1,0,360);
  ratio->SetBinContent(1,1);
  ratio->SetBinError(1,0);
  return ratio;

  TChain *Data_Tree= new TChain("pDVCS");
  Data_Tree->Add(Folder + TString("../../") + TRC_Sim); 
  
  TChain *MCData_Tree= new TChain("pDVCS");
  MCData_Tree->Add(MC_RC_Sim);

  TH1F *hvar = new TH1F("hvar","",100,0,0);
  TH1F *hvar_meas  = new TH1F("hvar_meas","",100,0,0);

  MCData_Tree->Project("hvar" , var, cut_bin );
  Data_Tree->Project("hvar_meas" , var, cut + cut_bin + cut_ref + TCut(Form("_strip_Nuc_BDT > %f",BDT_value)) );  
    
  ratio->SetBinContent(1,hvar->GetMean()/hvar_meas->GetMean());
  ratio->SetBinError(1,ratio->GetBinContent(1)*sqrt(pow(hvar->GetMeanError()/hvar->GetMean(),2) + pow(hvar_meas->GetMeanError()/hvar_meas->GetMean(),2)));

  delete hvar;
  delete hvar_meas;

  delete Data_Tree;
  delete MCData_Tree;

  return ratio;
}
