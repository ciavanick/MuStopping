#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"

#include "construction.h"
#include "physics.h"
#include "action.h"

int main(int argc, char **argv)
{
    G4RunManager *runManager = new G4RunManager(); // G4RunManager is the toolkit class that takes care of the program execution and manages the information of a Run

    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

    runManager->Initialize();

    G4UIExecutive *ui = 0;
    if (argc == 1)
    {
        ui = new G4UIExecutive(argc, argv); // ui manager
    }

    G4VisManager *visManager = new G4VisExecutive(); // vis excetutive
    visManager->Initialize();
    G4UImanager *UImanager = G4UImanager::GetUIpointer(); // User iterface manager creation

    if (ui)
    {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    }
    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

    return 0;
}