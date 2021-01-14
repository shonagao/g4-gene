#ifndef Analysis_h
#define Analysis_h 1

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TObjArray.h>
#pragma GCC diagnostic pop

#include "globals.hh"
#include "Define.hh"

#include "ParamManager.hh"

class G4Run;
class G4Event;
class G4Step;

class Analysis
{
  public:
    Analysis();
    virtual ~Analysis();

    void BeginOfRun(const G4Run *aRun );
    void EndOfRun(const G4Run *aRun );
    void BeginOfEvent(const G4Event *aEvent );
    void EndOfEvent(const G4Event *aEvent );
    void Save();

  private:
    TFile *fRootFile;
    TTree *fTree;
    time_t start, end;
    void DefineRoot();
    ParamManager *paramMan;

    G4int evID;
    G4double Genmom3, Gentheta, Genphi;
    G4double Genpos_x, Genpos_y, Genpos_z;

    G4int VDnhit;
    G4double VDtime[10];
    G4double VDx[10] , VDy[10] , VDz[10];
    G4double VDtheta[10], VDphi[10];
    G4double VDpx[10], VDpy[10], VDpz[10];
    G4double VDp[10], VDptheta[10], VDpphi[10];
    G4double VDvx[10] , VDvy[10] , VDvz[10];
    G4double VDvpx[10], VDvpy[10], VDvpz[10];
    G4double VDvp[10], VDvptheta[10], VDvpphi[10];
    G4int VDpid[10], VDtrackid[10];
    char VDpname[10][200];
    char VDpro[10][200];
};
#endif
