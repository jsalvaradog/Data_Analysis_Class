$HistoryLength = 0

Needs["CUDALink`"];
CUDADriverVersion[];
Lala = Import["Data.csv", "Data"];
Lala2 = Flatten[Lala];
LalaO = CUDASort[Lala2];
Export["Data1.csv", LalaO, "CSV"]

Clear[]
Quit
