#ifndef DETECTOR_HH
#define DETECTOR_HH

// MySD.hh
#include "G4VSensitiveDetector.hh"

class G4Step;
class G4TouchableHistory;

class MySD : public G4VSensitiveDetector {
public:
    MySD(const G4String& name);
    virtual ~MySD();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    virtual void Initialize(G4HCofThisEvent* hce) override;
    virtual void EndOfEvent(G4HCofThisEvent* hce) override;

private:
    G4int fHitsCollectionID;
    G4HCofThisEvent* fHCofThisEvent;
};


#endif
