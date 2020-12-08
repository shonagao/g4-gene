//########################################################
// PrimaryGeneratorAction
// Coordinate is always defined with Geant4 Global Coordinate
//########################################################
#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"

static const double PI = 4.*atan(1.0);
/////////////////////////////////////////////////////////
PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
  G4int nParticles = 1;
  ParticleGun = new G4ParticleGun(nParticles);
  particleTable = G4ParticleTable::GetParticleTable();
  ionTable = G4IonTable::GetIonTable();
  decayTable = new G4DecayTable();

  paramMan = ParamManager::GetParam();
  BeamParticle = paramMan->GetBeamParticle();
  BeamType     = paramMan->GetBeamType();
  BeamMom      = paramMan->GetBeamMom();
  BeamMomR     = paramMan->GetBeamMomRange();
  BeamX        = paramMan->GetBeamX();
  BeamXR       = paramMan->GetBeamXRange();
  BeamY        = paramMan->GetBeamY();
  BeamYR       = paramMan->GetBeamYRange();
  BeamZ        = paramMan->GetBeamZ();
  BeamZR       = paramMan->GetBeamZRange();
  BeamT        = paramMan->GetBeamTheta();
  BeamTR       = paramMan->GetBeamThetaRange();
  BeamP        = paramMan->GetBeamPhi();
  BeamPR       = paramMan->GetBeamPhiRange();
  DecayFlag    = paramMan->GetDecayFlag();

  x  = BeamX   * mm;
  y  = BeamY   * mm;
  z  = BeamZ   * mm;
  px = 0.      * MeV;
  py = 0.      * MeV;
  pz = BeamMom * MeV;

//  h_Eg_gene_             = (TH1D*)gROOT->FindObject("h_Eg_gene");

  particle = particleTable->FindParticle(BeamParticle);

  if(DecayFlag==0) particle->SetPDGStable(1);

  ParticleGun = new G4ParticleGun(1);
  ParticleGun->SetParticleDefinition(particle);
//  ParticleGun->SetParticleEnergy(0.*MeV);
  ParticleGun->SetParticleMomentum(G4ThreeVector(px,py,pz));
  ParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));

}

/////////////////////////////////////////////////////////
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete ParticleGun;
}

/////////////////////////////////////////////////////////
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  eventID=anEvent->GetEventID();

  switch(BeamType){
    case 0:
      break;
    case 1:
      GenerateUniform();
      ParticleGun = new G4ParticleGun(1);
      ParticleGun->SetParticleDefinition(particle);
      ParticleGun->SetParticleMomentum(G4ThreeVector(px,py,pz));
      ParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));
      break;
    default:
      break;
  }

  ParticleGun->GeneratePrimaryVertex(anEvent);
}

/////////////////////////////////////////////////////////
void PrimaryGeneratorAction::GenerateUniform()
{
  //x = 0.*mm;  y = 0.*mm;  z = -1500.*mm;
  x = (0+BeamX)*mm;
  y = (0+BeamY)*mm;
  z = (0+BeamZ)*mm;
  x += CLHEP::RandGauss::shoot(x,BeamXR*mm);
  y += CLHEP::RandGauss::shoot(y,BeamYR*mm);
  z += CLHEP::RandFlat::shoot(-BeamZR*mm,BeamZR*mm);
  G4ThreeVector pos(x, y, z);

  x = pos.x();  y = pos.y();  z = pos.z();

  G4double Mom;
  Mom = BeamMom * (1. + 0.01*BeamMomR*2.*(G4UniformRand()-0.5)) * MeV;
  G4double Theta = acos(1.-(1.-cos(BeamTR))*G4UniformRand());
  G4double Phi = (G4UniformRand()-0.5)*PI*2.;
  G4ThreeVector mom;
  mom.setRThetaPhi(Mom,Theta,Phi);
  mom.rotateY(BeamT);

  px = mom.x();  py = mom.y();  pz = mom.z();

}

