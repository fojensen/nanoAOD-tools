#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TTree.h>
#include <TCut.h>
#include <iostream>
#include <TH1D.h>

TH1D* runPoint(const TString infile, const int mass)
{
   std::cout << "mass: " << mass << std::endl;
   TFile * f = TFile::Open(infile);
   TTree * t = (TTree*)f->Get("Events");

   const TCut cut_e = "Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0";
   const TCut cut_mu = "Sum$(Muon_pt>=20. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId)>0";
   const TCut cut_tau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (32&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>0";
   const TCut cut_photon = "Sum$(TMath::Abs(Photon_eta)<2.5 && Photon_mvaID_WP90 && (Photon_isScEtaEB||Photon_isScEtaEE) && Photon_electronVeto)>0";
   const TCut baseline = cut_e&&cut_mu&&cut_tau&&cut_photon;
   const double n_denom = t->GetEntries(baseline);
   std::cout << "n_denom: " << n_denom << std::endl;

   const TCut trigger_mu = "HLT_Mu50 && Sum$(Muon_pt>=50. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId)==1";
   const TCut trigger_isomu = "(HLT_IsoMu24||HLT_IsoMu27) && Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1";
   const TCut trigger_photon = "HLT_Photon200 && Sum$(Photon_pt>=200. && TMath::Abs(Photon_eta)<2.5 && Photon_mvaID_WP90 && (Photon_isScEtaEB||Photon_isScEtaEE) && Photon_electronVeto)==1";
   const TCut trigger_mutau_a = "HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1||HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1||HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_CrossL1||HLT_IsoMu20_eta2p1_MediumChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1||HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_CrossL1||HLT_IsoMu20_eta2p1_TightChargedIsoPFTauHPS27_eta2p1_TightID_CrossL1";
   const TCut trigger_mutau_b = "Sum$(Tau_pt>=27. && TMath::Abs(Tau_eta)<2.1 && Tau_decayMode!=5 && Tau_decayMode!=6 && (32&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))==1 && Sum$(Muon_pt>=20. && TMath::Abs(Muon_eta)<2.1 && Muon_tightId && Muon_pfIsoId>=4)==1";
   const TCut trigger_mutau = trigger_mutau_a && trigger_mutau_b;

   const double n_mu = t->GetEntries(baseline&&trigger_mu);
   const double n_isomu = t->GetEntries(baseline&&trigger_isomu);
   const double n_mutau = t->GetEntries(baseline&&trigger_mutau);
   const double n_photon = t->GetEntries(baseline&&trigger_photon);

   const double e_mu = n_mu/n_denom;
   const double e_isomu = n_isomu/n_denom;
   const double e_mutau = n_mutau/n_denom;
   const double e_photon = n_photon/n_denom;

   std::cout << "   e_mu: " << e_mu << "; " << n_mu << std::endl;
   std::cout << "   e_isomu: " << e_isomu << "; " << n_isomu << std::endl;
   std::cout << "   e_mutau: " << e_mutau << "; " << n_mutau << std::endl;
   std::cout << "   e_photon: " << e_photon << "; " << n_photon << std::endl;

   char hnumname[100];
   sprintf(hnumname, "h_num_%d", mass);
   TH1D * h_num = new TH1D(hnumname, "", 4, 0.5, 4.5);
   h_num->Sumw2();
   h_num->SetBinContent(1, n_mu);     h_num->SetBinError(1, sqrt(n_mu));
   h_num->SetBinContent(2, n_isomu);  h_num->SetBinError(2, sqrt(n_isomu));
   h_num->SetBinContent(3, n_mutau);  h_num->SetBinError(3, sqrt(n_mutau));
   h_num->SetBinContent(4, n_photon); h_num->SetBinError(4, sqrt(n_photon));

   char hdenomname[100];
   sprintf(hdenomname, "h_denom_%d", mass);
   TH1D * h_denom = new TH1D(hdenomname, "", 4, 0.5, 4.5);
   h_denom->Sumw2();
   h_denom->SetBinContent(1, n_denom); h_denom->SetBinError(1, sqrt(n_denom));
   h_denom->SetBinContent(2, n_denom); h_denom->SetBinError(2, sqrt(n_denom));
   h_denom->SetBinContent(3, n_denom); h_denom->SetBinError(3, sqrt(n_denom));
   h_denom->SetBinContent(4, n_denom); h_denom->SetBinError(4, sqrt(n_denom));

   char hname[100];
   sprintf(hname, "h_%d", mass);
   TH1D * h = new TH1D(hname, "", 4, 0.5, 4.5);
   h->Divide(h_num, h_denom, 1, 1, "B");
   return h;
}

void signalEfficiency()
{
   const int n = 6;

   const TString f_250 = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m250_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/7FEC7B94-611C-364A-9A12-B9BD43C01EC3.root"; 
   TH1D * h_250 = runPoint(f_250, 250);

   const TString f_500 = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m500_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/B97EF17B-4634-EB45-8776-BF8CAE1E634A.root";
   TH1D * h_500 = runPoint(f_500, 500);
 
   const TString f_1000 = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m1000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/270000/1E3560C2-B140-F34F-B24D-E7A1AD26CEC2.root";
   TH1D * h_1000 = runPoint(f_1000, 1000);

   const TString f_2000 = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m2000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/100000/0DEDC987-CDD7-7A43-B657-DDA4AEEDEC30.root";
   TH1D * h_2000 = runPoint(f_2000, 2000);

   const TString f_3000 = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m3000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/250000/2C47664A-8C31-6048-94BB-EA5C6AE7D2C6.root";
   TH1D * h_3000 = runPoint(f_3000, 3000);

   const TString f_5000 = "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m5000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/120000/44BFF07F-8D14-0347-B215-040F8D99B95B.root";
   TH1D * h_5000 = runPoint(f_5000, 5000);

   const int masses[n] = {250, 500, 1000, 2000, 3000, 5000};
   TH1D * hists[n] = {h_250, h_500, h_1000, h_2000, h_3000, h_5000};

   TGraphErrors * g_mu = new TGraphErrors(n);
   g_mu->SetMarkerColor(6);
   g_mu->SetMarkerStyle(20);

   TGraphErrors * g_isomu = new TGraphErrors(n);
   g_isomu->SetMarkerColor(7);
   g_isomu->SetMarkerStyle(20);

   TGraphErrors * g_mutau = new TGraphErrors(n);
   g_mutau->SetMarkerColor(8);
   g_mutau->SetMarkerStyle(20);

   TGraphErrors * g_photon = new TGraphErrors(n);
   g_photon->SetMarkerColor(9);
   g_photon->SetMarkerStyle(20);

   for (int i = 0; i < n; ++i) {
      g_mu->SetPoint(i, masses[i], hists[i]->GetBinContent(1));
      g_mu->SetPointError(i, 0., hists[i]->GetBinError(1));
      std::cout << hists[i]->GetBinError(1) << std::endl;
      g_isomu->SetPoint(i, masses[i], hists[i]->GetBinContent(2));
      g_isomu->SetPointError(i, 0., hists[i]->GetBinError(2));
      g_mutau->SetPoint(i, masses[i], hists[i]->GetBinContent(3));
      g_mutau->SetPointError(i, 0., hists[i]->GetBinError(3));
      g_photon->SetPoint(i, masses[i], hists[i]->GetBinContent(4));
      g_photon->SetPointError(i, 0., hists[i]->GetBinError(4));
   }

   TCanvas * c = new TCanvas("c", "", 400, 400);
  
   g_mu->SetTitle("#mu + #tau_{h};#tau* mass [GeV];signal efficiency"); 
   g_mu->Draw("APE");
   g_mu->SetMinimum(0.5);
   g_mu->SetMaximum(1.);
   g_isomu->Draw("PE, SAME");
   g_mutau->Draw("PE, SAME");
   g_photon->Draw("PE, SAME");

   TLegend * l = new TLegend(0.25, 0.2, 0.875, 0.3);
   l->SetNColumns(4);
   l->SetBorderSize(0);
   l->SetHeader("trigger selection");
   l->AddEntry(g_mu, "single #mu", "P");
   l->AddEntry(g_isomu, "single isolated #mu", "P");
   l->AddEntry(g_mutau, "#mu + #tau_{h}", "P");
   l->AddEntry(g_photon, "single photon", "P");
   l->Draw();
}

