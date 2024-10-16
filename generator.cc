#include "generator.hh"
#include "G4Proton.hh"
#include "G4Alpha.hh"
#include "G4IonTable.hh"
#include "G4GeneralParticleSource.hh"

MyPrimaryGenerator::MyPrimaryGenerator() {
	gps = new G4GeneralParticleSource;
}

MyPrimaryGenerator::~MyPrimaryGenerator(){
	delete gps;
} 

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
    G4cout << "Generating primary particles from the GPS setup..." << G4endl;
    gps->GeneratePrimaryVertex(anEvent);  // This actually triggers the GPS to generate the particles as per the setup
}

