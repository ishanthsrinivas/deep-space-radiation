// MySD.cc
#include "detector.hh"
#include "hit.hh"
#include "G4VHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4THitsCollection.hh"

MySD::MySD(const G4String& name) 
    : G4VSensitiveDetector(name), fHitsCollectionID(-1) {
    collectionName.insert("MyHitCollection");
}

MySD::~MySD() {}

void MySD::Initialize(G4HCofThisEvent* hce) {
    fHCofThisEvent = hce;

    auto hitsCollection = new G4THitsCollection<MyHit>(SensitiveDetectorName, collectionName[0]);
    if (fHitsCollectionID < 0) {
        fHitsCollectionID = GetCollectionID(0);
    }
    hce->AddHitsCollection(fHitsCollectionID, hitsCollection);
}

G4bool MySD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4double edep = step->GetTotalEnergyDeposit();
    if (edep == 0.) return false;

    auto hit = new MyHit();
    hit->SetEdep(edep);
    hit->SetPos(step->GetPreStepPoint()->GetPosition());

    auto hitsCollection = static_cast<G4THitsCollection<MyHit>*>(fHCofThisEvent->GetHC(fHitsCollectionID));
    hitsCollection->insert(hit);

    return true;
}

void MySD::EndOfEvent(G4HCofThisEvent*) {
    // Can do any post-processing of hits here
}

