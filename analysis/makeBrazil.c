#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TGraph.h>
#include <iostream>

void runPoint(/*const TString channel*/)
{
   const int nsig = 17;
   const int masses[nsig] = {175, 250, 375, 500, 625, 750, 1000, 1250, 1500, 1750, 2000, 2500, 3000, 3500, 4000, 4500, 5000};

   const int colz[6] = {2, 3, 4, 6, 7, 8};

   TGraph * g[6];
   for (int i = 0; i < 6; ++i) {
      g[i] = new TGraph(nsig);
      g[i]->SetMarkerStyle(7);
      g[i]->SetMarkerColor(colz[i]);
      g[i]->SetLineColor(colz[i]);
      g[i]->SetTitle(";#tau* mass [GeV];upper limit on #sigma #times BF");
   }

   for (int i = 0; i < nsig; ++i) {
      //if (masses[i]<4000) {
      //std::cout << "mass = " << masses[i] << std::endl;
      char infile[100];
      sprintf(infile, "../condor/higgsCombineTest.AsymptoticLimits.mH%d.root", masses[i]);
      TFile * f = TFile::Open(infile);
      TTree * t = (TTree*)f->Get("limit");
      double limit = 0.;
      t->SetBranchAddress("limit", &limit);
      for (int j = 0; j < 6; ++j) {
         t->GetEntry(j);
         std::cout << limit << std::endl;
         g[j]->SetPoint(i, masses[i], limit);
      }
      //}
   }

   TCanvas * c = new TCanvas("c", "c", 600, 400);
   g[5]->Draw("APC");
   g[5]->SetMinimum(0.01);
   g[5]->SetMaximum(10.);
   //char title[100];
   //if (channel=="Electron") sprintf(title, "e + #tau_{h}");
   //if (channel=="Muon") sprintf(title, "#mu + #tau_{h}");
   //if (channel=="Tau") sprintf(title, "#tau_{h} + #tau_{h}");
   //if (channel=="MuonEG") sprintf(title, "#mu + e");
   //g[5]->SetTitle(title);
   c->SetLogy();
   for (int i = 0; i < 5; ++i) {
      g[i]->Draw("PC, SAME");
   }
   TLegend * l = new TLegend(0.5, 0.2, 0.875, 0.4);
   l->SetBorderSize(0);
   l->SetHeader("AsymptoticLimits ( CLs )");
   l->AddEntry(g[4], "Expected 97.5%", "P");
   l->AddEntry(g[3], "Expected 84.0%", "P");
   l->AddEntry(g[2], "Expected 50.0%", "P");
   l->AddEntry(g[1], "Expected 16.0%", "P");
   l->AddEntry(g[0], "Expected  2.5%", "P");
   l->Draw();

   c->SaveAs("./plots/limits.pdf");

}

void makeBrazil()
{
   runPoint();
   //runPoint("Muon");
   //runPoint("Tau");
}

