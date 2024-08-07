#include "physics.h"

MyPhysicsList::MyPhysicsList()
{
    //RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4EmLowEPPhysics());
}

MyPhysicsList::~MyPhysicsList() {}
