#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <TLorentzVector.h>

void taumdm_1()
{
   const TString infile = "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/WJetsToLNu__A0A48A5A-15B8-914B-8DC7-E407797D4539.root";
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/70000/A0A48A5A-15B8-914B-8DC7-E407797D4539.root";
   TFile * f = TFile::Open(infile);
   TTree * t = (TTree*)f->Get("Events");

   TH1D * h_massinc = new TH1D("h_massinc", ";#tau_{h} mass [GeV];events / 0.05 GeV", 40, 0., 2.);
   h_massinc->SetLineWidth(2);
   const double n_m = t->Project(h_massinc->GetName(), "Tau_mass", "Tau_genPartFlav==5 && TMath::Abs(Tau_eta)<2.3 && Tau_pt>=20.");
   h_massinc->Scale(1./n_m);

   TH1D * h_decayMode = new TH1D("h_decayMode", ";#tau_{h} decayMode;events / 1", 12, -0.5, 11.5);
   h_decayMode->SetLineWidth(2);
   const double n_d = t->Project("h_decayMode", "Tau_decayMode", "Tau_genPartFlav==5 && TMath::Abs(Tau_eta)<2.3 && Tau_pt>=20.");
   h_decayMode->Scale(1./n_d);

   TH1D * h_mass[12];
   TLegend * l = new TLegend(0.5, 0.75, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetHeader("decayMode");
   l->SetNColumns(2);
   int col = 2;
   for (int i = 0; i < 12; ++i) {
      h_mass[i] = (TH1D*)h_massinc->Clone("h_mass_"+TString::Itoa(i, 10));
      char buffer[100];
      sprintf(buffer, "Tau_genPartFlav==5 && Tau_decayMode==%d", i);
      const double n = t->Project(h_mass[i]->GetName(), "Tau_mass", buffer);
      if (n) {
         h_mass[i]->SetLineColor(col);
         ++col;
         h_mass[i]->Scale(1./n);
         char title[100];
         sprintf(title, "%d", i);
         l->AddEntry(h_mass[i], title, "L");
      }
   }
   h_mass[0]->Scale(0.16246);
   h_mass[0]->SetStats(0);

   TH2D * h_mdm = new TH2D("h_mdm", ";#tau_{h} mass [GeV];#tau_{h} decayMode", 40, 0., 2., 12, -0.5, 11.5);
   h_mdm->SetStats(0);
   const double n = t->Project("h_mdm", "Tau_decayMode:Tau_mass", "Tau_genPartFlav==5 && TMath::Abs(Tau_eta)<2.3 && Tau_pt>=20.");

   TCanvas * c = new TCanvas("c", "taumdm", 800, 800);
   c->Divide(2, 2);

   TPad * p1 = (TPad*)c->cd(1);
   h_massinc->Draw("HIST, E");
   h_massinc->SetLineWidth(2);
   h_massinc->SetStats(0);
   h_massinc->SetMinimum(0.);
   h_massinc->SetMaximum(0.2);
   //p1->SetLogy();   

   TPad * p2 = (TPad*)c->cd(2);
   h_decayMode->SetMarkerSize(2);
   h_decayMode->Draw("HIST, E, TEXT");
   h_decayMode->SetLineWidth(2);
   h_decayMode->SetStats(0);
   h_decayMode->SetMinimum(0.01);
   h_decayMode->SetMaximum(1.);
   p2->SetLogy();

   TPad * p3 = (TPad*)c->cd(3);
   h_mdm->Draw("COLZ");
   p3->SetLogz();

   TPad * p4 = (TPad*)c->cd(4);
   for (int i = 0; i < 12; ++i) {
      if (h_mass[i]->GetEntries()) {
         h_mass[i]->Draw("HIST, E, SAME");
      }
   }
   h_mass[0]->SetMinimum(0.);
   h_mass[0]->SetMaximum(0.2);
   l->Draw();

   c->SaveAs("./plots/taumdm.pdf");
}

void taumdm_2()
{
   const TString tag = "WJetsToLNu";
   const TString infile = "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/WJetsToLNu__A0A48A5A-15B8-914B-8DC7-E407797D4539.root";
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/70000/A0A48A5A-15B8-914B-8DC7-E407797D4539.root";

   //const TString tag = "DYJetsToLL";
   //const TString infile = "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/DYJetsToLL_M-50__51C9FDF1-F122-4943-87BA-6EFE4459F867.root";
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/100000/51C9FDF1-F122-4943-87BA-6EFE4459F867.root";

   //const TString tag = "TTJets";
   //const TString infile = "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/TTJets__3B433A98-416E-7242-B1F7-9E1153CBBC64.root";
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/3B433A98-416E-7242-B1F7-9E1153CBBC64.root";

   TFile * f = TFile::Open(infile);
   TTree * t = (TTree*)f->Get("Events");

   UInt_t nGenVisTau = 0;
   Int_t GenVisTau_status[20];
   Float_t GenVisTau_pt[20], GenVisTau_eta[20], GenVisTau_phi[20];
   t->SetBranchAddress("nGenVisTau", &nGenVisTau);
   t->SetBranchAddress("GenVisTau_status", GenVisTau_status);
   t->SetBranchAddress("GenVisTau_pt", GenVisTau_pt);
   t->SetBranchAddress("GenVisTau_eta", GenVisTau_eta);
   t->SetBranchAddress("GenVisTau_phi", GenVisTau_phi);

   UInt_t nTau = 0;
   Int_t Tau_decayMode[20];
   Float_t Tau_pt[20], Tau_eta[20], Tau_phi[20];
   t->SetBranchAddress("nTau", &nTau);
   t->SetBranchAddress("Tau_decayMode", Tau_decayMode);
   t->SetBranchAddress("Tau_pt", Tau_pt);
   t->SetBranchAddress("Tau_eta", Tau_eta);
   t->SetBranchAddress("Tau_phi", Tau_phi);

   TH2D * h = new TH2D("h", ";gen decayMode; reco decayMode", 17, -1.5, 15.5, 17, -1.5, 15.5);
   
   const int n = t->GetEntries();
   std::cout << "entries in the input tree: " << n << std::endl;
   for (int i = 0; i < n; ++i) {
      if (i%100000==0) std::cout << "beginning event: " << i << std::endl;
      t->GetEntry(i);

      for (unsigned int j = 0; j < nGenVisTau; ++j) {
         if (GenVisTau_pt[j]>=20. && TMath::Abs(GenVisTau_eta[j])<2.3) {
            TVector3 gentau;
            gentau.SetPtEtaPhi(GenVisTau_pt[j], GenVisTau_eta[j], GenVisTau_phi[j]);
            double mindr = 9.;
            int recodm = -1;
            for (unsigned int k = 0; k < nTau; ++k) {
               if (Tau_pt[k]>=20. && TMath::Abs(Tau_eta[k])<2.3) {
                  TVector3 tau;
                  tau.SetPtEtaPhi(Tau_pt[k], Tau_eta[k], Tau_phi[k]);
                  const double dr = gentau.DeltaR(tau);
                  if (dr<mindr) {
                     mindr = dr;
                     recodm = Tau_decayMode[k];
                  }
               }
            }
            if (mindr<0.3) {
               h->Fill(GenVisTau_status[j], recodm);
            } else {
               h->Fill(GenVisTau_status[j], -1);
            }
         }
      }
   }

   TCanvas * c = new TCanvas("c", "c", 400, 400);
   h->Draw("COLZ");
   h->SetStats(0);
   c->SetLogz();
   c->SaveAs("./plots/gendmdm.pdf");
}

void taumdm()
{
   taumdm_1();
   taumdm_2();
}

