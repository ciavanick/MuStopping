#include "construction.h"

MyDetectorConstruction::MyDetectorConstruction()
{
    DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction()
{
}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();

    auto H = nist->FindOrBuildElement(1);
    auto C = nist->FindOrBuildElement(6);
    auto N = nist->FindOrBuildElement(7);
    auto O = nist->FindOrBuildElement(8);
    auto Si = nist->FindOrBuildElement(14);
    auto Ge = nist->FindOrBuildElement(32);
    auto Sb = nist->FindOrBuildElement(51);
    auto I = nist->FindOrBuildElement(53);
    auto Cs = nist->FindOrBuildElement(55);
    auto Pb = nist->FindOrBuildElement(82);
    auto Bi = nist->FindOrBuildElement(83);
    auto Ca = new G4Element("Ca", "Ca", 31, (69.72 * g / mole));
    auto Na = new G4Element("Na", "Na", 11, (22.99 * g / mole));
    auto Mg = new G4Element("Mg", "Mg", 12, (24.305 * g / mole));
    auto K = new G4Element("K", "K", 19, (39.1 * g / mole));
    auto Mn = new G4Element("Mn", "Mn", 25, (54.93 * g / mole));
    auto Zn = new G4Element("Zn", "Zn", 30, (65.38 * g / mole));
    auto Ti = new G4Element("Ti", "Ti", 22, (47.86 * g / mole));
    auto Cr = new G4Element("Cr", "Cr", 24, (51.99 * g / mole));
    auto Al = new G4Element("Al", "Al", 13, (26.98 * g / mole));
    auto Cu = new G4Element("Cu", "Cu", 29, (63.55 * g / mole));
    auto Fe = new G4Element("Fe", "Fe", 26, (55.845 * g / mole));

    Titanium = new G4Material("Titanium", 22, (47.867 * g / mole), (4.54 * g / cm3));

    LiqHe = new G4Material("LiqHe", 2, (4.0 * g / mole), (0.145 * g / cm3));
    Copper = new G4Material("Copper", 29, (63.55 * g / mole), (8.960 * g / cm3));
    Vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    Vacuum2 = new G4Material("Vacuum", 1., (1.01 * g / mole), (1.e-5 * g / cm3), kStateGas, (293 * kelvin), (2.e-10 * bar));
    alMat = nist->FindOrBuildMaterial("G4_Al");

    Scintillator = new G4Material("Scintillator", (1.032 * g / cm3), 2);
    Scintillator->AddElement(H, (8.5 * perCent));  // 14
    Scintillator->AddElement(C, (91.5 * perCent)); // 86
    Scintillator->GetIonisation()->SetMeanExcitationEnergy(64.7 * eV);
    Scintillator->GetIonisation()->SetBirksConstant(0.126 * mm / MeV);

    // General plastic (BC408 scintillator density, used in my simulations)
    Plastic = new G4Material("Plastic", (1.06 * g / cm3), 2); // 1.032 - BC408
    Plastic->AddElement(H, 7.74 * perCent);                   // 14
    Plastic->AddElement(C, 92.26 * perCent);                  // 86

    Mylar = nist->FindOrBuildMaterial("G4_MYLAR");

    nTubs = 3;
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    //-------------------------------------------------
    // Green = LiquidHe
    // Yellow = Copper chamber
    // Magenta = Mylar foils
    // Blue = Plastic scintillator
    // Red = titanium foil
    //-------------------------------------------------

    const auto worldDimX = 500 * mm;
    const auto worldDimY = 500 * mm;
    const auto worldDimZ = 2500 * mm;

    //------------------------------------------------------------------
    // LiqHe
    const auto LiqHeDimX = 0.5 * 54.999 * mm;
    const auto LiqHeDimY = 0.5 * 28.999 * mm;
    const auto LiqHeDimZ = 0.5 * 2.499 * mm;

    const auto LiqHePosX = 0. * mm;
    const auto LiqHePosY = 0. * mm;
    const auto LiqHePosZ = 1.2495 * mm;

    //------------------------------------------------------------------
    // Copper Chamber
    const auto CopperChamberDimX = 0.50 * 5. * mm;
    const auto CopperChamberDimY = 0.50 * 31. * mm;
    const auto CopperChamberDimZ = 0.50 * 62. * mm;

    const auto CopperChamberPosX = -32.5 * mm;
    const auto CopperChamberPosY = 0.;
    const auto CopperChamberPosZ = 18.76399375 * mm;

    auto rotCopperChamber = new G4RotationMatrix();
    rotCopperChamber->rotateX(0 * deg);
    rotCopperChamber->rotateY(-30 * deg);
    rotCopperChamber->rotateZ(0 * deg);

    const auto CopperChamberSubDimX = 0.50 * 5.1 * mm;
    const auto CopperChamberSubDimY = 0.50 * 6. * mm;
    const auto CopperChamberSubDimZ = 0.50 * 12. * mm;

    const auto CopperChamberSubWindowDimX = 0.50 * 0. * mm;
    const auto CopperChamberSubWindowDimY = 0.50 * 1.5 * mm;
    const auto CopperChamberSubWindowDimZ = 0.50 * 5.1 * mm;

    auto rotCopperChambersSubWindow = new G4RotationMatrix();
    rotCopperChambersSubWindow->rotateX(0 * deg);
    rotCopperChambersSubWindow->rotateY(-30 * deg);
    rotCopperChambersSubWindow->rotateZ(0 * deg);
    //------------------------------------------------------------------
    // Titanium foil
    const auto TitaniumFoilDimX = 0.50 * 0.006 * mm;
    const auto TitaniumFoilDimY = 0.50 * 20. * mm;
    const auto TitaniumFoilDimz = 0.50 * 40. * mm;

    const auto TitaniumFoilPosX = -34.0 * mm;
    const auto TitaniumFoilPosY = 0. * mm;
    const auto TitaniumFoilPosZ = 19.62990915 * mm;

    auto rotTitaniumFoil = new G4RotationMatrix();
    rotTitaniumFoil->rotateX(0 * deg);
    rotTitaniumFoil->rotateY(-30 * deg);
    rotTitaniumFoil->rotateZ(0 * deg);

    //------------------------------------------------------------------
    // MyLar Tubes
    std::vector<G4double> MylarFoilsDimInnerRadius({98. * mm, 76. * mm, 54. * mm});
    std::vector<G4double> MylarFoilsDimOuterRadius({98.002 * mm, 76.002 * mm, 54.002 * mm});
    std::vector<G4double> MylarFoilsDimZ({0.50 * 123.0 * mm, 0.50 * 123.0 * mm, 0.50 * 123.0 * mm});

    const auto MylarFoilsPosX = 0. * mm;
    const auto MylarFoilsPosY = 0. * mm;
    const auto MylarFoilsPosZ = 23 * mm;
    //------------------------------------------------------------------
    // Plastic Scintilator

    const auto PlasticScintillatorDimX = 0.50 * 24.99 * mm;
    const auto PlasticScintillatorDimY = 0.50 * 11.99 * mm;
    const auto PlasticScintillatorDimZ = 0.50 * 0.022 * mm;

    const auto PlasticScintillatorPosX = -206. * mm;
    const auto PlasticScintillatorPosY = 0. * mm;
    const auto PlasticScintillatorPosZ = 118.9341555 * mm;

    auto rotPlasticScintillator = new G4RotationMatrix();
    rotPlasticScintillator->rotateX(0 * deg);
    rotPlasticScintillator->rotateY(60 * deg);
    rotPlasticScintillator->rotateZ(0 * deg);
    //------------------------------------------------------------------
    // Collimator Scintilator
    const auto collimatorInnerR = 0.1 * mm;
    const auto collimatorOuterR = 40 * mm;
    const auto collimatorDimZ = 0.50 * 5 * mm;

    const auto collimatorPosX = -209. * mm;
    const auto collimatorPosY = 0. * mm;
    const auto collimatorPosZ = 120.6662063 * mm;

    auto rotCollimator = new G4RotationMatrix();
    rotCollimator->rotateX(0 * deg);
    rotCollimator->rotateY(60 * deg);
    rotCollimator->rotateZ(0 * deg);

    const auto collimatorSubDimX = 0.50 * 25 * mm;
    const auto collimatorSubDimY = 0.50 * 12. * mm;
    const auto collimatorSubDimZ = 0.50 * 5.1 * mm;

    //------------------------------------------------------------------
    // Invisible detector
    const auto InvisibleInnerR = 0 * mm;
    const auto InvisibleOuterR = 60. * mm;
    const auto InvisibleDimZ = 0.5 * 0.00001 * mm;

    const auto InvisiblePosX = -220. * mm;
    const auto InvisiblePosY = 0. * mm;
    const auto InvisiblePosZ = 125.6662063 * mm;

    auto rotInvisible = new G4RotationMatrix();
    rotInvisible->rotateX(0 * deg);
    rotInvisible->rotateY(60 * deg);
    rotInvisible->rotateZ(0 * deg);

    //------------------------------------------------------------------
    // Invisible plastic detector
    const auto PlasticScintillatorInvisibleDimX = 0.50 * 24.99 * mm;
    const auto PlasticScintillatorInvisibleDimY = 0.50 * 11.99 * mm;
    const auto PlasticScintillatorInvisibleDimZ = 0.50 * 0.00001 * mm;

    const auto PlasticScintillatorInvisiblePosX = -35.05 * mm;
    const auto PlasticScintillatorInvisiblePosY = 0. * mm;
    const auto PlasticScintillatorInvisiblePosZ = 22.11399375 * mm + 1 * mm;
    //------------------------------------------------------------------
    // Invisible Mylar detector
    const auto MylarInvisibleInnerR = 97.0 * mm;
    const auto MylarInvisibleOuterR = 97.0001 * mm;
    const auto MylarInvisibleDimZ = 0.50 * 123.0 * mm;

    const auto MylarInvisiblePosX = 0. * mm;
    const auto MylarInvisiblePosY = 0. * mm;
    const auto MylarInvisiblePosZ = 23 * mm;

    //------------------------------------------------------------------

    auto RedVisAtt = new G4VisAttributes(G4Colour(1.0, 0.2, 0.2));
    auto BlueVisAtt = new G4VisAttributes(G4Colour(0.0, 127, 255));
    auto GreenVisAtt = new G4VisAttributes(G4Colour(0.5, 1.0, 0.5));
    auto YellowVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.));
    auto MagentaVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 1.));

    G4VisAttributes *visAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Red color
    visAtt->SetVisibility(true);

    // solid world creation
    solidWorld = new G4Box("solidWorld", worldDimX, worldDimY, worldDimZ);
    logicWorld = new G4LogicalVolume(solidWorld, Vacuum, "logicWorld", nullptr, nullptr, nullptr);
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    // liquid helium block creation
    solidLiqHeBlock = new G4Box("solidLiqHeBlock", LiqHeDimX, LiqHeDimY, LiqHeDimZ);
    logicLiqHeBlock = new G4LogicalVolume(solidLiqHeBlock, LiqHe, "logicLiqHeBlock");
    logicLiqHeBlock->SetVisAttributes(GreenVisAtt);
    physLiqHeMat = new G4PVPlacement(0, G4ThreeVector(LiqHePosX, LiqHePosY, LiqHePosZ), logicLiqHeBlock, "physLiqHeMat", logicWorld, false, 0, true);

    // copper chamber creation
    solidCopperChamber = new G4Box("solidCopperChamber", CopperChamberDimX, CopperChamberDimY, CopperChamberDimZ);
    solidCopperSubChamber = new G4Box("solidCopperSubChamber", CopperChamberSubDimX, CopperChamberSubDimY, CopperChamberSubDimZ);
    G4SubtractionSolid *SubCopperSubChamber = new G4SubtractionSolid("SubCopperSubChamber", solidCopperChamber, solidCopperSubChamber, 0, G4ThreeVector(0. * m, 0. * m, 0. * m));
    logicCopperChamber = new G4LogicalVolume(SubCopperSubChamber, Copper, "logicCopperChamber");
    logicCopperChamber->SetVisAttributes(YellowVisAtt);
    physCopperChamber = new G4PVPlacement(rotCopperChamber, G4ThreeVector(CopperChamberPosX, CopperChamberPosY, CopperChamberPosZ), logicCopperChamber, "physCopperChamber", logicWorld, false, 0, true);

    // collimator
    solidCollimator = new G4Tubs("solidCollimator", collimatorInnerR, collimatorOuterR, collimatorDimZ, 0 * deg, 360 * deg);
    solidCollimatorSub = new G4Box("solidCollimator", collimatorSubDimX, collimatorSubDimY, collimatorSubDimZ);
    G4SubtractionSolid *SubCollimator = new G4SubtractionSolid("SubCollimator", solidCollimator, solidCollimatorSub, 0, G4ThreeVector(0., 0., 0.));
    logicCollimator = new G4LogicalVolume(SubCollimator, Copper, "logicCollimator");
    physCollimator = new G4PVPlacement(rotCollimator, G4ThreeVector(collimatorPosX, collimatorPosY, collimatorPosZ), logicCollimator, "physCollimator", logicWorld, false, 0, true);

    // titanium foil creation
    solidTitaniumFoil = new G4Box("solidTitaniumFoil", TitaniumFoilDimX, TitaniumFoilDimY, TitaniumFoilDimz);
    logicTitaniumFoil = new G4LogicalVolume(solidTitaniumFoil, Titanium, "logicTitaniumFoil");
    logicTitaniumFoil->SetVisAttributes(RedVisAtt);
    physTitaniumFoil = new G4PVPlacement(rotTitaniumFoil, G4ThreeVector(TitaniumFoilPosX, TitaniumFoilPosY, TitaniumFoilPosZ), logicTitaniumFoil, "physTitaniumFoil", logicWorld, false, 0, true);

    // Mylar tubes creation
    for (G4int i = 0; i != nTubs; ++i)
    {
        solidMylarFoils[i] = new G4Tubs("solidMylarFoils", MylarFoilsDimInnerRadius[i], MylarFoilsDimOuterRadius[i], MylarFoilsDimZ[i], 0 * deg, 360 * deg);
        logicMylarFoils = new G4LogicalVolume(solidMylarFoils[i], Mylar, "logicMylarFoils");
        logicMylarFoils->SetVisAttributes(MagentaVisAtt);
        physMylarFoils = new G4PVPlacement(0, G4ThreeVector(MylarFoilsPosX, MylarFoilsPosY, MylarFoilsPosZ), logicMylarFoils, "physMylarFoils", logicWorld, false, i, true);
    }

    // scintillator creation
    solidPlasticScintillator = new G4Box("solidPlasticScintillator", PlasticScintillatorDimX, PlasticScintillatorDimY, PlasticScintillatorDimZ);
    logicPlasticScintillator = new G4LogicalVolume(solidPlasticScintillator, Scintillator, "logicPlasticScintillator");
    logicPlasticScintillator->SetVisAttributes(BlueVisAtt);
    physPlasticScintillator = new G4PVPlacement(rotPlasticScintillator, G4ThreeVector(PlasticScintillatorPosX, PlasticScintillatorPosY, PlasticScintillatorPosZ), logicPlasticScintillator, "physPlasticScintillator", logicWorld, false, 0, true);

    // invisible detector
    solidInvisible = new G4Tubs("solidInvisible", InvisibleInnerR, InvisibleOuterR, InvisibleDimZ, 0 * deg, 360 * deg);
    logicInvisible = new G4LogicalVolume(solidInvisible, Vacuum, "logicInvisible");
    physInvisible = new G4PVPlacement(rotInvisible, G4ThreeVector(InvisiblePosX, InvisiblePosY, InvisiblePosZ), logicInvisible, "physInvisible", logicWorld, false, 0, true);

    // scintillator creation
    solidPlasticScintillatorInvisible = new G4Box("solidPlasticScintillatorInvisible", PlasticScintillatorInvisibleDimX, PlasticScintillatorInvisibleDimY, PlasticScintillatorInvisibleDimZ);
    logicPlasticScintillatorInvisible = new G4LogicalVolume(solidPlasticScintillatorInvisible, Vacuum, "logicPlasticScintillatorInvisible");
    physPlasticScintillatorInvisible = new G4PVPlacement(rotPlasticScintillator, G4ThreeVector(PlasticScintillatorInvisiblePosX, PlasticScintillatorInvisiblePosY, PlasticScintillatorInvisiblePosZ), logicPlasticScintillatorInvisible, "physPlasticScintillatorInvisible", logicWorld, false, 0, true);

    // Mylar invisible
    solidMylarInvisible = new G4Tubs("solidMylarInvisible", MylarInvisibleInnerR, MylarInvisibleOuterR, MylarInvisibleDimZ, 0 * deg, 360 * deg);
    logicMylarInvisible = new G4LogicalVolume(solidMylarInvisible, Vacuum, "logicMylarInvisible");
    physMylarInvisible = new G4PVPlacement(0, G4ThreeVector(MylarInvisiblePosX, MylarInvisiblePosY, MylarInvisiblePosZ), logicMylarInvisible, "physMylarInvisible", logicWorld, false, 0, true);

    return physWorld;
}
