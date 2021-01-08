#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class G4PhysListFactoryMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsList: public G4VModularPhysicsList
{
public:

  PhysicsList();
  virtual ~PhysicsList();

  virtual void ConstructParticle();
  virtual void ConstructProcess();    
  void AddPhysicsList(const G4String& name);

  void AddDecay();
  void AddRadioactiveDecay();
  void AddStepMax();
  
private:
  G4VPhysicsConstructor*  fEmPhysicsList;
  std::vector<G4VPhysicsConstructor*>  fHadronPhys;
    
  G4PhysListFactoryMessenger* fFactMessenger;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

