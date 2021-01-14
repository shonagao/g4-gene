#include "DetectorConstruction.hh"
#include "ParamManager.hh"
#include "MaterialList.hh"
#include "Define.hh"

#include "Target.hh"
#include "VD.hh"
#include "VDSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"

#include <fstream>

//G4ThreadLocal 

////////////////////////////////////////////////////////////////
DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(), 
 fStepLimit(NULL), fCheckOverlaps(true)
{
  G4cout<<"Constructor DetectorConstruction"<<G4endl;
}

////////////////////////////////////////////////////////////////
DetectorConstruction::~DetectorConstruction()
{
  G4cout<<"Destructor DetectorConstruction"<<G4endl;
  delete fStepLimit;
}

////////////////////////////////////////////////////////////////
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return DefineVolumes();
}

////////////////////////////////////////////////////////////////
G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  MaterialList *mList = MaterialList::GetInstance();
  paramMan = ParamManager::GetParam();

  ///////////
  // World //
  ///////////
  G4double worldLength = 2.*m;
  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);

  G4Box* worldS = new G4Box( "world", worldLength/2., worldLength/2., worldLength/2. );

  G4LogicalVolume* worldLV = new G4LogicalVolume(
                 worldS,          // solid
                 mList->Vacuum,   // material
                 "World" );       // logical volume name
  
  G4VPhysicalVolume* worldPV = new G4PVPlacement(
                 0,               // rotation
                 G4ThreeVector(), // origin
                 worldLV,         // logical volume
                 "World",         // physical volume name
                 0,               // mother volume
                 false,           // boolean operations
                 0,               // copy number
                 fCheckOverlaps); // checking overlaps 

  G4VisAttributes* world_vis = new G4VisAttributes();
  world_vis->SetColor(G4Color(0.2, 0.2, 0.2, 0.05));
  worldLV->SetVisAttributes(world_vis);
//  logicworld->SetVisAttributes(G4VisAttributes::Invisible); 
 
  ////////////
  // target //
  ////////////
  target = new Target();
  G4ThreeVector tar_pos(0.*mm, 0.*mm, 0.*mm);
  G4RotationMatrix *tar_rot = new G4RotationMatrix();
  G4double thick = paramMan->GetTargetThick() * mm;
  target->target("TargetPV",tar_pos,tar_rot,thick,worldLV,mList->MyLiqH,0);
//  target->JLabTargetCell_2018("TargetPV",tar_pos,tar_rot,worldLV,0);

  //////////////////////
  // Virtual Detector //
  //////////////////////
  G4RotationMatrix *vd_rot = new G4RotationMatrix();
  for( int i=0; i<nvd; i++ ){
    vd[i] = new VD();
    G4ThreeVector vd_pos(0.*mm, 0.*mm, 0.*mm);
    vd[i]->SetVD("VD",vd_pos,vd_rot,300.*mm, 0.1*mm, worldLV,i);
  }

//  G4double maxStep = 0.5*chamberWidth;
//  fStepLimit = new G4UserLimits(maxStep);
//  trackerLV->SetUserLimits(fStepLimit);
 
  return worldPV;
}

////////////////////////////////////////////////////////////////
void DetectorConstruction::ConstructSDandField()
{
  // Sensitive Detectors
  G4SDManager* SDmanager= G4SDManager::GetSDMpointer();

  VDSD* vdsd = new VDSD("VDSD");
  SDmanager->AddNewDetector(vdsd);
  for( int i=0; i<nvd; i++ ){
    vd[i]->GetDetectorLogic()->SetSensitiveDetector(vdsd);
  }

}

////////////////////////////////////////////////////////////////
void DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}

////////////////////////////////////////////////////////////////
void DetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps)
{
  fCheckOverlaps = checkOverlaps;
}  
