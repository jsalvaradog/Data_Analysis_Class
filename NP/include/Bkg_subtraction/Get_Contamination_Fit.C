Double_t BDT::modelFunction(Double_t *x, Double_t *params) {
    // x[0] is the bin coordinate (if 1D histogram)
    Double_t a = params[0];
    Double_t b = params[1];
    Double_t c = params[2];

    // Retrieve bin contents from histograms
    //Double_t data = DATA->GetBinContent(DATA->FindBin(x[0]));
    Double_t dvcs = hDVCS->GetBinContent(hDVCS->FindBin(x[0]));
    Double_t pi0 = hPI0->GetBinContent(hPI0->FindBin(x[0]));
    Double_t sidis = hSIDIS->GetBinContent(hSIDIS->FindBin(x[0]));

    // Calculate the model value
    Double_t modelValue = a * dvcs + b * pi0 + c * sidis;

    // Return the difference squared from experimental data
    return modelValue;
    //return (data - modelValue) * (data - modelValue);
}

TH1* BDT::Get_Contamination_Fit(TCut cut, double BDT_cut, int Nphi)
{
  if(generate_fit)
    {
      //Initialization
      gStyle->SetOptStat(0);
      TCanvas *c1 = new TCanvas("c1","Histograms",1200,1000);
      c1->Divide(2,2);

      TChain *pDVCS_Data= new TChain("pDVCS");
      pDVCS_Data->Add(Folder + TData);

      TChain *pDVCS_Sim= new TChain("pDVCS");
      pDVCS_Sim->Add(Folder + TDVCS);

      TChain *pDVCS_Pi0= new TChain("pDVCS");
      pDVCS_Pi0->Add(Folder + TPi0);
      //pDVCS_Pi0->Add(Folder + TString("TMaxime_pi0.root"));

      TChain *pDVCS_Pi0_2= new TChain("pDVCS");
      pDVCS_Pi0_2->Add(Folder + TString("Tsidis.root"));

      TChain *pDVCS_bkg= new TChain("pDVCS");
      pDVCS_bkg->Add(Folder + TString("TMaxime_pi0.root"));


      auto hs1 = new THStack("hs1","M^{2}_{e#gamma X} (GeV^{2})");
      auto hs2 = new THStack("hs2","M^{2}_{e#gamma X} (GeV^{2})");
      auto hs3 = new THStack("hs3","M^{2}_{e#gamma X} (GeV^{2})");
      auto hs4 = new THStack("hs4","M^{2}_{e#gamma X} (GeV^{2})");

      TH1F *hist1c_Sim = new TH1F("hist1c_Sim","",100, 0., 2);
      TH1F *hist2c_Sim = new TH1F("hist2c_Sim","",100, 0., 2);
  
      TH1F *hist1c_Data_p = new TH1F("hist1c_Data_p","",100, 0., 2);
      TH1F *hist2c_Data_p = new TH1F("hist2c_Data_p","",100, 0., 2);
      TH1F *hist1c_Data_m = new TH1F("hist1c_Data_m","",100, 0., 2);
      TH1F *hist2c_Data_m = new TH1F("hist2c_Data_m","",100, 0., 2);

      TH1F *hist2c_bkg_p = new TH1F("hist2c_bkg_p","",100, 0., 2);
      TH1F *hist2c_bkg_m = new TH1F("hist2c_bkg_m","",100, 0., 2);

      TH1F *hist1c_Pi0 = new TH1F("hist1c_Pi0","",100, 0, 2);
      TH1F *hist2c_Pi0 = new TH1F("hist2c_Pi0","",100, 0, 2);

      TH1F *hist1c_Pi0_2 = new TH1F("hist1c_Pi0_2","",100, 0, 2);
      TH1F *hist2c_Pi0_2 = new TH1F("hist2c_Pi0_2","",100, 0, 2);

      TH1F *hist1c_SimAdd = new TH1F("hist1c_SimAdd","DVCS + #pi^{0}",100, 0., 2);
      TH1F *hist2c_SimAdd = new TH1F("hist2c_SimAdd","DVCS + #pi^{0}",100, 0., 2);
      TH1F *hist2c_SimAdd_2 = new TH1F("hist2c_SimAdd_2","DVCS + #pi^{0}",100, 0., 2);

      //Variables to plot
      const char *p2="mm2_eg";
      pDVCS_Data->Project("hist1c_Data_p", p2, cut + TCut("Helicity>0"));
      pDVCS_Data->Project("hist1c_Data_m", p2, cut + TCut("Helicity<0"));
      pDVCS_Data->Project("hist2c_Data_p", p2, cut + cut_ref + TCut(Form("_strip_Nuc_BDT > %f && Helicity>0", BDT_cut)));
      pDVCS_Data->Project("hist2c_Data_m", p2, cut + cut_ref + TCut(Form("_strip_Nuc_BDT > %f && Helicity<0", BDT_cut)));
      pDVCS_bkg->Project("hist2c_bkg_p", p2, (cut + cut_ref + TCut(Form("_strip_Nuc_BDT > %f && Helicity>0", BDT_cut)))* TCut("Weight"));
      pDVCS_bkg->Project("hist2c_bkg_m", p2, (cut + cut_ref + TCut(Form("_strip_Nuc_BDT > %f && Helicity<0", BDT_cut)))* TCut("Weight"));

      pDVCS_Sim->Project("hist1c_Sim", p2, cut);
      pDVCS_Sim->Project("hist2c_Sim", p2, cut + cut_ref + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut)));

      pDVCS_Pi0->Project("hist1c_Pi0", p2, cut); 
      pDVCS_Pi0->Project("hist2c_Pi0", p2, (cut + cut_ref + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut))));

      pDVCS_Pi0_2->Project("hist1c_Pi0_2", p2, cut);
      pDVCS_Pi0_2->Project("hist2c_Pi0_2", p2, cut + cut_ref + TCut(Form("_strip_Nuc_BDT > %f", BDT_cut)));

      double factor_p, factor_pi0_p, factor_sidis_p;
      double factor_m, factor_pi0_m, factor_sidis_m;
      double factor_bkg_p, factor_bkg_m;

      TF1 *fitFunc = new TF1("fitFunc",
        [this](double *x, double *par) -> double {
          return this->modelFunction(x, par);
          },    
        0, 3, 3  // xmin, xmax, npar
      );
      fitFunc->SetParameter(0, 0.25);
      fitFunc->SetParameter(1, 0.3);
      fitFunc->SetParameter(2, 0.2);
      fitFunc->SetParLimits(0, 0, 10);
      fitFunc->SetParLimits(1, 0, 10);
      fitFunc->SetParLimits(2, 0, 10);

      hist1c_Sim->SetLineColor(kBlack);
      hist1c_Data_p->SetLineColor(kRed);
      hist1c_Data_m->SetLineColor(kRed);
      hist1c_Pi0->SetLineColor(kBlue);
      hist1c_SimAdd->SetLineColor(kCyan);
      hist1c_Pi0_2->SetLineColor(kGreen);

      hist2c_Sim->SetLineColor(kBlack);
      hist2c_Data_p->SetLineColor(kRed);
      hist2c_Data_m->SetLineColor(kRed);
      hist2c_Pi0->SetLineColor(kBlue);
      hist2c_SimAdd->SetLineColor(kCyan);
      hist2c_Pi0_2->SetLineColor(kGreen);

      hist2c_bkg_p->SetLineColor(kMagenta);
      hist2c_bkg_m->SetLineColor(kMagenta);

      //**********************************//
      //Positive helicity case
      //**********************************//
      //Using a binned fit
  
      c1->cd(1);
      // Perform the fit
      hDVCS = hist1c_Sim;
      hPI0 = hist1c_Pi0;
      hSIDIS = hist1c_Pi0_2;
      hist1c_Data_p->Fit("fitFunc", "QNMR");
      // Retrieve fit results
      factor_p = fitFunc->GetParameter(0);
      factor_pi0_p = fitFunc->GetParameter(1);
      factor_sidis_p = fitFunc->GetParameter(2);

      gPad->SetLeftMargin(0.14);
      gPad->SetRightMargin(0.012);
      gPad->SetBottomMargin(0.15);
      gPad->SetTopMargin(0.1);

      hist1c_Sim->Scale(factor_p);
      hist1c_Pi0->Scale(factor_pi0_p);
      hist1c_Pi0_2->Scale(factor_sidis_p);

      hist1c_SimAdd->Add(hist1c_Sim, hist1c_Pi0,1,1);
      hist1c_SimAdd->Add(hist1c_SimAdd, hist1c_Pi0_2,1,1);

      hs1->Add(hist1c_Sim);
      hs1->Add(hist1c_Data_p);
      hs1->Add(hist1c_Pi0);
      hs1->Add(hist1c_Pi0_2);
      hs1->Add(hist1c_SimAdd);

      hs1->Draw("nostack,hist");
      hs1->SetTitle("Before BDT (Hel>0)");
      hs1->GetXaxis()->SetTitle("M_{e#gamma X}^{2} (GeV^{2})");
      hs1->GetYaxis()->SetTitle("Counts");
      hs1->GetXaxis()->SetTitleSize(0.07);
      hs1->GetYaxis()->SetTitleSize(0.07);
      hs1->GetXaxis()->SetLabelSize(0.06);
      hs1->GetYaxis()->SetLabelSize(0.06);
      hs1->GetYaxis()->SetTitleOffset(1.1);
      hs1->GetXaxis()->SetTitleOffset(1.0);
      hs1->GetYaxis()->SetNdivisions(6);
      hs1->GetXaxis()->SetNdivisions(8);
      hs1->DrawClone("nostack,hist");

    
      c1->cd(2);
      /*      
      // Perform the fit
      hDVCS = hist2c_Sim;
      hPI0 = hist2c_Pi0;
      hSIDIS = hist2c_Pi0_2;
      //hist2c_Sim->Scale(hist2c_Data_p->Integral() *0.9/ hist2c_Sim->Integral());
      //fitFunc->SetParLimits(0, 0.7, 1);   
      fitFunc->FixParameter(2, 0);   
      hist2c_Data_p->Fit("fitFunc", "QNMR");
      // Retrieve fit results
      factor_p = fitFunc->GetParameter(0);
      factor_pi0_p = fitFunc->GetParameter(1);
      factor_sidis_p = 1.0; //fitFunc->GetParameter(2);
      //Restore
      //fitFunc->ReleaseParameter(0);
      fitFunc->ReleaseParameter(2);
      */

      hDVCS = hist2c_Sim;
      hPI0 = hist2c_bkg_p;
      //fitFunc->FixParameter(0, 1);   
      fitFunc->SetParameter(1, 2);
      fitFunc->SetParLimits(1, 1, 50);
      fitFunc->FixParameter(2, 0);   
      hist2c_Data_p->Fit("fitFunc", "QNMR");
      // Retrieve fit results
      factor_p = fitFunc->GetParameter(0);
      factor_bkg_p = fitFunc->GetParameter(1);
      //Restore
      //fitFunc->ReleaseParameter(0);
      fitFunc->SetParLimits(1, 0, 10);
      fitFunc->ReleaseParameter(2);
      fitFunc->SetParameter(1, 1);

      gPad->SetLeftMargin(0.14);
      gPad->SetRightMargin(0.012);
      gPad->SetBottomMargin(0.15);
      gPad->SetTopMargin(0.1);

      hist2c_Sim->Scale(factor_p);
      hist2c_Pi0->Scale(factor_pi0_p);
      hist2c_Pi0_2->Scale(factor_sidis_p);
      //factor_bkg_p = hist2c_Pi0->Integral()/hist2c_bkg_p->Integral();
      hist2c_bkg_p->Scale(factor_bkg_p);
      
      hist2c_SimAdd->Add(hist2c_Sim, hist2c_Pi0,1,1);
      //hist2c_SimAdd->Add(hist2c_SimAdd, hist2c_Pi0_2,1,1);
      hist2c_SimAdd_2->Add(hist2c_Sim, hist2c_bkg_p,1,1);

      hs2->Add(hist2c_Sim);
      hs2->Add(hist2c_Data_p);
      hs2->Add(hist2c_Pi0);
      //hs2->Add(hist2c_Pi0_2);
      hs2->Add(hist2c_SimAdd);
      hs2->Add(hist2c_bkg_p);
      hs2->Add(hist2c_SimAdd_2);

      hs2->Draw("nostack,hist");
      hs2->SetTitle("After BDT (Hel>0)");
      hs2->GetXaxis()->SetTitle("M_{e#gamma X}^{2} (GeV^{2})");
      hs2->GetYaxis()->SetTitle("Counts");
      hs2->GetXaxis()->SetTitleSize(0.07);
      hs2->GetYaxis()->SetTitleSize(0.07);
      hs2->GetXaxis()->SetLabelSize(0.06);
      hs2->GetYaxis()->SetLabelSize(0.06);
      hs2->GetYaxis()->SetTitleOffset(1.1);
      hs2->GetXaxis()->SetTitleOffset(1.0);
      hs2->GetYaxis()->SetNdivisions(6);
      hs2->GetXaxis()->SetNdivisions(8);
      hs2->DrawClone("nostack,hist");
      
      //std::cout<<hist2c_Pi0->Integral()/hist2c_bkg_p->Integral()<<endl;

      // Legend
      TLegend *legend = new TLegend(); // Position of the legend
      legend->AddEntry(hist1c_Data_p, "Data", "l");
      legend->AddEntry(hist1c_Sim, "DVCS MC", "l");
      legend->AddEntry(hist1c_Pi0, "#pi^{0} MC", "l");
      legend->AddEntry(hist1c_Pi0_2, "Sidis MC", "l");
      legend->AddEntry(hist1c_SimAdd, "Total MC", "l");
      legend->Draw();

      // Re-scale to original
      hist1c_Sim->Scale(1./factor_p);
      hist1c_Pi0->Scale(1./factor_pi0_p);
      hist1c_Pi0_2->Scale(1./factor_sidis_p);
      hist2c_Sim->Scale(1./factor_p);
      hist2c_Pi0->Scale(1./factor_pi0_p);
      hist2c_Pi0_2->Scale(1./factor_sidis_p);


      //**********************************//
      //Negative helicity case
      //**********************************//
      double factor_dvcs_bef, factor_dvcs_aft;
      //plot 
      c1->cd(3);
      hDVCS = hist1c_Sim;
      hPI0 = hist1c_Pi0;
      hSIDIS = hist1c_Pi0_2;
      hist1c_Data_m->Fit("fitFunc", "QNMR");
      // Retrieve fit results
      factor_m = fitFunc->GetParameter(0);
      factor_pi0_m = fitFunc->GetParameter(1);
      factor_sidis_m = fitFunc->GetParameter(2);

      factor_dvcs_bef = factor_m;

      gPad->SetLeftMargin(0.14);
      gPad->SetRightMargin(0.012);
      gPad->SetBottomMargin(0.15);
      gPad->SetTopMargin(0.1);

      hist1c_Sim->Scale(factor_m);
      hist1c_Pi0->Scale(factor_pi0_m);
      hist1c_Pi0_2->Scale(factor_sidis_m);

      hist1c_SimAdd->Add(hist1c_Sim, hist1c_Pi0,1,1);
      hist1c_SimAdd->Add(hist1c_SimAdd, hist1c_Pi0_2,1,1);
  
      hs3->Add(hist1c_Sim);
      hs3->Add(hist1c_Data_m);
      hs3->Add(hist1c_Pi0);
      hs3->Add(hist1c_Pi0_2);
      hs3->Add(hist1c_SimAdd);

      hs3->Draw("nostack,hist");
      hs3->SetTitle("Before BDT (Hel<0)");
      hs3->GetXaxis()->SetTitle("M_{e#gamma X}^{2} (GeV^{2})");
      hs3->GetYaxis()->SetTitle("Counts");
      hs3->GetXaxis()->SetTitleSize(0.07);
      hs3->GetYaxis()->SetTitleSize(0.07);
      hs3->GetXaxis()->SetLabelSize(0.06);
      hs3->GetYaxis()->SetLabelSize(0.06);
      hs3->GetYaxis()->SetTitleOffset(1.1);
      hs3->GetXaxis()->SetTitleOffset(1.0);
      hs3->GetYaxis()->SetNdivisions(6);
      hs3->GetXaxis()->SetNdivisions(8);
      hs3->DrawClone("nostack,hist");

      c1->cd(4);
      //To fit independently
      /*
      hDVCS = hist2c_Sim;
      hPI0 = hist2c_Pi0;
      hSIDIS = hist2c_Pi0_2;
      //hist2c_Sim->Scale(hist2c_Data_m->GetMaximum() / hist2c_Sim->GetMaximum());
      //fitFunc->FixParameter(0, 1);
      fitFunc->FixParameter(2, 0);
      hist2c_Data_m->Fit("fitFunc", "QNMR");
      // Retrieve fit results
      factor_m = fitFunc->GetParameter(0);
      factor_pi0_m = fitFunc->GetParameter(1);
      factor_sidis_m = 1.0; //fitFunc->GetParameter(2);
      //Restore
      //fitFunc->ReleaseParameter(0);
      fitFunc->ReleaseParameter(2);
      */

      //To use the fit from bef_BDT
      hDVCS = hist2c_Sim;
      hPI0 = hist2c_bkg_m;
      //fitFunc->FixParameter(0, 1);
      fitFunc->SetParameter(1, 2);
      fitFunc->SetParLimits(1, 1, 50);
      fitFunc->FixParameter(2, 0);
      hist2c_Data_m->Fit("fitFunc", "QNMR");
      // Retrieve fit results
      factor_m = fitFunc->GetParameter(0);
      factor_bkg_m = fitFunc->GetParameter(1);
      //Restore
      //fitFunc->ReleaseParameter(0);
      fitFunc->SetParLimits(1, 0, 10);
      fitFunc->SetParameter(1, 1);
      fitFunc->ReleaseParameter(2);

      factor_dvcs_aft = factor_m;


      gPad->SetLeftMargin(0.14);
      gPad->SetRightMargin(0.012);
      gPad->SetBottomMargin(0.15);
      gPad->SetTopMargin(0.1);

      hist2c_Sim->Scale(factor_m);
      hist2c_Pi0->Scale(factor_pi0_m);
      hist2c_Pi0_2->Scale(factor_sidis_m);
      //factor_bkg_m = hist2c_Pi0->Integral()/hist2c_bkg_m->Integral();
      hist2c_bkg_m->Scale(factor_bkg_m);

      hist2c_SimAdd->Add(hist2c_Sim, hist2c_Pi0,1,1);
      //hist2c_SimAdd->Add(hist2c_SimAdd, hist2c_Pi0_2,1,1);
      hist2c_SimAdd_2->Add(hist2c_Sim, hist2c_bkg_m,1,1);

      hs4->Add(hist2c_Sim);
      hs4->Add(hist2c_Data_m);
      hs4->Add(hist2c_Pi0);
      //hs4->Add(hist2c_Pi0_2);
      hs4->Add(hist2c_SimAdd);
      hs4->Add(hist2c_bkg_m);
      hs4->Add(hist2c_SimAdd_2);

      hs4->Draw("nostack,hist");
      hs4->SetTitle("After BDT (Hel<0)");
      hs4->GetXaxis()->SetTitle("M_{e#gamma X}^{2} (GeV^{2})");
      hs4->GetYaxis()->SetTitle("Counts");
      hs4->GetXaxis()->SetTitleSize(0.07);
      hs4->GetYaxis()->SetTitleSize(0.07);
      hs4->GetXaxis()->SetLabelSize(0.06);
      hs4->GetYaxis()->SetLabelSize(0.06);
      hs4->GetYaxis()->SetTitleOffset(1.1);
      hs4->GetXaxis()->SetTitleOffset(1.0);
      hs4->GetYaxis()->SetNdivisions(6);
      hs4->GetXaxis()->SetNdivisions(8);
      hs4->DrawClone("nostack,hist");

      //std::cout<<hist2c_Pi0->Integral()/hist2c_bkg_m->Integral()<<endl;
      std::cout<<"Maxime scaling factors: "<<factor_bkg_p<<" "<<factor_bkg_m<<endl;
      c1->Print(Folder + TString("Bkg_fit.pdf"));
      std::cout<<"DVCS scaling factors: "<<factor_dvcs_bef<<" "<<factor_dvcs_aft<<" "<<factor_dvcs_aft/factor_dvcs_bef<<endl;
      boundaries.push_back(factor_dvcs_aft/factor_dvcs_bef);

      delete c1;
      delete pDVCS_Data;
      delete pDVCS_Sim;
      delete hist1c_Sim;
      delete hist1c_Data_p;
      delete hist1c_Data_m;
      delete hist2c_Sim;
      delete hist2c_Data_p;
      delete hist2c_Data_m;
      delete hist2c_bkg_p;
      delete hist2c_bkg_m;
      delete hist1c_Pi0;
      delete hist1c_Pi0_2;
      delete hist1c_SimAdd;
      delete fitFunc;
      delete hs1;
      delete hs2;
      delete hs3;
      delete hs4;
      delete legend;


      //********************************************
      //output Fit tree
      //*******************************************

      double weight;

      //output Pi0_p tree
      Double_t phi_M1;
      static vector<int>* flag_M1;
      static int hel1;

      TFile* out_sim1=new TFile(Folder + TString("Fit_Pi0.root"), "RECREATE");
      //pDVCS_Pi0->SetBranchStatus("Helicity", 0);
      TTree *tree1 = pDVCS_bkg->CopyTree(cut);
      tree1->SetMaxTreeSize(100000000000LL);

      TBranch* Wb1 = tree1->Branch("Weight_Fit", &weight);
      //TBranch* He_p1 = tree1->Branch("Helicity", &hel1);

      tree1->SetBranchAddress("Phi_Ph",&phi_M1);
      tree1->SetBranchAddress("Helicity",&hel1);
      //tree1->SetBranchAddress("bestCandidateFlag",&flag_M1);

      for(int t=0; t<tree1->GetEntries();t++)
	{
	  tree1->GetEntry(t);
    if(hel1>0)
    {weight = factor_bkg_p;}
    else
    {weight = factor_bkg_m;}

		  Wb1->Fill();
	}

      tree1->Write();
      delete tree1;
      out_sim1->Close();
      delete out_sim1;
  
/*
      //Output Sidis_p tree
      static vector<double>* phi_M2;
      static vector<int>* flag_M2;
      static int hel2;

      TFile* out_sim2=new TFile(Folder + TString("Fit_SIDIS_p.root"), "RECREATE");
      TTree *tree2 = pDVCS_Pi0_2->CopyTree(cut);
      tree2->SetMaxTreeSize(100000000000LL);

      TBranch* Wb2 = tree2->Branch("Weight_Fit", &weight);
      TBranch* He_p2 = tree2->Branch("Helicity", &hel2);

      tree2->SetBranchAddress("Phi_Ph",&phi_M2);
      tree2->SetBranchAddress("Helicity",&hel2);
      tree2->SetBranchAddress("bestCandidateFlag",&flag_M2);

      for(int t=0; t<tree2->GetEntries();t++)
	{
	  tree2->GetEntry(t);
	  for(int t1=0; t1<flag_M2->size(); t1++)
	    {
	      if(flag_M2->at(t1)==1)
		{
      hel2=1;
      weight = factor_sidis_p;
      He_p2->Fill();
      Wb2->Fill();
		}
	    }
	}
	  	
      tree2->Write();
      delete tree2;
      out_sim2->Close();
      delete out_sim2;
  
      //Output Sidis_m tree
      static vector<double>* phi_M4;
      static vector<int>* flag_M4;
      static int hel4;

      TFile* out_sim4=new TFile(Folder + TString("Fit_SIDIS_m.root"), "RECREATE");
      TTree *tree4 = pDVCS_Pi0_2->CopyTree(cut);
      tree4->SetMaxTreeSize(100000000000LL);

      TBranch* Wb4 = tree4->Branch("Weight_Fit", &weight);
      TBranch* He_m4 = tree4->Branch("Helicity", &hel4);

      tree4->SetBranchAddress("Phi_Ph",&phi_M4);
      tree4->SetBranchAddress("Helicity",&hel4);
      tree4->SetBranchAddress("bestCandidateFlag",&flag_M4);

      for(int t=0; t<tree4->GetEntries();t++)
	{
	  tree4->GetEntry(t);
	  for(int t1=0; t1<flag_M4->size(); t1++)
	    {
	      if(flag_M4->at(t1)==1)
		{
      hel4=1;
      weight = factor_sidis_m;
      He_m4->Fill();
      Wb4->Fill();
	    }
	  }
  }

      tree4->Write();
      delete tree4;
      out_sim4->Close();
      delete out_sim4;
*/
      //Merge
      TFile* outFileFit=new TFile(Folder + "Bkg_Fit.root", "RECREATE");
      TChain *outChain= new TChain("pDVCS");
      outChain->Add(Folder + TString("Fit_Pi0.root"));
      //outChain->Add(Folder + TString("Fit_Pi0_m.root"));
      //outChain->Add(Folder + TString("Fit_SIDIS_p.root"));
      //outChain->Add(Folder + TString("Fit_SIDIS_m.root"));
      TTree *outTree = outChain->CopyTree(cut);

      outTree->Write();
      delete outTree;
      outFileFit->Close();
      delete outFileFit;
      delete outChain;
      gSystem->Exec(TString("rm ") + Folder + TString("Fit_Pi0.root"));
      //gSystem->Exec(TString("rm ") + Folder + TString("Fit_Pi0_m.root"));
      //gSystem->Exec(TString("rm ") + Folder + TString("Fit_SIDIS_p.root"));
      //gSystem->Exec(TString("rm ") + Folder + TString("Fit_SIDIS_m.root"));

      delete pDVCS_bkg;
      delete pDVCS_Pi0;
      delete pDVCS_Pi0_2;
    }

  //**********************************************/
  //Get subtracted BSA
  //**********************************************/
  TCut cut_phi;
  double est1;
  double est1_FT;
  double est1_FD;
  double est2;
  double est2_FT;
  double est2_FD;
  std::ofstream outFile;
  std::ofstream outFile2;

  TChain *Data= new TChain("pDVCS");
  Data->Add(Folder + TData);

  TChain *bkg= new TChain("pDVCS");
  bkg->Add(Folder + TString("Bkg_Fit.root"));

  cut = cut  + cut_ref;
  TString mvars[4] = {"Phi_Ph","t_Ph","strip_Q2","strip_Xbj"};
  double Lbound[4] = {0.  , boundaries.at(0), boundaries.at(2), boundaries.at(4)};
  double Ubound[4] = {360., boundaries.at(1), boundaries.at(3), boundaries.at(5)};

  //Mean on the 3D bin
  for(int j=1; j<4; j++)
    {
      TH1F *Data_BDT = new TH1F("Data_BDT","",1000,Lbound[j], Ubound[j]);
      Data_BDT->Sumw2();

      TH1F *Phi_BDT = new TH1F("Phi_BDT","",1000,Lbound[j], Ubound[j]);
      Phi_BDT->Sumw2();

      Data->Project("Data_BDT", mvars[j], cut + cut_phi + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)));
      bkg->Project("Phi_BDT", mvars[j], (cut + cut_phi + TCut(Form("_strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight*Weight_Fit"));

      if(Data_BDT->Integral() < Phi_BDT->Integral())
	{
	  for(int k=1; k<=Data_BDT->GetNbinsX(); k++)
	    Phi_BDT->SetBinContent(k, Data_BDT->GetBinContent(k));
	}

      Data_BDT->Add(Data_BDT, Phi_BDT,1 ,-1);
      std::cout<<mvars[j]<<" (Fit) mean is: "<<Data_BDT->GetMean()<<endl;
	  
      switch(j)
	{
	case 1:
	  tmean1 = Data_BDT->GetMean();
	  break;
	case 2:
	  Qmean1 = Data_BDT->GetMean();
	  break;
	case 3:
	  xmean1 = Data_BDT->GetMean();
	  break;
	}
      delete Phi_BDT;
      delete Data_BDT;

    }
  //end of mean on the 3D bin

  if(means_fit)
    {
      TString mvars[4] = {"Phi_Ph","t_Ph","strip_Q2","strip_Xbj"};
      double Lbound[4] = {0., -10., 0., 0.};
      double Ubound[4] = {360., 0., 10., 1.0};

      outFile.open(Folder + TString("means_Fit.txt"));
      outFile2.open(Folder + TString("contamination_Fit.txt"));
      
      outFile <<"mean_phi error mean_t error mean_Q2 error mean_xB error"<<endl;
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
	      
	      //No helicity cut because it is simulated data
	      bkg->Project("Phi_p", mvars[j], (cut + cut_phi + TCut("Helicity > 0"))*TCut("Weight*Weight_Fit"));
	      bkg->Project("Phi_m", mvars[j], (cut + cut_phi + TCut("Helicity < 0"))*TCut("Weight*Weight_Fit"));
	      
	      if(Data_p->Integral() < Phi_p->Integral())
		{
		  for(int k=1; k<=Data_p->GetNbinsX(); k++)
		    Phi_p->SetBinContent(k, Data_p->GetBinContent(k));
		}

	      if(Data_m->Integral() < Phi_m->Integral())
		{
		  for(int k=1; k<=Data_m->GetNbinsX(); k++)
		    Phi_m->SetBinContent(k, Data_m->GetBinContent(k));
		}
		
		
	      if(Data_p->Integral() + Data_m->Integral() ==0)
		est1=0;
	      else
		est1=(Phi_p->Integral() + Phi_m->Integral())*1.0/(Data_p->Integral() + Data_m->Integral());  

	      delete Phi_p;
	      delete Phi_m;
	      //*************************************************************
	      TH1F *Phi_p_BDT = new TH1F("Phi_p_BDT","",1000,Lbound[j], Ubound[j]);
	      TH1F *Phi_m_BDT = new TH1F("Phi_m_BDT","",1000,Lbound[j], Ubound[j]);

	      Phi_p_BDT->Sumw2();
	      Phi_m_BDT->Sumw2();

	      bkg->Project("Phi_p_BDT", mvars[j], (cut + cut_phi + TCut(Form("Helicity > 0 && _strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight*Weight_Fit"));
	      bkg->Project("Phi_m_BDT", mvars[j], (cut + cut_phi + TCut(Form("Helicity < 0 && _strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight*Weight_Fit"));

	      if(Data_p_BDT->Integral() < Phi_p_BDT->Integral())
		{
		  for(int k=1; k<=Data_p_BDT->GetNbinsX(); k++)
		    Phi_p_BDT->SetBinContent(k, Data_p_BDT->GetBinContent(k));
		}

	      if(Data_m_BDT->Integral() < Phi_m_BDT->Integral())
		{
		  for(int k=1; k<=Data_m_BDT->GetNbinsX(); k++)
		    Phi_m_BDT->SetBinContent(k, Data_m_BDT->GetBinContent(k));
		}

	      entries_bef_Fit=Data_p_BDT->Integral() + Data_m_BDT->Integral() ;
	      if(Data_p_BDT->Integral() + Data_m_BDT->Integral() ==0)
		est2=0;
	      else
		est2=(Phi_p_BDT->Integral() + Phi_m_BDT->Integral())*1.0/(Data_p_BDT->Integral() + Data_m_BDT->Integral());

	      Data_p_BDT->Add(Data_p_BDT, Phi_p_BDT,1 ,-1);
	      Data_m_BDT->Add(Data_m_BDT, Phi_m_BDT,1 ,-1);
	      
	      entries_aft_Fit=Data_p_BDT->Integral() + Data_m_BDT->Integral();

	      TH1F *mean_final= new TH1F("mean_final","mean_final",1000, Lbound[j], Ubound[j]);
	      mean_final->Add(Data_p_BDT, Data_m_BDT, 1, 1);

  
	  
	      if(j==0)
		{
		  std::cout<<"\n Fit estimation: Phi bin "<<i+1<<" : "<<est1*100<<"% "<<est2*100<<"%"<<endl;
		  outFile2<<i+1<<" "<<entries_bef_Fit<<" "<<entries_aft_Fit<<" "<<est1*100<<"% "<<est2*100<<"%"<<endl;

		  if(entries_aft_Fit>1)
		    est1=mean_final->GetMean();
		  else
		    est1=0;

		  std::cout<<mvars[j]<<" mean in bin "<<i+1<<" is: "<<est1<<endl;
		  outFile<<" "<<est1<<" "<<mean_final->GetStdDev();
		}
	      else
		{
		  if(entries_aft_Fit>1)
		    est1=mean_final->GetMean();
		  else
		    est1=0;

		  std::cout<<mvars[j]<<" mean in bin "<<i+1<<" is: "<<est1<<endl;
		  outFile<<" "<<est1<<" "<<mean_final->GetStdDev();
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
  TH1F *Data_p_FT = new TH1F("Data_p_FT","",Nphi,0,360);
  TH1F *Data_m_FT = new TH1F("Data_m_FT","",Nphi,0,360);
  TH1F *Data_p_FD = new TH1F("Data_p_FD","",Nphi,0,360);
  TH1F *Data_m_FD = new TH1F("Data_m_FD","",Nphi,0,360);
  TH1F *Data_p_BDT = new TH1F("Data_p_BDT","",Nphi,0,360);
  TH1F *Data_m_BDT = new TH1F("Data_m_BDT","",Nphi,0,360);
  TH1F *Data_p_BDT_FT = new TH1F("Data_p_BDT_FT","",Nphi,0,360);
  TH1F *Data_m_BDT_FT = new TH1F("Data_m_BDT_FT","",Nphi,0,360);
  TH1F *Data_p_BDT_FD = new TH1F("Data_p_BDT_FD","",Nphi,0,360);
  TH1F *Data_m_BDT_FD = new TH1F("Data_m_BDT_FD","",Nphi,0,360);

  Data_p->Sumw2();
  Data_m->Sumw2();

  Data->Project("Data_p", "Phi_Ph", cut + TCut("Helicity>0"));
  Data->Project("Data_m", "Phi_Ph", cut + TCut("Helicity<0"));
  Data->Project("Data_p_FT", "Phi_Ph", cut + TCut("strip_Ph_Theta < 5 && Helicity>0"));
  Data->Project("Data_m_FT", "Phi_Ph", cut + TCut("strip_Ph_Theta < 5 && Helicity<0"));
  Data->Project("Data_p_FD", "Phi_Ph", cut + TCut("strip_Ph_Theta > 5 && Helicity>0"));
  Data->Project("Data_m_FD", "Phi_Ph", cut + TCut("strip_Ph_Theta > 5 && Helicity<0"));
  Data->Project("Data_p_BDT", "Phi_Ph", cut + TCut(Form("Helicity>0 && _strip_Nuc_BDT > %f",BDT_cut)));
  Data->Project("Data_m_BDT", "Phi_Ph", cut + TCut(Form("Helicity<0 && _strip_Nuc_BDT > %f",BDT_cut)));
  Data->Project("Data_p_BDT_FT", "Phi_Ph", cut + TCut(Form("strip_Ph_Theta < 5 && Helicity>0 && _strip_Nuc_BDT > %f",BDT_cut)));
  Data->Project("Data_m_BDT_FT", "Phi_Ph", cut + TCut(Form("strip_Ph_Theta < 5 && Helicity<0 && _strip_Nuc_BDT > %f",BDT_cut)));
  Data->Project("Data_p_BDT_FD", "Phi_Ph", cut + TCut(Form("strip_Ph_Theta > 5 && Helicity>0 && _strip_Nuc_BDT > %f",BDT_cut)));
  Data->Project("Data_m_BDT_FD", "Phi_Ph", cut + TCut(Form("strip_Ph_Theta > 5 && Helicity<0 && _strip_Nuc_BDT > %f",BDT_cut)));

  //****************To get estimation before BDT*****************

  TH1F *Phi_p = new TH1F("Phi_p","",Nphi,0,360);
  TH1F *Phi_m = new TH1F("Phi_m","",Nphi,0,360);
  TH1F *Phi_p_FT = new TH1F("Phi_p_FT","",Nphi,0,360);
  TH1F *Phi_m_FT = new TH1F("Phi_m_FT","",Nphi,0,360);
  TH1F *Phi_p_FD = new TH1F("Phi_p_FD","",Nphi,0,360);
  TH1F *Phi_m_FD = new TH1F("Phi_m_FD","",Nphi,0,360);

  Phi_p->Sumw2();
  Phi_m->Sumw2();
  Phi_p_FT->Sumw2();
  Phi_m_FT->Sumw2();
  Phi_p_FD->Sumw2();
  Phi_m_FD->Sumw2();

  bkg->Project("Phi_p", "Phi_Ph", (cut + TCut("Helicity > 0"))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_m", "Phi_Ph", (cut + TCut("Helicity < 0"))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_p_FT", "Phi_Ph", (cut + TCut("strip_Ph_Theta < 5 && Helicity > 0"))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_m_FT", "Phi_Ph", (cut + TCut("strip_Ph_Theta < 5 && Helicity < 0"))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_p_FD", "Phi_Ph", (cut + TCut("strip_Ph_Theta > 5 && Helicity > 0"))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_m_FD", "Phi_Ph", (cut + TCut("strip_Ph_Theta > 5 && Helicity < 0"))*TCut("Weight*Weight_Fit"));

  for(int k=1; k<=Data_p->GetNbinsX(); k++)
    {
      if(Data_p->GetBinContent(k) < Phi_p->GetBinContent(k))
	{
	  Phi_p->SetBinContent(k, Data_p->GetBinContent(k));
	}
      if(Data_m->GetBinContent(k) < Phi_m->GetBinContent(k))
	{
	  Phi_m->SetBinContent(k, Data_m->GetBinContent(k));
	}
      if(Data_p_FT->GetBinContent(k) < Phi_p_FT->GetBinContent(k))
	{
	  Phi_p_FT->SetBinContent(k, Data_p_FT->GetBinContent(k));
	}
      if(Data_m_FT->GetBinContent(k) < Phi_m_FT->GetBinContent(k))
	{
	  Phi_m_FT->SetBinContent(k, Data_m_FT->GetBinContent(k));
	}
      if(Data_p_FD->GetBinContent(k) < Phi_p_FD->GetBinContent(k))
	{
	  Phi_p_FD->SetBinContent(k, Data_p_FD->GetBinContent(k));
	}
      if(Data_m_FD->GetBinContent(k) < Phi_m_FD->GetBinContent(k))
	{
	  Phi_m_FD->SetBinContent(k, Data_m_FD->GetBinContent(k));
	}
    }

  if(Data_p->Integral() + Data_m->Integral() ==0)
    est1=0;
  else
    est1=(Phi_p->Integral() + Phi_m->Integral())*1.0/(Data_p->Integral() + Data_m->Integral());  

  if(Data_p_FT->Integral() + Data_m_FT->Integral() ==0)
    est1_FT=0;
  else
    est1_FT=(Phi_p_FT->Integral() + Phi_m_FT->Integral())*1.0/(Data_p_FT->Integral() + Data_m_FT->Integral());  

  if(Data_p_FD->Integral() + Data_m_FD->Integral() ==0)
    est1_FD=0;
  else
    est1_FD=(Phi_p_FD->Integral() + Phi_m_FD->Integral())*1.0/(Data_p_FD->Integral() + Data_m_FD->Integral());  


  delete Phi_p;
  delete Phi_m;
  delete Phi_p_FT;
  delete Phi_m_FT;
  delete Phi_p_FD;
  delete Phi_m_FD;
  delete Data_p_FT;
  delete Data_m_FT;
  delete Data_p_FD;
  delete Data_m_FD;
  //*************************************************************
  TH1F *Phi_p_BDT = new TH1F("Phi_p_BDT","",Nphi,0,360);
  TH1F *Phi_m_BDT = new TH1F("Phi_m_BDT","",Nphi,0,360);
  TH1F *Phi_p_BDT_FT = new TH1F("Phi_p_BDT_FT","",Nphi,0,360);
  TH1F *Phi_m_BDT_FT = new TH1F("Phi_m_BDT_FT","",Nphi,0,360);
  TH1F *Phi_p_BDT_FD = new TH1F("Phi_p_BDT_FD","",Nphi,0,360);
  TH1F *Phi_m_BDT_FD = new TH1F("Phi_m_BDT_FD","",Nphi,0,360);

  Phi_p_BDT->Sumw2();
  Phi_m_BDT->Sumw2();

  bkg->Project("Phi_p_BDT", "Phi_Ph", (cut + TCut(Form("Helicity > 0 && _strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_m_BDT", "Phi_Ph", (cut + TCut(Form("Helicity < 0 && _strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_p_BDT_FT", "Phi_Ph", (cut + TCut(Form("strip_Ph_Theta < 5 && Helicity > 0 && _strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_m_BDT_FT", "Phi_Ph", (cut + TCut(Form("strip_Ph_Theta < 5 && Helicity < 0 && _strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_p_BDT_FD", "Phi_Ph", (cut + TCut(Form("strip_Ph_Theta > 5 && Helicity > 0 && _strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight*Weight_Fit"));
  bkg->Project("Phi_m_BDT_FD", "Phi_Ph", (cut + TCut(Form("strip_Ph_Theta > 5 && Helicity < 0 && _strip_Nuc_BDT > %f",BDT_cut)))*TCut("Weight*Weight_Fit"));

  for(int k=1; k<=Data_p_BDT->GetNbinsX(); k++)
    {
      if(Data_p_BDT->GetBinContent(k) < Phi_p_BDT->GetBinContent(k))
	{
	  Phi_p_BDT->SetBinContent(k, Data_p_BDT->GetBinContent(k));
	}
      if(Data_m_BDT->GetBinContent(k) < Phi_m_BDT->GetBinContent(k))
	{
	  Phi_m_BDT->SetBinContent(k, Data_m_BDT->GetBinContent(k));
	}
      if(Data_p_BDT_FT->GetBinContent(k) < Phi_p_BDT_FT->GetBinContent(k))
	{
	  Phi_p_BDT_FT->SetBinContent(k, Data_p_BDT_FT->GetBinContent(k));
	}
      if(Data_m_BDT_FT->GetBinContent(k) < Phi_m_BDT_FT->GetBinContent(k))
	{
	  Phi_m_BDT_FT->SetBinContent(k, Data_m_BDT_FT->GetBinContent(k));
	}
      if(Data_p_BDT_FD->GetBinContent(k) < Phi_p_BDT_FD->GetBinContent(k))
	{
	  Phi_p_BDT_FD->SetBinContent(k, Data_p_BDT_FD->GetBinContent(k));
	}
      if(Data_m_BDT_FD->GetBinContent(k) < Phi_m_BDT_FD->GetBinContent(k))
	{
	  Phi_m_BDT_FD->SetBinContent(k, Data_m_BDT_FD->GetBinContent(k));
	}
    }

  entries_bef_Fit=Data_p_BDT->Integral() + Data_m_BDT->Integral();
  entries_bef_Fit_FT=Data_p_BDT_FT->Integral() + Data_m_BDT_FT->Integral();
  entries_bef_Fit_FD=Data_p_BDT_FD->Integral() + Data_m_BDT_FD->Integral();
 
  if(Data_p_BDT->Integral() + Data_m_BDT->Integral() ==0)
    est2=0;
  else
    est2=(Phi_p_BDT->Integral() + Phi_m_BDT->Integral())*1.0/(Data_p_BDT->Integral() + Data_m_BDT->Integral());

  if(Data_p_BDT_FT->Integral() + Data_m_BDT_FT->Integral() ==0)
    est2_FT=0;
  else
    est2_FT=(Phi_p_BDT_FT->Integral() + Phi_m_BDT_FT->Integral())*1.0/(Data_p_BDT_FT->Integral() + Data_m_BDT_FT->Integral());

  if(Data_p_BDT_FD->Integral() + Data_m_BDT_FD->Integral() ==0)
    est2_FD=0;
  else
    est2_FD=(Phi_p_BDT_FD->Integral() + Phi_m_BDT_FD->Integral())*1.0/(Data_p_BDT_FD->Integral() + Data_m_BDT_FD->Integral());
  std::cout<<"Fit estimation "<<est1<<" "<<est2<<endl;
  std::cout<<"Fit estimation FT "<<est1_FT<<" "<<est2_FT<<endl;
  std::cout<<"Fit estimation FD "<<est1_FD<<" "<<est2_FD<<endl;
  
  Data_p_BDT->Add(Data_p_BDT, Phi_p_BDT,1 ,-1);
  Data_m_BDT->Add(Data_m_BDT, Phi_m_BDT,1 ,-1);
  
  entries_aft_Fit=Data_p_BDT->Integral() + Data_m_BDT->Integral();
  entries_aft_Fit_FT=Data_p_BDT_FT->Integral() + Data_m_BDT_FT->Integral();
  entries_aft_Fit_FD=Data_p_BDT_FD->Integral() + Data_m_BDT_FD->Integral();

  std::cout<<"Overall "<<entries_bef_Fit<<" "<<entries_aft_Fit<<" "<<entries_bef_Fit_FT<<" "<<entries_bef_Fit_FD<<" (Total "<<entries_bef_Fit_FT+entries_bef_Fit_FD<<") "<<est1*100<<"% "<<est2*100<<"% "<<est1_FT*100<<"% "<<est2_FT*100<<"% "<<est1_FD*100<<"% "<<est2_FD*100<<"% "<<endl;
  boundaries.push_back(est1);
  boundaries.push_back(est2);
  boundaries.push_back(est1_FT);
  boundaries.push_back(est2_FT);
  boundaries.push_back(est1_FD);
  boundaries.push_back(est2_FD);

  if(means_fit)
    {
      outFile2<<"Overall "<<entries_bef_Fit<<" "<<entries_aft_Fit<<" "<<est1*100<<"% "<<est2*100<<"%"<<endl;
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
  //BA->Fit("fitf","Q");
  BA->SetTitle("RG-A note");


  // Create an output file to save the histogram
  TFile *outputFile = new TFile(Folder + TString("Fit_Clean.root"), "RECREATE");
  fitf->SetLineColor(kBlack);
  BA->SetLineColor(kBlack);
  BA->SetMarkerColor(kBlack);

  // Write the histogram to the output file
  BA->Write();

  // Close the output file
  outputFile->Close();

  std::ofstream outFile5(Folder + TString("BSA_Most_Values.txt"));
  std::ofstream outFile6(Folder + TString("entries_Fit_p.txt"));
  std::ofstream outFile7(Folder + TString("entries_Fit_m.txt"));
  for(int k=1; k<=BA->GetNbinsX(); k++)
    {
      outFile5<<Data_p_BDT->GetBinContent(k) + Data_m_BDT->GetBinContent(k)<<", "<<BA->GetBinContent(k)<<", "<<BA->GetBinError(k)<<endl;
      outFile6<<Data_p_BDT->GetBinContent(k)<<endl;
      outFile7<<Data_m_BDT->GetBinContent(k)<<endl;
    }
  outFile5.close();
  outFile6.close();
  outFile7.close();

  delete outputFile;




  fitf->SetLineColor(kRed);
  BA->SetLineColor(kRed);
  BA->SetMarkerColor(kRed);
  BA->SetAxisRange(-1.0, 1.0,"Y");
  BA->SetAxisRange( 0. ,360.,"X");
  BA->GetXaxis()->SetTitle("#phi(deg)");
  BA->GetYaxis()->SetTitle("BSA");
  BA->SetTitle("Method 1 estimation");
  BA->GetXaxis()->SetTitleSize(0.06);
  BA->GetYaxis()->SetTitleSize(0.06);
  BA->GetXaxis()->SetLabelSize(0.05);
  BA->GetYaxis()->SetLabelSize(0.05);
  BA->GetYaxis()->SetTitleOffset(0.5);
  BA->GetXaxis()->SetTitleOffset(0.5);
  BA->GetYaxis()->SetNdivisions(6);
  BA->GetXaxis()->SetNdivisions(4);
  BA->Draw();

  c2->Print(Folder + TString("Fit_BSA.pdf"));

  BSA_Amplitude_Fit=BA->GetBinContent(BA->GetMaximumBin());
  BSA_Amplitude_Fit_fit=fitf->GetParameter(0);
  BSA_Error_Fit_fit=fitf->GetParError(0);

  std::cout<<"Final amplitudes: value - fit "<<BSA_Amplitude_Fit<<" "<<BSA_Amplitude_Fit_fit<<endl;



  // Clean up memory
  delete c2;
  delete Phi_p_BDT;
  delete Phi_m_BDT;
  delete Phi_p_BDT_FT;
  delete Phi_m_BDT_FT;
  delete Phi_p_BDT_FD;
  delete Phi_m_BDT_FD;
  delete Data_p;
  delete Data_m;
  delete Data_p_BDT;
  delete Data_m_BDT;
  delete Data_p_BDT_FT;
  delete Data_m_BDT_FT;
  delete Data_p_BDT_FD;
  delete Data_m_BDT_FD;
  
  delete Data;
  delete bkg;
  
  return BA;
}

