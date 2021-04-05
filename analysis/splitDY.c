#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>

void runPoint(const TString infile, const TString outfile, const int channel)
{
   std::cout << channel << std::endl;
   TFile * f_in = TFile::Open(infile);
   TTree * t_in = (TTree*)f_in->Get("Events");
   const double n = t_in->GetEntries();
   std::cout << "number of entries in input tree: " << n << std::endl;

   TFile * f_out = new TFile(outfile, "RECREATE");
   const TCut cut = "Sum$(TMath::Abs(GenPart_pdgId)==15 && GenPart_genPartIdxMother>=0 && GenPart_pdgId[GenPart_genPartIdxMother]==23)>=2";
   TTree * t_out = t_in->CopyTree(channel==1?cut:!cut);
   const double n_out = t_out->GetEntries();
   std::cout << "number of entries in output tree: " << n_out << std::endl;

   t_out->Write();
   f_out->Close();
}

void splitDY(const int year)
{
   //const TString testfile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/C00024AD-3D0D-DE45-949F-E56A81BDDCA7.root";
   //const TString testfile = "C00024AD-3D0D-DE45-949F-E56A81BDDCA7.root";
   //runPoint(testfile, "ll.root", "tautau.root");

   if (year==2018) {
   runPoint("./outputData/DYJetsToLL_M50.root", "./outputData/DYJetsToEEMuMu_M50.root", 0);
   runPoint("./outputData/DYJetsToLL_M50.root", "./outputData/DYJetsToTauTau_M50.root", 1);
}

