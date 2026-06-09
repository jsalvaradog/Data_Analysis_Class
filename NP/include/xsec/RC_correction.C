TH1F* BDT::F_RC(int Nphi, TH1F*& Systematics) {
  gSystem->Exec(Form("cd %s%s && /work/clas12/jsalvg/RGA-Simulation/dvcsgen/dvcsgen --trig 1000000 --gpd 101 --nmax 1000000 --beam 10.6 --zpos -3.0 --zwidth 2.5 --radgen --writef 2 --radstable --y 0.01 0.97 --th 0.03 1 --ycol 0.0005 --weight --t %f %f --q2 %f %f --x %f %f >> /dev/null && cd -",dir.Data(), Folder.Data(),-1.0*boundaries.at(1),-1.0*boundaries.at(0),boundaries.at(2),boundaries.at(3),boundaries.at(4),boundaries.at(5)));
  gSystem->Exec(Form("cd %s%s && cp %s/include/xsec/lund2root_RC.C . && clas12root -l -b -q lund2root_RC.C && mv dvcsgen_test.root dvcsgen_DVCS_gen.root && rm -rf dvcsgen1.dat lund2root_RC.C && cd -",dir.Data(), Folder.Data(), dir.Data()));

  gSystem->Exec(Form("cd %s%s && /work/clas12/jsalvg/RGA-Simulation/dvcsgen/dvcsgen --trig 1000000 --gpd 101 --nmax 1000000 --beam 10.6 --zpos -3.0 --zwidth 2.5 --radgen --writef 2 --radstable --y 0.01 0.97 --th 0.03 1 --ycol 0.0005 --weight --t %f %f --q2 %f %f --x %f %f --bh 1 >> /dev/null && cd -",dir.Data(), Folder.Data(),-1.0*boundaries.at(1),-1.0*boundaries.at(0),boundaries.at(2),boundaries.at(3),boundaries.at(4),boundaries.at(5)));
  gSystem->Exec(Form("cd %s%s && cp %s/include/xsec/lund2root_RC.C . && clas12root -l -b -q lund2root_RC.C && mv dvcsgen_test.root dvcsgen_BH_gen.root && rm -rf dvcsgen1.dat lund2root_RC.C && cd -",dir.Data(), Folder.Data(), dir.Data()));

  //Dataset for the nominal computation
  TChain *Data_Tree= new TChain("tree");
  Data_Tree->Add(Folder + TString("dvcsgen_DVCS_gen.root"));
  
  TH1F *xborn = new TH1F("xborn","",Nphi,0,360);
  TH1F *xrad  = new TH1F("xrad","",Nphi,0,360);
  TH1F *nevs = new TH1F("nevs","",Nphi,0,360);
  TH1F *nevs_born  = new TH1F("nevs_born","",Nphi,0,360);
  TH1F *nevs_rad  = new TH1F("nevs_rad","",Nphi,0,360);
  TH1F *ratio_rad = new TH1F("ratio_rad","F_rad",Nphi,0,360);

  xborn->Sumw2();
  xrad->Sumw2();
  nevs->Sumw2();
  nevs_born->Sumw2();
  nevs_rad->Sumw2();
  ratio_rad->Sumw2();

  //Dataset for the systematics
  TChain *Data_Tree_Sys= new TChain("tree");
  Data_Tree_Sys->Add(Folder + TString("dvcsgen_BH_gen.root"));

  TH1F *xborn_Sys = new TH1F("xborn_Sys","",Nphi,0,360);
  TH1F *xrad_Sys  = new TH1F("xrad_Sys","",Nphi,0,360);
  TH1F *nevs_Sys = new TH1F("nevs_Sys","",Nphi,0,360);
  TH1F *nevs_born_Sys  = new TH1F("nevs_born_Sys","",Nphi,0,360);
  TH1F *nevs_rad_Sys  = new TH1F("nevs_rad_Sys","",Nphi,0,360);
  TH1F *ratio_rad_Sys = new TH1F("ratio_rad_Sys","F_rad",Nphi,0,360);

  xborn_Sys->Sumw2();
  xrad_Sys->Sumw2();
  nevs_Sys->Sumw2();
  nevs_born_Sys->Sumw2();
  nevs_rad_Sys->Sumw2();
  ratio_rad_Sys->Sumw2();

  //Cut 
  TString String_cut = (cut_bin + cut_kin + cut_sel + cut_ref).GetTitle();
  String_cut.ReplaceAll("bestCandidateFlag==1 && ", "");
  String_cut.ReplaceAll("_strip_Nuc_BDT_SIDIS", "Q2_meas");
  String_cut.ReplaceAll("strip_Q2", "Q2_meas");
  String_cut.ReplaceAll("strip_Xbj", "xB_meas");
  String_cut.ReplaceAll("t_Ph", "t_meas");
  String_cut.ReplaceAll("strip_El_P", "El_E");
  String_cut.ReplaceAll("strip_Ph_P", "Ph_E");
  String_cut.ReplaceAll("strip_El_Theta", "El_Theta");
  String_cut.ReplaceAll("strip_Ph_Theta", "Ph_Theta");
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
