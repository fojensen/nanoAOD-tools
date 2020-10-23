#include <iostream>
#include <TCanvas.h>
#include <TLegend.h>
#include <THStack.h>
#include <TH1D.h>
#include <TFile.h>
#include <TLine.h>

void runPoint(const TString histname)
{
   const int nmc = 9;
   TString mctags[nmc];
   int col[nmc];
   TString labels[nmc];
   mctags[0] = "ZZ";                   col[0] = 52;  labels[0] = "ZZ";
   mctags[1] = "WZ";                   col[1] = 53;  labels[1] = "WZ";
   mctags[2] = "WW";                   col[2] = 54;  labels[2] = "WW";
   mctags[3] = "ST_tW";                col[3] = 209;  labels[3] = "tW";
   mctags[4] = "TTToSemiLeptonic";     col[4] = 210;  labels[4] = "t#bar{t} #rightarrow l#nu2q";
   mctags[5] = "TTTo2L2Nu";            col[5] = 211;  labels[5] = "t#bar{t} #rightarrow 2l2#nu";
   mctags[6] = "EWKZ2Jets_ZToLL_M-50"; col[6] = 96;  labels[6] = "EWKZ50";
   mctags[7] = "DYJetsToLL_M-10to50";  col[7] = 97;  labels[7] = "DY10to50";
   mctags[8] = "DYJetsToLL_M-50";      col[8] = 98; labels[8] = "DY50";

   TH1D * h_mc[4][nmc];
   for (int i = 0; i < nmc; ++i) {
      char fname[100];
      sprintf(fname, "./outputHists_2018/%s_emb.root", mctags[i].Data());
      TFile * f_mc = TFile::Open(fname);
      for (int j = 0; j < 4; ++j) {
         char hname[100];
         sprintf(hname, "%s_%d", histname.Data(), j);
         h_mc[j][i] = (TH1D*)f_mc->Get(hname);
       }
   }

   TH1D * h_mcsum[4];
   for (int i = 0; i < 4; ++i) {
      char hname[100];
      sprintf(hname, "h_mcsum_%d", i);
      h_mcsum[i] = (TH1D*)h_mc[i][0]->Clone();
   }
   for (int i = 0; i < 4; ++i) {
      for (int j = 1; j < nmc; ++j) {
         h_mcsum[i]->Add(h_mc[i][j]);
      }
   }

   THStack * stack[4];
   for (int i = 0; i < 4; ++i) {
      stack[i] = new THStack();
      char stacktitle[100];
      sprintf(stacktitle, "%s;%s;%s", h_mc[i][0]->GetTitle(), h_mc[i][0]->GetXaxis()->GetTitle(), h_mc[i][0]->GetYaxis()->GetTitle());
      stack[i]->SetTitle(stacktitle);
      for (int j = 0; j < nmc; ++j) {
         h_mc[i][j]->SetFillColor(col[j]);
         stack[i]->Add(h_mc[i][j]);
      }  
   }  

   TH1D * h_emb[4];
   TFile * f_emb = TFile::Open("./outputHists_2018/Embedded.root");
   for (int i = 0; i < 4; ++i) {
      char hname[100]; 
      sprintf(hname, "%s_%d", histname.Data(), i);
      h_emb[i] = (TH1D*)f_emb->Get(hname);
   }

   TH1D * h_sig250[4];
   TFile * f_sig250 = TFile::Open("./outputHists_2018/Taustar_m250.root");
   for (int i = 0; i < 4; ++i) {
      char hname[100];
      sprintf(hname, "%s_%d", histname.Data(), i);
      h_sig250[i] = (TH1D*)f_sig250->Get(hname); 
      h_sig250[i]->SetLineStyle(2);
      h_sig250[i]->SetLineColor(81);
   }

   TH1D * h_sig500[4];
   TFile * f_sig500 = TFile::Open("./outputHists_2018/Taustar_m500.root");
   for (int i = 0; i < 4; ++i) {
      char hname[100];
      sprintf(hname, "%s_%d", histname.Data(), i);
      h_sig500[i] = (TH1D*)f_sig500->Get(hname);
      h_sig500[i]->SetLineStyle(2);
      h_sig500[i]->SetLineColor(86);
   }

   TH1D * r[4];
   for (int i = 0; i < 4; ++i) {
      char hname[100];
      sprintf(hname, "r_%d", i);
      r[i] = (TH1D*)h_emb[i]->Clone(hname);
      r[i]->Divide(h_mcsum[i]);
      r[i]->GetYaxis()->SetTitle("embedded / mc");
      r[i]->SetMarkerColor(602);
   }

   TLegend * leg = new TLegend(0.25, 0.7, 0.875, 0.875);
   leg->SetBorderSize(0);
   leg->SetNColumns(3);
   for (int i = 0; i < nmc; ++i) {
      leg->AddEntry(h_mc[0][i], labels[i], "F");
   }
   leg->AddEntry(h_emb[0], "embedded", "P");
   leg->AddEntry(h_sig250[0], "#tau* m250", "L");
   leg->AddEntry(h_sig500[0], "#tau* m500", "L");

   TCanvas * c = new TCanvas("c_"+histname, histname, 1600, 800);
   c->Divide(4, 2);
   
   for (int i = 0; i < 4; ++i) {
      TPad * p = (TPad*)c->cd(1+i);
      h_emb[i]->SetMarkerStyle(20);
      h_emb[i]->Draw("PE");
      stack[i]->SetMinimum(1);
      stack[i]->SetMaximum(1e7);
      stack[i]->Draw("HIST");
      h_emb[i]->Draw("PE, SAME");
      h_sig250[i]->Draw("HIST, SAME");
      h_sig500[i]->Draw("HIST, SAME");
      leg->Draw();
      p->SetLogy();
   }

   TLine * lin = new TLine(h_emb[0]->GetBinLowEdge(1),  1., h_emb[0]->GetBinLowEdge(h_emb[0]->GetNbinsX()+1), 1.);
   lin->SetLineStyle(2);
   for (int i = 0; i < 4; ++i) {
      c->cd(5+i);
      //r[i]->Draw("PE, TEXT"); r[i]->SetMarkerSize(3); 
      r[i]->Draw("PE"); r[i]->SetMarkerStyle(20);
      //r[i]->SetTitle(titles[i]);
      r[i]->SetStats(0);
      r[i]->SetMinimum(0.5);
      r[i]->SetMaximum(1.5);
      lin->Draw();
   }
   c->SaveAs("./plots/emb."+histname+".pdf"); 
}

void embeddedStudy()
{
   //runPoint("h_vismass");
   //runPoint("h_vispt");
   //runPoint("h_unit");
   //runPoint("h_mt");
   //runPoint("h_met");
   //runPoint("h_njets");
   //runPoint("h_nbjetsM");
   //runPoint("h_nbjetsT");
   //runPoint("h_npv");
   //runPoint("h_decayMode");
   runPoint("h_minmass200");
   //runPoint("h_maxmass");
}

