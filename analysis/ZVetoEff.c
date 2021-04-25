#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>

void ZVetoEff(const TString infile)
{
   std::cout << "infile: " << infile << std::endl;
   char buffer[100];
   sprintf(buffer, "../crab/%s.root", infile.Data());
   TFile *f = TFile::Open(buffer);
   TTree *t = (TTree*)f->Get("Events");

   const TCut cut_ee = "Sum$(Electron_genPartFlav==1)==2";
   const TCut cut_mm = "Sum$(Muon_genPartFlav==1)==2";
   const TCut cut_te = "Sum$(Electron_genPartFlav==15)==1 && Sum$(Tau_genPartFlav==5)==1";
   const TCut cut_tm = "Sum$(Muon_genPartFlav==15)==1 && Sum$(Tau_genPartFlav==5)==1";

   const TCut veto_ee = "EE_HavePair==0";
   const TCut veto_mm = "MuMu_HavePair==0"; 

   const double ee_tot = t->GetEntries(cut_ee);
   const double mm_tot = t->GetEntries(cut_mm);
   const double te_tot = t->GetEntries(cut_te);
   const double tm_tot = t->GetEntries(cut_tm);

   const double ee_eeveto = t->GetEntries(cut_ee && veto_ee);
   const double mm_mmveto = t->GetEntries(cut_mm && veto_mm);
   const double te_eeveto = t->GetEntries(cut_te && veto_ee);
   const double tm_mmveto = t->GetEntries(cut_tm && veto_mm);

   if (ee_tot>0.) {
      std::cout << ee_eeveto << " / " << ee_tot << std::endl;
      std::cout << "ee veto on ee events: " << ee_eeveto/ee_tot << std::endl;
   }
   if (mm_tot>0.) {
      std::cout << mm_mmveto << " / " << mm_tot << std::endl;
      std::cout << "mm veto on mm events: " << mm_mmveto/mm_tot << std::endl;
   }
   if (te_tot>0.) {
      std::cout << te_eeveto << " / " << te_tot << std::endl;
      std::cout << "ee veto on te events: " << te_eeveto/te_tot << std::endl;
   }
   if (tm_tot>0.) {
      std::cout << tm_mmveto << " / " << tm_tot << std::endl;
      std::cout << "mm veto on tm events: " << tm_mmveto/tm_tot << std::endl;
   }
}

