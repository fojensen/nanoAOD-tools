#include <iostream>
#include <THStack.h>
#include <TCut.h>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>

TFile * makeHists(const TString tag, const double weight=0.)
{
   std::cout << tag << std::endl;
   TFile * f_in = TFile::Open("./outputData/"+tag+".root");
   TTree * t = (TTree*)f_in->Get("Events");

   TCut baseline = "MuMuProducer_HavePair==0 && MuTauProducer_HavePair==1 && 128&Tau_idDeepTau2017v2p1VSjet[MuTauProducer_TauIdx]";
   baseline = baseline && TCut("MuTauProducer_mT<40. && MuTauProducer_nBJetT==0");

   const TCut ss = "MuTauProducer_qq==1";
   const TCut os = "MuTauProducer_qq==-1";

   char bufferss[1000];
   char bufferos[1000];
   if (weight) {
      sprintf(bufferss, "%f * (%s)", weight, TString(baseline && ss).Data());
      sprintf(bufferos, "%f * (%s)", weight, TString(baseline && os).Data());
   } else {
      sprintf(bufferss, "%s", TString(baseline && ss).Data());
      sprintf(bufferos, "%s", TString(baseline && os).Data());
   }

   const TString var = "MuTauProducer_MuTauVisMass";
   TH1D * h = new TH1D("h", ";#mu+#tau_{h} visible mass [GeV];events / 25 GeV", 10, 0., 250.);
   TH1D * h_ss = new TH1D("h_ss", ";#mu+#tau_{h} visible mass [GeV];events / 25 GeV", 10, 0., 250.);

   //const TString var = "MuTauProducer_nJet";
   //TH1D * h = new TH1D("h", ";# of jets;events / 1", 10, -0.5, 9.5);
   //TH1D * h_ss = new TH1D("h_ss", ";# of jets;events / 1", 10, -0.5, 9.5);

   //const TString var = "MuTauProducer_DeltaPhi";
   //TH1D * h = new TH1D("h", ";# of jets;events / 1", 10, -0.5, 9.5);
   //TH1D * h_ss = new TH1D("h_ss", ";# of jets;events / 1", 10, -0.5, 9.5);

   const int n_os = t->Project(h->GetName(), var, bufferos);
   const int n_ss = t->Project(h_ss->GetName(), var, bufferss);
   const double i_os = h->Integral();
   const double i_ss = h_ss->Integral();

   std::cout << "   os yield: " << i_os << "; " << n_os << " events in sample." << std::endl;
   std::cout << "   ss yield: " << i_ss << "; " << n_ss << " events in sample." << std::endl;
   
   TFile * f_out = new TFile("./outputHists/"+tag+".root", "RECREATE");
   h->Write();
   h_ss->Write();
   f_out->Close();
   return f_out;
}

TFile * makeQCDHists()
{
   std::cout << "QCD" << std::endl;
   TFile * f_data = TFile::Open("./outputHists/SingleMuon_2018D.root");
   TH1D * h_data = (TH1D*)f_data->Get("h_ss");
   std::cout << "   data events in ss region: " << h_data->Integral() << std::endl;
   
   TFile * f_WJetsToLNu = TFile::Open("./outputHists/WJetsToLNu.root");
   TH1D * h_WJetsToLNu = (TH1D*)f_WJetsToLNu->Get("h_ss");

   TFile * f_TTJets = TFile::Open("./outputHists/TTJets.root");
   TH1D * h_TTJets = (TH1D*)f_TTJets->Get("h_ss");

   TFile * f_DYJetsToEEMuMu = TFile::Open("./outputHists/DYJetsToEEMuMu_M-50.root");
   TH1D * h_DYJetsToEEMuMu = (TH1D*)f_DYJetsToEEMuMu->Get("h_ss");

   TFile * f_DYJetsToTauTau = TFile::Open("./outputHists/DYJetsToTauTau_M-50.root");
   TH1D * h_DYJetsToTauTau = (TH1D*)f_DYJetsToTauTau->Get("h_ss");

   h_data->Add(h_TTJets, -1.);
   h_data->Add(h_DYJetsToEEMuMu, -1.);
   h_data->Add(h_DYJetsToTauTau, -1.);
   h_data->Add(h_WJetsToLNu, -1.);
   h_data->Scale(1.06); // TRANSFER FACTOR, DERIVED FROM CONTROL REGION
   std::cout << "   expected background in os region: " << h_data->Integral() << std::endl;

   TFile * f_qcd = new TFile("./outputHists/QCD.root", "RECREATE");
   h_data->Write("h");
   f_qcd->Close();
   return f_qcd;
}

void makeHists()
{
   makeHists("SingleMuon_2018D");

   const double lumi = 31742.979;
   double xsweight[4];
   xsweight[0] = lumi * 831.76 / 10244307.;
   xsweight[1] = lumi * 6025.2 / (100194597.*(51./58.));
   xsweight[2] = lumi * 6025.2 / (100194597.*(51./58.));
   xsweight[3] = lumi * 61334.9 / 70454125.;

   double mcsum = 0.;

   makeHists("TTJets", xsweight[0]);
   makeHists("WJetsToLNu", xsweight[3]);
   makeHists("DYJetsToEEMuMu_M-50", xsweight[1]);
   makeHists("DYJetsToTauTau_M-50", xsweight[2]);
   makeQCDHists();

   TFile *f_SingleMuon_2018D = TFile::Open("./outputHists/SingleMuon_2018D.root");
   TH1D * h_SingleMuon_2018D = (TH1D*)f_SingleMuon_2018D->Get("h");
   h_SingleMuon_2018D->SetMarkerStyle(20);
   TH1D * h_SingleMuon_2018D_ss = (TH1D*)f_SingleMuon_2018D->Get("h_ss");
   h_SingleMuon_2018D_ss->SetMarkerStyle(20);

   TFile * f_TTJets = TFile::Open("./outputHists/TTJets.root");
   TH1D * h_TTJets = (TH1D*)f_TTJets->Get("h");
   h_TTJets->SetFillColor(2);
   mcsum += h_TTJets->Integral();
   TH1D * h_TTJets_ss = (TH1D*)f_TTJets->Get("h_ss");
   h_TTJets_ss->SetFillColor(2);

   TFile * f_QCD = TFile::Open("./outputHists/QCD.root");
   TH1D * h_QCD = (TH1D*)f_QCD->Get("h");
   h_QCD->SetFillColor(6);
   mcsum += h_QCD->Integral();

   TFile * f_WJetsToLNu = TFile::Open("./outputHists/WJetsToLNu.root");
   TH1D * h_WJetsToLNu = (TH1D*)f_WJetsToLNu->Get("h");
   h_WJetsToLNu->SetFillColor(5);
   TH1D * h_WJetsToLNu_ss = (TH1D*)f_WJetsToLNu->Get("h_ss");
   h_WJetsToLNu_ss->SetFillColor(5);
   mcsum += h_WJetsToLNu->Integral();

   TFile * f_DYJetsToEEMuMu = TFile::Open("./outputHists/DYJetsToEEMuMu_M-50.root");
   TH1D * h_DYJetsToEEMuMu = (TH1D*)f_DYJetsToEEMuMu->Get("h");
   h_DYJetsToEEMuMu->SetFillColor(3);
   TH1D * h_DYJetsToEEMuMu_ss = (TH1D*)f_DYJetsToEEMuMu->Get("h_ss");
   h_DYJetsToEEMuMu_ss->SetFillColor(3);
   mcsum += h_DYJetsToEEMuMu->Integral();
  
   TFile * f_DYJetsToTauTau = TFile::Open("./outputHists/DYJetsToTauTau_M-50.root");
   TH1D * h_DYJetsToTauTau = (TH1D*)f_DYJetsToTauTau->Get("h");
   h_DYJetsToTauTau->SetFillColor(4);
   TH1D * h_DYJetsToTauTau_ss = (TH1D*)f_DYJetsToTauTau->Get("h_ss");
   h_DYJetsToTauTau_ss->SetFillColor(4);
   mcsum += h_DYJetsToTauTau->Integral();

   std::cout << "fractions of expected background: " << std::endl;
   std::cout << "   TTJets: " << h_TTJets->Integral()/mcsum << std::endl;
   std::cout << "   QCD: " << h_QCD->Integral()/mcsum << std::endl;
   std::cout << "   WJetsToLNu: " << h_WJetsToLNu->Integral()/mcsum << std::endl;
   std::cout << "   DYJetsToEEMuMu: " << h_DYJetsToEEMuMu->Integral()/mcsum << std::endl;
   std::cout << "   DYJetsToTauTau: " << h_DYJetsToTauTau->Integral()/mcsum << std::endl;
 
   TCanvas * c = new TCanvas("c", "", 400, 400);
   h_SingleMuon_2018D->Draw("P, E");
   THStack * s = new THStack("s", "");
   s->SetTitle(h_SingleMuon_2018D->GetTitle());
   s->Add(h_TTJets);
   s->Add(h_QCD);
   s->Add(h_WJetsToLNu);
   s->Add(h_DYJetsToEEMuMu);
   s->Add(h_DYJetsToTauTau);
   s->Draw("HIST, SAME");
   h_SingleMuon_2018D->Draw("PE, SAME");
   c->SetLogy();
   h_SingleMuon_2018D->SetStats(0);
   h_SingleMuon_2018D->SetMinimum(100.);
   h_SingleMuon_2018D->SetMaximum(1000000.);

   TLegend * l = new TLegend(0.5, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   l->AddEntry(h_TTJets, "t#bar{t}", "F");
   l->AddEntry(h_QCD, "QCD", "F");
   l->AddEntry(h_WJetsToLNu, "W#rightarrow#ell#nu", "F");
   l->AddEntry(h_DYJetsToEEMuMu, "Z#rightarrow ee, #mu#mu", "F");
   l->AddEntry(h_DYJetsToTauTau, "Z#rightarrow #tau#tau", "F");
   l->AddEntry(h_SingleMuon_2018D, "data", "P");
   l->Draw();
}

