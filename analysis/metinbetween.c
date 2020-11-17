#include <TGraphErrors.h>
#include <TROOT.h>
#include <fstream>
#include <TH1D.h>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>
#include <iostream>
#include <TEfficiency.h>
#include <TCut.h>

pair<double,double> runPoint(const TString infile, TH1D * h_num, TH1D* h_denom)
{
   TFile * f = TFile::Open(infile);
   h_num->SetDirectory(f);
   h_denom->SetDirectory(f);
   TTree * t_ = (TTree*)f->Get("Events");
   gROOT->cd();
 
   std::cout << "start to copy tree" << std::endl;
   const TCut cut_mu = "Sum$(Muon_pt>=15. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=1)>0";
   const TCut cut_photon = "Sum$(Photon_mvaID_WP90 && Photon_electronVeto && (Photon_isScEtaEB||Photon_isScEtaEE))>0";
   const TCut cut_tau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe) && Tau_decayMode!=5 && Tau_decayMode!=6)>0";
   const TCut cut_e = "Sum$(Electron_pt>=32. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0";
   const TCut cut_mumu = "Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=2)<2";
   const TCut baseline = cut_mu && cut_photon && cut_tau && cut_e && cut_mumu;
   TTree * t = (TTree*)t_->CopyTree(baseline);
   std::cout << "copy successful" << std::endl;

   UInt_t nTau = 0;
   Float_t Tau_pt[25], Tau_eta[25], Tau_phi[25], Tau_mass[25];
   t->SetBranchAddress("nTau", &nTau);
   t->SetBranchAddress("Tau_pt", Tau_pt);
   t->SetBranchAddress("Tau_eta", Tau_eta);
   t->SetBranchAddress("Tau_phi", Tau_phi);
   t->SetBranchAddress("Tau_mass", Tau_mass);
   Int_t Tau_decayMode[25];
   UChar_t Tau_idDeepTau2017v2p1VSe[25], Tau_idDeepTau2017v2p1VSmu[25], Tau_idDeepTau2017v2p1VSjet[25];
   t->SetBranchAddress("Tau_decayMode", Tau_decayMode);
   t->SetBranchAddress("Tau_idDeepTau2017v2p1VSe", Tau_idDeepTau2017v2p1VSe);
   t->SetBranchAddress("Tau_idDeepTau2017v2p1VSmu", Tau_idDeepTau2017v2p1VSmu);
   t->SetBranchAddress("Tau_idDeepTau2017v2p1VSjet", Tau_idDeepTau2017v2p1VSjet);
   
   UInt_t nMuon = 0;
   Float_t Muon_pt[25], Muon_eta[25], Muon_phi[25], Muon_mass[25];
   t->SetBranchAddress("nMuon", &nMuon);
   t->SetBranchAddress("Muon_pt", Muon_pt);
   t->SetBranchAddress("Muon_eta", Muon_eta);
   t->SetBranchAddress("Muon_phi", Muon_phi);
   t->SetBranchAddress("Muon_mass", Muon_mass);
   Bool_t Muon_mediumId[25];
   UChar_t Muon_pfIsoId[25];
   t->SetBranchAddress("Muon_mediumId", Muon_mediumId);
   t->SetBranchAddress("Muon_pfIsoId", Muon_pfIsoId);

   UInt_t nPhoton = 0;
   Float_t Photon_pt[25], Photon_eta[25], Photon_phi[25];
   t->SetBranchAddress("nPhoton", &nPhoton);
   t->SetBranchAddress("Photon_pt", Photon_pt);
   t->SetBranchAddress("Photon_eta", Photon_eta);
   t->SetBranchAddress("Photon_phi", Photon_phi);
   Bool_t Photon_electronVeto[25];
   Bool_t Photon_mvaID_WP90[25];
   Bool_t Photon_isScEtaEB[25], Photon_isScEtaEE[25];
   t->SetBranchAddress("Photon_electronVeto", Photon_electronVeto);
   t->SetBranchAddress("Photon_mvaID_WP90", Photon_mvaID_WP90);
   t->SetBranchAddress("Photon_isScEtaEB", Photon_isScEtaEB);
   t->SetBranchAddress("Photon_isScEtaEE", Photon_isScEtaEE);

   Float_t MET_pt, MET_phi;
   t->SetBranchAddress("MET_pt", &MET_pt);
   t->SetBranchAddress("MET_phi", &MET_phi);

   double n_num = 0;
   double n_denom = 0;
   for (int i = 0; i < t->GetEntries(); ++i) {
      if (i%1000==0) std::cout << "beginning entry " << i << std::endl;
      t->GetEntry(i);

      TLorentzVector tau; 
      TVector3 tau_t;
      int ntau = 0;
      int maxiso_tau = 0;
      for (UInt_t j = 0; j < nTau; ++j) {
         if (Tau_pt[j]>=20. && TMath::Abs(Tau_eta[j])<2.3) {
            if ((1&Tau_idDeepTau2017v2p1VSjet[j]) && (8&Tau_idDeepTau2017v2p1VSmu[j]) && (4&Tau_idDeepTau2017v2p1VSe[j])) {
               if (Tau_decayMode[j]!=5 && Tau_decayMode[j]!=6) {
                  if (Tau_idDeepTau2017v2p1VSjet[j]>maxiso_tau) {
                     tau.SetPtEtaPhiM(Tau_pt[j], Tau_eta[j], Tau_phi[j], Tau_mass[j]);
                     tau_t.SetPtEtaPhi(Tau_pt[j], 0., Tau_phi[j]);
                     ++ntau;
                     maxiso_tau = Tau_idDeepTau2017v2p1VSjet[j];
                  }
               }
            }
         }
      }
      if (ntau==0) continue;

      TLorentzVector muon; 
      TVector3 muon_t;
      int nmu = 0;
      int maxiso_mu = 0;
      for (UInt_t j = 0; j < nMuon; ++j) {
         if (Muon_pt[j]>=15. && TMath::Abs(Muon_eta[j])<2.4) {
            if (Muon_mediumId[j] && Muon_pfIsoId[j]>=1) {
               if (Muon_pfIsoId[j]>maxiso_mu) {
                  muon.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
                  muon_t.SetPtEtaPhi(Muon_pt[j], 0., Muon_phi[j]);
                  ++nmu;
                  maxiso_mu = Muon_pfIsoId[j];
               }
            }
         }
      }
      if (nmu==0) continue;

      if (std::fabs(tau_t.DeltaPhi(muon_t)<0.3)) continue;
      if ((tau+muon).M()<100.) continue;

      TVector3 photon_t;
      int nphoton = 0;
      double maxpt = 0.;
      for (UInt_t j = 0; j < nPhoton; ++j) {
         if (TMath::Abs(Photon_eta[j])<2.5 && (Photon_isScEtaEB[j]||Photon_isScEtaEE[j])) {
            if (Photon_mvaID_WP90[j] && Photon_electronVeto[j]) {
               if (Photon_pt[j]>maxpt) {
                  ++nphoton;
                  photon_t.SetPtEtaPhi(Photon_pt[j], 0., Photon_phi[j]);
                  maxpt = Photon_pt[j];
               }
            }
         }
      }
      if (nphoton==0) continue;

      const double dr_mugamma = std::fabs(tau_t.DeltaPhi(photon_t));
      const double dr_taugamma = std::fabs(muon_t.DeltaPhi(photon_t));
      if ( dr_mugamma<0.3 || dr_taugamma<0.3 ) continue;

      TVector3 met;
      met.SetPtEtaPhi(MET_pt, 0., MET_phi);

      const double mass = (muon+tau).M();
      h_denom->Fill(mass);
      ++n_denom;

      const TVector3 tauxmet = tau_t.Cross(met);
      const TVector3 tauxmu = tau_t.Cross(muon_t);
      const TVector3 muxmet = muon_t.Cross(met);
      const TVector3 muxtau = muon_t.Cross(tau_t);
      if (tauxmet.Dot(tauxmu)>=0. && muxmet.Dot(muxtau)>=0.) {
         h_num->Fill(mass);
         ++n_num;
      }
   }

   return std::make_pair(n_num, n_denom);
}

void metinbetween_bkg()
{
   TH1D * h_num = new TH1D("h_num", ";visible mass (#mu+#tau_{h}) [GeV];events / 25 GeV", 8, 0., 200.);
   h_num->SetLineWidth(2);
   h_num->SetStats(0);
   h_num->Sumw2();
   TH1D * h_denom = (TH1D*)h_num->Clone("h_denom");

   //const TString inlist = "./filelists/ZGToLLG_01J_5f.list"; const TString tag = "ZGToLLG_01J_5f";
   //const TString inlist = "./filelists/WGToLNuG.list"; const TString tag = "WGToLNuG";
   const TString inlist = "./filelists/QCD_Pt-20toInf_MuEnrichedPt15.list"; const TString tag = "QCD";

   int n_num = 0;
   int n_denom = 0;

   std::ifstream infile(inlist);
   std::string line;
   while (std::getline(infile, line)) {
      // download the file
      char cmd_download[1000];
      sprintf(cmd_download, "xrdcp root://cmsxrootd.fnal.gov//%s ./", line.c_str());
      std::cout << cmd_download << std::endl;
      system(cmd_download);
      const char * fname = basename(line.c_str());
      // run the analyzer
      std::cout << "runPoint()" << std::endl;
      std::pair<double, double> p = runPoint(fname, h_num, h_denom);
      n_num += p.first;
      n_denom += p.second;
      // delete the file
      char cmd_delete[1000];
      sprintf(cmd_delete, "rm %s", fname);
      std::cout << cmd_delete << std::endl;
      system(cmd_delete);
      std::cout << "# of events in num, den: " << n_num << ", " << n_denom << std::endl;
      if (n_num>1000) break;
   }

   const double eff = n_num/n_denom;
   const double err = eff * sqrt((1./n_num)+(1./n_denom));
   std::cout << "inclusive eff: " << eff << " +- " << err << std::endl;

   TEfficiency * g_eff = new TEfficiency(*h_num, *h_denom);

   TCanvas * c = new TCanvas("c", "c", 400, 400);
   g_eff->Draw("");
   char title[100];
   sprintf(title, "%s;%s;efficiency", tag.Data(), h_num->GetXaxis()->GetTitle());
   g_eff->SetTitle(title);
   g_eff->SetMarkerStyle(20);
   c->SaveAs("./plots/metinbetween_bkg_"+tag+".pdf");
}

void metinbetween_sig()
{
   const int n = 10;
   const int mass[n] = {250, 375, 500, 625, 750, 1000, 2000, 3000, 4000, 5000};

   TH1D * h_num = new TH1D("h_num", ";visible mass (#mu+#tau_{h}) [GeV];events / 25 GeV", 8, 0., 200.);
   TH1D * h_denom = (TH1D*)h_num->Clone("h_denom");

   TGraphErrors * g = new TGraphErrors(n);
   for (int i = 0; i < n; ++i) {
      char inlist[1000];
      sprintf(inlist, "./filelists/Taustar_m%d.list", mass[i]);
      std::ifstream infile(inlist);
      std::string line;
      double n_num = 0;
      double n_denom = 0;
      while (std::getline(infile, line)) {
         // download the file
         char cmd_download[1000];
         sprintf(cmd_download, "xrdcp root://cmsxrootd.fnal.gov//%s ./", line.c_str());
         std::cout << cmd_download << std::endl;
         system(cmd_download);
         const char * fname = basename(line.c_str());
         // run the analyzer
         std::cout << "runPoint()" << std::endl;
         std::pair<double, double> p = runPoint(fname, h_num, h_denom);
         n_num += p.first;
         n_denom += p.second;
         // delete the file
         char cmd_delete[1000];
         sprintf(cmd_delete, "rm %s", fname);
         std::cout << cmd_delete << std::endl;
         system(cmd_delete);
      }
      const double eff = n_num/n_denom;
      const double err = eff * ((1./n_num)+(1./n_denom));
      g->SetPoint(i, mass[i], eff);
      g->SetPointError(i, 0., err);
   }

   TCanvas * c = new TCanvas("c", "c", 400, 400);
   g->Draw("APE");
   g->SetTitle(";#tau* mass [GeV];efficiency");
   g->SetMarkerStyle(20);
   g->SetMinimum(0.5);
   g->SetMaximum(1.);
   c->SaveAs("./plots/metinbetween_sig.pdf");
}

