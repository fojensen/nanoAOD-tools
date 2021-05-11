#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH2D.h>
#include <TH1D.h>
#include "addOverflow.h"

TFile * makeHists(const TString datatag, const int year, const TString channel, const bool blindA=true)
{
   std::cout << "*** makeHists() " << datatag << ", " << year << ", " << channel << std::endl;
   char finname[200];
   sprintf(finname, "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/%s.root", datatag.Data());
   TFile * infile = TFile::Open(finname);
 
   char foutname[200];
   sprintf(foutname, "./dataStudyOutput/%s_%d.root", datatag.Data(), year);
   TFile * outfile = new TFile(foutname, "RECREATE");  
   TH2D *h2[4];
   TH1D *h1_min[4], *h1_max[4];

   if (infile) {
   
   TTree * t = (TTree*)infile->Get("Events");
   std::cout << "   entries in tree: " << t->GetEntries() << std::endl;

   TCut baseline = "1>0";
   TCut regionA, regionB, regionC, regionD;
   TString var, varmin, varmax;
   TString title;

   if (channel=="Muon") {
      title = "#mu + #tau_{h}";
      var = "MuTau_MaxCollMass:MuTau_MinCollMass";
      varmin = "MuTau_MinCollMass";
      varmax = "MuTau_MaxCollMass";
      //baseline = baseline && TCut("MuTau_HavePair>0 && (MuTau_HaveTriplet==0||(MuTau_HaveTriplet>0&&Photon_pt[MuTau_PhotonIdx]<25.))");
      baseline = baseline && TCut("MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=100.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("MuTau_Trigger");
      baseline = baseline && TCut("Muon_pfIsoId[MuTau_MuIdx]>=4");
      if (year==2016) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=26.");
      if (year==2017) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      if (year==2018) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      baseline = baseline && TCut("MuTau_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
      regionA = "MuTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionC = "MuTau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      if (blindA) regionA = regionA && TCut("Photon_pt[MuTau_PhotonIdx]<0.");
   }
   if (channel=="Tau") {
      title = "#tau_{h} + #tau_{h}";
      var = "TauTau_MaxCollMass:TauTau_MinCollMass";
      varmin = "TauTau_MinCollMass";
      varmax = "TauTau_MaxCollMass";
      //baseline = baseline && TCut("TauTau_HavePair>0 && (TauTau_HaveTriplet==0||(TauTau_HaveTriplet>0&&Photon_pt[TauTau_PhotonIdx]<25.))");
      baseline = baseline && TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=75.");
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
      regionA = TCut("TauTau_qq==-1") &&  (tau0pass&&tau1pass);
      regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      regionC = TCut("TauTau_qq==+1") &&  (tau0pass&&tau1pass);
      regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      if (blindA) regionA = regionA && TCut("Photon_pt[TauTau_PhotonIdx]<25.");
   }
   if (channel=="Electron") {
      title = "e + #tau_{h}";
      var = "ElTau_MaxCollMass:ElTau_MinCollMass";
      varmin = "ElTau_MinCollMass";
      varmax = "ElTau_MaxCollMass";
      //baseline = baseline && TCut("ElTau_HavePair>0 && (ElTau_HaveTriplet==0||(ElTau_HaveTriplet>0&&Photon_pt[ElTau_PhotonIdx]<25.))");
      baseline = baseline && TCut("ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]>=100.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("ElTau_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
      if (year==2016) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=29.");
      if (year==2017) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      if (year==2018) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      baseline = baseline && TCut("ElTau_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "ElTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionC = "ElTau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      if (blindA) regionA = regionA && TCut("Photon_pt[ElTau_PhotonIdx]<25.");
   }
   if (channel=="MuonEG") {
      title = "e + #mu";
      var = "ElMu_MaxCollMass:ElMu_MinCollMass";
      varmin = "ElMu_MinCollMass";
      varmax = "ElMu_MaxCollMass";
      //baseline = baseline && TCut("ElMu_HavePair>0 && (ElMu_HaveTriplet==0||(ElMu_HaveTriplet>0&&Photon_pt[ElMu_PhotonIdx]<25.))");
      baseline = baseline && TCut("ElMu_HaveTriplet>0 && Photon_pt[ElMu_PhotonIdx]>=100.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("ElMu_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElMu_ElIdx]");
      const TCut c1 = "Electron_pt[ElMu_ElIdx]>=24. && Muon_pt[ElMu_MuIdx]>=13.";
      const TCut c2 = "Electron_pt[ElMu_ElIdx]>=13. && Muon_pt[ElMu_MuIdx]>=24.";
      baseline = baseline && (c1||c2);
      baseline = baseline && TCut("ElMu_Mass>=100.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=2)==1");
      regionA = "ElMu_qq==-1 && Muon_pfIsoId[ElMu_MuIdx]>=4";
      regionB = "ElMu_qq==-1 && Muon_pfIsoId[ElMu_MuIdx]>=2 && Muon_pfIsoId[ElMu_MuIdx]<4";
      regionC = "ElMu_qq==+1 && Muon_pfIsoId[ElMu_MuIdx]>=4";
      regionD = "ElMu_qq==+1 && Muon_pfIsoId[ElMu_MuIdx]>=2 && Muon_pfIsoId[ElMu_MuIdx]<4";
      if (blindA) regionA = regionA && TCut("Photon_pt[ElMu_PhotonIdx]<25.");
   }

   const TCut cuts[4] = {baseline&&regionA, baseline&&regionB, baseline&&regionC, baseline&&regionD};
   const TString titles[4] = {"A", "B", "C", "D"};

   TH2D h2_temp("h2_temp", ";min collinear mass [GeV];max collinear mass [GeV]", 1000, 0., 1000., 1000, 0., 1000.);
   h2_temp.SetTitle(title);
   h2_temp.SetStats(0);

   TH1D h1_temp("h1_temp", ";collinear mass [GeV];events / 100 GeV", 10, 0., 1000.);
   h1_temp.SetLineWidth(2);
   h1_temp.SetStats(0);

   for (int i = 0; i < 4; ++i) {
      if (blindA && i==0) continue;
      std::cout << "   filling region " << titles[i] << std::endl;
      //2d
      char h2name[100];
      sprintf(h2name, "h2_%s", titles[i].Data());
      h2[i] = (TH2D*)h2_temp.Clone(h2name);
      //h2[i]->SetTitle(titles[i]);
      const int n = t->Project(h2[i]->GetName(), var, cuts[i]);
      std::cout << "      " << n << " entries" << std::endl;
      //1d min
      char h1minname[100];
      sprintf(h1minname, "h1min_%s", titles[i].Data());
      h1_min[i] = (TH1D*)h1_temp.Clone(h1minname);
      char buffer[100];
      sprintf(buffer, "%s: %s", titles[i].Data(), title.Data());
      h1_min[i]->SetTitle(buffer);
      t->Project(h1_min[i]->GetName(), varmin, cuts[i]);
      addOverflow(h1_min[i]);
      //1d max
      char h1maxname[100];
      sprintf(h1maxname, "h1max_%s", titles[i].Data());
      h1_max[i] = (TH1D*)h1_temp.Clone(h1maxname);
      h1_max[i]->SetTitle(buffer);
      t->Project(h1_max[i]->GetName(), varmax, cuts[i]);
      addOverflow(h1_max[i]);
   }
   } else {
      std::cout << "   file not found!" << std::endl;
   }

   outfile->Write();
   outfile->Close();
   return outfile;
}

void fillAllHists(const TString channel, const bool blindA=true)
{
   const TString letters_2018[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      char buffer[100];
      sprintf(buffer, "%s%s_2018", channel.Data(), letters_2018[i].Data());
      makeHists(buffer, 2018, channel, blindA);
   }
   char cmd2018[1000];
   sprintf(cmd2018, "hadd -f ./dataStudyOutput/%s_2018_full.root ./dataStudyOutput/%s*_2018.root", channel.Data(), channel.Data());
   system(cmd2018);

   const TString letters_2017[5] = {"B", "C", "D", "E", "F"};
   for (int i = 0; i < 5; ++i) {
      char buffer[100];
      sprintf(buffer, "%s%s_2017", channel.Data(), letters_2017[i].Data());
      makeHists(buffer, 2017, channel, blindA);
   }
   char cmd2017[1000];
   sprintf(cmd2017, "hadd -f ./dataStudyOutput/%s_2017_full.root ./dataStudyOutput/%s*_2017.root", channel.Data(), channel.Data());
   system(cmd2017);
 
   const TString letters_2016[7] = {"B", "C", "D", "E", "F", "G", "H"};
   for (int i = 0; i < 7; ++i) {
      char buffer[100];
      sprintf(buffer, "%s%s_2016", channel.Data(), letters_2016[i].Data());
      makeHists(buffer, 2016, channel, blindA);
   }
   char cmd2016[1000];
   sprintf(cmd2016, "hadd -f ./dataStudyOutput/%s_2016_full.root ./dataStudyOutput/%s*_2016.root", channel.Data(), channel.Data());
   system(cmd2016);
}

void yieldCompare(const TString channel, const bool blindA=true)
{
   const int years[3] = {2016, 2017, 2018};
   const double lumi[3] = {19.5+16.5, 41.48, 59.83};
   const double lumitot = lumi[0]+lumi[1]+lumi[2];
   int nA[3] = {0, 0, 0};
   int nB[3] = {0, 0, 0};
   int nC[3] = {0, 0, 0};
   int nD[3] = {0, 0, 0};
   int nAtot = 0;
   int nBtot = 0;
   int nCtot = 0;
   int nDtot = 0;
   double eA[3] = {0., 0., 0.};
   double eB[3] = {0., 0., 0.};
   double eC[3] = {0., 0., 0.};
   double eD[3] = {0., 0., 0.};
   double errA[3] = {0., 0., 0.};
   double errB[3] = {0., 0., 0.};
   double errC[3] = {0., 0., 0.};
   double errD[3] = {0., 0., 0.};

   for (int i = 0; i < 3; ++i) {
      char infile[100];
      sprintf(infile, "./dataStudyOutput/%s_%d_full.root", channel.Data(), years[i]);
      TFile * f = TFile::Open(infile);

      //A
      if (!blindA) {
         TH2D * hA = (TH2D*)f->Get("h2_A");
         nA[i] = hA->GetEntries();
         if (nA[i]!=hA->Integral()) {
            std::cout << "overflow: " << "A, " << years[i] << std::endl;
            std::cout << nA[i] << " " << hA->Integral() << std::endl;
         }
         nAtot += hA->GetEntries();
         eA[i] = double(nA[i])/lumi[i];
         errA[i] = sqrt(double(nA[i]))/lumi[i];
      }
      //B
      TH2D * hB = (TH2D*)f->Get("h2_B");
      nB[i] = hB->GetEntries();
      if (nB[i]!=hB->Integral()) {
         std::cout << "overflow: " << "B, " << years[i] << std::endl;
         std::cout << nB[i] << " " << hB->Integral() << std::endl;
      }
      nBtot += hB->GetEntries();
      eB[i] = double(nB[i])/lumi[i];
      errB[i] = sqrt(double(nB[i]))/lumi[i];
      //C
      TH2D * hC = (TH2D*)f->Get("h2_C");
      nC[i] = hC->GetEntries();
      if (nC[i]!=hC->Integral()) {
         std::cout << "overflow: " << "C, " << years[i] << std::endl;
         std::cout << nC[i] << " " << hC->Integral() << std::endl;
      }
      nCtot += hC->GetEntries();
      eC[i] = double(nC[i])/lumi[i];
      errC[i] = sqrt(double(nC[i]))/lumi[i];
      //D
      TH2D * hD = (TH2D*)f->Get("h2_D");
      nD[i] = hD->GetEntries();
      if (nD[i]!=hD->Integral()) {
         std::cout << "overflow: " << "D, " << years[i] << std::endl;
         std::cout << nD[i] << " " << hD->Integral() << std::endl;
      }
      nDtot += hD->GetEntries();
      eD[i] = double(nD[i])/lumi[i];
      errD[i] = sqrt(double(nD[i]))/lumi[i];
   }

   if (!blindA) {
      std::cout << "region A" << std::endl;
      std::cout << "  average: " << nAtot << " events; " << nAtot/lumitot << " +- " << sqrt(nAtot)/lumitot << std::endl;
      for (int i = 0; i < 3; ++i) {
         std::cout << "   " << years[i] << ": " << nA[i] << " events; " << eA[i] << "+-" << errA[i] << std::endl;
      }
   }

   std::cout << "region B" << std::endl;
   std::cout << "  average: " << nBtot << " events; " << nBtot/lumitot << " +- " << sqrt(nBtot)/lumitot << std::endl;
   for (int i = 0; i < 3; ++i) {
      std::cout << "   " << years[i] << ": " << nB[i] << " events; " << eB[i] << "+-" << errB[i] << std::endl;
   }

   std::cout << "region C" << std::endl;
   std::cout << "  average: " << nCtot << " events; " << nCtot/lumitot << " +- " << sqrt(nCtot)/lumitot << std::endl;
   for (int i = 0; i < 3; ++i) {
      std::cout << "   " << years[i] << ": " << nC[i] << " events; " << eC[i] << "+-" << errC[i] << std::endl;
   }  

   std::cout << "region D" << std::endl;
   std::cout << "  average: " << nDtot << " events; " << nDtot/lumitot << " +- " << sqrt(nDtot)/lumitot << std::endl;
   for (int i = 0; i < 3; ++i) {
      std::cout << "   " << years[i] << ": " << nD[i] << " events; " << eD[i] << "+-" << errD[i] << std::endl;
   }
}

void plotStuff(const TString channel)
{
   char cmd[100];
   sprintf(cmd, "hadd -f ./dataStudyOutput/%s.root ./dataStudyOutput/%s_2018_full.root ./dataStudyOutput/%s_2017_full.root ./dataStudyOutput/%s_2016_full.root", channel.Data(), channel.Data(), channel.Data(), channel.Data());
   system(cmd);
 
   char infile[100];
   sprintf(infile, "./dataStudyOutput/%s.root", channel.Data());
   TFile *f = TFile::Open(infile);

   TH2D * h2_B = (TH2D*)f->Get("h2_B");
   h2_B->SetMarkerColor(6);
   h2_B->SetMarkerStyle(20);
   TH2D * h2_C = (TH2D*)f->Get("h2_C");
   h2_C->SetMarkerColor(7);
   h2_C->SetMarkerStyle(20);
   TH2D * h2_D = (TH2D*)f->Get("h2_D");
   h2_D->SetMarkerColor(8);
   h2_D->SetMarkerStyle(20);

   TH1D *h1_minB = (TH1D*)f->Get("h1min_B");
   TH1D *h1_maxB = (TH1D*)f->Get("h1max_B");
   h1_minB->SetLineColor(6);
   h1_maxB->SetLineColor(7);

   TH1D *h1_minC = (TH1D*)f->Get("h1min_C");
   TH1D *h1_maxC = (TH1D*)f->Get("h1max_C");
   h1_minC->SetLineColor(6);
   h1_maxC->SetLineColor(7);

   TH1D *h1_minD = (TH1D*)f->Get("h1min_D");
   TH1D *h1_maxD = (TH1D*)f->Get("h1max_D");
   h1_minD->SetLineColor(6);
   h1_maxD->SetLineColor(7);

   TLegend * leg1 = new TLegend(0.6, 0.7, 0.875, 0.875);
   leg1->SetBorderSize(0);
   leg1->AddEntry(h1_minB, "min", "L");
   leg1->AddEntry(h1_maxB, "max", "L");

   TLegend * leg2 = new TLegend(0.5, 0.7, 0.875, 0.875);
   leg2->SetBorderSize(0);
   leg2->AddEntry(h2_B, "B: " + TString::Itoa(h2_B->GetEntries(), 10) + " entries", "P");
   leg2->AddEntry(h2_C, "C: " + TString::Itoa(h2_C->GetEntries(), 10) + " entries", "P");
   leg2->AddEntry(h2_D, "D: " + TString::Itoa(h2_D->GetEntries(), 10) + " entries", "P");

   TCanvas * c = new TCanvas("c", channel, 800, 800);
   c->Divide(2, 2);

   c->cd(1);
   h2_B->Draw("");
   //h2_B->SetTitle("");
   h2_C->Draw("SAME");
   h2_D->Draw("SAME");
   leg2->Draw();

   c->cd(2);
   h1_minB->Draw("HIST");
   h1_maxB->Draw("HIST, SAME");
   leg1->Draw();

   c->cd(3);
   h1_minC->Draw("HIST");
   h1_maxC->Draw("HIST, SAME");
   leg1->Draw();

   c->cd(4);
   h1_minD->Draw("HIST");
   h1_maxD->Draw("HIST, SAME");
   leg1->Draw();

   c->SaveAs("./plots/dataStudy."+channel+".pdf");
}

void dataStudy(const TString channel, const bool blindA=true)
{
   fillAllHists(channel, blindA);
   yieldCompare(channel, blindA);
   plotStuff(channel);
}

