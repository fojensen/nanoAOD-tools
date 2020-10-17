#include <TLine.h>
#include <iostream>
#include <TH1D.h>
#include <THStack.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

void makeStack(const TString hname="h_vismass_0", const bool addJet=false, const bool sr=true)
{
   const int nmc = 10;
   TString mctags[nmc], labels[nmc];
   int col[nmc];
   mctags[0] = "ZZ";                   col[0] = 52;  labels[0] = "ZZ";
   mctags[1] = "WZ";                   col[1] = 53;  labels[1] = "WZ";
   mctags[2] = "WW";                   col[2] = 54;  labels[2] = "WW";
   mctags[3] = "ST_tW";                col[3] = 209;  labels[3] = "tW";
   mctags[4] = "TTToSemiLeptonic";     col[4] = 210;  labels[4] = "t#bar{t} #rightarrow l#nu2q";
   mctags[5] = "TTTo2L2Nu";            col[5] = 211;  labels[5] = "t#bar{t} #rightarrow 2l2#nu";
   mctags[6] = "EWKZ2Jets_ZToLL_M-50"; col[6] = 96;  labels[6] = "EWKZ50";
   mctags[7] = "DYJetsToLL_M-10to50";  col[7] = 97;  labels[7] = "DY10to50";
   mctags[8] = "DYJetsToLL_M-50";      col[8] = 98; labels[8] = "DY50";
   mctags[9] = "WGToLNuG";             col[9] = 1; labels[9] = "WGToLNuG";
 
   THStack * stack = new THStack();
   TLegend * l = new TLegend(0.25, 0.7, 0.875, 0.875);
   l->SetNColumns(3);
   l->SetBorderSize(0);

   TH1D * h_jet;
   if (addJet) {
      TFile * f_jet = TFile::Open("./outputHists_2018/QCD.root");
      h_jet = (TH1D*)f_jet->Get(hname);
      h_jet->SetFillColor(2);
      stack->Add(h_jet);
   }

   TH1D * h_mc[nmc];
   for (int i = 0; i < nmc; ++i) {
      char fname[100];
      sprintf(fname, "./outputHists_2018/%s_bkg.root", mctags[i].Data());
      TFile * f = TFile::Open(fname);
      h_mc[i] = (TH1D*)f->Get(hname);
      std::cout << "events in " << mctags[i] << ": " << h_mc[i]->Integral() << std::endl;
      h_mc[i]->SetFillColor(col[i]);
      stack->Add(h_mc[i]);
      l->AddEntry(h_mc[i], labels[i], "F");
   }
  
   char axistitle[100];
   sprintf(axistitle, "%s;%s;%s", h_mc[0]->GetTitle(), h_mc[0]->GetXaxis()->GetTitle(), h_mc[0]->GetYaxis()->GetTitle());
   stack->SetTitle(axistitle); 

   TH1D * h_sum = (TH1D*)h_mc[0]->Clone("h_mcsum");
   for (int i = 1; i < nmc; ++i) h_sum->Add(h_mc[i]);
   if (addJet) h_sum->Add(h_jet);

   TFile * f_emb = TFile::Open("./outputHists_2018/Embedded.root");
   TH1D * h_emb = (TH1D*)f_emb->Get(hname);
   std::cout << "events in embedded: " << h_emb->Integral() << std::endl;   
   h_emb->SetFillColor(7);
   stack->Add(h_emb);
   h_sum->Add(h_emb);
   l->AddEntry(h_emb, "emb", "F");

   if (addJet) l->AddEntry(h_jet, "jet", "F");
   
   TFile * f_sig250 = TFile::Open("./outputHists_2018/Taustar_m250.root");
   TH1D * h_sig250 = (TH1D*)f_sig250->Get(hname);
   std::cout << "events in tau* 250: " << h_sig250->Integral() << std::endl;
   h_sig250->SetLineColor(30);
   //h_sig250->SetLineStyle(2);
   h_sig250->SetLineWidth(2);
   l->AddEntry(h_sig250, "#tau* m250", "L");

   TFile * f_sig500 = TFile::Open("./outputHists_2018/Taustar_m500.root");
   TH1D * h_sig500 = (TH1D*)f_sig500->Get(hname);
   std::cout << "events in tau* 500: " << h_sig500->Integral() << std::endl;
   h_sig500->SetLineColor(40);
   //h_sig500->SetLineStyle(2);
   h_sig500->SetLineWidth(2);
   l->AddEntry(h_sig500, "#tau* m500", "L");
 
   TH1D * h_data;
   if (!sr) {
      TFile * f_data = TFile::Open("./outputHists_2018/SingleMuon.root");
      h_data = (TH1D*)f_data->Get(hname);
      std::cout << "events in data: " << h_data->Integral() << std::endl;
      h_data->SetMarkerStyle(20);
      l->AddEntry(h_data, "data", "P");
   }

   TH1D * r;
   if (!sr) {
      r = (TH1D*)h_data->Clone("r");
      r->Divide(h_sum);
      r->GetYaxis()->SetTitle("observed / predicted");
   }

   
   TCanvas * c = new TCanvas("c_"+hname, hname, 800, 400);
   c->Divide(2, 1);

   TPad * p1 = (TPad*)c->cd(1);
   stack->Draw("HIST");
   h_sig250->Draw("SAME, E");
   h_sig500->Draw("SAME, E");
   l->Draw();
   //h_data->SetMinimum(1);
   //h_data->SetMaximum(1e7);
   stack->SetMinimum(0.1);
   stack->SetMaximum(100.);
   p1->SetLogy();
   if (!sr) {
      h_data->Draw("PE, SAME");
      h_data->SetStats(0);
   }

   if (!sr) {
      c->cd(2);
      r->Draw("PE");
      r->SetStats(0);
      r->SetMinimum(0.);
      r->SetMaximum(2.);
      r->SetMarkerColor(602);
      TLine * line = new TLine(h_data->GetBinLowEdge(1), 1., h_data->GetBinLowEdge(h_data->GetNbinsX()+1), 1.);
      line->SetLineStyle(2);
      line->Draw();
   }

   c->SaveAs("./plots/stack."+hname+".pdf");
}

