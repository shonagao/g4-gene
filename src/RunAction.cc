#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

/////////////////////////////////////////////////////
RunAction::RunAction(Analysis *anaman)
 : G4UserRunAction(), anaMan(anaman)
{ 
}

/////////////////////////////////////////////////////
RunAction::~RunAction()
{}

/////////////////////////////////////////////////////
void RunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  anaMan->BeginOfRun(aRun);
}

/////////////////////////////////////////////////////
void RunAction::EndOfRunAction(const G4Run* aRun)
{
  anaMan->EndOfRun(aRun);
}
