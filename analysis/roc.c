//https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
#include <TCut.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <iostream>

void roc()
{
   const TString sigfile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";
   //const TString sigfile = "../../../E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";
   TFile * f_sig = TFile::Open(sigfile);
   TTree * t_sig = (TTree*)f_sig->Get("Events");

   const TString bkgfile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/BAEC21E7-03AB-6C41-B1BD-646EEB265CCA.root";
   //const TString bkgfile = "../../../BAEC21E7-03AB-6C41-B1BD-646EEB265CCA.root";
   TFile * f_bkg = TFile::Open(bkgfile);
   TTree * t_bkg = (TTree*)f_bkg->Get("Events");

   TCut taucut = "Tau_pt>=20. && Tau_pt<120. && TMath::Abs(Tau_eta)<2.3";
   taucut = taucut && TCut("(8&Tau_idDeepTau2017v2p1VSmu) && (128&Tau_idDeepTau2017v2p1VSe) && !(Tau_decayMode==5||Tau_decayMode==6)");
   const TCut sigcut = "Tau_genPartFlav==5";
   const TCut bkgcut = "Tau_genPartFlav==0";
   TCut wpcut[8];
   for (int i = 0; i < 8; ++i) {
      char buffer[100];
      const int mask = 1<<i;
      sprintf(buffer, "%i&Tau_idDeepTau2017v2p1VSjet", mask);
      wpcut[i] = TCut(buffer);
   }

   std::cout << "projecting denominator" << std::endl;
   double n_sig_tot = t_sig->GetEntries(taucut && sigcut);
   double n_bkg_tot = t_bkg->GetEntries(taucut && bkgcut);
   double n_sig[8], n_bkg[8];
   for (int i = 0; i < 8; ++i) {
      std::cout << "projecting numerator " << i << std::endl;
      n_sig[i] = t_sig->GetEntries(taucut && sigcut && wpcut[i]);
      n_bkg[i] = t_sig->GetEntries(taucut && bkgcut && wpcut[i]);
   }

   TGraphErrors * g = new TGraphErrors(8);
   g->SetTitle(";signal efficiency;background efficiency");
   g->SetMarkerStyle(20);
   for (int i = 0; i < 8; ++i) {
      const double eff_sig = n_sig[i]/n_sig_tot;
      const double eff_sig_err = eff_sig * sqrt((1./n_sig[i])+(1./n_sig_tot));
      const double eff_bkg = n_bkg[i]/n_bkg_tot;
      const double eff_bkg_err = eff_bkg * sqrt((1./n_bkg[i])+(1./n_bkg_tot));
      g->SetPoint(i, eff_sig, eff_bkg);
      g->SetPointError(i, eff_sig_err, eff_bkg_err);
   }

   TCanvas * c = new TCanvas("c", "", 400, 400);
   g->Draw("APE");
   g->SetMinimum(0.0001);
   g->SetMaximum(1.);
   c->SetLogy();
   TAxis * a = g->GetXaxis();
   a->SetLimits(0., 1.);
   c->SaveAs("./plots/roc.pdf");
}

