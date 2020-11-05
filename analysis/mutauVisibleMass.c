#include <TVector2.h>
#include <TChain.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <iostream>
#include <fstream>

int runPoint(const TString infile, TH1D * h[12])
{
   std::cout << infile << std::endl;

   char fname[1000];
   sprintf(fname, "xrdcp root://cmsxrootd.fnal.gov//%s ./", infile.Data());
   system(fname);
   const char * littlename = basename(infile.Data());
   std::cout<<littlename<<std::endl;
   TFile * f = TFile::Open(littlename);
   TTree * t = (TTree*)f->Get("Events");

   for (int i = 0; i < 12; ++i) h[i]->SetDirectory(f);

   UInt_t nTau = 0;
   UChar_t Tau_genPartFlav[100];
   Float_t Tau_pt[100], Tau_eta[100], Tau_phi[100], Tau_mass[100];
   Int_t Tau_decayMode[100];
   t->SetBranchAddress("nTau", &nTau);
   t->SetBranchAddress("Tau_genPartFlav", Tau_genPartFlav);
   t->SetBranchAddress("Tau_pt", Tau_pt);
   t->SetBranchAddress("Tau_eta", Tau_eta);
   t->SetBranchAddress("Tau_phi", Tau_phi);
   t->SetBranchAddress("Tau_mass", Tau_mass);
   t->SetBranchAddress("Tau_decayMode", Tau_decayMode);

   UInt_t nMuon = 0;
   UChar_t Muon_genPartFlav[100];
   Float_t Muon_pt[100], Muon_eta[100], Muon_phi[100], Muon_mass[100];
   t->SetBranchAddress("nMuon", &nMuon);
   t->SetBranchAddress("Muon_genPartFlav", Muon_genPartFlav);
   t->SetBranchAddress("Muon_pt", Muon_pt);
   t->SetBranchAddress("Muon_eta", Muon_eta);
   t->SetBranchAddress("Muon_phi", Muon_phi);
   t->SetBranchAddress("Muon_mass", Muon_mass);

   Float_t MET_pt = 0.;
   Float_t MET_phi = 0.;
   t->SetBranchAddress("MET_pt", &MET_pt);
   t->SetBranchAddress("MET_phi", &MET_phi);

   const int n = t->GetEntries();
   std::cout << "entries in the tree: " << n << std::endl;
   int ndenom = 0;
   for (int i = 0; i < n; ++i) {
      if (i%100000==0) {
         std::cout << "beginning entry " << i << std::endl;
         std::cout << "   # of taus in so far: " << ndenom << std::endl << std::endl;
      }
      t->GetEntry(i);
      TLorentzVector muon;
      int nmu = 0;
      for (UInt_t j = 0; j < nMuon; ++j) {
         if (Muon_genPartFlav[j]==15 && Muon_pt[j]>=27. && TMath::Abs(Muon_eta[j])<2.4) {
            muon.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
            ++nmu;
         }
      }
      if (nmu!=1) continue;
      
      int ntau = 0;
      int dm = -1;
      TLorentzVector tau;  
      for (UInt_t j = 0; j < nTau; ++j) {
         if (Tau_genPartFlav[j]==5 && Tau_pt[j]>=20. && TMath::Abs(Tau_eta[j])<2.3) {
            tau.SetPtEtaPhiM(Tau_pt[j], Tau_eta[j], Tau_phi[j], Tau_mass[j]);
            dm = Tau_decayMode[j];
            ++ntau;
         }
      }
      if (ntau!=1) continue;
     
      if (muon.DeltaR(tau)<0.5) continue;
       
      TVector2 met2;
      met2.SetMagPhi(MET_pt, MET_phi);
      TVector2 muon2;
      muon2.SetMagPhi(muon.Pt(), muon.Phi());
      const double mt = sqrt(2. * met2.Mod() * muon2.Mod() * (1. - cos(met2.DeltaPhi(muon2))));
      if (mt>=50.) continue;

      const double m = (muon+tau).M();
      h[dm]->Fill(m);

      ++ndenom;
   }

   char deletestring[1000];
   sprintf(deletestring, "rm %s", littlename);
   system(deletestring);
   
   return ndenom;
}

void mutauVisibleMass()
{
   TH1D * h[12];
   for (int i = 0; i < 12; ++i) {
      char title[100];
      sprintf(title, "decayMode = %d;visible mass [GeV];events / 5 GeV", i);
      h[i] = new TH1D("h_"+TString::Itoa(i, 10), title, 40, 0., 200.);
      h[i]->SetLineWidth(2);
   }

   std::ifstream infile("./filelists/DYJetsToLL_M-50.list");
   std::string line;
   int ndenom = 0;
   while (std::getline(infile, line)) {  
      ndenom += runPoint(line, h);
      std::cout << "# of taus: " << ndenom << std::endl;
      if (ndenom>=50000) break;
   }

   TCanvas * c = new TCanvas("c", "", 1600., 800.);
   c->Divide(4, 3);
   for (int i = 0; i < 12; ++i) {
      c->cd(i+1);
      h[i]->Draw("HIST, E");
   }
   c->SaveAs("./plots/mutauVisibleMass.pdf");
}

