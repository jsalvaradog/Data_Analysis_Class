TH1F* BDT::No_Rec_correction(TString Data, TString MCData, double BDT_cut, int Nphi, TH1F*& Systematics){

// Check if xsec_dists.root exists and read F_bin1 if available
TH1F* ratio;
TFile *f = TFile::Open(Folder + TString("xsec_dists.root"), "READ"); 
if (f && !f->IsZombie() && false) 
{
 std::cout<<"NoRec found on File"<<endl;
 ratio = dynamic_cast<TH1F*>(f->Get("F_noRec"));
 std::cout<<"\nAcc correction"<<endl; 
 for(int k=1; k<=Nphi; k++)
 {
   std::cout<<ratio->GetBinContent(k)<<" "<<ratio->GetBinError(k)<<std::endl;
 }
}
else
{
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);

  TString String_cut = cut_bin.GetTitle();
  String_cut.ReplaceAll("strip_Q2", "strip_Q2_MC");
  String_cut.ReplaceAll("strip_Xbj", "strip_Xbj_MC");
  String_cut.ReplaceAll("t_Ph", "t_Ph_MC");
  TCut cut_bin_gen = TCut(String_cut);

  TChain *Data_Tree= new TChain("pDVCS");
  Data_Tree->Add(Data);

  TChain *Data_bkg= new TChain("pDVCS");
  Data_bkg->Add(Folder + TString("../TMaxime_pi0.root"));

  TChain *MCData_Tree= new TChain("pDVCS");
  MCData_Tree->Add(MCData);

  TH1F *Phi_rec = new TH1F("Phi_rec","",Nphi,0,360);
  TH1F *Phi_rec_bkg = new TH1F("Phi_rec_bkg","",Nphi,0,360);
  TH1F *Phi_rec_Sys = new TH1F("Phi_rec_Sys","",Nphi,0,360);
  TH1F *Phi_mc = new TH1F("Phi_mc","",Nphi,0,360);
  ratio = new TH1F("ratio","F_noRec",Nphi,0,360);
  TH1F* ratio_Sys = new TH1F("ratio_Sys","F_noRec",Nphi,0,360);

  //BM procedure undo BDT and cut_ref cuts while also transports all events to the generated bin.
  Data_Tree->Project("Phi_rec", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * TCut("rWeight")); //Without BM
  Data_Tree->Project("Phi_rec_Sys", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value))) * TCut("rWeight0")); //Without BM

  //MC was simulated to data after BDT i.e. with leftover background. So I need to remove it
  Data_bkg->Project("Phi_rec_bkg", "Phi_Ph", (cut + cut_bin + cut_kin + cut_sel + cut_ref + TCut(Form("_strip_Nuc_BDT>%f", BDT_value)))*TCut("Weight")); //Without BM
  double MC_Entries = Phi_rec->Integral();
  Phi_rec_bkg->Scale(MC_Entries/boundaries.back()); //bkg is normalized to the experimental data. Boundaries.back() is the total number of data events 
  Phi_rec->Add(Phi_rec, Phi_rec_bkg, 1, -1);
  Phi_rec_Sys->Add(Phi_rec_Sys, Phi_rec_bkg, 1, -1);
  //Phi_rec->Scale(MC_Entries/Phi_rec->Integral());
  //Phi_rec_Sys->Scale(MC_Entries/Phi_rec_Sys->Integral());

  //To include BM I need to remove BDT and ref cut. Also bin becomes bin_gen
  //Data_Tree  ->Project("Phi_rec", "Phi_Ph", (cut + cut_bin_gen + cut_kin + cut_sel)*TCut("rWeight")); //With BM
  //Data_Tree  ->Project("Phi_rec_Sys", "Phi_Ph", (cut + cut_bin_gen + cut_kin + cut_sel)*TCut("rWeight0")); //With BM

  MCData_Tree->Project("Phi_mc" , "Phi_Nuc", cut + cut_bin + cut_kin + cut_sel); //Phi_Nuc is the generated Phi in the bin

  //Systematic error on the accceptance correction comes from the resolution matching
  ratio->Divide(Phi_rec, Phi_mc,1.0,1.0);
  ratio_Sys->Divide(Phi_rec_Sys, Phi_mc,1.0,1.0);

  double Sys = 0.;
  std::cout<<"\nAcc correction"<<endl;
  for(int k=1; k<=Nphi; k++)
  {
    //std::cout<<Phi_rec->GetBinContent(k)<<" "<<Phi_mc->GetBinContent(k)<<" "<<ratio->GetBinContent(k)<<std::endl;
    if(ratio->GetBinContent(k)==0)
      ratio->SetBinError(k,0);
    else
    {
      ratio->SetBinError(k,ratio->GetBinContent(k)*sqrt(1.0/Phi_rec->GetBinContent(k) + 1.0/Phi_mc->GetBinContent(k)));
      Sys = (ratio->GetBinContent(k)-ratio_Sys->GetBinContent(k))/ratio->GetBinContent(k);
      Systematics->SetBinError( k, Systematics->GetBinError(k) + pow(Sys,2) );
    }
      std::cout<<" "<<ratio->GetBinContent(k)<<" "<<ratio->GetBinError(k)<<" "<<Sys*100<<"%"<<std::endl;
  }
  
  //DVCS TESTING
  //std::cout<<"\nDVCS testing: Expected events after BM"<<endl;
  //for(int k=1; k<=Nphi; k++)
  //{
  //  std::cout<<Phi_rec->GetBinContent(k)<<endl;
  //}

  delete Phi_rec;
  delete Phi_rec_Sys;
  delete ratio_Sys;
  delete Phi_mc;
  delete Data_Tree;
  delete MCData_Tree;
}
  return ratio;
}
