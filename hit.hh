

#ifndef HIT_HH
#define HIT_HH

// MyHit.hh
#include "G4VHit.hh"
#include "G4ThreeVector.hh"

class MyHit : public G4VHit {
public:
    MyHit();
    virtual ~MyHit();

    void SetEdep(G4double ed) { fEdep = ed; }
    G4double GetEdep() const { return fEdep; }

    void SetPos(G4ThreeVector pos) { fPos = pos; }
    G4ThreeVector GetPos() const { return fPos; }

private:
    G4double fEdep;
    G4ThreeVector fPos;
};


#endif
