
void BDT::Training_on_bins(TString Data, int NumEv, int bin=0)//, TCut cut, TString DVCS, TString Pi0, vector<TString> vars)
{
  int NBINS_t=3;
  int NBINS_x=3;
  int NBINS_Q=3;
  int NBINS = 10;

  TFile *File = new TFile(Data);
  TTree *ch1 = (TTree *)(File->Get("pDVCS"));
  
  TH1F *temp2 = new TH1F("temp2","Histogram",10,-200,0);
  ch1->Project("temp2", "t_Ph",cut);
  int DATASZ=temp2->GetEntries();
  delete temp2;
  
  //int NBINS=DATASZ/(NumEv*NBINS_t);
  //int NBINS_Q = NBINS%NBINS_x >0 ? (NBINS/NBINS_x) + 1 : (NBINS/NBINS_x);
  std::cout<<"Total number of events is "<<DATASZ<<endl;
  int NumEv_Corr=DATASZ/(NBINS*NBINS_t);  

  delete ch1;
  File->Close();
  delete File;

  std::vector<vector<double>> bins;
  std::vector<double> binst;
  std::vector<double> aux;

  double bins_t[4] = {-13.908200, -0.781163, -0.339554, -0.000041};
  double *bins_Q;
  double *bins_x;
  int bin_number=10;
  TString Folder_old=Folder;
    

  //NEED TO GIVE BINS AS INPUT!
  int k0=0, kN=NBINS_t, m0=0, mN=NBINS_Q, n0=0, nN;
  int in_range;
  if(bin!=0)
    {
      bin_number=bin;
      k0=(bin_number -1)/9 +1 - 1;
      kN=(bin_number -1)/9 +1;
      in_range = (bin_number -1)%9 +1; //Convert the bin number into a bin_number between 1 and 9
      m0=(in_range -1)/NBINS_x - 1;
      mN=(in_range -1)/NBINS_x;
      n0=(in_range-1)%NBINS_x - 1;
    }

  for(int k=k0;k<kN;k++)
    {
      aux.clear();
      if (k==0)
	{
	  aux.push_back(1.003650);
	  aux.push_back(2.250580);
	  aux.push_back(3.232600);
	  aux.push_back(11.189300);
	  bins.push_back(aux);
	  aux.clear();
	  
	  aux.push_back(0.059511);
	  aux.push_back(0.158438);
	  aux.push_back(0.239953);
	  aux.push_back(0.418176);
	  bins.push_back(aux);
	  aux.clear();
	  
	  aux.push_back(0.125293);
	  aux.push_back(0.246012);
	  aux.push_back(0.345544);
	  aux.push_back(0.508824);
	  bins.push_back(aux);
	  aux.clear();
	  
	  aux.push_back(0.181055);
	  aux.push_back(0.346616);
	  aux.push_back(0.461646);
	  aux.push_back(0.775363);
	  bins.push_back(aux);
	  aux.clear();
	}
      if (k==1)
	{
	  aux.push_back(1.001100);
	  aux.push_back(2.000500);
	  aux.push_back(2.748080);
	  aux.push_back(9.674350);
	  bins.push_back(aux);
	  aux.clear();
	  
	  aux.push_back(0.056738);
	  aux.push_back(0.119315);
	  aux.push_back(0.167430);
	  aux.push_back(0.390013);
	  bins.push_back(aux);
	  aux.clear();
	  
	  aux.push_back(0.111259);
	  aux.push_back(0.165230);
	  aux.push_back(0.218732);
	  aux.push_back(0.467046);
	  bins.push_back(aux);
	  aux.clear();
	  
	  aux.push_back(0.153305);
	  aux.push_back(0.228296);
	  aux.push_back(0.295716);
	  aux.push_back(0.689304);
	  bins.push_back(aux);
	  aux.clear();
	}
      if (k==2)
	{
	  aux.push_back(1.000510);
	  aux.push_back(1.823140);
	  aux.push_back(2.389770);
	  aux.push_back(8.928210);
	  bins.push_back(aux);
	  aux.clear();
	  
	  aux.push_back(0.056515);
	  aux.push_back(0.101721);
	  aux.push_back(0.118623);
	  aux.push_back(0.366043);
	  bins.push_back(aux);
	  aux.clear();
	  
	  aux.push_back(0.101679);
	  aux.push_back(0.133084);
	  aux.push_back(0.151032);
	  aux.push_back(0.430764);
	  bins.push_back(aux);
	  aux.clear();
	  
	  aux.push_back(0.133748);
	  aux.push_back(0.178059);
	  aux.push_back(0.215117);
	  aux.push_back(0.657785);
	  bins.push_back(aux);
	  aux.clear();
	}
      bins_Q=bins.at(0).data();
      for(int m=m0;m<mN;m++)
	{
	  bins_x=bins.at(m+1).data();
	  nN = (bin==0) ? min(NBINS_x,NBINS - m*NBINS_x) : (in_range-1)%NBINS_x;	  
	  for(int n=n0;n<nN;n++)
	    {
	        TH1 *Orig;
		TH1 *Most;
		TH1 *Maxi;

	      TCut cut_bin = TCut(Form("bestCandidateFlag==1  && t_Ph>%f && t_Ph<%f && strip_Q2>%f && strip_Q2<%f && strip_Xbj>%f && strip_Xbj<%f",bins_t[k],bins_t[k+1],bins_Q[m],bins_Q[m+1],bins_x[n],bins_x[n+1]));
	      std::cout<<"*******************************************"<<endl;
	      std::cout<<"*******************************************"<<endl;
	      std::cout<<Form("\n\n BIN t_Ph>%f && t_Ph<%f && strip_Q2>%f && strip_Q2<%f && strip_Xbj>%f && strip_Xbj<%f",bins_t[k],bins_t[k+1],bins_Q[m],bins_Q[m+1],bins_x[n],bins_x[n+1])<<endl;
	      boundaries.clear();
	      boundaries.push_back(bins_t[k]);
	      boundaries.push_back(bins_t[k+1]);
	      boundaries.push_back(bins_Q[m]);
	      boundaries.push_back(bins_Q[m+1]);
	      boundaries.push_back(bins_x[n]);
	      boundaries.push_back(bins_x[n+1]);
	      Folder = Folder_old + TString("bin_")+Form("%i/",bin_number);
	      gSystem->Exec(TString("mkdir -p ") + Folder);

	      //Training(cut + cut_bin, DVCS, Pi0, Vars);
	      //Training_vars(Data, DVCS, Pi0, cut + cut_bin);
	      //Add_BDT_var(cut + cut_bin, Data, TData, Vars);
	      //Add_BDT_var(cut + cut_bin, DVCS, TDVCS, Vars);
	      //Add_BDT_var(cut + cut_bin, Pi0, TPi0, Vars);
	      ////Add_BDT_var_float(cut + cut_bin, Pi0, TPi0);
	      //Explore(TData, TDVCS, cut + cut_bin);
	      
	      //Filter(TData, cut + cut_bin + TCut(Form("_strip_Nuc_BDT > %f",BDT_value)), TString("Data_NP_Theta_g_5.root"));

	      std::cout<<"\n Get Contamination BDT way"<<endl;
	      Get_Contamination(cut + cut_bin, BDT_value);
	      
	      std::cout<<"\n Get Contamination Mostafa way"<<endl;
	      //Add_BDT_var(cut + cut_bin, "/home/munoz/Datasets/DVMP/NP/DIS/Quality_Pi_as_DVCS_NP.root", "Tested_1gamma.root", Vars);
	      
	      Most=Get_Contamination_Mostafa(cut + cut_bin, BDT_value);
	      //boundaries.push_back(1);
	      //boundaries.push_back(1);
	      
	      std::cout<<"\n Get Contamination Maxime way"<<endl;
	      Maxi=Maxime(cut + cut_bin, BDT_value, bin_number);
	      //boundaries.push_back(1);
	      //boundaries.push_back(1);
	      
	      Orig=Single_BSA("Data_NP_Theta_g_5.root",N_Phi);
	      Orig->SetTitle("Before");
	      //gStyle->SetOptFit(0);
	      gStyle->SetOptTitle(0);
	      TCanvas* c3 = new TCanvas("c3","Histograms");
	      Orig->Draw();
	      Most->Draw("SAME");
	      Maxi->Draw("SAME");
	      c3->BuildLegend();

	      c3->Print(Folder + TString("befo_vs_Most.pdf"));
	      gStyle->SetOptTitle(1);

	      //Compare_three(cut + cut_bin, "TMostafa_pi0.root", "TMaxime_pi0.root");
	      delete c3;
	      delete Orig;
	      delete Most;
	      delete Maxi;
	      
	      bin_number+=1;

	      std::ofstream outFile(Folder + TString("Amplitudes.txt"));
	      outFile<<"type value fit"<<endl;	      
	      outFile<<"Raw "<<BSA_Amplitude<<" "<<BSA_Amplitude_fit<<endl;	      
	      outFile<<"Mostafa "<<BSA_Amplitude_most<<" "<<BSA_Amplitude_most_fit<<endl;	      
	      outFile<<"Maxime "<<BSA_Amplitude_maxi<<" "<<BSA_Amplitude_maxi_fit<<endl;	      
	      outFile.close();

	      std::cout<<"type value fit"<<endl;	      
	      std::cout<<"Raw "<<BSA_Amplitude<<" "<<BSA_Amplitude_fit<<endl;	      
	      std::cout<<"Mostafa "<<BSA_Amplitude_most<<" "<<BSA_Amplitude_most_fit<<endl;	      
	      std::cout<<"Maxime "<<BSA_Amplitude_maxi<<" "<<BSA_Amplitude_maxi_fit<<endl;
	    }
	}

      bins.clear();
    }

  Folder = Folder_old;

  delete bins_Q;
  delete bins_x;

  return;
}
