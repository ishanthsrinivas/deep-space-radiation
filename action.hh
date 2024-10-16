#include "G4VUserActionInitialization.hh"
#include "generator.hh"

#ifndef ACTION_HH
#define ACTION_HH

class MyActionInitialization : public G4VUserActionInitialization{
	public:
		MyActionInitialization();
		~MyActionInitialization();
		
	virtual void Build() const;

};


#endif
