#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4ChargeExchangePhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4NeutronCrossSectionXS.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "G4IonElasticPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmParameters.hh"
#include "G4PhysListFactoryMessenger.hh"

#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsFTFP_BERT_TRV.hh"
#include "G4HadronPhysicsFTF_BIC.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_FTFP_BERT.hh"
#include "G4HadronPhysicsQGS_BIC.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"

#include "G4SystemOfUnits.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
  SetDefaultCutValue(1.0*mm);
  G4int ver = 1;
  SetVerboseLevel(ver);
//
//  fParticleList  = new G4DecayPhysics();
//  fEmPhysicsList = new G4EmStandardPhysics();
 // EM Physics
  RegisterPhysics( new G4EmStandardPhysics(ver));

  // Synchroton Radiation & GN Physics
  RegisterPhysics( new G4EmExtraPhysics(ver) );

  // Decays 
  RegisterPhysics( new G4DecayPhysics(ver) );

   // Hadron Elastic scattering
  RegisterPhysics( new G4HadronElasticPhysics(ver) );

   // Hadron Physics
  RegisterPhysics( new G4HadronPhysicsFTFP_BERT(ver));

  // Stopping Physics
  RegisterPhysics( new G4StoppingPhysics(ver) );

  // Ion Physics
  RegisterPhysics( new G4IonPhysics(ver));
  
  // Neutron tracking cut
  RegisterPhysics( new G4NeutronTrackingCut(ver));

}

PhysicsList::~PhysicsList()
{
//  delete fParticleList;
//  delete fEmPhysicsList;
//  for(size_t i=0; i<fHadronPhys.size(); i++) {
//    delete fHadronPhys[i];
//  }
}

//void PhysicsList::ConstructParticle()
//{
////  fParticleList->ConstructParticle();
//  G4BosonConstructor  pBosonConstructor;
//  pBosonConstructor.ConstructParticle();
//
//  G4LeptonConstructor pLeptonConstructor;
//  pLeptonConstructor.ConstructParticle();
// 
//  G4MesonConstructor pMesonConstructor;
//  pMesonConstructor.ConstructParticle();
// 
//  G4BaryonConstructor pBaryonConstructor;
//  pBaryonConstructor.ConstructParticle();
// 
//  G4IonConstructor pIonConstructor;
//  pIonConstructor.ConstructParticle();
// 
//  G4ShortLivedConstructor pShortLivedConstructor;
//  pShortLivedConstructor.ConstructParticle();
//}

//void PhysicsList::ConstructProcess()
//{
//  AddTransportation();
//  AddPhysicsList("FTFP_BERT_EMV");
////  fEmPhysicsList->ConstructProcess();
////  fParticleList->ConstructProcess();
////  AddDecay();
//  AddRadioactiveDecay();
//  for(size_t i=0; i<fHadronPhys.size(); i++) {
//    fHadronPhys[i]->ConstructProcess();
//  }
//}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

//void PhysicsList::AddPhysicsList(const G4String& name)
//{
//  G4cout<<"AddPhysicsList "<<name<<G4endl;
//
//  if (name == "emstandard_opt0") {
//    delete fEmPhysicsList;
//    fEmPhysicsList = new G4EmStandardPhysics();
//  }
//  else if (name == "emstandard_opt1") {
//    delete fEmPhysicsList;
//    fEmPhysicsList = new G4EmStandardPhysics_option1();
//  }
//  else if (name == "emstandard_opt2") {
//    delete fEmPhysicsList;
//    fEmPhysicsList = new G4EmStandardPhysics_option2();
//  }
//  else if (name == "emstandard_opt3") {
//    delete fEmPhysicsList;
//    fEmPhysicsList = new G4EmStandardPhysics_option3();
//  }
//  else if (name == "emstandard_opt4") {
//    delete fEmPhysicsList;
//    fEmPhysicsList = new G4EmStandardPhysics_option4();
//  }
//  else if (name == "emstandardGS") {
//    delete fEmPhysicsList;
//    fEmPhysicsList = new G4EmStandardPhysicsGS();
//  }
//  else if (name == "FTFP_BERT_EMV") {
//    AddPhysicsList("FTFP_BERT");
//    AddPhysicsList("emstandard_opt1");
//  }
//  else if (name == "FTFP_BERT_EMX") {
//    AddPhysicsList("FTFP_BERT");
//    AddPhysicsList("emstandard_opt2");
//  }
//  else if (name == "FTFP_BERT_EMY") {
//    AddPhysicsList("FTFP_BERT");
//    AddPhysicsList("emstandard_opt3");
//  }
//  else if (name == "FTFP_BERT_EMZ") {
//    AddPhysicsList("FTFP_BERT");
//    AddPhysicsList("emstandard_opt4");
//  }
//  else if (name == "FTFP_BERT") {
//    fHadronPhys.push_back( new G4HadronPhysicsFTFP_BERT());
//  }
//  else if (name == "FTFP_BERT_TRV") {
//    AddPhysicsList("emstandardGS");
//    G4EmParameters::Instance()->SetMscStepLimitType( fUseSafety );
//    fHadronPhys.push_back( new G4HadronPhysicsFTFP_BERT_TRV());
//  }
//  else if (name == "FTF_BIC") {
//    fHadronPhys.push_back( new G4HadronPhysicsFTF_BIC());
//  }
//  else if (name == "QBBC") {
//    AddPhysicsList("emstandard_opt0");
//    fHadronPhys.push_back( new G4HadronInelasticQBBC());
//  }
//  else if (name == "QGSP_BERT") {
//    fHadronPhys.push_back( new G4HadronPhysicsQGSP_BERT());
//  }
//  else if (name == "QGSP_FTFP_BERT") {
//    fHadronPhys.push_back( new G4HadronPhysicsQGSP_FTFP_BERT());
//  }
//  else if (name == "QGSP_FTFP_BERT_EMV") {
//    AddPhysicsList("QGSP_FTFP_BERT");
//    AddPhysicsList("emstandard_opt1");
//  }
//  else if (name == "QGSP_BERT_EMV") {
//    AddPhysicsList("QGSP_BERT");
//    AddPhysicsList("emstandard_opt1");
//  }
//  else if (name == "QGSP_BERT_EMX") {
//    AddPhysicsList("QGSP_BERT");
//    AddPhysicsList("emstandard_opt2");
//  }
//  else if (name == "QGSP_BERT_HP") {
//    fHadronPhys.push_back( new G4HadronPhysicsQGSP_BERT_HP());
//  }
//  else if (name == "QGSP_BIC") {
//    fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC());
//    fHadronPhys.push_back( new G4IonElasticPhysics());
//  }
//  else if (name == "QGSP_BIC_EMY") {
//    AddPhysicsList("QGSP_BIC");
//    AddPhysicsList("emstandard_opt3");
//  }
//  else if (name == "QGS_BIC") {
//    fHadronPhys.push_back( new G4HadronPhysicsQGS_BIC());
//  }
//  else if (name == "QGSP_BIC_HP") {
//    fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC_HP());
//  }
//  else if (name == "RadioactiveDecay") {
//    fHadronPhys.push_back( new G4RadioactiveDecayPhysics());
//  }
//  else {
//    G4cout << "AddPhysicsList " << name << ">"
//           << " is not defined" << G4endl;
//  }
//}

//#include "G4PhysicsListHelper.hh"
//#include "G4Decay.hh"
//void PhysicsList::AddDecay()
//{
//  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
//  // Decay Process
//  G4Decay* fDecayProcess = new G4Decay();
//  auto particleIterator=GetParticleIterator();
//  particleIterator->reset();
//  while( (*particleIterator)() ){
//    G4ParticleDefinition* particle = particleIterator->value();
//    if (fDecayProcess->IsApplicable(*particle))
//      ph->RegisterProcess(fDecayProcess, particle);
//  }
//}
//
//#include "G4PhysicsListHelper.hh"
//#include "G4RadioactiveDecay.hh"
//#include "G4GenericIon.hh"
//#include "G4NuclideTable.hh"
//void PhysicsList::AddRadioactiveDecay()
//{
//  G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
//  radioactiveDecay->SetARM(true);                //Atomic Rearangement
//  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
//  ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
//  // mandatory for G4NuclideTable
//  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1*picosecond);
//}
//
