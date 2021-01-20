#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>

void runPoint(const TString infile, const TString llfile, const TString tautaufile)
{
   TFile * f_in = TFile::Open(infile);
   TTree * t_in = (TTree*)f_in->Get("Events");
   const double n = t_in->GetEntries();
   std::cout << "number of entries in input tree (n): " << n << std::endl;

   //const TCut cut_ee =     "Sum$(TMath::Abs(GenPart_pdgId)==11 && GenPart_genPartIdxMother>=0 && GenPart_pdgId[GenPart_genPartIdxMother]==23)==2";
   //const TCut cut_mumu =   "Sum$(TMath::Abs(GenPart_pdgId)==13 && GenPart_genPartIdxMother>=0 && GenPart_pdgId[GenPart_genPartIdxMother]==23)==2";
   //const TCut cut_tautau = "Sum$(TMath::Abs(GenPart_pdgId)==15 && GenPart_genPartIdxMother>=0 && GenPart_pdgId[GenPart_genPartIdxMother]==23)==2";

   const TCut cut_tautau = "Sum$(Tau_genPartFlav==5) || Sum$(Muon_genPartFlav==15) || Sum$(Electron_genPartFlav==15)";

   TFile * f_ll = new TFile(llfile, "RECREATE");
   //TTree * t_ll = t_in->CopyTree( (cut_ee||cut_mumu) && !cut_tautau );
   TTree * t_ll = t_in->CopyTree(!cut_tautau);
   const double n_ll = t_ll->GetEntries();
   t_ll->Write();
   f_ll->Close();
   std::cout  << "number of entries in ll tree (n_ll): " << n_ll << std::endl;

   TFile * f_tautau = new TFile(tautaufile, "RECREATE");
   //TTree * t_tautau = t_in->CopyTree( cut_tautau && !(cut_ee||cut_mumu) );
   TTree * t_tautau = t_in->CopyTree(cut_tautau);
   const double n_tautau = t_tautau->GetEntries();
   t_tautau->Write();
   f_tautau->Close();
   std::cout  << "number of entries in tautau tree (n_tautau): " << n_tautau << std::endl;

   const double n_lost = n-n_ll-n_tautau;
   std::cout << "n_lost (n-n_ll-n_tautau): " << n_lost << std::endl;
   std::cout << "n_ll/n: " << n_ll/n << std::endl;
   std::cout << "n_tautau/n: " << n_tautau/n << std::endl;
   std::cout << "n_lost/n: " << n_lost/n << std::endl;
}

void splitDY()
{
   //const TString testfile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/C00024AD-3D0D-DE45-949F-E56A81BDDCA7.root";
   //const TString testfile = "C00024AD-3D0D-DE45-949F-E56A81BDDCA7.root";
   //runPoint(testfile, "ll.root", "tautau.root");

   runPoint("./outputData/DYJetsToLL_M50.root", "./outputData/DYJetsToEEMuMu_M50.root", "./outputData/DYJetsToTauTau_M50.root");
}

