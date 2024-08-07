#include "generator.h"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    G4int nOfParticles = 1;
    fParticleGun = new G4ParticleGun(nOfParticles); // inside G4ParticleGun we have the number of particles per event, one run contains several events and each event can contain several particle, here just 1 particle (one vertex per event)

    // particle definition
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName = "mu+";
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

    fParticleGun->SetParticleDefinition(particle);

    // initializing the mean spatial points
    x0 = -230 * mm;
    y0 = 0. * mm;
    z0 = 132.7905619 * mm;

    // initializing the sigmas for spatial points
    xSigma = 6 * mm;
    ySigma = 7 * mm;
    zSigma = 0.;

    // setting the beamPipeRadius
    beamPipeRadius = 1e10 * mm;

    // initializing the mean momentum distribution
    p0 = 12.5 * MeV;

    // initializing the sigma for the momentum
    pSigma = 0.152866242 * MeV;

    // initializing the angles for the momentum
    xangle0 = 0.;
    yangle0 = 0.;

    // initializing the sigma of the momentum
    xangleSigma = 0.;
    yangleSigma = 0.;
    zangleSigma = 0.;

    // directions
    xDirection = 0.866;
    yDirection = 0.;
    zDirection = -0.5;

    //pitch
    pitch = 0;
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) // here we want to create the particle gun
{

    G4double x, y, z;
    G4double p, px, py, pz;
    G4double xangle, yangle;
    G4double sinXangle, sinYangle;

    G4int checkNrOfCounts = 0;
    G4double r = 0;
    do
    {
        if (xSigma > 0)
        {
            x = G4RandGauss::shoot(x0, xSigma);
        } //  Gaussian distribution
        else if (xSigma < 0)
        {
            x = x0 + xSigma * (G4UniformRand() * 2. - 1.);
        } //  Uniform step distribution
        else
        {
            x = x0;
        } //  Point-like

        if (ySigma > 0)
        {
            y = G4RandGauss::shoot(y0, ySigma);
        }
        else if (ySigma < 0)
        {
            y = y0 + ySigma * (G4UniformRand() * 2. - 1.);
        }
        else
        {
            y = y0;
        }

        if (zSigma > 0)
        {
            z = G4RandGauss::shoot(z0, zSigma);
        }
        else if (zSigma < 0)
        {
            z = z0 + zSigma * (G4UniformRand() * 2. - 1.);
        }
        else
        {
            z = z0;
        }
        checkNrOfCounts++;
        if (checkNrOfCounts > 1000)
        {
            G4cout
                << "musrPrimaryGeneratorAction::GeneratePrimaries:  Too strict requirements on the r or z position!"
                << G4endl;
        }
        // The generated muon has to stay within some well defined region,  e.g. within the beampipe

        auto x2 = (x - x0) * (x - x0);
        auto y2 = (y - y0) * (y - y0);
        r = std::sqrt(x2 + y2);
    } while (r > beamPipeRadius);

    // Gaussian distribution for the p
    if (pSigma > 0)
    {
        p = G4RandGauss::shoot(p0, pSigma);
    }
    else
    {
        p = p0;
    }
    if (xangleSigma > 0)
    {
        xangle = G4RandGauss::shoot(xangle0, xangleSigma);
    }
    else
    {
        xangle = xangle0;
    }
    //  Add the beam tilt, which depends on the distance from the beam centre.
    if (pitch != 0)
    {
        xangle += -pitch * (x - x0);
    }

    if (yangleSigma > 0)
    {
        yangle = G4RandGauss::shoot(yangle0, yangleSigma);
    }
    else
    {
        yangle = yangle0;
    }
    //  Add the beam tilt, which depends on the distance from the beam centre.
    if (pitch != 0)
    {
        yangle += -pitch * (y - y0);
    }

    // Initial angle (px and py component of the momentum)
    xangle = G4RandGauss::shoot(xangle0, xangleSigma);
    yangle = G4RandGauss::shoot(yangle0, yangleSigma);

    sinXangle = std::sin(xangle);
    sinYangle = std::sin(yangle);
    px = p * sinXangle;
    py = p * sinYangle;
    pz = std::sqrt(p * p - px * px - py * py);

    if ((xDirection == 0) && (yDirection == 0))
    {
        // Rotation does not work for beam direction along z.
        pz = zDirection * pz;
        // No change to the beam spot...
    }
    else
    {
        auto pRot = new G4ThreeVector(px, py, pz);
        pRot->rotate(std::acos(zDirection), G4ThreeVector(-yDirection, xDirection, 0));
        px = pRot->x();
        py = pRot->y();
        pz = pRot->z();

        // Rotate also beam spot
        auto rRot = new G4ThreeVector(x - x0, y - y0, z - z0);
        rRot->rotate(std::acos(zDirection), G4ThreeVector(-yDirection, xDirection, 0));
        x = x0 + rRot->x();
        y = y0 + rRot->y();
        z = z0 + rRot->z();
    }
    fParticleGun->SetParticlePosition(G4ThreeVector(x, y, z));
    G4double particle_mass = fParticleGun->GetParticleDefinition()->GetPDGMass();
    G4cout<< "Particle mass : "<< particle_mass << "\n";
    G4double particleEnergy = std::sqrt(p * p + particle_mass * particle_mass) - particle_mass;
    fParticleGun->SetParticleEnergy(particleEnergy);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px, py, pz));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}