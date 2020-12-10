char PARTICLE[30][20] = {"gamma", "e-", "e+", "mu-", "mu+",
                         "pi-", "pi+", "kaon-", "kaon+", "kaon0S",
                         "kaon0L", "proton", "neutron", "lambda", "sigma-",
                         "sigma+", "", "", "", "deuteron",
                         "triton", "He3", "H4", "alpha", "Li7"
                         "Be7", "Be9", "", "", ""};
char PROCESS[20][200]= {"mother", "eBrem", "eIoni", "conv", "compt",
                        "electronNuclear", "positronNuclear", "photonNuclear", "", "",
                        "Decay", "CoulombScat", "annihil", "Elastic", "Inelastic",
                        "hBertini", "", "", "", ""};


int pname2pid(char *pname){
  int pid = -2;
  for(int i=0;i<30;i++){
    if(strcmp(pname,PARTICLE[i])==0){ pid = i; return pid; }
  }
  cout<<pname<<"  "<<pid<<endl;
  return pid;
}

int process2pid(char *proname){
  int process = -2;
  for(int i=0;i<20;i++){
    if( strcmp(proname+strlen(proname)-9,PROCESS[i]+strlen(PROCESS[i])-9)==0){ process = i; return process; }
    if( strcmp(proname+strlen(proname)-7,PROCESS[i]+strlen(PROCESS[i])-7)==0){ process = i; return process; }
    if(strncmp(proname,PROCESS[i],8)==0){ process = i; return process; }
  }
  cout<<proname<<"  "<<process<<endl;
  return process;
}

void draw(string ifname = "root/output.root"){
  TChain *tree = new TChain("tree");
  tree->Add(Form("%s",ifname.c_str()));

  TH1D *h_nhit    = new TH1D("h_nhit"   ,"h_nhit"   ,10,0,10);
  TH1D *h_pname   = new TH1D("h_pname"  ,"h_pname"  ,32,-2,30);
  TH1D *h_mass    = new TH1D("h_mass"   ,"h_mass"   ,400,-100,100);
  TH1D *h_process[30];
  TH2D *h_p_theta[30];

  SetTH1(h_nhit   ,"No Hits","Hits","Counts");
  SetTH1(h_pname  ,"PID","","Counts");
  h_nhit->SetMinimum(0.8);
  h_pname->SetMinimum(0.8);
  h_pname->GetXaxis()->SetLabelSize(0.04);
  h_pname->LabelsOption("v");
  h_pname->GetXaxis()->SetBinLabel(1 ,"others");
  for(int i=0;i<30;i++){
    h_pname->GetXaxis()->SetBinLabel(i+3 ,PARTICLE[i]);
  }

  for(int i=0;i<30;i++){
    h_process[i] = new TH1D(Form("h_process_%d",i),Form("h_process_%d",i),22,-2,20);
    SetTH1(h_process[i],Form("PROCESS(%s)",PARTICLE[i]),"","Counts");
    h_process[i]->SetMinimum(0.8);
    h_process[i]->GetXaxis()->SetLabelSize(0.05);
    for(int j=0;j<20;j++){
      h_process[i]->GetXaxis()->SetBinLabel(j+3 ,PROCESS[j]);
    }

   h_p_theta[i] = new TH2D(Form("h_p_theta_%d",i),Form("h_p_theta_%d",i),200,0.,60.,200,0,4000.);
    SetTH2(h_p_theta[i],Form("Mom v.s #theta (%s)",PARTICLE[i]),"#theta (degree)","Momentum (MeV/c)");
  }

  double mom_i, theta_i, phi_i;
  int nhit, pid[10], trackid[10];
  double theta[10], p[10], ptheta[10], pphi[10];
  char pro[10][20], pname[10][20];

  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("mom_i"    ,1);  tree->SetBranchAddress("mom_i"    ,&mom_i    );
  tree->SetBranchStatus("theta_i"  ,1);  tree->SetBranchAddress("theta_i"  ,&theta_i  );
  tree->SetBranchStatus("phi_i"    ,1);  tree->SetBranchAddress("phi_i"    ,&phi_i    );
  tree->SetBranchStatus("vdnhit"   ,1);  tree->SetBranchAddress("vdnhit"   ,&nhit     );
  tree->SetBranchStatus("vdtheta"  ,1);  tree->SetBranchAddress("vdtheta"  , theta    );
  tree->SetBranchStatus("vdp"      ,1);  tree->SetBranchAddress("vdp"      , p        );
  tree->SetBranchStatus("vdptheta" ,1);  tree->SetBranchAddress("vdptheta" , ptheta   );
  tree->SetBranchStatus("vdpphi"   ,1);  tree->SetBranchAddress("vdpphi"   , pphi     );
  tree->SetBranchStatus("vdpid"    ,1);  tree->SetBranchAddress("vdpid"    , pid      );
  tree->SetBranchStatus("vdtrackid",1);  tree->SetBranchAddress("vdtrackid", trackid  );
  tree->SetBranchStatus("vdpro0"   ,1);  tree->SetBranchAddress("vdpro0"   ,&pro[0]   );
  tree->SetBranchStatus("vdpro1"   ,1);  tree->SetBranchAddress("vdpro1"   ,&pro[1]   );
  tree->SetBranchStatus("vdpro2"   ,1);  tree->SetBranchAddress("vdpro2"   ,&pro[2]   );
  tree->SetBranchStatus("vdpro3"   ,1);  tree->SetBranchAddress("vdpro3"   ,&pro[3]   );
  tree->SetBranchStatus("vdpro4"   ,1);  tree->SetBranchAddress("vdpro4"   ,&pro[4]   );
  tree->SetBranchStatus("vdpro5"   ,1);  tree->SetBranchAddress("vdpro5"   ,&pro[5]   );
  tree->SetBranchStatus("vdpro6"   ,1);  tree->SetBranchAddress("vdpro6"   ,&pro[6]   );
  tree->SetBranchStatus("vdpro7"   ,1);  tree->SetBranchAddress("vdpro7"   ,&pro[7]   );
  tree->SetBranchStatus("vdpro8"   ,1);  tree->SetBranchAddress("vdpro8"   ,&pro[8]   );
  tree->SetBranchStatus("vdpro9"   ,1);  tree->SetBranchAddress("vdpro9"   ,&pro[9]   );
  tree->SetBranchStatus("vdpname0" ,1);  tree->SetBranchAddress("vdpname0" ,&pname[0] );
  tree->SetBranchStatus("vdpname1" ,1);  tree->SetBranchAddress("vdpname1" ,&pname[1] );
  tree->SetBranchStatus("vdpname2" ,1);  tree->SetBranchAddress("vdpname2" ,&pname[2] );
  tree->SetBranchStatus("vdpname3" ,1);  tree->SetBranchAddress("vdpname3" ,&pname[3] );
  tree->SetBranchStatus("vdpname4" ,1);  tree->SetBranchAddress("vdpname4" ,&pname[4] );
  tree->SetBranchStatus("vdpname5" ,1);  tree->SetBranchAddress("vdpname5" ,&pname[5] );
  tree->SetBranchStatus("vdpname6" ,1);  tree->SetBranchAddress("vdpname6" ,&pname[6] );
  tree->SetBranchStatus("vdpname7" ,1);  tree->SetBranchAddress("vdpname7" ,&pname[7] );
  tree->SetBranchStatus("vdpname8" ,1);  tree->SetBranchAddress("vdpname8" ,&pname[8] );
  tree->SetBranchStatus("vdpname9" ,1);  tree->SetBranchAddress("vdpname9" ,&pname[9] );

  int ENum = tree->GetEntries();
//  cout<<ENum<<endl;
  for(int n=0;n<ENum;n++){
    tree->GetEntry(n);

    h_nhit->Fill(nhit);
    int PID = -1;
    int PRO = -1;
    int HYPER = 0;
    TVector3 p1, p2, p3, p4; // e, t, K, ep
    TLorentzVector lp, lp1, lp2, lp3, lp4;

    for(int i=0;i<nhit;i++){
      PID = pname2pid(pname[i]);
      h_pname->Fill(PID);
//      cout<<"pro  "<<pro[i]<<endl;
      PRO = process2pid(pro[i]);
      if(PID>-1){
        h_process[PID]->Fill(PRO);
        h_p_theta[PID]->Fill(ptheta[i]*180./PI,p[i]);
        if(PID == 8){
          p1.SetMagThetaPhi(mom_i, theta_i, phi_i);
          lp1.SetVect(p1);   lp1.SetE(sqrt(mom_i*mom_i));
          p2.SetMagThetaPhi(0, 0, 0);
          lp2.SetVect(p2);   lp2.SetE(Mp);
          p3.SetMagThetaPhi(p[i], ptheta[i], pphi[i]);
          lp3.SetVect(p3);   lp3.SetE(sqrt(p[i]*p[i] + MK*MK));
          HYPER++;
//      lp = lp1 + lp2 - lp3;
//          cout<<mom_i<<"  "<<p[i]<<"  "<<ptheta[i]<<"  "<<sqrt( (mom_i+Mp-sqrt(p[i]*p[i]+MK*MK))*(mom_i+Mp-sqrt(p[i]*p[i]+MK*MK)) - (mom_i*mom_i + p[i]*p[i] - 2.*mom_i*p[i]*cos(theta[i])) )<<"  "<<lp.M()<<endl;
        }
      }
    }
    if(HYPER == 1){
      lp = lp1 + lp2 - lp3;
      double mass = lp.M() - 1115.683;
      h_mass->Fill(mass);
    }
  }

#if 1
  TCanvas *c1 = new TCanvas("c1","c1",1200,900);
  c1->Divide(1,2,1E-5,1E-5);
  c1->cd(1)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogy();
    h_nhit->Draw();
  c1->cd(2)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogy();
    h_pname->Draw();

  TCanvas *c2 = new TCanvas("c2","c2",1700,900);
  c2->Divide(2,3,1E-5,1E-5);
  c2->cd(1)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogy();
    h_process[0]->Draw();
  c2->cd(2)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogy();
    h_process[1]->Draw();
  c2->cd(3)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogy();
    h_process[2]->Draw();
  c2->cd(4)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogy();
    h_process[6]->Draw();
  c2->cd(5)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogy();
    h_process[8]->Draw();
  c2->cd(6)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogy();
    h_process[11]->Draw();

  TCanvas *c3 = new TCanvas("c3","c3",1700,900);
  c3->Divide(3,3,1E-5,1E-5);
  c3->cd(1)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogz();
    h_p_theta[0]->Draw("colz");
  c3->cd(2)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogz();
    h_p_theta[1]->Draw("colz");
  c3->cd(3)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogz();
    h_p_theta[2]->Draw("colz");
  c3->cd(4)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogz();
    h_p_theta[6]->Draw("colz");
  c3->cd(5)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogz();
    h_p_theta[8]->Draw("colz");
  c3->cd(6)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogz();
    h_p_theta[11]->Draw("colz");
  c3->cd(7)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogz();
    h_p_theta[12]->Draw("colz");
  c3->cd(8)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogz();
    h_p_theta[13]->Draw("colz");
  c3->cd(9)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogz();

  TCanvas *c4 = new TCanvas("c4","c4",1200,800);
  c4->Divide(1,1,1E-5,1E-5);
  c4->cd(1)->SetMargin(0.15,0.15,0.15,0.15); gPad->SetLogy();
    h_mass->Draw();
#endif
}

void merge(){
  TChain *tree = new TChain("tree");
  for(int i=0;i<100;i++){
    tree->Add(Form("root/output%d.root",10000+i));
  }

  TFile *fout = new TFile("root/output.root","recreate");
  TTree *newtree = tree->CloneTree();
  newtree->Write(); 
  fout->Write(); 
  fout->Close(); 
}
