#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>

void splitDY()
{
   TFile * f_in = TFile::Open("./outputData/DYJetsToLL_M-50.root");
   TTree * t_in = (TTree*)f_in->Get("Events");
   std::cout << "number of entries in input tree: " << t_in->GetEntries() << std::endl;

   const TCut cut_TauTau = "Sum$(TMath::Abs(GenPart_pdgId)==15 && GenPart_genPartIdxMother>=0 && GenPart_pdgId[GenPart_genPartIdxMother]==23)==2";

   TFile * f_eemumu = new TFile("./outputData/DYJetsToEEMuMu_M-50.root", "RECREATE");
   TTree * t_eemumu = t_in->CopyTree(!cut_TauTau);
   std::cout << "number of entries in eemumu tree: " << t_eemumu->GetEntries() << std::endl;
   t_eemumu->Write();
   f_eemumu->Close();

   TFile * f_tautau = new TFile("./outputData/DYJetsToTauTau_M-50.root", "RECREATE");
   TTree * t_tautau = t_in->CopyTree(cut_TauTau);
   std::cout << "number of entries in tautau tree: " << t_tautau->GetEntries() << std::endl;
   t_tautau->Write();
   f_tautau->Close();
}

