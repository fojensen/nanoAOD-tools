//https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
#include <TPaveText.h>
#include <TCut.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <iostream>

void roc()
{
   //const TString fname_sig = "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/WJetsToLNu__A0A48A5A-15B8-914B-8DC7-E407797D4539.root";
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/70000/A0A48A5A-15B8-914B-8DC7-E407797D4539.root";
  
   //const TString fname_sig = "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/VBFHToTauTau__6AC0F107-DD1C-6A4B-9730-CC94E9B2BA94.root";
   //const TString fname_sig = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/VBFHToTauTau_M125_13TeV_powheg_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1/100000/6AC0F107-DD1C-6A4B-9730-CC94E9B2BA94.root";

   //const TString fname_bkg = "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/DYJetsToLL_M-50__51C9FDF1-F122-4943-87BA-6EFE4459F867.root";
   const TString fname_bkg = "0262164B-9CA8-8F44-A9B9-2E0056FD9428.root";
   const TString fname_sig = fname_bkg;
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/100000/51C9FDF1-F122-4943-87BA-6EFE4459F867.root";

   //const TString infile = "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/TTJets__3B433A98-416E-7242-B1F7-9E1153CBBC64.root";
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/3B433A98-416E-7242-B1F7-9E1153CBBC64.root";

   TFile * f_sig = TFile::Open(fname_sig);
   TTree * t_sig = (TTree*)f_sig->Get("Events");

   TFile * f_bkg = TFile::Open(fname_bkg);
   TTree * t_bkg = (TTree*)f_bkg->Get("Events");

   TCut taucut = "Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6";
   taucut = taucut && TCut("(4&Tau_idDeepTau2017v2p1VSe) && (8&Tau_idDeepTau2017v2p1VSmu)");
   taucut = taucut && TCut("Tau_decayMode==0||Tau_decayMode==1||Tau_decayMode==2");
   //taucut = taucut && TCut("Tau_decayMode==10||Tau_decayMode==11||Tau_decayMode==12");
   const TCut sigcut = "Tau_genPartFlav==5";
   const TCut bkgcut = "Tau_genPartFlav==0";

   TCut wpcut[8];
   for (int i = 0; i < 8; ++i) {
      char buffer[100];
      const int mask = 1<<i;
      sprintf(buffer, "%i&Tau_idDeepTau2017v2p1VSjet", mask);
      std::cout << buffer << std::endl;
      wpcut[i] = TCut(buffer);
   }

   const double n_sig_tot = t_sig->GetEntries(taucut && sigcut);
   const double n_bkg_tot = t_bkg->GetEntries(taucut && bkgcut);
   double n_sig[8], n_bkg[8];
   for (int i = 0; i < 8; ++i) {
      n_sig[i] = t_sig->GetEntries(taucut && sigcut && wpcut[i]);
      n_bkg[i] = t_bkg->GetEntries(taucut && bkgcut && wpcut[i]);
   }

   TGraphErrors * g = new TGraphErrors(8);
   g->SetTitle(";#tau id efficiency;jet mistag efficiency");
   g->SetMarkerStyle(20);
   for (int i = 0; i < 8; ++i) {
      const double eff_sig = n_sig[i]/n_sig_tot;
      const double eff_sig_err = eff_sig * sqrt((1./n_sig[i])+(1./n_sig_tot));
      const double eff_bkg = n_bkg[i]/n_bkg_tot;
      const double eff_bkg_err = eff_bkg * sqrt((1./n_bkg[i])+(1./n_bkg_tot));
      g->SetPoint(i, eff_sig, eff_bkg);
      g->SetPointError(i, eff_sig_err, eff_bkg_err); 
   }

   std::cout << "inclusive efficiencies (sig, bkg)" << std::endl;
   for (int i = 0; i < 8; ++i) {
      double x, y;
      g->GetPoint(i, x, y);
      std::cout << x << ", " << y << std::endl;
   }

   TCanvas * c = new TCanvas("c", "c", 400, 400);
   g->Draw("APE");
   g->SetMinimum(0.001);
   g->SetMaximum(1.);
   c->SetLogy();
   TAxis * a = g->GetXaxis();
   a->SetLimits(0., 1.);

   TPaveText *pt = new TPaveText(.5, .25, .875, .3, "NB, NDC");
   pt->SetFillColor(0);
   pt->AddText("1-prong");
   //pt->AddText("3-prong");
   pt->Draw();

   c->SaveAs("./plots/roc.1prong.pdf");
   //c->SaveAs("./plots/roc.3prong.pdf");
}

