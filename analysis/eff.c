//https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <iostream>
#include <TLegend.h>

void eff(const bool isSig=true)
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

   std::cout << "producing efficiency curves: " << tag << std::endl;
   if (isSig) {
      std::cout << "treated as signal" << std::endl;
   } else {
      std::cout << "treated as background (i.e. mistag)" << std::endl;
   }

   TFile * f = TFile::Open(infile);
   TTree * t = (TTree*)f->Get("Events");
  
   TH1D *h_denom = new TH1D("h_denom", ";#tau_{h} p_{T} [GeV];#tau_{h} / 10 GeV", 10, 20., 120.);
   TH1D *h_num[4];
   for (int i = 0; i < 4; ++i) {
      h_num[i] = (TH1D*)h_denom->Clone("h_num_"+TString::Itoa(i, 10));
   }
 
   UInt_t nTau = 0;
   Float_t Tau_pt[20];
   Float_t Tau_eta[20];
   UChar_t Tau_genPartFlav[20];
   Int_t Tau_decayMode[20];
   UChar_t Tau_idDeepTau2017v2p1VSe[20];
   UChar_t Tau_idDeepTau2017v2p1VSmu[20];
   UChar_t Tau_idDeepTau2017v2p1VSjet[20];

   t->SetBranchAddress("nTau", &nTau);
   t->SetBranchAddress("Tau_pt", Tau_pt);
   t->SetBranchAddress("Tau_eta", Tau_eta);
   t->SetBranchAddress("Tau_genPartFlav", Tau_genPartFlav);
   t->SetBranchAddress("Tau_decayMode", Tau_decayMode);
   t->SetBranchAddress("Tau_idDeepTau2017v2p1VSe", Tau_idDeepTau2017v2p1VSe);
   t->SetBranchAddress("Tau_idDeepTau2017v2p1VSmu", Tau_idDeepTau2017v2p1VSmu);
   t->SetBranchAddress("Tau_idDeepTau2017v2p1VSjet", Tau_idDeepTau2017v2p1VSjet);

   int tauMatch;
   isSig ? tauMatch=5 : tauMatch=2;

   const int n = t->GetEntries();
   std::cout << "entries in the tree: " << n << std::endl;
   int ndenom = 0;
   for (int i = 0; i < n; ++i) {
      if (i%100000==0) std::cout << "beginning event: " << i << std::endl;
      t->GetEntry(i);
      for (unsigned int j = 0; j < nTau; ++j) {
         if (Tau_genPartFlav[j]==tauMatch) {
            const bool tauID = (32&Tau_idDeepTau2017v2p1VSjet[j]) && (32&Tau_idDeepTau2017v2p1VSe[j]) && !(Tau_decayMode[j]==5||Tau_decayMode[j]==6);
            if (Tau_pt[j]>=20. && TMath::Abs(Tau_eta[j])<2.3 && tauID) {
               h_denom->Fill(Tau_pt[j]);
               ++ndenom;
               for (int k = 0; k < 4; ++k) {
                  const int mask = 1<<k;
                  //std::cout << mask << std::endl;
                  const bool passid = mask&Tau_idDeepTau2017v2p1VSmu[j];
                  if (passid) {
                     h_num[k]->Fill(Tau_pt[j]);
                  } else {
                     break;
                  }
               }
            }
         }
      }
      if (ndenom>=10000) break;
   }

   TGraphAsymmErrors *g[4];
   TLegend * l = new TLegend(0.25, 0.175, 0.875, 0.3);
   l->SetNColumns(2);
   l->SetBorderSize(0);
   const TString labels[4] = {"VLoose" ,"Loose", "Medium", "Tight"};
   for (int i = 0; i < 4; ++i) {    
      g[i] = new TGraphAsymmErrors();
      g[i]->Divide(h_num[i], h_denom);
      g[i]->SetLineColor(i+2);
      g[i]->SetMarkerColor(i+2);
      g[i]->SetMarkerStyle(7);
      char buffer[100];
      sprintf(buffer, ";%s;tagging efficiency", h_denom->GetXaxis()->GetTitle());
      g[i]->SetTitle(buffer);
      l->AddEntry(g[i], labels[i], "P");
   }

   TCanvas * c = new TCanvas("c", tag, 400, 400);
   g[0]->Draw("APE");
   if (isSig) {
      g[0]->SetMinimum(0.);
      g[0]->SetMaximum(1.);
   } else {
      g[0]->SetMinimum(0.001);
      g[0]->SetMaximum(1.);
      c->SetLogy();
   }
   for (int i = 1; i < 4; ++i) g[i]->Draw("PE, SAME");
   l->Draw();
   if (isSig) {
      c->SaveAs("./plots/eff."+tag+".sig.pdf");
   } else {
      c->SaveAs("./plots/eff."+tag+".bkg.pdf");
   }
}

