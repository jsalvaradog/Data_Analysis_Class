void BDT::Combine_2root(TString input, TCut TheCut, int bin_number, TString pre_path="")
{
  TFile *file_FT = TFile::Open(TString("FT/") + TString("bin_")+Form("%i/",bin_number) + input);
  TFile *file_FD = TFile::Open(TString("FD/") + TString("bin_")+Form("%i/",bin_number) + input);
  TTree *tree_FT = dynamic_cast<TTree*>(file_FT->Get("pDVCS"));
  TTree *tree_FD = dynamic_cast<TTree*>(file_FD->Get("pDVCS"));

  	
  std::cout<<input<<endl;
  if (tree_FT->GetEntries() == 0)
    {
      gSystem->Exec(TString("cp ") + TString("FT/") + TString("bin_")+Form("%i/",bin_number) + input + TString(" ") + Folder + TString("FT_") + input);
    }
  else
    {
      Filter(pre_path + TString("../../FT/") + TString("bin_")+Form("%i/",bin_number) + input, TheCut + TCut("_strip_Nuc_BDT > 0.04"), TString("FT_") + input);
    }
  if (tree_FD->GetEntries() == 0)
    {
      gSystem->Exec(TString("cp ") + TString("FD/") + TString("bin_")+Form("%i/",bin_number) + input + TString(" ") + Folder + TString("FD_") + input);
    }
  else
    {
      Filter(pre_path + TString("../../FD/") + TString("bin_")+Form("%i/",bin_number) + input, TheCut + TCut("_strip_Nuc_BDT > 0.0 "), TString("FD_") + input);
    }
  
  TChain *chain = new TChain("pDVCS");
  chain->Add(Folder + TString("FT_") + input);
  chain->Add(Folder + TString("FD_") + input);

  TFile *File = new TFile(Folder + input,"RECREATE");
  chain->CloneTree(-1,"fast");
  
  File->Write();

  gSystem->Exec(TString("rm ") + Folder + TString("FT_") + input);
  gSystem->Exec(TString("rm ") + Folder + TString("FD_") + input);

  delete chain;
  File->Close();
  delete File;

  file_FT->Close();
  file_FD->Close();
  delete file_FT;
  delete file_FD;

}


void BDT::Combine_FT_FD(int bin=0, TString pre_path="")
{
  TCut Mbins[64];  
  Mbins[0]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0    && strip_Xbj < 0.13");
  Mbins[1]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0.13 && strip_Xbj < 0.21");
  Mbins[2]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0.21 && strip_Xbj < 1.0 ");
  Mbins[3]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0    && strip_Xbj < 0.13");
  Mbins[4]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0.13 && strip_Xbj < 0.21");
  Mbins[5]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0.21 && strip_Xbj < 1.0 ");
  Mbins[6]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0    && strip_Xbj < 0.13");
  Mbins[7]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0.13 && strip_Xbj < 0.21");
  Mbins[8]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0.21 && strip_Xbj < 1.0 ");
  Mbins[9]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0    && strip_Xbj < 0.13");
  Mbins[10]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0.13 && strip_Xbj < 0.21");
  Mbins[11]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 1 && strip_Q2 < 1.4 && strip_Xbj > 0.21 && strip_Xbj < 1.0 ");

  Mbins[12]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0    && strip_Xbj < 0.13");
  Mbins[13]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0.13 && strip_Xbj < 0.21");
  Mbins[14]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0.21 && strip_Xbj < 1.0 ");
  Mbins[15]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0    && strip_Xbj < 0.13");
  Mbins[16]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0.13 && strip_Xbj < 0.21");
  Mbins[17]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0.21 && strip_Xbj < 1.0 ");
  Mbins[18]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0    && strip_Xbj < 0.13");
  Mbins[19]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0.13 && strip_Xbj < 0.21");
  Mbins[20]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0.21 && strip_Xbj < 1.0 ");
  Mbins[21]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0    && strip_Xbj < 0.13");
  Mbins[22]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0.13 && strip_Xbj < 0.21");
  Mbins[23]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 1.4 && strip_Q2 < 1.8 && strip_Xbj > 0.21 && strip_Xbj < 1.0 ");

  Mbins[24]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0    && strip_Xbj < 0.16");
  Mbins[25]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0.16 && strip_Xbj < 0.26");
  Mbins[26]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0.26 && strip_Xbj < 1.0 ");
  Mbins[27]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0    && strip_Xbj < 0.16");
  Mbins[28]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0.16 && strip_Xbj < 0.26");
  Mbins[29]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0.26 && strip_Xbj < 1.0 ");
  Mbins[30]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0    && strip_Xbj < 0.16");
  Mbins[31]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0.16 && strip_Xbj < 0.26");
  Mbins[32]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0.26 && strip_Xbj < 1.0 ");
  Mbins[33]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0    && strip_Xbj < 0.16");
  Mbins[34]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0.16 && strip_Xbj < 0.26");
  Mbins[35]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 1.8 && strip_Q2 < 2.4 && strip_Xbj > 0.26 && strip_Xbj < 1.0 ");

  Mbins[36]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0    && strip_Xbj < 0.21");
  Mbins[37]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0.21 && strip_Xbj < 0.33");
  Mbins[38]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0.33 && strip_Xbj < 1.0 ");
  Mbins[39]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0    && strip_Xbj < 0.21");
  Mbins[40]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0.21 && strip_Xbj < 0.33");
  Mbins[41]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0.33 && strip_Xbj < 1.0 ");
  Mbins[42]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0    && strip_Xbj < 0.21");
  Mbins[43]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0.21 && strip_Xbj < 0.33");
  Mbins[44]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0.33 && strip_Xbj < 1.0 ");
  Mbins[45]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0    && strip_Xbj < 0.21");
  Mbins[46]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0.21 && strip_Xbj < 0.33");
  Mbins[47]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 2.4 && strip_Q2 < 3.25 && strip_Xbj > 0.33 && strip_Xbj < 1.0 ");

  Mbins[48]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 3.25 && strip_Q2 < 5.0 && strip_Xbj > 0    && strip_Xbj < 0.33");
  Mbins[49]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 3.25 && strip_Q2 < 5.0 && strip_Xbj > 0.33 && strip_Xbj < 1.0 ");
  Mbins[50]= TCut("bestCandidateFlag==1 && t_Ph<0    && t_Ph>-0.2 && strip_Q2 > 3.25 && strip_Q2 < 5.0 && strip_Xbj > 0    && strip_Xbj < 0.33 ");
  Mbins[51]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 3.25 && strip_Q2 < 5.0 && strip_Xbj > 0.33 && strip_Xbj < 1.0  ");
  Mbins[52]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 3.25 && strip_Q2 < 5.0 && strip_Xbj > 0.   && strip_Xbj < 0.33");
  Mbins[53]= TCut("bestCandidateFlag==1 && t_Ph<-0.2 && t_Ph>-0.4 && strip_Q2 > 3.25 && strip_Q2 < 5.0 && strip_Xbj > 0.33 && strip_Xbj < 1.0 ");
  Mbins[54]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 3.25 && strip_Q2 < 5.0 && strip_Xbj > 0    && strip_Xbj < 0.33");
  Mbins[55]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 3.25 && strip_Q2 < 5.0 && strip_Xbj > 0.33 && strip_Xbj < 1.0 ");

  Mbins[56]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 5.0 && strip_Q2 < 15.0 && strip_Xbj > 0    && strip_Xbj < 0.55");
  Mbins[57]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 5.0 && strip_Q2 < 15.0 && strip_Xbj > 0.55 && strip_Xbj < 1.0 ");
  Mbins[58]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 5.0 && strip_Q2 < 15.0 && strip_Xbj > 0    && strip_Xbj < 0.55");
  Mbins[59]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 5.0 && strip_Q2 < 15.0 && strip_Xbj > 0.55 && strip_Xbj < 1.0 ");
  Mbins[60]= TCut("bestCandidateFlag==1 && t_Ph<-0.4 && t_Ph>-0.8 && strip_Q2 > 5.0 && strip_Q2 < 15.0 && strip_Xbj > 0    && strip_Xbj < 0.55");
  Mbins[61]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 5.0 && strip_Q2 < 15.0 && strip_Xbj > 0.55 && strip_Xbj < 1.0 ");
  Mbins[62]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 5.0 && strip_Q2 < 15.0 && strip_Xbj > 0    && strip_Xbj < 0.55");
  Mbins[63]= TCut("bestCandidateFlag==1 && t_Ph<-0.8 && t_Ph>-100 && strip_Q2 > 5.0 && strip_Q2 < 15.0 && strip_Xbj > 0.55 && strip_Xbj < 1.0 ");

  double bins[64][6] = {
			{-0.2, 0, 1, 1.4, 0, 0.13},
			{-0.2, 0, 1, 1.4, 0.13, 0.21},
			{-0.2, 0, 1, 1.4, 0.21, 1},
			{-0.4, -0.2, 1, 1.4, 0, 0.13},
			{-0.4, -0.2, 1, 1.4, 0.13, 0.21},
			{-0.4, -0.2, 1, 1.4, 0.21, 1},
			{-0.8, -0.4, 1, 1.4, 0, 0.13},
			{-0.8, -0.4, 1, 1.4, 0.13, 0.21},
			{-0.8, -0.4, 1, 1.4, 0.21, 1},
			{-100, -0.8, 1, 1.4, 0, 0.13},
			{-100, -0.8, 1, 1.4, 0.13, 0.21},
			{-100, -0.8, 1, 1.4, 0.21, 1},

			{-0.2, 0, 1.4, 1.8, 0, 0.13},
			{-0.2, 0, 1.4, 1.8, 0.13, 0.21},
			{-0.2, 0, 1.4, 1.8, 0.21, 1},
			{-0.4, -0.2, 1.4, 1.8, 0, 0.13},
			{-0.4, -0.2, 1.4, 1.8, 0.13, 0.21},
			{-0.4, -0.2, 1.4, 1.8, 0.21, 1},
			{-0.8, -0.4, 1.4, 1.8, 0, 0.13},
			{-0.8, -0.4, 1.4, 1.8, 0.13, 0.21},
			{-0.8, -0.4, 1.4, 1.8, 0.21, 1},
			{-100, -0.8, 1.4, 1.8, 0, 0.13},
			{-100, -0.8, 1.4, 1.8, 0.13, 0.21},
			{-100, -0.8, 1.4, 1.8, 0.21, 1},

			{-0.2, 0, 1.8, 2.4, 0, 0.16},
			{-0.2, 0, 1.8, 2.4, 0.16, 0.26},
			{-0.2, 0, 1.8, 2.4, 0.26, 1},
			{-0.4, -0.2, 1.8, 2.4, 0, 0.16},
			{-0.4, -0.2, 1.8, 2.4, 0.16, 0.26},
			{-0.4, -0.2, 1.8, 2.4, 0.26, 1},
			{-0.8, -0.4, 1.8, 2.4, 0, 0.16},
			{-0.8, -0.4, 1.8, 2.4, 0.16, 0.26},
			{-0.8, -0.4, 1.8, 2.4, 0.26, 1},
			{-100, -0.8, 1.8, 2.4, 0, 0.16},
			{-100, -0.8, 1.8, 2.4, 0.16, 0.26},
			{-100, -0.8, 1.8, 2.4, 0.26, 1},

			{-0.2, 0, 2.4, 3.25, 0, 0.21},
			{-0.2, 0, 2.4, 3.25, 0.21, 0.33},
			{-0.2, 0, 2.4, 3.25, 0.33, 1},
			{-0.4, -0.2, 2.4, 3.25, 0, 0.21},
			{-0.4, -0.2, 2.4, 3.25, 0.21, 0.33},
			{-0.4, -0.2, 2.4, 3.25, 0.33, 1},
			{-0.8, -0.4, 2.4, 3.25, 0, 0.21},
			{-0.8, -0.4, 2.4, 3.25, 0.21, 0.33},
			{-0.8, -0.4, 2.4, 3.25, 0.33, 1},
			{-100, -0.8, 2.4, 3.25, 0, 0.21},
			{-100, -0.8, 2.4, 3.25, 0.21, 0.33},
			{-100, -0.8, 2.4, 3.25, 0.33, 1},

			{-0.2, 0, 3.25, 5, 0, 0.33},
			{-0.2, 0, 3.25, 5, 0.33, 1},
			{-0.2, 0, 3.25, 5, 0, 0.33},
			{-0.4, -0.2, 3.25, 5, 0.33, 1},
			{-0.4, -0.2, 3.25, 5, 0, 0.33},
			{-0.4, -0.2, 3.25, 5, 0.33, 1},
			{-0.8, -0.4, 3.25, 5, 0, 0.33},
			{-0.8, -0.4, 3.25, 5, 0.33, 1},
			{-0.8, -0.4, 5, 15, 0, 0.55},
			{-100, -0.8, 5, 15, 0.55, 1},
			{-100, -0.8, 5, 15, 0, 0.55},
			{-100, -0.8, 5, 15, 0.55, 1},
			{-0.8, -0.4, 5, 15, 0, 0.55},
			{-100, -0.8, 5, 15, 0.55, 1},
			{-100, -0.8, 5, 15, 0, 0.55},
			{-100, -0.8, 5, 15, 0.55, 1}
  };

  int Nphibins[64] = {
		      29,
		      22,
		      18,
		      30,
		      23,
		      13,
		      27,
		      26,
		      9,
		      14,
		      12,
		      12,
		      23,
		      24,
		      21,
		      24,
		      23,
		      15,
		      17,
		      22,
		      11,
		      18,
		      14,
		      23,
		      24,
		      25,
		      23,
		      24,
		      28,
		      15,
		      19,
		      27,
		      12,
		      27,
		      17,
		      10,
		      21,
		      21,
		      18,
		      23,
		      25,
		      15,
		      19,
		      22,
		      12,
		      13,
		      16,
		      10,
		      19,
		      19,
		      23,
		      18,
		      21,
		      17,
		      15,
		      13,
		      12,
		      12,
		      13,
		      12,
		      13,
		      12,
		      13,
		      18};

  std::vector<double> xValues;
  std::vector<double> yValues;
  std::vector<double> yErrors;
  std::vector<double> xErrors;
  std::vector<double> phi_bins;

  double x, y, yErr;
  double binWidth;
  double xErr;
  int numPoints;

  std::ifstream inputFile;
  std::string line;


  int bin_number=1;
  TString Folder_old=Folder;


  int k0=0, kN=64;
  if(bin!=0)
    {
      bin_number=bin;
      k0=bin-1;
      kN=bin;      
    }
    

  for(int k=k0;k<kN;k++)
    {
      std::cout<<bin_number<<endl;
      if(bin_number==3)
      //if(bin_number==2 || bin_number==3 || bin_number==6 || bin_number==15 || bin_number==18 || bin_number==27 || bin_number==30 || bin_number==33 || bin_number==39 || bin_number==42 || bin_number==45 || bin_number==48 || bin_number==50 || bin_number==52 || bin_number==54 || bin_number==58 || bin_number==60 || bin_number==62 || bin_number==64)
	{
	  bin_number++;
	  continue;
	}
      TH1 *Orig;
      TH1 *Pcase;
      TH1 *Most;
      TH1 *Maxi;

      TCut cut_bin = Mbins[k];
      std::cout<<Form("\n\n t_Ph>%f && t_Ph<%f && strip_Q2>%f && strip_Q2<%f && strip_Xbj>%f && strip_Xbj<%f",bins[k][0],bins[k][1],bins[k][2],bins[k][3],bins[k][4],bins[k][5])<<endl;
      boundaries.clear();
      boundaries.push_back(bins[k][0]);
      boundaries.push_back(bins[k][1]);
      boundaries.push_back(bins[k][2]);
      boundaries.push_back(bins[k][3]);
      boundaries.push_back(bins[k][4]);
      boundaries.push_back(bins[k][5]);
      Folder = Folder_old + TString("bin_")+Form("%i/",bin_number);
      gSystem->Exec(TString("mkdir -p ") + Folder);

      //Combine:
      Combine_2root("Data_NP_Theta_g_5.root", cut + cut_bin, bin_number,pre_path);
      Combine_2root("TMostafa_pi0.root", cut + cut_bin, bin_number,pre_path);
      Combine_2root("TMaxime_pi0.root", cut + cut_bin, bin_number,pre_path);
      Combine_2root(l.TData, cut + cut_bin, bin_number,pre_path);

      //TMaxime_pi0.root
      boundaries.push_back(1);
      boundaries.push_back(1);
      	      
      std::cout<<"\n Apply Mostafa way"<<endl;
      Most=Get_Contamination_Mostafa(cut + cut_bin, BDT_value,Nphibins[k]);
      //boundaries.push_back(1);
      //boundaries.push_back(1);

      std::cout<<"\n Get Contamination Maxime way"<<endl;
      Maxi=Maxime(cut + cut_bin, BDT_value, bin_number,Nphibins[k]);
	      
      Orig=Single_BSA("Data_NP_Theta_g_5.root",Nphibins[k]);

      gStyle->SetOptFit(0);
      gStyle->SetOptTitle(0);
      Orig->SetAxisRange(-1., 1.,"Y");
      Orig->SetMarkerColor(kBlack);
      Orig->SetLineColor(kBlack);
      Most->SetAxisRange(-1., 1.,"Y");
      Most->SetMarkerColor(kBlue);
      Most->SetLineColor(kBlue);
      Most->GetFunction("fitf")->SetLineColor(kBlue);
      Maxi->SetAxisRange(-1., 1.,"Y");
      Maxi->SetMarkerColor(kRed);
      Maxi->SetLineColor(kRed);
      Maxi->GetFunction("fitf")->SetLineColor(kRed);

      Most->SetTitle("Method 1");
      Maxi->SetTitle("Method 2");

	      
      Orig->SetTitle("Before");
      TCanvas* c3 = new TCanvas("c3","Histograms");
      Orig->Draw();
      Most->Draw("SAME");
      Maxi->Draw("SAME");
      c3->BuildLegend();
      c3->Print(Folder + TString("Background_subtraction.pdf"));
      delete c3;
      gStyle->SetOptTitle(1);

      
      TCanvas* c4 = new TCanvas("c4","Histograms");
      //Plot Maxime BSA
      inputFile.open(Form("/work/clas12/jsalvg/Maxime/P/Maxime_BSA/bin_%i.txt",bin_number)); // Replace with the name of the block file you want to read
      xValues.clear();
      yValues.clear();
      xErrors.clear();
      yErrors.clear();
      while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        iss >> x >> y >> yErr;
	x=x*180/TMath::Pi();
        xErr = (360./Nphibins[k]) / 2.0;
        
        xValues.push_back(x);
        yValues.push_back(y);
        yErrors.push_back(yErr);
        xErrors.push_back(xErr);
      }
      numPoints = xValues.size();

      inputFile.close();
      TGraphErrors* graph = new TGraphErrors(numPoints, xValues.data(), yValues.data(), xErrors.data(), yErrors.data());
      graph->SetTitle("RG-A Reported");
      graph->SetMarkerColor(kBlack);
      graph->SetLineColor(kBlack);
      graph->SetMinimum(-1.);
      graph->SetMaximum(1.);
 

      Most->Draw("E0");
      Maxi->Draw("SAME, E0");
      graph->Draw("SAME P");

      c4->BuildLegend();
      c4->Print(Folder + TString("RGA_vs_This.pdf"));
      delete c4;

      
      //Compare_three(cut + cut_bin, "TMaxime_pi0.root", "TMostafa_pi0.root");
	      	      

      TCanvas* c5 = new TCanvas("c5","Histograms");
      gStyle->SetOptFit(0);
      gStyle->SetOptTitle(0);
      TFile *inputFile = TFile::Open(TString("../P/Maxime_Analysis/") +  TString("bin_")+Form("%i/",bin_number)+  TString("Mostafa_Clean.root"));
      Pcase=dynamic_cast<TH1F*>(inputFile->Get("Asymmetry_Data_m_BDT-Data_p_BDT"));

      Pcase->SetMinimum(-1.);
      Pcase->SetMaximum(1.);

      Pcase->SetLineColor(kRed);
      Pcase->SetMarkerColor(kRed);
      Pcase->GetFunction("fitf")->SetLineColor(kRed);
      Pcase->SetTitle("With proton");
      Most->SetTitle("Without proton");
      
      //Maxi->SetTitle("Without proton");

      Pcase->Draw();
      Most->Draw("SAME");
      graph->Draw("SAME P");
      c5->BuildLegend();
      c5->Print(Folder + TString("RGA_vs_P_vs_NP_most.pdf"));
      delete c5;
      
      
      




      TChain *chain_MC = new TChain("pDVCS");
      chain_MC->Add("../P/Maxime_Analysis/Data_NP_Theta_g_5.root");

      TH1F *mm2_P = new TH1F("mm2_P","With proton",100,0.0,5.0);
      chain_MC->Project("mm2_P", "mm2_eg", cut + cut_bin);
	      
      TH1F *mm2_Most = Apply_Contamination_Mostafa_mm2(cut + cut_bin);
      TH1F *mm2_Maxi = Apply_Contamination_Maxime_mm2(cut + cut_bin);

      TCanvas* c6 = new TCanvas("c6","Histograms");
      mm2_P->SetLineColor(kBlack);
      mm2_Most->SetLineColor(kBlue);
      mm2_Maxi->SetLineColor(kRed);
	      
      mm2_Most->SetTitle("Method 1");
      mm2_Maxi->SetTitle("Method 2");

      mm2_P->Scale(1.0/mm2_P->Integral());
      mm2_Most->Scale(1.0/mm2_Most->Integral());
      mm2_Maxi->Scale(1.0/mm2_Maxi->Integral());
	      
      mm2_P->Draw("HIST");
      mm2_Most->Draw("HIST,SAME");
      mm2_Maxi->Draw("HIST,SAME");

      c6->BuildLegend();
      c6->Print(Folder + TString("mm2_eg.pdf"));
      delete c6;

      std::cout<<"SUMMARY:"<<endl;	      

      std::ofstream outFile(Folder + TString("Amplitudes.txt"));
      outFile<<"type value fit error on fit"<<endl;	      
      outFile<<"Raw "<<BSA_Amplitude<<" "<<BSA_Amplitude_fit<<" "<<BSA_Error_fit<<endl;	      
      outFile<<"Mostafa "<<BSA_Amplitude_most<<" "<<BSA_Amplitude_most_fit<<" "<<BSA_Error_most_fit<<endl;	      
      outFile<<"Maxime "<<BSA_Amplitude_maxi<<" "<<BSA_Amplitude_maxi_fit<<" "<<BSA_Error_maxi_fit<<endl;	      

      std::cout<<"type value fit"<<endl;	      
      cout<<"Raw "<<BSA_Amplitude<<" "<<BSA_Amplitude_fit<<" "<<BSA_Error_fit<<endl;	      
      cout<<"Mostafa "<<BSA_Amplitude_most<<" "<<BSA_Amplitude_most_fit<<" "<<BSA_Error_most_fit<<endl;	      
      cout<<"Maxime "<<BSA_Amplitude_maxi<<" "<<BSA_Amplitude_maxi_fit<<" "<<BSA_Error_maxi_fit<<endl;	      

      outFile<<"Entries before BDT: "<<entries_bef_BDT<<endl;
      outFile<<"Mostafa entries/estimation on bin "<<bin_number<< " before/after: "<<entries_bef_most<<" "<<entries_aft_most<<" "<<boundaries.at(8)*100<<"% "<<boundaries.at(9)*100<<"% "<<endl;  
      outFile<<"Maxime  entries/estimation on bin "<<bin_number<< " before/after: "<<entries_bef_maxi<<" "<<entries_aft_maxi<<" "<<boundaries.at(10)*100<<"% "<<boundaries.at(11)*100<<"% "<<endl;  
      std::cout<<"Entries before BDT: "<<entries_bef_BDT<<endl;
      std::cout<<"Mostafa entries/estimation on bin "<<bin_number<< " before/after: "<<entries_bef_most<<" "<<entries_aft_most<<" "<<boundaries.at(8)*100<<"% "<<boundaries.at(9)*100<<"% "<<endl;  
      std::cout<<"Maxime  entries/estimation on bin "<<bin_number<< " before/after: "<<entries_bef_maxi<<" "<<entries_aft_maxi<<" "<<boundaries.at(10)*100<<"% "<<boundaries.at(11)*100<<"% "<<endl;  
      bin_number+=1;

      outFile.close();


      delete Orig;
      delete Pcase;
      delete Most;
      delete Maxi;

      delete mm2_P;
      delete mm2_Most;
      delete mm2_Maxi;

      bin_number+=1;	      
    }

  Folder = Folder_old;

  return;
}
