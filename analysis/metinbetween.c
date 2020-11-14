#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>
#include <TGraphErrors.h>
#include <iostream>

pair<double,double> runPoint(const TString infile)
{
   TFile * f = TFile::Open(infile);
   TTree * t = (TTree*)f->Get("Events");

   UInt_t nTau = 0;
   UChar_t Tau_genPartFlav[100];
   Float_t Tau_pt[100], Tau_eta[100], Tau_phi[100], Tau_mass[100];
   t->SetBranchAddress("nTau", &nTau);
   t->SetBranchAddress("Tau_genPartFlav", Tau_genPartFlav);
   t->SetBranchAddress("Tau_pt", Tau_pt);
   t->SetBranchAddress("Tau_eta", Tau_eta);
   t->SetBranchAddress("Tau_phi", Tau_phi);
   t->SetBranchAddress("Tau_mass", Tau_mass);

   UInt_t nMuon = 0;
   UChar_t Muon_genPartFlav[100];
   Float_t Muon_pt[100], Muon_eta[100], Muon_phi[100], Muon_mass[100];
   t->SetBranchAddress("nMuon", &nMuon);
   t->SetBranchAddress("Muon_genPartFlav", Muon_genPartFlav);
   t->SetBranchAddress("Muon_pt", Muon_pt);
   t->SetBranchAddress("Muon_eta", Muon_eta);
   t->SetBranchAddress("Muon_phi", Muon_phi);
   t->SetBranchAddress("Muon_mass", Muon_mass);

   UInt_t nPhoton = 0;
   Float_t Photon_pt[100], Photon_eta[100];
   UChar_t Photon_genPartFlav[100];
   t->SetBranchAddress("nPhoton", &nPhoton);
   t->SetBranchAddress("Photon_pt", Photon_pt);
   t->SetBranchAddress("Photon_eta", Photon_eta);
   t->SetBranchAddress("Photon_genPartFlav", Photon_genPartFlav);

   Float_t MET_pt = 0.;
   Float_t MET_phi = 0.;
   t->SetBranchAddress("MET_pt", &MET_pt);
   t->SetBranchAddress("MET_phi", &MET_phi);

   double denom = 0.;
   double num = 0.;
   for (int i = 0; i < t->GetEntries(); ++i) {
      //if (i%10000==0) std::cout << "beginning entry " << i << std::endl;
      t->GetEntry(i);

      TLorentzVector muon; 
      TVector3 muon_t;
      int nmu = 0;
      for (UInt_t j = 0; j < nMuon; ++j) {
         if (Muon_genPartFlav[j]==15 && Muon_pt[j]>=27. && TMath::Abs(Muon_eta[j])<2.4) {
            muon.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
            muon_t.SetPtEtaPhi(Muon_pt[j], 0., Muon_phi[j]);
            ++nmu;
         }
      }
      if (nmu!=1) continue;

      TLorentzVector tau; 
      TVector3 tau_t;
      int ntau = 0; 
      for (UInt_t j = 0; j < nTau; ++j) {
         if (Tau_genPartFlav[j]==5 && Tau_pt[j]>=20. && TMath::Abs(Tau_eta[j])<2.3) {
            tau.SetPtEtaPhiM(Tau_pt[j], Tau_eta[j], Tau_phi[j], Tau_mass[j]);
            tau_t.SetPtEtaPhi(Tau_pt[j], 0., Tau_phi[j]);
            ++ntau;
         }
      }
      if (ntau!=1) continue;

      if (tau.DeltaR(muon)<0.7) continue;
      if ((tau+muon).M()<100.) continue;

      int nphoton = 0;
      for (UInt_t j = 0; j < nPhoton; ++j) {
         if (Photon_genPartFlav[j]==1 && TMath::Abs(Photon_eta[j])<2.5) {
            if (Photon_pt[j]>=100.) {
               ++nphoton;
            }
         }
      }
      if (nphoton==0) continue;

      TVector3 met;
      met.SetPtEtaPhi(MET_pt, 0., MET_phi);

      const TVector3 tauxmet = tau_t.Cross(met);
      const TVector3 tauxmu = tau_t.Cross(muon_t);
      const TVector3 muxmet = muon_t.Cross(met);
      const TVector3 muxtau = muon_t.Cross(tau_t);
      if (tauxmet.Dot(tauxmu)>=0. && muxmet.Dot(muxtau)>=0.) {
         ++num;
      }
      ++denom;
   }

   const double eff = num/denom;
   const double err = eff * sqrt((1./num)+(1./denom));
   return std::make_pair(eff, err);
}

void metinbetween()
{
   const int n = 8;
   TString infiles[n];
   infiles[0] = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m250_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/7FEC7B94-611C-364A-9A12-B9BD43C01EC3.root";
   infiles[1] = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m500_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/B97EF17B-4634-EB45-8776-BF8CAE1E634A.root";
   infiles[2] = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m750_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/270000/F7DE8AEE-AC69-284A-A468-6E17429A04F6.root";
   infiles[3] = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m1000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/270000/1E3560C2-B140-F34F-B24D-E7A1AD26CEC2.root";
   infiles[4] = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m2000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/100000/0DEDC987-CDD7-7A43-B657-DDA4AEEDEC30.root";
   infiles[5] = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m3000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/250000/2C47664A-8C31-6048-94BB-EA5C6AE7D2C6.root";
   infiles[6] = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m4000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/270000/7226A379-9FA7-F84C-893C-DF9A8E4B400A.root";
   infiles[7] = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m5000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/120000/44BFF07F-8D14-0347-B215-040F8D99B95B.root";

   double mass[n];
   mass[0] = 250.;
   mass[1] = 500.;
   mass[2] = 750.;
   mass[3] = 1000.;
   mass[4] = 2000.;
   mass[5] = 3000.;
   mass[6] = 4000.;
   mass[7] = 5000.;

   TGraphErrors * g = new TGraphErrors(8);
   for (int i = 0; i < n; ++i) {
      // download the file
      char cmd_download[1000];
      sprintf(cmd_download, "xrdcp root://cmsxrootd.fnal.gov//%s ./", infiles[i].Data());
      std::cout << cmd_download << std::endl;
      system(cmd_download);
      const char * fname = basename(infiles[i].Data());
      // run the analyzer
      std::cout << "runPoint()" << std::endl;
      std::pair<double, double> p = runPoint(fname);
      g->SetPoint(i, mass[i], p.first);
      g->SetPointError(i, 0., p.second);
      // delete the file
      char cmd_delete[1000];
      sprintf(cmd_delete, "rm %s", fname);
      std::cout << cmd_delete << std::endl;
      system(cmd_delete);
   }

   TCanvas * c = new TCanvas("c", "c", 400, 400);
   g->Draw("APE");
   g->SetTitle(";#tau* mass [GeV];efficiency");
   g->SetMarkerStyle(20);
   g->SetMinimum(0.5);
   g->SetMaximum(1.);
   c->SaveAs("./plots/metinbetween.pdf");
}

