#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
: logicDetector1(nullptr), logicDetector2(nullptr)
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {

    G4NistManager* nist = G4NistManager::Instance();
    
    // Mother volume
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
    if(!worldMat) {
        G4cerr << "Error: World material (G4_AIR) not found!" << G4endl;
        return nullptr;
    }

    G4Box* solidWorld = new G4Box("solidWorld", 1.0*m, 1.0*m, 1.0*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    // Layer 1: Water
    G4Material* lightMat = nist->FindOrBuildMaterial("G4_WATER");
    if(!lightMat) {
        G4cerr << "Error: Light material (G4_WATER) not found!" << G4endl;
        return nullptr;
    }

    G4Box* solidLight = new G4Box("solidLight", 0.1*m, 0.1*m, 0.01*m);
    G4LogicalVolume* logicLight = new G4LogicalVolume(solidLight, lightMat, "logicLight");
    G4VPhysicalVolume* physLight = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.3*m), logicLight, "physLight", logicWorld, false, 0, true);

    // Layer 2: Boron Carbide
    G4Material* heavyMat = nist->FindOrBuildMaterial("G4_BORON_CARBIDE");
    if(!heavyMat) {
        G4cerr << "Error: Heavy material (G4_BORON_CARBIDE) not found!" << G4endl;
        return nullptr;
    }

    G4Box* solidHeavy = new G4Box("solidHeavy", 0.1*m, 0.1*m, 0.005*m);
    G4LogicalVolume* logicHeavy = new G4LogicalVolume(solidHeavy, heavyMat, "logicHeavy");
    G4VPhysicalVolume* physHeavy = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.5*m), logicHeavy, "physHeavy", logicWorld, false, 0, true);

   // Detector layer 1 (in front of light)
    G4Box* solidDetector1 = new G4Box("solidDetector1", 0.1*m, 0.1*m, 0.005*m);
    logicDetector1 = new G4LogicalVolume(solidDetector1, worldMat, "logicDetector1");
    
    for(G4int i = 0; i < 100; i++) {
        for(G4int j = 0; j < 100; j++) {
            new G4PVPlacement(0, G4ThreeVector(-0.005*m+(i+0.01)*0.001*m, -0.005*m+(j+0.01)*0.001*m, 0.20*m), logicDetector1, "physDetector1", logicWorld, false, j+i*100, true);
        }
    }

    // Detector layer 2 (under light)
    G4Box* solidDetector2 = new G4Box("solidDetector2", 0.01*m, 0.01*m, 0.01*m);
    logicDetector2 = new G4LogicalVolume(solidDetector2, worldMat, "logicDetector2");
    
    for(G4int i = 0; i < 10; i++) {
        for(G4int j = 0; j < 10; j++) {
            new G4PVPlacement(0, G4ThreeVector(-0.005*m+(i+0.01)*0.001*m, -0.005*m+(j+0.01)*0.001*m, 0.40*m), logicDetector2, "physDetector2", logicWorld, false, j+i*100, true);
        }
    }

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
    MySD* sensDet = new MySD("SensitiveDetector");
    
    if(logicDetector1) {
        logicDetector1->SetSensitiveDetector(sensDet);
    } else {
        G4cerr << "Error: logicDetector1 not initialized!" << G4endl;
    }
    
    if(logicDetector2) {
        logicDetector2->SetSensitiveDetector(sensDet);
    } else {
        G4cerr << "Error: logicDetector2 not initialized!" << G4endl;
    }
}
