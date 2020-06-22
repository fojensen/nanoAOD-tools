#include <TLegend.h>
#include <TCanvas.h>
#include <iostream>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TGraphAsymmErrors.h>

TFile * runMCSum()
{
   std::cout << "running on summed mc..." << std::endl;
   const TString samples[3] = {"WJetsToLNu", "DYJetsToLL_M-50", "TTJets"};
   const double lumi = 31742.979;
   double xsweight[3];
   xsweight[0] = lumi * 61334.9 / 70454125.;
   xsweight[1] = lumi * 6025.2 / 100194597.;
   xsweight[2] = lumi * 831.76 / 10244307.

   TH1D *h_pt_sum = new TH1D("h_pt_sum", ";#tau_{h} p_{T} [GeV];events / 10 GeV", 10, 20., 120.);
   TH1D *h_eta_sum = new TH1D("h_eta_sum", ";#tau_{h} |#eta|;events / 0.23", 10, 0., 2.3);
   TH1D *h_pt_sum_num[8], *h_eta_sum_num[8];
   for (int i = 0; i < 8; ++i) {
      h_pt_sum_num[i] = (TH1D*)h_pt_sum->Clone("h_pt_sum_num_"+TString::Itoa(i, 10));
      h_eta_sum_num[i] = (TH1D*)h_eta_sum->Clone("h_eta_sum_num_"+TString::Itoa(i, 10));
   }

   for (int i = 0; i < 3; ++i) {
      std::cout << samples[i] << std::endl;
      TFile *f = TFile::Open("./hists."+samples[i]+".root");

      TH1D * htemp_pt = (TH1D*)f->Get("h_pt");
      std::cout << xsweight[i]*htemp_pt->Integral() << std::endl;
      h_pt_sum->Add(htemp_pt, xsweight[i]);

      TH1D * htemp_eta = (TH1D*)f->Get("h_eta");
      std::cout << xsweight[i]*htemp_eta->Integral() << std::endl;
      h_eta_sum->Add(htemp_eta, xsweight[i]);

      for (int j = 0; j < 8; ++j) {

         TH1D * htemp_pt_num = (TH1D*)f->Get("h_pt_num_"+TString::Itoa(j, 10));
         //std::cout << htemp_pt_num->Integral() << std::endl;
         h_pt_sum_num[j]->Add(htemp_pt_num, xsweight[i]);

         TH1D * htemp_eta_num = (TH1D*)f->Get("h_eta_num_"+TString::Itoa(j, 10));
         //std::cout << htemp_eta_num->Integral() << std::endl;
         h_eta_sum_num[j]->Add(htemp_eta_num, xsweight[i]);
      }
   }

   TGraphAsymmErrors *g_pt[8], *g_eta[8];
   for (int i = 0; i < 8; ++i) {
 //     std::cout << "dividing histograms" << std::endl;
      g_pt[i] = new TGraphAsymmErrors();
      g_pt[i]->SetName("g_pt_"+TString::Itoa(i, 10));
      //std::cout << h_pt_sum_num[i]->Integral() << " " << h_pt_sum->Integral() << std::endl;
      g_pt[i]->Divide(h_pt_sum_num[i], h_pt_sum);
      g_pt[i]->SetMarkerStyle(20);
      g_pt[i]->SetLineColor(2+i);
      g_pt[i]->SetMarkerColor(2+i);
      g_eta[i] = new TGraphAsymmErrors();
      g_eta[i]->SetName("g_eta_"+TString::Itoa(i, 10));
      //std::cout << h_eta_sum_num[i]->Integral() << " " << h_eta_sum->Integral() << std::endl;
      g_eta[i]->Divide(h_eta_sum_num[i], h_eta_sum);
      g_eta[i]->SetMarkerStyle(20);
      g_eta[i]->SetLineColor(2+i);
      g_eta[i]->SetMarkerColor(2+i);
   }

   TFile * f = new TFile("./outputData/mcsum.hists.root", "RECREATE");
   h_pt_sum->Write("h_pt");
   h_eta_sum->Write("h_eta");
   for (int i = 0; i < 8; ++i) {
      h_pt_sum_num[i]->Write("h_pt_num_"+TString::Itoa(i, 10));
      h_eta_sum_num[i]->Write("h_eta_num_"+TString::Itoa(i, 10));
      g_pt[i]->Write();
      g_eta[i]->Write();
   }
   f->Close();
   return f;
}

TFile * runPoint(const TString tag)
{
   std::cout << "running on " << tag << "..." << std::endl;
   TFile *f = TFile::Open("outputData/"+tag+".root");
   TTree *t = (TTree*)f->Get("Events");

   TCut baseline = "MuMuProducer_HavePair==0 && MuTauProducer_HavePair>0 && MuTauProducer_mT>=40. && MuTauProducer_nBJetT==0 && MuTauProducer_VisMass>=91.1876";
   baseline = baseline && TCut("Tau_pt[MuTauProducer_TauIdx]<120.");

   TH1D *h_pt = new TH1D("h_pt", ";#tau_{h} p_{T} [GeV];events / 10 GeV", 10, 20., 120.);
   TH1D *h_eta = new TH1D("h_eta", ";#tau_{h} |#eta|;events / 0.23", 10, 0., 2.3); 
   TH1D *h_pt_num[8], *h_eta_num[8];
   for (int i = 0; i < 8; ++i) {
      h_pt_num[i] = (TH1D*)h_pt->Clone("h_pt_num_"+TString::Itoa(i, 10));
      h_eta_num[i] = (TH1D*)h_eta->Clone("h_eta_num_"+TString::Itoa(i, 10));
   }

   std::cout << "projecting denominator..." << std::endl;
   std::cout << t->Project(h_pt->GetName(), "Tau_pt[MuTauProducer_TauIdx]", baseline) << std::endl;
   std::cout << t->Project(h_eta->GetName(), "TMath::Abs(Tau_eta[MuTauProducer_TauIdx])", baseline) << std::endl;

   for (int i = 0; i < 8; ++i) {
      std::cout << "projecting numerator " << i << "..." << std::endl;
      char buffer[100];
      const int mask = 1<<i;
      sprintf(buffer, "%i&Tau_idDeepTau2017v2p1VSjet[MuTauProducer_TauIdx]", mask);
      const TCut cutTag = TCut(buffer);
      std::cout << t->Project(h_pt_num[i]->GetName(), "Tau_pt[MuTauProducer_TauIdx]", baseline && cutTag) << std::endl;
      const int n = t->Project(h_eta_num[i]->GetName(), "TMath::Abs(Tau_eta[MuTauProducer_TauIdx])", baseline && cutTag);
      std::cout << n << std::endl;
      if (n==0) break;
   }

   TGraphAsymmErrors *g_pt[8], *g_eta[8];
   for (int i = 0; i < 8; ++i) {    
      g_pt[i] = new TGraphAsymmErrors();
      g_pt[i]->SetName("g_pt_"+TString::Itoa(i, 10));
      g_pt[i]->Divide(h_pt_num[i], h_pt);
      g_pt[i]->SetLineColor(i+2);
      g_pt[i]->SetMarkerColor(i+2);
      g_pt[i]->SetMarkerStyle(7);
      char buffer_pt[100];
      sprintf(buffer_pt, ";%s;tagging efficiency", h_pt->GetXaxis()->GetTitle());
      g_pt[i]->SetTitle(buffer_pt);
      g_eta[i] = new TGraphAsymmErrors();
      g_eta[i]->SetName("g_eta_"+TString::Itoa(i, 10));
      g_eta[i]->Divide(h_eta_num[i], h_eta);
      g_eta[i]->SetLineColor(i+2);
      g_eta[i]->SetMarkerColor(i+2);
      g_eta[i]->SetMarkerStyle(7);
      char buffer_eta[100];
      sprintf(buffer_eta, ";%s;tagging efficiency", h_eta->GetXaxis()->GetTitle());
      g_eta[i]->SetTitle(buffer_eta);
   }
 
   TFile * fout = new TFile("./outputData/"+tag+".hists.root", "RECREATE");
   h_pt->Write();
   h_eta->Write();
   for (int i = 0; i < 8; ++i) {
      h_pt_num[i]->Write();
      h_eta_num[i]->Write();
      g_pt[i]->Write();
      g_eta[i]->Write();
   }
   fout->Close();
   return fout;
}

void makePlot()
{
   TGraphAsymmErrors *g_pt_data[8], *g_eta_data[8];
   TFile * f_data = TFile::Open("./outputData/SingleMuon_2018D.hists.root");
   for (int i = 0; i < 8; ++i) {
      g_pt_data[i] = (TGraphAsymmErrors*)f_data->Get("g_pt_"+TString::Itoa(i, 10));
      g_pt_data[i]->SetMarkerStyle(47);
      g_pt_data[i]->SetMarkerColor(2+i);
      g_pt_data[i]->SetLineColor(2+i);
      g_eta_data[i] = (TGraphAsymmErrors*)f_data->Get("g_eta_"+TString::Itoa(i, 10));
      g_eta_data[i]->SetMarkerStyle(47);
      g_eta_data[i]->SetMarkerColor(2+i);
      g_eta_data[i]->SetLineColor(2+i);
   }
   
   TGraphAsymmErrors *g_pt_mc[8], *g_eta_mc[8];
   TFile * f_mc = TFile::Open("./outputData/mcsum.hists.root");
   for (int i = 0; i < 8; ++i) {
      g_pt_mc[i] = (TGraphAsymmErrors*)f_mc->Get("g_pt_"+TString::Itoa(i, 10));
      g_pt_mc[i]->SetMarkerStyle(20);
      g_pt_mc[i]->SetMarkerColor(2+i);
      g_pt_mc[i]->SetLineColor(2+i); 
      g_eta_mc[i] = (TGraphAsymmErrors*)f_mc->Get("g_eta_"+TString::Itoa(i, 10));
      g_eta_mc[i]->SetMarkerStyle(20);
      g_eta_mc[i]->SetMarkerColor(2+i);
      g_eta_mc[i]->SetLineColor(2+i);
   }

   TCanvas * c = new TCanvas("c", "", 1600, 800);
   c->Divide(4, 2);
   for (int i = 0; i < 8; ++i) {
      TPad * p = (TPad*)c->cd(i+1);
      g_pt_data[i]->Draw("APE");
      g_pt_data[i]->SetMaximum(1.);
      g_pt_data[i]->SetMinimum(0.001);
      g_pt_mc[i]->Draw("PE, SAME");
      g_pt_data[i]->Draw("PE, SAME");
      p->SetLogy();
      TLegend * l = new TLegend(0.5, 0.2, 0.875, 0.3);
      l->SetNColumns(2);
      l->SetBorderSize(0);
      l->AddEntry(g_pt_data[i], "data", "P");
      l->AddEntry(g_pt_mc[i], "mc", "P");
      l->Draw();
   }

   TGraphAsymmErrors *r_pt[8];//, *r_eta[8];
   for (int i = 0; i < 8; ++i) {
      r_pt[i] = (TGraphAsymmErrors*)g_pt_data[i]->Clone("r_pt_"+TString::Itoa(i, 10));
      for (int j = 0; j < g_pt_data[i]->GetN(); ++j) {
         double x_data, y_data;
         g_pt_data[i]->GetPoint(j, x_data, y_data);
         double x_mc, y_mc;
         g_pt_mc[i]->GetPoint(j, x_mc, y_mc);
         const double r = y_data/y_mc;
         r_pt[i]->SetPoint(j, x_data, r);
      }
   }

   TCanvas * c2 = new TCanvas("c2", "", 1600, 800); 
   c2->Divide(4, 2);
   for (int i = 0; i < 8; ++i) {
      c2->cd(i+1);
      r_pt[i]->Draw("APE");
      r_pt[i]->SetMinimum(0.75);
      r_pt[i]->SetMaximum(1.25);
   }
}

void jetFake()
{
   const TString samples[3] = {"WJetsToLNu", "DYJetsToLL_M-50", "TTJets"};
   TFile * f_mc[3];
   for (int i = 0; i < 3; ++i) f_mc[i] = runPoint(samples[i]);
   runMCSum();
   TFile * f_data = runPoint("SingleMuon_2018D");
   makePlot();
}

