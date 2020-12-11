//https://cms-nanoaod-integration.web.cern.ch/integration/master-106X/mc106X_doc.html
#include <TCut.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <iostream>

void roc()
{
   const TString tag = "WJetsToLNu";
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";
   //const TString infile = "/uscms_data/d3/fojensen/tauHATS/CMSSW_10_2_18/src/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";
   const TString infile = "root://cmseos.fnal.gov//store/user/hats/2020/Tau/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";

   //const TString tag = "DYJetsToLL";
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/E78C9017-BB6E-FE48-BA37-E059AEA79CD3.root";
   //const TString infile = "/uscms_data/d3/fojensen/tauHATS/CMSSW_10_2_18/src/E78C9017-BB6E-FE48-BA37-E059AEA79CD3.root";
   //const TString infile = "root://cmseos.fnal.gov//store/user/hats/2020/Tau/E78C9017-BB6E-FE48-BA37-E059AEA79CD3.root"

   //const TString tag = "TTJets";
   //const TString infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/8969BAAF-2D11-7449-A180-97850997CD0A.root";
   //const TString infile = "/uscms_data/d3/fojensen/tauHATS/CMSSW_10_2_18/src/8969BAAF-2D11-7449-A180-97850997CD0A.root";
   //const TString infile = "root://cmseos.fnal.gov//store/user/hats/2020/Tau/8969BAAF-2D11-7449-A180-97850997CD0A.root";
   
   std::cout << "producing ROC curve: " << tag << std::endl;

   TFile * f_sig = TFile::Open(infile);
   TTree * t_sig = (TTree*)f_sig->Get("Events");

   TFile * f_bkg = TFile::Open(infile);
   TTree * t_bkg = (TTree*)f_bkg->Get("Events");

   TCut taucut = "Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3";
   taucut = taucut && TCut("(8&Tau_idDeepTau2017v2p1VSmu) && (128&Tau_idDeepTau2017v2p1VSe) && !(Tau_decayMode==5||Tau_decayMode==6)");
   const TCut sigcut = "Tau_genPartFlav==5";
   const TCut bkgcut = "Tau_genPartFlav==0";
   TCut wpcut[7];
   for (int i = 0; i < 7; ++i) {
      char buffer[100];
      const int mask = 1<<i;
      sprintf(buffer, "%i&Tau_idDeepTau2017v2p1VSjet", mask);
      wpcut[i] = TCut(buffer);
   }

   double n_sig_tot = t_sig->GetEntries(taucut && sigcut);
   double n_bkg_tot = t_bkg->GetEntries(taucut && bkgcut);
   double n_sig[7], n_bkg[7];
   for (int i = 0; i < 7; ++i) {
      n_sig[i] = t_sig->GetEntries(taucut && sigcut && wpcut[i]);
      n_bkg[i] = t_sig->GetEntries(taucut && bkgcut && wpcut[i]);
   }

   TGraphErrors * g = new TGraphErrors(7);
   g->SetTitle(";signal efficiency;background efficiency");
   g->SetMarkerStyle(20);
   for (int i = 0; i < 7; ++i) {
      const double eff_sig = n_sig[i]/n_sig_tot;
      const double eff_sig_err = eff_sig * sqrt((1./n_sig[i])+(1./n_sig_tot));
      const double eff_bkg = n_bkg[i]/n_bkg_tot;
      const double eff_bkg_err = eff_bkg * sqrt((1./n_bkg[i])+(1./n_bkg_tot));
      g->SetPoint(i, eff_sig, eff_bkg);
      g->SetPointError(i, eff_sig_err, eff_bkg_err); 
   }

   std::cout << "inclusive efficiencies (sig, bkg)" << std::endl;
   for (int i = 0; i < 7; ++i) {
      double x,y;
      g->GetPoint(i, x, y);
      std::cout << x << ", " << y << std::endl;
   }

   TCanvas * c = new TCanvas("c_"+tag, tag, 400, 400);
   g->Draw("APE");
   g->SetMinimum(0.001);
   g->SetMaximum(1.);
   c->SetLogy();
   TAxis * a = g->GetXaxis();
   a->SetLimits(0., 1.);
   c->SaveAs("./plots/roc."+tag+".pdf");
}

