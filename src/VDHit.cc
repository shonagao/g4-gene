#include "VDHit.hh"

G4Allocator<VDHit> VDHitAllocator;

VDHit::VDHit(const G4ThreeVector &gPos,
             const G4ThreeVector &gMom,
             const G4ThreeVector &vPos,
             const G4ThreeVector &vMom,
             G4double             Time,
             G4String             Pname,
             G4int                Pid,
             G4int                TrackID,
             G4String             Process)
 : gpos(gPos), gmom(gMom), vpos(vPos), vmom(vMom), time(Time), pname(Pname), pid(Pid), trackid(TrackID), process(Process)
{
}

VDHit::~VDHit()
{
}

void VDHit::Draw()
{
}

void VDHit::Print()
{
}


