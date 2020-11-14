#include "addOverflow.h"
#include <TCut.h>
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
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
   baseline = baseline && TCut("(8&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx]) && Muon_pfIsoId[MuTauGamma_MuIdx]>=2");
   baseline = baseline && TCut("Tau_decayMode[MuTauGamma_TauIdx]!=5 && Tau_decayMode[MuTauGamma_TauIdx]!=6");
   baseline = baseline && TCut("JetProducer_nBJetT==0");
   baseline = baseline && TCut("MuTauGamma_MuTauMass>=91.1876");
   baseline = baseline && TCut("Muon_pfIsoId[MuTauGamma_MuIdx]>=4");
   //baseline = baseline && TCut("JetProducer_nBJetT>0 || MuTauGamma_MuTauMass<91.1876 || Muon_pfIsoId[MuTauGamma_MuIdx]>=2&&Muon_pfIsoId[MuTauGamma_MuIdx]<4");
   baseline = baseline && TCut("MuTauGamma_haveTriplet>0 && Photon_pt[MuTauGamma_PhotonIdx]>=100.");
   baseline = baseline && TCut("Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter");

   baseline = baseline && TCut("MuTauGamma_MuTauMass>=100.");
   baseline = baseline && TCut("MuTauGamma_MuGammaDeltaR>=0.7 && MuTauGamma_TauGammaDeltaR>=0.7");
   baseline = baseline && TCut("Muon_tightId[MuTauGamma_MuIdx]");
   baseline = baseline && TCut("32&Tau_idDeepTau2017v2p1VSe[MuTauGamma_TauIdx]");
   baseline = baseline && TCut("Photon_isScEtaEB[MuTauGamma_PhotonIdx]||Photon_isScEtaEE[MuTauGamma_PhotonIdx]");

   const TCut regionB = "MuTauGamma_qq==+1 &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionC = "MuTauGamma_qq==-1 && !(32&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionD = "MuTauGamma_qq==+1 && !(32&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regions = regionB || regionC || regionD;

   //TFile * f = TFile::Open("./outputData_2018/SingleMuon.root"); const TString tag = "SingleMuon";
   TFile * f = TFile::Open("./outputData_2018/Embedded.root"); const TString tag = "Embedded";
   TTree * t_ = (TTree*)f->Get("Events");

   std::cout << "CopyTree()" << std::endl;
   TTree * t = (TTree*)t_->CopyTree(baseline);

   TH2D * h2_B = new TH2D("h2_B", ";min collinear mass [GeV];max collinear mass [GeV]", 1000, 0., 1000., 1000, 0., 1000.);
   h2_B->SetMarkerStyle(20);
   h2_B->SetStats(0);
   TH2D * h2_C = (TH2D*)h2_B->Clone("h2_C");
   TH2D * h2_D = (TH2D*)h2_B->Clone("h2_D");
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

   //TH1D * h_min = new TH1D("h_min", ";min collinear mass [GeV];events / 100 GeV", 10, 0., 1000.);
   //t->Project("h_min", "TMath::Min(MuTauGamma_MuGammaCollinearMass, MuTauGamma_TauGammaCollinearMass)", baseline && regions);
   //addOverflow(h_min);

   //TH1D * h_max = new TH1D("h_max", ";max collinear mass [GeV];events / 200 GeV", 10, 0., 2000.);
   //t->Project("h_max", "TMath::Max(MuTauGamma_MuGammaCollinearMass, MuTauGamma_TauGammaCollinearMass)", baseline && regions);
   //addOverflow(h_max);

   //TCanvas * c = new TCanvas("c", "", 800, 800);
   //c->Divide(2, 2);
   TCanvas * c = new TCanvas("c", "", 500, 500);

   //c->cd(2);
   h2_C->Draw("P");
   h2_D->Draw("P, SAME");
   h2_B->Draw("P, SAME");

   TLegend * l = new TLegend(0.4, 0.175, 0.875, 0.3);
   l->SetBorderSize(0);
   l->AddEntry(h2_B, "B: " + TString::Itoa(n_B, 10) + " events", "P");
   l->AddEntry(h2_C, "C: " + TString::Itoa(n_C, 10) + " events", "P");
   l->AddEntry(h2_D, "D: " + TString::Itoa(n_D, 10) + " events", "P");
   l->Draw();

/*   TPad * p3 = (TPad*)c->cd(3);
   h_min->Draw("HIST, E");
   h_min->SetLineWidth(2);
   p3->SetLogy();

   TPad * p4 = (TPad*)c->cd(4);
   h_max->Draw("HIST, E");
   h_max->SetLineWidth(2);
   p4->SetLogy();*/

   c->SaveAs("./plots/datacryields."+tag+".vm100.mgtg0p7.mti.tighte.ebee.lowtau.pdf");

   return (n_B+n_C+n_D);
}

