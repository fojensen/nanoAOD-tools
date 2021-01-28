#include <THStack.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <iostream>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TGraphAsymmErrors.h>

TFile * runPoint(const TString tag, TH1D * h, const TString var, const double xsweight=1.)
{
   std::cout << "runPoint(): " << tag << std::endl;
   char infile[1000];
   sprintf(infile, "root://cmseos.fnal.gov//store/user/cmsdas/2021/short_exercises/Tau/%s.root", tag.Data());
   TFile *f = TFile::Open(infile);
   TTree *t = (TTree*)f->Get("Events");

   TCut baseline = "MuTauProducer_HavePair>0";
   baseline = baseline && TCut("Muon_pfIsoId[MuTauProducer_MuIdx]>=2 && (HLT_IsoMu24||HLT_IsoMu27) && Muon_pt[MuTauProducer_MuIdx]>=27.");
   baseline = baseline && TCut("1&Tau_idDeepTau2017v2p1VSjet[MuTauProducer_TauIdx]"); //dont even bother if it doesnt pass the loosest wp

   char buffer_denom[1000];
   sprintf(buffer_denom, "%f * (%s)", xsweight, TString(baseline).Data());

   TH1D *h_denom = (TH1D*)h->Clone("h_denom");
   TH1D *h_num[8];
   for (int i = 0; i < 8; ++i) h_num[i] = (TH1D*)h->Clone("h_num_"+TString::Itoa(i, 10));

   t->Project(h_denom->GetName(), var, buffer_denom);
   for (int i = 0; i < 8; ++i) {
      char buffer[100];
      const int mask = 1<<i;
      sprintf(buffer, "%i&Tau_idDeepTau2017v2p1VSjet[MuTauProducer_TauIdx]", mask);
      const TCut cutTag = TCut(buffer);
      char buffer_num[1000];
      sprintf(buffer_num, "%f * (%s)", xsweight, TString(baseline&&cutTag).Data());
      const int n = t->Project(h_num[i]->GetName(), var, buffer_num);
      if (n==0) break;
   }

   TGraphAsymmErrors *g[8];
   for (int i = 0; i < 8; ++i) {    
      g[i] = new TGraphAsymmErrors();
      g[i]->SetName("g_"+TString::Itoa(i, 10));
      g[i]->Divide(h_num[i], h_denom, "N");
      g[i]->SetLineColor(i+2);
      g[i]->SetMarkerColor(i+2);
      g[i]->SetMarkerStyle(7);
      char buffer[100];
      sprintf(buffer, ";%s;tagging efficiency", h_denom->GetXaxis()->GetTitle());
      g[i]->SetTitle(buffer);
   }

   TFile * fout = new TFile("./outputHists/"+tag+".root", "RECREATE");
   h_denom->Write();
   for (int i = 0; i < 8; ++i) {
      h_num[i]->Write();
      g[i]->Write();
   }
   fout->Close();
   return fout;
}

void makePlots()
{
   std::cout << "makePlots()" << std::endl;
   TGraphAsymmErrors *g_data[8];
   TFile * f_data = TFile::Open("./outputHists/bkgSubtractedData.root");
   for (int i = 0; i < 8; ++i) {
      g_data[i] = (TGraphAsymmErrors*)f_data->Get("g_"+TString::Itoa(i, 10));
      g_data[i]->SetMarkerStyle(47);
      g_data[i]->SetMarkerColor(7);
      g_data[i]->SetLineColor(7);
   }
   
   TGraphAsymmErrors *g_mc[8];
   TFile * f_mc = TFile::Open("./outputHists/WJetsToLNu.root");
   for (int i = 0; i < 8; ++i) {
      g_mc[i] = (TGraphAsymmErrors*)f_mc->Get("g_"+TString::Itoa(i, 10));
      g_mc[i]->SetMarkerStyle(20);
      g_mc[i]->SetMarkerColor(8);
      g_mc[i]->SetLineColor(8); 
   }

   const TString taglabels[8] = {"VVVLoose", "VVLoose" ,"VLoose" ,"Loose", "Medium", "Tight", "VTight", "VVTight"};

   TCanvas * c1 = new TCanvas("c1", "", 1600, 800);
   c1->Divide(4, 2);
   for (int i = 0; i < 8; ++i) {
      TPad * p = (TPad*)c1->cd(i+1);
      g_data[i]->Draw("APE");
      g_data[i]->SetMaximum(1.1);
      g_data[i]->SetMinimum(0.001);
      g_data[i]->SetTitle(taglabels[i]);
      g_mc[i]->Draw("PE, SAME");
      g_data[i]->Draw("PE, SAME");
      p->SetLogy();
      TLegend * l = new TLegend(0.5, 0.2, 0.875, 0.3);
      l->SetNColumns(2);
      l->SetBorderSize(0);
      l->AddEntry(g_data[i], "data", "P");
      l->AddEntry(g_mc[i], "mc", "P");
      l->Draw();
   }
   c1->SaveAs("./plots/fakerate.pdf");

   // scale factors
   TGraphAsymmErrors *r[8];
   for (int i = 0; i < 8; ++i) {
      r[i] = (TGraphAsymmErrors*)g_data[i]->Clone("r_"+TString::Itoa(i, 10));
      for (int j = 0; j < g_data[i]->GetN(); ++j) {
         double x_data, y_data;
         g_data[i]->GetPoint(j, x_data, y_data);
         const double y_data_err = g_data[i]->GetErrorY(j);

         double x_mc, y_mc;
         g_mc[i]->GetPoint(j, x_mc, y_mc);
         const double y_mc_err = g_mc[i]->GetErrorY(j);

         const double r_val = y_data/y_mc;
         const double r_err = r_val * sqrt((y_data_err/y_data)*(y_data_err/y_data)+(y_mc_err/y_mc)*(y_mc_err/y_mc));
         r[i]->SetPoint(j, x_data, r_val);
         r[i]->SetPointEYhigh(j, r_err);
         r[i]->SetPointEYlow(j, r_err);
         char title[100];
         sprintf(title, ";%s;data / mc", g_data[i]->GetXaxis()->GetTitle());
         r[i]->SetTitle(title);
      }
   }

   TCanvas * c2 = new TCanvas("c2", "", 1600, 800); 
   c2->Divide(4, 2);
   for (int i = 0; i < 8; ++i) {
      c2->cd(i+1);
      r[i]->SetMarkerColor(1);
      r[i]->SetLineColor(1);
      r[i]->Draw("APE");
      r[i]->SetMinimum(0.75);
      r[i]->SetMaximum(1.25);
      r[i]->SetTitle(taglabels[i]);
   }
   c2->SaveAs("./plots/scalefactors.pdf"); 
}

TFile * bkgSubtractedData()
{
   std::cout << "bkgSubtractedData()" << std::endl;
   TFile * f_data = TFile::Open("./outputHists/SingleMuon_2018D.root");
   TH1D *h = (TH1D*)f_data->Get("h_denom");
   TH1D *h_num[8];
   for (int i = 0; i < 8; ++i) {
      h_num[i] = (TH1D*)f_data->Get("h_num_"+TString::Itoa(i, 10));
   }

   const int nbkg = 4;
   const TString samples[nbkg] = {"TTJets", "DYJetsToEEMuMu_M50", "DYJetsToTauTau_M50", "QCD"};
   for (int i = 0; i < nbkg; ++i) {
      std::cout << "i " << i << std::endl;
      TFile *f = TFile::Open("./outputHists/"+samples[i]+".root");
      TH1D * htemp = (TH1D*)f->Get("h_denom");
      h->Add(htemp, -1.);
      for (int j = 0; j < 8; ++j) {
         std::cout << "j " << j << std::endl;
         TH1D * htemp_num = (TH1D*)f->Get("h_num_"+TString::Itoa(j, 10));
         h_num[j]->Add(htemp_num, -1.);
      }
   }

   TFile * f = new TFile("./outputHists/bkgSubtractedData.root", "RECREATE");
   h->Write();
   for (int i = 0; i < 8; ++i) {
      h_num[i]->Write("h_"+TString::Itoa(i, 10));
   }

   TGraphAsymmErrors *g[8];
   for (int i = 0; i < 8; ++i) {    
      g[i] = new TGraphAsymmErrors();
      g[i]->SetName("g_"+TString::Itoa(i, 10));
      g[i]->Divide(h_num[i], h, "N");
      g[i]->SetLineColor(i+2);
      g[i]->SetMarkerColor(i+2);
      g[i]->SetMarkerStyle(7);
      char buffer[100];
      sprintf(buffer, ";%s;tagging efficiency", h->GetXaxis()->GetTitle());
      g[i]->SetTitle(buffer);
      g[i]->Write();
   }

   f->Close();
   return f;
}

void jetFake()
{
   std::cout << "jetFake()" << std::endl;
   TH1D * h = new TH1D("h", ";#tau_{h} p_{T} [GeV];events / 20 GeV", 5, 20., 120.);
   const TString var = "Tau_pt[MuTauProducer_TauIdx]";

   runPoint("SingleMuon_2018D", h, var);

   const int nmc = 5;
   const double lumi = 31742.979; //https://twiki.cern.ch/CMS/RA2b13TeVProduction
   TString samples[nmc] = {"TTJets", "DYJetsToEEMuMu_M50", "DYJetsToTauTau_M50", "QCD", "WJetsToLNu"};
   double xsweight[nmc];
   xsweight[0] = lumi * 831.76 / 10244307.;
   xsweight[1] = lumi * 6025.2 / 100194597.;
   xsweight[2] = lumi * 6025.2 / 100194597.;
   xsweight[3] = lumi * 239400.0 / 22165320.;
   xsweight[4] = lumi * 61334.9 / 70454125.;
   for (int i = 0; i < nmc; ++i) runPoint(samples[i], h, var, xsweight[i]);

   TFile * f_cleanData = bkgSubtractedData();
   makePlots();
}

