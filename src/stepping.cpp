#include "stepping.h"

MySteppingAction::MySteppingAction() = default;

MySteppingAction::~MySteppingAction() = default;

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
    
   G4AnalysisManager *man = G4AnalysisManager::Instance();

    const auto track = step->GetTrack();
    const auto &partName = track->GetDefinition()->GetParticleName();
    const auto &physVolume = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    //const auto globalTime = step->GetPreStepPoint()->GetGlobalTime() / ns;
    const auto kinE = step->GetPreStepPoint()->GetKineticEnergy();
    G4ThreeVector momentum = track->GetDynamicParticle()->GetMomentum();
    const auto p = std::sqrt(momentum.x()*momentum.x() + momentum.y()*momentum.y() + momentum.z()*momentum.z());
    const auto stepNb = track->GetCurrentStepNumber();
    const auto parentID = track->GetParentID();
    const auto trackStatus = track->GetTrackStatus();
    const auto currentEvent = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    const auto stopCondition = ((trackStatus == fStopButAlive) || (trackStatus == fStopAndKill) || (trackStatus == fSuspend)); //stopping condition
    if((parentID == 0) && stopCondition == true)
    {
        const auto range = std::abs(-500 - track->GetPosition().z()/ mm);
        man->FillNtupleDColumn(0, 0, track->GetPosition().x()/ mm); //x posirion in cm
        man->FillNtupleDColumn(0, 1, track->GetPosition().y()/ mm); //y posirion in cm
        man->FillNtupleDColumn(0, 2, track->GetPosition().z()/ mm); //z posirion in cm
        man->FillNtupleDColumn(0, 3, range); //z posirion in cm
        man->FillNtupleIColumn(0, 4, (physVolume == "physLiqHeMat")); //check if the volume is LiqHe
        man->FillNtupleIColumn(0, 5, (physVolume == "physCopperChamber")); //check if the volume is the copper chamber
        man->FillNtupleIColumn(0, 6, (physVolume == "physCollimator")); //check if the volume is the collimator
        man->FillNtupleIColumn(0, 7, (physVolume == "physTitaniumFoil")); //check if the volume is Titanium fol
        man->FillNtupleIColumn(0, 8, (physVolume == "physMylarFoils")); //check if the volume is Mylar foils
        man->FillNtupleIColumn(0, 9, (physVolume == "physPlasticScintillator")); //check if the volume is Plastic scintillator
        man->FillNtupleIColumn(0, 10, stepNb); //retrieve the step number
        man->FillNtupleIColumn(0, 11, currentEvent); //Save the eventID
        man->AddNtupleRow(0);
    }

    if(parentID == 1 && stepNb == 1){
        man->FillNtupleDColumn(1, 0, track->GetPosition().x()/ mm); //x posirion in cm
        man->FillNtupleDColumn(1, 1, track->GetPosition().y()/ mm); //y posirion in cm
        man->FillNtupleDColumn(1, 2, track->GetPosition().z()/ mm); //z posirion in cm
        man->FillNtupleIColumn(1, 3, (partName == "e-")); //check if the particle is an electron
        man->FillNtupleIColumn(1, 4, 1); //count the total number of secondary particles
        man->FillNtupleDColumn(1, 5, kinE); //get kinetic energy
        man->FillNtupleIColumn(1, 6, currentEvent); //Save the eventID
        man->AddNtupleRow(1);
    }

    if((parentID == 1) && stopCondition == true)
    {
        man->FillNtupleDColumn(2, 0, track->GetPosition().x()/ mm); //x posirion in cm
        man->FillNtupleDColumn(2, 1, track->GetPosition().y()/ mm); //y posirion in cm
        man->FillNtupleDColumn(2, 2, track->GetPosition().z()/ mm); //z posirion in cm
        man->FillNtupleIColumn(2, 3, (physVolume == "physAlMat")); //check if the volume is Aluminium
        man->FillNtupleIColumn(2, 4, (partName == "e-")); //check if the particle stopped is an electron
        man->FillNtupleIColumn(2, 5, 1); //count all secondary particles that stops
        man->FillNtupleIColumn(2, 5, stepNb); //retrieve the step number
        man->FillNtupleIColumn(2, 6, currentEvent); //Save the eventID
        man->AddNtupleRow(2);
    }

    if((parentID == 0) && physVolume == "physInvisible")
    {
        man->FillNtupleDColumn(3, 0, kinE); 
        man->FillNtupleDColumn(3, 1, p); 
        man->AddNtupleRow(3);
    }

    if((parentID == 0) && physVolume == "physPlasticScintillatorInvisible")
    {
        man->FillNtupleDColumn(4, 0, kinE); 
        man->FillNtupleDColumn(4, 1, p); 
        man->AddNtupleRow(4);
    }

    if((parentID == 0) && physVolume == "physMylarInvisible")
    {
        man->FillNtupleDColumn(5, 0, kinE); 
        man->FillNtupleDColumn(5, 1, p); 
        man->AddNtupleRow(5);
    }
    
    
}