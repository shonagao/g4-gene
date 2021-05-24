#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "PhysicsList_User.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhaseSpaceDecayChannel.hh"
#include "G4KL3DecayChannel.hh"
#include "G4DecayTable.hh"
#include "G4Material.hh"
#include "G4OpticalPhoton.hh"
#include "G4Ions.hh"
#include "G4ios.hh"
#include <iomanip>

#include "G4IonConstructor.hh"

#include "G4BaryonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

PhysicsList_User::PhysicsList_User()
  : G4VUserPhysicsList()
{
  std::cout<<"physicslist constructor"<<std::endl;
  defaultCutValue = 0.1*cm;
}

PhysicsList_User::~PhysicsList_User()
{
  std::cout<<"physicslist destractor"<<std::endl;
}

void PhysicsList_User::ConstructParticle()
{
  std::cout<<"physicslist constructparticle"<<std::endl;
  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
  ConstructHeavyIon();
}

void PhysicsList_User::ConstructBosons()
{
  std::cout<<"physicslist constructbosons"<<std::endl;
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();
  // gamma
  G4Gamma::GammaDefinition();
  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void PhysicsList_User::ConstructLeptons()
{
  std::cout<<"physicslist constructleptons"<<std::endl;
  // leptons
  //  e+/-
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  // mu+/-
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  // nu_e
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  // nu_mu
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

void PhysicsList_User::ConstructMesons()
{
  std::cout<<"physicslist constructmesons"<<std::endl;
  //  mesons
  //    light mesons
  // Pion +/- 0
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  // Kain +/- 0
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();
  // Eta
  G4Eta::EtaDefinition();
  G4EtaPrime::EtaPrimeDefinition();

}

void PhysicsList_User::ConstructBaryons()
{
  std::cout<<"physicslist constructbaryons"<<std::endl;
//  G4BaryonConstructor pBaryonConstructor;
//  pBaryonConstructor.ConstructParticle();
  G4BaryonConstructor::ConstructParticle();

//  G4ShortLivedConstructor pShortLivedConstructor;
//  pShortLivedConstructor.ConstructParticle();
  G4ShortLivedConstructor::ConstructParticle();
}

void PhysicsList_User::ConstructHeavyIon()
{
  //Ions
  G4IonConstructor::ConstructParticle();

}

void PhysicsList_User::ConstructProcess()
{
  std::cout<<"physicslist constructor"<<std::endl;

    AddTransportation();
    ConstructEM();
    /*
      G4StepLimiter* stepLimiter = new G4StepLimiter();
      G4UserSpecialCuts* userCuts = new G4UserSpecialCuts();
      theParticleIterator->reset();
      while ((*theParticleIterator)()){
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();
      pmanager ->AddDiscreteProcess(stepLimiter);
      pmanager ->AddDiscreteProcess(userCuts);
      }
    */
}

#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"

///////Cut
//void PhysicsList_User::SetCuts()
//{
//  std::cout<<"physicslist setcuts"<<std::endl;
//  // Suppress error message int case e/gamma/proton do not exist
//  G4int temp = GetVerboseLevel();
//  // Retrive verbose level
//  SetVerboseLevel(temp);
//
////  SetCutValue(defaultCutValue, "gamma");
////  SetCutValue(defaultCutValue, "e-");
////  SetCutValue(defaultCutValue, "e+");
//
//// add 2011_10_11
//  SetCutsWithDefault();
//
//  // Production thresholds for detector regions
//  //double Pb_thickness = paramMan->GetPbThickness();
//  G4String regName = "logicBlock";
//  G4Region* reg = G4RegionStore::GetInstance()->GetRegion(regName);
//  G4ProductionCuts* cuts = new G4ProductionCuts;
//  cuts->SetProductionCut(0.1*mm);
//  reg->SetProductionCuts(cuts);
//// to here 2011_10_11
//
//
//   if (verboseLevel>0) DumpCutValuesTable();
////    SetCutsWithDefault();  
////  theParticleIterator->reset();
////  while( (*theParticleIterator)() ){
////    G4ParticleDefinition *particle=theParticleIterator->value();
////    particle->SetApplyCutsFlag( true );
////  }
//}

///////EM
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"


#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"

#include "G4UserSpecialCuts.hh"

void PhysicsList_User::ConstructEM()
{
  std::cout<<"physicslist constructEM"<<std::endl;
  auto theParticleIterator = GetParticleIterator();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition *particle = theParticleIterator->value();
    G4ProcessManager *pManager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if( particleName == "gamma" ){
      pManager->AddProcess( new G4UserSpecialCuts(), -1, -1, 1 );    
      pManager->AddDiscreteProcess( new G4PhotoElectricEffect() );
      pManager->AddDiscreteProcess( new G4ComptonScattering() );
      pManager->AddDiscreteProcess( new G4GammaConversion() );
    }
    else if( particleName == "e-" ){
      pManager->AddProcess( new G4UserSpecialCuts(),     -1, -1, 1 );
      pManager->AddProcess( new G4eMultipleScattering(), -1,  1, 2 );
      pManager->AddProcess( new G4eIonisation(),         -1,  2, 3 );
      pManager->AddProcess( new G4eBremsstrahlung(),     -1,  3, 4 );
    }
    else if( particleName == "e+" ){
      pManager->AddProcess( new G4UserSpecialCuts(),     -1, -1, 1 );
      pManager->AddProcess( new G4eMultipleScattering(), -1,  1, 2 );
      pManager->AddProcess( new G4eIonisation(),         -1,  2, 3 );
      pManager->AddProcess( new G4eBremsstrahlung(),     -1,  3, 4 );
      pManager->AddProcess( new G4eplusAnnihilation(),    1, -1, 5 );
    }
    else if( particleName == "mu+" || particleName == "mu-" ){
      pManager->AddProcess( new G4MuMultipleScattering(), -1,  1, 1 );
      pManager->AddProcess( new G4MuIonisation(),         -1,  2, 2 ); 
      pManager->AddProcess( new G4MuBremsstrahlung(),     -1, -1, 3 );
      pManager->AddProcess( new G4MuPairProduction(),     -1, -1, 4 );
    }
    else if( particleName == "proton" ||
	     particleName == "kaon+" ||
	     particleName == "pi-" ||
	     particleName == "pi+"    ) {
      pManager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pManager->AddProcess(new G4hIonisation,         -1, 2, 2);
      pManager->AddProcess(new G4hBremsstrahlung,     -1, 3, 3);
      pManager->AddProcess(new G4hPairProduction,     -1, 4, 4);
    }
    /*	 else if ( particleName == "alpha" ||
      particleName == "deuteron" ||
      particleName == "He3" ){ 
      pManager->AddProcess( new G4hMultipleScattering,  -1,  1, 1 );
      pManager->AddProcess( new G4ionIonisation,        -1,  2, 2 );
	 }
	 else if ( particleName == "GenericIon" ){
	 pManager->AddProcess( new G4hMultipleScattering,  -1,  1, 1 );
	 pManager->AddProcess( new G4ionIonisation,        -1,  2, 2 );
	 }
	 else if( (!particle->IsShortLived()) &&
	 (particle->GetPDGCharge() != 0.0) &&
	 (particle->GetParticleName() != "chargedgeantino")){
	 pManager->AddProcess( new G4hMultipleScattering,  -1,  1, 1 );
      pManager->AddProcess( new G4hIonisation,          -1,  2, 2 );
      }*/
    else if( (!particle->IsShortLived()) &&
             (particle->GetPDGCharge()!=0.0) &&
	     !( particleName=="chargedgeantino"
		|| particleName=="antichargedgeantino")){
      //      pManager->AddProcess( new G4UserSpecialCuts(),      -1, -1, 1 );
      pManager->AddProcess( new G4hMultipleScattering(),  -1,  1, 1 );
      pManager->AddProcess( new G4hIonisation(),          -1,  2, 2 );
    }
  }
}

///////Decay
#include "G4Decay.hh"

void PhysicsList_User::ConstructDecay()
{
  std::cout<<"physicslist constructdecay"<<std::endl;
  G4Decay *theDecayProcess = new G4Decay();
  auto theParticleIterator = GetParticleIterator();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition *particle = theParticleIterator->value();
    G4ProcessManager *pManager = particle->GetProcessManager();
    if( theDecayProcess->IsApplicable(*particle) ){
      pManager->AddProcess( theDecayProcess );
      pManager->SetProcessOrdering( theDecayProcess, idxPostStep );
      pManager->SetProcessOrdering( theDecayProcess, idxAtRest );
    }
  }
}
