//https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <iostream>
//#include <TLegend.h>

void eff()
{
   const bool isSig = true;
   const TString tag = "WJetsToLNu";

   TString infile;
   if (tag=="WJetsToLNu") {   
      //infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";
      //infile = "/uscms_data/d3/fojensen/tauHATS/CMSSW_10_2_18/src/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";
      infile = "root://cmseos.fnal.gov//store/user/hats/2020/Tau/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";
   }
   if (tag=="DYJetsToLL") {
      //infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/E78C9017-BB6E-FE48-BA37-E059AEA79CD3.root";
      //infile = "/uscms_data/d3/fojensen/tauHATS/CMSSW_10_2_18/src/E78C9017-BB6E-FE48-BA37-E059AEA79CD3.root";
      infile = "root://cmseos.fnal.gov//store/user/hats/2020/Tau/E78C9017-BB6E-FE48-BA37-E059AEA79CD3.root";
   }
   if (tag=="TTJets") {
      //infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/8969BAAF-2D11-7449-A180-97850997CD0A.root";
      //infile = "/uscms_data/d3/fojensen/tauHATS/CMSSW_10_2_18/src/8969BAAF-2D11-7449-A180-97850997CD0A.root";
      infile = "root://cmseos.fnal.gov//store/user/hats/2020/Tau/8969BAAF-2D11-7449-A180-97850997CD0A.root";
   }

   std::cout << "producing efficiency curves: " << tag << std::endl;
   if (isSig) {
      std::cout << "treated as signal" << std::endl;
   } else {
      std::cout << "treated as background (i.e. mistag)" << std::endl;
   }

   TFile * f = TFile::Open(infile);
   TTree * t = (TTree*)f->Get("Events");
  
   TH1D *h_pt = new TH1D("h_pt", ";#tau_{h} p_{T} [GeV];#tau_{h} / 10 GeV", 10, 20., 120.);
   TH1D *h_eta = new TH1D("h_eta", ";#tau_{h} |#eta|;#tau_{h} / 0.23", 10, 0., 2.3);
   TH1D *h_pt_num[8], *h_eta_num[8];
   for (int i = 0; i < 8; ++i) {
      h_pt_num[i] = (TH1D*)h_pt->Clone("h_pt_num_"+TString::Itoa(i, 10));
      h_eta_num[i] = (TH1D*)h_eta->Clone("h_eta_num_"+TString::Itoa(i, 10));
   }
 
   UInt_t nTau = 0;
   Float_t Tau_pt[50];
   Float_t Tau_eta[50];
   UChar_t Tau_genPartFlav[50];
   Int_t Tau_decayMode[50];
   UChar_t Tau_idDeepTau2017v2p1VSe[50];
   UChar_t Tau_idDeepTau2017v2p1VSmu[50];
   UChar_t Tau_idDeepTau2017v2p1VSjet[50];
   //Int_t Tau_jetIdx[50];

   t->SetBranchAddress("nTau", &nTau);
   t->SetBranchAddress("Tau_pt", Tau_pt);
   t->SetBranchAddress("Tau_eta", Tau_eta);
   t->SetBranchAddress("Tau_genPartFlav", Tau_genPartFlav);
   t->SetBranchAddress("Tau_decayMode", Tau_decayMode);
   t->SetBranchAddress("Tau_idDeepTau2017v2p1VSe", Tau_idDeepTau2017v2p1VSe);
   t->SetBranchAddress("Tau_idDeepTau2017v2p1VSmu", Tau_idDeepTau2017v2p1VSmu);
   t->SetBranchAddress("Tau_idDeepTau2017v2p1VSjet", Tau_idDeepTau2017v2p1VSjet);
   //t->SetBranchAddress("Tau_jetIdx", Tau_jetIdx);

   int tauMatch;
   isSig ? tauMatch=5 : tauMatch=0;

   int n = t->GetEntries();
   std::cout << "entries in the tree: " << n << std::endl;
   for (int i = 0; i < n; ++i) {
      if (i%100000==0) std::cout << "beginning event: " << i << std::endl;
      t->GetEntry(i);
      for (unsigned int j = 0; j < nTau; ++j) {
         if (Tau_genPartFlav[j]==tauMatch) {
            const bool tauID = (8&Tau_idDeepTau2017v2p1VSmu[j]) && (128&Tau_idDeepTau2017v2p1VSe[j]) && !(Tau_decayMode[j]==5||Tau_decayMode[j]==6);
            if (Tau_pt[j]>=20. && TMath::Abs(Tau_eta[j])<2.3 && tauID) {
               h_pt->Fill(Tau_pt[j]);
               h_eta->Fill(TMath::Abs(Tau_eta[j]));
               for (int k = 0; k < 8; ++k) {
                  const int mask = 1<<k;
                  const bool passid = mask&Tau_idDeepTau2017v2p1VSjet[j];
                  //std::cout << mask << std::endl;
                  if (passid) {
                     const bool tauID = (8&Tau_idDeepTau2017v2p1VSmu[j]) && (128&Tau_idDeepTau2017v2p1VSe[j]) && !(Tau_decayMode[j]==5||Tau_decayMode[j]==6);
                     h_pt_num[k]->Fill(Tau_pt[j]);
                     h_eta_num[k]->Fill(TMath::Abs(Tau_eta[j]));
                  } else {
                     break;
                  }
               }
            }
         }
      }
   }

   TGraphAsymmErrors *g_pt[8], *g_eta[8];
   //TLegend * l = new TLegend(0.25, 0.7, 0.875, 0.875);
   //l->SetNColumns(4);
   //l->SetBorderSize(0);
   //const TString labels[8] = {"VVVLoose", "VVLoose" ,"VLoose" ,"Loose", "Medium", "Tight", "VTight", "VVTight"};
   for (int i = 0; i < 8; ++i) {    
      g_pt[i] = new TGraphAsymmErrors();
      g_pt[i]->Divide(h_pt_num[i], h_pt);
      g_pt[i]->SetLineColor(i+2);
      g_pt[i]->SetMarkerColor(i+2);
      g_pt[i]->SetMarkerStyle(7);
      char buffer_pt[100];
      sprintf(buffer_pt, ";%s;tagging efficiency", h_pt->GetXaxis()->GetTitle());
      g_pt[i]->SetTitle(buffer_pt);
      //l->AddEntry(g_pt[i], labels[i], "P");
      g_eta[i] = new TGraphAsymmErrors();
      g_eta[i]->Divide(h_eta_num[i], h_eta);
      g_eta[i]->SetLineColor(i+2);
      g_eta[i]->SetMarkerColor(i+2);
      g_eta[i]->SetMarkerStyle(7);
      char buffer_eta[100];
      sprintf(buffer_eta, ";%s;tagging efficiency", h_eta->GetXaxis()->GetTitle());
      g_eta[i]->SetTitle(buffer_eta);
   }

   TCanvas * c1 = new TCanvas("c1", tag, 800, 400);
   c1->Divide(2, 1);

   TPad * p11 = (TPad*)c1->cd(1);
   g_pt[0]->Draw("APE");
   if (isSig) {
      g_pt[0]->SetMinimum(0.);
      g_pt[0]->SetMaximum(1.);
   } else {
      g_pt[0]->SetMinimum(0.001);
      g_pt[0]->SetMaximum(1.);
      p11->SetLogy();
   }
   for (int i = 1; i < 8; ++i) g_pt[i]->Draw("PE, SAME");
   //l->Draw();

   TPad * p12 = (TPad*)c1->cd(2);
   g_eta[0]->Draw("APE");
   if (isSig) {
      g_eta[0]->SetMinimum(0.);
      g_eta[0]->SetMaximum(1.1);
   } else {
      g_eta[0]->SetMinimum(0.001);
      g_eta[0]->SetMaximum(1.1);
      p12->SetLogy();
   }
   for (int i = 1; i < 8; ++i) g_eta[i]->Draw("PE, SAME");  
   //l->Draw();

   if (isSig) {
      c1->SaveAs("./plots/sig."+tag+".pdf");
   } else {
      c1->SaveAs("./plots/bkg."+tag+".pdf");
   }

   /*TCanvas *c2 = new TCanvas("c2", tag, 800, 400);
   c2->Divide(2, 1);
   TPad * p21 = (TPad*)c2->cd(1);
   h_pt->Draw("HIST, E");
   h_pt->SetMinimum(1.);
   p21->SetLogy();
   c2->cd(2);
   h_eta->Draw("HIST, E");
   h_eta->SetMinimum(0.);
   if (isSig) {
      c2->SaveAs("./plots/eff."+tag+".dists.pdf");
   } else {
      c2->SaveAs("./plots/mis."+tag+".dists.pdf");
   }*/
}

