#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>

int runPoint(const TString list, const double xs)
{
   std::cout << "beginning " << list << std::endl;
   std::ifstream infile("./filelists/"+list+".list");
   std::string line;

   const TCut cut_Mu = "(Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=4)>0)";
   const TCut cut_Trigger = "(HLT_IsoMu24||HLT_IsoMu27||HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1)";
   const TCut cut_Electron = "(Sum$(Electron_pt>=32. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP80)==0)";
   const TCut cut_Photon = "(Sum$(Photon_pt>=32. && TMath::Abs(Photon_eta)<2.5 && Photon_mvaID_WP90 && Photon_electronVeto)>0)";
   const TCut cut_Tau = "(Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && (64&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (Tau_decayMode!=5&&Tau_decayMode!=6)>0))";
   const TCut cut_Flag = "(Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter)";
   const TCut baseline = cut_Mu && cut_Trigger && cut_Electron && cut_Photon && cut_Tau && cut_Flag;
   
   double n = 0.;
   double ntot = 0.;
   int nfiles = 0;
   while (std::getline(infile, line)) {
      if (nfiles%10==0) std::cout << "   " << line << std::endl;
      char buffer[10000];
      sprintf(buffer, "root://cmsxrootd.fnal.gov//%s", line.c_str());
      TFile * f = TFile::Open(buffer);
      TTree * t = (TTree*)f->Get("Events");
      n +=  t->GetEntries(baseline);
      ntot += t->GetEntries();
      ++nfiles;
   }

   std::cout << "***" << std::endl;
   std::cout << "running on " << list << std::endl;
   std::cout << "   files in mc sample: " << nfiles << std::endl;
   std::cout << "   events in mc sample: " << ntot << std::endl;
   std::cout << "   events in mc passing baseline selection: " << n << std::endl;
   const double xsWeight =  59725.419 * xs / ntot;
   const double y = n * xsWeight;
   std::cout << "   expected yields for 2018: " << y << std::endl;
   std::cout << "***" << std::endl;
   return n;
}

void getN()
{
   //runPoint("GluGluHToTauTau_M125", 3.0469376);;
   //runPoint("VBFHToTauTau_M125", 0.23720704);
   //runPoint("ttHToTauTau_M125", 0.031805312);

   //runPoint("GJets_HT-40To100", 8608.);
   //runPoint("GJets_HT-100To200", 8608.);
   //runPoint("GJets_HT-200To400", 2190.0);
   //runPoint("GJets_HT-400To600", 258.0);
   //runPoint("GJets_HT-600ToInf", 85.11);

   //runPoint("GJets_DR-0p4_HT-100To200", 5030.0);
   //runPoint("GJets_DR-0p4_HT-200To400", 1125.0);
   //runPoint("GJets_DR-0p4_HT-400To600", 124.7);
   runPoint("GJets_DR-0p4_HT-600ToInf", 40.46);
}

