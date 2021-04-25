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
      void histInit();
      void loadCuts(const int year, TCut cuts[4]);
      void fillMCHists(const int year);
      void fillDataHists(const int year);
      void addOverflowToHists();
      void makeABCDHists();
      void sumMCHists();
      void saveHists();

      TString makeString();
      TString channel;
      TString var;
      int mass;
      bool blindA;
      TFile *fout;
      TH1D *h;
      TH1D *h_WW[4], *h_WZ[4], *h_ZZ[4];
      TH1D *h_TTTo2L2Nu[4], *h_TTToSemiLeptonic[4];
      TH1D *h_ST_tW_top[4], *h_ST_tW_antitop[4];
      TH1D *h_ST_t_channel_top[4], *h_ST_t_channel_antitop[4];
      TH1D *h_DYJetsToLLM10[4];
      TH1D *h_DYJetsToEEMuMu[4], *h_DYJetsToTauTau[4];
      TH1D *h_taustar[4];
      TH1D *h_data[4];
      TH1D *h_ABCD[4];
      TH1D *h_mcsum[4];
      TH1D *h_CoD, *h_CoD_inc;
      TH1D *h_BCoD, *h_BCoD_inc;
      const int nmc = 13;
      TString mctags[13];
};

void plotControlRegions(const bool blindA, const int mass, const TString fname)
{
   std::cout << "plotControlRegions()" << std::endl;

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
      sprintf(title, "%s;%s;%s", labels[i].Data(), h_WW[i]->GetXaxis()->GetTitle(), h_WW[i]->GetYaxis()->GetTitle());
      s[i]->SetTitle(title); 
   }

   TH1D * h_BCoD = (TH1D*)f->Get("h_BCoD");
   h_BCoD->SetFillColor(98);
   TH1D * h_BCoD_inc = (TH1D*)f->Get("h_BCoD_inc");
   //h_BCoD->SetFillColor(98);
   h_BCoD_inc->SetFillColor(98);
   //s[0]->Add(h_BCoD);
   s[0]->Add(h_BCoD_inc);

   const double ymax = pow(10, ceil(log10(max))+1);
   double ymin = 0.1;
   if (ymax>=100.) ymin = 1.;
   if (ymax>=1000.) ymin = 10.;
   if (ymax>=10000.) ymin = 100.;
   if (ymax>=100000.) ymin = 1000.;

   TLegend * lA = new TLegend(0.25, 0.7, 0.875, 0.875);
   lA->SetNColumns(2);
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
   
   lA->AddEntry(h_BCoD, "BCoD", "F");
   if (!blindA) lA->AddEntry(h_data[0], "data", "P");
   lBCD->AddEntry(h_data[1], "data", "P");

   TCanvas * c1 = new TCanvas("c1", "c1", 800, 800);
   c1->Divide(2, 2);

   TPad * p1 = (TPad*)c1->cd(1);
   s[0]->Draw("HIST");
   h_taustar[0]->Draw("HIST, E, SAME");
   if (!blindA) h_data[0]->Draw("P, SAME");
   p1->SetLogy();
   lA->Draw();
   s[0]->SetMaximum(ymax); s[0]->SetMinimum(ymin);

   TPad * p2 = (TPad*)c1->cd(2);
   s[1]->Draw("HIST");
   h_taustar[1]->Draw("HIST, E, SAME");
   h_data[1]->Draw("P, SAME");
   p2->SetLogy();
   lBCD->Draw();
   s[1]->SetMaximum(ymax); s[1]->SetMinimum(ymin);

   TPad * p3 = (TPad*)c1->cd(3);
   s[2]->Draw("HIST");
   h_taustar[2]->Draw("HIST, E, SAME");
   h_data[2]->Draw("P, SAME");
   p3->SetLogy();
   lBCD->Draw();
   s[2]->SetMaximum(ymax); s[2]->SetMinimum(ymin);

   TPad * p4 = (TPad*)c1->cd(4);
   s[3]->Draw("HIST");
   h_taustar[3]->Draw("HIST, E, SAME");
   h_data[3]->Draw("P, SAME");
   p4->SetLogy();
   lBCD->Draw();
   s[3]->SetMaximum(ymax); s[3]->SetMinimum(ymin);

   //c1->SaveAs();

   TCanvas * c3 = new TCanvas("c3", "c3", 400, 400);
   TH1D *h_CoD = (TH1D*)f->Get("h_CoD");
   TH1D *h_CoD_inc = (TH1D*)f->Get("h_CoD_inc");
   h_CoD->Draw("PE");
   h_CoD->SetMarkerStyle(20);
   h_CoD->SetStats(0);
   //h_CoD->SetMinimum(0.8*(h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1)));
   //h_CoD->SetMaximum(1.2*(h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1)));
   TLine * lup = new TLine(h_CoD_inc->GetBinLowEdge(1), h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1), h_CoD_inc->GetBinLowEdge(h_CoD_inc->GetNbinsX()+1), h_CoD_inc->GetBinContent(1)+h_CoD_inc->GetBinError(1));
   lup->SetLineStyle(2);
   lup->Draw();
   TLine * ldown = new TLine(h_CoD_inc->GetBinLowEdge(1), h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1), h_CoD_inc->GetBinLowEdge(h_CoD_inc->GetNbinsX()+1), h_CoD_inc->GetBinContent(1)-h_CoD_inc->GetBinError(1));  
   ldown->SetLineStyle(2);
   ldown->Draw();

   //c3->SaveAs();

   TH1D * h_mcsum = (TH1D*)f->Get("h_mcsum_A");
   TH1D * h_bkgsum = (TH1D*)h_mcsum->Clone("h_bkgsum");
   h_bkgsum->Add(h_BCoD);
   const double sum = h_bkgsum->Integral();

   std::cout << "expected background fractions: ; # of entries" << std::endl;
   std::cout << " WW: " << h_WW[0]->Integral()/sum << "; " << h_WW[0]->GetEntries() << std::endl;
   std::cout << " WZ: " << h_WZ[0]->Integral()/sum << "; " << h_WZ[0]->GetEntries() << std::endl;
   std::cout << " ZZ: " << h_ZZ[0]->Integral()/sum << "; " << h_ZZ[0]->GetEntries() << std::endl;
   std::cout << " TTTo2L2Nu: " << h_TTTo2L2Nu[0]->Integral()/sum << "; " << h_TTTo2L2Nu[0]->GetEntries() << std::endl;
   std::cout << " TTToSemiLeptonic: " << h_TTToSemiLeptonic[0]->Integral()/sum << "; " << h_TTToSemiLeptonic[0]->GetEntries() << std::endl;
   std::cout << " ST_tW_top: " << h_ST_tW_top[0]->Integral()/sum << "; " << h_ST_tW_top[0]->GetEntries() << std::endl;
   std::cout << " ST_tW_antitop: " <<h_ST_tW_antitop[0] ->Integral()/sum << "; " << h_ST_tW_antitop[0]->GetEntries() << std::endl;
   std::cout << " ST_t_channel_top: " << h_ST_t_channel_top[0]->Integral()/sum << "; " << h_ST_t_channel_top[0]->GetEntries() << std::endl;
   std::cout << " ST_t_channel_antitop: " << h_ST_t_channel_antitop[0]->Integral()/sum << "; " << h_ST_t_channel_antitop[0]->GetEntries() << std::endl;
   std::cout << " DYJetsToLLM10: " << h_DYJetsToLLM10[0]->Integral()/sum << "; " << h_DYJetsToLLM10[0]->GetEntries() << std::endl;
   std::cout << " DYJetsToEEMuMu: " << h_DYJetsToEEMuMu[0]->Integral()/sum << "; " << h_DYJetsToEEMuMu[0]->GetEntries() << std::endl;
   std::cout << " DYJetsToTauTau: " << h_DYJetsToTauTau[0]->Integral()/sum << "; " << h_DYJetsToTauTau[0]->GetEntries() << std::endl;
   std::cout << " BCoD: " << h_BCoD->Integral()/sum << std::endl;

   if (!blindA) {
      TH1D * r = (TH1D*)h_data[0]->Clone("r");
      r->Divide(h_bkgsum);
      r->GetYaxis()->SetTitle("observed / prediction");
      r->SetMarkerStyle(20);
      TCanvas * c2 = new TCanvas("c2", "c2", 400, 400);
      r->Draw("PE");
      r->SetStats(0);
      r->SetMinimum(0.);
      r->SetMaximum(2.);
      TLine * line = new TLine(r->GetBinLowEdge(1), 1., r->GetBinLowEdge(r->GetNbinsX()+1), 1.);
      line->SetLineStyle(2);
      line->Draw();
      //c2->SaveAs();
   }
}

void runAnalysis::runAll()
{
   std::cout << "runAll()" << std::endl;
   blindA = true;
   //h = new TH1D("h", ";visible mass [GeV];events / 10 GeV", 20, 0., 200.);
   h = new TH1D("h", ";min coll mass [GeV];events / 100 GeV", 5, 0., 1000.);
   h->Sumw2();
   channel = "Muon";
   //var = "MuTau_Mass";
   var = "MuTau_MinCollMass";
   mass = 250;

   mctags[0] = "WW";
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
   mctags[12] = "Taustar_m"+TString::Itoa(mass,10);

   const TString fname = "tree2018_m"+TString::Itoa(mass, 10)+".root";
   fout = new TFile(fname, "RECREATE"); 
   histInit();
   fillMCHists(2015);
   fillMCHists(2016);
   fillDataHists(2016);
   fillMCHists(2017);
   fillDataHists(2017);
   fillMCHists(2018);
   fillDataHists(2018);
   addOverflowToHists();
   makeABCDHists();
   sumMCHists();
   saveHists();
   fout->Close();
   plotControlRegions(blindA, mass, fname);
}

void runAnalysis::histInit()
{
   std::cout << "histInit()" << std::endl;
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      h_WW[i] = (TH1D*)h->Clone("h_WW_"+labels[i]);
      h_WZ[i] = (TH1D*)h->Clone("h_WZ_"+labels[i]);
      h_ZZ[i] = (TH1D*)h->Clone("h_ZZ_"+labels[i]);
      h_TTTo2L2Nu[i] = (TH1D*)h->Clone("h_TTTo2L2Nu_"+labels[i]);
      h_TTToSemiLeptonic[i] = (TH1D*)h->Clone("h_TTToSemiLeptonic_"+labels[i]);
      h_ST_tW_top[i] = (TH1D*)h->Clone("h_ST_tW_top_"+labels[i]);
      h_ST_tW_antitop[i] = (TH1D*)h->Clone("h_ST_tW_antitop_"+labels[i]);
      h_ST_t_channel_top[i] = (TH1D*)h->Clone("h_ST_t_channel_top_"+labels[i]);
      h_ST_t_channel_antitop[i] = (TH1D*)h->Clone("h_ST_t_channel_antitop_"+labels[i]);
      h_DYJetsToLLM10[i] = (TH1D*)h->Clone("h_DYJetsToLLM10_"+labels[i]);
      h_DYJetsToEEMuMu[i] = (TH1D*)h->Clone("h_DYJetsToEEMuMu_"+labels[i]);
      h_DYJetsToTauTau[i] = (TH1D*)h->Clone("h_DYJetsToTauTau_"+labels[i]);
      char hname[100];
      sprintf(hname, "h_Taustar_m%d_%s", mass,labels[i].Data());
      h_taustar[i] = (TH1D*)h->Clone(hname);
      h_data[i] = (TH1D*)h->Clone("h_data_"+labels[i]);     
   }
}

void runAnalysis::loadCuts(const int year, TCut cuts[4])
{
   std::cout << "loadCuts()" << std::endl;
   TCut baseline, regionA, regionB, regionC, regionD;
   baseline = regionA = regionB = regionC = regionD = "1>0";
   if (channel=="Muon") {
      //baseline = baseline && TCut("MuTau_HavePair>0 && (MuTau_HaveTriplet==0||(MuTau_HaveTriplet>0&&Photon_pt[MuTau_PhotonIdx]<25.))");
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
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
      regionA = "MuTau_qq==-1 && (64&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(64&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionC = "MuTau_qq==+1 && (64&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(64&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   }
   if (channel=="Tau") {
      baseline = baseline && TCut("TauTau_HavePair>0 && (TauTau_HaveTriplet==0||(TauTau_HaveTriplet>0&&Photon_pt[TauTau_PhotonIdx]<25.))");
      //baseline = baseline && TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]<25.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("TauTau_Trigger");
      baseline = baseline && TCut("Tau_pt[TauTau_Tau0Idx]>=40. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1");
      baseline = baseline && TCut("Tau_pt[TauTau_Tau1Idx]>=40. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
      //baseline = baseline && TCut("TauTau_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      const TCut tau0pass = "(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau0fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau1pass = "(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      const TCut tau1fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      regionA = TCut("TauTau_qq==-1") &&  (tau0pass&&tau1pass);
      regionC = TCut("TauTau_qq==+1") &&  (tau0pass&&tau1pass);

      //regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      //regionB = TCut("TauTau_qq==-1") && (tau0fail&&tau1fail);
      //regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass)||(tau0fail&&tau1fail));
      regionB = TCut("TauTau_qq==-1") && (tau0fail||tau1fail);
      
      //regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      //regionD = TCut("TauTau_qq==+1") && (tau0fail&&tau1fail);
      //regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass)||(tau0fail&&tau1fail));
      regionD = TCut("TauTau_qq==+1") && (tau0fail||tau1fail);
   }
   if (channel=="Electron") {
      baseline = baseline && TCut("ElTau_HavePair>0 && (ElTau_HaveTriplet==0||(ElTau_HaveTriplet>0&&Photon_pt[ElTau_PhotonIdx]<25.))");
      //baseline = baseline && TCut("ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]<25.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("ElTau_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
      if (year==2015||year==2016) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=29.");
      if (year==2017) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      if (year==2018) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      //baseline = baseline && TCut("ElTau_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "ElTau_qq==-1 && (64&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(64&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionC = "ElTau_qq==+1 && (64&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(64&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   }
   if (channel=="ElMu") {
      baseline = baseline && TCut("ElMu_HavePair>0 && (ElMu_HaveTriplet==0||(ElMu_HaveTriplet>0&&Photon_pt[ElMu_PhotonIdx]<25.))");
      //baseline = baseline && TCut("ElMu_HaveTriplet>0 && Photon_pt[ElMu_PhotonIdx]>=100.");
      //baseline = baseline && TCut("ElMu_HaveTriplet>0 && Photon_pt[ElMu_PhotonIdx]<25.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("ElMu_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElMu_ElIdx]");
      const TCut c1 = "Electron_pt[ElMu_ElIdx]>=24. && Muon_pt[ElMu_MuIdx]>=13.";
      const TCut c2 = "Electron_pt[ElMu_ElIdx]>=13. && Muon_pt[ElMu_MuIdx]>=24.";
      baseline = baseline && (c1||c2);
      //baseline = baseline && TCut("ElMu_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=2)==1");
      regionA = "ElMu_qq==-1 && Muon_pfIsoId[ElMu_MuIdx]>=4";
      regionB = "ElMu_qq==-1 && Muon_pfIsoId[ElMu_MuIdx]>=2 && Muon_pfIsoId[ElMu_MuIdx]<4";
      regionC = "ElMu_qq==+1 && Muon_pfIsoId[ElMu_MuIdx]>=4";
      regionD = "ElMu_qq==+1 && Muon_pfIsoId[ElMu_MuIdx]>=2 && Muon_pfIsoId[ElMu_MuIdx]<4";
   }
   //if (blindA) regionA = regionA && TCut("1<0");
   cuts[0] = baseline && regionA;
   cuts[1] = baseline && regionB;
   cuts[2] = baseline && regionC;
   cuts[3] = baseline && regionD;
}

void runAnalysis::fillMCHists(const int year)
{
   std::cout << "fillMCHists(): " << year << std::endl;
   double lumi;
   if (year==2015) lumi = 19500.;
   if (year==2016) lumi = 16800.;
   //if (year==2016) lumi = 19500.+16800.;
   if (year==2017) lumi = 41480.;
   if (year==2018) lumi = 59830.;
   const TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/";
   const TString labels[4] = {"A", "B", "C", "D"};
   TCut cuts[4];
   loadCuts(year, cuts);
   for (int i = 0; i < nmc; ++i) {
      std::cout << "filling " << mctags[i] << std::endl;
      char infile[100];
      sprintf(infile, "%s/%s_%d.root", eostag.Data(), mctags[i].Data(), year);
      TFile * f = TFile::Open(infile);
      TTree * t = (TTree*)f->Get("Events");
      for (int j = 0; j < 4; ++j) {
         char buffer[3000];
         if (year!=2015 && (mctags[i]=="DYJetsToTauTau"||mctags[i]=="DYJetsToEEMuMu")) {
            sprintf(buffer, "%f * xsWeight_Njets * (%s)", lumi, TString(cuts[j]).Data());
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

void runAnalysis::fillDataHists(const int year)
{
   std::cout << "fillDataHists(): " << year << std::endl;
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

   const TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/";
   for (auto i = letters.begin(); i != letters.end(); ++i) {
      char infile[100];
      sprintf(infile, "%s/%s%s_%d.root", eostag.Data(), channel.Data(), i->Data(), year);
      TFile * f = TFile::Open(infile);
      TTree * t = (TTree*)f->Get("Events");
      fout->cd();
      for (int j = 0; j < 4; ++j) {
         if (j==0 && blindA) continue;
         char histname[100];
         sprintf(histname, "+%s", h_data[j]->GetName());
         std::cout << h_data[j]->GetName() << std::endl;
         std::cout << " entries in projection: " << t->Project(histname, var, cuts[j]) << std::endl;
      }
   }
}

void runAnalysis::addOverflowToHists()
{
   std::cout << "addOverflowToHists()" << std::endl;
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
      addOverflow(h_data[i]);
      addOverflow(h_taustar[i]);
   }
}

void runAnalysis::makeABCDHists()
{
   std::cout << "makeABCDHists()" << std::endl;
   const TString labels[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
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
   }
  
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

   // calculate the binned prediction
   h_CoD = (TH1D*)h_ABCD[2]->Clone("h_CoD");
   h_CoD->Divide(h_ABCD[3]);
   h_CoD->GetYaxis()->SetTitle("C / D");
   h_BCoD = (TH1D*)h_CoD->Clone("h_BCoD");
   h_BCoD->Multiply(h_ABCD[1]);
   // calculate the inclusive prediction
   h_CoD_inc = (TH1D*)h->Clone("h_CoD_inc");
   for (int i = 1; i <= h->GetNbinsX(); ++i) {
      h_CoD_inc->SetBinContent(i, CoD);
      h_CoD_inc->SetBinError(i, CoDerr);
   }
   h_CoD_inc->GetYaxis()->SetTitle("C / D");
   h_BCoD_inc = (TH1D*)h_CoD_inc->Clone("h_BCoD_inc");
   h_BCoD_inc->Multiply(h_ABCD[1]);
}

void runAnalysis::sumMCHists()
{
   std::cout << "sumMCHists()" << std::endl;
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
}

void runAnalysis::saveHists()
{
   std::cout << "saveHists()" << std::endl;
   fout->cd();
   for (int i = 0; i < 4; ++i) {
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
      h_ABCD[i]->Write();
      h_taustar[i]->Write();
      h_data[i]->Write();
      h_mcsum[i]->Write();
   }
   h_CoD->Write();
   h_BCoD->Write();
   h_CoD_inc->Write();
   h_BCoD_inc->Write();
}

