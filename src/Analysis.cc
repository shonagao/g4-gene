#include "Analysis.hh"
#include "PrimaryGeneratorAction.hh"
#include "VDSD.hh"
#include "VDHit.hh"

#include "Define.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include <time.h>

/////////////////////////////////
Analysis::Analysis()
: fRootFile(0), fTree(0)
{
  paramMan = ParamManager::GetParam();
  start=time(NULL);
  time(&start);
  DefineRoot();
}
/////////////////////////////////
Analysis::~Analysis(){
  G4cout<<"Destructor Analysis"<<G4endl;
  Save();
}
/////////////////////////////////
void Analysis::BeginOfRun(const G4Run *aRun ){
  G4cout<<"Start Run: "<<aRun->GetRunID()<<G4endl;
}
/////////////////////////////////
void Analysis::EndOfRun(const G4Run *aRun ){
  G4cout<<"End Run: "<<aRun->GetRunID()<<G4endl;
}
/////////////////////////////////
void Analysis::BeginOfEvent(const G4Event *aEvent ){
  evID = aEvent->GetEventID();
}
/////////////////////////////////
void Analysis::EndOfEvent(const G4Event *aEvent ){
  evID = aEvent->GetEventID();

  G4SDManager* SDManager = G4SDManager::GetSDMpointer();

  G4HCofThisEvent* HCTE= aEvent-> GetHCofThisEvent();
  if(!HCTE) return;

  if(evID%100000==0){
    end=time(NULL);
    time(&end);
//    sprintf(clout,"%.0f sec",difftime(end,start));
    G4cout<<Form("eventID  %d  %.0lf sec",evID,difftime(end,start))<<G4endl;
  }
  /////////////////////
  //Initial condition//
  /////////////////////
  G4double Genmom_x = aEvent->GetPrimaryVertex()->GetPrimary()->GetPx();
  G4double Genmom_y = aEvent->GetPrimaryVertex()->GetPrimary()->GetPy();
  G4double Genmom_z = aEvent->GetPrimaryVertex()->GetPrimary()->GetPz();
  G4ThreeVector Genmom(Genmom_x, Genmom_y, Genmom_z);
  Genmom3  = Genmom.mag();
  Gentheta = Genmom.theta();
  Genphi   = Genmom.phi();
  Genpos_x = aEvent->GetPrimaryVertex()->GetX0();
  Genpos_y = aEvent->GetPrimaryVertex()->GetY0();
  Genpos_z = aEvent->GetPrimaryVertex()->GetZ0();
  
  /////////////////////
  // Virtual Detector//
  /////////////////////
  G4int vdID[nvd];
  VDHitsCollection* vdHC[nvd];
  bool HIT = false;

  for(int i=0;i<nvd;i++){
    vdID[i] = -1;
    std::ostringstream id;
    id << i;
    G4String DetName_VD = G4String("VD_") + id.str();
    vdID[i] = SDManager->GetCollectionID(DetName_VD);
    vdHC[i] = (VDHitsCollection*)(HCTE->GetHC(vdID[i]));
    if(!vdHC[i]){ std::cout<<"no VDHitsCollection"<<std::endl; return; }
    G4int vdhits = vdHC[i]->entries();
    VDnhit = vdhits;
    if(vdhits>10){ vdhits=10; }
    if(vdhits>0){ HIT = true; }

    for(int n=0;n<10;n++){
      VDtime[n] = -9999;
      VDx[n]  = VDy[n]  = VDz[n]  = VDtheta[n] = VDphi[n]    = -9999;
      VDpx[n] = VDpy[n] = VDpz[n] = VDp[n]     = VDptheta[n] = VDpphi[n] =  -9999;
      VDpid[n] = VDtrackid[n] = -99;
      memset( VDpro[n], 0, sizeof( VDpro[n] ) );
      memset( VDpname[n], 0, sizeof( VDpname[n] ) );
    }
 
    for(int n=0;n<vdhits;n++){
      VDHit *fVDhit = (*vdHC[i])[n];
      VDtime[n] = fVDhit->GetTime();
      G4ThreeVector VDgpos = fVDhit->GetGPos();
      G4ThreeVector VDgmom = fVDhit->GetGMom();
      VDx[n] = VDgpos.x(); VDy[n] = VDgpos.y(); VDz[n] = VDgpos.z();
      VDtheta[n] = VDgpos.theta(); VDphi[n] = VDgpos.phi();
      VDpx[n] = VDgmom.x(); VDpy[n] = VDgmom.y(); VDpz[n] = VDgmom.z();
      VDp[n] = VDgmom.mag(); VDptheta[n] = VDgmom.theta(); VDpphi[n] = VDgmom.phi();
      VDpid[n]      = fVDhit->GetPID();
      VDtrackid[n]  = fVDhit->GetTrackID();
      std::string process  = fVDhit->GetProcess();
      std::string pname    = fVDhit->GetPname();
      sprintf(VDpro[n], process.c_str());
      sprintf(VDpname[n], pname.c_str());
    }
   
  }
  
  if( HIT ){
    fTree->Fill();
  }
}

/////////////////////////////////
void Analysis::Save(){
  fRootFile->Write();
  fRootFile->Close();
  if(fRootFile) delete fRootFile;
}

/////////////////////////////////
void Analysis::DefineRoot(){
  fRootFile = new TFile(paramMan->GetOutputFile(),"RECREATE","",0);
  if( !fRootFile ){
    G4cout<<"Problem creating the rootfile "<<paramMan->GetOutputFile()<<G4endl;
    return;
  }

  new TH1D("h_Eg_gene"      ,"h_Eg_gene"       ,1600,0,1600);
  
  fTree = new TTree("tree","geant4");
  fTree->Branch("eventid" , &evID , "eventid/I"       );
  fTree->Branch("mom_i"   , &Genmom3 , "mom_i/D"         );
  fTree->Branch("theta_i" , &Gentheta, "theta_i/D"       );
  fTree->Branch("phi_i"   , &Genphi  , "phi_i/D"         );
  fTree->Branch("x_i"     , &Genpos_x  , "x_i/D"         );
  fTree->Branch("y_i"     , &Genpos_y  , "y_i/D"         );
  fTree->Branch("z_i"     , &Genpos_z  , "z_i/D"         );
  
  //Virtual Detector
  fTree->Branch("vdnhit"    ,&VDnhit     ,      "vdnhit/I"                );
  fTree->Branch("vdx"       , VDx        ,      "vdx[10]/D"               );
  fTree->Branch("vdy"       , VDy        ,      "vdy[10]/D"               );
  fTree->Branch("vdz"       , VDz        ,      "vdz[10]/D"               );
  fTree->Branch("vdtheta"   , VDtheta    ,      "vdtheta[10]/D"           );
  fTree->Branch("vdphi"     , VDphi      ,      "vdphi[10]/D"             );
  fTree->Branch("vdp"       , VDp        ,      "vdp[10]/D"               );
  fTree->Branch("vdpx"      , VDpx       ,      "vdpx[10]/D"              );
  fTree->Branch("vdpy"      , VDpy       ,      "vdpy[10]/D"              );
  fTree->Branch("vdpz"      , VDpz       ,      "vdpz[10]/D"              );
  fTree->Branch("vdptheta"  , VDptheta   ,      "vdptheta[10]/D"          );
  fTree->Branch("vdpphi"    , VDpphi     ,      "vdpphi[10]/D"            );
  fTree->Branch("vdpid"     , VDpid      ,      "vdpid[10]/I"             );
  fTree->Branch("vdtrackid" , VDtrackid  ,      "vdtrackid[10]/I"         );
  fTree->Branch("vdtime"    , VDtime     ,      "vdtime[10]/D"            );
  fTree->Branch("vdpro0"    , VDpro[0]   ,      "vdpro0[10]/C"            );
  fTree->Branch("vdpro1"    , VDpro[1]   ,      "vdpro1[10]/C"            );
  fTree->Branch("vdpro2"    , VDpro[2]   ,      "vdpro2[10]/C"            );
  fTree->Branch("vdpro3"    , VDpro[3]   ,      "vdpro3[10]/C"            );
  fTree->Branch("vdpro4"    , VDpro[4]   ,      "vdpro4[10]/C"            );
  fTree->Branch("vdpro5"    , VDpro[5]   ,      "vdpro5[10]/C"            );
  fTree->Branch("vdpro6"    , VDpro[6]   ,      "vdpro6[10]/C"            );
  fTree->Branch("vdpro7"    , VDpro[7]   ,      "vdpro7[10]/C"            );
  fTree->Branch("vdpro8"    , VDpro[8]   ,      "vdpro8[10]/C"            );
  fTree->Branch("vdpro9"    , VDpro[9]   ,      "vdpro9[10]/C"            );
  fTree->Branch("vdpname0"  , VDpname[0] ,      "vdpname0[10]/C"          );
  fTree->Branch("vdpname1"  , VDpname[1] ,      "vdpname1[10]/C"          );
  fTree->Branch("vdpname2"  , VDpname[2] ,      "vdpname2[10]/C"          );
  fTree->Branch("vdpname3"  , VDpname[3] ,      "vdpname3[10]/C"          );
  fTree->Branch("vdpname4"  , VDpname[4] ,      "vdpname4[10]/C"          );
  fTree->Branch("vdpname5"  , VDpname[5] ,      "vdpname5[10]/C"          );
  fTree->Branch("vdpname6"  , VDpname[6] ,      "vdpname6[10]/C"          );
  fTree->Branch("vdpname7"  , VDpname[7] ,      "vdpname7[10]/C"          );
  fTree->Branch("vdpname8"  , VDpname[8] ,      "vdpname8[10]/C"          );
  fTree->Branch("vdpname9"  , VDpname[9] ,      "vdpname9[10]/C"          );
}

