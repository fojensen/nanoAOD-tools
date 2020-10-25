#include <TCut.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>

void sigYields()
{
   const TCut mu = "Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_pfIsoId>=4 && Muon_mediumId)==1";
   const TCut tau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && (64&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe) && (Tau_decayMode!=5&&Tau_decayMode!=6))==1";
   const TCut photon = "Sum$(Photon_pt>=100. && TMath::Abs(Photon_eta)<2.5 && Photon_mvaID_WP90 && Photon_electronVeto)==1";
   const TCut trigger = "HLT_IsoMu24||HLT_IsoMu27";
   const TCut eVeto = "Sum$(Electron_pt>=32. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0";
   const TCut Zveto = "Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=2)<2";
   const TCut bVeto = "Sum$(Jet_pt>=20. && TMath::Abs(Jet_eta)<2.5 && (4&Jet_jetId) && Jet_btagDeepB>=0.7527)==0";
   const TCut baseline = mu && tau && photon && trigger && eVeto && Zveto && bVeto;

   const TString infile = "root://cmsxrootd.fnal.gov///store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m250_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/7FEC7B94-611C-364A-9A12-B9BD43C01EC3.root";
   TFile * f = TFile::Open(infile);
   TTree * t = (TTree*)f->Get("Events");

   const double xs = 0.02135;
   //const double lumi = 59725.419;
   const double lumi = 41525.059;
   const double n1 = t->GetEntries();
   const double n2 = t->GetEntries(baseline);
   const double nexp = (lumi*(xs/n1)) * n2;
   const double eff = n2/n1;
   
   std::cout << n1 << " " << n2 << " " << nexp << " " << eff << std::endl;
}

