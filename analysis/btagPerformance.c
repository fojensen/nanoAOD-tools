#include <iostream>
#include <TFile.h>
#include <TTree.h>

void runPoint(const TString infile, const int year, const bool isSig)
{
   std::cout << "year: " << year << std::endl;
   std::cout << "   file: " << infile << std::endl;
   double wp[3];
   if (year==2016) {
      wp[0] = 0.2217;
      wp[1] = 0.6321;
      wp[2] = 0.8953;
   }
   if (year==2017) {
      wp[0] = 0.1355;
      wp[1] = 0.4506;
      wp[2] = 0.7738;
   }
   if (year==2018) {
      wp[0] = 0.1208;
      wp[1] = 0.4168;
      wp[2] = 0.7665;
   }

   char fname[1000];
   sprintf(fname, "root://cmsxrootd.fnal.gov//%s", infile.Data());
   TFile * f = TFile::Open(fname);
   TTree * t = (TTree*)f->Get("Events");

   UInt_t nJet;
   Float_t Jet_pt[20], Jet_eta[20];
   Float_t Jet_btagDeepB[20];
   Int_t Jet_jetId[20];
   Int_t Jet_hadronFlavour[20];

   t->SetBranchAddress("nJet", &nJet);
   t->SetBranchAddress("Jet_pt", Jet_pt);
   t->SetBranchAddress("Jet_eta", Jet_eta);
   t->SetBranchAddress("Jet_btagDeepB", Jet_btagDeepB);
   t->SetBranchAddress("Jet_jetId", Jet_jetId);
   t->SetBranchAddress("Jet_hadronFlavour", Jet_hadronFlavour);

   double ndenom = 0.;
   double nl = 0.;
   double nm = 0.;
   double nt = 0.;

   for (int i = 0; i < t->GetEntries(); ++i) {
      t->GetEntry(i);
      for (int j = 0; j < nJet; ++j) {
         const bool g1 = isSig && Jet_hadronFlavour[j]==5;
         const bool g2 = !isSig && Jet_hadronFlavour[j]!=5 && Jet_hadronFlavour[j]!=4;
         if (g1||g2) {
            if (Jet_pt[j]>=20. && TMath::Abs(Jet_eta[j])<2.5 && (4&Jet_jetId[j])) {
               ++ndenom;
               if (Jet_btagDeepB[j]>=wp[0]) ++nl;
               if (Jet_btagDeepB[j]>=wp[1]) ++nm;
               if (Jet_btagDeepB[j]>=wp[2]) ++nt;
            }
         }
      }
      if ( (isSig&&nt>=2000.) || (!isSig&&ndenom>=100000.) ) break;
   }

   std::cout << "   number of jets: " << ndenom << std::endl;
   std::cout << "   L,M,T: " << nl << ", " << nm << ", " << nt << std::endl;

   const double el = nl/ndenom;
   double elerr = sqrt((1./nl)+(1./ndenom));
   elerr = el * elerr;

   const double em = nm/ndenom;
   double emerr = sqrt((1./nm)+(1./ndenom));
   emerr = em * elerr;

   const double et = nt/ndenom;
   double eterr = sqrt((1./nt)+(1./ndenom));
   eterr = et * eterr;

   std::cout << "   eL: " << el << "+-" << elerr << std::endl;
   std::cout << "   eM: " << em << "+-" << emerr << std::endl;
   std::cout << "   eT: " << et << "+-" << eterr << std::endl;
}

void bcheck_sig()
{
   const bool isSig = true;
   
   const TString f2018 = "/store/mc/RunIISummer20UL18NanoAODv2/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v15_L1v1-v1/270000/019426EE-3D50-1249-B266-F6DBA0AFE3B5.root";
   runPoint(f2018, 2018, isSig);

   const TString f2017 = "/store/mc/RunIISummer20UL17NanoAODv2/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_mc2017_realistic_v8-v1/00000/12B6E2C4-456F-7546-8395-EE557A14B441.root";
   runPoint(f2017, 2017, isSig);

   const TString f2016 = "/store/mc/RunIISummer20UL16NanoAODv2/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v15-v1/00000/04004BA9-A496-774E-85EB-812B9777F78E.root";
   runPoint(f2016, 2016, isSig);

   const TString f2016pre = "/store/mc/RunIISummer20UL16NanoAODAPVv2/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_mcRun2_asymptotic_preVFP_v9-v1/10000/04798F8C-5C5B-9148-A9F1-2F67E7073D63.root";
   runPoint(f2016pre, 2016, isSig);
}

void bcheck_bkg()
{
   const bool isSig = false;
 
   const TString f2018 = "/store/mc/RunIISummer20UL18NanoAODv2/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v15_L1v1-v1/00000/07C08149-569D-104A-9310-E277C9CC92D8.root";
   runPoint(f2018, 2018, isSig);

   const TString f2017 = "/store/mc/RunIISummer20UL17NanoAODv2/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/106X_mc2017_realistic_v8-v1/230000/14B8E74A-0A70-8B44-A321-967800ECA0BD.root";
   runPoint(f2017, 2017, isSig);

   const TString f2016 = "/store/mc/RunIISummer20UL16NanoAODv2/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v15-v1/260000/062085CD-8DF4-1D40-8042-63998B6A3A95.root";
   runPoint(f2016, 2016, isSig);

   //const TString f2016pre = "";
   //runPoint(f2016pre, 2016, isSig);
}
