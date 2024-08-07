#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ThreeVector.hh"
#include <Randomize.hh>
#include "globals.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    MyPrimaryGenerator();
    ~MyPrimaryGenerator();

    virtual void GeneratePrimaries(G4Event *anEvent); // here we want to create the particle gun

private:
    G4ParticleGun *fParticleGun;

    G4long seed = 1;

    G4double x0;
    G4double y0;
    G4double z0;
    G4double xSigma;
    G4double ySigma;
    G4double zSigma;
    G4double beamPipeRadius;
    G4double p0;
    G4double pSigma;
    G4double xangle0;
    G4double yangle0;
    G4double xangleSigma;
    G4double yangleSigma;
    G4double zangleSigma;
    G4double pitch;
    G4double xDirection;
    G4double yDirection;
    G4double zDirection;
};

#endif