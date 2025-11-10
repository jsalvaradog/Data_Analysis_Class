SetDirectory[NotebookDirectory[]];

Matrixp = Import["BM_Matrix_p.csv", "Data"];
Matrixp=Drop[Matrixp, None, {65}];
Matrixm = Import["BM_Matrix_m.csv", "Data"];
Matrixm=Drop[Matrixm, None, {65}];

InvMp=Inverse[Matrixp];
InvMm=Inverse[Matrixm];

vecIpMost = Import["entries_most_p.csv", "Data"];
vecImMost = Import["entries_most_m.csv", "Data"];
vecIpMaxi = Import["entries_maxi_p.csv", "Data"];
vecImMaxi = Import["entries_maxi_m.csv", "Data"];

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

