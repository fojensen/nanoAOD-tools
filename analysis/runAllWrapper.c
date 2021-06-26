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
      void makeMCSum();
      void bkgFraction();
      void fillKappa(const int nProng);
      void saveHists();

      bool doPredDM;

      void makePrediction_ABCD();
//      void makePrediction_dm();

      TString channel;
      TString var;
      int mass;
      bool blindA;
      TFile *fout;
      TH1D *h;
      
      TH1D *h8_truetautau[8], *h8_realtau[8], *h8_lfaketau[8];
      TH1D *h8_mcsum[8];
      //TH1D *h8_jetfaketau[8];
      TH1D *h8_data[8];
      TH1D *h8_Taustar_m175[8],  *h8_Taustar_m250[8], *h8_Taustar_m375[8], *h8_Taustar_m500[8], *h8_Taustar_m625[8], *h8_Taustar_m750[8];
      TH1D *h8_Taustar_m1000[8], *h8_Taustar_m1250[8], *h8_Taustar_m1500[8], *h8_Taustar_m1750[8];
      TH1D *h8_Taustar_m2000[8], *h8_Taustar_m2500[8];
      TH1D *h8_Taustar_m3000[8], *h8_Taustar_m3500[8];
      TH1D *h8_Taustar_m4000[8], *h8_Taustar_m4500[8];
      TH1D *h8_Taustar_m5000[8];
      TH1D *h8_ABCD[8];

      void sum8Hists();
      TH1D *h_truetautau[4], *h_realtau[4], *h_lfaketau[4];
      TH1D *h_mcsum[4];
      //TH1D *h_jetfaketau[4];
      TH1D *h_data[4];
      TH1D *h_Taustar_m175[4],  *h_Taustar_m250[4],  *h_Taustar_m375[4],  *h_Taustar_m500[4], *h_Taustar_m625[4], *h_Taustar_m750[4];
      TH1D *h_Taustar_m1000[4], *h_Taustar_m1250[4], *h_Taustar_m1500[4], *h_Taustar_m1750[4];
      TH1D *h_Taustar_m2000[4], *h_Taustar_m2500[4];
      TH1D *h_Taustar_m3000[4], *h_Taustar_m3500[4];
      TH1D *h_Taustar_m4000[4], *h_Taustar_m4500[4];
      TH1D *h_Taustar_m5000[4];
      TH1D *h_ABCD[4];

      TCut cut_1p, cut_3p;
      TH1D * h_1p, *h_3p;

      TH1D *h_kappa, *h_kappa_inc;
      TH1D *h_kappa_1p, *h_kappa_1p_inc;
      TH1D *h_kappa_3p, *h_kappa_3p_inc;

      /*TH1D *h_bps_0p01, *h_bps_0p01_inc;
      TH1D *h_bps_0p1, *h_bps_0p1_inc;
      TH1D *h_bps_0p5, *h_bps_0p5_inc;
      TH1D *h_bps_1, *h_bps_1_inc;*/

      TH1D *h_CoD,    *h_CoD_inc;
      TH1D *h_CoD_1p, *h_CoD_1p_inc;
      TH1D *h_CoD_3p, *h_CoD_3p_inc;
      TH1D *h_AoB,    *h_AoB_inc;
      TH1D *h_AoB_1p, *h_AoB_1p_inc;
      TH1D *h_AoB_3p, *h_AoB_3p_inc;
      TH1D *h_BCoD,    *h_BCoD_inc;
      TH1D *h_BCoD_1p, *h_BCoD_1p_inc;
      TH1D *h_BCoD_3p, *h_BCoD_3p_inc;
//      TH1D *h_BCoD_dm, *h_BCoD_dm_inc;
      const int nsig = 17;
      TString sigtags[17];
      const int nmc = 12;
      TString mctags[12];
};

void plotRegions4(/*const TString fname, */const TString channel, const int nProng, const bool blindA, const int mass, const bool doPredDM)
{std::cout << "plotRegions4() " << channel << blindA << std::endl;

   char fname[30];
   //sprintf(fname, "%s_m%d_unblind.root", channel.Data(), mass);
   sprintf(fname, "%s_m%d_blind.root", channel.Data(), mass);
   TFile * f = TFile::Open(fname);

   TH1D *h_lfaketau[4], *h_truetautau[4], *h_realtau[4];
   //TH1D * h_jetfaketau[4];
   TH1D *h_Taustar1[4];
   TH1D *h_Taustar2[4];
   TH1D *h_data[4];
   THStack *s[4];

   TString title;
   if (channel=="Muon") title="#mu + #tau_{h}";
   if (channel=="Electron") title="e + #tau_{h}";
   if (channel=="Tau") title="#tau_{h} + #tau_{h}";
   if (channel=="MuonEG") title="e + #mu";

   TString labels[4];
   if (nProng==0) {
      labels[0] = "A"; labels[1] = "B"; labels[2] = "C"; labels[3] = "D";
   } else if (nProng==1) {
      labels[0] = "A1"; labels[1] = "B1"; labels[2] = "C1"; labels[3] = "D1";
   } else if (nProng==3) {
      labels[0] = "A3"; labels[1] = "B3"; labels[2] = "C3"; labels[3] = "D3";
   } else {
      return;
   }

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

      char hname1[100];
      sprintf(hname1, "h_Taustar_m250_%s", labels[i].Data());
      h_Taustar1[i] = (TH1D*)f->Get(hname1);
      h_Taustar1[i]->SetLineColor(94);
      h_Taustar1[i]->SetLineWidth(2);

      char hname2[100];
      sprintf(hname2, "h_Taustar_m1000_%s", labels[i].Data());
      h_Taustar2[i] = (TH1D*)f->Get(hname2);
      h_Taustar2[i]->SetLineColor(95);
      h_Taustar2[i]->SetLineWidth(2);

      h_data[i] = (TH1D*)f->Get("h_data_"+labels[i]);
      h_data[i]->SetMarkerStyle(20);
      max = TMath::Max(max, h_data[i]->GetMaximum());

      char title[100];
      sprintf(title, "%s;%s;%s", h_lfaketau[i]->GetTitle(), h_lfaketau[i]->GetXaxis()->GetTitle(), h_lfaketau[i]->GetYaxis()->GetTitle());
      s[i]->SetTitle(title);
   }

   TH1D *h_AoB, *h_AoB_inc;
   TH1D *h_CoD, *h_CoD_inc;
   TH1D *h_BCoD, *h_BCoD_inc;
   TH1D *h_bkgsum, *h_bkgsum_inc;
   TH1D *h_kappa, *h_kappa_inc;
   if (nProng==0) {
      h_CoD = (TH1D*)f->Get("h_CoD");
      h_CoD_inc = (TH1D*)f->Get("h_CoD_inc");
      h_BCoD = (TH1D*)f->Get("h_BCoD");
      h_BCoD_inc = (TH1D*)f->Get("h_BCoD_inc");
      h_bkgsum = (TH1D*)((TH1D*)f->Get("h_mcsum_A"))->Clone("h_bkgsum");
      if (!blindA) {
         h_AoB = (TH1D*)f->Get("h_AoB");
         h_AoB_inc = (TH1D*)f->Get("h_AoB_inc");
         h_kappa = (TH1D*)f->Get("h_kappa");
      }
   } else if (nProng==1) {
      h_CoD = (TH1D*)f->Get("h_CoD_1p");
      h_CoD_inc = (TH1D*)f->Get("h_CoD_1p_inc");
      h_BCoD = (TH1D*)f->Get("h_BCoD_1p");
      h_BCoD_inc = (TH1D*)f->Get("h_BCoD_1p_inc");
      h_bkgsum = (TH1D*)((TH1D*)f->Get("h_mcsum_A1"))->Clone("h_bkgsum");
      if (!blindA) {
         h_AoB = (TH1D*)f->Get("h_AoB_1p");
         h_AoB_inc = (TH1D*)f->Get("h_AoB_1p_inc");
         h_kappa = (TH1D*)f->Get("h_kappa_1p");
         h_kappa_inc = (TH1D*)f->Get("h_kappa_1p_inc");
      }
   } else if (nProng==3) {
      h_CoD = (TH1D*)f->Get("h_CoD_3p");
      h_CoD_inc = (TH1D*)f->Get("h_CoD_3p_inc");
      h_BCoD = (TH1D*)f->Get("h_BCoD_3p");
      h_BCoD_inc = (TH1D*)f->Get("h_BCoD_3p_inc");
      h_bkgsum = (TH1D*)((TH1D*)f->Get("h_mcsum_A3"))->Clone("h_bkgsum");
      if (!blindA) {
         h_AoB = (TH1D*)f->Get("h_AoB_3p");
         h_AoB_inc = (TH1D*)f->Get("h_AoB_3p_inc");
         h_kappa = (TH1D*)f->Get("h_kappa_3p");
         h_kappa_inc = (TH1D*)f->Get("h_kappa_3p_inc");
      }  
   } else {
      return;
   }
   h_bkgsum_inc = (TH1D*)h_bkgsum->Clone("h_bkgsum_inc");
   h_bkgsum->Add(h_BCoD);
   h_bkgsum_inc->Add(h_BCoD_inc);
 
   h_BCoD->SetFillColor(207);
   s[0]->Add(h_BCoD);

   const double ymax = pow(10, ceil(log10(max))+1);
   double ymin = 0.01;
   if (max>=10.) ymin = 0.1;
   if (max>=100.) ymin = 1.;
   if (max>=1000.) ymin = 10.;
   if (max>=10000.) ymin = 100.;

   TLegend * lA = new TLegend(0.25, 0.75, 0.875, 0.875);
   lA->SetNColumns(2);
   lA->SetBorderSize(0);
   //lA->AddEntry(h_jetfaketau[0], "jet #rightarrow #tau_{h}", "F");
   lA->AddEntry(h_lfaketau[0], "e,#mu,#tau_{e},#tau_{#mu} #rightarrow #tau_{h}", "F");
   lA->AddEntry(h_realtau[0], "#tau_{h} #rightarrow #tau_{h}; !#tau#tau", "F");
   lA->AddEntry(h_truetautau[0], "true #tau#tau", "F");
   lA->AddEntry(h_Taustar1[0], "#tau* 250", "L");
   lA->AddEntry(h_Taustar2[0], "#tau* 1000", "L");

   TLegend *lBCD = (TLegend*)lA->Clone();
   lBCD->AddEntry(h_data[1], "data", "P");   

   lA->AddEntry(h_BCoD, "BC/D", "F");
   if (!blindA) lA->AddEntry(h_data[0], "data", "P");

   char canvasname[50];
   sprintf(canvasname, "canvas_plotRegions_%d", nProng);
   TCanvas * canvas = new TCanvas(canvasname, canvasname, 1200, 800);
   canvas->Divide(3, 2);

   TPad * p2 = (TPad*)canvas->cd(2);
   s[0]->Draw("HIST");
   h_Taustar1[0]->Draw("HIST, E, SAME");
   h_Taustar2[0]->Draw("HIST, E, SAME");
   if (!blindA) h_data[0]->Draw("P, SAME");
   p2->SetLogy();
   lA->Draw();
   s[0]->SetMaximum(ymax); s[0]->SetMinimum(ymin);

   TPad * p3 = (TPad*)canvas->cd(3);
   s[1]->Draw("HIST");
   h_Taustar1[1]->Draw("HIST, E, SAME");
   h_Taustar2[1]->Draw("HIST, E, SAME");
   h_data[1]->Draw("P, SAME");
   p3->SetLogy();
   lBCD->Draw();
   s[1]->SetMaximum(ymax); s[1]->SetMinimum(ymin);

   TPad * p5 = (TPad*)canvas->cd(5);
   s[2]->Draw("HIST");
   h_Taustar1[2]->Draw("HIST, E, SAME");
   h_Taustar2[2]->Draw("HIST, E, SAME");
   h_data[2]->Draw("P, SAME");
   p5->SetLogy();
   lBCD->Draw();
   s[2]->SetMaximum(ymax); s[2]->SetMinimum(ymin);

   TPad * p6 = (TPad*)canvas->cd(6);
   s[3]->Draw("HIST");
   h_Taustar1[3]->Draw("HIST, E, SAME");
   h_Taustar2[3]->Draw("HIST, E, SAME");
   h_data[3]->Draw("P, SAME");
   p6->SetLogy();
   lBCD->Draw();
   s[3]->SetMaximum(ymax); s[3]->SetMinimum(ymin);

   TPad * p4 = (TPad*)canvas->cd(4);
   h_CoD->Draw("PE");
   h_CoD->SetMarkerStyle(20);
   h_CoD->SetMarkerColor(3);
   h_CoD->SetLineColor(3);
   h_CoD->SetStats(0);
   h_CoD->SetMinimum(0.);
   h_CoD->SetMaximum(1.5);
   //p4->SetLogy();

   TLine * lup = new TLine(h_CoD_inc->GetBinLowEdge(1), h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1), h_CoD_inc->GetBinLowEdge(h_CoD_inc->GetNbinsX()+1), h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1));   
   lup->SetLineStyle(2);
   lup->SetLineColor(3);
   lup->Draw();
   TLine * ldown = new TLine(h_CoD_inc->GetBinLowEdge(1), h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1), h_CoD_inc->GetBinLowEdge(h_CoD_inc->GetNbinsX()+1), h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1));  
   ldown->SetLineStyle(2);
   ldown->SetLineColor(3);
   ldown->Draw();

   if (!blindA) {
      h_AoB->Draw("PE, SAME");
      h_AoB->SetMarkerStyle(20);
      h_AoB->SetMarkerColor(2);
      h_AoB->SetLineColor(2);

      TLine * lupAB = new TLine(h_AoB_inc->GetBinLowEdge(1), h_AoB_inc->GetBinContent(1)+h_AoB_inc->GetBinError(1), h_AoB_inc->GetBinLowEdge(h_AoB_inc->GetNbinsX()+1), h_AoB_inc->GetBinContent(1)+h_AoB_inc->GetBinError(1));
      lupAB->SetLineStyle(2);
      lupAB->SetLineColor(2);
      lupAB->Draw();
      TLine * ldownAB = new TLine(h_AoB_inc->GetBinLowEdge(1), h_AoB_inc->GetBinContent(1)-h_AoB_inc->GetBinError(1), h_AoB_inc->GetBinLowEdge(h_AoB_inc->GetNbinsX()+1), h_AoB_inc->GetBinContent(1)-h_AoB_inc->GetBinError(1));  
      ldownAB->SetLineStyle(2);
      ldownAB->SetLineColor(2);
      ldownAB->Draw();

      h_kappa->SetMarkerStyle(20);
      h_kappa->SetMarkerColor(4);
      h_kappa->SetLineColor(4);
      h_kappa->Draw("PE, SAME");
      h_kappa->SetMinimum(0.);
      h_kappa->SetMaximum(2.);
      h_kappa->SetStats(0);
      h_kappa->GetYaxis()->SetTitle("#kappa");

      TLine * l_kappaup = new TLine(h_kappa_inc->GetBinLowEdge(1), h_kappa_inc->GetBinContent(1)+h_kappa_inc->GetBinError(1), h_kappa_inc->GetBinLowEdge(h_kappa_inc->GetNbinsX()+1),  h_kappa_inc->GetBinContent(1)+h_kappa_inc->GetBinError(1));
      l_kappaup->SetLineStyle(2);
      l_kappaup->SetLineColor(4); 
      l_kappaup->Draw();   
      TLine * l_kappadown = new TLine(h_kappa_inc->GetBinLowEdge(1), h_kappa_inc->GetBinContent(1)-h_kappa_inc->GetBinError(1), h_kappa_inc->GetBinLowEdge(h_kappa_inc->GetNbinsX()+1),  h_kappa_inc->GetBinContent(1)-h_kappa_inc->GetBinError(1));
      l_kappadown->SetLineStyle(2);
      l_kappadown->SetLineColor(4);      
      l_kappadown->Draw();

      TLine * line2 = new TLine(h_kappa->GetBinLowEdge(1), 1., h_kappa->GetBinLowEdge(h_kappa->GetNbinsX()+1), 1.);
      line2->SetLineStyle(2);
      line2->Draw();

      TLegend * l = new TLegend(0.25, 0.8, 0.875, 0.875);
      l->SetNColumns(2);
      l->SetBorderSize(0);
      l->AddEntry(h_AoB, "A / B", "P");
      l->AddEntry(h_CoD, "C / D", "P");
      l->AddEntry(h_kappa, "#kappa", "P");
      l->Draw();

   }

   if (!blindA) {
      canvas->cd(1);

      TH1D * r = (TH1D*)h_data[0]->Clone("r");
      r->Divide(h_bkgsum);
      r->GetYaxis()->SetTitle("observed / predicted");
      r->SetMarkerStyle(20);
      r->SetMarkerColor(6);
      r->SetLineColor(6);
      r->Draw("PE");
      r->SetStats(0);
      r->SetMinimum(0.);
      r->SetMaximum(2.);

      TH1D * r_inc = (TH1D*)h_data[0]->Clone("r_inc");
      r_inc->Divide(h_bkgsum_inc);
      r_inc->SetMarkerStyle(20);
      r_inc->SetMarkerColor(7);
      r_inc->SetLineColor(7);
      r_inc->Draw("PE, SAME");

      TLegend * l2 = new TLegend(0.25, 0.75, 0.875, 0.875);
      l2->SetBorderSize(0);
      l2->SetNColumns(2);
      l2->AddEntry(r_inc, "inclusive C/D", "P");
      l2->AddEntry(r, "binned C/D ", "P");
      l2->Draw();

      TLine * line = new TLine(r->GetBinLowEdge(1), 1., r->GetBinLowEdge(r->GetNbinsX()+1), 1.);
      line->SetLineStyle(2);
      line->Draw();

   }
   char outfile[50];
   //if (nProng==0) {
   //   sprintf(outfile, "./plots/%s_m%d_np0.lt100.pdf", channel.Data(), mass);
   //} else if (nProng==1) {
   //   sprintf(outfile, "./plots/%s_m%d_np1.lt100.pdf", channel.Data(), mass);
   //} else if (nProng==3) {
   //   sprintf(outfile, "./plots/%s_m%d_np3.lt100.pdf", channel.Data(), mass);
   //} else {
   //   return;
   //}
   //sprintf(outfile, "%s_m%d_unblind.pdf", channel.Data(), mass);
   sprintf(outfile, "%s_m%d_blind.pdf", channel.Data(), mass);
   canvas->SaveAs(outfile);
   std::cout << "end plotRegions4() " << channel << blindA << std::endl;
}

/*void plotRegions8(const TString channel, const bool blindA, const int mass, const bool doPredDM)
{std::cout << "plotRegions8() " << channel << blindA << std::endl;

   char fname[100];
   sprintf(fname, "%s_m%d.root", channel.Data(), mass);
   TFile * f = TFile::Open(fname);

   TH1D *h_lfaketau[8], *h_truetautau[8], *h_realtau[8];
   //TH1D * h_jetfaketau[8];
   TH1D *h_Taustar1[8];
   TH1D *h_Taustar2[8];
   TH1D *h_data[8];
   THStack *s[8];

   TString title;
   if (channel=="Muon") title="#mu + #tau_{h}";
   if (channel=="Electron") title="e + #tau_{h}";
   if (channel=="Tau") title="#tau_{h} + #tau_{h}";
   if (channel=="MuonEG") title="e + #mu";

   TH1D * h_BCoD_1p = (TH1D*)f->Get("h_BCoD_1p");
   TH1D * h_BCoD_3p = (TH1D*)f->Get("h_BCoD_3p");

   const TString labels[8] = {"A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"};
   double max = 0.;
   for (int i = 0; i < 8; ++i) {
      s[i] = new THStack("s_"+labels[i], "");

      //h_jetfaketau[i] = (TH1D*)f->Get("h_jetfaketau_"+labels[i]);
      //h_jetfaketau[i]->SetFillColor(222);
      //s[i]->Add(h_jetfaketau[i]);

      h_lfaketau[i] = (TH1D*)f->Get("h8_lfaketau_"+labels[i]);
      h_lfaketau[i]->SetFillColor(222);
      s[i]->Add(h_lfaketau[i]);

      h_realtau[i] = (TH1D*)f->Get("h8_realtau_"+labels[i]);
      h_realtau[i]->SetFillColor(226);
      s[i]->Add(h_realtau[i]);

      h_truetautau[i] = (TH1D*)f->Get("h8_truetautau_"+labels[i]);
      h_truetautau[i]->SetFillColor(209);
      s[i]->Add(h_truetautau[i]);

      char hname1[100];
      sprintf(hname1, "h8_Taustar_m175_%s", labels[i].Data());
      h_Taustar1[i] = (TH1D*)f->Get(hname1);
      h_Taustar1[i]->SetLineColor(94);
      h_Taustar1[i]->SetLineWidth(2);

      char hname2[100];
      sprintf(hname2, "h8_Taustar_m1000_%s", labels[i].Data());
      h_Taustar2[i] = (TH1D*)f->Get(hname2);
      h_Taustar2[i]->SetLineColor(95);
      h_Taustar2[i]->SetLineWidth(2);

      h_data[i] = (TH1D*)f->Get("h8_data_"+labels[i]);
      h_data[i]->SetMarkerStyle(20);
      max = TMath::Max(max, h_data[i]->GetMaximum());

      char title[100];
      sprintf(title, "%s;%s;%s", h_lfaketau[i]->GetTitle(), h_lfaketau[i]->GetXaxis()->GetTitle(), h_lfaketau[i]->GetYaxis()->GetTitle());
      s[i]->SetTitle(title);
      std::cout << title << std::endl;
   }

   h_BCoD_1p->SetFillColor(207);
   s[0]->Add(h_BCoD_1p);
   h_BCoD_3p->SetFillColor(207);
   s[1]->Add(h_BCoD_3p);

   const double ymax = pow(10, ceil(log10(max))+1);
   double ymin = 0.01;
   if (max>=10.) ymin = 0.1;
   if (max>=100.) ymin = 1.;
   if (max>=1000.) ymin = 10.;
   if (max>=10000.) ymin = 100.;

   TLegend * lA = new TLegend(0.25, 0.75, 0.875, 0.875);
   lA->SetNColumns(2);
   lA->SetBorderSize(0);
   //lA->AddEntry(h_jetfaketau[0], "jet #rightarrow #tau_{h}", "F");
   lA->AddEntry(h_lfaketau[0], "e,#mu,#tau_{e},#tau_{#mu} #rightarrow #tau_{h}", "F");
   lA->AddEntry(h_realtau[0], "#tau_{h} #rightarrow #tau_{h}; !#tau#tau", "F");
   lA->AddEntry(h_truetautau[0], "true #tau#tau", "F");
   lA->AddEntry(h_Taustar1[0], "#tau* 175", "L");
   lA->AddEntry(h_Taustar2[0], "#tau* 1000", "L");

   TLegend *lBCD = (TLegend*)lA->Clone();
   
   lA->AddEntry(h_BCoD_1p, "BC/D", "F");
   if (!blindA) lA->AddEntry(h_data[0], "data", "P");
   lBCD->AddEntry(h_data[1], "data", "P");

   TCanvas * canvas = new TCanvas("canvas_plotRegions8", "plotRegions8", 1600, 800);
   canvas->Divide(4, 2);

   const int cn[8] = {1, 5, 2, 6, 3, 7, 4, 8};
   for (int i = 0; i < 8; ++i) {
      TPad * p2 = (TPad*)canvas->cd(cn[i]);
      s[i]->Draw("HIST");
      h_Taustar1[i]->Draw("HIST, E, SAME");
      h_Taustar2[i]->Draw("HIST, E, SAME");
      const bool drawdata = ! ( blindA && (i==0||i==1) );
      if (drawdata) h_data[i]->Draw("P, SAME");
      p2->SetLogy();
      if (i==0||i==1) {
         lA->Draw();
      } else {
         lBCD->Draw();
      }
      s[i]->SetMaximum(ymax); s[i]->SetMinimum(ymin);
   } 

   char outfile[50];
   if (doPredDM) {
      sprintf(outfile, "%s_m%d_8_predDM.pdf", channel.Data(), mass);
    } else {
      sprintf(outfile, "%s_m%d_8.pdf", channel.Data(), mass);
   }
   canvas->SaveAs(outfile);
   std::cout << "end plotRegions8() " << channel << blindA << std::endl;
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
   std::cout << "end makeVar() " <<  mass << " " << channel << std::endl;  
   return TString(outstring);
}

void runAnalysis::runAll()
{std::cout << "runAll()" << std::endl;

//   if (mass==0) {
       //if (channel=="Electron") var = "(Tau_decayMode[ElTau_TauIdx]==0||Tau_decayMode[ElTau_TauIdx]==1||Tau_decayMode[ElTau_TauIdx]==2) ? 1 : (Tau_decayMode[ElTau_TauIdx]==10||Tau_decayMode[ElTau_TauIdx]==11||Tau_decayMode[ElTau_TauIdx]==12) ? 3 : 0";
       //if (channel=="Muon")     var = "(Tau_decayMode[MuTau_TauIdx]==0||Tau_decayMode[MuTau_TauIdx]==1||Tau_decayMode[MuTau_TauIdx]==2) ? 1 : (Tau_decayMode[MuTau_TauIdx]==10||Tau_decayMode[MuTau_TauIdx]==11||Tau_decayMode[MuTau_TauIdx]==12) ? 3 : 0";
       //if (channel=="Tau")      var = "(Tau_decayMode[TauTau_Tau0Idx]==0||Tau_decayMode[TauTau_Tau0Idx]==1||Tau_decayMode[TauTau_Tau0Idx]==2) ? 1 : (Tau_decayMode[TauTau_Tau0Idx]==10||Tau_decayMode[TauTau_Tau0Idx]==11||Tau_decayMode[TauTau_Tau0Idx]==12) ? 3 : 0";
       if (channel=="Electron") var = "ElTau_nProng";
       if (channel=="Muon")     var = "MuTau_nProng";
        if (channel=="Tau")      var = "TauTau_Tau1nProng";
       //if (channel=="MuonEG")   var = "1.";
       h =  new TH1D("h", ";# of prongs;events / bin", 4, -0.5, 3.5);
//   } else {
      //var = makeVar(mass, channel);
      //h = new TH1D("h", ";bin;events / bin", 5, -0.5, 4.5);
      //if (channel=="Electron") var = "ElTau_Mass";
      //if (channel=="Muon")     var = "MuTau_Mass";
      //if (channel=="Tau")      var = "TauTau_Mass";
      //if (channel=="MuonEG")   var = "ElMu_Mass";
      //h = new TH1D("h", ";visible mass [GeV];events / 10 GeV", 20, 0., 200.);
      //h = new TH1D("h", ";photon p_{T} [GeV];events / 10 GeV", 10, 0., 100.);
      //var = "Photon_pt[MuTau_PhotonIdx]";
  // }
   
   //var = "1.";
   //h = new TH1D("h", ";the unit bin;events", 1, 0.5, 1.5);

   h->Sumw2();

   if (channel=="Electron") h->SetTitle("e + #tau_{h}");
   if (channel=="Muon") h->SetTitle("#mu + #tau_{h}");
   if (channel=="Tau") h->SetTitle("#tau_{h} + #tau_{h}");
   if (channel=="MuonEG") h->SetTitle("e + #mu");

   mctags[0] = "WW";
   mctags[1] = "WZ";
   mctags[2] = "ZZ";
   mctags[3] = "TTTo2L2Nu_bVeto"; //mctags[3] = "TTTo2L2Nu";
   mctags[4] = "TTToSemiLeptonic_bVeto"; //mctags[4] = "TTToSemiLeptonic";
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

   char fname[25];
   //if (mass==0 && blindA) {
   //    sprintf(fname, "%s_dm.root", channel.Data());
   //} else if (mass==0) {
   //   sprintf(fname, "%s_dm_cr.root", channel.Data());
   //} else {
   //sprintf(fname, "%s_m%d_lt100.root", channel.Data(), mass);
   //sprintf(fname, "%s_m%d_unblind.root", channel.Data(), mass);
   sprintf(fname, "%s_m%d_blind.root", channel.Data(), mass);
   //}
   fout = new TFile(fname, "RECREATE"); 

   dataHistInit();
   mcHistInit();
   sigHistInit();
   fillSigHists(2018); fillMCHists(2018); fillDataHists(2018);
   fillSigHists(2017); fillMCHists(2017); fillDataHists(2017);
   fillSigHists(2016); fillMCHists(2016); fillDataHists(2016);
   //fillMCHists(2015); fillSigHists(2015);
   dataHistOverflow();
   sigHistOverflow();
   mcHistOverflow();
   makeMCSum(); //h8_mcsum
   sum8Hists(); //8->4
   makeABCDHists();
   makePrediction_ABCD();
   //if (doPredDM) makePrediction_dm();
   if (!blindA) {
      fillKappa(0);
      fillKappa(1);
      fillKappa(3);
   }
   //sumBkgHists();
   bkgFraction();
   saveHists();
   fout->Close();
   //plotRegions4(channel, 0, blindA, mass, doPredDM);
   //plotRegions4(channel, 1, blindA, mass, doPredDM);
   //plotRegions4(channel, 3, blindA, mass, doPredDM);
   //plotRegions8(channel, blindA, mass, doPredDM);
   std::cout << "end runAll()" << std::endl;
}

void runAnalysis::dataHistInit()
{std::cout << "dataHistInit()" << std::endl;
   
   const TString labels[8] = {"A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"};
   for (int i = 0; i < 8; ++i) {
      h8_data[i] = (TH1D*)h->Clone("h_data_"+labels[i]);
      char titles[100];
      sprintf(titles, "%s: %s", h->GetTitle(), labels[i].Data());
      h8_data[i]->SetTitle(titles);
   }
   std::cout << "end dataHistInit()" << std::endl;
}

void runAnalysis::mcHistInit()
{std::cout << "mcHistInit()" << std::endl; 
   const TString labels[8] = {"A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"};
   for (int i = 0; i < 8; ++i) {
      //h_jetfaketau[i] = (TH1D*)h->Clone("h8_jetfaketau_"+labels[i]);
      h8_lfaketau[i] = (TH1D*)h->Clone("h_lfaketau_"+labels[i]);
      h8_realtau[i] = (TH1D*)h->Clone("h_realtau_"+labels[i]);
      h8_truetautau[i] = (TH1D*)h->Clone("h_truetautau_"+labels[i]);
      char titles[100];
      sprintf(titles, "%s: %s", h->GetTitle(), labels[i].Data());
      //h8_jetfaketau[i]->SetTitle(titles);
      h8_lfaketau[i]->SetTitle(titles);
      h8_realtau[i]->SetTitle(titles);
      h8_truetautau[i]->SetTitle(titles);
   }
   std::cout << "end mcHistInit()" << std::endl;
}

void runAnalysis::sigHistInit()
{std::cout << "sigHistInit()" << std::endl;
   const TString labels[8] = {"A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"};
   for (int i = 0; i < 8; ++i) {
      h8_Taustar_m175[i] = (TH1D*)h->Clone("h_Taustar_m175_"+labels[i]);
      h8_Taustar_m250[i] = (TH1D*)h->Clone("h_Taustar_m250_"+labels[i]);
      h8_Taustar_m375[i] = (TH1D*)h->Clone("h_Taustar_m375_"+labels[i]);
      h8_Taustar_m500[i] = (TH1D*)h->Clone("h_Taustar_m500_"+labels[i]);
      h8_Taustar_m625[i] = (TH1D*)h->Clone("h_Taustar_m625_"+labels[i]);
      h8_Taustar_m750[i] = (TH1D*)h->Clone("h_Taustar_m750_"+labels[i]);
      h8_Taustar_m1000[i] = (TH1D*)h->Clone("h_Taustar_m1000_"+labels[i]);
      h8_Taustar_m1250[i] = (TH1D*)h->Clone("h_Taustar_m1250_"+labels[i]);
      h8_Taustar_m1500[i] = (TH1D*)h->Clone("h_Taustar_m1500_"+labels[i]);
      h8_Taustar_m1750[i] = (TH1D*)h->Clone("h_Taustar_m1750_"+labels[i]);
      h8_Taustar_m2000[i] = (TH1D*)h->Clone("h_Taustar_m2000_"+labels[i]);
      h8_Taustar_m2500[i] = (TH1D*)h->Clone("h_Taustar_m2500_"+labels[i]);
      h8_Taustar_m3000[i] = (TH1D*)h->Clone("h_Taustar_m3000_"+labels[i]);
      h8_Taustar_m3500[i] = (TH1D*)h->Clone("h_Taustar_m3500_"+labels[i]);
      h8_Taustar_m4000[i] = (TH1D*)h->Clone("h_Taustar_m4000_"+labels[i]);
      h8_Taustar_m4500[i] = (TH1D*)h->Clone("h_Taustar_m4500_"+labels[i]);
      h8_Taustar_m5000[i] = (TH1D*)h->Clone("h_Taustar_m5000_"+labels[i]);
   }
   std::cout << "end sigHistInit()" << std::endl;
}

void runAnalysis::loadCuts(const int year, TCut cuts[8])
{std::cout << "loadCuts() " << year << std::endl;

   TCut baseline, regionA, regionB, regionC, regionD;
   baseline = regionA = regionB = regionC = regionD = "1>0";
   if (channel=="Electron") {
      //baseline = baseline && TCut("ElTau_HavePair>0 && (ElTau_HaveTriplet==0||(ElTau_HaveTriplet>0&&Photon_pt[ElTau_PhotonIdx]<95.))");
      //baseline = baseline && TCut("ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]>=50. && Photon_pt[ElTau_PhotonIdx]<95.");
      baseline = baseline && TCut("ElTau_HaveTriplet>0");
      char ptcut[100];
      //sprintf(ptcut, "Photon_pt[ElTau_PhotonIdx]>=%f && Photon_pt[ElTau_PhotonIdx]<100.", double(mass));
      sprintf(ptcut, "Photon_pt[ElTau_PhotonIdx]>=%f", double(mass));
      baseline = baseline && TCut(ptcut);
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
      //cut_1p = "Tau_decayMode[ElTau_TauIdx]==0||Tau_decayMode[ElTau_TauIdx]==1||Tau_decayMode[ElTau_TauIdx]==2";
      //cut_3p = "Tau_decayMode[ElTau_TauIdx]==10||Tau_decayMode[ElTau_TauIdx]==11||Tau_decayMode[ElTau_TauIdx]==12";
      cut_1p = "ElTau_nProng==1";
      cut_3p = "ElTau_nProng==3";
   }
   if (channel=="Muon") {
      //baseline = baseline && TCut("MuTau_HavePair>0 && (MuTau_HaveTriplet==0||(MuTau_HaveTriplet>0&&Photon_pt[MuTau_PhotonIdx]<10.))");
      //baseline = baseline && TCut("MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=70. && Photon_pt[MuTau_PhotonIdx]<95.");
      //baseline = baseline && TCut("MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=10. && Photon_pt[MuTau_PhotonIdx]<50.");
      baseline = baseline && TCut("MuTau_HaveTriplet>0");
      char ptcut[100];
      //sprintf(ptcut, "Photon_pt[MuTau_PhotonIdx]>=%f && Photon_pt[MuTau_PhotonIdx]<100.", double(mass));
      sprintf(ptcut, "Photon_pt[MuTau_PhotonIdx]>=%f", double(mass));
      baseline = baseline && TCut(ptcut);
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
      //cut_1p = "Tau_decayMode[MuTau_TauIdx]==0||Tau_decayMode[MuTau_TauIdx]==1||Tau_decayMode[MuTau_TauIdx]==2";
      //cut_3p = "Tau_decayMode[MuTau_TauIdx]==10||Tau_decayMode[MuTau_TauIdx]==11||Tau_decayMode[MuTau_TauIdx]==12";
      cut_1p = "MuTau_nProng==1";
      cut_3p = "MuTau_nProng==3";
   }
   if (channel=="Tau") {
      //baseline = baseline && TCut("TauTau_HavePair>0 && (TauTau_HaveTriplet==0||(TauTau_HaveTriplet>0&&Photon_pt[TauTau_PhotonIdx]<70.))");
      //baseline = baseline && TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=75.");
      //baseline = baseline && TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=25. && Photon_pt[TauTau_PhotonIdx]<70.");
      baseline = baseline && TCut("TauTau_HaveTriplet>0");
      char ptcut[100];
      //sprintf(ptcut, "Photon_pt[TauTau_PhotonIdx]>=%f && Photon_pt[TauTau_PhotonIdx]<75.", double(mass));
      sprintf(ptcut, "Photon_pt[TauTau_PhotonIdx]>=%f", double(mass));
      baseline = baseline && TCut(ptcut);
      //?baseline = baseline && TCut("JetProducer_nBJetT==0");
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
      //cut_1p = "Tau_decayMode[TauTau_Tau0Idx]==0||Tau_decayMode[TauTau_Tau0Idx]==1||Tau_decayMode[TauTau_Tau0Idx]==2";
      //cut_3p = "Tau_decayMode[TauTau_Tau0Idx]==10||Tau_decayMode[TauTau_Tau0Idx]==11||Tau_decayMode[TauTau_Tau0Idx]==12";
      cut_1p = "TauTau_Tau1nProng==1";
      cut_3p = "TauTau_Tau1nProng==3";
   }
   if (channel=="MuonEG") {
      //baseline = baseline && TCut("ElMu_HavePair>0 && (ElMu_HaveTriplet==0||(ElMu_HaveTriplet>0&&Photon_pt[ElMu_PhotonIdx]<100.))");
      //baseline = baseline && TCut("ElMu_HaveTriplet>0 && Photon_pt[ElMu_PhotonIdx]>=100.");
      baseline = baseline && TCut("ElMu_HaveTriplet>0 && Photon_pt[ElMu_PhotonIdx]>=50. && Photon_pt[ElMu_PhotonIdx]<100.");
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
   cuts[0] = baseline && regionA && cut_1p;
   cuts[1] = baseline && regionA && cut_3p;
   cuts[2] = baseline && regionB && cut_1p;
   cuts[3] = baseline && regionB && cut_3p;
   cuts[4] = baseline && regionC && cut_1p;
   cuts[5] = baseline && regionC && cut_3p;
   cuts[6] = baseline && regionD && cut_1p;
   cuts[7] = baseline && regionD && cut_3p;

   std::cout << "end loadCuts() " << year << std::endl;
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

   TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_12052021";

   //TChain * c = new TChain("Events");
   TChain c("Events");
   for (int i = 0; i < nmc; ++i) {
      //if (i==3) continue; //skip TTTo2L2Nu
      //if (i==4) continue; //skip TTToSemileptonic
      char infile[1000];
      sprintf(infile, "%s/%s_%d.root", eostag.Data(), mctags[i].Data(), year);
      std::cout <<infile << std::endl;
      c.Add(infile);
   }

   const TString labels[8] = {"A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"};
   TCut cuts[8];
   loadCuts(year, cuts);
   for (int i = 0; i < 8; ++i) {
      std::cout << "filling region : " << labels[i] << std::endl;
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
      char hname2[25];
      sprintf(hname2, "+h_lfaketau_%s", labels[i].Data());
      ntot += c.Project(hname2, var, buffer2);
      // real tau
      char buffer3[3000];
      sprintf(buffer3, "%f * xsWeight * (%s)", lumi, TString(cuts[i] && cut_realtau).Data());
      char hname3[25];
      sprintf(hname3, "+h_realtau_%s", labels[i].Data());
      ntot += c.Project(hname3, var, buffer3);
      // true tautau
      char buffer4[3000];
      sprintf(buffer4, "%f * xsWeight * (%s)", lumi, TString(cuts[i] && cut_truetautau).Data());
      char hname4[25];
      sprintf(hname4, "+h_truetautau_%s", labels[i].Data());
      ntot += c.Project(hname4, var, buffer4);
      if (ntot!=n) {
         std::cout << "**** missing some entries! ****" << std::endl;
         std::cout << " entries in region: " << n << std::endl;
         std::cout << " entries in projections: " << ntot << std::endl;
      }
   }
   std::cout << "end fillMCHists() " << year << std::endl;
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

   const TString labels[8] = {"A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"};
   TCut cuts[8];
   loadCuts(year, cuts);

   const TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_12052021";
   for (int i = 0; i < nsig; ++i) {
      std::cout << "filling " << sigtags[i] << std::endl;
      char infile[100];
      sprintf(infile, "%s/%s_%d.root", eostag.Data(), sigtags[i].Data(), year);
      TFile * f = TFile::Open(infile);
      if (!f) continue;
      TTree * t = (TTree*)f->Get("Events");
      for (int j = 0; j < 8; ++j) {
         char buffer[3000];
         sprintf(buffer, "%f * xsWeight * (%s)", lumi, TString(cuts[j]).Data());
         fout->cd();
         char hname[25];
         sprintf(hname, "+h_%s_%s", sigtags[i].Data(), labels[j].Data());
         std::cout << " entries in projection: " << t->Project(hname, var, buffer) << std::endl;
      }
   }
   std::cout << "end fillSigHists(): " << year << std::endl;
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
   TCut cuts[8];
   loadCuts(year, cuts);

   const TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_12052021";
   for (auto i = letters.begin(); i != letters.end(); ++i) {
      char infile[100];
      if (channel=="MuonEG") {
         sprintf(infile, "%s/%s%s_%d.root", eostag.Data(), "ElMu", i->Data(), year);
      } else {
         sprintf(infile, "%s/%s%s_%d.root", eostag.Data(), channel.Data(), i->Data(), year);
      }
      const TString labels[8] = {"A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"};
      TFile * f = TFile::Open(infile);
      TTree * t = (TTree*)f->Get("Events");
      fout->cd();
      for (int j = 0; j < 8; ++j) {
         if ((j==0||j==1) && blindA) continue;
         std::cout << "filling region : " << labels[j] << std::endl;
         char histname[100];
         sprintf(histname, "+%s", h8_data[j]->GetName());
         std::cout << " entries in projection: " << t->Project(histname, var, cuts[j]) << std::endl;
      }
   }
   std::cout << "end fillDataHists(): " << year << std::endl;
}

void runAnalysis::dataHistOverflow()
{std::cout << "dataHistOverflow()" << std::endl;
   for (int i = 0; i < 8; ++i) {
      addOverflow(h8_data[i]);
   }
   std::cout << "end dataHistOverflow()" << std::endl;
}

void runAnalysis::mcHistOverflow()
{std::cout << "mcHistOverflow()" << std::endl;
   for (int i = 0; i < 8; ++i) {
      //addOverflow(h8_jetfaketau[i]);
      addOverflow(h8_lfaketau[i]);
      addOverflow(h8_realtau[i]);
      addOverflow(h8_truetautau[i]);
   }
   std::cout << "end mcHistOverflow()" << std::endl;
}

void runAnalysis::sigHistOverflow()
{std::cout << "sigHistOverflow()" << std::endl;
   for (int i = 0; i < 8; ++i) {
      addOverflow(h8_Taustar_m175[i]);
      addOverflow(h8_Taustar_m250[i]);
      addOverflow(h8_Taustar_m375[i]);
      addOverflow(h8_Taustar_m500[i]);
      addOverflow(h8_Taustar_m625[i]);
      addOverflow(h8_Taustar_m750[i]);
      addOverflow(h8_Taustar_m1000[i]);
      addOverflow(h8_Taustar_m1250[i]);
      addOverflow(h8_Taustar_m1500[i]);
      addOverflow(h8_Taustar_m1750[i]);
      addOverflow(h8_Taustar_m2000[i]);
      addOverflow(h8_Taustar_m2500[i]);
      addOverflow(h8_Taustar_m3000[i]);
      addOverflow(h8_Taustar_m3500[i]);
      addOverflow(h8_Taustar_m4000[i]);
      addOverflow(h8_Taustar_m4500[i]);
      addOverflow(h8_Taustar_m5000[i]);
   }
   std::cout << "end sigHistOverflow()" << std::endl;
}

void runAnalysis::sum8Hists()
{std::cout << "sum8Hists()" << std::endl;
   
   /*h_truetautau[0] = h8_truetautau[0]->Clone("h_truetautau_A");
   h_truetautau[0]->Add(h8_truetautau[1]);
   h_truetautau[1] = h8_truetautau[2]->Clone("h_truetautau_B");
   h_truetautau[1]->Add(h8_truetautau[3]);
   h_truetautau[2] = h8_truetautau[4]->Clone("h_truetautau_C");
   h_truetautau[2]->Add(h8_truetautau[5]);
   h_truetautau[3] = h8_truetautau[6]->Clone("h_truetautau_D");
   h_truetautau[3]->Add(h8_truetautau[7]);*/

   TString title = "";
   if (channel=="Muon") title="#mu + #tau_{h}";
   if (channel=="Electron") title="e + #tau_{h}";
   if (channel=="Tau") title="#tau_{h} + #tau_{h}";
   if (channel=="MuonEG") title="e + #mu";

   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      std::cout << "summing region " << labels[i] << std::endl;
      char titles[100];
      sprintf(titles, "%s: %s", title.Data(), labels[i].Data());

      h_truetautau[i] = (TH1D*)h8_truetautau[2*i]->Clone("h_truetautau_"+labels[i]);
      h_truetautau[i]->Add(h8_truetautau[(2*i)+1]);
      h_truetautau[i]->SetTitle(titles);
      h_realtau[i] = (TH1D*)h8_realtau[2*i]->Clone("h_realtau_"+labels[i]);
      h_realtau[i]->Add(h8_realtau[(2*i)+1]);
      h_realtau[i]->SetTitle(titles);
      h_lfaketau[i] = (TH1D*)h8_lfaketau[2*i]->Clone("h_lfaketau_"+labels[i]);
      h_lfaketau[i]->Add(h8_lfaketau[(2*i)+1]);
      h_lfaketau[i]->SetTitle(titles);
      h_mcsum[i] = (TH1D*)h8_mcsum[2*i]->Clone("h_mcsum_"+labels[i]);
      h_mcsum[i]->Add(h8_mcsum[(2*i)+1]);
      h_mcsum[i]->SetTitle(titles);
      //h_jetfaketau[i] = (TH1D*)h8_jetfaketau[2*i]->Clone("h_jetfaketau_"+labels[i]);
      //h_jetfaketau[i]->Add(h8_jetfaketau[(2*i)+1]);
      //h_jetfaketau[i]->SetTitle(titles);
      h_data[i] = (TH1D*)h8_data[2*i]->Clone("h_data_"+labels[i]);
      h_data[i]->Add(h8_data[(2*i)+1]);
      h_data[i]->SetTitle(titles);
   }
   for (int i = 0; i < 4; ++i) {
      std::cout << "summing region " << labels[i] << std::endl;
      char titles[100];
      sprintf(titles, "%s: %s", title.Data(), labels[i].Data());

      h_Taustar_m175[i] = (TH1D*)h8_Taustar_m175[2*i]->Clone("h_Taustar_m175_"+labels[i]);
      h_Taustar_m175[i]->Add(h8_Taustar_m175[(2*i)+1]);

      h_Taustar_m250[i] = (TH1D*)h8_Taustar_m250[2*i]->Clone("h_Taustar_m250_"+labels[i]);
      h_Taustar_m250[i]->Add(h8_Taustar_m250[(2*i)+1]);

      h_Taustar_m375[i] = (TH1D*)h8_Taustar_m375[2*i]->Clone("h_Taustar_m375_"+labels[i]);
      h_Taustar_m375[i]->Add(h8_Taustar_m375[(2*i)+1]);

      h_Taustar_m500[i] = (TH1D*)h8_Taustar_m500[2*i]->Clone("h_Taustar_m500_"+labels[i]);
      h_Taustar_m500[i]->Add(h8_Taustar_m500[(2*i)+1]);  

      h_Taustar_m625[i] = (TH1D*)h8_Taustar_m625[2*i]->Clone("h_Taustar_m625_"+labels[i]);
      h_Taustar_m625[i]->Add(h8_Taustar_m625[(2*i)+1]);

      h_Taustar_m750[i] = (TH1D*)h8_Taustar_m750[2*i]->Clone("h_Taustar_m750_"+labels[i]);
      h_Taustar_m750[i]->Add(h8_Taustar_m750[(2*i)+1]);

      h_Taustar_m1000[i] = (TH1D*)h8_Taustar_m1000[2*i]->Clone("h_Taustar_m1000_"+labels[i]);
      h_Taustar_m1000[i]->Add(h8_Taustar_m1000[(2*i)+1]);

      h_Taustar_m1250[i] = (TH1D*)h8_Taustar_m1250[2*i]->Clone("h_Taustar_m1250_"+labels[i]);
      h_Taustar_m1250[i]->Add(h8_Taustar_m1250[(2*i)+1]);

      h_Taustar_m1500[i] = (TH1D*)h8_Taustar_m1500[2*i]->Clone("h_Taustar_m1500_"+labels[i]);
      h_Taustar_m1500[i]->Add(h8_Taustar_m1500[(2*i)+1]);

      h_Taustar_m1750[i] = (TH1D*)h8_Taustar_m1750[2*i]->Clone("h_Taustar_m1750_"+labels[i]);
      h_Taustar_m1750[i]->Add(h8_Taustar_m1750[(2*i)+1]);

      h_Taustar_m2000[i] = (TH1D*)h8_Taustar_m2000[2*i]->Clone("h_Taustar_m2000_"+labels[i]);
      h_Taustar_m2000[i]->Add(h8_Taustar_m2000[(2*i)+1]);

      h_Taustar_m2500[i] = (TH1D*)h8_Taustar_m2500[2*i]->Clone("h_Taustar_m2500_"+labels[i]);
      h_Taustar_m2500[i]->Add(h8_Taustar_m2500[(2*i)+1]);

      h_Taustar_m3000[i] = (TH1D*)h8_Taustar_m3000[2*i]->Clone("h_Taustar_m3000_"+labels[i]);
      h_Taustar_m3000[i]->Add(h8_Taustar_m3000[(2*i)+1]);

      h_Taustar_m3500[i] = (TH1D*)h8_Taustar_m3500[2*i]->Clone("h_Taustar_m3500_"+labels[i]);
      h_Taustar_m3500[i]->Add(h8_Taustar_m3500[(2*i)+1]);

      h_Taustar_m4000[i] = (TH1D*)h8_Taustar_m4000[2*i]->Clone("h_Taustar_m4000_"+labels[i]);
      h_Taustar_m4000[i]->Add(h8_Taustar_m4000[(2*i)+1]);

      h_Taustar_m4500[i] = (TH1D*)h8_Taustar_m4500[2*i]->Clone("h_Taustar_m4500_"+labels[i]);
      h_Taustar_m4500[i]->Add(h8_Taustar_m4500[(2*i)+1]);

      h_Taustar_m5000[i] = (TH1D*)h8_Taustar_m5000[2*i]->Clone("h_Taustar_m5000_"+labels[i]);
      h_Taustar_m5000[i]->Add(h8_Taustar_m5000[(2*i)+1]);     
   }
   std::cout << "end sum8Hists()" << std::endl;
}

/*void runAnalysis::makePrediction_dm()
{std::cout << "makePrediction_dm()" << std::endl;
   
   // open file with fake rates
   TFile * f_dm = TFile::Open("Muon_m0.root");

   TH1D * h_CoD_ = (TH1D*)f_dm->Get("h_CoD");
   std::cout << "h_CoD_: " << h_CoD_ << std::endl;
   const double fr_1p = h_CoD_->GetBinContent(2);
   //const double frerr_1p = h_CoD_->GetBinError(2);
   const double fr_3p = h_CoD_->GetBinContent(4);
   //const double frerr_3p = h_CoD_->GetBinError(4);

   TH1D * h_kappa_ = (TH1D*)f_dm->Get("h_kappa");
   std::cout << "h_kappa_: " << h_kappa_ << std::endl;
   const double kappa_1p = h_kappa_->GetBinContent(2);
   //const double kappaerr_1p = h_kappa_->GetBinError(2);
   const double kappa_3p = h_kappa_->GetBinContent(4);
   //const double kappaerr_3p = h_kappa_->GetBinError(4);

   h_1p = (TH1D*)h8_ABCD[2]->Clone("h_1p");
   h_1p->Scale(kappa_1p * fr_1p);

   h_3p = (TH1D*)h8_ABCD[3]->Clone("h_3p");
   h_3p->Scale(kappa_3p * fr_3p);

   h_BCoD_dm = (TH1D*)h_1p->Clone("h_BCoD_dm");
   h_BCoD_dm->Add(h_3p);

   //f_dm->Close();
   std::cout << "end makePrediction_dm()" << std::endl;
}*/

/*void makePrediction_dm()
{std::cout << "makePrediction_dm()" << std::endl;

   // open file with fake rates
   TFile * f_dm = TFile::Open("Muon_m0.root");

   TH1D * h_CoD_ = (TH1D*)f_dm->Get("h_CoD");
   std::cout << "h_CoD_: " << h_CoD_ << std::endl;
   const double fr_1p = h_CoD_->GetBinContent(2);
   const double frerr_1p = h_CoD_->GetBinError(2);
   const double fr_3p = h_CoD_->GetBinContent(4);
   const double frerr_3p = h_CoD_->GetBinError(4);

   TH1D * h_kappa_ = (TH1D*)f_dm->Get("h_kappa");
   std::cout << "h_kappa_: " << h_kappa_ << std::endl;
   const double kappa_1p = h_kappa_->GetBinContent(2);
   const double kappaerr_1p = h_kappa_->GetBinError(2);
   const double kappa_3p = h_kappa_->GetBinContent(4);
   const double kappaerr_3p = h_kappa_->GetBinError(4);
   
   //f_dm->Close();

   TFile * f = TFile::Open("Muon_m1000.root", "UPDATE");

   TH1D * h_ABCD_B1 = (TH1D*)f->Get("h_ABCD_B1");
   TH1D * h_BCoD_dm1p = (TH1D*)h_ABCD_B1->Clone("h_BCoD_dm1p");
   for (int i = 1; i <= h_ABCD_B1->GetNbinsX(); ++i) {
      const double val = h_BCoD_dm1p->GetBinContent(i);
      const double err = h_BCoD_dm1p->GetBinError(i);
      double newval = 0.;
      double newerr = 0.;
      if (val>0.) {
         newval = val * kappa_1p * fr_1p;
         newerr = (err/val)*(err/val) + (frerr_1p/fr_1p)*(frerr_1p/fr_1p) + (kappaerr_1p/kappa_1p)*(kappaerr_1p/kappa_1p);
         newerr = newval * sqrt(newerr);
      }
      h_BCoD_dm1p->SetBinContent(i, newval);
      h_BCoD_dm1p->SetBinError(i, newerr);
   }

   TH1D * h_ABCD_B3 = (TH1D*)f->Get("h_ABCD_B3");
   TH1D * h_BCoD_dm3p = (TH1D*)h_ABCD_B3->Clone("h_BCoD_dm3p");
   for (int i = 1; i <= h_ABCD_B3->GetNbinsX(); ++i) {
      const double val = h_BCoD_dm3p->GetBinContent(i);
      const double err = h_BCoD_dm3p->GetBinError(i);
      double newval = 0.;
      double newerr = 0.;
      if (val>0.) {
         newval = val * kappa_3p * fr_3p;
         newerr = (err/val)*(err/val) + (frerr_3p/fr_3p)*(frerr_3p/fr_3p) + (kappaerr_3p/kappa_3p)*(kappaerr_3p/kappa_3p);
         newerr = newval * sqrt(newerr);
      }
      h_BCoD_dm3p->SetBinContent(i, newval);
      h_BCoD_dm3p->SetBinError(i, newerr);
   }

   TH1D * h_BCoD_dm = (TH1D*)h_BCoD_dm1p->Clone("h_BCoD_dm");
   h_BCoD_dm->Add(h_BCoD_dm3p);

   h_BCoD_dm1p->Write();
   h_BCoD_dm3p->Write();
   h_BCoD_dm->Write();

   //f->Close();

   TCanvas * c = new TCanvas("c", "", 1200, 800);
   c->Divide(3, 2);
   
   TPad * p1 = (TPad*)c->cd(1);
   
   h_ABCD_B1->SetMarkerColor(6);
   h_ABCD_B1->SetLineColor(6);
   h_ABCD_B1->SetMarkerSize(2);
   h_ABCD_B3->SetMarkerColor(7);
   h_ABCD_B3->SetLineColor(7);
   h_ABCD_B3->SetMarkerSize(2);
   
   h_ABCD_B1->Draw("P, TEXT");
   h_ABCD_B3->Draw("PE, TEXT, SAME");
   h_ABCD_B1->SetStats(0);
   p1->SetLogy();

   TLegend * l = new TLegend(0.5, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->AddEntry(h_ABCD_B1, "B1", "P");
   l->AddEntry(h_ABCD_B3, "B3", "P");
   l->Draw();
   
   TPad * p2 = (TPad*)c->cd(2);
   
   h_BCoD_dm1p->SetMarkerColor(6);
   h_BCoD_dm1p->SetLineColor(6);
   h_BCoD_dm1p->SetMarkerSize(2);
   h_BCoD_dm3p->SetMarkerColor(7);
   h_BCoD_dm3p->SetLineColor(7);
   h_BCoD_dm3p->SetMarkerSize(2);
   h_BCoD_dm1p->Draw("PE, TEXT");
   h_BCoD_dm3p->Draw("PE, TEXT, SAME");
   h_BCoD_dm1p->SetStats(0);
   p2->SetLogy();

   TLegend * l2 = new TLegend(0.5, 0.7, 0.875, 0.875);
   l2->SetBorderSize(0);
   l2->AddEntry(h_ABCD_B1, "1-prong estimate", "P");
   l2->AddEntry(h_ABCD_B3, "3-prong estimate", "P");
   l2->Draw();

   TPad * p3 = (TPad*)c->cd(3);
   h_BCoD_dm->SetMarkerSize(2);
   h_BCoD_dm->Draw("PE, TEXT");
   h_BCoD_dm->SetStats(0);
   p3->SetLogy();

   c->cd(4);
   h_kappa_->SetMarkerSize(2);
   h_kappa_->Draw("PE, TEXT");
   h_kappa_->SetStats(0);
   
   c->cd(5);
   h_CoD_->SetMarkerSize(2);
   h_CoD_->Draw("PE, TEXT");
   h_CoD_->SetStats(0);

   //f_dm->Close();
   std::cout << "end makePrediction_dm()" << std::endl;
}
*/
void runAnalysis::makeABCDHists()
{std::cout << "makeABCDHists()" << std::endl;  
   const TString labels8[8] = {"A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"};
   for (int i = 0; i < 8; ++i) {
      h8_ABCD[i] = (TH1D*)h8_data[i]->Clone("h_ABCD_"+labels8[i]);
      //h8_ABCD[i]->Add(h8_jetfaketau[i], -1.);
      h8_ABCD[i]->Add(h8_lfaketau[i], -1.);
      h8_ABCD[i]->Add(h8_realtau[i], -1.);
      h8_ABCD[i]->Add(h8_truetautau[i], -1.);
   }
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      h_ABCD[i] = (TH1D*)h_data[i]->Clone("h_ABCD_"+labels[i]);
      //h_ABCD[i]->Add(h_jetfaketau[i], -1.);
      h_ABCD[i]->Add(h_lfaketau[i], -1.);
      h_ABCD[i]->Add(h_realtau[i], -1.);
      h_ABCD[i]->Add(h_truetautau[i], -1.);
   }
   std::cout << "end makeABCDHists()" << std::endl;
}

void runAnalysis::makePrediction_ABCD()
{std::cout << "makePrediction_ABCD()" << std::endl;

   TH1D *hA, *hB, *hC, *hD;
   if (!blindA) hA = (TH1D*)h_ABCD[0]->Clone("hA");
   hB = (TH1D*)h_ABCD[1]->Clone("hB");
   hC = (TH1D*)h_ABCD[2]->Clone("hC");
   hD = (TH1D*)h_ABCD[3]->Clone("hD");

   double Berr, Cerr, Derr;
   const double Bin = hB->IntegralAndError(1, h->GetNbinsX()+1, Berr);
   const double Cin = hC->IntegralAndError(1, h->GetNbinsX()+1, Cerr);
   const double Din = hD->IntegralAndError(1, h->GetNbinsX()+1, Derr);
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

   // inclusive
   h_CoD = (TH1D*)h_ABCD[2]->Clone("h_CoD");
   h_CoD->SetTitle(title_CoD);
   h_CoD->Divide(h_ABCD[3]);
   h_CoD_inc = (TH1D*)h->Clone("h_CoD_inc"); 
   h_CoD_inc->SetTitle(title_CoD);
   for (int i = 1; i <= h->GetNbinsX(); ++i) {
      h_CoD_inc->SetBinContent(i, CoD);
      h_CoD_inc->SetBinError(i, CoDerr);
   }
   h_BCoD = (TH1D*)h_CoD->Clone("h_BCoD");
   h_BCoD->Multiply(h_ABCD[1]);
   h_BCoD_inc = (TH1D*)h_CoD_inc->Clone("h_BCoD_inc");
   h_BCoD_inc->Multiply(h_ABCD[1]);

   //const bool addKappa = false;
   //if (addKappa && mass==0) {
   //   h_BCoD->Multiply(h_kappa);
   //   h_BCoD_inc->Multiply(h_kappa_inc);
   //}

   // 1-prong
   h_CoD_1p = (TH1D*)h8_ABCD[4]->Clone("h_CoD_1p");
   h_CoD_1p->SetTitle(title_CoD);
   h_CoD_1p->Divide(h8_ABCD[6]);
   h_CoD_1p_inc = (TH1D*)h->Clone("h_CoD_1p_inc"); 
   h_CoD_1p_inc->SetTitle(title_CoD);
   for (int i = 1; i <= h->GetNbinsX(); ++i) {
      h_CoD_1p_inc->SetBinContent(i, CoD); //!
      h_CoD_1p_inc->SetBinError(i, CoDerr); //!
   }
   h_BCoD_1p = (TH1D*)h_CoD_1p->Clone("h_BCoD_1p");
   h_BCoD_1p->Multiply(h8_ABCD[2]);
   h_BCoD_1p_inc = (TH1D*)h_CoD_1p_inc->Clone("h_BCoD_1p_inc");
   h_BCoD_1p_inc->Multiply(h8_ABCD[2]);

   // 3-prong
   h_CoD_3p = (TH1D*)h8_ABCD[5]->Clone("h_CoD_3p");
   h_CoD_3p->SetTitle(title_CoD);
   h_CoD_3p->Divide(h8_ABCD[7]);
   h_CoD_3p_inc = (TH1D*)h->Clone("h_CoD_3p_inc"); 
   h_CoD_3p_inc->SetTitle(title_CoD);
   for (int i = 1; i <= h->GetNbinsX(); ++i) {
      h_CoD_3p_inc->SetBinContent(i, CoD); //!
      h_CoD_3p_inc->SetBinError(i, CoDerr); //!
   }
   h_BCoD_3p = (TH1D*)h_CoD_3p->Clone("h_BCoD_3p");
   h_BCoD_3p->Multiply(h8_ABCD[3]);
   h_BCoD_3p_inc = (TH1D*)h_CoD_3p_inc->Clone("h_BCoD_3p_inc");
   h_BCoD_3p_inc->Multiply(h8_ABCD[3]);

   //h_BCoD_dm = (TH1D*)h_BCoD_1p->Clone("h_BCoD_dm");
   //h_BCoD_dm->Add(h_BCoD_3p);

   if (!blindA) {
      h_AoB = (TH1D*)hA->Clone("h_AoB");
      h_AoB->Divide(hB);
      h_AoB->GetYaxis()->SetTitle("A / B");
      h_AoB_inc = (TH1D*)h->Clone("h_AoB_inc");

      h_AoB_1p = (TH1D*)h8_ABCD[0]->Clone("h_AoB_1p");
      h_AoB_1p->Divide(h8_ABCD[2]);
      h_AoB_1p->GetYaxis()->SetTitle("A / B");
      h_AoB_1p_inc = (TH1D*)h->Clone("h_AoB_1p_inc");

      h_AoB_3p = (TH1D*)h8_ABCD[1]->Clone("h_AoB_3p");
      h_AoB_3p->Divide(h8_ABCD[3]);
      h_AoB_3p->GetYaxis()->SetTitle("A / B");
      h_AoB_3p_inc = (TH1D*)h->Clone("h_AoB_3p_inc");

      double Aerr_, Berr_;
      const double Ain_ = hA->IntegralAndError(1, h->GetNbinsX()+1, Aerr_);
      const double Bin_ = hB->IntegralAndError(1, h->GetNbinsX()+1, Berr_);
      std::cout << "inclusive A: " << Ain_ << "+-" << Aerr_ << std::endl;
      std::cout << "inclusive B: " << Bin_ << "+-" << Berr_ << std::endl;
      const double AoB_ = Ain_/Bin_;
      const double AoBerr_ = AoB_ * sqrt( (Aerr_/Ain_)*(Aerr_/Ain_) + (Berr_/Bin_)*(Berr_/Bin_) );
      std::cout << "inclusive transfer factor: " << AoB_ << " +- " << AoBerr_ << std::endl;
      for (int i = 1; i <= h->GetNbinsX(); ++i) {
         h_AoB_inc->SetBinContent(i, AoB_);
         h_AoB_inc->SetBinError(i, AoBerr_);
      }
   }
   std::cout << "end makePrediction()" << std::endl;
}

void runAnalysis::makeMCSum()
{std::cout << "makeMCSum()" << std::endl;
   
   fout->cd();

   const TString labels8[8] = {"A1", "A3", "B1", "B3", "C1", "C3", "D1", "D3"};
   for (int i = 0; i < 8; ++i) {
      h8_mcsum[i] = (TH1D*)h8_realtau[i]->Clone("h_mcsum_"+labels8[i]);
      h8_mcsum[i]->Add(h8_lfaketau[i]);
      h8_mcsum[i]->Add(h8_truetautau[i]);
      //h_mcsum[i]->Add(h_jetfaketau[i]);
    }
/*
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      h_mcsum[i] = (TH1D*)h_realtau[i]->Clone("h_mcsum_"+labels[i]);
      h_mcsum[i]->Add(h_lfaketau[i]);
      h_mcsum[i]->Add(h_truetautau[i]);
      //h_mcsum[i]->Add(h_jetfaketau[i]);
   }*/
   std::cout << "end makeMCSum()" << std::endl;
}

/*void runAnalysis::sumBkgHists()
{std::cout << "sumBkgHists()" << std::endl;
   
   h_bkgsum_inc = (TH1D*)h_mcsum[0]->Clone("h_bkgsum_inc");
   h_bkgsum = (TH1D*)h_mcsum[0]->Clone("h_bkgsum");

//   h_bkgsum_inc->Add(h_BCoD_inc);
 //  h_bkgsum->Add(h_BCoD);

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
   if (mass==250)  h_temp = (TH1D*)h_Taustar_m250[0]->Clone("h_temp");
   if (mass==375)  h_temp = (TH1D*)h_Taustar_m375[0]->Clone("h_temp");
   if (mass==500)  h_temp = (TH1D*)h_Taustar_m500[0]->Clone("h_temp");
   if (mass==625)  h_temp = (TH1D*)h_Taustar_m625[0]->Clone("h_temp");
   if (mass==750)  h_temp = (TH1D*)h_Taustar_m750[0]->Clone("h_temp");
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
   std::cout << "end sumBkgHists()" << std::endl;
}*/

void runAnalysis::bkgFraction()
{std::cout << "bkgFraction()" << std::endl;
   
   const TString labels[4] = {"A", "B", "C", "D"};
   std::cout << "expected background fractions: ; # of entries" << std::endl;
   for (int i = 0; i < 4; ++i) {
      std::cout << " region " << labels[i] << std::endl;
      double sum = 0.;
      if (i==0 && !blindA) std::cout << "yield in data: " << h_data[i]->GetEntries() << std::endl;
      //if (i==0) sum = h_bkgsum_inc->Integral(); //mc+prediction
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
      if (i==0) std::cout << "  jet prediction: " << h_BCoD_inc->Integral()/sum << "; " << h_BCoD_inc->GetEntries() << std::endl;
      if (i==1||i==2||i==3) std::cout << "  jet residual: " << h_ABCD[i]->Integral()/sum << "; " << h_ABCD[i]->GetEntries() << std::endl;
   }
   std::cout << "end bkgFraction()" << std::endl;
}

void runAnalysis::fillKappa(const int nProng)
{std::cout << "fillKappa()" << std::endl;

   double n[4], err[4];
   if (nProng==0) {
      h_kappa = (TH1D*)h_ABCD[0]->Clone("h_kappa");
      h_kappa->Multiply(h_ABCD[3]);
      h_kappa->Divide(h_ABCD[1]);
      h_kappa->Divide(h_ABCD[2]);
      h_kappa->GetYaxis()->SetTitle("#kappa");
      for (int i = 0; i < 4; ++i ) n[i] = h_ABCD[i]->IntegralAndError(1, h->GetNbinsX()+1, err[i]);
      h_kappa_inc = (TH1D*)h_ABCD[0]->Clone("h_kappa_inc");
      h_kappa_inc->GetYaxis()->SetTitle("#kappa");
   } else if (nProng==1) {
      h_kappa_1p = (TH1D*)h8_ABCD[0]->Clone("h_kappa_1p");
      h_kappa_1p->Multiply(h8_ABCD[6]);
      h_kappa_1p->Divide(h8_ABCD[2]);
      h_kappa_1p->Divide(h8_ABCD[4]);
      h_kappa_1p->GetYaxis()->SetTitle("#kappa");
      for (int i = 0; i < 4; ++i ) h8_ABCD[2*i]->IntegralAndError(1, h->GetNbinsX()+1, err[i]);
      h_kappa_1p_inc = (TH1D*)h8_ABCD[0]->Clone("h_kappa_1p_inc");
      h_kappa_1p_inc->GetYaxis()->SetTitle("#kappa");
   } else if (nProng==3) {
      h_kappa_3p = (TH1D*)h8_ABCD[1]->Clone("h_kappa_3p");
      h_kappa_3p->Multiply(h8_ABCD[7]);
      h_kappa_3p->Divide(h8_ABCD[3]);
      h_kappa_3p->Divide(h8_ABCD[5]);
      h_kappa_3p->GetYaxis()->SetTitle("#kappa");
      for (int i = 0; i < 4; ++i ) h8_ABCD[(2*i)+1]->IntegralAndError(1, h->GetNbinsX()+1, err[i]);
      h_kappa_3p_inc = (TH1D*)h8_ABCD[0]->Clone("h_kappa_3p_inc");
      h_kappa_3p_inc->GetYaxis()->SetTitle("#kappa");
   } else {
      return;
   }

   const double kappa = (n[0]*n[3])/(n[1]*n[2]);
   double kappa_err = 0.;
   for (int i = 0; i < 4; ++i) kappa_err += (err[i]/n[i]) * (err[i]/n[i]);
   kappa_err = kappa * sqrt(kappa_err);

   if (nProng==0) {
      for (int i = 1; i <= h->GetNbinsX(); ++i) {
         h_kappa_inc->SetBinContent(i, kappa);
         h_kappa_inc->SetBinError(i, kappa_err);
      }
   } else if (nProng==1) {
      for (int i = 1; i <= h->GetNbinsX(); ++i) {
         h_kappa_1p_inc->SetBinContent(i, kappa);
         h_kappa_1p_inc->SetBinError(i, kappa_err);
      }
   } else if (nProng==3) {
      for (int i = 1; i <= h->GetNbinsX(); ++i) {
         h_kappa_3p_inc->SetBinContent(i, kappa);
         h_kappa_3p_inc->SetBinError(i, kappa_err);
      }
   } else {
      return;
   }
   std::cout << "end fillKappa()" << std::endl;
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
   for (int i = 0; i < 8; ++i) {
      //h8_jetfaketau[i]->Write();
      h8_lfaketau[i]->Write();
      h8_realtau[i]->Write();
      h8_truetautau[i]->Write();
   }
   for (int i = 0; i < 4; ++i) {
      h_mcsum[i]->Write();   
      h_ABCD[i]->Write();
      h_data[i]->Write();
   }
   for (int i = 0; i < 8; ++i) {
      h8_mcsum[i]->Write();
      h8_ABCD[i]->Write();
      h8_data[i]->Write();
   }
 
   h_CoD->Write();
   h_CoD_inc->Write();

   h_BCoD->Write();
   h_BCoD_inc->Write();

   h_CoD_1p->Write();
   h_CoD_1p_inc->Write();
   
   h_BCoD_1p->Write();
   h_BCoD_1p_inc->Write();
 
   h_CoD_3p->Write();
   h_CoD_3p_inc->Write();
 
   h_BCoD_3p->Write();
   h_BCoD_3p_inc->Write();
   
   //h_bps_0p01->Write(); h_bps_0p01_inc->Write();
   //h_bps_0p1->Write(); h_bps_0p1_inc->Write();
   //h_bps_0p5->Write(); h_bps_0p5_inc->Write();
   //h_bps_1->Write(); h_bps_1_inc->Write();

   //if (mass==0) {
   //   h_1p->Write();
   //   h_3p->Write();
   //}

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
   for (int i = 0; i < 8; ++i) {
      h8_Taustar_m175[i]->Write();
      h8_Taustar_m250[i]->Write();
      h8_Taustar_m375[i]->Write();
      h8_Taustar_m500[i]->Write();
      h8_Taustar_m625[i]->Write();
      h8_Taustar_m750[i]->Write();
      h8_Taustar_m1000[i]->Write();
      h8_Taustar_m1250[i]->Write();
      h8_Taustar_m1500[i]->Write();
      h8_Taustar_m1750[i]->Write();
      h8_Taustar_m2000[i]->Write();
      h8_Taustar_m2500[i]->Write();
      h8_Taustar_m3000[i]->Write();
      h8_Taustar_m3500[i]->Write();
      h8_Taustar_m4000[i]->Write();
      h8_Taustar_m4500[i]->Write();
      h8_Taustar_m5000[i]->Write();
   }
   
   if (!blindA) {
      h_kappa->Write();
      h_kappa_inc->Write();
      h_kappa_1p->Write();
      h_kappa_1p_inc->Write();
      h_kappa_3p->Write();
      h_kappa_3p_inc->Write();
      h_AoB->Write();
      h_AoB_inc->Write();
      h_AoB_1p->Write();
      h_AoB_1p_inc->Write();
      h_AoB_3p->Write();
      h_AoB_3p_inc->Write();
   }
   std::cout << "end saveHists()" << std::endl;
}

void runAllWrapper(const TString channel, const int mass, const bool blindA, const bool doPredDM)
{std::cout << "runAllWrapper() " << channel << " " << mass << " " << blindA << std::endl;
  
   if (!(channel=="Electron"||channel=="Muon"||channel=="Tau"||channel=="MuonEG")) {
      std::cout << "bad channel!" << std::endl;
      return;
   }
   runAnalysis r;
   r.channel = channel;
   r.mass = mass;
   r.blindA = blindA;
   r.doPredDM = doPredDM;
   r.runAll();
   std::cout << "end runAllWrapper()" << std::endl;
}

