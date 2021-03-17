#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH2D.h>

TFile * makeHists(const TString datatag, const int year, const TString shorttag)
{
   std::cout << "makeHists() " << datatag << std::endl;
   char finname[200];
   //sprintf(finname, "root://131.225.204.161:1094//store/user/fojensen/cmsdas_28022020/%s.root", datatag.Data());
   sprintf(finname, "root://131.225.204.161:1094//store/user/fojensen/cmsdas_08032020/%s.root", datatag.Data());
   TFile * infile = TFile::Open(finname);
   TTree * t = (TTree*)infile->Get("Events");
   std::cout << "   entries in tree: " << t->GetEntries() << std::endl;

   TCut baseline = "MuMu_HavePair==0||(MuMu_HavePair==1&&MuMu_Mass<50.)";
   baseline = baseline && TCut("EE_HavePair==0||(EE_HavePair==1&&EE_Mass<50.)");
   TCut regionA, regionB, regionC, regionD;
   TString var;
   TString title;

   if (shorttag=="Muon") {
      title = "#mu + #tau_{h}";
      var = "TMath::Max(MuTau_MuCollMass, MuTau_TauCollMass):TMath::Min(MuTau_MuCollMass, MuTau_TauCollMass)";
      baseline = baseline && TCut("MuTau_HaveTriplet>0");
      baseline = baseline && TCut("Photon_pt[MuTau_PhotonIdx]>=100.");
      baseline = baseline && TCut("MuTau_Mass>=100. && JetProducer_nBJetM==0");
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
      regionA = regionA && TCut("Photon_pt[MuTau_PhotonIdx]<50.");
   }
   if (shorttag=="Tau") {
      title = "#tau_{h} + #tau_{h}";
      var = "TMath::Max(TauTau_Tau0CollMass, TauTau_Tau1CollMass):TMath::Min(TauTau_Tau0CollMass, TauTau_Tau1CollMass)";
      baseline = baseline && TCut("TauTau_HaveTriplet>0");
      baseline = baseline && TCut("Photon_pt[TauTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("TauTau_Mass>=100. && JetProducer_nBJetM==0");
      baseline = baseline && TCut("TauTau_Mass>=91.1876 && JetProducer_nBJetT==0");
      baseline = baseline && TCut("TauTau_Trigger");
      baseline = baseline && TCut("Tau_pt[TauTau_Tau0Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1");
      baseline = baseline && TCut("Tau_pt[TauTau_Tau1Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      const TCut tau0pass = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau0fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau1pass = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      const TCut tau1fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      regionA = TCut("TauTau_qq==-1") &&  (tau0pass&&tau1pass);
      regionA = regionA && TCut("Photon_pt[TauTau_PhotonIdx]<50.");
      regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      regionC = TCut("TauTau_qq==+1") &&  (tau0pass&&tau1pass);
      regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   }
   if (shorttag=="Electron") {
      title = "e + #tau_{h}";
      var = "TMath::Max(ElTau_ElCollMass, ElTau_TauCollMass):TMath::Min(ElTau_ElCollMass, ElTau_TauCollMass)";
      baseline = baseline && TCut("ElTau_HaveTriplet>0");
      baseline = baseline && TCut("Photon_pt[ElTau_PhotonIdx]>=100.");
      baseline = baseline && TCut("ElTau_Mass>=100. && JetProducer_nBJetM==0");
      baseline = baseline && TCut("ElTau_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
      if (year==2016) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=29.");
      if (year==2017) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      if (year==2018) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionA = regionA && TCut("Photon_pt[ElTau_PhotonIdx]<50.");
      regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionC = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   }

   const TCut cuts[4] = {baseline&&regionA, baseline&&regionB, baseline&&regionC, baseline&&regionD};

   TH2D h_temp("h_temp", ";min collinear mass [GeV];max collinear mass [GeV]", 1000, 0., 1000., 1000, 0., 1000.);
   h_temp.SetTitle(title);
   h_temp.SetStats(0);

   char foutname[200];
   sprintf(foutname, "./outputHists/%s.root", datatag.Data());
   TFile * outfile = new TFile(foutname, "RECREATE");
   TH2D *h[4];
   const TString titles[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      if (i==0) continue;
      std::cout << "   filling region " << titles[i] << std::endl;
      char hname[100];
      sprintf(hname, "h_%s", titles[i].Data());
      h[i] = (TH2D*)h_temp.Clone(hname);
      h[i]->SetTitle(titles[i]);
      const int n = t->Project(h[i]->GetName(), var, cuts[i]);
      std::cout << "   # of events in projection: " << n << std::endl;
   }
   //outfile->Close();
   return outfile;
}

void data2d(const TString shorttag)
{
   TH2D h_temp("h_temp", ";min collinear mass [GeV];max collinear mass [GeV]", 1000, 0., 1000., 1000, 0., 1000.);
   if (shorttag=="Electron") h_temp.SetTitle("e + #tau_{h}");
   if (shorttag=="Muon") h_temp.SetTitle("#mu + #tau_{h}");
   if (shorttag=="Tau") h_temp.SetTitle("#tau_{h} + #tau_{h}");
   h_temp.SetStats(0);

   const TString letters_2016[7] = {"B", "C", "D", "E", "F_v1", "G", "H"};
   const TString letters_2017[7] = {"B", "C", "D", "E", "F"};
   const TString letters_2018[7] = {"A", "B", "C", "D"};

   //TH2D * h_sumA2018 = (TH2D*)h_temp.Clone("h_sumA2018");
   TH2D * h_sumB2018 = (TH2D*)h_temp.Clone("h_sumB2018");
   TH2D * h_sumC2018 = (TH2D*)h_temp.Clone("h_sumC2018");
   TH2D * h_sumD2018 = (TH2D*)h_temp.Clone("h_sumD2018");
   for (int i = 0; i < 4; ++i) {
      char buffer[100];
      sprintf(buffer, "%s%s_2018", shorttag.Data(), letters_2018[i].Data());
      TFile *f = makeHists(buffer, 2018, shorttag);
      //TH2D * h_A = (TH2D*)f->Get("h_A");
      TH2D * h_B = (TH2D*)f->Get("h_B");
      TH2D * h_C = (TH2D*)f->Get("h_C");
      TH2D * h_D = (TH2D*)f->Get("h_D");
      //h_sumA2018->Add(h_A);
      h_sumB2018->Add(h_B);
      h_sumC2018->Add(h_C);
      h_sumD2018->Add(h_D);
   }

   //TH2D * h_sumA2017 = (TH2D*)h_temp.Clone("h_sumA2017");
   TH2D * h_sumB2017 = (TH2D*)h_temp.Clone("h_sumB2017");
   TH2D * h_sumC2017 = (TH2D*)h_temp.Clone("h_sumC2017");
   TH2D * h_sumD2017 = (TH2D*)h_temp.Clone("h_sumD2017");
   for (int i = 0; i < 5; ++i) {
      char buffer[100];
      sprintf(buffer, "%s%s_2017", shorttag.Data(), letters_2017[i].Data());
      TFile * f = makeHists(buffer, 2017, shorttag);
      //TH2D * h_A = (TH2D*)f->Get("h_A");
      TH2D * h_B = (TH2D*)f->Get("h_B");
      TH2D * h_C = (TH2D*)f->Get("h_C");
      TH2D * h_D = (TH2D*)f->Get("h_D");
      //h_sumA2017->Add(h_A);
      h_sumB2017->Add(h_B);
      h_sumC2017->Add(h_C);
      h_sumD2017->Add(h_D);  
   }

   //TH2D * h_sumA2016 = (TH2D*)h_temp.Clone("h_sumA2016");
   TH2D * h_sumB2016 = (TH2D*)h_temp.Clone("h_sumB2016");
   TH2D * h_sumC2016 = (TH2D*)h_temp.Clone("h_sumC2016");
   TH2D * h_sumD2016 = (TH2D*)h_temp.Clone("h_sumD2016");
   for (int i = 0; i < 7; ++i) {
      char buffer[100];
      sprintf(buffer, "%s%s_2016", shorttag.Data(), letters_2016[i].Data());
      TFile * f = makeHists(buffer, 2016, shorttag);
      //TH2D * h_A = (TH2D*)f->Get("h_A");
      TH2D * h_B = (TH2D*)f->Get("h_B");
      TH2D * h_C = (TH2D*)f->Get("h_C");
      TH2D * h_D = (TH2D*)f->Get("h_D");
      //h_sumA2016->Add(h_A);
      h_sumB2016->Add(h_B);
      h_sumC2016->Add(h_C);
      h_sumD2016->Add(h_D);
   }

   /*TH2D * h_sumA = (TH2D*)h_sumA2016->Clone("h_sumA");
   h_sumA->Add(h_sumA2017);
   h_sumA->Add(h_sumA2018);
   h_sumA->SetMarkerStyle(20);
   h_sumA->SetMarkerColor(6);*/

   TH2D * h_sumB = (TH2D*)h_sumB2016->Clone("h_sumB");
   h_sumB->Add(h_sumB2017);
   h_sumB->Add(h_sumB2018);
   h_sumB->SetMarkerStyle(20);
   h_sumB->SetMarkerColor(7);

   TH2D * h_sumC = (TH2D*)h_sumC2016->Clone("h_sumC");
   h_sumC->Add(h_sumC2017);
   h_sumC->Add(h_sumC2018);
   h_sumC->SetMarkerStyle(20);
   h_sumC->SetMarkerColor(8);

   TH2D * h_sumD = (TH2D*)h_sumD2016->Clone("h_sumD");
   h_sumD->Add(h_sumD2017);
   h_sumD->Add(h_sumD2018);
   h_sumD->SetMarkerStyle(20);
   h_sumD->SetMarkerColor(9);

   TCanvas * c = new TCanvas("c", shorttag, 400, 400);

   //h_sumA->Draw("P");
   h_sumB->Draw("P, SAME");
   h_sumC->Draw("P, SAME");
   h_sumD->Draw("P, SAME");

   TLegend * l = new TLegend(0.5, 0.75, 0.875, 0.875);
   l->SetBorderSize(0);
   //l->AddEntry(h_sumA, "A: " + TString::Itoa(h_sumA->GetEntries(), 10), "P");
   l->AddEntry(h_sumB, "B: " + TString::Itoa(h_sumB->GetEntries(), 10), "P");
   l->AddEntry(h_sumC, "C: " + TString::Itoa(h_sumC->GetEntries(), 10), "P");
   l->AddEntry(h_sumD, "D: " + TString::Itoa(h_sumD->GetEntries(), 10), "P");
   l->Draw();   

   c->SaveAs("./plots/data2d_"+shorttag+".pdf");
}

