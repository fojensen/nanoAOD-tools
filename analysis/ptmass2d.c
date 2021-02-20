#include <TCut.h>
#include <TH2D.h>
#include <TChain.h>
#include <TCanvas.h>
#include <iostream>
#include <TLegend.h>
#include <TH2D.h>

void runpoint(const TString datatag = "EGamma")
{
   std::cout << "running on " << datatag << std::endl;

   TChain * chain = new TChain("Events");
   TCut baseline, regionA, regionB, regionC, regionD;
   TString var, title;

   int nfiles = 0;

   if (datatag=="EGamma") {
   // e + tauh
   nfiles = chain->Add("root://cmseos.fnal.gov///store/user/fojensen/processedEmbedded_10211328/*ElTau*.root");
   var = "ElTau_Mass:Photon_pt[ElTau_PhotonIdx]";
   title = "e+#tau_{h}";
   baseline = "ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]>=32. && JetProducer_nBJetM==0 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   //baseline = baseline && TCut("ZProducer_EEHavePair==0 && ZProducer_MuMuHavePair==0");
   baseline = baseline && TCut("HLT_Ele32_WPTight_Gsf && Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
   baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=4)==0");
   regionA = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionC = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   }

   if (datatag=="SingleMuon") {
   // mu + tauh
   nfiles = chain->Add("root://cmseos.fnal.gov///store/user/fojensen/processedEmbedded_10211328/*MuTau*.root");
   var = "MuTau_Mass:Photon_pt[MuTau_PhotonIdx]";
   title = "#mu+#tau_{h}";
   baseline = "MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]>=32. && JetProducer_nBJetM==0 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   //baseline = baseline && TCut("ZProducer_EEHavePair==0 && ZProducer_MuMuHavePair==0");
   baseline = baseline && TCut("(HLT_IsoMu24||HLT_IsoMu27) && Muon_pfIsoId[MuTau_MuIdx]>=4");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=4)==1");
   regionA = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionC = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   }

   if (datatag=="Tau") {
   // tauh + tauh
   nfiles = chain->Add("root://cmseos.fnal.gov///store/user/fojensen/processedEmbedded_10211328/*TauTau*.root");
   var = "TauTau_Mass:Photon_pt[TauTau_PhotonIdx]";
   title = "#tau_{h}+#tau_{h}";
   baseline = "TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]>=32. && JetProducer_nBJetM==0";
   //baseline = baseline && TCut("ZProducer_EEHavePair==0 && ZProducer_MuMuHavePair==0");
   baseline = baseline && TCut("TauTau_Trigger");
   baseline = baseline && TCut("(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && Tau_pt[TauTau_Tau0Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1");
   baseline = baseline && TCut("(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && Tau_pt[TauTau_Tau1Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=4)==0");
   const TCut tau0pass = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
   const TCut tau0fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
   const TCut tau1pass = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
   const TCut tau1fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
   regionA = TCut("TauTau_qq==-1") &&  (tau0pass&&tau1pass);
   regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   regionC = TCut("TauTau_qq==+1") &&  (tau0pass&&tau1pass);
   regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   }

   TH2D * h2 = new TH2D("h2_"+datatag, ";photon p_{T} [GeV];visible mass [GeV]", 500, 0., 500., 500, 0., 500.);
   h2->SetMarkerStyle(20);
   h2->SetStats(0);

   const TCut cuts[4] = {baseline&&regionA, baseline&&regionB, baseline&&regionC, baseline&&regionD};
   //for (int i = 0; i < 4; ++i) std::cout << cuts[i] << std::endl;

   std::cout << "files in chain: " << nfiles << std::endl;
   const int n1 = chain->GetEntries();
   std::cout << "entries in chain: " << n1 << std::endl;

   TH2D * h[4];
   int n2[4] = {0,0,0,0};
   const TString labels[4] = {"A", "B", "C", "D"};
   const int colors[4] = {2, 3, 4, 5};
   TLegend * l = new TLegend(0.6, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   for (int i = 0; i < 4; ++i) {
      std::cout << "Region " << labels[i] << std::endl;
      h[i] = (TH2D*)h2->Clone("h_"+datatag+"_"+labels[i]);
      //char buffer[100];
      //sprintf(buffer, "%s; %s", title.Data(), labels[i].Data());
      h[i]->SetTitle(title);
      h[i]->SetMarkerColor(colors[i]);
      const int n2 = chain->Project(h[i]->GetName(), var, cuts[i]);
      std::cout << "   # of entries: " << n2 << std::endl;
      std::cout << "   Integral(): " << h[i]->Integral() << std::endl;
      l->AddEntry(h[i], labels[i], "P");
   }

   TCanvas * canvas = new TCanvas("canvas_"+datatag, datatag, 500, 500);
   for (int i = 3; i >=0; --i) {
      std::cout << "i: " << i << std::endl;
      h[i]->Draw("P, SAME");
   }
   l->Draw();

   /*TFile * fsig = TFile::Open("./outputData_2018/Taustar_m250.root");
   TTree * t_sig= (TTree*)fsig->Get("Events");  
   TH2D * sig = (TH2D*)h2->Clone("sig");
   const int n_sig = t_sig->Project("sig", var, regionA&&baseline);
   sig->SetMarkerColor(54);
   //l->AddEntry(sig, "A sig: " + TString::Itoa(n_sig, 10) + " events", "P");
   sig->Draw("P, SAME");
   sig->SetMarkerStyle(7);
   sig->SetMarkerColor(6);
   h2_A->Draw("P, SAME");*/

   canvas->SaveAs("./plots/ptmass2d."+datatag+".pdf");
}

void ptmass2d()
{
   runpoint("EGamma");
   runpoint("SingleMuon");
   runpoint("Tau");
}

