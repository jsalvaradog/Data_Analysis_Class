void effective_eta()
{
    TChain* chainData = new TChain("epeta");
    chainData->Add("/work/clas12/jsalvg/Data/eta/pass2_RGA/inb/Quality_Data_epeta_NP.root");

    TCut Mbins[94];
    Mbins[0]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[1]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[2]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[3]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[4]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[5]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[6]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");

Mbins[7]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[8]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[9]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[10]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[11]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[12]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[13]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");

Mbins[14]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[15]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[16]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[17]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[18]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[19]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[20]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");

Mbins[21]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[22]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[23]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[24]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[25]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.000000 && strip_Q2<1.600000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[26]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[27]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[28]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[29]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[30]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[31]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");
Mbins[32]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.0512   && strip_Xbj<0.120000");

Mbins[33]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[34]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[35]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[36]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[37]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[38]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[39]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");

Mbins[40]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[41]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[42]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[43]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[44]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[45]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[46]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");

Mbins[47]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[48]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[49]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[50]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[51]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>1.600000 && strip_Q2<2.400000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[52]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[53]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[54]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[55]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[56]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[57]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");
Mbins[58]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.120000   && strip_Xbj<0.170000");

Mbins[59]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[60]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[61]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[62]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[63]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[64]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[65]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");

Mbins[66]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[67]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[68]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[69]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[70]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[71]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.450000   && strip_Xbj<0.6");
Mbins[72]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>2.400000 && strip_Q2<3.250000 && strip_Xbj>0.450000   && strip_Xbj<0.6");

Mbins[73]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[74]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[75]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[76]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[77]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[78]= TCut("bestCandidateFlag==1 && t_Ph>-0.070000 && t_Ph<-0.040000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");
Mbins[79]= TCut("bestCandidateFlag==1 && t_Ph>-0.040000 && t_Ph<0.000000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.170000   && strip_Xbj<0.270000");

Mbins[80]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[81]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[82]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[83]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[84]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[85]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.450000   && strip_Xbj<0.6");
Mbins[86]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>3.250000 && strip_Q2<5.000000 && strip_Xbj>0.450000   && strip_Xbj<0.6");

Mbins[87]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[88]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[89]= TCut("bestCandidateFlag==1 && t_Ph>-0.250000 && t_Ph<-0.170000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[90]= TCut("bestCandidateFlag==1 && t_Ph>-0.170000 && t_Ph<-0.120000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");
Mbins[91]= TCut("bestCandidateFlag==1 && t_Ph>-0.120000 && t_Ph<-0.070000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.270000   && strip_Xbj<0.450000");

Mbins[92]= TCut("bestCandidateFlag==1 && t_Ph>-1.000000 && t_Ph<-0.400000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.450000   && strip_Xbj<0.6");
Mbins[93]= TCut("bestCandidateFlag==1 && t_Ph>-0.400000 && t_Ph<-0.250000 && strip_Q2>5.000000 && strip_Q2<9.0000000 && strip_Xbj>0.450000   && strip_Xbj<0.6");

TCut cut2g;
gStyle->SetOptStat(0);
std::ofstream outfile("eta/fractions.dat", std::ios::app);
for(int i=1; i<=94; i++)
{
  TCanvas *c1 = new TCanvas("c1", "Fit", 800, 600);

  //Convert cut to string
  TString String_cut = Mbins[i-1].GetTitle();

  //replace Ph by eta
  String_cut.ReplaceAll("t_Ph", "t_eta");	  
  String_cut.ReplaceAll("strip_Ph_P", "strip_eta_P");
  String_cut.ReplaceAll("mm2_eg", "strip_Xbj");
  String_cut.ReplaceAll("gamma", "eta");
  String_cut.ReplaceAll("_strip_Nuc_BDT_SIDIS", "strip_El_P");

  //Create cut for 2gamma case
  cut2g = TCut(String_cut) + TCut("strip_eta_2DChi2 < 0.04 && abs(mm2_eNgg)<0.01") + TCut("mm2_egg<1.5");

  TH1F* h1 = new TH1F("h1","Missing proton mass", 100, 0.2, 0.4);
  h1->SetMinimum(0);
  h1->SetXTitle("M_{#gamma #gamma}[GeV^{2}]");
  chainData->Project("h1", "strip_eta_IM2", cut2g);

  if(h1->GetEntries()<100) {
      outfile << i << " " << 0.0 << std::endl;
      delete c1;
      delete h1;
      continue;
  }
  
  TF1 *fitFunc = new TF1("fitFunc", "[0]*exp(-0.5*((x-[1])/[2])^2) + [3]*exp([4]*x)", h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
  fitFunc->SetParLimits(0, 0, 1e10); // Parameter 0 >= 0
  fitFunc->SetParLimits(3, 0, 1e10); // Parameter 3 >= 0
  fitFunc->SetParameters(h1->GetMaximum(), h1->GetMean(), h1->GetRMS()/2, h1->GetMaximum()/10, -1);
  //fitFunc->FixParameter(1, 0.938*0.938); // Proton mass
  fitFunc->SetLineColor(kBlack);
  fitFunc->SetLineStyle(kDashed);
  h1->Fit(fitFunc, "RQ");

  h1->Draw();
  fitFunc->Draw("same");

  // Draw Gaussian component
  TF1* gaussComp = new TF1("gaussComp", "[0]*exp(-0.5*((x-[1])/[2])^2)", h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
  gaussComp->SetParameters(fitFunc->GetParameter(0), fitFunc->GetParameter(1), fitFunc->GetParameter(2));
  gaussComp->SetLineColor(kBlue);
  gaussComp->Draw("same");

  // Draw exponential component
  TF1* expoComp = new TF1("expoComp", "[0]*exp([1]*x)", h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
  expoComp->SetParameters(fitFunc->GetParameter(3), fitFunc->GetParameter(4));
  expoComp->SetLineColor(kRed);
  expoComp->Draw("same");

  double totalEvents = h1->Integral();
  double gaussAmp = fitFunc->GetParameter(0);
  double gaussMean = fitFunc->GetParameter(1);
  double gaussSigma = fitFunc->GetParameter(2);

  // Integrate the Gaussian over the histogram range
  TF1* gaussInt = new TF1("gaussInt", "[0]*exp(-0.5*((x-[1])/[2])^2)", h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax());
  gaussInt->SetParameters(gaussAmp, gaussMean, gaussSigma);
  double etaEvents = gaussInt->Integral(h1->GetXaxis()->GetXmin(), h1->GetXaxis()->GetXmax()) / h1->GetBinWidth(1);

  double fracEta = (totalEvents > 0) ? etaEvents / totalEvents : 0;

  std::cout << "Bin " << i << ": Estimated eta events (Gaussian) = " << etaEvents
        << ", Total events = " << totalEvents
        << ", Fraction = " << fracEta << std::endl;

  delete gaussInt;

  TString outname;
  outname.Form("eta/bin_%i.pdf", i);
  c1->SaveAs(outname);

    outfile << i << " " << fracEta << std::endl;

  delete fitFunc;
  delete c1;
  delete h1;
  delete gaussComp;
  delete expoComp;  
}
    outfile.close();

}