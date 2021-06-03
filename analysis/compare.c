#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <TCut.h>
#include <TCanvas.h>
#include <TH1D.h>

TString makeVar(const double mass, const TString channel)
{std::cout << "makeVar() " <<  mass << " " << channel << std::endl;

   char outstring[1000];
   const double upper=mass+0.25*mass;
   const double lower=mass-0.25*mass;

   if (channel=="Electron") {
      sprintf(outstring,
      "(ETau_MaxCollMass<%f)?1 : (ETau_MinCollMass>=%f)?4 : (ETau_MaxCollMass>=%f&&ETau_MinCollMass<%f)?3 : ((ETau_MaxCollMass>=%f&&ETau_MaxCollMass<%f)||(ETau_MinCollMass>=%f&&ETau_MinCollMass<%f))?2 : 0",
                          lower,                      upper,                      upper,                lower,                       lower,                upper,                   lower,                upper
      );
   }
   if (channel=="Muon") {
      sprintf(outstring,
      "(MuTau_MaxCollMass<%f)?1 : (MuTau_MinCollMass>=%f)?4 : (MuTau_MaxCollMass>=%f&&MuTau_MinCollMass<%f)?3 : ((MuTau_MaxCollMass>=%f&&MuTau_MaxCollMass<%f)||(MuTau_MinCollMass>=%f&&MuTau_MinCollMass<%f))?2 : 0",
                          lower,                      upper,                      upper,                lower,                       lower,                upper,                   lower,                upper
      );
   }
   if (channel=="Tau") {
      sprintf(outstring,
      "(TauTau_MaxCollMass<%f)?1 : (TauTau_MinCollMass>=%f)?4 : (TauTau_MaxCollMass>=%f&&TauTau_MinCollMass<%f)?3 : ((TauTau_MaxCollMass>=%f&&TauTau_MaxCollMass<%f)||(TauTau_MinCollMass>=%f&&TauTau_MinCollMass<%f))?2 : 0",
                           lower,                       upper,                       upper,                 lower,                        lower,                 upper,                    lower,                 upper
      );
   }
   if (channel=="MuonEG") {
      sprintf(outstring,
      "(ElMu_MaxCollMass<%f)?1 : (ElMu_MinCollMass>=%f)?4 : (ElMu_MaxCollMass>=%f&&ElMu_MinCollMass<%f)?3 : ((ElMu_MaxCollMass>=%f&&ElMu_MaxCollMass<%f)||(ElMu_MinCollMass>=%f&&ElMu_MinCollMass<%f))?2 : 0",
                           lower,                       upper,                       upper,                 lower,                        lower,                 upper,                    lower,                 upper
      );
   }

   std::cout << "end makeString()" << std::endl;
   return TString(outstring);
}

void compare(const TString channel)
{
   const int year = 2018;
   const bool blindA = false;
   TCut baseline;
   TCut regionA, regionB, regionC, regionD;
      if (channel=="Electron") {
      //title = "e + #tau_{h}";
      //var = "ETau_MaxCollMass:ETau_MinCollMass";
      //varmin = "ETau_MinCollMass";
      //varmax = "ETau_MaxCollMass";
      //baseline = baseline && TCut("ETau_HavePair>0 && (ETau_HaveTriplet==0||(ETau_HaveTriplet>0&&Photon_pt[ETau_PhotonIdx]<25.))");
      baseline = baseline && TCut("ETau_HaveTriplet>0 && Photon_pt[ETau_PhotonIdx]>=0.");
      //baseline = baseline && TCut("JetProducer_nBJetT==0");
      //baseline = baseline && TCut("ETau_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ETau_EIdx]");
//      if (year==2016) baseline = baseline && TCut("Electron_pt[ETau_EIdx]>=20.");
  //    if (year==2017) baseline = baseline && TCut("Electron_pt[ETau_EIdx]>=34.");
    //  if (year==2018) baseline = baseline && TCut("Electron_pt[ETau_EIdx]>=34.");
      //baseline = baseline && TCut("ETau_Mass>=100.");
      /*********/baseline = baseline && TCut("32&Tau_idDeepTau2017v2p1VSe[ETau_TauIdx]");/*********/
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "ETau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx])";
      regionB = "ETau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx])";
      regionC = "ETau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx])";
      regionD = "ETau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx])";
      //if (blindA) regionA = regionA && TCut("Photon_pt[ETau_PhotonIdx]<25.");
   }

   const TString var = makeVar(1000, channel);
   std::cout << "var: " << var << std::endl;

   TFile * f1 = TFile::Open("../crab/sig_m1000_f0p1_fprime0p1_Skim.root");
   TTree * t1 = (TTree*)f1->Get("Events");
   TH1D * h1 = new TH1D("h1", ";analysis bin;events / bin", 5, -0.5, 4.5);
   h1->SetStats(0);
   h1->SetLineWidth(2);
   h1->Sumw2();
   const double n1 = t1->Project("h1", var, baseline&&regionA);
   std::cout << "n1: " << n1 << std::endl;
   h1->Scale(1./n1);

   TFile * f2 = TFile::Open("../crab/sig_m1000_f1_fprime0p1_Skim.root");
   TTree * t2 = (TTree*)f2->Get("Events");
   TH1D * h2 = new TH1D("h2", ";analysis bin;events / bin", 5, -0.5, 4.5);
   h2->SetStats(0);
   h2->SetLineWidth(2);
   h2->Sumw2();
   const double n2 = t2->Project("h2", var, baseline&&regionA);
   std::cout << "n2: " << n2 << std::endl;
   h2->Scale(1./n2);

   TH1D * hr = (TH1D*)h2->Clone("hr");
   hr->Divide(h1);

   TCanvas * c = new TCanvas("c", channel, 800, 400);
   c->Divide(2, 1);

   TPad * p1 = (TPad*)c->cd(1);
   h1->Draw("HIST, E");
   h1->SetMinimum(0.001);
   h1->SetMaximum(1.);
   p1->SetLogy();
   h2->Draw("HIST, E, SAME");

   c->cd(2);
   hr->SetMarkerSize(2);
   hr->Draw("TEXT, E");

   for (int i = 0; i < 5; ++i) {
      std::cout << "i: " << i << std::endl;
      std::cout << h1->GetBinContent(i+1) << " +- " << h1->GetBinError(i+1) << std::endl;
      std::cout << h2->GetBinContent(i+1) << " +- " << h2->GetBinError(i+1) << std::endl;
      std::cout << hr->GetBinContent(i+1) << " +- " << hr->GetBinError(i+1) << std::endl;
   }

}

