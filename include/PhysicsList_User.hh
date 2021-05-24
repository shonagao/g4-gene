#ifndef PhysicsList_User_h
#define PhysicsList_User_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"
#include "ParamManager.hh"

class PhysicsList_User: public G4VUserPhysicsList
{
  public:
    PhysicsList_User();
   ~PhysicsList_User();

  protected:
    // Construct particle and physics
    void ConstructParticle();
    void ConstructProcess();

//    void SetCuts();

  protected:
    // these methods Construct particles
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBaryons();
    void ConstructHeavyIon();

  protected:
    // these methods Construct physics processes and register them
    void ConstructGeneral();

  private:
    void ConstructEM();
    void ConstructDecay();
//  void AddTransportation();  // remove A01 PhysicsList

  private:
    ParamManager *paramMan;

};

#endif
