#include <TLine.h>
#include <iostream>
#include <THStack.h>
#include <TCut.h>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include "addOverflow.h"
#include <TString.h>

TString makeString(const double mass, const TString channel)
{
   std::cout << "makeString()" << std::endl;
   std::cout << "   mass: " << mass << ", channel: " << channel << std::endl;
   char outstring[1000];
   const double upper=mass+100.;
   const double lower=mass-100.;
   
   if (channel=="Electron") {
      sprintf(outstring,
      "(ElTau_MaxCollMass<%f)?1 : (ElTau_MinCollMass>=%f)?4 : (ElTau_MaxCollMass>=%f&&ElTau_MinCollMass<%f)?3 : ((ElTau_MaxCollMass>=%f&&ElTau_MaxCollMass<%f)||(ElTau_MinCollMass>=%f&&ElTau_MinCollMass<%f))?2 : 0",
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

   std::cout << "end makeString()" << std::endl;
   return TString(outstring);
}

TFile * runPoint(const TString sampletag, const TString channel, const int year, const bool isMC, const bool blindA)
{
   std::cout << "runPoint()" << std::endl;
   std::cout << "   sampletag: " << sampletag << ", channel: " << channel << ", year: " << year << ", isMC: " << isMC << ", blindA: " << blindA << std::endl;

   char hname[100];
   sprintf(hname, "h_%s_%s_%d", sampletag.Data(), channel.Data(), year);
   //TH1D * h = new TH1D(hname, ";min collinear mass;events / 250 GeV", 4, 0., 1000.);
   //TH1D * h = new TH1D(hname, ";analysis bin;events", 5, -0.5, 4.5);
   TH1D * h = new TH1D(hname, ";visible mass [GeV];events / 10 GeV", 20, 0., 200.);
   h->Sumw2();
   //h->SetLineWidth(2);

   const TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/";
   char infile[100];
   sprintf(infile, "%s/%s_%d.root", eostag.Data(), sampletag.Data(), year);
   TFile * f = TFile::Open(infile);

   TString title = "";
   if (channel=="Electron") title = "e + #tau_{h}";
   if (channel=="Muon") title = "#mu + #tau_{h}";
   if (channel=="Tau") title = "#tau_{h} + #tau_{h}";
   TH1D * h_A = (TH1D*)h->Clone(TString(h->GetName())+"_A");
   h_A->SetTitle("A: " + title);
   TH1D * h_B = (TH1D*)h->Clone(TString(h->GetName())+"_B");
   h_B->SetTitle("B: " + title);
   TH1D * h_C = (TH1D*)h->Clone(TString(h->GetName())+"_C");
   h_C->SetTitle("C: " + title);
   TH1D * h_D = (TH1D*)h->Clone(TString(h->GetName())+"_D");
   h_D->SetTitle("D: " + title);

   if (f) {

   TString var;
   var = makeString(375., channel);
   //if (channel=="Electron") var = "TMath::Min(ElTau_ElCollMass, ElTau_TauCollMass)";
   //if (channel=="Muon") var = "TMath::Min(MuTau_MuCollMass, MuTau_TauCollMass)";
   //if (channel=="Tau") "TMath::Min(TauTau_Tau0CollMass, TauTau_Tau1CollMass)";
   var = "MuTau_Mass";
   
   TCut baseline = "1>0";
   TCut regionA, regionB, regionC, regionD; 

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
   if (channel=="Tau") {
      baseline = baseline && TCut("TauTau_HavePair>0 && TauTau_HaveTriplet==0");
      //baseline = baseline && TCut("TauTau_HaveTriplet>0");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      //baseline = baseline && TCut("Photon_pt[TauTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("TauTau_Mass>=91.1876");
      baseline = baseline && TCut("TauTau_Trigger");
      baseline = baseline && TCut("Tau_pt[TauTau_Tau0Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1");
      baseline = baseline && TCut("Tau_pt[TauTau_Tau1Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      const TCut tau0pass = "(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau0fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
      const TCut tau1pass = "(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      const TCut tau1fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
      regionA = TCut("TauTau_qq==-1") &&  (tau0pass&&tau1pass);
      regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
      regionC = TCut("TauTau_qq==+1") &&  (tau0pass&&tau1pass);
      regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   }
   if (channel=="Electron") {
      baseline = baseline && TCut("ElTau_HavePair>0 && ElTau_HaveTriplet==0");
      //baseline = baseline && TCut("ElTau_HaveTriplet>0");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      //baseline = baseline && TCut("Photon_pt[ElTau_PhotonIdx]>=100.");
      //baseline = baseline && TCut("ElTau_Mass>=91.1876");
      baseline = baseline && TCut("ElTau_Trigger");
      baseline = baseline && TCut("Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
      if (year==2016) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=29.");
      if (year==2017) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      if (year==2018) baseline = baseline && TCut("Electron_pt[ElTau_ElIdx]>=34.");
      baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
      baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
      regionA = "ElTau_qq==-1 && (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionC = "ElTau_qq==+1 && (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
      regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   }
   const TCut cuts[4] = {baseline && regionA, baseline && regionB, baseline && regionC, baseline && regionD};

   TTree * t = (TTree*)f->Get("Events");
   std::cout << "   # of entries in tree: " << t->GetEntries() << std::endl;

   char bufferA[2000], bufferB[2000], bufferC[2000], bufferD[2000];
   if (isMC) {
      double lumi = 0.;
      if (year==2016) lumi = 36000.;
      if (year==2017) lumi = 41480.;
      if (year==2018) lumi = 59830.;
      TString weighttag = "xsWeight";
      if (sampletag=="DYJetsToEEMuMu"||sampletag=="DYJetsToTauTau") weighttag = "xsWeight_Njets";
      //if (sampletag=="WJetsToLNu") weighttag = "xsWeight_Njets";
      sprintf(bufferA, "%f * %s * (%s)", lumi, weighttag.Data(), TString(cuts[0]).Data());
      sprintf(bufferB, "%f * %s * (%s)", lumi, weighttag.Data(), TString(cuts[1]).Data());
      sprintf(bufferC, "%f * %s * (%s)", lumi, weighttag.Data(), TString(cuts[2]).Data());
      sprintf(bufferD, "%f * %s * (%s)", lumi, weighttag.Data(), TString(cuts[3]).Data());
   } else {
      sprintf(bufferA, "%s", TString(cuts[0]).Data());
      sprintf(bufferB, "%s", TString(cuts[1]).Data());
      sprintf(bufferC, "%s", TString(cuts[2]).Data());
      sprintf(bufferD, "%s", TString(cuts[3]).Data());
   }
 
   if (!blindA) {
      std::cout << "   filling " << h_A->GetName() << std::endl;
      const int n_A = t->Project(h_A->GetName(), var, bufferA);
      double e_A = 0.;
      const double i_A = h_A->IntegralAndError(1, h->GetNbinsX()+1, e_A);
      std::cout << "      " << i_A << "+-" << e_A << "; " << n_A << ", " << 1./sqrt(n_A) << std::endl;
      addOverflow(h_A);
   }

   std::cout << "   filling " << h_B->GetName() << std::endl;
   const int n_B = t->Project(h_B->GetName(), var, bufferB);
   double e_B = 0.;
   const double i_B = h_B->IntegralAndError(1, h->GetNbinsX()+1, e_B);
   std::cout << "      " << i_B << "+-" << e_B << "; " << n_B << ", " << 1./sqrt(n_B) << std::endl; 
   addOverflow(h_B);

   std::cout << "   filling " << h_C->GetName() << std::endl;
   const int n_C = t->Project(h_C->GetName(), var, bufferC);
   double e_C = 0.;
   const double i_C = h_C->IntegralAndError(1, h->GetNbinsX()+1, e_C);
   std::cout << "      " << i_C << "+-" << e_C << "; " << n_C << ", " << 1./sqrt(n_C) << std::endl;
   addOverflow(h_C);

   std::cout << "   filling " << h_D->GetName() << std::endl;
   const int n_D = t->Project(h_D->GetName(), var, bufferD);
   double e_D = 0.;
   const double i_D = h_D->IntegralAndError(1, h->GetNbinsX()+1, e_D);
   std::cout << "      " << i_D << "+-" << e_D << "; " << n_D << ", " << 1./sqrt(n_D) << std::endl;
   addOverflow(h_D);

   } else {
      std::cout << "   file does not exist!" << std::endl;
   }

   //save those histograms
   char outfname[100];
   if (isMC) {
      sprintf(outfname, "./outputHists/%s_%s_%d.root", sampletag.Data(), channel.Data(), year); 
   } else {
      sprintf(outfname, "./outputHists/%s_%d.root", sampletag.Data(), year);
   }
   TFile * f_out = new TFile(outfname, "RECREATE");
   h_A->Write("h_A");
   h_B->Write("h_B");
   h_C->Write("h_C");
   h_D->Write("h_D");
   f_out->Close();
   std::cout << "end runPoint()" << std::endl;
   return f_out;
}

void makeABCDHists(const TString channel, const int year)
{
   std::cout << "makeABCDHists()" << std::endl;
   std::cout << "   channel: " << channel << ", year: " << year << std::endl;
   char indata[100];
   if (year==0) {
      sprintf(indata, "./outputHists/%s.root", channel.Data());
   } else {
      sprintf(indata, "./outputHists/%s_%d.root", channel.Data(), year);
   }
   TFile * f_data = TFile::Open(indata);
   TH1D * h_data_B = (TH1D*)((TH1D*)f_data->Get("h_B"))->Clone("h_data_B");
   TH1D * h_data_C = (TH1D*)((TH1D*)f_data->Get("h_C"))->Clone("h_data_C");
   TH1D * h_data_D = (TH1D*)((TH1D*)f_data->Get("h_D"))->Clone("h_data_D");

   const int nmc = 13;
   TString mctag[nmc];
   mctag[0] = "VBFHToZG";
   mctag[1] = "GluGluHToZG";
   mctag[2] = "WW";
   mctag[3] = "WZ";
   mctag[4] = "ZZ";
   mctag[5] = "TTTo2L2Nu";
   mctag[6] = "TTToSemiLeptonic";
   mctag[7] = "ST_tW_top";
   mctag[8] = "ST_tW_antitop";
   mctag[9] = "ST_t_channel_antitop";
   mctag[10] = "ST_t_channel_top";
   mctag[11] = "DYJetsToEEMuMu";
   mctag[12] = "DYJetsToTauTau";

   TH1D *h_A[nmc], *h_B[nmc], *h_C[nmc], *h_D[nmc];
   for (int i = 0; i < nmc; ++i) {
      char fname[100];
      if (year==0) {
         sprintf(fname, "./outputHists/%s_%s.root", mctag[i].Data(), channel.Data());
      } else {
         sprintf(fname, "./outputHists/%s_%s_%d.root", mctag[i].Data(), channel.Data(), year);
      }
      TFile * f = TFile::Open(fname);
      h_A[i] = (TH1D*)f->Get("h_A");
      h_B[i] = (TH1D*)f->Get("h_B");
      h_C[i] = (TH1D*)f->Get("h_C");
      h_D[i] = (TH1D*)f->Get("h_D");
   }

   // subtract the mc from the data in the BCD regions
   for (int i = 0; i < nmc; ++i) {
      h_data_B->Add(h_B[i], -1.);
      h_data_C->Add(h_C[i], -1.);
      h_data_D->Add(h_D[i], -1.);
   }

   double Berr, Cerr, Derr;
   const double Bin = h_data_B->IntegralAndError(1, h_data_B->GetNbinsX()+1, Berr);
   const double Cin = h_data_C->IntegralAndError(1, h_data_C->GetNbinsX()+1, Cerr);
   const double Din = h_data_D->IntegralAndError(1, h_data_D->GetNbinsX()+1, Derr);
   std::cout << "inclusive B: " << Bin << "+-" << Berr << std::endl;
   std::cout << "inclusive C: " << Cin << "+-" << Cerr << std::endl;
   std::cout << "inclusive D: " << Din << "+-" << Derr << std::endl;

   const double CoD = Cin/Din;
   const double CoDerr = CoD * sqrt( (Cerr/Cin)*(Cerr/Cin) + (Derr/Din)*(Derr/Din) );
   std::cout << "inclusive transfer factor: " << CoD << " +- " << CoDerr << std::endl;
   const double BCoD = Bin * CoD;
   const double BCoDerr = BCoD * sqrt( (Berr/Bin)*(Berr/Bin) + (CoDerr/CoD)*(CoDerr/CoD) );
   std::cout << "inclusive prediction: " << BCoD << " +- " << BCoDerr << std::endl;

   // calculate the C/D transfer factor
   TH1D * h_CoD = (TH1D*)h_data_C->Clone("h_CoD");
   h_CoD->Divide(h_data_D);
   h_CoD->GetYaxis()->SetTitle("C / D");
   if (channel=="Electron") h_CoD->SetTitle("e + #tau_{h}");
   if (channel=="Muon") h_CoD->SetTitle("#mu + #tau_{h}");
   if (channel=="Tau") h_CoD->SetTitle("#tau_{h} + #tau_{h}");

   // multiply the transfer factor to get the prediction
   TH1D * h_BCoD = (TH1D*)h_data_B->Clone("h_BCoD");
   h_BCoD->GetYaxis()->SetTitle("B * ( C / D )");
   h_BCoD->SetStats(0);
   TH1D * h_BCoD_inc = (TH1D*)h_BCoD->Clone("h_BCoD_inc");
   h_BCoD->Multiply(h_CoD);
   h_BCoD_inc->Scale(CoD);

   TString title = "";
   if (channel=="Electron") title = "e + #tau_{h}";
   if (channel=="Muon") title = "#mu + #tau_{h}";
   if (channel=="Tau") title = "#tau_{h} + #tau_{h}";

   TCanvas * c = new TCanvas("c", channel, 800, 800);
   c->Divide(2, 2);

   c->cd(1);
   h_BCoD->SetLineColor(7);
   h_BCoD->SetLineWidth(2);
   h_BCoD->Draw("HIST, E");
   char predtitle[100];
   sprintf(predtitle, "A: %s", title.Data()); 
   h_BCoD->SetTitle(predtitle);
   h_BCoD_inc->SetLineColor(8);
   h_BCoD_inc->SetLineWidth(2);
   h_BCoD_inc->Draw("HIST, E, SAME");

   TLegend * l1 = new TLegend(0.3, 0.7, 0.875, 0.875);
   l1->SetBorderSize(0);
   l1->SetNColumns(2);
   l1->AddEntry(h_BCoD, "binned", "L");
   l1->AddEntry(h_BCoD_inc, "inclusive", "L");
   l1->Draw();

   c->cd(2);
   h_data_B->Draw("HIST, E");
   h_data_B->SetLineWidth(2);
   h_data_B->SetStats(0);
   
   c->cd(3);
   h_data_C->SetLineColor(6);
   h_data_C->SetLineWidth(2);
   h_data_C->Draw("HIST, E");
   h_data_C->SetStats(0);
   h_data_C->SetTitle(title);
   h_data_D->SetLineColor(7);
   h_data_D->SetLineWidth(2);
   h_data_D->Draw("HIST, E, SAME");
   h_data_C->SetMaximum(1.25*TMath::Max(h_data_C->GetMaximum(), h_data_D->GetMaximum()));

   TLegend * l3 = new TLegend(0.3, 0.8, 0.875, 0.875);
   l3->SetBorderSize(0);
   l3->SetNColumns(2);
   l3->AddEntry(h_data_C, "C", "L");
   l3->AddEntry(h_data_D, "D", "L");
   l3->Draw();

   c->cd(4);
   h_CoD->SetStats(0);
   h_CoD->SetMarkerStyle(20);
   h_CoD->Draw("PE");

   TLine * lineup = new TLine(h_CoD->GetBinLowEdge(1), CoD+CoDerr, h_CoD->GetBinLowEdge(h_CoD->GetNbinsX()+1), CoD+CoDerr);
   lineup->SetLineStyle(2);
   TLine * linedown = new TLine(h_CoD->GetBinLowEdge(1), CoD-CoDerr, h_CoD->GetBinLowEdge(h_CoD->GetNbinsX()+1), CoD-CoDerr);
   linedown->SetLineStyle(2);
   lineup->Draw();
   linedown->Draw();

   c->SaveAs("./plots/multijet."+channel+".pdf");
 
   // save those histograms to a root file
   char outfname[100];
   if (year==0) {
      sprintf(outfname, "./outputHists/ABCD_%s.root", channel.Data());
   } else {
      sprintf(outfname, "./outputHists/ABCD_%s_%d.root", channel.Data(), year);
   }
   TFile * f_qcd = new TFile(outfname, "RECREATE");
   h_data_B->Write("h_B");
   h_data_C->Write("h_C");
   h_data_D->Write("h_D");
   h_BCoD->Write("h_A");
   h_CoD->Write("h_CoD");
   f_qcd->Close();
   std::cout << "end makeABCDHists()" << std::endl;
   //return f_qcd;
}

void plotControlRegions(const TString channel, const bool blindA, const int year)
{
   std::cout << "plotControlRegions()" << std::endl;
   std::cout << "   channel: " << channel << ", blindA: " << blindA << ", year: " << year << std::endl;

   char infdata[100];
   if (year==0) {
      sprintf(infdata, "./outputHists/%s.root", channel.Data());
   } else {
      sprintf(infdata, "./outputHists/%s_%d.root", channel.Data(), year);
   }
   TFile *f_data = TFile::Open(infdata);
   TH1D * h_data_A;
   if (!blindA) h_data_A = (TH1D*)f_data->Get("h_A");
   TH1D * h_data_B = (TH1D*)f_data->Get("h_B");
   TH1D * h_data_C = (TH1D*)f_data->Get("h_C");
   TH1D * h_data_D = (TH1D*)f_data->Get("h_D");

   const int nsig = 2;
   TString sigtag[nsig];
   sigtag[0] = "Taustar_m375";
   sigtag[1] = "Taustar_m750";
   TString siglabels[nsig];
   siglabels[0] = "#tau* 375";
   siglabels[1] = "#tau* 750";
   const int sigcolz[nsig] = {209, 207};
   TH1D *h_sig_A[nsig], *h_sig_B[nsig], *h_sig_C[nsig], *h_sig_D[nsig];
   for (int i = 0; i < nsig; ++i) {
      char infmc[100];
      if (year==0) {
         sprintf(infmc, "./outputHists/%s_%s.root", sigtag[i].Data(), channel.Data());
      } else {
         sprintf(infmc, "./outputHists/%s_%s_%d.root", sigtag[i].Data(), channel.Data(), year);
      }
      TFile * f = TFile::Open(infmc);
      h_sig_A[i] = (TH1D*)f->Get("h_A");
      h_sig_B[i] = (TH1D*)f->Get("h_B");
      h_sig_C[i] = (TH1D*)f->Get("h_C");
      h_sig_D[i] = (TH1D*)f->Get("h_D");
      h_sig_A[i]->SetLineColor(sigcolz[i]);
      h_sig_A[i]->SetLineStyle(2);
      h_sig_B[i]->SetLineColor(sigcolz[i]);
      h_sig_B[i]->SetLineStyle(2);
      h_sig_C[i]->SetLineColor(sigcolz[i]);
      h_sig_C[i]->SetLineStyle(2);
      h_sig_D[i]->SetLineColor(sigcolz[i]);
      h_sig_D[i]->SetLineStyle(2);
   }

   const int nmc = 13;
   TString mctag[nmc];
   mctag[0] = "VBFHToZG";
   mctag[1] = "GluGluHToZG";
   mctag[2] = "WW";
   mctag[3] = "WZ";
   mctag[4] = "ZZ";
   mctag[5] = "TTTo2L2Nu";
   mctag[6] = "TTToSemiLeptonic";
   mctag[7] = "ST_tW_top";
   mctag[8] = "ST_tW_antitop";
   mctag[9] = "ST_t_channel_antitop";
   mctag[10] = "ST_t_channel_top";
   mctag[11] = "DYJetsToEEMuMu";
   mctag[12] = "DYJetsToTauTau";
    
   TString labels[nmc];
   for (int i = 0; i < nmc; ++i) {
      labels[i] = mctag[i];
   }
 
   int colz[nmc];
   for (int i = 0; i < nmc; ++i) {
      colz[i] = i+2;
   }

   // extract histograms from the root file
   TH1D *h_mc_A[nmc], *h_mc_B[nmc], *h_mc_C[nmc], *h_mc_D[nmc];
   for (int i = 0; i < nmc; ++i) {
      char infmc[100];
      if (year==0) {
         sprintf(infmc, "./outputHists/%s_%s.root", mctag[i].Data(), channel.Data());
      } else {
         sprintf(infmc, "./outputHists/%s_%s_%d.root", mctag[i].Data(), channel.Data(), year);
      }
      TFile * f = TFile::Open(infmc);
      h_mc_A[i] = (TH1D*)f->Get("h_A");
      h_mc_B[i] = (TH1D*)f->Get("h_B");
      h_mc_C[i] = (TH1D*)f->Get("h_C");
      h_mc_D[i] = (TH1D*)f->Get("h_D");
      h_mc_A[i]->SetFillColor(colz[i]);
      h_mc_B[i]->SetFillColor(colz[i]);
      h_mc_C[i]->SetFillColor(colz[i]);
      h_mc_D[i]->SetFillColor(colz[i]);
      if (h_mc_A[i]->GetEntries() || h_mc_B[i]->GetEntries() || h_mc_C[i]->GetEntries() || h_mc_D[i]->GetEntries()) {
         std::cout << mctag[i] << " has entries" << std::endl;
      }
   }

   char titleA[100];
   sprintf(titleA, "%s;%s;%s", h_mc_A[0]->GetTitle(), h_mc_A[0]->GetXaxis()->GetTitle(), h_mc_A[0]->GetYaxis()->GetTitle());
   THStack * s_A = new THStack("s_A", titleA);
   for (int i = 0; i < nmc; ++i) s_A->Add(h_mc_A[i]);

   //TFile *f_ABCD = makeABCDHists(channel, year);
   makeABCDHists(channel, year);
   char qcdin[100];
   sprintf(qcdin, "./outputHists/ABCD_%s.root", channel.Data());
   TFile *f_ABCD = TFile::Open(qcdin);
   TH1D * h_ABCD_A = (TH1D*)f_ABCD->Get("h_A");
   h_ABCD_A->SetFillColor(95);
   s_A->Add(h_ABCD_A);

   char titleB[100];
   sprintf(titleB, "%s;%s;%s", h_mc_B[0]->GetTitle(), h_mc_B[0]->GetXaxis()->GetTitle(), h_mc_B[0]->GetYaxis()->GetTitle());
   THStack * s_B = new THStack("s_B", titleB);
   for (int i = 0; i < nmc; ++i) s_B->Add(h_mc_B[i]);

   char titleC[100];
   sprintf(titleC, "%s;%s;%s", h_mc_C[0]->GetTitle(), h_mc_C[0]->GetXaxis()->GetTitle(), h_mc_C[0]->GetYaxis()->GetTitle());
   THStack * s_C = new THStack("s_C", titleC);
   for (int i = 0; i < nmc; ++i) s_C->Add(h_mc_C[i]);

   char titleD[100];
   sprintf(titleD, "%s;%s;%s", h_mc_D[0]->GetTitle(), h_mc_D[0]->GetXaxis()->GetTitle(), h_mc_D[0]->GetYaxis()->GetTitle());
   THStack * s_D = new THStack("s_D", titleD);
   for (int i = 0; i < nmc; ++i) s_D->Add(h_mc_D[i]);

   TLegend * lA = new TLegend(0.25, 0.7, 0.875, 0.875);
   lA->SetBorderSize(0);
   lA->SetNColumns(2);
   for (int i = 0; i < nmc; ++i) lA->AddEntry(h_mc_A[i], labels[i], "F");
   lA->AddEntry(h_ABCD_A, "B * ( C / D )", "F");
   lA->AddEntry(h_sig_A[0], siglabels[0], "L");
   lA->AddEntry(h_sig_A[1], siglabels[1], "L");

   TLegend * l = new TLegend(0.25, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   for (int i = 0; i < nmc; ++i) l->AddEntry(h_mc_B[i], labels[i], "F");
   l->AddEntry(h_data_B, "data", "P");
   l->AddEntry(h_sig_B[0], siglabels[0], "L");
   l->AddEntry(h_sig_B[1], siglabels[1], "L");

   double max = TMath::Max(h_data_B->GetMaximum(), h_data_C->GetMaximum());
   max = TMath::Max(max, h_data_D->GetMaximum());
   if (!blindA) max = TMath::Max(max, h_data_A->GetMaximum());
   const double ymax = pow(10, ceil(log10(max))+1);
   const double ymin = 1.;

   TCanvas * c = new TCanvas("c_plotControlRegions", channel, 800, 800);
   c->Divide(2, 2);

   TPad * p1 = (TPad*)c->cd(1);
   s_A->Draw("HIST");
   if (!blindA) {
      h_data_A->Draw("PE, SAME");
      h_data_A->SetMarkerStyle(20);
   }
   p1->SetLogy();
   s_A->SetMinimum(ymin);
   s_A->SetMaximum(ymax);
   h_sig_A[0]->Draw("HIST, E, SAME");
   h_sig_A[1]->Draw("HIST, E, SAME");
   lA->Draw(); 

   TPad * p2 = (TPad*)c->cd(2);
   s_B->Draw("HIST");
   h_data_B->Draw("PE, SAME");
   h_data_B->SetMarkerStyle(20);
   p2->SetLogy();
   s_B->SetMinimum(ymin);
   s_B->SetMaximum(ymax);
   h_sig_B[0]->Draw("HIST, E, SAME");
   h_sig_B[1]->Draw("HIST, E, SAME");
   l->Draw();

   TPad * p3 = (TPad*)c->cd(3);
   s_C->Draw("HIST");
   h_data_C->Draw("PE, SAME");
   h_data_C->SetMarkerStyle(20);
   p3->SetLogy();
   s_C->SetMinimum(ymin);
   s_C->SetMaximum(ymax);
   h_sig_C[0]->Draw("HIST, E, SAME");
   h_sig_C[1]->Draw("HIST, E, SAME");
   l->Draw();

   TPad * p4 = (TPad*)c->cd(4);
   s_D->Draw("HIST");
   h_data_D->Draw("PE, SAME");
   h_data_D->SetMarkerStyle(20);
   p4->SetLogy();
   s_D->SetMinimum(ymin);
   s_D->SetMaximum(ymax);
   h_sig_D[0]->Draw("HIST, E, SAME");
   h_sig_D[1]->Draw("HIST, E, SAME");
   l->Draw();

   c->SaveAs("./plots/cr."+channel+".pdf");

   if (!blindA) {
      TH1D *h_bkgsum_A = (TH1D*)h_mc_A[0]->Clone("h_bkgSum_A");
      for (int i = 1; i < nmc; ++i) h_bkgsum_A->Add(h_mc_A[i]);
      h_bkgsum_A->Add(h_ABCD_A);
      TH1D * r = (TH1D*)h_data_A->Clone("r");
      r->Divide(h_bkgsum_A);
      r->GetYaxis()->SetTitle("observed / prediction");
      r->SetMarkerStyle(20);
      TCanvas * c2 = new TCanvas("c2", "c2", 400, 400);
      r->Draw("PE");
      r->SetStats(0);
      //if (r->GetMaximum()>=10.) r->SetMaximum(10.);
      r->SetMinimum(0.);
      r->SetMaximum(2.);
      TLine * line = new TLine(r->GetBinLowEdge(1), 1., r->GetBinLowEdge(r->GetNbinsX()+1), 1.);
      line->SetLineStyle(2);
      line->Draw();
      c2->SaveAs("./plots/crr."+channel+".pdf");
   }

   std::cout << "end plotControlRegions()" << std::endl;
}

void makeAllHists(const TString channel, const int year, const bool blindA)
{
   std::cout << "makeAllHists()" << std::endl;
   std::cout << "   channel: " << channel << ", year: " << year << ", blindA: " << blindA << std::endl;

   const int nmc = 16;
   TString mctag[nmc];
   mctag[0] = "VBFHToZG";
   mctag[1] = "GluGluHToZG";
   mctag[2] = "WW";
   mctag[3] = "WZ";
   mctag[4] = "ZZ";
   mctag[5] = "TTTo2L2Nu";
   mctag[6] = "TTToSemiLeptonic";
   mctag[7] = "ST_tW_top";
   mctag[8] = "ST_tW_antitop";
   mctag[9] = "ST_t_channel_antitop";
   mctag[10] = "ST_t_channel_top";
   mctag[11] = "DYJetsToEEMuMu";
   mctag[12] = "DYJetsToTauTau";
   mctag[13] = "Taustar_m375";
   mctag[14] = "Taustar_m750";
   mctag[15] = "WJetsToLNu";
   for (int i = 0; i < nmc; ++i) {
      runPoint(mctag[i], channel, year, true, false);
   }
  
   std::vector<TString> letters;
   if (year==2018) {
      letters.push_back("A");
      letters.push_back("B");
      letters.push_back("C");
      letters.push_back("D");
   }
   if (year==2017) {
      letters.push_back("B");
      letters.push_back("C");
      letters.push_back("D");
      letters.push_back("E");
      letters.push_back("F");
   }
   if (year==2016) {
      letters.push_back("B");
      letters.push_back("C");
      letters.push_back("D");
      letters.push_back("E");
      letters.push_back("F");
      letters.push_back("G");
      letters.push_back("H");
   }
   for (auto i = letters.begin(); i != letters.end(); ++i) {
      char datatag[100];
      sprintf(datatag, "%s%s", channel.Data(), i->Data());
      runPoint(datatag, channel, year, false, blindA);
   }
   std::cout << "end makeAllHists()" << std::endl;
}

void combineHistogramsMC(const TString channel)
{
   std::cout << "combineHistogramsMC()" << std::endl;
   std::cout << "   channel: " << channel << std::endl;
   const int nmc = 16;
   TString mctag[nmc];
   mctag[0] = "VBFHToZG";
   mctag[1] = "GluGluHToZG";
   mctag[2] = "WW";
   mctag[3] = "WZ";
   mctag[4] = "ZZ";
   mctag[5] = "TTTo2L2Nu";
   mctag[6] = "TTToSemiLeptonic";
   mctag[7] = "ST_tW_top";
   mctag[8] = "ST_tW_antitop";
   mctag[9] = "ST_t_channel_antitop";
   mctag[10] = "ST_t_channel_top";
   mctag[11] = "DYJetsToEEMuMu";
   mctag[12] = "DYJetsToTauTau";
   mctag[13] = "Taustar_m375";
   mctag[14] = "Taustar_m750";
   mctag[15] = "WJetsToLNu";

   for (int i = 0; i < nmc; ++i) {
      char cmd1[1000];
      sprintf(cmd1, "hadd -f ./outputHists/%s_%s.root ./outputHists/%s_%s_2016.root ./outputHists/%s_%s_2017.root ./outputHists/%s_%s_2018.root",
         mctag[i].Data(), channel.Data(), mctag[i].Data(), channel.Data(), mctag[i].Data(), channel.Data(), mctag[i].Data(), channel.Data()
      );
      system(cmd1);
   }
   std::cout << "end combineHistogramsMC()" << std::endl;
}

void combineHistogramsData(const TString channel)
{
   std::cout << "combineHistogramsData()" << std::endl;
   std::cout << "   channel: " << channel << std::endl;
  
   char cmd18[1000];
   sprintf(cmd18, "hadd -f ./outputHists/%s_2018.root ./outputHists/%sA_2018.root ./outputHists/%sB_2018.root ./outputHists/%sC_2018.root ./outputHists/%sD_2018.root",
      channel.Data(), channel.Data(), channel.Data(), channel.Data(), channel.Data());
   system(cmd18);
   
   char cmd17[1000];
   sprintf(cmd17, "hadd -f ./outputHists/%s_2017.root ./outputHists/%sB_2017.root ./outputHists/%sC_2017.root ./outputHists/%sD_2017.root ./outputHists/%sE_2017.root ./outputHists/%sF_2017.root",
      channel.Data(), channel.Data(), channel.Data(), channel.Data(), channel.Data(), channel.Data());
   system(cmd17);
   
   char cmd16[1000];
   sprintf(cmd16, "hadd -f ./outputHists/%s_2016.root ./outputHists/%sB_2016.root ./outputHists/%sC_2016.root ./outputHists/%sD_2016.root ./outputHists/%sE_2016.root ./outputHists/%sF_2016.root ./outputHists/%sG_2016.root ./outputHists/%sH_2016.root",
      channel.Data(), channel.Data(), channel.Data(), channel.Data(), channel.Data(), channel.Data(), channel.Data(), channel.Data());
   system(cmd16);
   
   char cmd[1000];
   sprintf(cmd, "hadd -f ./outputHists/%s.root ./outputHists/%s_2018.root ./outputHists/%s_2017.root ./outputHists/%s_2016.root",
      channel.Data(), channel.Data(), channel.Data(), channel.Data());
   system(cmd);

   std::cout << "end combineHistogramsData()" << std::endl;
}

void yields_ZTauTau(const TString channel, const bool blindA)
{
   std::cout << "yields_ZTauTau()" << std::endl;
   std::cout << "   channel: " << channel << ", blindA: " << blindA << std::endl;
   //makeAllHists(channel, 2018, blindA);
   //makeAllHists(channel, 2017, blindA);
   //makeAllHists(channel, 2016, blindA);
   //combineHistogramsMC(channel);
   //combineHistogramsData(channel);
   plotControlRegions(channel, blindA, 0);
   std::cout << "end yields_ZTauTau()" << std::endl;
}

