void BDT::Theory(int model, int bin, double xmean, double Qmean, double tmean, int Nphi){
  TString model_str;
  int model_val;
  switch (model)
  {
  case 1:
    model_str = TString("BH");
    model_val = 35;
    break;
  case 2:
    model_str = TString("VGG");
    model_val = 35;
    break;
  case 3:
    model_str = TString("KM");
    model_val = 63;
    break;
  case 4:
    model_str = TString("GK");
    model_val = 99;
    break;
  }

  TString filename = extXSEC + model_str + Form("/bin_%i.txt",bin);
  std::ifstream file(filename);


  if (file.good() && false) {
      std::cerr << "Theory files exist for "<< model_str<< std::endl;
    }
    else
    {
    std::cout<<"Creating theory prediction for "<<model_str<<endl;
    gSystem->Exec(Form("rm -rf %s%s/VGG && cp -r %sinclude/xsec/VGG %s%s",dir.Data(),Folder.Data(),dir.Data(),dir.Data(),Folder.Data()));
    if(model==1)
    {
      /*
    gSystem->Exec(TString("cd ") + Folder + Form("VGG && ( \
        echo 3 && \
        echo 4 && \
        echo 1 && \
        echo 1 && \
        echo 3 && \
        echo 1 && \
        echo 10.6 && \
        echo 3 && \
        echo %f && \
        echo %f && \
        echo 0 && \
        echo %f && \
        echo %f && \
        echo %f && \
        echo 360) | ./dvcs >> /dev/null && \
        mv dvcs_* phi.dat && cd -", Qmean, xmean, -1.0*tmean, 360.*0.5/Nphi, 360./60));  
        */  
  //BH computation
  std::cout<<"Computing BH integral"<<endl;
  gSystem->Exec(Form("cp -r %sinclude/xsec/VGG/* %s%s && cp %sinclude/xsec/VGG/F_bin.sh %s%s && cd %s%s && ./F_bin.sh %f %f %f %f %f %f %f >> /dev/null && cat int.dat > int_BH.dat && tac int.dat >> int_BH.dat && rm int.dat && mv int_BH.dat VGG/phi.dat && cd -",dir.Data(),dir.Data(),Folder.Data(),dir.Data(),dir.Data(),Folder.Data(),dir.Data(),Folder.Data(), boundaries.at(4), boundaries.at(5), boundaries.at(2), boundaries.at(3), -1.0*boundaries.at(1), -1.0*boundaries.at(0), (360./Nphi)));
      }
    else if(model==2)
    {
    gSystem->Exec(TString("cd ") + Folder + Form("VGG && ( \
    echo 3 && \
    echo 4 && \
    echo 3 && \
    echo 1 && \
    echo %i && \
    echo 1 && \
    echo 5 && \
    echo 8 && \
    echo 1.098 && \
    echo 2 && \
    echo 2 && \
    echo 2 && \
    echo 0.3 && \
    echo 0.3 && \
    echo 1 && \
    echo 1 && \
    echo 1 && \
    echo 3 && \
    echo 1 && \
    echo 10.6 && \
    echo 3 && \
    echo %f && \
    echo %f && \
    echo 0 && \
    echo %f && \
    echo %f && \
    echo %f && \
    echo 360) | ./dvcs >> /dev/null && \
    mv dvcs_* phi.dat && cd -", model_val, Qmean, xmean, -1.0*tmean, 360.*0.5/Nphi, 360./Nphi));
    }
    else if(model==3 || model==4)
    {
    gSystem->Exec(TString("cd ") + Folder + Form("VGG && ( \
    echo 3 && \
    echo 4 && \
    echo 3 && \
    echo 1 && \
    echo %i && \
    echo 2 && \
    echo 2 && \
    echo 1 && \
    echo 1 && \
    echo 1 && \
    echo 3 && \
    echo 1 && \
    echo 10.6 && \
    echo 3 && \
    echo %f && \
    echo %f && \
    echo 0 && \
    echo %f && \
    echo %f && \
    echo %f && \
    echo 360) | ./dvcs >> /dev/null && \
    mv dvcs_* phi.dat && cd -", model_val,Qmean, xmean, -1.0*tmean, 360.*0.5/Nphi, 360./Nphi));
    }
    else
    {
      std::cout<<"Model not implemented"<<endl;
      return;
    }
    gSystem->Exec(TString("cp ") + Folder + TString("VGG/phi.dat ") + extXSEC + model_str + Form("/bin_%i.txt", bin));
    
    gSystem->Exec("rm -r " + Folder +  TString("VGG"));
  
    }

    
    return;

}
