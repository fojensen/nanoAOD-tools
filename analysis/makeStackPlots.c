#include <iostream>
#include <THStack.h>
#include <TCut.h>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>

void runPoint(TH1D * h, const TString var)
{
   std::cout << "plotting " << var << std::endl;
   const TCut baseline = "MuMuProducer_HavePair==0 && MuTauProducer_HavePair==1";

   TFile * f_data = TFile::Open("./outputData/SingleMuon_2018D.root");
   TTree * t_data = (TTree*)f_data->Get("Events"); 
   TH1D * h_data = (TH1D*)h->Clone("h_data_"+TString(h->GetName()));
   t_data->Project(h_data->GetName(), var, baseline);

   const double lumi = 31742.979;
   TString samples[3] = {"TTJets", "DYJetsToLL_M-50", "WJetsToLNu"};
   double xsweight[3];
   xsweight[0] = lumi * 831.76 / 10244307.;
   xsweight[1] = lumi * 6025.2 / 100194597.;
   xsweight[2] = lumi * 61334.9 / 70454125.;

   THStack * s = new THStack("s", "");
   s->SetTitle(h->GetTitle());
   TH1D * h_mc[3];
   for (int i = 0; i < 3; ++i) {
      TFile * f = TFile::Open("./outputData/"+samples[i]+".root");
      TTree * t = (TTree*)f->Get("Events");
      h_mc[i] = (TH1D*)h->Clone("h_mc_"+TString(h->GetName())+"_"+TString::Itoa(i, 10));
      h_mc[i]->SetFillColor(2+i);
      char buffer[100];
      sprintf(buffer, "%f * (%s)", xsweight[i], TString(baseline).Data());
      t->Project(h_mc[i]->GetName(), var, buffer);
      std::cout << h_mc[i]->Integral() << std::endl;
      s->Add(h_mc[i]);
   }
   
   TCanvas * c = new TCanvas("c_"+TString(h->GetName()), var, 400, 400);
   h_data->SetMarkerStyle(20);
   h_data->Draw("PE, SAME");
   h_data->SetStats(0);
   h_data->SetMinimum(100.);
   h_data->SetMaximum(100000000.);
   c->SetLogy();
   s->Draw("HIST, SAME");
   h_data->Draw("PE, SAME");

   TLegend * l = new TLegend(0.3, 0.75, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   l->AddEntry(h_data, "data", "P");
   for (int i = 0; i < 3; ++i) l->AddEntry(h_mc[i], samples[i], "F");
   l->Draw();
}

void makeStackPlots()
{
   TH1D * h_tauPt = new TH1D("h_tauPt", ";#tau_{h} p_{T} [GeV];events / 25 GeV", 10, 0., 250.);
   runPoint(h_tauPt, "Tau_pt[MuTauProducer_TauIdx]");

   TH1D * h_muPt = new TH1D("h_muPt", ";#mu p_{T} [GeV];events / 25 GeV", 10, 0., 250.);
   runPoint(h_muPt, "Muon_pt[MuTauProducer_MuIdx]");

   TH1D * h_mT = new TH1D("h_mT", ";m_{T} [GeV];events / 25 GeV", 10, 0., 250.);
   runPoint(h_mT, "MuTauProducer_mT");

   TH1D * h_nBJetT = new TH1D("h_nBJetT", ";# of b-tagged jets (tight);events / 1", 5, -0.5, 4.5);
   runPoint(h_nBJetT, "MuTauProducer_nBJetT");

   TH1D * h_nBJetM = new TH1D("h_nBJet", ";# of b-tagged jets (medium);events / 1", 5, -0.5, 4.5);
   runPoint(h_nBJetM, "MuTauProducer_nBJetM");

   TH1D * h_nJet = new TH1D("h_nJet", ";# of jets;events / 1", 7, -0.5, 6.5);
   runPoint(h_nJet, "MuTauProducer_nJet");

   TH1D * h_VisMass = new TH1D("h_VisMass", ";#mu+#tau_{h} visible mass [GeV];events / 25 GeV", 10, 0., 250.);
   runPoint(h_VisMass, "MuTauProducer_VisMass");

   TH1D * h_nTau = new TH1D("h_nTau", ";# of #tau_{h};events / 1", 5, -0.5, 4.5);
   runPoint(h_nTau, "MuTauProducer_nGoodTau");

   TH1D * h_nMuon = new TH1D("h_nMuon", ";# of #mu;events / 1", 5, -0.5, 4.5);
   runPoint(h_nMuon, "MuTauProducer_nGoodMuon");

   TH1D * h_HavePair = new TH1D("h_HavePair", ";# of #mu+#tau_{h} pairs;events / 1", 5, -0.5, 4.5);
   runPoint(h_HavePair, "MuTauProducer_HavePair");

   TH1D * h_DeltaPhi = new TH1D("h_DeltaPhi", ";#Delta#phi(#mu, #tau_{h});events / .4", 8, 0., 3.2);
   runPoint(h_DeltaPhi, "MuTauProducer_DeltaPhi");

   TH1D * h_qq = new TH1D("h_qq", ";q_{#mu} * q_{#tau_{h}};events / 1", 3, -1.5, 1.5);
   runPoint(h_qq, "MuTauProducer_qq");

   TH1D * h_MET = new TH1D("h_MET", ";MET [GeV];events / 25 GeV", 10, 0., 250.);
   runPoint(h_MET, "MET_pt");
}

