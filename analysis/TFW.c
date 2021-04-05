#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TCut.h>
#include "addOverflow.h"

void TFW()
{
   TH1D * h = new TH1D("h", ";m_{T} [GeV];events/ 40 GeV", 5, 0., 200.);
   h->SetStats(0);
   h->SetLineWidth(2);

   const TString fname_2016 = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/WJetsToLNu_2016.root";
   TFile * f_2016 = TFile::Open(fname_2016);
   TTree * t_2016;
   if (f_2016) {
      t_2016 = (TTree*)f_2016->Get("Events");
   } else {
      std::cout << "missing 2016" << std::endl;
   }
   TH1D * h_2016[4];

   const TString fname_2017 = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/WJetsToLNu_2017.root";
   TFile * f_2017 = TFile::Open(fname_2017);
   TTree * t_2017;
   if (f_2017) {
      t_2017 = (TTree*)f_2017->Get("Events");
   } else {
       std::cout << "missing 2017" << std::endl;
   }
   TH1D * h_2017[4];

   const TString fname_2018 = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/WJetsToLNu_2018.root";
   TFile * f_2018 = TFile::Open(fname_2018);
   TTree * t_2018;
   if (f_2018) {
      t_2018 = (TTree*)f_2018->Get("Events");
   } else {
      std::cout << "missing 2018" << std::endl;
   }
   TH1D * h_2018[4];

   TCut baseline = "MuTau_HaveTriplet>0";
   //baseline = baseline && TCut("JetProducer_nBJetT==0");
   //baseline = baseline && TCut("Photon_pt[MuTau_PhotonIdx]>=100.");
   //baseline = baseline && TCut("MuTau_Mass>=100.");
   //baseline = baseline && TCut("MuTau_Trigger");
   baseline = baseline && TCut("Muon_pfIsoId[MuTau_MuIdx]>=4");
   const TCut pt2016 = TCut("Muon_pt[MuTau_MuIdx]>=26.");
   const TCut pt2017 = TCut("Muon_pt[MuTau_MuIdx]>=29.");
   const TCut pt2018 = TCut("Muon_pt[MuTau_MuIdx]>=29.");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
   const TCut regionA = "MuTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   const TCut regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   const TCut regionC = "MuTau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   const TCut regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";

   const TCut cuts[4] = {baseline&&regionA, baseline&&regionB, baseline&&regionC, baseline&&regionD};
   const TString letters[4] = {"A", "B", "C", "D"};

   for (int i = 0; i < 4; ++i) {
      std::cout << "projections for region " << letters[i] << std::endl;
      //2016//
      h_2016[i] = (TH1D*)h->Clone("h_2016_"+letters[i]);
      h_2016[i]->SetTitle(letters[i]);
      if (f_2016) {
         std::cout << "   2016" << std::endl;
         char cuts2016[1000];
         sprintf(cuts2016, "36000. * xsWeight * (%s)", TString(cuts[i]&&pt2016).Data());
         std::cout << t_2016->Project(h_2016[i]->GetName(), "MuTau_mT", cuts2016) << std::endl;
         addOverflow(h_2016[i]);
      }
      //2017//
      h_2017[i] = (TH1D*)h->Clone("h_2017_"+letters[i]);
      h_2017[i]->SetTitle(letters[i]);
      if (f_2017) {
         std::cout << "   2017" << std::endl;
         char cuts2017[1000];
         sprintf(cuts2017, "41480. * xsWeight * (%s)", TString(cuts[i]&&pt2017).Data());
         std::cout << t_2017->Project(h_2017[i]->GetName(), "MuTau_mT", cuts2017) << std::endl;
         addOverflow(h_2017[i]);
      }
      //2018//
      h_2018[i] = (TH1D*)h->Clone("h_2018_"+letters[i]);
      h_2018[i]->SetTitle(letters[i]);
      if (f_2018) {
         std::cout << "   2018" << std::endl;
         char cuts2018[1000];
         sprintf(cuts2018, "59830. * xsWeight * (%s)", TString(cuts[i]&&pt2018).Data());
         std::cout << t_2018->Project(h_2018[i]->GetName(), "MuTau_mT", cuts2018) << std::endl;
         addOverflow(h_2018[i]);
      }
   }

   TH1D * h_A = (TH1D*)h_2016[0]->Clone("h_A");
   h_A->SetTitle("A");
   h_A->Add(h_2017[0]);
   h_A->Add(h_2018[0]);

   TH1D * h_B = (TH1D*)h_2016[1]->Clone("h_B");
   h_B->SetTitle("B");
   h_B->Add(h_2017[1]);
   h_B->Add(h_2018[1]);

   TH1D * h_C = (TH1D*)h_2016[2]->Clone("h_C");
   h_C->SetTitle("C");
   h_C->Add(h_2017[2]);
   h_C->Add(h_2018[2]);

   TH1D * h_D = (TH1D*)h_2016[3]->Clone("h_D");
   h_D->SetTitle("D");
   h_D->Add(h_2017[3]);
   h_D->Add(h_2018[3]); 

   TCanvas * c1 = new TCanvas("c1", "", 800, 800);
   c1->Divide(2, 2);
   c1->cd(1);
   h_A->Draw("HIST, E");
   h_A->SetMinimum(0.);
   c1->cd(2);
   h_B->Draw("HIST, E");
   h_B->SetMinimum(0.);
   c1->cd(3);
   h_C->Draw("HIST, E");
   h_C->SetMinimum(0.);
   c1->cd(4);
   h_D->Draw("HIST, E");
   h_D->SetMinimum(0.);

   TH1D * r = (TH1D*)h_C->Clone("r");
   h_C->GetYaxis()->SetTitle("C / D");
   h_C->SetTitle("");
   r->Divide(h_D);
   r->SetMarkerStyle(20);
   TCanvas * c2 = new TCanvas("c2", "", 400, 400);
   r->Draw("PE");
}

