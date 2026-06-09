#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

// Event-level variables
float xB, Q2, t, xsec_rad;

// Particle-level variables
float El_Px, El_Py, El_Pz, El_E, El_Theta;
float Ph_Px, Ph_Py, Ph_Pz, Ph_E, Ph_Theta;
float Nuc_Px, Nuc_Py, Nuc_Pz, Nuc_E, Nuc_Theta;
float theta_gamma_e;

// Renamed and updated branches
float phi;
float E_true, xsec_born;

// vectors
TVector3 k_vec, kp_vec, p_vec, pp_vec, ph_vec;
TLorentzVector p, pp, k, kp, ph;

void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
  }
  
void createTTreeFromLund(TString inputFileName, TTree*& tree) {
    int flag;

    std::ifstream infile(inputFileName);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << inputFileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int numParticles;
        float dummy;
        flag=0;
        
        // Read event header information
        if (!(iss >> numParticles >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy >> xsec_rad)) {
            std::cerr << "Error reading event header. Posible NaN or infinity in xsec_rad." << std::endl;
            std::cout<<line<<endl;
            iss >> numParticles;
            for(int k=0; k<numParticles;k++)
            {
                std::getline(infile, line);
                std::cout<<line<<endl;    
            }
            //flag=1;
            continue;
        }
        // Read particle information
        for (int i=0; i < numParticles; i++) {
            if(flag==1)
            {
                std::getline(infile, line);
            }
            std::getline(infile, line);
            std::istringstream partStream(line);

            int index, pid;
            float px, py, pz;
            float x2, x10, x11;
            float vx, vy, vz;

            if (!(partStream >> index >> x2 >> dummy >> pid >> dummy >> dummy
                           >> px >> py >> pz >> x10 >> x11
                           >> vx >> vy >> vz)) {
                std::cerr << "Error reading particle data." << std::endl;
                std::cout<<line<<endl;
                continue;
            }
            if (pid == 11) {  // Electron
                El_Px = px; El_Py = py; El_Pz = pz; El_E = sqrt(px*px + py*py + pz*pz + 0.000511*0.000511);
                El_Theta = acos(El_Pz/El_E)*180/TMath::Pi();                
            } 
            else if (pid == 22 && i==2) {  // Photon
                Ph_Px = px; Ph_Py = py; Ph_Pz = pz; Ph_E = sqrt(px*px + py*py + pz*pz);
                Ph_Theta = acos(Ph_Pz/Ph_E)*180/TMath::Pi();
            } 
            else if (pid == 2212) {  // Nucleon
                Nuc_Px = px; Nuc_Py = py; Nuc_Pz = pz; Nuc_E = sqrt(px*px + py*py + pz*pz + 0.938*0.938);
                double Nuc_P = sqrt(px*px + py*py + pz*pz);
                Nuc_Theta = acos(Nuc_Pz/Nuc_P)*180/TMath::Pi();                
            }
        }
        
        if(flag==1)
            continue;

        kp_vec.SetXYZ(El_Px, El_Py, El_Pz);
        pp_vec.SetXYZ(Nuc_Px, Nuc_Py, Nuc_Pz);
        ph_vec.SetXYZ(Ph_Px, Ph_Py, Ph_Pz);

        kp.SetXYZM(El_Px, El_Py, El_Pz,0.511e-3);
        pp.SetXYZM(Nuc_Px, Nuc_Py, Nuc_Pz,0.938);
        ph.SetXYZM(Ph_Px, Ph_Py, Ph_Pz,0);

	Q2=-1.0*(k-kp).M2();
	xB=Q2/(2.*0.938*(k.E() - kp.E()));
        t=(p-pp).M2();
        theta_gamma_e = kp_vec.Angle(ph_vec)*180/TMath::Pi();

        TVector3 leptoP=k_vec.Cross(kp_vec);
	    TVector3 hadroP=(k_vec - kp_vec).Cross(ph_vec);

	    phi = 180. / TMath::Pi() * leptoP.Angle(hadroP);
	    
	    if (leptoP.Dot(ph_vec) < 0.)
	      phi = 360. - phi;

	//For BH integration
	double ElP = 1.0; //(torus==-1) ? 2.0 : 1.0;
	double PhP = 10; //(torus== 1) ? 8.5 : 8.2;
	bool det_angles = (ph.Theta()*180./TMath::Pi()<2) || (ph.Theta()*180./TMath::Pi()>40) || (kp.Theta()*180./TMath::Pi()<5) || (kp.Theta()*180./TMath::Pi()>40);
	bool det_mom = (kp.P()<ElP) || (ph.P()<2) ;
	bool kin_cuts = (t<-1.) || (-1.0*t/Q2>1) || (kp_vec.Angle(ph_vec)*180./TMath::Pi()<5);
	if(det_angles || det_mom || kin_cuts)
		continue;

	xsec_born=xsec_rad;
	tree->Fill();
    }

}




int lund2root_LP() {
    TString inputFileName;    
    TString outputFileName; 
    TString tor; 
    TString model;
        	  
    inputFileName = TString("dvcsgen1.dat");
    outputFileName = TString("dvcsgen_test.root");
    
    k_vec.SetXYZ(0,0,10.6);
    p_vec.SetXYZ(0,0,0);

    k.SetXYZM(0,0,10.6,0.511e-3);
    p.SetXYZM(0,0,0,0.938);

    
    // Create a ROOT file and a TTree
    TFile* outFile = new TFile(outputFileName, "RECREATE");
    TTree* tree = new TTree("tree", "DVCS Events from LUND File");

    // Create branches in the TTree
    tree->Branch("xB", &xB);
    tree->Branch("Q2", &Q2);
    tree->Branch("t", &t);
    tree->Branch("phi", &phi);
    tree->Branch("xsec_rad", &xsec_rad);
    tree->Branch("xsec_born", &xsec_born);
    tree->Branch("theta_gamma_e", &theta_gamma_e);

    tree->Branch("El_Px", &El_Px);
    tree->Branch("El_Py", &El_Py);
    tree->Branch("El_Pz", &El_Pz);
    tree->Branch("El_E", &El_E);
    tree->Branch("El_Theta", &El_Theta);

    tree->Branch("Ph_Px", &Ph_Px);
    tree->Branch("Ph_Py", &Ph_Py);
    tree->Branch("Ph_Pz", &Ph_Pz);
    tree->Branch("Ph_E", &Ph_E);
    tree->Branch("Ph_Theta", &Ph_Theta);

    tree->Branch("Nuc_Px", &Nuc_Px);
    tree->Branch("Nuc_Py", &Nuc_Py);
    tree->Branch("Nuc_Pz", &Nuc_Pz);
    tree->Branch("Nuc_E", &Nuc_E);
    tree->Branch("Nuc_Theta", &Nuc_Theta);

    createTTreeFromLund(inputFileName, tree);

    cout << "\nConversion completed. Output saved in " << outputFileName << endl;
    cout << "Number of entries: " << tree->GetEntries() << endl;

    outFile->Write();
    tree->Write();
    outFile->Close();

    return 0;
}

