#include <iostream>
#include <TCut.h>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>

TH1D * runpoint(const int channel, const TString filetag)
{
   TCut baseline;
   TString var;

   if (channel==0) {
      baseline = "MuTau_HavePair>0 && MuTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && Muon_pfIsoId[MuTau_MuIdx]>=4";
      var = "MuTau_Mass";
   }
   if (channel==1) {
      baseline = "ElTau_HavePair>0 && ElTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && Electron_mvaFall17V2Iso_WP80[ElTau_ElIdx]";
      var = "ElTau_Mass";
   }
   if (channel==2) {
      baseline = "TauTau_HavePair>0 && TauTau_qq==-1";
      baseline = baseline && TCut("Tau_pt[TauTau_Tau0Idx]>=35. && Tau_pt[TauTau_Tau1Idx]>=35. && (32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && (32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1 && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
      var = "TauTau_Mass";
   }

   TString infile;
   TFile * f = 0;
   if (filetag=="VBF") f = TFile::Open("./outputData/VBFHToTauTau.root");
   if (filetag=="GluGlu") f = TFile::Open("./outputData/GluGluHToTauTau.root");
   if (filetag=="Taustar_m250") f = TFile::Open("./outputData/Taustar_m250.root");

   TTree * t = (TTree*)f->Get("Events");

   char buffer[100];
   sprintf(buffer, "h_%d_%s", channel, filetag.Data());
   TH1D * h = new TH1D(buffer, ";visible mass [GeV];events / 25 GeV", 12, 0., 300.);
   h->SetLineWidth(2);
   h->SetStats(0);
 //  h->SetMinimum(0.0001);
  // h->SetMaximum(1.);

   const double n = t->Project(h->GetName(), var, baseline);
   std::cout << n << std::endl;
   h->Scale(1./n);
   return h;
}

void hmass()
{ 
   TH1D * ha = runpoint(0, "VBF");
   ha->SetLineColor(6);
   TH1D * hb = runpoint(1, "VBF");
   hb->SetLineColor(6);
   TH1D * hc = runpoint(2, "VBF");
   hc->SetLineColor(6);

   TH1D * hd = runpoint(0, "GluGlu");
   hd->SetLineColor(7);
   TH1D * he = runpoint(1, "GluGlu");
   he->SetLineColor(7);
   TH1D * hf = runpoint(2, "GluGlu");
   hf->SetLineColor(7);

   TH1D * hg = runpoint(0, "Taustar_m250");
   hg->SetLineColor(8);
   TH1D * hh = runpoint(1, "Taustar_m250");
   hh->SetLineColor(8);
   TH1D * hi = runpoint(2, "Taustar_m250");
   hi->SetLineColor(8);

   TLegend * l = new TLegend(0.7, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->AddEntry(ha, "VBF", "L");
   l->AddEntry(hd, "GluGlu", "L");
   l->AddEntry(hg, "#tau^{*} m250", "L");

   TLine * line = new TLine(125., 0.0001, 125., 1.);
   line->SetLineStyle(2);

   TCanvas * c = new TCanvas("c", "hmass", 1200, 400);
   c->Divide(3,1);

   TPad * p1 = (TPad*)c->cd(1);
   ha->GetXaxis()->SetTitle("#mu+#tau_{h} visible mass [GeV]");
   ha->Draw("HIST, E, SAME");
   line->Draw();
   hd->Draw("HIST, E, SAME");
   hg->Draw("HIST, E, SAME");
   ha->SetMinimum(0.0001);
   ha->SetMaximum(1.);
   l->Draw();
   p1->SetLogy();

   TPad * p2 = (TPad*)c->cd(2);
   hb->GetXaxis()->SetTitle("e+#tau_{h} visible mass [GeV]");
   hb->Draw("HIST, E, SAME");
   line->Draw();
   he->Draw("HIST, E, SAME");
   hh->Draw("HIST, E, SAME");
   hb->SetMinimum(0.0001);
   hb->SetMaximum(1.);
   l->Draw();
   p2->SetLogy();

   TPad * p3 = (TPad*)c->cd(3);
   hc->GetXaxis()->SetTitle("#tau_{h}+#tau_{h} visible mass [GeV]");
   hc->Draw("HIST, E, SAME");
   line->Draw();
   hf->Draw("HIST, E, SAME");
   hi->Draw("HIST, E, SAME");
   hc->SetMinimum(0.0001);
   hc->SetMaximum(1.);
   l->Draw();
   p3->SetLogy();

   c->SaveAs("./plots/hmass.pdf");
}

