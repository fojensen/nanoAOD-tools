#include <iomanip>
#include <iostream>
//#include <TFile.h>
#include <TChain.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH2D.h>
//#include <TH1D.h>
//#include "addOverflow.h"

class dataStudy {
   public:
      void run();
 bool blindA;

      TString channel;     
      TChain * chain[3];
      void chainInit();
      
      TH2D *h2_A[3], *h2_B[3], *h2_C[3], *h2_D[3];
      TH2D *h2_Asum, *h2_Bsum, *h2_Csum, *h2_Dsum;
   
      int n_A[3], n_B[3], n_C[3], n_D[3];
      int n_Asum, n_Bsum, n_Csum, n_Dsum;

      void histInit();
      void sumHists();
      
      void fillHists(const int year);
      void yieldCompare();
      void plotStuff();
};

void dataStudy::sumHists()
{
   h2_Asum = (TH2D*)h2_A[0]->Clone("h2_Asum");
   h2_Bsum = (TH2D*)h2_B[0]->Clone("h2_Bsum");
   h2_Csum = (TH2D*)h2_C[0]->Clone("h2_Csum");
   h2_Dsum = (TH2D*)h2_D[0]->Clone("h2_Dsum");
   for (int i = 1; i < 3; ++i) {
      h2_Asum->Add(h2_A[i]);
      h2_Bsum->Add(h2_B[i]);
      h2_Csum->Add(h2_C[i]);
      h2_Dsum->Add(h2_D[i]);  
   }
}

void dataStudy::fillHists(const int year)
{
   std::cout << "filling histograms for year: " << year << std::endl;
   
   TCut baseline = "1>0";
   TCut regionA, regionB, regionC, regionD;
   TString var;
   
   if (channel=="Electron") {
      var = "ElTau_MaxCollMass:ElTau_MinCollMass";
      //baseline = baseline && TCut("ElTau_HavePair>0 && (ElTau_HaveTriplet==0||(ElTau_HaveTriplet>0&&Photon_pt[ElTau_PhotonIdx]<95.))");
      //baseline = baseline && TCut("ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]>=50. && Photon_pt[ElTau_PhotonIdx]<95.");
      baseline = baseline && TCut("ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]>=100.");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("ElTau_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
      if (year==2016) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=29.");
      if (year==2017) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      if (year==2018) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      baseline = baseline && TCut("ElTau_Mass>=100.");
      /*********/baseline = baseline && TCut("32&Tau_idDeepTau2017v2p1VSe[ElTau_TauIdx]");/*********/
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "ElTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionC = "ElTau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      if (blindA) regionA = regionA && TCut("Photon_pt[ElTau_PhotonIdx]<100.");
   }
   if (channel=="Muon") {
      var = "MuTau_MaxCollMass:MuTau_MinCollMass";
      //baseline = baseline && TCut("MuTau_HavePair>0 && (MuTau_HaveTriplet==0||(MuTau_HaveTriplet>0&&Photon_pt[MuTau_PhotonIdx]<95.))");
      //baseline = baseline && TCut("MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=50. && Photon_pt[MuTau_PhotonIdx]<95.");
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
      if (blindA) regionA = regionA && TCut("Photon_pt[MuTau_PhotonIdx]<100.");
   }
   if (channel=="Tau") {
      var = "TauTau_MaxCollMass:TauTau_MinCollMass";
      //baseline = baseline && TCut("TauTau_HavePair>0 && (TauTau_HaveTriplet==0||(TauTau_HaveTriplet>0&&Photon_pt[TauTau_PhotonIdx]<70.))");
      //baseline = baseline && TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=25. && Photon_pt[TauTau_PhotonIdx]<70.");
      baseline = baseline && TCut("TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=75.");
      //baseline = baseline && TCut("JetProducer_nBJetT==0");
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
      //regionD = TCut("TauTau_qq==+1") && (tau0fail || tau1fail)
      if (blindA) regionA = regionA && TCut("Photon_pt[TauTau_PhotonIdx]<75.");
   } 
   if (channel=="MuonEG") {
      var = "ElMu_MaxCollMass:ElMu_MinCollMass";
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
      if (blindA) regionA = regionA && TCut("Photon_pt[ElMu_PhotonIdx]<100.");
   }

   const TCut cutsA = baseline&&regionA;
   const TCut cutsB = baseline&&regionB;
   const TCut cutsC = baseline&&regionC;
   const TCut cutsD = baseline&&regionD;

   if (year==2016) {
      if (!blindA) std::cout << chain[0]->Project("h2_A_2016", var, cutsA) << std::endl;
      std::cout << chain[0]->Project("h2_B_2016", var, cutsB) << std::endl;
      std::cout << chain[0]->Project("h2_C_2016", var, cutsC) << std::endl;
      std::cout << chain[0]->Project("h2_D_2016", var, cutsD) << std::endl;
   }
   if (year==2017) {
      if (!blindA) std::cout << chain[1]->Project("h2_A_2017", var, cutsA) << std::endl;
      std::cout << chain[1]->Project("h2_B_2017", var, cutsB) << std::endl;
      std::cout << chain[1]->Project("h2_C_2017", var, cutsC) << std::endl;
      std::cout << chain[1]->Project("h2_D_2017", var, cutsD) << std::endl;
   }
   if (year==2018) {
      if (!blindA) std::cout << chain[2]->Project("h2_A_2018", var, cutsA) << std::endl;
      std::cout << chain[2]->Project("h2_B_2018", var, cutsB) << std::endl;
      std::cout << chain[2]->Project("h2_C_2018", var, cutsC) << std::endl;
      std::cout << chain[2]->Project("h2_D_2018", var, cutsD) << std::endl;
   }

}

void dataStudy::chainInit()
{
   const TString letters_2018[4] = {"A", "B", "C", "D"};
   chain[2] = new TChain("Events");
   for (int i = 0; i < 4; ++i) {
      char fname[100];
      sprintf(fname, "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_12052021/%s%s_2018.root", channel.Data(), letters_2018[i].Data());
      chain[2]->Add(fname);
   }

   const TString letters_2017[5] = {"B", "C", "D", "E", "F"};
   chain[1] = new TChain("Events");
   for (int i = 0; i < 5; ++i) {
      char fname[100];
      sprintf(fname, "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_12052021/%s%s_2017.root", channel.Data(), letters_2017[i].Data());
      chain[1]->Add(fname);
   }
 
   const TString letters_2016[7] = {"B", "C", "D", "E", "F", "G", "H"};
   chain[0] = new TChain("Events");
   for (int i = 0; i < 7; ++i) {
      char fname[100];
      sprintf(fname, "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_12052021/%s%s_2016.root", channel.Data(), letters_2016[i].Data());
      chain[0]->Add(fname);
   }
}

void dataStudy::histInit()
{
   TH2D h2("h2", ";min collinear mass [GeV];max collinear mass [GeV]", 1000, 0., 1000., 1000, 0., 1000.);
   char title[20];
   if (channel=="Electron") sprintf(title, "e + #tau_{h}");
   if (channel=="Muon") sprintf(title, "#mu + #tau_{h}");
   if (channel=="Tau") sprintf(title, "#tau_{h} + #tau_{h}");
   h2.SetTitle(title);
   h2.SetStats(0);
   const TString years[3] = {"2016", "2017", "2018"}; 
   for (int i = 0; i < 3; ++i) {
      h2_A[i] = (TH2D*)h2.Clone("h2_A_"+years[i]);
      h2_B[i] = (TH2D*)h2.Clone("h2_B_"+years[i]);
      h2_C[i] = (TH2D*)h2.Clone("h2_C_"+years[i]);
      h2_D[i] = (TH2D*)h2.Clone("h2_D_"+years[i]);
   }
}

void dataStudy::yieldCompare()
{
   const int years[3] = {2016, 2017, 2018};
   const double lumi[3] = {36.33, 41.48, 59.83};
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
      //A
      if (!blindA) {
         nA[i] = h2_A[i]->GetEntries();
         if (nA[i]!=h2_A[i]->Integral()) {
            std::cout << "overflow: " << "A, " << years[i] << std::endl;
            std::cout << nA[i] << " " << h2_A[i]->Integral() << std::endl;
         }
         nAtot += h2_A[i]->GetEntries();
         eA[i] = double(nA[i])/lumi[i];
         errA[i] = sqrt(double(nA[i]))/lumi[i];
      }
      //B
      nB[i] = h2_B[i]->GetEntries();
      if (nB[i]!=h2_B[i]->Integral()) {
         std::cout << "overflow: " << "B, " << years[i] << std::endl;
         std::cout << nB[i] << " " << h2_B[i]->Integral() << std::endl;
      }
      nBtot += h2_B[i]->GetEntries();
      eB[i] = double(nB[i])/lumi[i];
      errB[i] = sqrt(double(nB[i]))/lumi[i];
      //C
      nC[i] = h2_C[i]->GetEntries();
      if (nC[i]!=h2_C[i]->Integral()) {
         std::cout << "overflow: " << "C, " << years[i] << std::endl;
         std::cout << nC[i] << " " << h2_C[i]->Integral() << std::endl;
      }
      nCtot += h2_C[i]->GetEntries();
      eC[i] = double(nC[i])/lumi[i];
      errC[i] = sqrt(double(nC[i]))/lumi[i];
      //D
      nD[i] = h2_D[i]->GetEntries();
      if (nD[i]!=h2_D[i]->Integral()) {
         std::cout << "overflow: " << "D, " << years[i] << std::endl;
         std::cout << nD[i] << " " << h2_D[i]->Integral() << std::endl;
      }
      nDtot += h2_D[i]->GetEntries();
      eD[i] = double(nD[i])/lumi[i];
      errD[i] = sqrt(double(nD[i]))/lumi[i];
   }

   std::cout << std::setprecision(3) << std::endl;
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

void dataStudy::plotStuff()
{
   h2_Asum->SetMarkerColor(6);
   h2_Asum->SetMarkerStyle(20);
   h2_Bsum->SetMarkerColor(7);
   h2_Bsum->SetMarkerStyle(20);
   h2_Csum->SetMarkerColor(8);
   h2_Csum->SetMarkerStyle(20);
   h2_Dsum->SetMarkerColor(9);
   h2_Dsum->SetMarkerStyle(20);

   TLegend * leg2 = new TLegend(0.6, 0.2, 0.875, 0.4);
   leg2->SetBorderSize(0);

   if (!blindA) { 
      leg2->AddEntry(h2_Asum, "A: " + TString::Itoa(h2_Asum->GetEntries(), 10) + " entries", "P");
   }
   leg2->AddEntry(h2_Bsum, "B: " + TString::Itoa(h2_Bsum->GetEntries(), 10) + " entries", "P");
   leg2->AddEntry(h2_Csum, "C: " + TString::Itoa(h2_Csum->GetEntries(), 10) + " entries", "P");
   leg2->AddEntry(h2_Dsum, "D: " + TString::Itoa(h2_Dsum->GetEntries(), 10) + " entries", "P");

   TCanvas * c = new TCanvas("c", channel, 400, 400); 
   if (!blindA) {
      h2_Asum->Draw("");
      h2_Bsum->Draw("SAME");
   } else {
      h2_Bsum->Draw("");
   }
   h2_Csum->Draw("SAME");
   h2_Dsum->Draw("SAME");
   leg2->Draw();

   char savetag[30];
   if (blindA) {
      sprintf(savetag, "./plots/dataStudy.%s.12052021.pdf", channel.Data());
   } else {
      sprintf(savetag, "./plots/dataStudy.%s.sidebandregion.pdf", channel.Data());
   }
   c->SaveAs(savetag);
}

void dataStudy::run()
{
   chainInit();
   histInit();
   fillHists(2016);
   fillHists(2017);
   fillHists(2018);
   sumHists();
   yieldCompare();
   plotStuff();
}

void dataStudyWrapper(const TString channel, const bool blindA=true)
{
   dataStudy d;
   d.channel = channel;
   d.blindA = blindA;
   d.run();
}

