void analysis(Int_t count = 0, TString rootFilePath = "build/output0.root")
{
    gStyle->SetOptStat(1111);

    TTree *t1, *t2, *t3 = new TTree();
    TFile *file = new TFile(rootFilePath, "read");
    // retrieving the tree
    t1 = (TTree *)file->Get("t1");
    // defining all the branches variables
    Double_t fPosX, fPosY, fPosZ;
    Int_t StopInLiqHe, StopInCopperChamber, StopInCollimator, StopInTitaniumFoil, StopInMylarFoils, StopInPlasticScintillator;
    Int_t nOfStopInLiqHe = 0;
    Int_t nOfStopInCopperChamber = 0;
    Int_t nOfStopInCollimator = 0;
    Int_t nOfStopInTitaniumFoil = 0;
    Int_t nOfStopInMylarFoils = 0;
    Int_t nOfStopInPlasticScintillator = 0;
    Int_t nOfTotalStops = 0;

    // setting the branch addresses for t1
    t1->SetBranchAddress("fPosX", &fPosX);
    t1->SetBranchAddress("fPosY", &fPosY);
    t1->SetBranchAddress("fPosZ", &fPosZ);
    t1->SetBranchAddress("StopInLiqHe", &StopInLiqHe);
    t1->SetBranchAddress("StopInCopperChamber", &StopInCopperChamber);
    t1->SetBranchAddress("StopInCollimator", &StopInCollimator);
    t1->SetBranchAddress("StopInTitaniumFoil", &StopInTitaniumFoil);
    t1->SetBranchAddress("StopInMylarFoils", &StopInMylarFoils);
    t1->SetBranchAddress("StopInPlasticScintillator", &StopInPlasticScintillator);

    auto nEntries = static_cast<Int_t>(t1->GetEntries());
    // TH3F *hT1Pos = new TH3F("hT1Pos", "Stopping distribution", 2000, -1000., +1000., 2000, -1000., +1000., 2000, -1000., +1000.);
    TH1F *hT1PosX = new TH1F("hT1PosX", "Stopping distribution", 20000, -500., +500.);
    // TH1F *hT1PosStopping = new TH1F("hT1PosStopping", "Stopping distribution", 10000, 0.013, +0.0155);
    TH1F *hT1PosY = new TH1F("hT1PosY", "Stopping distribution", 20000, -500., +500.);
    TH1F *hT1PosZ = new TH1F("hT1PosZ", "Stopping distribution", 20000, -500., +500.);
    TH2F *hT1PosXZ = new TH2F("hT1PosXZ", "Stopping distribution", 20000, -500., +500., 20000, -500., +500.);
    TH2F *hT1PosXY = new TH2F("hT1PosXY", "Stopping distribution", 20000, -500., +500., 20000, -500., +500.);
    for (Int_t i = 0; i != nEntries; ++i)
    {
        t1->GetEntry(i);
        // Filling the histograms with only the stopped tracks
        if (StopInLiqHe == 1)
        {
            ++nOfStopInLiqHe;
            hT1PosX->Fill(fPosX);
            hT1PosY->Fill(fPosY);
            hT1PosZ->Fill(fPosZ);
            hT1PosXZ->Fill(fPosX, fPosZ);
            hT1PosXY->Fill(fPosX, fPosY);
        }
        else if (StopInCopperChamber == 1)
        {
            ++nOfStopInCopperChamber;
        }
        else if (StopInCollimator == 1)
        {
            ++nOfStopInCollimator;
        }
        else if (StopInTitaniumFoil == 1)
        {
            ++nOfStopInTitaniumFoil;
        }
        else if (StopInMylarFoils == 1)
        {
            ++nOfStopInMylarFoils;
        }
        else if (StopInPlasticScintillator == 1)
        {
            ++nOfStopInPlasticScintillator;
        }
        ++nOfTotalStops;
    }
    // converting counters from int to double
    auto StopInLiqHeD = static_cast<Double_t>(nOfStopInLiqHe);
    auto nOfStopInCopperChamberD = static_cast<Double_t>(nOfStopInCopperChamber);
    auto nOfStopInCollimatorD = static_cast<Double_t>(nOfStopInCollimator);
    auto nOfStopInTitaniumFoilD = static_cast<Double_t>(nOfStopInTitaniumFoil);
    auto nOfStopInMylarFoilsD = static_cast<Double_t>(nOfStopInMylarFoils);
    auto nOfStopInPlasticScintillatorD = static_cast<Double_t>(nOfStopInPlasticScintillator);
    auto nOfTotalStopsD = static_cast<Double_t>(nOfTotalStops);
    // computing the percentage of stopped muons
    TVectorD PercentageOfStoppingMuons(1);
    PercentageOfStoppingMuons[0] = StopInLiqHeD / nOfTotalStopsD;
    std::cout << "percentage of muons that stop in LiqHe : " << PercentageOfStoppingMuons[0] * 100 << "%" << "\n";
    std::cout << "percentage of muons that stop in the Copper Chamber : " << nOfStopInCopperChamberD / nOfTotalStopsD * 100 << "%" << "\n";
    std::cout << "percentage of muons that stop in the Collimator : " << nOfStopInCollimatorD / nOfTotalStopsD * 100 << "%" << "\n";
    std::cout << "percentage of muons that stop in the Titanium foil : " << nOfStopInTitaniumFoilD / nOfTotalStopsD * 100 << "%" << "\n";
    std::cout << "percentage of muons that stop in the Scintillator: " << nOfStopInPlasticScintillatorD / nOfTotalStopsD * 100 << "%" << "\n";

    // plotting
    TCanvas *c1 = new TCanvas();
    c1->Divide(3, 1);
    c1->cd(1);
    hT1PosX->Draw();
    c1->cd(2);
    hT1PosY->Draw();
    c1->cd(3);
    hT1PosZ->Draw();
    TCanvas *c2 = new TCanvas();
    c2->Divide(2, 1);
    c2->cd(1);
    hT1PosXZ->Draw("colz");
    c2->cd(2);
    hT1PosXY->Draw("colz");

    // saving al objects
    TString result("result");
    TString savename1D("plots/" + result + count + "H1D.pdf");
    TString savename2D("plots/" + result + count + "H2D.pdf");
    TString savename("plots/" + result + count + ".root");
    c1->SaveAs(savename1D);
    c2->SaveAs(savename2D);
    TFile *fileToWrite = new TFile(savename, "recreate");
    hT1PosX->Write();
    hT1PosY->Write();
    hT1PosZ->Write();
    // hT1PosXZ->Write();
    // hT1PosXY->Write();
    PercentageOfStoppingMuons.Write("PercentageOfStoppingMuons");
    fileToWrite->Close();
}