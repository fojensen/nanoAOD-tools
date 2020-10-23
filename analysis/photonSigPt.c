#include <TStyle.h>
#include <TCut.h>
#include <TTree.h>
#include "addOverflow.h"
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TFile.h>
#include <iostream>

TH1D * getFractions(TH1D* hin)
{
   std::cout << hin->GetName() << std::endl;
   TH1D * hout = (TH1D*)hin->Clone("hout");
   const double inc = hin->Integral();
   std::cout << "inc: " << inc << std::endl;
   const int n = hin->GetNbinsX();
   std::cout << "n: " << n << std::endl;
   for (int i = 0; i < n+1; ++i) {
      const double eff = hin->Integral(0, i) / inc;
      std::cout << "low edge: " << hin->GetBinLowEdge(i) << " eff: " << eff << std::endl;
      hout->SetBinContent(i, eff);
   }
   return hout;
}

TH1D * runPoint(const TString infile, const TString tag)
{
   char buffer[1000];
   sprintf(buffer, "root://cmsxrootd.fnal.gov//%s", infile.Data());
   //sprintf(buffer, "%s", infile.Data());
   TFile * f = TFile::Open(buffer);
   TTree * t = (TTree*)f->Get("Events");

   TH1D * h = new TH1D("h_"+tag, ";photon p_{T} [GeV];events / 25 GeV", 8, 0., 200.);
   h->SetLineWidth(2);
   h->SetStats(0);
   h->SetMarkerSize(2);
   const TCut cutMuon = "Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=4)==1";
   const TCut cutTau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (64&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))==1";
   const TCut cutTrigger = "HLT_IsoMu27 || HLT_IsoMu24";

   std::cout << "start copy the tree" << std::endl;
   TTree * t_skim = (TTree*)t->CopyTree(cutMuon && cutTau && cutTrigger);
   std::cout << "end copy the tree" << std::endl;

   const double n1 = t_skim->GetEntries();
   const double n2 = t_skim->Project(h->GetName(), "Photon_pt", "TMath::Abs(Photon_eta)<2.5 && Photon_electronVeto && Photon_mvaID_WP90");

   std::cout << n1 << " " << n2 << std::endl;

   addOverflow(h);

   h->Scale(1./n2);
   return h;
}

void photonSigPt()
{
   gStyle->SetPaintTextFormat("4.3f");

   //const TString f250 = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m250_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/7FEC7B94-611C-364A-9A12-B9BD43C01EC3.root";
   //const TString f250 = "7FEC7B94-611C-364A-9A12-B9BD43C01EC3.root";
   //TH1D * h_250 = runPoint(f250, "250");
   //h_250->SetLineColor(6);

   const TString f375 = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m375_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/100000/FF34EF39-6132-0347-A0E5-6361A85F15C2.root";
   TH1D * h_375 = runPoint(f375, "375");
   h_375->SetLineColor(7);

   //const TString f500 = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m500_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/B97EF17B-4634-EB45-8776-BF8CAE1E634A.root";
   //TH1D * h_500 = runPoint(f500);
   //h_500->SetLineColor(8);

   //const TString f625 = "/store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m625_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/100000/300236C3-B93D-8847-AE65-1973AA2F1506.root";
   //TH1D * h_625 = runPoint(f625);
   //h_625->SetLineColor(9);

   //TH1D * c_250 = getFractions(h_250);
   TH1D * c_375 = getFractions(h_375);
   //TH1D * c_500 = getFractions(h_500);
   //TH1D * c_625 = getFractions(h_625);

   TCanvas * c = new TCanvas("c", "", 800, 400);
   c->Divide(2, 1);
   
   TPad * p1 = (TPad*)c->cd(1);
   //h_250->Draw("HIST, E, TEXT");
   //h_250->SetMaximum(1.);
   //h_250->SetMinimum(0.01);
   p1->SetLogy();
   h_375->Draw("HIST, E, SAME");
   //h_500->Draw("HIST, E, SAME");
   //h_625->Draw("HIST, E, SAME");

   TLegend * l = new TLegend(0.25, 0.6, 0.5, 0.875);
   //l->SetNColumns(2);
   l->SetBorderSize(0);
   l->SetHeader("#tau* mass");
   //l->AddEntry(h_250, "250 GeV", "L");
   l->AddEntry(h_375, "375 GeV", "L");
   //l->AddEntry(h_500, "500 GeV", "L");
   //l->AddEntry(h_625, "625 GeV", "L");
   l->Draw();

   TPad * p2 = (TPad*)c->cd(2);
   //c_250->Draw("HIST, E, TEXT");
   //c_250->SetMaximum(1.);
   //c_250->SetMinimum(0.01);
   c_375->Draw("HIST, E, SAME");
   //c_500->Draw("HIST, E, SAME");
   //c_625->Draw("HIST, E, SAME");
   l->Draw();
   p2->SetLogy();

   c->SaveAs("./plots/photonsigpt.pdf");
}

