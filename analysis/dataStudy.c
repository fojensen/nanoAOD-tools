#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include "addOverflow.c"

TFile * makeHists(const TString datatag, const TString year, const TString shorttag)
{
   std::cout << "makeHists() " << datatag << " " << year << std::endl;
   char finname[200];
   sprintf(finname, "root://131.225.204.161:1094//store/user/fojensen/cmsdas_08032020/%s.root", datatag.Data());
   TFile * infile = TFile::Open(finname);
   TTree * t = (TTree*)infile->Get("Events");
   std::cout << "   entries in tree: " << t->GetEntries() << std::endl;

   TCut baseline = "MuMu_HavePair==0||(MuMu_HavePair==1&&MuMu_Mass<50.)";
   baseline = baseline && TCut("EE_HavePair==0||(EE_HavePair==1&&EE_Mass<50.)");
   baseline = baseline && TCut("JetProducer_nBJetM==0");
   TCut regionA, regionB, regionC, regionD;
   TString var;

   if (shorttag=="Muon") {
      var = "Photon_pt[MuTau_PhotonIdx]";
      baseline = baseline && TCut("MuTau_HaveTriplet>0");
      baseline = baseline && TCut("MuTau_Mass>=100.");
      baseline = baseline && TCut("MuTau_Trigger");
      baseline = baseline && TCut("Muon_pfIsoId[MuTau_MuIdx]>=4");
      if (year=="2016") baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=26.");
      if (year=="2017") baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      if (year=="2018") baseline = baseline && TCut("Muon_pt[MuTau_MuIdx]>=29.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
      regionA = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionA = regionA && TCut("Photon_pt[MuTau_PhotonIdx]<50.");
      regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionC = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
      regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   }
   if (shorttag=="Tau") {
      var = "Photon_pt[TauTau_PhotonIdx]";
      baseline = baseline && TCut("TauTau_HaveTriplet>0");
      baseline = baseline && TCut("TauTau_Mass>=100.");
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
      var = "Photon_pt[ElTau_PhotonIdx]";
      baseline = baseline && TCut("ElTau_HaveTriplet>0");
      baseline = baseline && TCut("ElTau_Mass>=100.");
      baseline = baseline && TCut("ElTau_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
      if (year=="2016") baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=29.");
      if (year=="2017") baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      if (year=="2018") baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionA = regionA && TCut("Photon_pt[ElTau_PhotonIdx]<50.");
      regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionC = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   }

   const TCut cuts[4] = {baseline&&regionA, baseline&&regionB, baseline&&regionC, baseline&&regionD};

   TH1D h_temp("h_temp", ";photon p_{T} [GeV];events / 10 GeV", 11, 0., 110.);
   h_temp.SetLineWidth(2);
   h_temp.SetStats(0);

   char foutname[200];
   sprintf(foutname, "./outputHists/%s.root", datatag.Data());
   TFile * outfile = new TFile(foutname, "RECREATE");
   TH1D *h[4];
   const TString titles[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      std::cout << "   filling region " << titles[i] << std::endl;
      char hname[100];
      sprintf(hname, "h_%s", titles[i].Data());
      h[i] = (TH1D*)h_temp.Clone(hname);
      h[i]->SetTitle(titles[i]);
      const int n = t->Project(h[i]->GetName(), var, cuts[i]);
      std::cout << "   # of events in projection: " << n << std::endl;
      addOverflow(h[i]);
   }
   h[0]->Write("h_A");
   h[1]->Write("h_B");
   h[2]->Write("h_C");
   h[3]->Write("h_D");
   //outfile->Close();
   return outfile;
}

void dataStudy(const TString shorttag)
{
   TH1D h_temp("h_temp", ";photon p_{T} [GeV];events / 10 GeV", 11, 0., 110.);
   h_temp.SetLineWidth(2);
   h_temp.SetStats(0);

   const TString letters_2016[7] = {"B", "C", "D", "E", "F_v1", "G", "H"};
   const double lumi_2016[7] = {5746.010/1000., 2572.903/1000., 4242.292/1000., 4025.228/1000., 3104.509/1000., 7575.579/1000., 8650.628/1000.};
   const double lumitot_2016 = 35917.149/1000.;

   const TString letters_2017[7] = {"B", "C", "D", "E", "F"};
   const double lumi_2017[5] = {4.823, 9.664, 4.252, 9.278, 13.540};
   const double lumitot_2017 = 4.823+9.664+4.252+9.278+13.540;

   const TString letters_2018[7] = {"A", "B", "C", "D"};
   const double lumi_2018[4] = {14.00, 7.10, 6.94, 31.93};
   const double lumitot_2018 = 14.00+7.10+6.94+31.93;

   TFile *f_2018[4];
   TH1D *h_2018A[4], *h_2018B[4], *h_2018C[4], *h_2018D[4];
   TH1D * h_sumA2018 = (TH1D*)h_temp.Clone("h_sumA2018");
   TH1D * h_sumB2018 = (TH1D*)h_temp.Clone("h_sumB2018");
   TH1D * h_sumC2018 = (TH1D*)h_temp.Clone("h_sumC2018");
   TH1D * h_sumD2018 = (TH1D*)h_temp.Clone("h_sumD2018");
   for (int i = 0; i < 4; ++i) {
      char buffer[100];
      sprintf(buffer, "%s_2018%s", shorttag.Data(), letters_2018[i].Data());
      f_2018[i] = makeHists(buffer, "2018", shorttag);
      //f_2018[i] = TFile::Open("./outputHists/"+tag_2018[i]+".root");
      h_2018A[i] = (TH1D*)f_2018[i]->Get("h_A");
      h_2018B[i] = (TH1D*)f_2018[i]->Get("h_B");
      h_2018C[i] = (TH1D*)f_2018[i]->Get("h_C");
      h_2018D[i] = (TH1D*)f_2018[i]->Get("h_D");
      h_sumA2018->Add(h_2018A[i]);
      h_sumB2018->Add(h_2018B[i]);
      h_sumC2018->Add(h_2018C[i]);
      h_sumD2018->Add(h_2018D[i]);
   }

   TFile *f_2017[5];
   TH1D *h_2017A[5], *h_2017B[5], *h_2017C[5], *h_2017D[5];
   TH1D * h_sumA2017 = (TH1D*)h_temp.Clone("h_sumA2017");
   TH1D * h_sumB2017 = (TH1D*)h_temp.Clone("h_sumB2017");
   TH1D * h_sumC2017 = (TH1D*)h_temp.Clone("h_sumC2017");
   TH1D * h_sumD2017 = (TH1D*)h_temp.Clone("h_sumD2017");
   for (int i = 0; i < 5; ++i) {
      char buffer[100];
      sprintf(buffer, "%s_2017%s", shorttag.Data(), letters_2017[i].Data());
      f_2017[i] = makeHists(buffer, "2017", shorttag);
      //f_2017[i] = TFile::Open("./outputHists/"+tag_2017[i]+".root");
      h_2017A[i] = (TH1D*)f_2017[i]->Get("h_A");
      h_2017B[i] = (TH1D*)f_2017[i]->Get("h_B");
      h_2017C[i] = (TH1D*)f_2017[i]->Get("h_C");
      h_2017D[i] = (TH1D*)f_2017[i]->Get("h_D");
      h_sumA2017->Add(h_2017A[i]);
      h_sumB2017->Add(h_2017B[i]);
      h_sumC2017->Add(h_2017C[i]);
      h_sumD2017->Add(h_2017D[i]);  
   }

   TFile *f_2016[7];
   TH1D *h_2016A[7], *h_2016B[7], *h_2016C[7], *h_2016D[7];
   TH1D * h_sumA2016 = (TH1D*)h_temp.Clone("h_sumA2016");
   TH1D * h_sumB2016 = (TH1D*)h_temp.Clone("h_sumB2016");
   TH1D * h_sumC2016 = (TH1D*)h_temp.Clone("h_sumC2016");
   TH1D * h_sumD2016 = (TH1D*)h_temp.Clone("h_sumD2016");
   for (int i = 0; i < 7; ++i) {
      char buffer[100];
      sprintf(buffer, "%s_2016%s", shorttag.Data(), letters_2016[i].Data());
      f_2016[i] = makeHists(buffer, "2016", shorttag);
      //f_2016[i] = TFile::Open("./outputHists/"+tag_2016[i]+".root");
      h_2016A[i] = (TH1D*)f_2016[i]->Get("h_A");
      h_2016B[i] = (TH1D*)f_2016[i]->Get("h_B");
      h_2016C[i] = (TH1D*)f_2016[i]->Get("h_C");
      h_2016D[i] = (TH1D*)f_2016[i]->Get("h_D");
      h_sumA2016->Add(h_2016A[i]);
      h_sumB2016->Add(h_2016B[i]);
      h_sumC2016->Add(h_2016C[i]);
      h_sumD2016->Add(h_2016D[i]);
   }

   TH1D * h_sumA = (TH1D*)h_sumA2016->Clone("h_sumA");
   h_sumA->Add(h_sumA2017);
   h_sumA->Add(h_sumA2018);

   TH1D * h_sumB = (TH1D*)h_sumB2016->Clone("h_sumB");
   h_sumB->Add(h_sumB2017);
   h_sumB->Add(h_sumB2018);

   TH1D * h_sumC = (TH1D*)h_sumC2016->Clone("h_sumC");
   h_sumC->Add(h_sumC2017);
   h_sumC->Add(h_sumC2018);

   TH1D * h_sumD = (TH1D*)h_sumD2016->Clone("h_sumD");
   h_sumD->Add(h_sumD2017);
   h_sumD->Add(h_sumD2018);

   TCanvas * c1 = new TCanvas("c1", shorttag, 800, 800);
   c1->Divide(2, 2);

   TPad * p11 = (TPad*)c1->cd(1);
   h_sumA->Draw("HIST");
   h_sumA->SetMinimum(0.1);
   h_sumA->SetMaximum(100000.);
   p11->SetLogy();

   TPad * p12 = (TPad*)c1->cd(2);
   h_sumB->Draw("HIST");
   h_sumB->SetMinimum(0.1);
   h_sumB->SetMaximum(100000.);
   p12->SetLogy();

   TPad * p13 = (TPad*)c1->cd(3);
   h_sumC->Draw("HIST");
   h_sumC->SetMinimum(0.1);
   h_sumC->SetMaximum(100000.);
   p13->SetLogy();

   TPad * p14 = (TPad*)c1->cd(4);
   h_sumD->Draw("HIST");
   h_sumD->SetMinimum(0.1);
   h_sumD->SetMaximum(100000.);
   p14->SetLogy();

   c1->SaveAs("./plots/"+shorttag+".collmass.pdf");

   TCanvas * c2 = new TCanvas("c2", shorttag, 800, 800);
   c2->Divide(2, 2);

   TPad * p21 = (TPad*)c2->cd(1);
   h_sumA2016->Scale(1./lumitot_2016);
   h_sumA2017->Scale(1./lumitot_2017);
   h_sumA2018->Scale(1./lumitot_2018);
   h_sumA2016->Draw("HIST, E");
   h_sumA2016->SetMinimum(0.01);
   h_sumA2016->SetMaximum(1000.);
   h_sumA2017->Draw("HIST, E, SAME");
   h_sumA2018->Draw("HIST, E, SAME");
   h_sumA2016->SetLineColor(6);
   h_sumA2017->SetLineColor(7);
   h_sumA2018->SetLineColor(8);
   p21->SetLogy();

   TLegend * l = new TLegend(0.5, 0.75, 0.875, 0.875);
   l->SetBorderSize(0);
   l->AddEntry(h_sumA2016, "2016", "L");
   l->AddEntry(h_sumA2017, "2017", "L");
   l->AddEntry(h_sumA2018, "2018", "L");
   l->Draw();

   TPad * p22 = (TPad*)c2->cd(2);
   h_sumB2016->Scale(1./lumitot_2016);
   h_sumB2017->Scale(1./lumitot_2017);
   h_sumB2018->Scale(1./lumitot_2018);
   h_sumB2016->Draw("HIST, E");
   h_sumB2016->SetMinimum(0.01);
   h_sumB2016->SetMaximum(1000.);
   h_sumB2017->Draw("HIST, E, SAME");
   h_sumB2018->Draw("HIST, E, SAME");
   h_sumB2016->SetLineColor(6);
   h_sumB2017->SetLineColor(7);
   h_sumB2018->SetLineColor(8);
   l->Draw();
   p22->SetLogy();

   TPad * p23 = (TPad*)c2->cd(3);
   h_sumC2016->Scale(1./lumitot_2016);
   h_sumC2017->Scale(1./lumitot_2017);
   h_sumC2018->Scale(1./lumitot_2018);
   h_sumC2016->Draw("HIST, E");
   h_sumC2016->SetMinimum(0.01);
   h_sumC2016->SetMaximum(100.);
   h_sumC2017->Draw("HIST, E, SAME");
   h_sumC2018->Draw("HIST, E, SAME");
   h_sumC2016->SetLineColor(6);
   h_sumC2017->SetLineColor(7);
   h_sumC2018->SetLineColor(8);
   l->Draw();
   p23->SetLogy();

   TPad * p24 = (TPad*)c2->cd(4);
   h_sumD2016->Scale(1./lumitot_2016);
   h_sumD2017->Scale(1./lumitot_2017);
   h_sumD2018->Scale(1./lumitot_2018);
   h_sumD2016->Draw("HIST, E");
   h_sumD2016->SetMinimum(0.01);
   h_sumD2016->SetMaximum(1000.);
   h_sumD2017->Draw("HIST, E, SAME");
   h_sumD2018->Draw("HIST, E, SAME");
   h_sumD2016->SetLineColor(6);
   h_sumD2017->SetLineColor(7);
   h_sumD2018->SetLineColor(8);
   l->Draw();
   p24->SetLogy();

   c2->SaveAs("./plots/"+shorttag+"_norm.pdf");
}

