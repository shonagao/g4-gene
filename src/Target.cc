#include "Target.hh"

#include "MaterialList.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include <string.h>
#include <sstream>

Target::Target()
: TargetS(0), TargetLV(0)
{
}

Target::~Target()
{
}

G4VPhysicalVolume* Target::target(const G4String      &Name,
				                          const G4ThreeVector &Pos,
				                          G4RotationMatrix    *Rot,
                                  const G4double      &Thick,
				                          G4LogicalVolume     *Mother,
                                  G4Material          *Material,
				                          int                 ID)
{

// Tube Name, Rmin, Rmax, Thick, PHImin, PHImax
  TargetS  = new G4Tubs("TargetS", 0.*mm, 10.*mm, Thick/2., 0.*degree, 360.*degree );
  TargetLV = new G4LogicalVolume(TargetS, Material, "TargetLV");
  TargetPV = new G4PVPlacement(Rot, Pos, TargetLV, Name, Mother, 0, ID, 0);

  G4VisAttributes* target_vis = new G4VisAttributes();
  target_vis->SetColor(G4Color(0,0,1,0.5));
  TargetLV->SetVisAttributes(target_vis);
//  TargetLV->SetVisAttributes(G4VisAttributes::Invisible);

  return TargetPV;
}

G4VPhysicalVolume* Target::JLabTargetCell_2018(const G4String      &Name,
				                                       const G4ThreeVector &Pos,
				                                       G4RotationMatrix    *Rot,
				                                       G4LogicalVolume     *Mother,
				                                       int                 ID)
{

  MaterialList *mList = MaterialList::GetInstance();

  TargetS  = new G4Tubs("TargetS", 0.*mm, 10.*mm, 10./2., 0.*degree, 360.*degree );
  TargetLV = new G4LogicalVolume(TargetS, mList->Fe, "TargetLV");
  TargetPV = new G4PVPlacement(Rot, Pos, TargetLV, Name, Mother, 0, ID, 0);

  G4VisAttributes* target_vis = new G4VisAttributes();
  target_vis->SetColor(G4Color(0,0,1,0.5));
  TargetLV->SetVisAttributes(target_vis);
//  TargetLV->SetVisAttributes(G4VisAttributes::Invisible);

  return TargetPV;
}


