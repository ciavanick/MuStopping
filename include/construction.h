#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GenericMessenger.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"
//------------------------------------------------
#include "G4SystemOfUnits.hh" //system of units

#include <vector>

class MyDetectorConstruction : public G4VUserDetectorConstruction // user detector construction class implemented in geant4
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    virtual G4VPhysicalVolume *Construct(); // all the description of the detector must be put in that function
private:
    G4Material *Vacuum, *Vacuum2, *alMat, *LiqHe, *Copper, *Scintillator, *Plastic, *Titanium, *Mylar;
    G4Box *solidWorld, *solidAlBlock, *solidLiqHeBlock, *solidCopperChamber, *solidTitaniumFoil, *solidPlasticScintillator;
    G4Box *solidCopperSubChamber, *solidCopperWindowsChamber, *solidCollimatorSub, *solidPlasticScintillatorInvisible;
    // G4SubtractionSolid *SubCopperSubChamber, SubCopperWindowsChamber;
    G4Tubs *solidMylarFoils[3], *solidCollimator, *solidInvisible, *solidMylarInvisible;
    G4int nTubs;
    G4LogicalVolume *logicWorld, *logicAlBlock, *logicLiqHeBlock, *logicCopperChamber, *logicTitaniumFoil, *logicMylarFoils, *logicPlasticScintillator, *logicCollimator, *logicInvisible, *logicPlasticScintillatorInvisible, *logicMylarInvisible;
    G4VPhysicalVolume *physWorld, *physAlMat, *physLiqHeMat, *physCopperChamber, *physTitaniumFoil, *physMylarFoils, *physPlasticScintillator, *physCollimator, *physInvisible, *physPlasticScintillatorInvisible, *physMylarInvisible;
    G4RotationMatrix *rotation;
    G4GenericMessenger *fMessenger;
    void DefineMaterials();
};

#endif