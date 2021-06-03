#include <TCanvas.h>
#include <TFile.h>
#include <TChain.h>
#include <TCut.h>
#include <iostream>
#include <TH1D.h>

void getLeptonFR(const TString channel="Electron")
{
   std::cout << "getLeptonFR(): " << channel << std::endl;
   TChain * c = new TChain("Events");
   c->Add("root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/WJetsToLNu_2018.root");

   const TCut cut_denom = "Sum$(Tau_genPartFlav==5)==1";
   TCut cut_num;
   if (channel=="Electron") cut_num = "Sum$(Electron_mvaFall17V2Iso_WP90 && TMath::Abs(Electron_eta)<2.5 && Electron_pt>=12.)==1";
   if (channel=="Muon") cut_num = "Sum$(Muon_tightId && Muon_pfIsoId>=4 && TMath::Abs(Muon_eta)<2.4 && Muon_pt>=8.)==1";

   const double n_denom = c->GetEntries(cut_denom);
   const double n_num = c->GetEntries(cut_num && cut_denom);
   std::cout << "n_denom: " << n_denom << std::endl;
   std::cout << "n_num: " << n_num << std::endl;
   std::cout << "n_num/n_denom: " << n_num/n_denom << std::endl;
}

void getTauFR(const TString channel="Electron")
{
   std::cout << "getTauFR(): " << channel << std::endl;
   TChain * c = new TChain("Events");
   c->Add("root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/WJetsToLNu_2018.root");

   TCut cut_denom, cut_num;
   if (channel=="Electron") {
      cut_denom = "Sum$(Electron_genPartFlav==1||Electron_genPartFlav==15)==1";  
      cut_num = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (32&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (32&Tau_idDeepTau2017v2p1VSe) && Tau_genPartFlav!=1 && Tau_genPartFlav!=3)==1";
   }
   if (channel=="Muon") {
      cut_denom = "Sum$(Muon_genPartFlav==1||Muon_genPartFlav==15)==1";
      cut_num = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (32&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe) && Tau_genPartFlav!=2 && Tau_genPartFlav!=4)==1";
   }

   const double n_denom = c->GetEntries(cut_denom);
   const double n_num = c->GetEntries(cut_num && cut_denom);
   std::cout << "n_denom: " << n_denom << std::endl;
   std::cout << "n_num: " << n_num << std::endl;
   std::cout << "n_num/n_denom: " << n_num/n_denom << std::endl;
}

void fillYear(const int year, const TString channel, TH1D * h_faketau, TH1D * h_fakelepton)
{
   std::cout << "fillYear(): " << year << ", " << channel << std::endl;
   TChain * c = new TChain("Events");
   if (year==2015) c->Add("root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/WJetsToLNu_2015.root");
   if (year==2016) c->Add("root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/WJetsToLNu_2016.root");
   if (year==2017) c->Add("root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/WJetsToLNu_2017.root");
   if (year==2018) c->Add("root://cmseos.fnal.gov//store/user/fojensen/cmsdas_16042021/WJetsToLNu_2018.root");

   double lumi = 0.;
   if (year==2015) lumi = 19500.;
   if (year==2016) lumi = 16800.;
   //if (year==2016) lumi = 36330.;
   if (year==2017) lumi = 41480.;
   if (year==2018) lumi = 59830.;

   TCut baseline, regionA;
   TCut cut_faketau;
   TString var;
   if (channel=="Electron") {
      //var = "Photon_pt[ETau_EIdx]";
      var = "Tau_pt[ETau_TauIdx]";
      //var = "1.";
      baseline = baseline && TCut("ETau_HavePair>0");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ETau_EIdx]");
      if (year==2015||year==2016) baseline = baseline && TCut("Electron_pt[ETau_EIdx]>=29.");
      if (year==2017) baseline = baseline && TCut("Electron_pt[ETau_EIdx]>=34.");
      if (year==2018) baseline = baseline && TCut("Electron_pt[ETau_EIdx]>=34.");
      baseline = baseline && TCut("32&Tau_idDeepTau2017v2p1VSe[ETau_TauIdx]");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "ETau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[ETau_TauIdx])";
      cut_faketau = "Sum$(Electron_genPartFlav==1)==1 || Sum$(Electron_genPartFlav==15)==1";
   }
   if (channel=="Muon") {
      //var = "Photon_pt[MuTau_MuIdx]";
      var = "Tau_pt[MuTau_MuIdx]";
      //var = "1.";
      baseline = baseline && TCut("MuTau_HavePair>0");
      baseline = baseline && TCut("Muon_pfIsoId[MuTau_MuIdx]>=4");
      if (year==2015||year==2016) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=26.");
      if (year==2017) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      if (year==2018) baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
      regionA = "MuTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      cut_faketau = "Sum$(Muon_genPartFlav==1)==1 || Sum$(Muon_genPartFlav==15)==1";
   }

   TCut cut_fakelepton = "Sum$(Tau_genPartFlav==5)==1";
   cut_fakelepton = cut_fakelepton && baseline && regionA;
   cut_faketau = cut_faketau && baseline && regionA;

   char cuts1[2000];
   char h1name[100];
   sprintf(h1name, "+%s", h_faketau->GetName());
   sprintf(cuts1, "%f * xsWeight * (%s)", lumi, TString(cut_faketau).Data());
   std::cout << c->Project(h1name, var, cuts1) << std::endl;

   char cuts2[2000];
   char h2name[100];
   sprintf(h2name, "+%s", h_fakelepton->GetName());
   sprintf(cuts2, "%f * xsWeight * (%s)", lumi, TString(cut_fakelepton).Data());
   std::cout << c->Project(h2name, var, cuts2) << std::endl;
}

void WStudy(const TString channel = "Electron")
{ 
   //TH1D * h_faketau = new TH1D("h_faketau", ";photon p_{T};", 10, 0., 200);
   TH1D * h_faketau = new TH1D("h_faketau", ";#tau_{h} p_{T};", 10, 0., 200);
   //TH1D * h_faketau = new TH1D("h_faketau", ";the unit bin;", 1, 0.5, 1.5);
   h_faketau->SetLineWidth(2);
   h_faketau->SetStats(0);
   TH1D * h_fakelepton = (TH1D*)h_faketau->Clone("h_fakelepton"); 
   h_faketau->SetLineColor(6);
   h_fakelepton->SetLineColor(7);

   fillYear(2018, channel, h_faketau, h_fakelepton);
   fillYear(2017, channel, h_faketau, h_fakelepton);
   fillYear(2016, channel, h_faketau, h_fakelepton);
   fillYear(2015, channel, h_faketau, h_fakelepton);

   const double n_faketau = h_faketau->Integral();
   const double n_fakelepton = h_fakelepton->Integral();
   std::cout << "n_faketau: " << n_faketau << std::endl;
   std::cout << "n_fakelepton: " << n_fakelepton << std::endl;
   std::cout << "n_fakelepton/n_faketau: " << n_fakelepton/n_faketau << std::endl;

   TCanvas * canvas = new TCanvas("canvas", "", 800, 400);
   canvas->Divide(2, 1);

   TPad * p1 = (TPad*)canvas->cd(1);
   h_faketau->Draw("HIST, E, SAME");
   h_fakelepton->Draw("HIST, E");
   p1->SetLogy();
   h_fakelepton->SetMinimum(1.);
   h_fakelepton->SetMaximum(1000.);

   //TH1D * i_fakelepton = (TH1D*)h_fakelepton->Clone("i_fakelepton");
   //TH1D * i_faketau = (TH1D*)h_faketau->Clone("i_faketau");
   TPad * p2 = (TPad*)canvas->cd(2);
   TH1D * r = (TH1D*)h_fakelepton->Clone("r");
   r->Divide(h_faketau);
   r->Draw("PE");
   r->SetMinimum(0.0001);
   r->SetMaximum(1.);
   p2->SetLogy();
}

