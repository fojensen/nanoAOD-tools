#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>

int runPoint(const TString list, const double xs)
{
   std::ifstream infile("./filelists/"+list+".list");
   std::string line;

   const TCut muon = "Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=4)>0";
   const TCut photon = "Sum$(Photon_pt>=100. && TMath::Abs(Photon_eta)<2.5 && Photon_mvaID_WP80 && Photon_electronVeto)>0";
   const TCut tau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && (64&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu))>0";
   const TCut baseline = muon && photon && tau;
   //const TCut electron = "Sum$(Electron_pt>=32. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP80)==0";
   //const TCut trigger = "HLT_IsoMu24||HLT_IsoMu27";
   //const TCut baseline = muon && photon && tau && electron && trigger; 

   double n = 0;
   double ntot = 0;

   while (std::getline(infile, line)) {
      std::cout << "   " << line << std::endl;
      char buffer[1000];
      sprintf(buffer, "root://cmsxrootd.fnal.gov//%s", line.c_str());
      TFile * f = TFile::Open(buffer);
      TTree * t = (TTree*)f->Get("Events");
      n +=  t->GetEntries(baseline);
      ntot += t->GetEntries();
   }
   std::cout << "***" << std::endl;
   std::cout << "running on " << list << std::endl;
   std::cout << "   events in mc sample: " << ntot << std::endl;
   std::cout << "   events in mc passing baseline selection: " << n << std::endl;
   const double xsWeight =  59725.419 * xs / double(ntot);
   const double y = n * xsWeight;
   std::cout << "   expected yields for 2018: " << y << std::endl;
   std::cout << "***" << std::endl;
   return n;
}

void getN()
{
   runPoint("GluGluHToTauTau_M125", 3.0469376);;
   runPoint("VBFHToTauTau_M125", 0.23720704);
   runPoint("ttHToTauTau_M125", 0.031805312);
}

