#include "G4VPhysicalVolume.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4TouchableHandle.hh"
#include "G4SystemOfUnits.hh"
#include "VDSD.hh"
#include "VDHit.hh"

#include <fstream>
using namespace std;

VDSD::VDSD(const G4String& Name): G4VSensitiveDetector(Name)
{
  paramMan = ParamManager::GetParam();

  for(int i=0;i<nvd;i++){
    std::ostringstream id;
    id << i;
    G4String DetectorName = G4String("VD_") + id.str();
	  collectionName.insert(DetectorName);
  }
}

VDSD::~VDSD()
{
}

void VDSD::Initialize(G4HCofThisEvent* HCTE)
{
  for(int i=0;i<nvd;i++){
    hitsCollection[i] = new VDHitsCollection(SensitiveDetectorName,collectionName[i]);
    G4int hcid = GetCollectionID(i);
	HCTE->AddHitsCollection(hcid, hitsCollection[i]);
    edep = 0;
  }
}

G4bool VDSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  const G4StepPoint* preStepPoint  = aStep-> GetPreStepPoint();
//  const G4StepPoint* postStepPoint = aStep-> GetPostStepPoint();
  const G4Track *aTrack            = aStep->GetTrack();
  G4TouchableHistory* touchable    = (G4TouchableHistory*)(preStepPoint-> GetTouchable());
  G4TouchableHandle theTouchable   = preStepPoint->GetTouchableHandle();
  G4VPhysicalVolume *Vol = touchable-> GetVolume();

  G4int         trackID  = aTrack->GetTrackID();
 // G4int         parentID = aTrack->GetParentID();
 // G4double      charge   = aTrack->GetDefinition()->GetPDGCharge();
  G4int         volID    = Vol->GetCopyNo();
  G4ThreeVector gpos     = preStepPoint->GetPosition();
  G4ThreeVector lpos     = touchable->GetHistory()->GetTopTransform().TransformPoint(gpos);
  G4ThreeVector gmom     = preStepPoint->GetMomentum();
  G4double      time     = preStepPoint->GetGlobalTime();
  G4String      pname    = aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName();
  G4int         pid      = aTrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
  G4double      pmass    = aTrack->GetDynamicParticle()->GetMass();
//  G4double      tr_len   = aTrack->GetTrackLength();
  G4ThreeVector vpos     = aTrack->GetVertexPosition();
  G4double      vkin     = aTrack->GetVertexKineticEnergy();
  G4ThreeVector vpdir    = aTrack->GetVertexMomentumDirection();
  G4double      vpabs    = sqrt(pow(vkin+pmass,2)-pmass*pmass);
  G4ThreeVector vp       = G4ThreeVector(vpdir.x()*vpabs, vpdir.y()*vpabs, vpdir.z()*vpabs);
  G4String hit_process   = aTrack->GetStep()->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  G4String cre_process   = "mother";
  if(trackID>1){ cre_process = aTrack->GetCreatorProcess()->GetProcessName(); }
  edep += aStep->GetTotalEnergyDeposit();

//  G4cout<<trackID<<"  "<<pname<<"  "<<pid<<"  "<<hit_process<<"  "<<cre_process<<G4endl;

//  if((gpos.theta()>1.*degree && gmom.mag()>50.*MeV) || fabs(pid)>100){
  if((gpos.theta()>5.*degree && gmom.mag()>500.*MeV) || (fabs(pid)>100 && gmom.mag()>250.*MeV)){
    VDHit *ahit = new VDHit(gpos,gmom,time,pname,pid,trackID,cre_process);
    hitsCollection[volID]->insert(ahit);
  }
  return true;
}

void VDSD::EndOfEvent(G4HCofThisEvent*)
{
}

void VDSD::DrawAll()
{
}

void VDSD::PrintAll()
{
  for(int i=0;i<nvd;i++){
    hitsCollection[i]-> PrintAllHits();
  }
}

