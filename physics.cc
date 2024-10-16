#include "physics.hh"

MyPhysicsList::MyPhysicsList(){

	// Electromagnetic Physics
   	RegisterPhysics(new G4EmStandardPhysics());

   	// Hadronic Physics using QGSP_BIC_HP
   	RegisterPhysics(new G4HadronPhysicsQGSP_BERT_HP());

   	// Decay Physics
   	RegisterPhysics(new G4DecayPhysics());
}

MyPhysicsList::~MyPhysicsList() {}
