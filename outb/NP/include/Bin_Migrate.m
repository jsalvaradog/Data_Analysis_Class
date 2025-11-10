Matrixp = Import["BM_Matrix_p.csv", "Data"];
Matrixm = Import["BM_Matrix_m.csv", "Data"];

InvMp=Transpose[Inverse[Matrixp]];
InvMm=Transpose[Inverse[Matrixm]];

vecIpMost = Flatten[Import["entries_most_p.csv", "Data"]];
vecImMost = Flatten[Import["entries_most_m.csv", "Data"]];
vecIpMaxi = Flatten[Import["entries_maxi_p.csv", "Data"]];
vecImMaxi = Flatten[Import["entries_maxi_m.csv", "Data"]];

vecOpMost=InvMp . vecIpMost;
vecOmMost=InvMm . vecImMost;
vecOpMaxi=InvMp . vecIpMaxi;
vecOmMaxi=InvMm . vecImMaxi;

Export["entries_most_p_mig.csv", vecOpMost]
Export["entries_most_m_mig.csv", vecOmMost]
Export["entries_maxi_p_mig.csv", vecOpMaxi]
Export["entries_maxi_m_mig.csv", vecOmMaxi]
Clear[]


Quit

