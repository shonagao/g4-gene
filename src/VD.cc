#include "VD.hh"
#include "ParamManager.hh"

#include "Define.hh"

#include "MaterialList.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include <string.h>
#include <sstream>

VD::VD()
: solidVD_Sphere(0), solidVD_Box(0), logicVD(0), physiVD(0)
{
}

VD::~VD()
{
}

//Sphere
G4VPhysicalVolume* VD::SetVD(const G4String      &Name,
                             const G4ThreeVector &Pos,
                             G4RotationMatrix    *Rot,
                             G4double             Radius,
                             G4double             Thick,
                             G4LogicalVolume     *Mother,
			                       int                  ID)
{
  G4NistManager *nist = G4NistManager::Instance();
  nist->FindOrBuildMaterial("G4_Galactic");
  G4Material *vacuum = G4Material::GetMaterial("G4_Galactic");

  std::ostringstream id;
  id << ID;

  solidVD_Sphere = new G4Sphere(Name+id.str()+"S", Radius, (Radius+Thick), 0*degree, 360*degree, 0*degree, 180*degree);
  logicVD        = new G4LogicalVolume(solidVD_Sphere, vacuum, Name+id.str()+"LV");
  physiVD        = new G4PVPlacement(Rot, Pos, logicVD, Name+id.str()+"PV", Mother, false, ID);

  Visualize();

  return physiVD;
}

//Box
G4VPhysicalVolume* VD::SetVD(const G4String      &Name,
                             const G4ThreeVector &Pos,
                             G4RotationMatrix    *Rot,
                             G4double             X,
                             G4double             Y,
                             G4double             Z,
                             G4LogicalVolume     *Mother,
			                       int                 ID)
{
  G4NistManager *nist = G4NistManager::Instance();
  nist->FindOrBuildMaterial("G4_Galactic");
  G4Material *vacuum = G4Material::GetMaterial("G4_Galactic");

  std::ostringstream id;
  id << ID;

  solidVD_Box = new G4Box(Name+id.str()+"S", X, Y, Z);
  logicVD     = new G4LogicalVolume(solidVD_Box, vacuum, Name+id.str()+"LV");
  physiVD     = new G4PVPlacement(Rot, Pos, logicVD, Name+id.str()+"PV", Mother, false, ID);

  Visualize();

  // visual //
  return physiVD;
}

void VD::Visualize(){
  G4VisAttributes* vis = new G4VisAttributes();
  vis->SetColor(G4Color(0,0,0,0.1));
  vis->SetForceSolid(true);
  logicVD->SetVisAttributes(vis);
//  logicVD->SetVisAttributes(G4VisAttributes::Invisible);
}
