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

   //loose cuts for W
   TCut baseline = "MuMuProducer_HavePair==0 && MuTauProducer_HavePair==1";

   //loose cuts for Z->mu+tau
   //baseline = baseline && TCut("MuTauProducer_qq==-1 && 128&Tau_idDeepTau2017v2p1VSjet[MuTauProducer_TauIdx]");
   //tight cuts for Z->mu+tau
   //baseline = baseline && TCut("MuTauProducer_mT<40. && MuTauProducer_nBJetT==0 && MuTauProducer_MuTauVisMass<91.1876");
   //baseline = baseline && TCut("MuTauProducer_nBJetT==0");
   //tight cuts for W
   //baseline = baseline && TCut("MuTauProducer_mT>=40. && MuTauProducer_nBJetM==0 && MuTauProducer_MuTauVisMass>=91.1876");

   TFile * f_data = TFile::Open("root://cmseos.fnal.gov//store/user/hats/2020/Tau/SingleMuon_2018D.root");
   //TFile * f_data = TFile::Open("./outputData/SingleMuon_2018D.root");
   TTree * t_data = (TTree*)f_data->Get("Events"); 
   TH1D * h_data = (TH1D*)h->Clone("h_data_"+TString(h->GetName()));
   t_data->Project(h_data->GetName(), var, baseline);

   const int nmc = 4;
   const double lumi = 31742.979; //https://twiki.cern.ch/CMS/RA2b13TeVProduction
   TString samples[nmc] = {"TTJets", "DYJetsToEEMuMu_M-50", "DYJetsToTauTau_M-50", "WJetsToLNu"};
   double xsweight[nmc];
   xsweight[0] = lumi * 831.76 / 10244307.;
   xsweight[1] = lumi * 6025.2 / 100194597.;
   xsweight[2] = lumi * 6025.2 / 100194597.;
   xsweight[3] = lumi * 61334.9 / 70454125.;

   THStack * s = new THStack("s", "");
   s->SetTitle(h->GetTitle());
   TH1D * h_mc[nmc];
   double sum = 0.;
   for (int i = 0; i < nmc; ++i) {
      char infile[1000];
      sprintf(infile, "root://cmseos.fnal.gov//store/user/hats/2020/Tau/%s.root", samples[i].Data());
      TFile * f = TFile::Open(infile);
      TTree * t = (TTree*)f->Get("Events");
      const TString hname = "h_mc_"+TString(h->GetName())+"_"+TString::Itoa(i, 10);
      h_mc[i] = (TH1D*)h->Clone(hname);
      h_mc[i]->SetFillColor(2+i);
      char buffer[1000];
      sprintf(buffer, "%f * (%s)", xsweight[i], TString(baseline).Data());
      t->Project(h_mc[i]->GetName(), var, buffer);
      sum += h_mc[i]->Integral();
      s->Add(h_mc[i]);
   }

   std::cout << "expected background composition: " << std::endl;
   for (int i = 0; i < nmc; ++i) {
      const double h_integral = h_mc[i]->Integral();
      std::cout << samples[i] << " " << h_integral << " " << h_integral/sum << std::endl;
   }
   
   TCanvas * c = new TCanvas("c_"+TString(h->GetName()), var, 400, 400);
   h_data->SetMarkerStyle(20);
   h_data->Draw("PE, SAME");
   h_data->SetStats(0);
   h_data->SetMinimum(0.1);
   h_data->SetMaximum(10000000.);
   c->SetLogy();
   s->Draw("HIST, SAME");
   h_data->Draw("PE, SAME");
   
   TLegend * l = new TLegend(0.3, 0.75, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   l->AddEntry(h_data, "data", "P");
   for (int i = 0; i < nmc; ++i) l->AddEntry(h_mc[i], samples[i], "F");
   l->Draw();

   c->SaveAs("./plots/"+TString(h->GetName())+".pdf");
}

void makeStackPlots()
{
   TH1D * h_mT = new TH1D("h_mT", ";m_{T} [GeV];events / 25 GeV", 10, 0., 250.);
   runPoint(h_mT, "MuTauProducer_mT");

   TH1D * h_nBJetT = new TH1D("h_nBJetT", ";# of b-tagged jets (tight);events / 1", 5, -0.5, 4.5);
   runPoint(h_nBJetT, "MuTauProducer_nBJetT");
   
   TH1D * h_VisMass = new TH1D("h_VisMass", ";#mu+#tau_{h} visible mass [GeV];events / 25 GeV", 10, 0., 250.);
   runPoint(h_VisMass, "MuTauProducer_MuTauVisMass");

   TH1D * h_tauMass = new TH1D("h_tauMass", ";#tau_{h} mass [GeV];events / 0.1 GeV", 20, 0., 2.);
   runPoint(h_tauMass, "Tau_mass[MuTauProducer_TauIdx]");

   TH1D * h_decayMode = new TH1D("h_decayMode", ";decayMode;events / 1", 12, -0.5, 11.5);
   runPoint(h_decayMode, "Tau_decayMode[MuTauProducer_TauIdx]");
}

