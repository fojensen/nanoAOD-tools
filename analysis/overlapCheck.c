#include <TLegend.h>
#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TH1D.h>
#include <TCanvas.h>

//https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
void runPoint(const TString infile, const TString tag)
{
   // download the file
   char cmd_download[1000];
   sprintf(cmd_download, "xrdcp root://cmsxrootd.fnal.gov//%s ./", infile.Data());
   std::cout << cmd_download << std::endl;
   system(cmd_download);
   const char * fname = basename(infile.Data());

   TFile * f = TFile::Open(fname);
   TTree * t = (TTree*)f->Get("Events");
 
   UInt_t nMuon = 0;
   Float_t Muon_pt[100];
   Float_t Muon_eta[100];
   Float_t Muon_phi[100];
   Float_t Muon_mass[100];
   UChar_t Muon_genPartFlav[100];
 
   UInt_t nTau = 0;
   Float_t Tau_pt[100];
   Float_t Tau_eta[100];
   Float_t Tau_phi[100];
   Float_t Tau_mass[100];
   UChar_t Tau_genPartFlav[100];

   UInt_t nJet = 0;
   Float_t Jet_pt[100];
   Float_t Jet_eta[100];
   Float_t Jet_phi[100];
   Float_t Jet_mass[100];
   Int_t Jet_jetId[100];
   Float_t Jet_btagDeepB[100];
   
   t->SetBranchAddress("nMuon", &nMuon);
   t->SetBranchAddress("Muon_pt", Muon_pt);
   t->SetBranchAddress("Muon_eta", Muon_eta);
   t->SetBranchAddress("Muon_phi", Muon_phi);
   t->SetBranchAddress("Muon_mass", Muon_mass);
   t->SetBranchAddress("Muon_genPartFlav", Muon_genPartFlav);
   
   t->SetBranchAddress("nTau", &nTau);
   t->SetBranchAddress("Tau_pt", Tau_pt);
   t->SetBranchAddress("Tau_eta", Tau_eta);
   t->SetBranchAddress("Tau_phi", Tau_phi);
   t->SetBranchAddress("Tau_mass", Tau_mass);
   t->SetBranchAddress("Tau_genPartFlav", Tau_genPartFlav);

   t->SetBranchAddress("nJet", &nJet);
   t->SetBranchAddress("Jet_pt", Jet_pt);
   t->SetBranchAddress("Jet_eta", Jet_eta);
   t->SetBranchAddress("Jet_phi", Jet_phi);
   t->SetBranchAddress("Jet_mass", Jet_mass);
   t->SetBranchAddress("Jet_btagDeepB", Jet_btagDeepB);
   t->SetBranchAddress("Jet_jetId", Jet_jetId);
 
   TH1D * h_nb = new TH1D("h_nb", ";# of b-tagged jets;events / 1", 5, -0.5, 4.5);
   h_nb->SetLineWidth(2);
   h_nb->SetStats(0);
   h_nb->Sumw2();
   h_nb->SetLineColor(6);
   TH1D * h_nb_overlap = (TH1D*)h_nb->Clone("h_nb_overlap");
   h_nb_overlap->SetLineColor(7);
 
   int ntot = 0;
   for (int i = 0; i < t->GetEntries(); ++i) {
      if (i%1000==0) std::cout << "beginning entry " << i << std::endl;
      t->GetEntry(i);

      TLorentzVector Muon_;
      int nmu = 0;
      for (UInt_t j = 0; j < nMuon; ++j) {
         if (Muon_genPartFlav[j]==15 && Muon_pt[j]>=27. && TMath::Abs(Muon_eta[j]<2.4)) {
            Muon_.SetPtEtaPhiM(Muon_pt[j], Muon_eta[j], Muon_phi[j], Muon_mass[j]);
            ++nmu;
         }
      }
      if (nmu!=1) continue;

      TLorentzVector Tau_;
      int ntau = 0;
      for (UInt_t j = 0; j < nTau; ++j) {
         if (Tau_genPartFlav[j]==5 && Tau_pt[j]>=20. && TMath::Abs(Tau_eta[j])<2.3) {
            Tau_.SetPtEtaPhiM(Tau_pt[j], Tau_eta[j], Tau_phi[j], Tau_mass[j]);
            ++ntau;
         }
      }
      if (ntau!=1) continue;

      if (Muon_.DeltaR(Tau_)<0.7) continue;

      int nb_overlap = 0;
      int nb = 0;
      for (UInt_t j = 0; j < nJet; ++j) {
         if (Jet_jetId[j] && Jet_pt[j]>=20. && TMath::Abs(Jet_eta[j])<2.5) {
            TLorentzVector jet;
            jet.SetPtEtaPhiM(Jet_pt[j], Jet_eta[j], Jet_phi[j], Jet_mass[j]);
            const double dr_mu = Muon_.DeltaR(jet);
            const double dr_tau = Tau_.DeltaR(jet);
            //https://twiki.cern.ch/CMS/BtagRecommendation102X
            //if (Jet_btagDeepB[j]>=0.1241) {
            //if (Jet_btagDeepB[j]>=0.4184) {
            if (Jet_btagDeepB[j]>=0.7527) {
               ++nb_overlap;
               if (dr_mu>=0.4 && dr_tau>=0.4) {
                  ++nb;
               }
            }
         }
      }

      h_nb->Fill(nb);
      h_nb_overlap->Fill(nb_overlap);
      ++ntot;
      //if (ntot==1000) break;
   }

   TLegend * l = new TLegend(0.5, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->AddEntry(h_nb, "no overlap", "L");
   l->AddEntry(h_nb_overlap, "allow overlap", "L");

   TCanvas * c = new TCanvas("c_"+tag, tag, 400, 400);
   h_nb->Draw("HIST, E");
   h_nb_overlap->Draw("HIST, E, SAME");
   c->SetLogy();
   h_nb->SetMinimum(0.001);
   h_nb->SetMaximum(1.);
   l->Draw();
   c->SaveAs("./overlapCheck."+tag+".pdf");

   // delete the file
   char cmd_delete[1000];
   sprintf(cmd_delete, "rm %s", fname);
   std::cout << cmd_delete << std::endl;
   system(cmd_delete);
}

void overlapCheck()
{
   const TString infile1 = "/store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/40000/EE8FEFE9-39C6-4244-BE22-42EEA0B786FB.root";
   const TString tag1 = "DYJetsToLL_M-50";
   runPoint(infile1, tag1);

   const TString infile2 = "/store/mc/RunIIAutumn18NanoAODv6/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/FCD5C184-19F0-B34B-8E70-F7D280E392EA.root";
   const TString tag2 = "TTTo2L2Nu";
   runPoint(infile2, tag2);

   const TString infile3 = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m250_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/7FEC7B94-611C-364A-9A12-B9BD43C01EC3.root";
   const TString tag3 = "taustar_m250";
   runPoint(infile3, tag3);
}

