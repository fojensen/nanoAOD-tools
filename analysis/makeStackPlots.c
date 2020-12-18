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

   TCut baseline = "MuTauProducer_HavePair>0 && Muon_pfIsoId[MuTauProducer_MuIdx]>=4 && (HLT_IsoMu24||HLT_IsoMu27)";
   baseline = baseline && TCut("1&Tau_idDeepTau2017v2p1VSjet[MuTauProducer_TauIdx]");
   //baseline = baseline && TCut("ZProducer_EEHavePair==0 && ZProducer_MuMuHavePair==0 && ZProducer_TauTauHavePair==0");
   //baseline = baseline && TCut("Sum$(Electron_pt>=10. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
   //baseline = baseline && TCut("JetProducer_nBJetM==0");
   //baseline = baseline && TCut("MuTauProducer_mT>=50.");
   //baseline = baseline && TCut("MuTauProducer_Mass>=91.1876");

   TFile * f_data = TFile::Open("root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/SingleMuon_2018D.root");
   TTree * t_data = (TTree*)f_data->Get("Events"); 
   
   TH1D * h_data = (TH1D*)h->Clone("h_data_"+TString(h->GetName()));
   t_data->Project(h_data->GetName(), var, baseline);

   const int nmc = 5;
   const double lumi = 31742.979; //https://twiki.cern.ch/CMS/RA2b13TeVProduction
   TString samples[nmc] = {"TTJets", "DYJetsToEEMuMu_M50", "DYJetsToTauTau_M50", "QCD", "WJetsToLNu"};
   double xsweight[nmc];
   xsweight[0] = lumi * 831.76 / 10244307.;
   xsweight[1] = lumi * 6025.2 / 100194597.;
   xsweight[2] = lumi * 6025.2 / 100194597.;
   xsweight[3] = lumi * 239400.0 / 22165320.;
   xsweight[4] = lumi * 61334.9 / 70454125.;

   THStack * s = new THStack("s", "");
   s->SetTitle(h->GetTitle());
   TH1D * h_mc[nmc];
   double sum = 0.;
   for (int i = 0; i < nmc; ++i) {
      char infile[1000];
      sprintf(infile, "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/%s.root", samples[i].Data());
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

   std::cout << "expected data composition: " << std::endl;
   for (int i = 0; i < nmc; ++i) {
      const double h_integral = h_mc[i]->Integral();
      std::cout << "   " << samples[i] << " " << h_integral << " " << h_integral/sum << std::endl;
   }
   
   TCanvas * c = new TCanvas("c_"+TString(h->GetName()), var, 400, 400);
   h_data->SetMarkerStyle(20);
   h_data->Draw("PE, SAME");
   h_data->SetStats(0);
   h_data->SetMinimum(10.);
   h_data->SetMaximum(1.e8);
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
   TH1D * h_mT = new TH1D("h_mT", ";m_{T} [GeV];events / 20 GeV", 10, 0., 200.);
   runPoint(h_mT, "MuTauProducer_mT");

   TH1D * h_nBJetM = new TH1D("h_nBJetM", ";# of b-tagged jets (medium);events / 1", 5, -0.5, 4.5);
   runPoint(h_nBJetM, "JetProducer_nBJetM");

   TH1D * h_nBJetT = new TH1D("h_nBJetT", ";# of b-tagged jets (tight);events / 1", 5, -0.5, 4.5);
   runPoint(h_nBJetT, "JetProducer_nBJetT");

   TH1D * h_VisMass = new TH1D("h_VisMass", ";#mu+#tau_{h} visible mass [GeV];events / 25 GeV", 10, 0., 250.);
   runPoint(h_VisMass, "MuTauProducer_Mass");

   TH1D * h_nEle = new TH1D("h_nEle", ";# of electrons;events / 1", 4, -0.5, 3.5);
   runPoint(h_nEle, "Sum$(Electron_pt>=10. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)");

   TH1D * h_nEE = new TH1D("h_nEE", ";# of e^{+}e^{-} pairs;events / 1", 3, -0.5, 2.5);
   runPoint(h_nEE, "ZProducer_EEHavePair");

   TH1D * h_nMuMu = new TH1D("h_nMuMu", ";# of #mu^{+}#mu^{-} pairs;events / 1", 3, -0.5, 2.5);
   runPoint(h_nMuMu, "ZProducer_MuMuHavePair");

   TH1D * h_nTauTau = new TH1D("h_nTauTau", ";# of #tau_{h}^{+}#tau_{h}^{-} pairs;events / 1", 3, -0.5, 2.5);
   runPoint(h_nTauTau, "ZProducer_TauTauHavePair");
}

