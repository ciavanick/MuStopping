#include "run.h"

MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->CreateNtuple("t1", "all data for primary muons here");
    man->CreateNtupleDColumn("fPosX");
    man->CreateNtupleDColumn("fPosY");
    man->CreateNtupleDColumn("fPosZ");
    man->CreateNtupleDColumn("fPosZrange");
    man->CreateNtupleIColumn("StopInLiqHe");
    man->CreateNtupleIColumn("StopInCopperChamber");
    man->CreateNtupleIColumn("StopInCollimator");
    man->CreateNtupleIColumn("StopInTitaniumFoil");
    man->CreateNtupleIColumn("StopInMylarFoils");
    man->CreateNtupleIColumn("StopInPlasticScintillator");
    man->CreateNtupleIColumn("StepNumber");
    man->CreateNtupleIColumn("fEventID");
    man->FinishNtuple(0);

    man->CreateNtuple("t2", "all data for electron here");
    man->CreateNtupleDColumn("fPosX");
    man->CreateNtupleDColumn("fPosY");
    man->CreateNtupleDColumn("fPosZ");
    man->CreateNtupleIColumn("fElectrons");
    man->CreateNtupleIColumn("fNumOfSecondary");
    man->CreateNtupleDColumn("fKinEnergy");
    man->CreateNtupleIColumn("fEventID");
    man->FinishNtuple(1);

    man->CreateNtuple("t3", "all data for electron absorbed here");
    man->CreateNtupleDColumn("fPosX");
    man->CreateNtupleDColumn("fPosY");
    man->CreateNtupleDColumn("fPosZ");
    man->CreateNtupleIColumn("StopInAl");
    man->CreateNtupleIColumn("fElectronsStop");
    man->CreateNtupleIColumn("fNumOfSecondaryStop");
    man->CreateNtupleIColumn("StepNumber");
    man->CreateNtupleIColumn("fEventID");
    man->FinishNtuple(2);

    man->CreateNtuple("t4", "all data for crosscheck here");
    man->CreateNtupleDColumn("fKinEnergy");
    man->CreateNtupleDColumn("fMomentum");
    man->FinishNtuple(3);

    man->CreateNtuple("t5", "all data for crosscheck here");
    man->CreateNtupleDColumn("fKinEnergy");
    man->CreateNtupleDColumn("fMomentum");
    man->FinishNtuple(4);

    man->CreateNtuple("t6", "all data for crosscheck here");
    man->CreateNtupleDColumn("fKinEnergy");
    man->CreateNtupleDColumn("fMomentum");
    man->FinishNtuple(5);



}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile("output" + strRunID.str() + ".root");
}

void MyRunAction::EndOfRunAction(const G4Run *)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}