TH1* BDT::Get_Contamination_Mostafa(TCut cut, double BDT_cut, int Nphi)
{
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  TChain *Pi01g= new TChain("pDVCS");
  Pi01g->Add(Folder + TString("Tested_Pi0_1gamma.root"));

  TChain *Pi02g= new TChain("eppi0");
  Pi02g->Add(sim_eppi0);

  TChain *DIS1g= new TChain("pDVCS");
  DIS1g->Add(Folder + TString("Tested_DIS_1gamma.root"));

  TChain *DIS2g= new TChain("eppi0");
  DIS2g->Add(sim_eppi0_DIS);

  //Use quality 3 as it has the cuts for RGA eppi0 selection
  TChain *Pi02gData= new TChain("eppi0");
  Pi02gData->Add(eppi0);

  TChain *Data= new TChain("pDVCS");
  Data->Add(Folder + TData);

  //Convert cut to string
  TString String_cut = cut.GetTitle();
  //replace Ph by Pi0
  String_cut.ReplaceAll("t_Ph", "t_Pi0");
	
  TString l1 = Folder[0];
  TString l2 = Folder[1];
  TString l3 = Folder[2];
  TString temps = l1+l2+l3;
  if(temps == "FT/")
    String_cut.ReplaceAll("strip_Ph_Theta", "mm2_eNgg");//mm2_eNgg for FT and theta_Pi0_e for FD
  if(temps == "FD/")
    String_cut.ReplaceAll("strip_Ph_Theta", "theta_Pi0_e");//mm2_eNgg for FT and theta_Pi0_e for FD
	  
  String_cut.ReplaceAll("strip_Ph_P", "strip_Pi0_P");
  String_cut.ReplaceAll("mm2_eg", "strip_Xbj");
  String_cut.ReplaceAll("gamma", "Pi0");
  //Create cut for 2gamma case
  TCut cut2g = TCut(String_cut) + TCut("(strip_Ph1_P>2 || strip_Ph2_P>2)"); // && (strip_Ph1_Theta <5 || strip_Ph2_Theta <5)");

  TCut cut_phi;
  TCut cut_phi2;
  double est1;
  double est2;
  std::ofstream outFile;
  std::ofstream outFile2;

  
  if(generate_most)
    {
      //Pi0
      TH1F *Pi01g_p = new TH1F("Pi01g_p","",Nphi,0,360);
      TH1F *Pi01g_m = new TH1F("Pi01g_m","",Nphi,0,360);
      TH1F *Pi01g_p_BDT = new TH1F("Pi01g_p_BDT","",Nphi,0,360);
      TH1F *Pi01g_m_BDT = new TH1F("Pi01g_m_BDT","",Nphi,0,360);
  
      TH1F *Pi02g_p = new TH1F("Pi02g_p","",Nphi,0,360);
      TH1F *Pi02g_m = new TH1F("Pi02g_m","",Nphi,0,360);

      //DIS
      TH1F *DIS1g_p = new TH1F("DIS1g_p","",Nphi,0,360);
      TH1F *DIS1g_m = new TH1F("DIS1g_m","",Nphi,0,360);
      TH1F *DIS1g_p_BDT = new TH1F("DIS1g_p_BDT","",Nphi,0,360);
      TH1F *DIS1g_m_BDT = new TH1F("DIS1g_m_BDT","",Nphi,0,360);
  
      TH1F *DIS2g_p = new TH1F("DIS2g_p","",Nphi,0,360);
      TH1F *DIS2g_m = new TH1F("DIS2g_m","",Nphi,0,360);

      //2gamma Data
      TH1F *Pi02g_Data_p = new TH1F("Pi02g_Data_p","",Nphi,0,360);
      TH1F *Pi02g_Data_m = new TH1F("Pi02g_Data_m","",Nphi,0,360);

      TH1F *Data_p = new TH1F("Data_p","",Nphi,0,360);
      TH1F *Data_m = new TH1F("Data_m","",Nphi,0,360);
      TH1F *Data_p_BDT = new TH1F("Data_p_BDT","",Nphi,0,360);
      TH1F *Data_m_BDT = new TH1F("Data_m_BDT","",Nphi,0,360);

      //Ratio Pi0
      TH1F *ratio_p_Pi0 = new TH1F("ratio_p_Pi0","ratio_p_Pi0",Nphi,0,360);
      TH1F *ratio_m_Pi0 = new TH1F("ratio_m_Pi0","ratio_m_Pi0",Nphi,0,360);
      TH1F *ratio_p_Pi0_BDT = new TH1F("ratio_p_Pi0_BDT","ratio_p_Pi0_BDT",Nphi,0,360);
      TH1F *ratio_m_Pi0_BDT = new TH1F("ratio_m_Pi0_BDT","ratio_m_Pi0_BDT",Nphi,0,360);

      //Ratio DIS
      TH1F *ratio_p_DIS = new TH1F("ratio_p_DIS","ratio_p_DIS",Nphi,0,360);
      TH1F *ratio_m_DIS = new TH1F("ratio_m_DIS","ratio_m_DIS",Nphi,0,360);
      TH1F *ratio_p_DIS_BDT = new TH1F("ratio_p_DIS_BDT","ratio_p_DIS_BDT",Nphi,0,360);
      TH1F *ratio_m_DIS_BDT = new TH1F("ratio_m_DIS_BDT","ratio_m_DIS_BDT",Nphi,0,360);

      //Ratio r Final
      TH1F *ratio_r_p = new TH1F("ratio_r_p","ratio_r_p",Nphi,0,360);
      TH1F *ratio_r_m = new TH1F("ratio_r_m","ratio_r_m",Nphi,0,360);
      TH1F *ratio_r_p_BDT = new TH1F("ratio_r_p_BDT","ratio_r_p_BDT",Nphi,0,360);
      TH1F *ratio_r_m_BDT = new TH1F("ratio_r_m_BDT","ratio_r_m_BDT",Nphi,0,360);

      //Ratio Final
      TH1F *ratio_p = new TH1F("ratio_p","ratio_p",Nphi,0,360);
      TH1F *ratio_m = new TH1F("ratio_m","ratio_m",Nphi,0,360);
      TH1F *ratio_p_BDT = new TH1F("ratio_p_BDT","ratio_p_BDT",Nphi,0,360);
      TH1F *ratio_m_BDT = new TH1F("ratio_m_BDT","ratio_m_BDT",Nphi,0,360);

      //Final background
      TH1F *bkg_p = new TH1F("bkg_p","bkg_p",Nphi,0,360);
      TH1F *bkg_m = new TH1F("bkg_m","bkg_m",Nphi,0,360);
      TH1F *bkg_p_BDT = new TH1F("bkg_p_BDT","bkg_p_BDT",Nphi,0,360);
      TH1F *bkg_m_BDT = new TH1F("bkg_m_BDT","bkg_m_BDT",Nphi,0,360);

      //Cleaned data
      TH1F *data_p_bkg_free = new TH1F("data_p_bkg_free","data_p_bkg_free",Nphi,0,360);
      TH1F *data_m_bkg_free = new TH1F("data_m_bkg_free","data_m_bkg_free",Nphi,0,360);

      TH1F *data_p_BDT_bkg_free = new TH1F("data_p_BDT_bkg_free","data_p_BDT_bkg_free",Nphi,0,360);
      TH1F *data_m_BDT_bkg_free= new TH1F("data_m_BDT_bkg_free","data_m_BDT_bkg_free",Nphi,0,360);

      Pi01g_p->Sumw2();
      Pi01g_m->Sumw2();
      Pi01g_p_BDT->Sumw2();
      Pi01g_m_BDT->Sumw2();
      Pi02g_p->Sumw2();
      Pi02g_m->Sumw2();

      DIS1g_p->Sumw2();
      DIS1g_m->Sumw2();
      DIS1g_p_BDT->Sumw2();
      DIS1g_m_BDT->Sumw2();
      DIS2g_p->Sumw2();
      DIS2g_m->Sumw2();

      Pi02g_Data_p->Sumw2();
      Pi02g_Data_m->Sumw2();
      Data_p->Sumw2();
      Data_m->Sumw2();

      //Pi0
      Pi01g->Project("Pi01g_p", "Phi_Ph", cut);
      Pi01g->Project("Pi01g_m", "Phi_Ph", cut);
      Pi01g->Project("Pi01g_p_BDT", "Phi_Ph", cut + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)));
      Pi01g->Project("Pi01g_m_BDT", "Phi_Ph", cut + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)));

      Pi02g->Project("Pi02g_p", "Phi_Pi0", cut2g + TCut("strip_Pi0_2DChi2 < 0.04 && abs(mm2_eNgg)<0.01"));
      Pi02g->Project("Pi02g_m", "Phi_Pi0", cut2g + TCut("strip_Pi0_2DChi2 < 0.04 && abs(mm2_eNgg)<0.01"));

      //DIS
      DIS1g->Project("DIS1g_p", "Phi_Ph", cut);
      DIS1g->Project("DIS1g_m", "Phi_Ph", cut);
      DIS1g->Project("DIS1g_p_BDT", "Phi_Ph", cut + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)));
      DIS1g->Project("DIS1g_m_BDT", "Phi_Ph", cut + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)));

      DIS2g->Project("DIS2g_p", "Phi_Pi0", cut2g + TCut("strip_Pi0_2DChi2 < 0.04 && abs(mm2_eNgg)<0.01"));
      DIS2g->Project("DIS2g_m", "Phi_Pi0", cut2g + TCut("strip_Pi0_2DChi2 < 0.04 && abs(mm2_eNgg)<0.01"));

      //2gamma data
      Pi02gData->Project("Pi02g_Data_p", "Phi_Pi0", cut2g + TCut("Helicity>0") + TCut("strip_Pi0_2DChi2 < 0.04 && abs(mm2_eNgg)<0.01"));
      Pi02gData->Project("Pi02g_Data_m", "Phi_Pi0", cut2g + TCut("Helicity<0") + TCut("strip_Pi0_2DChi2 < 0.04 && abs(mm2_eNgg)<0.01"));

      //data
      Data->Project("Data_p", "Phi_Ph", cut + TCut("Helicity>0"));
      Data->Project("Data_m", "Phi_Ph", cut + TCut("Helicity<0"));
      Data->Project("Data_p_BDT", "Phi_Ph", cut + TCut(Form("Helicity>0 && _strip_Nuc_BDT > %f",BDT_cut)));
      Data->Project("Data_m_BDT", "Phi_Ph", cut + TCut(Form("Helicity<0 && _strip_Nuc_BDT > %f",BDT_cut)));

      //Ratio Pi0
      ratio_p_Pi0->Divide(Pi01g_p,Pi02g_p,1,1);
      ratio_m_Pi0->Divide(Pi01g_m,Pi02g_m,1,1);
      ratio_p_Pi0_BDT->Divide(Pi01g_p_BDT,Pi02g_p,1,1);
      ratio_m_Pi0_BDT->Divide(Pi01g_m_BDT,Pi02g_m,1,1);

      //Ratio DIS
      ratio_p_DIS->Divide(DIS1g_p,DIS2g_p,1,1);
      ratio_m_DIS->Divide(DIS1g_m,DIS2g_m,1,1);
      ratio_p_DIS_BDT->Divide(DIS1g_p_BDT,DIS2g_p,1,1);
      ratio_m_DIS_BDT->Divide(DIS1g_m_BDT,DIS2g_m,1,1);

      //Ratio r: n_{pi0}^{2g}/n_{dis}^{2g}
      Pi02g_p->Scale( DIS1g_p->Integral()*1.0/Pi01g_p->Integral());
      ratio_r_p->Divide(Pi02g_p,DIS2g_p,1,1);
      Pi02g_m->Scale( DIS1g_m->Integral()*1.0/Pi01g_m->Integral());
      ratio_r_m->Divide(Pi02g_m,DIS2g_m,1,1);

      Pi02g_p->Scale( Pi01g_p->Integral()*1.0/DIS1g_p->Integral());
      Pi02g_p->Scale( DIS1g_p_BDT->Integral()*1.0/Pi01g_p_BDT->Integral());
      ratio_r_p_BDT->Divide(Pi02g_p,DIS2g_p,1,1);
      Pi02g_m->Scale( Pi01g_m->Integral()*1.0/DIS1g_m->Integral());
      Pi02g_m->Scale( DIS1g_m_BDT->Integral()*1.0/Pi01g_m_BDT->Integral());
      ratio_r_m_BDT->Divide(Pi02g_m,DIS2g_m,1,1);

      //Final factor: (n_{pi0}^{1g} + n_{dis}^{1g})/(n_{pi0}^{2g} + n_{dis}^{2g})
      //(r*r_pi0 + r_dis)/(1+r)
      for (int i = 1; i <= ratio_p->GetNbinsX(); i++) 
	{
	  ratio_p->SetBinContent(i, (ratio_r_p->GetBinContent(i)*ratio_p_Pi0->GetBinContent(i) + ratio_p_DIS->GetBinContent(i))/(1.0 + ratio_r_p->GetBinContent(i)) );
	  ratio_m->SetBinContent(i, (ratio_r_m->GetBinContent(i)*ratio_m_Pi0->GetBinContent(i) + ratio_m_DIS->GetBinContent(i))/(1.0 + ratio_r_m->GetBinContent(i)) );
	  ratio_p_BDT->SetBinContent(i, (ratio_r_p_BDT->GetBinContent(i)*ratio_p_Pi0_BDT->GetBinContent(i) + ratio_p_DIS_BDT->GetBinContent(i))/(1.0 + ratio_r_p_BDT->GetBinContent(i)) );
	  ratio_m_BDT->SetBinContent(i, (ratio_r_m_BDT->GetBinContent(i)*ratio_m_Pi0_BDT->GetBinContent(i) + ratio_m_DIS_BDT->GetBinContent(i))/(1.0 + ratio_r_m_BDT->GetBinContent(i)) );
	}

      //Final background
      bkg_p->Multiply(ratio_p,Pi02g_Data_p,1,1);
      bkg_m->Multiply(ratio_m,Pi02g_Data_m,1,1);
      bkg_p_BDT->Multiply(ratio_p_BDT,Pi02g_Data_p,1,1);
      bkg_m_BDT->Multiply(ratio_m_BDT,Pi02g_Data_m,1,1);


      //********************************************
      //output Mostafa tree
      //*******************************************
      TChain *ch0= new TChain("pDVCS");
      ch0->Add(Folder + TString("Tested_Pi0_1gamma.root"));
      ch0->Add(Folder + TString("Tested_DIS_1gamma.root"));

      TFile* out_sim=new TFile(Folder + TString("Mostafa_pi0.root"), "RECREATE");
      TTree *tree = ch0->CopyTree(cut);
      tree->SetMaxTreeSize(100000000000LL);
      TBranch* Wb = tree->Branch("Weight", &weight);
      static vector<double>* phi_M;
      static vector<int>* flag_M;
      static int hel_M;
      tree->SetBranchAddress("Phi_Ph",&phi_M);
      tree->SetBranchAddress("Helicity",&hel_M);
      tree->SetBranchAddress("bestCandidateFlag",&flag_M);
      for(int t=0; t<tree->GetEntries();t++)
	{
	  tree->GetEntry(t);
	  for(int t1=0; t1<flag_M->size(); t1++)
	    {
	      if(flag_M->at(t1)==1 )
		{
		  if(hel_M>0)
		    weight = bkg_p->GetBinContent(bkg_p->FindBin(phi_M->at(t1)))*1.0/Pi01g_p->GetBinContent(Pi01g_p->FindBin(phi_M->at(t1)));
		  else 
		    weight = bkg_m->GetBinContent(bkg_m->FindBin(phi_M->at(t1)))*1.0/Pi01g_m->GetBinContent(Pi01g_m->FindBin(phi_M->at(t1)));
		
		  if(TMath::Finite(weight))
		    Wb->Fill();
		  else
		    {
		      weight=0;
		      Wb->Fill();
		    }
		}
	    }
	}
      tree->Write();
      delete tree;
      out_sim->Close();
      delete out_sim;
      delete ch0;

      delete Pi01g_p;
      delete Pi01g_m;
      delete Pi01g_p_BDT;
      delete Pi01g_m_BDT;
      delete Pi02g_p;
      delete Pi02g_m;

      delete DIS1g_p;
      delete DIS1g_m;
      delete DIS1g_p_BDT;
      delete DIS1g_m_BDT;
      delete DIS2g_p;
      delete DIS2g_m;

      delete Pi02g_Data_p;
      delete Pi02g_Data_m;
      delete Data_p;
      delete Data_m;
      delete Data_p_BDT;
      delete Data_m_BDT;


      delete ratio_p_Pi0;
      delete ratio_m_Pi0;
      delete ratio_p_Pi0_BDT;
      delete ratio_m_Pi0_BDT;

      delete ratio_p_DIS;
      delete ratio_m_DIS;
      delete ratio_p_DIS_BDT;
      delete ratio_m_DIS_BDT;

      delete ratio_p;
      delete ratio_m;
      delete ratio_p_BDT;
      delete ratio_m_BDT;

      delete bkg_p;
      delete bkg_m;
      delete bkg_p_BDT;
      delete bkg_m_BDT;

      delete data_p_bkg_free;
      delete data_m_bkg_free;
      delete data_p_BDT_bkg_free;
      delete data_m_BDT_bkg_free;
  
      Add_BDT_var(cut, Folder + TString("Mostafa_pi0.root"), "TMostafa_pi0.root", Vars);
      gSystem->Exec(TString("rm ") + Folder + TString("Mostafa_pi0.root"));
    }
  
  
  
  TChain *bkg= new TChain("pDVCS");
  bkg->Add(Folder + TString("TMostafa_pi0.root"));

  if(means_most)
    {
      TString mvars[4] = {"Phi_Ph","t_Ph","strip_Q2","strip_Xbj"};
      double Lbound[4] = {0., -10., 0., 0.};
      double Ubound[4] = {360., 0., 10., 1.0};
      outFile.open(Folder + TString("means_most.txt"));
      outFile2.open(Folder + TString("contamination_most.txt"));
      outFile <<"bin_number mean_phi error mean_t eror mean_Q2 error mean_xB error"<<endl;
      outFile2 <<"bin_number entries_bef entries_aft before after"<<endl;

      for(int i=0; i<Nphi; i++)
	{
	  cut_phi =TCut(Form("Phi_Ph > %f && Phi_Ph < %f", (360./Nphi)*i, (360./Nphi)*(i+1)));
	  for(int j=0; j<4; j++)
	    {

	      TH1F *Data_p = new TH1F("Data_p","",1000,Lbound[j], Ubound[j]);
	      TH1F *Data_m = new TH1F("Data_m","",1000,Lbound[j], Ubound[j]);
	      TH1F *Data_p_BDT = new TH1F("Data_p_BDT","",1000,Lbound[j], Ubound[j]);
	      TH1F *Data_m_BDT = new TH1F("Data_m_BDT","",1000,Lbound[j], Ubound[j]);

	      Data_p->Sumw2();
	      Data_m->Sumw2();

	      Data->Project("Data_p", mvars[j], cut + cut_phi + TCut("Helicity>0"));
	      Data->Project("Data_m", mvars[j], cut + cut_phi + TCut("Helicity<0"));
	      Data->Project("Data_p_BDT", mvars[j], cut + cut_phi + TCut(Form("Helicity>0 && _strip_Nuc_BDT > %f",BDT_cut)));
	      Data->Project("Data_m_BDT", mvars[j], cut + cut_phi + TCut(Form("Helicity<0 && _strip_Nuc_BDT > %f",BDT_cut)));

	      //****************To get estimation before BDT*****************
	      TH1F *Phi_p = new TH1F("Phi_p","",1000,Lbound[j], Ubound[j]);
	      TH1F *Phi_m = new TH1F("Phi_m","",1000,Lbound[j], Ubound[j]);
	      Phi_p->Sumw2();
	      Phi_m->Sumw2();

	      bkg->Project("Phi_p", mvars[j], (cut + cut_phi )*TCut("Weight"));
	      bkg->Project("Phi_m", mvars[j], (cut + cut_phi )*TCut("Weight"));
	      
  	      est1=(Phi_p->Integral() + Phi_m->Integral())*1.0/(Data_p->Integral() + Data_m->Integral());
	      delete Phi_p;
	      delete Phi_m;
	      //*************************************************************
	      TH1F *Phi_p_BDT = new TH1F("Phi_p_BDT","",1000,Lbound[j], Ubound[j]);
	      TH1F *Phi_m_BDT = new TH1F("Phi_m_BDT","",1000,Lbound[j], Ubound[j]);

	      Phi_p_BDT->Sumw2();
	      Phi_m_BDT->Sumw2();

	      bkg->Project("Phi_p_BDT", mvars[j], (cut + cut_phi + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight"));
	      bkg->Project("Phi_m_BDT", mvars[j], (cut + cut_phi + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight"));
	      
	      entries_bef_most=Data_p_BDT->Integral() + Data_m_BDT->Integral() ;
	      est2=(Phi_p_BDT->Integral() + Phi_m_BDT->Integral())*1.0/(Data_p_BDT->Integral() + Data_m_BDT->Integral());

	      Data_p_BDT->Add(Data_p_BDT, Phi_p_BDT,1 ,-1);
	      Data_m_BDT->Add(Data_m_BDT, Phi_m_BDT,1 ,-1);
	      
	      for(int k=1; k<=Data_p_BDT->GetNbinsX(); k++)
		{
		  if(Data_p_BDT->GetBinContent(k) < 0)
		    Data_p_BDT->SetBinContent(k,0.0);

		  if(Data_m_BDT->GetBinContent(k) < 0)
		    Data_m_BDT->SetBinContent(k,0.0);	
		}

	      entries_aft_most=Data_p_BDT->Integral() + Data_m_BDT->Integral();

	      TH1F *mean_final= new TH1F("mean_final","mean_final",1000, Lbound[j], Ubound[j]);
	      mean_final->Add(Data_p_BDT, Data_m_BDT, 1, 1);

  
	  
	      if(j==0)
		{
		  std::cout<<"\n Mostafa estimation: Phi bin "<<i+1<<" : "<<est1*100<<"% "<<est2*100<<"%"<<endl;
		  outFile2<<i+1<<" "<<entries_bef_most<<" "<<entries_aft_most<<" "<<est1*100<<"% "<<est2*100<<"%"<<endl;

		  est1=mean_final->GetMean();
		  std::cout<<mvars[j]<<" mean in bin "<<i+1<<" is: "<<est1<<endl;
		  outFile<<" "<<est1<<" "<<mean_final->GetMeanError();
		}
	      else
		{
		  est1=mean_final->GetMean();
		  std::cout<<mvars[j]<<" mean in bin "<<i+1<<" is: "<<est1<<endl;
		  outFile<<" "<<est1<<" "<<mean_final->GetMeanError();
		}
	  
	      delete Phi_p_BDT;
	      delete Phi_m_BDT;
	      delete Data_p;
	      delete Data_m;
	      delete Data_p_BDT;
	      delete Data_m_BDT;
	      delete mean_final;

	    }
	  outFile<<" "<<endl;
	}
      outFile.close();
    }






  TH1F *Data_p = new TH1F("Data_p","",Nphi,0,360);
  TH1F *Data_m = new TH1F("Data_m","",Nphi,0,360);
  TH1F *Data_p_BDT = new TH1F("Data_p_BDT","",Nphi,0,360);
  TH1F *Data_m_BDT = new TH1F("Data_m_BDT","",Nphi,0,360);

  Data_p->Sumw2();
  Data_m->Sumw2();

  Data->Project("Data_p", "Phi_Ph", cut + TCut("Helicity>0"));
  Data->Project("Data_m", "Phi_Ph", cut + TCut("Helicity<0"));
  Data->Project("Data_p_BDT", "Phi_Ph", cut + TCut(Form("Helicity>0 && _strip_Nuc_BDT > %f",BDT_cut)));
  Data->Project("Data_m_BDT", "Phi_Ph", cut + TCut(Form("Helicity<0 && _strip_Nuc_BDT > %f",BDT_cut)));

  //****************To get estimation before BDT*****************
  TH1F *Phi_p = new TH1F("Phi_p","",Nphi,0,360);
  TH1F *Phi_m = new TH1F("Phi_m","",Nphi,0,360);
  Phi_p->Sumw2();
  Phi_m->Sumw2();

  bkg->Project("Phi_p", "Phi_Ph", (cut)*TCut("Weight"));
  bkg->Project("Phi_m", "Phi_Ph", (cut)*TCut("Weight"));
  std::cout<<Phi_p->Integral()<<endl;
  est1=(Phi_p->Integral() + Phi_m->Integral())*1.0/(Data_p->Integral() + Data_m->Integral());
  delete Phi_p;
  delete Phi_m;
  //*************************************************************
  TH1F *Phi_p_BDT = new TH1F("Phi_p_BDT","",Nphi,0,360);
  TH1F *Phi_m_BDT = new TH1F("Phi_m_BDT","",Nphi,0,360);

  Phi_p_BDT->Sumw2();
  Phi_m_BDT->Sumw2();

  bkg->Project("Phi_p_BDT", "Phi_Ph", (cut + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight"));
  bkg->Project("Phi_m_BDT", "Phi_Ph", (cut + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight"));

  entries_bef_most=Data_p_BDT->Integral() + Data_m_BDT->Integral();
  est2=(Phi_p_BDT->Integral() + Phi_m_BDT->Integral())*1.0/(Data_p_BDT->Integral() + Data_m_BDT->Integral());
  std::cout<<"Mostafa estimation "<<est1<<" "<<est2<<endl;
  
  Data_p_BDT->Add(Data_p_BDT, Phi_p_BDT,1 ,-1);
  Data_m_BDT->Add(Data_m_BDT, Phi_m_BDT,1 ,-1);
  
  for(int k=1; k<=Data_p_BDT->GetNbinsX(); k++)
    {
      if(Data_p_BDT->GetBinContent(k) < 0)
	Data_p_BDT->SetBinContent(k,0.0);

      if(Data_m_BDT->GetBinContent(k) < 0)
	Data_m_BDT->SetBinContent(k,0.0);	
    }

  entries_aft_most=Data_p_BDT->Integral() + Data_m_BDT->Integral();


  std::cout<<"Overall "<<entries_bef_most<<" "<<entries_aft_most<<" "<<est1*100<<"% "<<est2*100<<"%"<<endl;
  boundaries.push_back(est1);
  boundaries.push_back(est2);

  if(means_most)
    {
      outFile2<<"Overall "<<entries_bef_most<<" "<<entries_aft_most<<" "<<est1*100<<"% "<<est2*100<<"%"<<endl;
      outFile2.close();
    }
  
  TH1 *BA= Data_m_BDT->GetAsymmetry(Data_p_BDT);
  TCanvas* c2 = new TCanvas("c2","Histograms");

  
  //The fit gets attached to BA, so if BA is deleted, everything is deleted
  //That is why I plot a new "fit" function
  TF1 *fitf = new TF1("fitf","[0]*sin(x*TMath::Pi()/180)/(1+[1]*cos(x*TMath::Pi()/180))",0,360);
  fitf->SetParameter(0,0.1);
  fitf->SetParameter(1,-0.3);
  fitf->SetParLimits(0,0,1.0);
  fitf->SetParLimits(1,-1.,1.);
	  
  BA->SetAxisRange(-1., 1.,"Y");	  
  BA->Scale(1.0/Bpol);
  BA->Fit("fitf","Q");
  BA->SetTitle("RG-A note");


  // Create an output file to save the histogram
  TFile *outputFile = new TFile(Folder + TString("Mostafa_Clean.root"), "RECREATE");
  fitf->SetLineColor(kBlack);
  BA->SetLineColor(kBlack);
  BA->SetMarkerColor(kBlack);

  // Write the histogram to the output file
  BA->Write();

  // Close the output file
  outputFile->Close();

  std::ofstream outFile5(Folder + TString("BSA_Most_Values.txt"));
  for(int k=1; k<=BA->GetNbinsX(); k++)
    {
      outFile5<<Data_p_BDT->GetBinContent(k) + Data_m_BDT->GetBinContent(k)<<", "<<BA->GetBinContent(k)<<", "<<BA->GetBinError(k)<<endl;
    }
  
  outFile5.close();


  fitf->SetLineColor(kRed);
  BA->SetLineColor(kRed);
  BA->SetMarkerColor(kRed);
  BA->SetAxisRange(-0.3, 0.3,"Y");
  BA->SetAxisRange( 0. ,360.,"X");
  BA->GetXaxis()->SetTitle("#phi (deg)");
  BA->Draw();

  c2->Print(Folder + TString("Mostafa_BSA.pdf"));
  BSA_Amplitude_most=BA->GetBinContent(BA->GetMaximumBin());
  BSA_Amplitude_most_fit=fitf->GetParameter(0);
  BSA_Error_most_fit=fitf->GetParError(0);

  std::cout<<"Final amplitudes: value - fit "<<BSA_Amplitude_most<<" "<<BSA_Amplitude_most_fit<<endl;



  // Clean up memory
  delete outputFile;
      
  delete c2;
  delete Phi_p_BDT;
  delete Phi_m_BDT;
  
  delete Data_p;
  delete Data_m;
  delete Data_p_BDT;
  delete Data_m_BDT;
  
  delete Data;
  delete bkg;
  
  delete Pi01g;
  delete Pi02g;
  delete DIS1g;
  delete DIS2g;
  delete Pi02gData;
  
  return BA;
}
