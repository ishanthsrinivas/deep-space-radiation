#include <iostream>
#include "G4TrajectoryDrawByParticleID.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv){

	//runManager, detectorConstruction and physics list
	G4RunManager *runManager = new G4RunManager();
	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	runManager->Initialize();
	
	
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	UImanager->ApplyCommand("/vis/open OGL");
	UImanager->ApplyCommand("/vis/drawVolume");
	UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
	UImanager->ApplyCommand("/vis/show/trajectories true");
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
	UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
	UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID");
	UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set proton red");
	UImanager->ApplyCommand("/vis/modeling/trajectories/drawByParticleID-0/set alpha blue");
	
	ui->SessionStart();
	
	return 0;

}
