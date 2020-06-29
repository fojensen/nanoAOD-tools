#include <THStack.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <iostream>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TGraphAsymmErrors.h>

TFile * runPoint(const TString tag, const double xsweight=1.)
{
   std::cout << "running on " << tag << "..." << std::endl;
   TFile *f = TFile::Open("./outputData/"+tag+".root");
   TTree *t = (TTree*)f->Get("Events");

   TCut baseline = "MuMuProducer_HavePair==0 && MuTauProducer_HavePair==1";
   baseline = baseline && TCut("MuTauProducer_mT>=40.");
   baseline = baseline && TCut("MuTauProducer_nBJetT==0");
   //baseline = baseline && TCut("MuTauProducer_MuTauVisMass>=91.1876");
   baseline = baseline && TCut("Tau_pt[MuTauProducer_TauIdx]<120.");

   char buffer_denom[1000];
   sprintf(buffer_denom, "%f * (%s)", xsweight, TString(baseline).Data());

   TH1D *h_pt = new TH1D("h_pt", ";#tau_{h} p_{T} [GeV];events / 10 GeV", 10, 20., 120.);
   TH1D *h_pt_num[8], *h_eta_num[8];
   for (int i = 0; i < 8; ++i) {
      h_pt_num[i] = (TH1D*)h_pt->Clone("h_pt_num_"+TString::Itoa(i, 10));
   }

   std::cout << "projecting denominator..." << std::endl;
   std::cout << t->Project(h_pt->GetName(), "Tau_pt[MuTauProducer_TauIdx]", buffer_denom) << std::endl;

   for (int i = 0; i < 8; ++i) {
      std::cout << "projecting numerator " << i << "..." << std::endl;
      char buffer[100];
      const int mask = 1<<i;
      sprintf(buffer, "%i&Tau_idDeepTau2017v2p1VSjet[MuTauProducer_TauIdx]", mask);
      const TCut cutTag = TCut(buffer);
      char buffer_num[1000];
      sprintf(buffer_num, "%f * (%s)", xsweight, TString(baseline&&cutTag).Data());
      const int n = t->Project(h_pt_num[i]->GetName(), "Tau_pt[MuTauProducer_TauIdx]", buffer_num);
      std::cout << n << std::endl;
      if (n==0) break;
   }

   TGraphAsymmErrors *g_pt[8];
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
   }

   TFile * fout = new TFile("./outputHists/"+tag+".root", "RECREATE");
   h_pt->Write();
   for (int i = 0; i < 8; ++i) {
      h_pt_num[i]->Write();
      g_pt[i]->Write();
   }
   fout->Close();
   return fout;
}

void makePlots()
{
   TGraphAsymmErrors *g_pt_data[8];
   TFile * f_data = TFile::Open("./outputHists/bkgSubtractedData.root");
   for (int i = 0; i < 8; ++i) {
      g_pt_data[i] = (TGraphAsymmErrors*)f_data->Get("g_pt_"+TString::Itoa(i, 10));
      g_pt_data[i]->SetMarkerStyle(47);
      g_pt_data[i]->SetMarkerColor(7);
      g_pt_data[i]->SetLineColor(7);
   }
   
   TGraphAsymmErrors *g_pt_mc[8];
   TFile * f_mc = TFile::Open("./outputHists/WJetsToLNu.root");
   for (int i = 0; i < 8; ++i) {
      g_pt_mc[i] = (TGraphAsymmErrors*)f_mc->Get("g_pt_"+TString::Itoa(i, 10));
      g_pt_mc[i]->SetMarkerStyle(20);
      g_pt_mc[i]->SetMarkerColor(8);
      g_pt_mc[i]->SetLineColor(8); 
   }

   const TString taglabels[8] = {"VVVLoose", "VVLoose" ,"VLoose" ,"Loose", "Medium", "Tight", "VTight", "VVTight"};

   TCanvas * c1 = new TCanvas("c1", "", 1600, 800);
   c1->Divide(4, 2);
   for (int i = 0; i < 8; ++i) {
      TPad * p = (TPad*)c1->cd(i+1);
      g_pt_data[i]->Draw("APE");
      g_pt_data[i]->SetMaximum(1.1);
      g_pt_data[i]->SetMinimum(0.001);
      g_pt_data[i]->SetTitle(taglabels[i]);
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
   c1->SaveAs("./plots/fakerate.pdf");

   // scale factors
   TGraphAsymmErrors *r_pt[8];
   for (int i = 0; i < 8; ++i) {
      r_pt[i] = (TGraphAsymmErrors*)g_pt_data[i]->Clone("r_pt_"+TString::Itoa(i, 10));
      for (int j = 0; j < g_pt_data[i]->GetN(); ++j) {
         double x_data, y_data;
         g_pt_data[i]->GetPoint(j, x_data, y_data);
         const double y_data_err = g_pt_data[i]->GetErrorY(j);

         double x_mc, y_mc;
         g_pt_mc[i]->GetPoint(j, x_mc, y_mc);
         const double y_mc_err = g_pt_mc[i]->GetErrorY(j);

         const double r = y_data/y_mc;
         const double r_err = r * sqrt((y_data_err/y_data)*(y_data_err/y_data)+(y_mc_err/y_mc)*(y_mc_err/y_mc));
         r_pt[i]->SetPoint(j, x_data, r);
         r_pt[i]->SetPointEYhigh(j, r_err);
         r_pt[i]->SetPointEYlow(j, r_err);
         r_pt[i]->SetTitle(";#tau_{h} p_{T} [GeV];data / mc");
      }
   }

   TCanvas * c2 = new TCanvas("c2", "", 1600, 800); 
   c2->Divide(4, 2);
   for (int i = 0; i < 8; ++i) {
      c2->cd(i+1);
      r_pt[i]->SetMarkerColor(1);
      r_pt[i]->SetLineColor(1);
      r_pt[i]->Draw("APE");
      r_pt[i]->SetMinimum(0.75);
      r_pt[i]->SetMaximum(1.25);
      r_pt[i]->SetTitle(taglabels[i]);
   }
   c2->SaveAs("./plots/scalefactors.pdf");
   
}

TFile * bkgSubtractedData()
{
   TFile * f_data = TFile::Open("./outputHists/SingleMuon_2018D.root");
   TH1D *h_pt = (TH1D*)f_data->Get("h_pt");
   TH1D *h_pt_num[8], *h_eta_num[8];
   for (int i = 0; i < 8; ++i) {
      h_pt_num[i] = (TH1D*)f_data->Get("h_pt_num_"+TString::Itoa(i, 10));
   }

   const int nbkg = 3;
   const TString samples[nbkg] = {"DYJetsToEEMuMu_M-50", "DYJetsToTauTau_M-50", "TTJets"};
   for (int i = 0; i < nbkg; ++i) {
      TFile *f = TFile::Open("./outputHists/"+samples[i]+".root");
      TH1D * htemp_pt = (TH1D*)f->Get("h_pt");
      h_pt->Add(htemp_pt, -1.);
      for (int j = 0; j < 8; ++j) {
         TH1D * htemp_pt_num = (TH1D*)f->Get("h_pt_num_"+TString::Itoa(j, 10));
         h_pt_num[j]->Add(htemp_pt_num, -1.);
      }
   }

   TFile * f = new TFile("./outputHists/bkgSubtractedData.root", "RECREATE");
   h_pt->Write();
   for (int i = 0; i < 8; ++i) {
      h_pt_num[i]->Write("h_pt_"+TString::Itoa(i, 10));
   }

   TGraphAsymmErrors *g_pt[8];
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
      g_pt[i]->Write();
   }

   f->Close();
   return f;
}

void makeStackPlot()
{
   TFile * f_data = TFile::Open("./outputHists/SingleMuon_2018D.root");
   TH1D * h_data = (TH1D*)f_data->Get("h_pt");

   double mcsum = 0.;

   const int nmc = 4;
   const TString samples[nmc] = {"TTJets", "DYJetsToEEMuMu_M-50", "DYJetsToTauTau_M-50", "WJetsToLNu"};
   TH1D * h_mc[nmc];
   THStack * s = new THStack("s", "");
   for (int i = 0; i < nmc; ++i) {
      TFile * f = TFile::Open("./outputHists/"+samples[i]+".root");
      h_mc[i] = (TH1D*)f->Get("h_pt");
      h_mc[i]->SetFillColor(2+i);
      s->Add(h_mc[i]);
      mcsum += h_mc[i]->Integral();
   }
   TCanvas * c = new TCanvas("c_makeStackPlots", "", 400, 400);
   h_data->Draw("PE");
   s->Draw("SAME, HIST");
   h_data->Draw("PE, SAME");
   h_data->SetMarkerStyle(20);
   h_data->SetStats(0);
   c->SetLogy();
   h_data->SetMinimum(100.);
   h_data->SetMaximum(10000000.);

   TLegend * l = new TLegend(0.5, 0.6, 0.875, 0.875);
   l->SetBorderSize(0); 
   l->AddEntry(h_data, "data", "P");
   for (int i = 0; i < nmc; ++i) l->AddEntry(h_mc[i], samples[i], "F");
   l->Draw();

   for (int i = 0; i < nmc; ++i) {  
      std::cout << samples[i] << " " << h_mc[i]->Integral() / mcsum << std::endl;
   }
   c->SaveAs("./plots/fakerate_tauptdenom.pdf");
}

void jetFake()
{
   runPoint("SingleMuon_2018D");

   const int nmc = 4;
   const TString samples[nmc] = {"WJetsToLNu", "DYJetsToEEMuMu_M-50", "DYJetsToTauTau_M-50", "TTJets"};
   const double lumi = 31742.979;
   double xsweight[nmc];
   xsweight[0] = lumi * 61334.9 / 70454125.;
   xsweight[1] = lumi * 6025.2 / 100194597.;
   xsweight[2] = lumi * 6025.2 / 100194597.;
   xsweight[3] = lumi * 831.76 / 10244307.;
   for (int i = 0; i < nmc; ++i) runPoint(samples[i], xsweight[i]);

   makeStackPlot();

   TFile * f_cleanData = bkgSubtractedData();
   makePlots();
}

