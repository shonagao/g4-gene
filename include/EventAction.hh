#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "Define.hh"

#include "Analysis.hh"
#include "globals.hh"

//#include <TFile.h>
//#include <TTree.h>
//#include <TObjArray.h>

class EventAction : public G4UserEventAction
{
  public:
    EventAction(Analysis *analysismanager);
    virtual ~EventAction();

    virtual void  BeginOfEventAction(const G4Event* anEvent);
    virtual void    EndOfEventAction(const G4Event* anEvent);

  private:
    time_t start, end;

    Analysis *anaMan;

};

#endif
