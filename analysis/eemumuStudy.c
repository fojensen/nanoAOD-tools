#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TH1D.h>
#include <TCanvas.h>

void eemumuStudy()
{
   TCut baseline = "1>0";
   TCut regionA, regionB, regionC, regionD;
   const TString channel="Muon";
   const int year = 2018;

   if (channel=="Muon") {
      baseline = baseline && TCut("MuTau_HavePair>0 && MuTau_HaveTriplet==0");
      //baseline = baseline && TCut("MuTau_HaveTriplet>0");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      //baseline = baseline && TCut("Photon_pt[MuTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("MuTau_Mass>=91.1876");
      baseline = baseline && TCut("MuTau_Trigger");
      baseline = baseline && TCut("Muon_pfIsoId[MuTau_MuIdx]>=4");
      if (year==2016) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=26.");
      if (year==2017) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      if (year==2018) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
      regionA = "MuTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionC = "MuTau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   }

   TFile * f = TFile::Open("root://cmseos.fnal.gov///store/user/fojensen/cmsdas_22032021/DYJetsToEEMuMu_2018.root");
   TTree * t = (TTree*)f->Get("Events");

   TH1D * h_nMu = new TH1D("h_nMu", ";Sum$(Muon_genPartFlav==1);", 5, -0.5, 4.5);
   TH1D * h_nEl = new TH1D("h_nEl", ";Sum$(Electron_genPartFlav==1);", 5, -0.5, 4.5);

   char cutstring[2000];
   sprintf(cutstring, "xsWeight_Njets * (%s)", TString(baseline&&regionA).Data());
   
   t->Project(h_nMu->GetName(), "Sum$(Muon_genPartFlav==1)", cutstring);
   t->Project(h_nEl->GetName(), "Sum$(Electron_genPartFlav==1)", cutstring);

   TCanvas * c = new TCanvas("c", "", 800, 400);
   c->Divide(2,1);
   c->cd(1);
   h_nMu->Draw();
   c->cd(2);
   h_nEl->Draw();
}


