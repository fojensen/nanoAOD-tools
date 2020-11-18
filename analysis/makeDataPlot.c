#include <TCut.h>
#include <TFile.h>
#include <TH2D.h>
#include <TTree.h>
#include <TCanvas.h>
#include <iostream>
#include <TLegend.h>

int makeDataPlot()
{
   TCut baseline = "1>0";
   baseline = baseline && TCut("MuTauGamma_havePair>0");
   baseline = baseline && TCut("Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=2)<2");
   baseline = baseline && TCut("MuTauGamma_trigger");
   baseline = baseline && TCut("(8&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])");
   baseline = baseline && TCut("Tau_decayMode[MuTauGamma_TauIdx]!=5 && Tau_decayMode[MuTauGamma_TauIdx]!=6");
   baseline = baseline && TCut("JetProducer_nBJetT==0");
   baseline = baseline && TCut("MuTauGamma_MuTauMass>=91.1876");
   baseline = baseline && TCut("Muon_pfIsoId[MuTauGamma_MuIdx]>=4");
   baseline = baseline && TCut("MuTauGamma_haveTriplet>0 && Photon_pt[MuTauGamma_PhotonIdx]>=100.");
   baseline = baseline && TCut("Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter");

   baseline = baseline && TCut("Photon_isScEtaEB[MuTauGamma_PhotonIdx]||Photon_isScEtaEE[MuTauGamma_PhotonIdx]");
   baseline = baseline && TCut("MuTauGamma_MuTauMass>=100.");
   baseline = baseline && TCut("Tau_pt[MuTauGamma_TauIdx]>=30.");
   baseline = baseline && TCut("MuTauGamma_MuGammaDeltaR>=0.7 && MuTauGamma_TauGammaDeltaR>=0.7");
   baseline = baseline && TCut("(32&Tau_idDeepTau2017v2p1VSe[MuTauGamma_TauIdx])");
   baseline = baseline && TCut("Muon_tightId[MuTauGamma_MuIdx]");

   const TCut regionB = "MuTauGamma_qq==+1 &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionC = "MuTauGamma_qq==-1 && !(32&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionD = "MuTauGamma_qq==+1 && !(32&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";

   //TFile * f = TFile::Open("./outputData_2018/SingleMuon.root"); const TString tag = "SingleMuon";
   TFile * f = TFile::Open("./outputData_2018/Embedded.root"); const TString tag = "Embedded";
   //TFile * f = TFile::Open("./outputData_2018/Taustar_m250.root"); const TString tag = "taustar_m250";
   TTree * t_ = (TTree*)f->Get("Events");

   std::cout << "CopyTree()" << std::endl;
   TTree * t = (TTree*)t_->CopyTree(baseline);

   TH2D * h2 = new TH2D("h2", ";min collinear mass [GeV];max collinear mass [GeV]", 1000, 0., 1000., 1000, 0., 1000.);
   h2->SetMarkerStyle(20);
   h2->SetStats(0);
   TH2D * h2_B = (TH2D*)h2->Clone("h2_B");
   TH2D * h2_C = (TH2D*)h2->Clone("h2_C");
   TH2D * h2_D = (TH2D*)h2->Clone("h2_D");
   h2_B->SetMarkerColor(223);
   h2_C->SetMarkerColor(207);
   h2_D->SetMarkerColor(209);

   const TString var = "TMath::Max(MuTauGamma_MuGammaCollinearMass, MuTauGamma_TauGammaCollinearMass):TMath::Min(MuTauGamma_MuGammaCollinearMass, MuTauGamma_TauGammaCollinearMass)";
   std::cout << "Project()" << std::endl;
   const int n_B = t->Project("h2_B", var, regionB);
   std::cout << "Project()" << std::endl;
   const int n_C = t->Project("h2_C", var, regionC);
   std::cout << "Project()" << std::endl;
   const int n_D = t->Project("h2_D", var, regionD);
   int ntot = n_B + n_C + n_D;

   TCanvas * c = new TCanvas("c", "", 500, 500);

   h2_C->Draw("P");
   h2_D->Draw("P, SAME");
   h2_B->Draw("P, SAME");

   TLegend * l = new TLegend(0.5, 0.175, 0.875, 0.4);
   l->SetBorderSize(0);
   l->AddEntry(h2_B, "B: " + TString::Itoa(n_B, 10) + " events", "P");
   l->AddEntry(h2_C, "C: " + TString::Itoa(n_C, 10) + " events", "P");
   l->AddEntry(h2_D, "D: " + TString::Itoa(n_D, 10) + " events", "P");

   TH2D * h2_A = (TH2D*)h2->Clone("h2_A");
   if (tag=="Embedded" || tag=="taustar_m250") {
      const TCut regionA = "MuTauGamma_qq==-1 && (64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
      TH2D * h2_A = (TH2D*)h2->Clone("h2_A");
      std::cout << "Project()" << std::endl;
      const int n_A = t->Project("h2_A", var, regionA);
      h2_A->SetMarkerColor(7);
      l->AddEntry(h2_A, "A: " + TString::Itoa(n_A, 10) + " events", "P");
      h2_A->Draw("P, SAME");
      ntot = ntot + n_A;
   }

   l->Draw();
   c->SaveAs("./plots/datacryields."+tag+".eeeb.m100.pt30.dr0p7.tighte.tightmu.lowtau.pdf");

   return ntot;
}

