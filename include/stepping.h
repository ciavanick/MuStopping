#ifndef STEPPING_HH
#define STEPPING_HH

#include <G4UserSteppingAction.hh>
#include <G4SteppingManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4EventManager.hh>
#include <G4Event.hh>
#include <G4RootAnalysisManager.hh>
#include <G4RunManager.hh>



#include "run.h"

class MySteppingAction : public G4UserSteppingAction
{
public:
    MySteppingAction();
    ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step*) override;
};

#endif