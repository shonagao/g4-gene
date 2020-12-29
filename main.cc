#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "ParamManager.hh"
#include "Analysis.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "PhysicsList.hh"

//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"
//#else
//#include "G4RunManager.hh"
//#endif
#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"

#include "GetRandomSeed.hh"
#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  G4String runID = "0000";
  G4String InputFileName = "param/input.in";
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }
  else if ( argc == 3 ) {
    runID = argv[2];
  }
  else if ( argc == 4 ) {
    runID = argv[2];
    InputFileName = argv[3];
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  int initSeed=GetIntFromKernelEntropyPool()&0x7FFFFFFF;
  CLHEP::HepRandom::setTheSeed(initSeed);
  int startSeed=CLHEP::HepRandom::getTheSeed();
  G4cout << "Initial Seed = " << startSeed << G4endl;
  CLHEP::HepRandom::showEngineStatus();

  // Construct the default run manager
  std::cout<<"Run Manager"<<std::endl;
  G4RunManager* runManager = new G4RunManager;
/*
#ifdef G4MULTITHREADED  
  G4MTRunManager* runManager = new G4MTRunManager;
  std::cout<<"multi thread"<<std::endl;
#else
  G4RunManager* runManager = new G4RunManager;
#endif
*/

  // Parameter Manager
  ParamManager *paramManager = new ParamManager(runID, InputFileName);

  // Set mandatory initialization classes
  std::cout<<"Detector Construction"<<std::endl;
  runManager->SetUserInitialization(new DetectorConstruction());

  std::cout<<"Physics List"<<std::endl;
  PhysicsList *physicsList = new PhysicsList();
//  G4VModularPhysicsList* physicsList = new FTFP_BERT;
//  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);
    
  //analyzer
  Analysis *anaManager = new Analysis();

  // Set user action classes
  runManager->SetUserInitialization(new ActionInitialization(anaManager));

  // Initialize visualization
  std::cout<<"Vis Manager"<<std::endl;
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  std::cout<<"UI Manager"<<std::endl;
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    std::cout<<"batch mode"<<std::endl;
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    std::cout<<"execute macro/init_vis.mac"<<std::endl;
    UImanager->ApplyCommand("/control/execute macro/init_vis.mac");
    if (ui->IsGUI()) {
      G4cout<<"execute macro/gui.mac"<<G4endl;
      UImanager->ApplyCommand("/control/execute macro/gui.mac");
    }
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !
  
  delete visManager;
  delete paramManager;
  delete anaManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
