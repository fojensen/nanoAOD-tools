#include <TChain.h>
#include <iostream>
#include <TH1D.h>
#include <TFile.h>
#include <TCut.h>
#include <TTree.h>
#include "addOverflow.h"
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>

class runAnalysis {
  public:
      void runAll();
      void mcHistInit();
      void sigHistInit();
      void dataHistInit();
      void loadCuts(const int year, TCut cuts[4]);
      void fillMCHists(const int year);
      void fillSigHists(const int year);
      void fillDataHists(const int year);
      void mcHistOverflow();
      void sigHistOverflow();
      void dataHistOverflow();
      void makeABCDHists();
      void sumMCHists();
      void sumBkgHists();
      void bkgFraction();
      void saveHists();

      TString channel;
      TString var;
      int mass;
      bool blindA;
      TFile *fout;
      TH1D *h;
      
      TH1D *h_truetautau[4], *h_realtau[4], *h_lfaketau[4];
      TH1D *h_jetfaketau[4];

      /*TH1D *h_WW[4], *h_WZ[4], *h_ZZ[4];
      TH1D *h_TTTo2L2Nu[4], *h_TTToSemiLeptonic[4];
      TH1D *h_ST_tW_top[4], *h_ST_tW_antitop[4];
      TH1D *h_ST_t_channel_top[4], *h_ST_t_channel_antitop[4];
      TH1D *h_DYJetsToLLM10[4];
      TH1D *h_DYJetsToEEMuMu[4], *h_DYJetsToTauTau[4];*/

      TH1D *h_Taustar_m175[5], *h_Taustar_m250[4], *h_Taustar_m375[4], *h_Taustar_m500[4], *h_Taustar_m625[4], *h_Taustar_m750[4];
      TH1D *h_Taustar_m1000[4], *h_Taustar_m1250[4], *h_Taustar_m1500[4], *h_Taustar_m1750[4];
      TH1D *h_Taustar_m2000[4], *h_Taustar_m2500[4];
      TH1D *h_Taustar_m3000[4], *h_Taustar_m3500[4];
      TH1D *h_Taustar_m4000[4], *h_Taustar_m4500[4];
      TH1D *h_Taustar_m5000[4];

      TH1D *h_data[4];
      TH1D *h_ABCD[4];
      TH1D *h_mcsum[4];
      TH1D *h_bkgsum, *h_bkgsum_inc;
      TH1D *h_bps_0p01, *h_bps_0p01_inc;
      TH1D *h_bps_0p1, *h_bps_0p1_inc;
      TH1D *h_bps_0p5, *h_bps_0p5_inc;
      TH1D *h_bps_1, *h_bps_1_inc;
      TH1D *h_CoD, *h_CoD_inc;
      TH1D *h_BCoD, *h_BCoD_inc;
      const int nsig = 17;
      TString sigtags[17];
      const int nmc = 12;
      TString mctags[12];
};

void plotControlRegions(const TString channel, const int mass, const bool blindA)
{std::cout << "plotControlRegions() " << channel << " " << mass << " " << blindA << std::endl;

   char fname[100];
   sprintf(fname, "%s_m%d.root", channel.Data(), mass);
   TFile * f = TFile::Open(fname);

   TH1D *h_lfaketau[4], *h_truetautau[4], *h_realtau[4];
   //TH1D * h_jetfaketau[4];
   TH1D *h_taustar[4];
   TH1D *h_data[4];
   THStack *s[4];

   TH1D *h_bkgsum_inc = (TH1D*)f->Get("h_bkgsum_inc");
   TH1D *h_BCoD_inc = (TH1D*)f->Get("h_BCoD_inc");

   TH1D *h_bkgsum = (TH1D*)f->Get("h_bkgsum");
   TH1D *h_BCoD_binned = (TH1D*)f->Get("h_BCoD");

   TString title;
   if (channel=="Muon") title="#mu + #tau_{h}";
   if (channel=="Electron") title="e + #tau_{h}";
   if (channel=="Tau") title="#tau_{h} + #tau_{h}";
   if (channel=="MuonEG") title="e + #mu";

   const TString labels[4] = {"A", "B", "C", "D"};
   double max = 0.;
   for (int i = 0; i < 4; ++i) {
      s[i] = new THStack("s_"+labels[i], "");

      //h_jetfaketau[i] = (TH1D*)f->Get("h_jetfaketau_"+labels[i]);
      //h_jetfaketau[i]->SetFillColor(222);
      //s[i]->Add(h_jetfaketau[i]);

      h_lfaketau[i] = (TH1D*)f->Get("h_lfaketau_"+labels[i]);
      h_lfaketau[i]->SetFillColor(222);
      s[i]->Add(h_lfaketau[i]);

      h_realtau[i] = (TH1D*)f->Get("h_realtau_"+labels[i]);
      h_realtau[i]->SetFillColor(226);
      s[i]->Add(h_realtau[i]);

      h_truetautau[i] = (TH1D*)f->Get("h_truetautau_"+labels[i]);
      h_truetautau[i]->SetFillColor(209);
      s[i]->Add(h_truetautau[i]);

      char hname[100];
      sprintf(hname, "h_Taustar_m%d_%s", mass, labels[i].Data());
      h_taustar[i] = (TH1D*)f->Get(hname);
      h_taustar[i]->SetLineColor(94);
      h_taustar[i]->SetLineWidth(2);

      h_data[i] = (TH1D*)f->Get("h_data_"+labels[i]);
      h_data[i]->SetMarkerStyle(20);
      max = TMath::Max(max, h_data[i]->GetMaximum());

     char title[100];
     sprintf(title, "%s;%s;%s", h_taustar[i]->GetTitle(), h_taustar[i]->GetXaxis()->GetTitle(), h_taustar[i]->GetYaxis()->GetTitle());
     s[i]->SetTitle(title);
   }

   h_BCoD_inc->SetFillColor(207);
   s[0]->Add(h_BCoD_inc);

   const double ymax = pow(10, ceil(log10(max))+1);
   double ymin = 0.01;
   if (max>=10.) ymin = 0.1;
   if (max>=100.) ymin = 1.;
   if (max>=1000.) ymin = 10.;
   if (max>=10000.) ymin = 100.;
   //const double ymin = 0.1;

   TLegend * lA = new TLegend(0.25, 0.7, 0.875, 0.875);
   lA->SetNColumns(2);
   lA->SetBorderSize(0);
   //lA->AddEntry(h_jetfaketau[0], "jet #rightarrow #tau_{h}", "F");
   lA->AddEntry(h_lfaketau[0], "e,#mu,#tau_{e},#tau_{#mu} #rightarrow #tau_{h}", "F");
   lA->AddEntry(h_realtau[0], "#tau_{h} #rightarrow #tau_{h}; !#tau#tau", "F");
   lA->AddEntry(h_truetautau[0], "true #tau#tau", "F");
   lA->AddEntry(h_taustar[0], "#tau* "+TString::Itoa(mass, 10), "L");

   TLegend *lBCD = (TLegend*)lA->Clone();
   
   lA->AddEntry(h_BCoD_inc, "jet", "F");
   if (!blindA) lA->AddEntry(h_data[0], "data", "P");
   lBCD->AddEntry(h_data[1], "data", "P");

   TCanvas * canvas = new TCanvas("canvas", "canvas", 1200, 800);
   canvas->Divide(3, 2);

   TPad * p2 = (TPad*)canvas->cd(2);
   s[0]->Draw("HIST");
   h_taustar[0]->Draw("HIST, E, SAME");
   if (!blindA) h_data[0]->Draw("P, SAME");
   p2->SetLogy();
   lA->Draw();
   s[0]->SetMaximum(ymax); s[0]->SetMinimum(ymin);

   TPad * p3 = (TPad*)canvas->cd(3);
   s[1]->Draw("HIST");
   h_taustar[1]->Draw("HIST, E, SAME");
   h_data[1]->Draw("P, SAME");
   p3->SetLogy();
   lBCD->Draw();
   s[1]->SetMaximum(ymax); s[1]->SetMinimum(ymin);

   TPad * p5 = (TPad*)canvas->cd(5);
   s[2]->Draw("HIST");
   h_taustar[2]->Draw("HIST, E, SAME");
   h_data[2]->Draw("P, SAME");
   p5->SetLogy();
   lBCD->Draw();
   s[2]->SetMaximum(ymax); s[2]->SetMinimum(ymin);

   TPad * p6 = (TPad*)canvas->cd(6);
   s[3]->Draw("HIST");
   h_taustar[3]->Draw("HIST, E, SAME");
   h_data[3]->Draw("P, SAME");
   p6->SetLogy();
   lBCD->Draw();
   s[3]->SetMaximum(ymax); s[3]->SetMinimum(ymin);

   TPad * p4 = (TPad*)canvas->cd(4);
   TH1D *h_CoD = (TH1D*)f->Get("h_CoD");
   TH1D *h_CoD_inc = (TH1D*)f->Get("h_CoD_inc");
   h_CoD->Draw("PE");
   h_CoD->SetMarkerStyle(20);
   h_CoD->SetStats(0);
   h_CoD->SetMinimum(0.);
   h_CoD->SetMaximum(2*h_CoD->GetMaximum());
   //p4->SetLogy();
   //h_CoD->SetMinimum(0.8*(h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1)));
   //h_CoD->SetMaximum(1.2*(h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1)));
   TLine * lup = new TLine(h_CoD_inc->GetBinLowEdge(1), h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1), h_CoD_inc->GetBinLowEdge(h_CoD_inc->GetNbinsX()+1), h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1));
   lup->SetLineStyle(2);
   lup->Draw();
   TLine * ldown = new TLine(h_CoD_inc->GetBinLowEdge(1), h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1), h_CoD_inc->GetBinLowEdge(h_CoD_inc->GetNbinsX()+1), h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1));  
   ldown->SetLineStyle(2);
   ldown->Draw();

   if (!blindA) {
      canvas->cd(1);

      TH1D * r = (TH1D*)h_data[0]->Clone("r");
      r->Divide(h_bkgsum);
      r->GetYaxis()->SetTitle("observed / prediction");
      r->SetMarkerStyle(20);
      r->SetMarkerColor(8);
      r->SetLineColor(8);
      r->Draw("PE");
      r->SetStats(0);
      r->SetMinimum(0.);
      r->SetMaximum(2.);

      TH1D * r_inc = (TH1D*)h_data[0]->Clone("r_inc");
      r_inc->Divide(h_bkgsum_inc);
      r_inc->SetMarkerStyle(20);
      r_inc->SetMarkerColor(9);
      r_inc->SetLineColor(9);
      r_inc->Draw("PE, SAME");

      TLegend * l2 = new TLegend(0.25, 0.75, 0.875, 0.875);
      l2->SetBorderSize(0);
      l2->SetNColumns(2);
      l2->AddEntry(r, "binned C/D ", "P");
      l2->AddEntry(r_inc, "inclusive C/D", "P");
      l2->Draw();

      TLine * line = new TLine(r->GetBinLowEdge(1), 1., r->GetBinLowEdge(r->GetNbinsX()+1), 1.);
      line->SetLineStyle(2);
      line->Draw();      

   }
   char outfile[50];
   sprintf(outfile, "%s_m%d.pdf", channel.Data(), mass);
   canvas->SaveAs(outfile);
}

/*void plotControlRegions(const TString channel, const int mass, const bool blindA)
{std::cout << "plotControlRegions() " << channel << " " << mass << " " << blindA << std::endl;

   char fname[100];
   sprintf(fname, "%s_m%d.root", channel.Data(), mass);
   TFile * f = TFile::Open(fname);

   TH1D *h_WW[4], *h_WZ[4], *h_ZZ[4];
   TH1D *h_TTTo2L2Nu[4], *h_TTToSemiLeptonic[4];
   TH1D *h_ST_tW_top[4], *h_ST_tW_antitop[4];
   TH1D *h_ST_t_channel_top[4], *h_ST_t_channel_antitop[4];
   TH1D *h_DYJetsToLLM10[4];
   TH1D *h_DYJetsToEEMuMu[4], *h_DYJetsToTauTau[4];
   TH1D *h_taustar[4];
   TH1D *h_data[4];
   THStack *s[4];

   TH1D *h_bkgsum_inc = (TH1D*)f->Get("h_bkgsum_inc");
   TH1D *h_BCoD_inc = (TH1D*)f->Get("h_BCoD_inc");

   TH1D *h_bkgsum = (TH1D*)f->Get("h_bkgsum");
   TH1D *h_BCoD_binned = (TH1D*)f->Get("h_BCoD");

   TString title;
   if (channel=="Electron") title="e + #tau_{h}";
   if (channel=="Muon") title="#mu + #tau_{h}";
   if (channel=="Tau") title="#tau_{h} + #tau_{h}";
   if (channel=="MuonEG") title="e + #mu";

   const TString labels[4] = {"A", "B", "C", "D"};
   double max = 0.;
   for (int i = 0; i < 4; ++i) {
      s[i] = new THStack("s_"+labels[i], "");

      h_WW[i] = (TH1D*)f->Get("h_WW_"+labels[i]);
      h_WW[i]->SetFillColor(212);
      s[i]->Add(h_WW[i]);

      h_WZ[i] = (TH1D*)f->Get("h_WZ_"+labels[i]);
      h_WZ[i]->SetFillColor(211);
      s[i]->Add(h_WZ[i]);

      h_ZZ[i] = (TH1D*)f->Get("h_ZZ_"+labels[i]);
      h_ZZ[i]->SetFillColor(210);
      s[i]->Add(h_ZZ[i]);

      h_TTTo2L2Nu[i] = (TH1D*)f->Get("h_TTTo2L2Nu_"+labels[i]);
      h_TTTo2L2Nu[i]->SetFillColor(58);
      s[i]->Add(h_TTTo2L2Nu[i]);

      h_TTToSemiLeptonic[i] = (TH1D*)f->Get("h_TTToSemiLeptonic_"+labels[i]);
      h_TTToSemiLeptonic[i]->SetFillColor(59);
      s[i]->Add(h_TTToSemiLeptonic[i]);

      h_ST_tW_top[i] = (TH1D*)f->Get("h_ST_tW_top_"+labels[i]);
      h_ST_tW_top[i]->SetFillColor(221);
      s[i]->Add(h_ST_tW_top[i]);

      h_ST_tW_antitop[i] = (TH1D*)f->Get("h_ST_tW_antitop_"+labels[i]);
      h_ST_tW_antitop[i]->SetFillColor(222);
      s[i]->Add(h_ST_tW_antitop[i]);

      h_ST_t_channel_top[i] = (TH1D*)f->Get("h_ST_t_channel_top_"+labels[i]);
      h_ST_t_channel_top[i]->SetFillColor(223);  
      s[i]->Add(h_ST_t_channel_top[i]);

      h_ST_t_channel_antitop[i] = (TH1D*)f->Get("h_ST_t_channel_antitop_"+labels[i]);
      h_ST_t_channel_antitop[i]->SetFillColor(224);
      s[i]->Add(h_ST_t_channel_antitop[i]);

      h_DYJetsToLLM10[i] = (TH1D*)f->Get("h_DYJetsToLLM10_"+labels[i]);
      h_DYJetsToLLM10[i]->SetFillColor(7);
      s[i]->Add(h_DYJetsToLLM10[i]);

      h_DYJetsToEEMuMu[i] = (TH1D*)f->Get("h_DYJetsToEEMuMu_"+labels[i]);
      h_DYJetsToEEMuMu[i]->SetFillColor(5);
      s[i]->Add(h_DYJetsToEEMuMu[i]);

      h_DYJetsToTauTau[i] = (TH1D*)f->Get("h_DYJetsToTauTau_"+labels[i]);
      h_DYJetsToTauTau[i]->SetFillColor(9);
      s[i]->Add(h_DYJetsToTauTau[i]);

      char hname[100];
      sprintf(hname, "h_Taustar_m%d_%s", mass, labels[i].Data());
      h_taustar[i] = (TH1D*)f->Get(hname);
      h_taustar[i]->SetLineColor(94);
      h_taustar[i]->SetLineWidth(2);

      h_data[i] = (TH1D*)f->Get("h_data_"+labels[i]);
      h_data[i]->SetMarkerStyle(20);
      max = TMath::Max(max, h_data[i]->GetMaximum());

     char title[100];
     sprintf(title, "%s;%s;%s", h_WW[i]->GetTitle(), h_WW[i]->GetXaxis()->GetTitle(), h_WW[i]->GetYaxis()->GetTitle());
     s[i]->SetTitle(title); 
   }

   h_BCoD_inc->SetFillColor(98);
   s[0]->Add(h_BCoD_inc);

   const double ymax = pow(10, ceil(log10(max))+1);
   double ymin = 0.01;
   if (max>=10.) ymin = 0.1;
   if (max>=100.) ymin = 1.;
   if (max>=1000.) ymin = 10.;
   if (max>=10000.) ymin = 100.;

   TLegend * lA = new TLegend(0.25, 0.7, 0.875, 0.875);
   lA->SetNColumns(3);
   lA->SetBorderSize(0);
   lA->AddEntry(h_WW[0], "WW", "F");
   lA->AddEntry(h_WZ[0], "WZ", "F");
   lA->AddEntry(h_ZZ[0], "ZZ", "F");
   lA->AddEntry(h_TTTo2L2Nu[0], "TTTo2L2Nu", "F");
   lA->AddEntry(h_TTToSemiLeptonic[0], "TTToSemiLeptonic", "F");
   lA->AddEntry(h_ST_tW_top[0], "ST_tW_top", "F");
   lA->AddEntry(h_ST_tW_antitop[0], "ST_tW_antitop", "F");
   lA->AddEntry(h_ST_t_channel_top[0], "ST_t_channel_top", "F");
   lA->AddEntry(h_ST_t_channel_antitop[0], "ST_t_channel_antitop", "F");
   lA->AddEntry(h_DYJetsToLLM10[0], "DYJetsToLLM10", "F");
   lA->AddEntry(h_DYJetsToEEMuMu[0], "DYJetsToEEMuMu", "F");
   lA->AddEntry(h_DYJetsToTauTau[0], "DYJetsToTauTau", "F");
   lA->AddEntry(h_taustar[0], "#tau* "+TString::Itoa(mass, 10), "L");

   TLegend *lBCD = (TLegend*)lA->Clone();
   
   lA->AddEntry(h_BCoD_inc, "jet", "F");
   if (!blindA) lA->AddEntry(h_data[0], "data", "P");
   lBCD->AddEntry(h_data[1], "data", "P");

   TCanvas * canvas = new TCanvas("canvas", "canvas", 1200, 800);
   canvas->Divide(3, 2);

   TPad * p2 = (TPad*)canvas->cd(2);
   s[0]->Draw("HIST");
   h_taustar[0]->Draw("HIST, E, SAME");
   if (!blindA) h_data[0]->Draw("P, SAME");
   p2->SetLogy();
   lA->Draw();
   s[0]->SetMaximum(ymax); s[0]->SetMinimum(ymin);

   TPad * p3 = (TPad*)canvas->cd(3);
   s[1]->Draw("HIST");
   h_taustar[1]->Draw("HIST, E, SAME");
   h_data[1]->Draw("P, SAME");
   p3->SetLogy();
   lBCD->Draw();
   s[1]->SetMaximum(ymax); s[1]->SetMinimum(ymin);

   TPad * p5 = (TPad*)canvas->cd(5);
   s[2]->Draw("HIST");
   h_taustar[2]->Draw("HIST, E, SAME");
   h_data[2]->Draw("P, SAME");
   p5->SetLogy();
   lBCD->Draw();
   s[2]->SetMaximum(ymax); s[2]->SetMinimum(ymin);

   TPad * p6 = (TPad*)canvas->cd(6);
   s[3]->Draw("HIST");
   h_taustar[3]->Draw("HIST, E, SAME");
   h_data[3]->Draw("P, SAME");
   p6->SetLogy();
   lBCD->Draw();
   s[3]->SetMaximum(ymax); s[3]->SetMinimum(ymin);

   TPad * p4 = (TPad*)canvas->cd(4);
   TH1D *h_CoD = (TH1D*)f->Get("h_CoD");
   TH1D *h_CoD_inc = (TH1D*)f->Get("h_CoD_inc");
   h_CoD->Draw("PE");
   h_CoD->SetMarkerStyle(20);
   h_CoD->SetStats(0);
   h_CoD->SetMinimum(0.);
   h_CoD->SetMaximum(2*h_CoD->GetMaximum());
   //p4->SetLogy();
   //h_CoD->SetMinimum(0.8*(h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1)));
   //h_CoD->SetMaximum(1.2*(h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1)));
   TLine * lup = new TLine(h_CoD_inc->GetBinLowEdge(1), h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1), h_CoD_inc->GetBinLowEdge(h_CoD_inc->GetNbinsX()+1), h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1));
   lup->SetLineStyle(2);
   lup->Draw();
   TLine * ldown = new TLine(h_CoD_inc->GetBinLowEdge(1), h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1), h_CoD_inc->GetBinLowEdge(h_CoD_inc->GetNbinsX()+1), h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1));  
   ldown->SetLineStyle(2);
   ldown->Draw();

   if (!blindA) {
      canvas->cd(1);

      TH1D * r = (TH1D*)h_data[0]->Clone("r");
      r->Divide(h_bkgsum);
      r->GetYaxis()->SetTitle("observed / prediction");
      r->SetMarkerStyle(20);
      r->SetMarkerColor(8);
      r->SetLineColor(8);
      r->Draw("PE");
      r->SetStats(0);
      r->SetMinimum(0.);
      r->SetMaximum(2.);

      TH1D * r_inc = (TH1D*)h_data[0]->Clone("r_inc");
      r_inc->Divide(h_bkgsum_inc);
      r_inc->SetMarkerStyle(20);
      r_inc->SetMarkerColor(9);
      r_inc->SetLineColor(9);
      r_inc->Draw("PE, SAME");

      TLegend * l2 = new TLegend(0.25, 0.75, 0.875, 0.875);
      l2->SetBorderSize(0);
      l2->SetNColumns(2);
      l2->AddEntry(r, "binned C/D ", "P");
      l2->AddEntry(r_inc, "inclusive C/D", "P");
      l2->Draw();

      TLine * line = new TLine(r->GetBinLowEdge(1), 1., r->GetBinLowEdge(r->GetNbinsX()+1), 1.);
      line->SetLineStyle(2);
      line->Draw();      

   }
   char outfile[50];
   sprintf(outfile, "%s_m%d.pdf", channel.Data(), mass);
   canvas->SaveAs(outfile);
}
*/
TString makeVar(const double mass, const TString channel)
{std::cout << "makeVar() " <<  mass << " " << channel << std::endl;

   char outstring[1000];
   const double upper=mass+0.5*mass;
   const double lower=mass-0.5*mass;

   if (channel=="Electron") {
      sprintf(outstring,
      "(ElTau_MaxCollMass<%f)?1 : (ElTau_MinCollMass>=%f)?4 : (ElTau_MaxCollMass>=%f&&ElTau_MinCollMass<%f)?3 : ((ElTau_MaxCollMass>=%f&&ElTau_MaxCollMass<%f)||(ElTau_MinCollMass>=%f&&ElTau_MinCollMass<%f))?2 : 0",
                          lower,                      upper,                      upper,                lower,                       lower,                upper,                   lower,                upper
      );
   }
   if (channel=="Muon") {
      sprintf(outstring,
      "(MuTau_MaxCollMass<%f)?1 : (MuTau_MinCollMass>=%f)?4 : (MuTau_MaxCollMass>=%f&&MuTau_MinCollMass<%f)?3 : ((MuTau_MaxCollMass>=%f&&MuTau_MaxCollMass<%f)||(MuTau_MinCollMass>=%f&&MuTau_MinCollMass<%f))?2 : 0",
                          lower,                      upper,                      upper,                lower,                       lower,                upper,                   lower,                upper
      );
   }
   if (channel=="Tau") {
      sprintf(outstring,
      "(TauTau_MaxCollMass<%f)?1 : (TauTau_MinCollMass>=%f)?4 : (TauTau_MaxCollMass>=%f&&TauTau_MinCollMass<%f)?3 : ((TauTau_MaxCollMass>=%f&&TauTau_MaxCollMass<%f)||(TauTau_MinCollMass>=%f&&TauTau_MinCollMass<%f))?2 : 0",
                           lower,                       upper,                       upper,                 lower,                        lower,                 upper,                    lower,                 upper
      );
   }
   if (channel=="MuonEG") {
      sprintf(outstring,
      "(ElMu_MaxCollMass<%f)?1 : (ElMu_MinCollMass>=%f)?4 : (ElMu_MaxCollMass>=%f&&ElMu_MinCollMass<%f)?3 : ((ElMu_MaxCollMass>=%f&&ElMu_MaxCollMass<%f)||(ElMu_MinCollMass>=%f&&ElMu_MinCollMass<%f))?2 : 0",
                           lower,                       upper,                       upper,                 lower,                        lower,                 upper,                    lower,                 upper
      );
   }

   std::cout << "end makeString()" << std::endl;
   return TString(outstring);
}

void runAnalysis::runAll()
{std::cout << "runAll()" << std::endl;

   //if (channel=="Electron") var = "ElTau_Mass";
   //if (channel=="Muon") var = "MuTau_Mass";
   //if (channel=="Tau") var = "TauTau_Mass";
   //if (channel=="MuonEG") var = "ElMu_Mass";
   //h = new TH1D("h", ";visible mass [GeV];events / 10 GeV", 20, 0., 200.);

   //var = "MuTau_MinCollMass";
   //h = new TH1D("h", ";min coll mass [GeV];events / 200 GeV", 15, 0., 3000.);

   var = makeVar(mass, channel);
   h = new TH1D("h", ";analysis bin;events / bin", 5, -0.5, 4.5);

   //var = "TMath::Abs(Photon_eta[MuTau_PhotonIdx])";
   //h = new TH1D("h", ";photon |#eta|;events / bin", 10, 0., 2.5);

   //var = "MuTau_mT";
   //h = new TH1D("h", ";mT [GeV];events / bin", 10, 0., 100.);

   //var = "1.";
   //h = new TH1D("h", ";the unit bin;events", 1, 0.5, 1.5);

   //if (channel=="Electron") var = "ElTau_ETGCollMass";
   //if (channel=="Muon") var = "MuTau_MTGCollMass";
   //if (channel=="Tau") var = "TauTau_TTGCollMass";
   //if (channel=="MuonEG") var = "ElMu_EMGCollMass";
   //h = new TH1D("h", ";3-body collinear mass [GeV];events / 100 GeV", 10, 0., 1000.);

   h->Sumw2();

   if (channel=="Electron") h->SetTitle("e + #tau_{h}");
   if (channel=="Muon") h->SetTitle("#mu + #tau_{h}");
   if (channel=="Tau") h->SetTitle("#tau_{h} + #tau_{h}");
   if (channel=="MuonEG") h->SetTitle("e + #mu");

   mctags[0] = "WW";
   //mctags[0] = "WGToLNuG";
   mctags[1] = "WZ";
   mctags[2] = "ZZ";
   mctags[3] = "TTTo2L2Nu";
   mctags[4] = "TTToSemiLeptonic";
   mctags[5] = "ST_tW_top";
   mctags[6] = "ST_tW_antitop";
   mctags[7] = "ST_t_channel_antitop";
   mctags[8] = "ST_t_channel_top";
   mctags[9] = "DYJetsToLLM10";
   mctags[10] = "DYJetsToEEMuMu";
   mctags[11] = "DYJetsToTauTau";

   sigtags[0] = "Taustar_m175";
   sigtags[1] = "Taustar_m250";
   sigtags[2] = "Taustar_m375";
   sigtags[3] = "Taustar_m500";
   sigtags[4] = "Taustar_m625";
   sigtags[5] = "Taustar_m750";
   sigtags[6] = "Taustar_m1000";
   sigtags[7] = "Taustar_m1250";
   sigtags[8] = "Taustar_m1500";
   sigtags[9] = "Taustar_m1750";
   sigtags[10] = "Taustar_m2000";
   sigtags[11] = "Taustar_m2500";
   sigtags[12] = "Taustar_m3000";
   sigtags[13] = "Taustar_m3500";
   sigtags[14] = "Taustar_m4000";
   sigtags[15] = "Taustar_m4500";
   sigtags[16] = "Taustar_m5000";

   char fname[100];
   sprintf(fname, "%s_m%d.root", channel.Data(), mass);
   fout = new TFile(fname, "RECREATE"); 

   dataHistInit();
   mcHistInit();
   sigHistInit();

   //fillMCHists(2015);
   fillMCHists(2016); fillSigHists(2016); fillDataHists(2016);
   fillMCHists(2017); fillSigHists(2017); fillDataHists(2017);
   fillMCHists(2018); fillSigHists(2018); fillDataHists(2018);

   dataHistOverflow();
   sigHistOverflow();
   mcHistOverflow();

   makeABCDHists();
   sumMCHists();
   sumBkgHists();
   bkgFraction();
   saveHists();
   fout->Close();
   plotControlRegions(channel, mass, blindA);
}

void runAnalysis::dataHistInit()
{std::cout << "dataHistInit()" << std::endl;
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      char titles[100];
      sprintf(titles, "%s: %s", h->GetTitle(), labels[i].Data());
      h_data[i] = (TH1D*)h->Clone("h_data_"+labels[i]);
      h_data[i]->SetTitle(titles);
   }
}

void runAnalysis::mcHistInit()
{std::cout << "mcHistInit()" << std::endl; 
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      char titles[100];
      sprintf(titles, "%s: %s", h->GetTitle(), labels[i].Data());
      //h_jetfaketau[i] = (TH1D*)h->Clone("h_jetfaketau_"+labels[i]);
      //h_jetfaketau[i]->SetTitle(titles);
      h_lfaketau[i] = (TH1D*)h->Clone("h_lfaketau_"+labels[i]);
      h_lfaketau[i]->SetTitle(titles);
      h_realtau[i] = (TH1D*)h->Clone("h_realtau_"+labels[i]);
      h_realtau[i]->SetTitle(titles);
      h_truetautau[i] = (TH1D*)h->Clone("h_truetautau_"+labels[i]);
      h_truetautau[i]->SetTitle(titles);
   }
}

/*void runAnalysis::mcHistInit()
{std::cout << "mcHistInit()" << std::endl;
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      char titles[100];
      sprintf(titles, "%s: %s", h->GetTitle(), labels[i].Data());
      h_WW[i] = (TH1D*)h->Clone("h_WW_"+labels[i]);
      h_WW[i]->SetTitle(titles);
      h_WZ[i] = (TH1D*)h->Clone("h_WZ_"+labels[i]);
      h_WZ[i]->SetTitle(titles);
      h_ZZ[i] = (TH1D*)h->Clone("h_ZZ_"+labels[i]);
      h_ZZ[i]->SetTitle(titles);
      h_TTTo2L2Nu[i] = (TH1D*)h->Clone("h_TTTo2L2Nu_"+labels[i]);
      h_TTTo2L2Nu[i]->SetTitle(titles);
      h_TTToSemiLeptonic[i] = (TH1D*)h->Clone("h_TTToSemiLeptonic_"+labels[i]);
      h_TTToSemiLeptonic[i]->SetTitle(titles);
      h_ST_tW_top[i] = (TH1D*)h->Clone("h_ST_tW_top_"+labels[i]);
      h_ST_tW_top[i]->SetTitle(titles);
      h_ST_tW_antitop[i] = (TH1D*)h->Clone("h_ST_tW_antitop_"+labels[i]);
      h_ST_tW_antitop[i]->SetTitle(titles);
      h_ST_t_channel_top[i] = (TH1D*)h->Clone("h_ST_t_channel_top_"+labels[i]);
      h_ST_t_channel_top[i]->SetTitle(titles);
      h_ST_t_channel_antitop[i] = (TH1D*)h->Clone("h_ST_t_channel_antitop_"+labels[i]);
      h_ST_t_channel_antitop[i]->SetTitle(titles);
      h_DYJetsToLLM10[i] = (TH1D*)h->Clone("h_DYJetsToLLM10_"+labels[i]);
      h_DYJetsToLLM10[i]->SetTitle(titles);
      h_DYJetsToEEMuMu[i] = (TH1D*)h->Clone("h_DYJetsToEEMuMu_"+labels[i]);
      h_DYJetsToEEMuMu[i]->SetTitle(titles);
      h_DYJetsToTauTau[i] = (TH1D*)h->Clone("h_DYJetsToTauTau_"+labels[i]);
      h_DYJetsToTauTau[i]->SetTitle(titles);
   }
}
*/
void runAnalysis::sigHistInit()
{std::cout << "sigHistInit()" << std::endl;
   const TString labels[4] = {"A", "B", "C", "D"};  
   for (int i = 0; i < 4; ++i) {
      h_Taustar_m175[i] = (TH1D*)h->Clone("h_Taustar_m175_"+labels[i]);
      h_Taustar_m250[i] = (TH1D*)h->Clone("h_Taustar_m250_"+labels[i]);
      h_Taustar_m375[i] = (TH1D*)h->Clone("h_Taustar_m375_"+labels[i]);
      h_Taustar_m500[i] = (TH1D*)h->Clone("h_Taustar_m500_"+labels[i]);
      h_Taustar_m625[i] = (TH1D*)h->Clone("h_Taustar_m625_"+labels[i]);
      h_Taustar_m750[i] = (TH1D*)h->Clone("h_Taustar_m750_"+labels[i]);
      h_Taustar_m1000[i] = (TH1D*)h->Clone("h_Taustar_m1000_"+labels[i]);
      h_Taustar_m1250[i] = (TH1D*)h->Clone("h_Taustar_m1250_"+labels[i]);
      h_Taustar_m1500[i] = (TH1D*)h->Clone("h_Taustar_m1500_"+labels[i]);
      h_Taustar_m1750[i] = (TH1D*)h->Clone("h_Taustar_m1750_"+labels[i]);
      h_Taustar_m2000[i] = (TH1D*)h->Clone("h_Taustar_m2000_"+labels[i]);
      h_Taustar_m2500[i] = (TH1D*)h->Clone("h_Taustar_m2500_"+labels[i]);
      h_Taustar_m3000[i] = (TH1D*)h->Clone("h_Taustar_m3000_"+labels[i]);
      h_Taustar_m3500[i] = (TH1D*)h->Clone("h_Taustar_m3500_"+labels[i]);
      h_Taustar_m4000[i] = (TH1D*)h->Clone("h_Taustar_m4000_"+labels[i]);
      h_Taustar_m4500[i] = (TH1D*)h->Clone("h_Taustar_m4500_"+labels[i]);
      h_Taustar_m5000[i] = (TH1D*)h->Clone("h_Taustar_m5000_"+labels[i]);
   }
}

void runAnalysis::loadCuts(const int year, TCut cuts[4])
{std::cout << "loadCuts() " << year << std::endl;

   TCut baseline, regionA, regionB, regionC, regionD;
   baseline = regionA = regionB = regionC = regionD = "1>0";
   if (channel=="Electron") {
      //baseline = baseline && TCut("ElTau_HavePair>0 && (ElTau_HaveTriplet==0||(ElTau_HaveTriplet>0&&Photon_pt[ElTau_PhotonIdx]<50.))");
      baseline = baseline && TCut("ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]<25.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("ElTau_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
      if (year==2015||year==2016) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=29.");
      if (year==2017) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      if (year==2018) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      baseline = baseline && TCut("ElTau_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "ElTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionC = "ElTau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   }
   if (channel=="Muon") {
      //baseline = baseline && TCut("MuTau_HavePair>0 && (MuTau_HaveTriplet==0||(MuTau_HaveTriplet>0&&Photon_pt[MuTau_PhotonIdx]<50.))");
      baseline = baseline && TCut("MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]<25.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("MuTau_Trigger");
      baseline = baseline && TCut("Muon_pfIsoId[MuTau_MuIdx]>=4");
      if (year==2015||year==2016) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=26.");
      if (year==2017) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      if (year==2018) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      baseline = baseline && TCut("MuTau_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=2)==1");
      regionA = "MuTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionC = "MuTau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   }
   if (channel=="Tau") {
      //baseline = baseline && TCut("TauTau_HavePair>0 && (TauTau_HaveTriplet==0||(TauTau_HaveTriplet>0&&Photon_pt[TauTau_PhotonIdx]<50.))");
      baseline = baseline && TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=75.");
      //baseline = baseline && TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]<25.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("TauTau_Trigger");
      baseline = baseline && TCut("Tau_pt[TauTau_Tau0Idx]>=40. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1");
      baseline = baseline && TCut("Tau_pt[TauTau_Tau1Idx]>=40. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
      baseline = baseline && TCut("TauTau_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      const TCut tau0pass = "(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau0fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau1pass = "(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      const TCut tau1fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      regionA = TCut("TauTau_qq==-1") && (tau0pass&&tau1pass);
      regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      regionC = TCut("TauTau_qq==+1") && (tau0pass&&tau1pass);
      regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      //regionB = TCut("TauTau_qq==-1") && (tau0fail || tau1fail);
      //regionD = TCut("TauTau_qq==+1") && (tau0fail || tau1fail);
   }
   if (channel=="MuonEG") {
      //baseline = baseline && TCut("ElMu_HavePair>0 && (ElMu_HaveTriplet==0||(ElMu_HaveTriplet>0&&Photon_pt[ElMu_PhotonIdx]<50.))");
      baseline = baseline && TCut("ElMu_HaveTriplet>0 && Photon_pt[ElMu_PhotonIdx]>=100.");
      //baseline = baseline && TCut("ElMu_HaveTriplet>0 && Photon_pt[ElMu_PhotonIdx]<25.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("ElMu_Trigger");
      const TCut c1 = "Electron_pt[ElMu_ElIdx]>=24. && Muon_pt[ElMu_MuIdx]>=13.";
      const TCut c2 = "Electron_pt[ElMu_ElIdx]>=13. && Muon_pt[ElMu_MuIdx]>=24.";
      baseline = baseline && (c1||c2);
      baseline = baseline && TCut("ElMu_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=2)==1");
      baseline = baseline && TCut("Muon_pfIsoId[ElMu_MuIdx]>=2 && Electron_mvaFall17V2Iso_WP90[ElMu_ElIdx]");
      const TCut looseMuon = "Muon_pfIsoId[ElMu_MuIdx]>=2 && Muon_pfIsoId[ElMu_MuIdx]<4";
      const TCut tightMuon = "Muon_pfIsoId[ElMu_MuIdx]>=4";
      const TCut looseElectron = "Electron_pfRelIso03_all[ElMu_ElIdx]>=0.08";
      const TCut tightElectron = "Electron_pfRelIso03_all[ElMu_ElIdx]<0.08";
      regionA = TCut("ElMu_qq==-1") && (tightMuon && tightElectron);
      regionB = TCut("ElMu_qq==-1") && (looseMuon || looseElectron);
      regionC = TCut("ElMu_qq==+1") && (tightMuon && tightElectron);
      regionD = TCut("ElMu_qq==+1") && (looseMuon || looseElectron);
   }
   //if (blindA) regionA = regionA && TCut("1<0");
   cuts[0] = baseline && regionA;
   cuts[1] = baseline && regionB;
   cuts[2] = baseline && regionC;
   cuts[3] = baseline && regionD;
}

void runAnalysis::fillMCHists(const int year)
{std::cout << "fillMCHists() " << year << std::endl;
   
   double lumi;
   //if (year==2015) lumi = 19500.;
   //if (year==2016) lumi = 16800.;
   if (year==2016) lumi = 36330.;
   if (year==2017) lumi = 41480.;
   if (year==2018) lumi = 59830.;

   TCut cut_lfaketau, cut_realtau, cut_truetautau;
   TCut cut_jetfaketau;
   if (channel=="Electron") {
      //cut_jetfaketau = "Tau_genPartFlav[ElTau_TauIdx]==0";
      cut_lfaketau = "Tau_genPartFlav[ElTau_TauIdx]==1||Tau_genPartFlav[ElTau_TauIdx]==2||Tau_genPartFlav[ElTau_TauIdx]==3||Tau_genPartFlav[ElTau_TauIdx]==4";
      cut_realtau = "Tau_genPartFlav[ElTau_TauIdx]==5 && Electron_genPartFlav[ElTau_ElIdx]!=15";
      cut_truetautau = "Tau_genPartFlav[ElTau_TauIdx]==5 && Electron_genPartFlav[ElTau_ElIdx]==15";
   }
   if (channel=="Muon") {
      //cut_jetfaketau = "Tau_genPartFlav[MuTau_TauIdx]==0";
      cut_lfaketau = "Tau_genPartFlav[MuTau_TauIdx]==1||Tau_genPartFlav[MuTau_TauIdx]==2||Tau_genPartFlav[MuTau_TauIdx]==3||Tau_genPartFlav[MuTau_TauIdx]==4";
      cut_realtau = "Tau_genPartFlav[MuTau_TauIdx]==5 && Muon_genPartFlav[MuTau_MuIdx]!=15";
      cut_truetautau = "Tau_genPartFlav[MuTau_TauIdx]==5 && Muon_genPartFlav[MuTau_MuIdx]==15";
   }
   if (channel=="Tau") {
      //cut_jetfaketau = "Tau_genPartFlav[TauTau_Tau0Idx]==0 || Tau_genPartFlav[TauTau_Tau1Idx]==0";
      const TCut cut_realtau_a = "Tau_genPartFlav[TauTau_Tau0Idx]==5 && (Tau_genPartFlav[TauTau_Tau1Idx]==1||Tau_genPartFlav[TauTau_Tau1Idx]==2||Tau_genPartFlav[TauTau_Tau1Idx]==3||Tau_genPartFlav[TauTau_Tau1Idx]==4)";
      const TCut cut_realtau_b = "Tau_genPartFlav[TauTau_Tau1Idx]==5 && (Tau_genPartFlav[TauTau_Tau0Idx]==1||Tau_genPartFlav[TauTau_Tau0Idx]==2||Tau_genPartFlav[TauTau_Tau0Idx]==3||Tau_genPartFlav[TauTau_Tau0Idx]==4)";
      cut_realtau = cut_realtau_a||cut_realtau_b;
      const TCut cut_lfaketau_a = "Tau_genPartFlav[TauTau_Tau0Idx]==1||Tau_genPartFlav[TauTau_Tau0Idx]==2||Tau_genPartFlav[TauTau_Tau0Idx]==3||Tau_genPartFlav[TauTau_Tau0Idx]==4";
      const TCut cut_lfaketau_b = "Tau_genPartFlav[TauTau_Tau1Idx]==1||Tau_genPartFlav[TauTau_Tau1Idx]==2||Tau_genPartFlav[TauTau_Tau1Idx]==3||Tau_genPartFlav[TauTau_Tau1Idx]==4";
      cut_lfaketau = cut_lfaketau_a && cut_lfaketau_b;
      cut_truetautau = "Tau_genPartFlav[TauTau_Tau0Idx]==5 && Tau_genPartFlav[TauTau_Tau1Idx]==5";
   }
   if (channel=="MuonEG") {

      //j->e or j->mu or both
      //const TCut cut_jetfaketau_a = "Electron_genPartFlav[ElMu_ElIdx]==5 || Electron_genPartFlav[ElMu_ElIdx]==4 || Electron_genPartFlav[ElMu_ElIdx]==3";
      //const TCut cut_jetfaketau_b = "Muon_genPartFlav[ElMu_MuIdx]==5 || Muon_genPartFlav[ElMu_MuIdx]==4 || Muon_genPartFlav[ElMu_MuIdx]==3";
      //cut_jetfaketau = cut_jetfaketau_a || cut_jetfaketau_b;

      //one lepton is from a tau decay and the other is prompt
      cut_lfaketau = "(Electron_genPartFlav[ElMu_ElIdx]==1 && Muon_genPartFlav[ElMu_MuIdx]==15) || (Electron_genPartFlav[ElMu_ElIdx]==15 && Muon_genPartFlav[ElMu_MuIdx]==1)";
      //both leptons are true leptons, but not from tau decay
      cut_realtau = "Electron_genPartFlav[ElMu_ElIdx]==1 && Muon_genPartFlav[ElMu_MuIdx]==1";
      //both leptons are from tau decays 
      cut_truetautau = "Electron_genPartFlav[ElMu_ElIdx]==15 && Muon_genPartFlav[ElMu_MuIdx]==15";
   }

   TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021";

   //TChain * c = new TChain("Events");
   TChain c("Events");
   for (int i = 0; i < nmc; ++i) {
      char infile[1000];
      sprintf(infile, "%s/%s_%d.root", eostag.Data(), mctags[i].Data(), year);
      std::cout <<infile << std::endl;
      c.Add(infile);
   }

   const TString labels[4] = {"A", "B", "C", "D"};
   TCut cuts[4];
   loadCuts(year, cuts);
   for (int i = 0; i < 4; ++i) {
      const int n = c.GetEntries(cuts[i]);
      int ntot = 0;
      // jet fake tau
      //char buffer1[3000];
      //sprintf(buffer1, "%f * xsWeight * (%s)", lumi, TString(cuts[i] && cut_jetfaketau).Data());
      //char hname1[100];
      //sprintf(hname1, "+h_jetfaketau_%s", labels[i].Data());
      //ntot += c.Project(hname1, var, buffer1);
      // e mu fake tau
      char buffer2[3000];
      sprintf(buffer2, "%f * xsWeight * (%s)", lumi, TString(cuts[i] && cut_lfaketau).Data());
      char hname2[100];
      sprintf(hname2, "+h_lfaketau_%s", labels[i].Data());
      ntot += c.Project(hname2, var, buffer2);
      // real tau
      char buffer3[3000];
      sprintf(buffer3, "%f * xsWeight * (%s)", lumi, TString(cuts[i] && cut_realtau).Data());
      char hname3[100];
      sprintf(hname3, "+h_realtau_%s", labels[i].Data());
      ntot += c.Project(hname3, var, buffer3);
      // true tautau
      char buffer4[3000];
      sprintf(buffer4, "%f * xsWeight * (%s)", lumi, TString(cuts[i] && cut_truetautau).Data());
      char hname4[100];
      sprintf(hname4, "+h_truetautau_%s", labels[i].Data());
      ntot += c.Project(hname4, var, buffer4);
      if (ntot!=n) {
         std::cout << "**** missing some entries! ****" << std::endl;
         std::cout << " entries in region: " << n << std::endl;
         std::cout << " entries in projections: " << ntot << std::endl;
      }
   }
}

/*void runAnalysis::fillMCHists(const int year)
{std::cout << "fillMCHists() " << year << std::endl;
   
   const bool vetoFake = true;
   TCut cut_vetoFake;
   if (vetoFake) {
      if (channel=="Electron") cut_vetoFake = "Tau_genPartFlav[ElTau_TauIdx]==1||Tau_genPartFlav[ElTau_TauIdx]==2||Tau_genPartFlav[ElTau_TauIdx]==3||Tau_genPartFlav[ElTau_TauIdx]==4||Tau_genPartFlav[ElTau_TauIdx]==5";
      if (channel=="Muon")     cut_vetoFake = "Tau_genPartFlav[MuTau_TauIdx]==1||Tau_genPartFlav[MuTau_TauIdx]==2||Tau_genPartFlav[MuTau_TauIdx]==3||Tau_genPartFlav[MuTau_TauIdx]==4||Tau_genPartFlav[MuTau_TauIdx]==5"; 
      if (channel=="Tau") {
         const TCut cut_vetoFake0 = "Tau_genPartFlav[TauTau_Tau0Idx]==1||Tau_genPartFlav[TauTau_Tau0Idx]==2||Tau_genPartFlav[TauTau_Tau0Idx]==3||Tau_genPartFlav[TauTau_Tau0Idx]==4||Tau_genPartFlav[TauTau_Tau0Idx]==5";
         const TCut cut_vetoFake1 = "Tau_genPartFlav[TauTau_Tau1Idx]==1||Tau_genPartFlav[TauTau_Tau1Idx]==2||Tau_genPartFlav[TauTau_Tau1Idx]==3||Tau_genPartFlav[TauTau_Tau1Idx]==4||Tau_genPartFlav[TauTau_Tau1Idx]==5"; 
         cut_vetoFake = cut_vetoFake0 && cut_vetoFake1;
      }
   }

   double lumi;
   //if (year==2015) lumi = 19500.;
   //if (year==2016) lumi = 16800.;
   if (year==2016) lumi = 19500.+16800.;
   if (year==2017) lumi = 41480.;
   if (year==2018) lumi = 59830.;
   TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/";
   const TString labels[4] = {"A", "B", "C", "D"};
   TCut cuts[4];
   loadCuts(year, cuts);
   for (int i = 0; i < nmc; ++i) {
      std::cout << "filling " << mctags[i] << std::endl;
      char infile[100];
      sprintf(infile, "%s/%s_%d.root", eostag.Data(), mctags[i].Data(), year);
      //std::cout << infile << std::endl;
      TFile * f = TFile::Open(infile);
      if (f==NULL) continue;
      TTree * t = (TTree*)f->Get("Events");
      for (int j = 0; j < 4; ++j) {
         char buffer[3000];
         if (vetoFake) {
            sprintf(buffer, "%f * xsWeight * (%s)", lumi, TString(cuts[j]&&cut_vetoFake).Data());
         } else {
            sprintf(buffer, "%f * xsWeight * (%s)", lumi, TString(cuts[j]).Data());
         }
         fout->cd();
         char hname[100];
         sprintf(hname, "+h_%s_%s", mctags[i].Data(), labels[j].Data());
         std::cout << " entries in projection: " << t->Project(hname, var, buffer) << std::endl;
      }
   }
}
*/

void runAnalysis::fillSigHists(const int year)
{std::cout << "fillSigHists(): " << year << std::endl;

   double lumi;
   //if (year==2015) lumi = 19500.;
   //if (year==2016) lumi = 16800.;
   if (year==2016) lumi = 36330.;
   if (year==2017) lumi = 41480.;
   if (year==2018) lumi = 59830.;

   const TString labels[4] = {"A", "B", "C", "D"};
   TCut cuts[4];
   loadCuts(year, cuts);

   const TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_26042021";
   for (int i = 0; i < nsig; ++i) {
      std::cout << "filling " << sigtags[i] << std::endl;
      char infile[100];
      sprintf(infile, "%s/%s_%d.root", eostag.Data(), sigtags[i].Data(), year);
      TFile * f = TFile::Open(infile);
      if (!f) continue;
      TTree * t = (TTree*)f->Get("Events");
      for (int j = 0; j < 4; ++j) {
         char buffer[3000];
         sprintf(buffer, "%f * xsWeight * (%s)", lumi, TString(cuts[j]).Data());
         fout->cd();
         char hname[100];
         sprintf(hname, "+h_%s_%s", sigtags[i].Data(), labels[j].Data());
         std::cout << " entries in projection: " << t->Project(hname, var, buffer) << std::endl;
      }
   }
}

void runAnalysis::fillDataHists(const int year)
{std::cout << "fillDataHists(): " << year << std::endl;
   
   std::vector<TString> letters;
   if (year==2018) {
      letters.push_back("A");
      letters.push_back("B");
      letters.push_back("C");
      letters.push_back("D");
   }
   if (year==2017) {
      letters.push_back("B");
      letters.push_back("C");
      letters.push_back("D");
      letters.push_back("E");
      letters.push_back("F");
   }
   if (year==2016) { 
      letters.push_back("B");
      letters.push_back("C");
      letters.push_back("D");
      letters.push_back("E");
      letters.push_back("F");
      letters.push_back("G");
      letters.push_back("H");
   }
   TCut cuts[4]; 
   loadCuts(year, cuts);

   const TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021";
   for (auto i = letters.begin(); i != letters.end(); ++i) {
      char infile[100];
      if (channel=="MuonEG") {
         sprintf(infile, "%s/%s%s_%d.root", eostag.Data(), "ElMu", i->Data(), year);
      } else {
         sprintf(infile, "%s/%s%s_%d.root", eostag.Data(), channel.Data(), i->Data(), year);
      }
      //std::cout << infile << std::endl;
      TFile * f = TFile::Open(infile);
      TTree * t = (TTree*)f->Get("Events");
      fout->cd();
      for (int j = 0; j < 4; ++j) {
         if (j==0 && blindA) continue;
         char histname[100];
         sprintf(histname, "+%s", h_data[j]->GetName());
         std::cout << " entries in projection: " << t->Project(histname, var, cuts[j]) << std::endl;
      }
   }
}

void runAnalysis::dataHistOverflow()
{std::cout << "dataHistOverflow()" << std::endl;
   for (int i = 0; i < 4; ++i) {
      addOverflow(h_data[i]);
   }
}

void runAnalysis::mcHistOverflow()
{std::cout << "mcHistOverflow()" << std::endl;
   for (int i = 0; i < 4; ++i) {
      //addOverflow(h_jetfaketau[i]);
      addOverflow(h_lfaketau[i]);
      addOverflow(h_realtau[i]);
      addOverflow(h_truetautau[i]);
      addOverflow(h_data[i]);
   }
}

/*void runAnalysis::mcHistOverflow()
{std::cout << "mcHistOverflow()" << std::endl;
  for (int i = 0; i < 4; ++i) {
      addOverflow(h_WW[i]);
      addOverflow(h_WZ[i]);
      addOverflow(h_ZZ[i]);
      addOverflow(h_TTTo2L2Nu[i]);
      addOverflow(h_TTToSemiLeptonic[i]);
      addOverflow(h_ST_tW_top[i]);
      addOverflow(h_ST_tW_antitop[i]);
      addOverflow(h_ST_t_channel_top[i]);
      addOverflow(h_ST_t_channel_antitop[i]);
      addOverflow(h_DYJetsToLLM10[i]);
      addOverflow(h_DYJetsToEEMuMu[i]);
      addOverflow(h_DYJetsToTauTau[i]);
   }
}*/

void runAnalysis::sigHistOverflow()
{std::cout << "sigHistOverflow()" << std::endl;
   for (int i = 0; i < 4; ++i) {
      addOverflow(h_Taustar_m175[i]);
      addOverflow(h_Taustar_m250[i]);
      addOverflow(h_Taustar_m375[i]);
      addOverflow(h_Taustar_m500[i]);
      addOverflow(h_Taustar_m625[i]);
      addOverflow(h_Taustar_m750[i]);
      addOverflow(h_Taustar_m1000[i]);
      addOverflow(h_Taustar_m1250[i]);
      addOverflow(h_Taustar_m1500[i]);
      addOverflow(h_Taustar_m1750[i]);
      addOverflow(h_Taustar_m2000[i]);
      addOverflow(h_Taustar_m2500[i]);
      addOverflow(h_Taustar_m3000[i]);
      addOverflow(h_Taustar_m3500[i]);
      addOverflow(h_Taustar_m4000[i]);
      addOverflow(h_Taustar_m4500[i]);
      addOverflow(h_Taustar_m5000[i]);
   }
}

void runAnalysis::makeABCDHists()
{std::cout << "makeABCDHists()" << std::endl;
   
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      h_ABCD[i] = (TH1D*)h_data[i]->Clone("h_ABCD_"+labels[i]);
      //h_ABCD[i]->Add(h_jetfaketau[i], -1.);
      h_ABCD[i]->Add(h_lfaketau[i], -1.);
      h_ABCD[i]->Add(h_realtau[i], -1.);
      h_ABCD[i]->Add(h_truetautau[i], -1.);
   }
   /*for (int i = 0; i < 4; ++i) {
      h_ABCD[i] = (TH1D*)h_data[i]->Clone("h_ABCD_"+labels[i]);
      h_ABCD[i]->Add(h_WW[i], -1.);
      h_ABCD[i]->Add(h_WZ[i], -1.);
      h_ABCD[i]->Add(h_ZZ[i], -1.);
      h_ABCD[i]->Add(h_TTTo2L2Nu[i], -1.);
      h_ABCD[i]->Add(h_TTToSemiLeptonic[i], -1.);
      h_ABCD[i]->Add(h_ST_tW_top[i], -1.);
      h_ABCD[i]->Add(h_ST_tW_antitop[i], -1.);
      h_ABCD[i]->Add(h_ST_t_channel_top[i], -1.);
      h_ABCD[i]->Add(h_ST_t_channel_antitop[i], -1.);
      h_ABCD[i]->Add(h_DYJetsToLLM10[i], -1.);
      h_ABCD[i]->Add(h_DYJetsToEEMuMu[i], -1.);
      h_ABCD[i]->Add(h_DYJetsToTauTau[i], -1.);
   }*/

   double Berr, Cerr, Derr;
   const double Bin = h_ABCD[1]->IntegralAndError(1, h->GetNbinsX()+1, Berr);
   const double Cin = h_ABCD[2]->IntegralAndError(1, h->GetNbinsX()+1, Cerr);
   const double Din = h_ABCD[3]->IntegralAndError(1, h->GetNbinsX()+1, Derr);
   std::cout << "inclusive B: " << Bin << "+-" << Berr << std::endl;
   std::cout << "inclusive C: " << Cin << "+-" << Cerr << std::endl;
   std::cout << "inclusive D: " << Din << "+-" << Derr << std::endl;
   const double CoD = Cin/Din;
   const double CoDerr = CoD * sqrt( (Cerr/Cin)*(Cerr/Cin) + (Derr/Din)*(Derr/Din) );
   std::cout << "inclusive transfer factor: " << CoD << " +- " << CoDerr << std::endl;
   const double BCoD = Bin * CoD;
   const double BCoDerr = BCoD * sqrt( (Berr/Bin)*(Berr/Bin) + (CoDerr/CoD)*(CoDerr/CoD) );
   std::cout << "inclusive prediction: " << BCoD << " +- " << BCoDerr << std::endl;

   char title_CoD[100];
   TString temptitle;
   if (channel=="Electron") temptitle="e + #tau_{h}";
   if (channel=="Muon")     temptitle="#mu + #tau_{h}";
   if (channel=="Tau")      temptitle="#tau_{h} + #tau_{h}";
   if (channel=="MuonEG")     temptitle="e + #mu";
   sprintf(title_CoD, "%s;%s;C / D", temptitle.Data(), h_ABCD[1]->GetXaxis()->GetTitle());

   // calculate the binned C / D
   h_CoD = (TH1D*)h_ABCD[2]->Clone("h_CoD");
   h_CoD->SetTitle(title_CoD);
   h_CoD->Divide(h_ABCD[3]);
   // calculate the inclusive C / D
   h_CoD_inc = (TH1D*)h->Clone("h_CoD_inc"); 
   h_CoD_inc->SetTitle(title_CoD);
   for (int i = 1; i <= h->GetNbinsX(); ++i) {
      h_CoD_inc->SetBinContent(i, CoD);
      h_CoD_inc->SetBinError(i, CoDerr);
   }
   // calculate the binned B * C / D
   h_BCoD = (TH1D*)h_CoD->Clone("h_BCoD");
   h_BCoD->Multiply(h_ABCD[1]);
   // calculate the inclusive B * C / D
   h_BCoD_inc = (TH1D*)h_CoD_inc->Clone("h_BCoD_inc");
   h_BCoD_inc->Multiply(h_ABCD[1]);
}

void runAnalysis::sumMCHists()
{std::cout << "sumMCHists()" << std::endl;
   
   fout->cd();
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      h_mcsum[i] = (TH1D*)h_realtau[i]->Clone("h_mcsum_"+labels[i]);
      h_mcsum[i]->Add(h_lfaketau[i]);
      h_mcsum[i]->Add(h_truetautau[i]);
      //h_mcsum[i]->Add(h_jetfaketau[i]);
   }
}

/*void runAnalysis::sumMCHists()
{std::cout << "sumMCHists()" << std::endl;
   
   fout->cd();
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      h_mcsum[i] = (TH1D*)h_WW[i]->Clone("h_mcsum_"+labels[i]);
      h_mcsum[i]->Add(h_WZ[i]);
      h_mcsum[i]->Add(h_ZZ[i]);
      h_mcsum[i]->Add(h_TTTo2L2Nu[i]);
      h_mcsum[i]->Add(h_TTToSemiLeptonic[i]);
      h_mcsum[i]->Add(h_ST_tW_top[i]);
      h_mcsum[i]->Add(h_ST_tW_antitop[i]);
      h_mcsum[i]->Add(h_ST_t_channel_top[i]);
      h_mcsum[i]->Add(h_ST_t_channel_antitop[i]);
      h_mcsum[i]->Add(h_DYJetsToLLM10[i]);
      h_mcsum[i]->Add(h_DYJetsToEEMuMu[i]);
      h_mcsum[i]->Add(h_DYJetsToTauTau[i]);
   }
}*/

void runAnalysis::sumBkgHists()
{std::cout << "sumBkgHists()" << std::endl;
   
   h_bkgsum_inc = (TH1D*)h_mcsum[0]->Clone("h_bkgsum_inc");
   h_bkgsum_inc->Add(h_BCoD_inc);

   h_bkgsum = (TH1D*)h_mcsum[0]->Clone("h_bkgsum");
   h_bkgsum->Add(h_BCoD);

   h_bps_0p01_inc = (TH1D*)h_bkgsum_inc->Clone("h_bps_0p01_inc");
   h_bps_0p01 = (TH1D*)h_bkgsum->Clone("h_bps_0p01");

   h_bps_0p1_inc = (TH1D*)h_bkgsum_inc->Clone("h_bps_0p1_inc");
   h_bps_0p1 = (TH1D*)h_bkgsum->Clone("h_bps_0p1");

   h_bps_0p5_inc = (TH1D*)h_bkgsum_inc->Clone("h_bps_0p5_inc");
   h_bps_0p5 = (TH1D*)h_bkgsum->Clone("h_bps_0p5");

   h_bps_1_inc = (TH1D*)h_bkgsum_inc->Clone("h_bps_1_inc");
   h_bps_1 = (TH1D*)h_bkgsum->Clone("h_bps_1");

   TH1D * h_temp = (TH1D*)h->Clone("h_temp");;
   if (mass==175) h_temp = (TH1D*)h_Taustar_m175[0]->Clone("h_temp");
   if (mass==250) h_temp = (TH1D*)h_Taustar_m250[0]->Clone("h_temp");
   if (mass==375) h_temp = (TH1D*)h_Taustar_m375[0]->Clone("h_temp");
   if (mass==500) h_temp = (TH1D*)h_Taustar_m500[0]->Clone("h_temp");
   if (mass==625) h_temp = (TH1D*)h_Taustar_m625[0]->Clone("h_temp");
   if (mass==750) h_temp = (TH1D*)h_Taustar_m750[0]->Clone("h_temp");
   if (mass==1000) h_temp = (TH1D*)h_Taustar_m1000[0]->Clone("h_temp");
   if (mass==1250) h_temp = (TH1D*)h_Taustar_m1250[0]->Clone("h_temp");
   if (mass==1500) h_temp = (TH1D*)h_Taustar_m1500[0]->Clone("h_temp");
   if (mass==1750) h_temp = (TH1D*)h_Taustar_m1750[0]->Clone("h_temp");
   if (mass==2000) h_temp = (TH1D*)h_Taustar_m2000[0]->Clone("h_temp");
   if (mass==2500) h_temp = (TH1D*)h_Taustar_m2500[0]->Clone("h_temp");
   if (mass==3000) h_temp = (TH1D*)h_Taustar_m3000[0]->Clone("h_temp");
   if (mass==3500) h_temp = (TH1D*)h_Taustar_m3500[0]->Clone("h_temp");
   if (mass==4000) h_temp = (TH1D*)h_Taustar_m4000[0]->Clone("h_temp");
   if (mass==4500) h_temp = (TH1D*)h_Taustar_m4500[0]->Clone("h_temp");
   if (mass==5000) h_temp = (TH1D*)h_Taustar_m5000[0]->Clone("h_temp");

   h_temp->Scale(0.01);
   h_bps_0p01_inc->Add(h_temp);
   h_bps_0p01->Add(h_temp);

   h_temp->Scale(100 * 0.1);
   h_bps_0p1_inc->Add(h_temp);
   h_bps_0p1->Add(h_temp);

   h_temp->Scale(10 * 0.5);
   h_bps_0p5_inc->Add(h_temp);
   h_bps_0p5->Add(h_temp);

   h_temp->Scale(2. * 1.);
   h_bps_1_inc->Add(h_temp);
   h_bps_1->Add(h_temp);
}

void runAnalysis::bkgFraction()
{std::cout << "bkgFraction()" << std::endl;
   
   const TString labels[4] = {"A", "B", "C", "D"};
   std::cout << "expected background fractions: ; # of entries" << std::endl;
   for (int i = 0; i < 4; ++i) {
      std::cout << " region " << labels[i] << std::endl;
      double sum = 0.;
      if (i==0 && !blindA) std::cout << "yield in data: " << h_data[i]->GetEntries() << std::endl;
      if (i==0) sum = h_bkgsum_inc->Integral(); //mc+prediction
      if (i==1||i==2||i==3) {
         sum = h_data[i]->Integral();
         std::cout << "yield in data: " << h_data[i]->GetEntries() << std::endl;
      }
      if (sum==0.) {
         std::cout << "  *** NO EVENTS in Integral() ***" << std::endl;
         sum=1.;
      }
      //std::cout << "  jetfaketau: " << h_jetfaketau[i]->Integral()/sum << "; " << h_jetfaketau[i]->GetEntries() << std::endl;
      std::cout << "  lfaketau: " << h_lfaketau[i]->Integral()/sum << "; " << h_lfaketau[i]->GetEntries() << std::endl;
      std::cout << "  realtau: " << h_realtau[i]->Integral()/sum << "; " << h_realtau[i]->GetEntries() << std::endl;
      std::cout << "  truetautau: " << h_truetautau[i]->Integral()/sum << "; " << h_truetautau[i]->GetEntries() << std::endl;
      /*std::cout << "  WW: " << h_WW[i]->Integral()/sum << "; " << h_WW[i]->GetEntries() << std::endl;
      std::cout << "  WZ: " << h_WZ[i]->Integral()/sum << "; " << h_WZ[i]->GetEntries() << std::endl;
      std::cout << "  ZZ: " << h_ZZ[i]->Integral()/sum << "; " << h_ZZ[i]->GetEntries() << std::endl;
      std::cout << "  TTTo2L2Nu: " << h_TTTo2L2Nu[i]->Integral()/sum << "; " << h_TTTo2L2Nu[i]->GetEntries() << std::endl;
      std::cout << "  TTToSemiLeptonic: " << h_TTToSemiLeptonic[i]->Integral()/sum << "; " << h_TTToSemiLeptonic[i]->GetEntries() << std::endl;
      std::cout << "  ST_tW_top: " << h_ST_tW_top[i]->Integral()/sum << "; " << h_ST_tW_top[i]->GetEntries() << std::endl;
      std::cout << "  ST_tW_antitop: " <<h_ST_tW_antitop[i] ->Integral()/sum << "; " << h_ST_tW_antitop[i]->GetEntries() << std::endl;
      std::cout << "  ST_t_channel_top: " << h_ST_t_channel_top[i]->Integral()/sum << "; " << h_ST_t_channel_top[i]->GetEntries() << std::endl;
      std::cout << "  ST_t_channel_antitop: " << h_ST_t_channel_antitop[i]->Integral()/sum << "; " << h_ST_t_channel_antitop[i]->GetEntries() << std::endl;
      std::cout << "  DYJetsToLLM10: " << h_DYJetsToLLM10[i]->Integral()/sum << "; " << h_DYJetsToLLM10[i]->GetEntries() << std::endl;
      std::cout << "  DYJetsToEEMuMu: " << h_DYJetsToEEMuMu[i]->Integral()/sum << "; " << h_DYJetsToEEMuMu[i]->GetEntries() << std::endl;
      std::cout << "  DYJetsToTauTau: " << h_DYJetsToTauTau[i]->Integral()/sum << "; " << h_DYJetsToTauTau[i]->GetEntries() << std::endl;*/
      if (i==0) std::cout << "  jet prediction: " << h_BCoD_inc->Integral()/sum << "; " << h_BCoD_inc->GetEntries() << std::endl;
      if (i==1||i==2||i==3) std::cout << "  jet residual: " << h_ABCD[i]->Integral()/sum << "; " << h_ABCD[i]->GetEntries() << std::endl;
   }
}

void runAnalysis::saveHists()
{std::cout << "saveHists()" << std::endl;

   //quick sum
   //for (int i = 0; i < 4; ++i) h_realtau[i]->Add(h_lfaketau[i]);

   fout->cd();
   for (int i = 0; i < 4; ++i) {
      //h_jetfaketau[i]->Write();
      h_lfaketau[i]->Write();
      h_realtau[i]->Write();
      h_truetautau[i]->Write();
   }
   /*for (int i = 0; i < 4; ++i) {
      h_WW[i]->Write();
      h_WZ[i]->Write();
      h_ZZ[i]->Write();
      h_TTTo2L2Nu[i]->Write();
      h_TTToSemiLeptonic[i]->Write();
      h_ST_tW_top[i]->Write();
      h_ST_tW_antitop[i]->Write();
      h_ST_t_channel_top[i]->Write();
      h_ST_t_channel_antitop[i]->Write();
      h_DYJetsToLLM10[i]->Write();
      h_DYJetsToEEMuMu[i]->Write();
      h_DYJetsToTauTau[i]->Write();
   }*/

   for (int i = 0; i < 4; ++i) {
      h_mcsum[i]->Write();
      h_ABCD[i]->Write();
      h_data[i]->Write();
   }
   h_bkgsum->Write();
   h_bkgsum_inc->Write();
   h_bps_0p01->Write(); h_bps_0p01_inc->Write();
   h_bps_0p1->Write(); h_bps_0p1_inc->Write();
   h_bps_0p5->Write(); h_bps_0p5_inc->Write();
   h_bps_1->Write(); h_bps_1_inc->Write();
   h_CoD->Write();
   h_BCoD->Write();
   h_CoD_inc->Write();
   h_BCoD_inc->Write();
   for (int i = 0; i < 4; ++i) {
      h_Taustar_m175[i]->Write();
      h_Taustar_m250[i]->Write();
      h_Taustar_m375[i]->Write();
      h_Taustar_m500[i]->Write();
      h_Taustar_m625[i]->Write();
      h_Taustar_m750[i]->Write();
      h_Taustar_m1000[i]->Write();
      h_Taustar_m1250[i]->Write();
      h_Taustar_m1500[i]->Write();
      h_Taustar_m1750[i]->Write();
      h_Taustar_m2000[i]->Write();
      h_Taustar_m2500[i]->Write();
      h_Taustar_m3000[i]->Write();
      h_Taustar_m3500[i]->Write();
      h_Taustar_m4000[i]->Write();
      h_Taustar_m4500[i]->Write();
      h_Taustar_m5000[i]->Write();
   }
}

void runAllWrapper(const TString channel, const int mass, const bool blindA)
{std::cout << "runAllWrapper() " << channel << " " << mass << " " << blindA << std::endl;
   
   runAnalysis r;
   r.channel = channel;
   r.mass = mass;
   r.blindA = blindA;
   r.runAll();
}

