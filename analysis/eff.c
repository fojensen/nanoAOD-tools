//https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <iostream>
//#include <TLegend.h>

void eff(const bool isSig=true)
{
   TString infile;
   if (isSig) {
//      infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";
      infile = "../../../E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root";
   } else {
      //infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/240000/2438666B-82C0-4545-8304-1DA4B7A4E46C.root";
      //infile = "2438666B-82C0-4545-8304-1DA4B7A4E46C.root";
      //infile = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/QCD_Pt_50to80_TuneCP5_13TeV_pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/60000/BAEC21E7-03AB-6C41-B1BD-646EEB265CCA.root";
      infile = "../../../BAEC21E7-03AB-6C41-B1BD-646EEB265CCA.root";
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
         const bool tauID = (8&Tau_idDeepTau2017v2p1VSmu[j]) && (128&Tau_idDeepTau2017v2p1VSe[j]) && !(Tau_decayMode[j]==5||Tau_decayMode[j]==6);
         if (Tau_pt[j]>=20. && Tau_pt[j]<120. && TMath::Abs(Tau_eta[j])<2.3 && tauID) {
            if (Tau_genPartFlav[j]==tauMatch) {
               //if (Tau_jetIdx[j]==-1) std::cout << "no matching jet?" << std::endl;
               h_pt->Fill(Tau_pt[j]);
               h_eta->Fill(TMath::Abs(Tau_eta[j]));
               for (int k = 0; k < 8; ++k) {
                  const int mask = 1<<k;
                  const bool passid = mask&Tau_idDeepTau2017v2p1VSjet[j];
                  //std::cout << mask << std::endl;
                  if (passid) {
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

   TString title;
   isSig ? title = "signal" : title = "background";
 
   TCanvas * c1 = new TCanvas("c1", title, 800, 400);
   c1->Divide(2, 1);

   TPad * p11 = (TPad*)c1->cd(1);
   g_pt[0]->Draw("APE");
   if (isSig) {
      g_pt[0]->SetMinimum(0.);
      g_pt[0]->SetMaximum(1.1);
   } else {
      g_pt[0]->SetMinimum(0.001);
      g_pt[0]->SetMaximum(10.);
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
      g_eta[0]->SetMaximum(10.);
      p12->SetLogy();
   }
   for (int i = 1; i < 8; ++i) g_eta[i]->Draw("PE, SAME"); 
   //l->Draw();
   isSig ? c1->SaveAs("./plots/eff.WJetsToLNu.pdf") : c1->SaveAs("./plots/eff.QCD_Pt_30to50.pdf");

   TCanvas *c2 = new TCanvas("c2", title, 800, 400);
   c2->Divide(2, 1);
   TPad * p21 = (TPad*)c2->cd(1);
   h_pt->Draw("HIST, E");
   h_pt->SetMinimum(1.);
   p21->SetLogy();
   c2->cd(2);
   h_eta->Draw("HIST, E");
   h_eta->SetMinimum(0.);
   isSig ? c2->SaveAs("./plots/dists.WJetsToLNu.pdf") : c2->SaveAs("./plots/dists.QCD_Pt_30to50.pdf");
}

