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

TString makestring(const double mass, const TString channel)
{
   char outstring[1000];
   const double upper=mass-100.
   const double lower=mass+100.
   
   if (channel=="Electron") {
      sprintf(outstring,
      "(ElTau_MaxCollMass<%f)?1 : (ElTau_MinCollMass>=%f)?4 : (ElTau_MaxCollMass>=%f&&ElTau_MinCollMass<%f)?3 : ((ElTau_MaxCollMass>=%f&&ElTau_MaxCollMass<%f)||(ElTau_MinCollMass>=%f&&ElTau_MinCollMass<%f))?1 : 0",
                          lower,                      upper,                      upper,                lower,                       lower,                upper,                   lower,                upper
      );
   }
   if (channel=="Muon") {
      sprintf(outstring,
      "(MuTau_MaxCollMass<%f)?1 : (MuTau_MinCollMass>=%f)?4 : (MuTau_MaxCollMass>=%f&&MuTau_MinCollMass<%f)?3 : ((MuTau_MaxCollMass>=%f&&MuTau_MaxCollMass<%f)||(MuTau_MinCollMass>=%f&&MuTau_MinCollMass<%f))?1 : 0",
                          lower,                      upper,                      upper,                lower,                       lower,                upper,                   lower,                upper
      );
   }
   if (channel=="Tau") {
      sprintf(outstring,
      "(TauTau_MaxCollMass<%f)?1 : (TauTau_MinCollMass>=%f)?4 : (TauTau_MaxCollMass>=%f&&TauTau_MinCollMass<%f)?3 : ((TauTau_MaxCollMass>=%f&&TauTau_MaxCollMass<%f)||(TauTau_MinCollMass>=%f&&TauTau_MinCollMass<%f))?1 : 0",
                          lower,                      upper,                      upper,                lower,                       lower,                upper,                   lower,                upper
      );
   }

   return TString(outstring);
}

TFile * runPoint(const TString sampletag, const TString channel, const int year, const bool isMC=false, const double blindA=0.)
{
   std::cout << "runPoint() " << sampletag << " " << year << std::endl;
   const TString eostag = "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_20032021/backups/";
   char infile[100];

   if (sampletag=="DYJetsToEEMuMu_M50" || sampletag=="DYJetsToTauTau_M50") {
      sprintf(infile, "%s/%s_%d.root", eostag.Data(), "DYJetsToLL_M50", year);
   } else {
      sprintf(infile, "%s/%s_%d.root", eostag.Data(), sampletag.Data(), year);
   }
   TFile * f = TFile::Open(infile);

   char hname[100];
   sprintf(hname, "h_%s_%s_%d", sampletag.Data(), channel.Data(), year);
   //TH1D * h = new TH1D(hname, ";min collinear mass;events / 250 GeV", 4, 0., 1000.);
   TH1D * h = new TH1D(hname, ";analysis bin;events", 5, -0.5, 4.5);
   h->Sumw2();
   TString var;
   TString titletag;
   if (channel=="Electron") {
      //var = "TMath::Min(ElTau_ElCollMass, ElTau_TauCollMass)";
      var = makeString(375., channel);
      titletag = "e + #tau_{h}";
   }  
   if (channel=="Muon") {
      //var = "TMath::Min(MuTau_MuCollMass, MuTau_TauCollMass)";
      var = makeString(375., channel);
      titletag = "#mu + #tau_{h}";
   }
   if (channel=="Tau") {
      //var = "TMath::Min(TauTau_Tau0CollMass, TauTau_Tau1CollMass)";
      var = makeString(375., channel);
      titletag = "#tau_{h} + #tau_{h}";
   }

   TH1D * h_A = (TH1D*)h->Clone(TString(h->GetName())+"_A");
   h_A->SetTitle("A: " + titletag);
   TH1D * h_B = (TH1D*)h->Clone(TString(h->GetName())+"_B");
   h_B->SetTitle("B: " + titletag);
   TH1D * h_C = (TH1D*)h->Clone(TString(h->GetName())+"_C");
   h_C->SetTitle("C: " + titletag);
   TH1D * h_D = (TH1D*)h->Clone(TString(h->GetName())+"_D");
   h_D->SetTitle("D: " + titletag);

   if (f) {

   TCut baseline = "1>0";
   TCut regionA, regionB, regionC, regionD; 

   TString weighttag = "xsWeight";
   if (sampletag=="DYJetsToEEMuMu_M50" || sampletag=="DYJetsToTauTau_M50") {
     weighttag = "xsWeight_DY";
     const TCut tautau = "Sum$(TMath::Abs(GenPart_pdgId)==15 && GenPart_genPartIdxMother>=0 && GenPart_pdgId[GenPart_genPartIdxMother]==23)>=2";
   }

   if (channel=="Muon") {
      baseline = baseline && TCut("MuTau_HaveTriplet>0");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("Photon_pt[MuTau_PhotonIdx]>=100.");
      baseline = baseline && TCut("MuTau_Mass>=100.");
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
      baseline = baseline && TCut("TauTau_HaveTriplet>0");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("Photon_pt[TauTau_PhotonIdx]>=100.");
      baseline = baseline && TCut("TauTau_Mass>=100.");
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
      baseline = baseline && TCut("ElTau_HaveTriplet>0");
      baseline = baseline && TCut("JetProducer_nBJetT==0");
      baseline = baseline && TCut("Photon_pt[ElTau_PhotonIdx]>=100.");
      baseline = baseline && TCut("ElTau_Mass>=100.");
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
   sprintf(outfname, "./outputHists/%s_%s_%d.root", sampletag.Data(), channel.Data(), year); 
   TFile * f_out = new TFile(outfname, "RECREATE");
   h_A->Write("h_A");
   h_B->Write("h_B");
   h_C->Write("h_C");
   h_D->Write("h_D");
   f_out->Close();
   return f_out;
}

TFile * makeABCDHists(const TString channel, const int year=0)
{
   std::cout << "makeABCDHists()" << std::endl;
   char indata[100];
   if (year==0) {
      sprintf(indata, "./outputHists/%s_%s.root", channel.Data(), channel.Data());
   } else {
      sprintf(indata, "./outputHists/%s_%s_%d.root", channel.Data(), channel.Data(), year);
   }
   TFile * f_data = TFile::Open(indata);
   TH1D * data_B = (TH1D*)f_data->Get("h_B");
   TH1D * data_C = (TH1D*)f_data->Get("h_C");
   TH1D * data_D = (TH1D*)f_data->Get("h_D");

   const int nmc = 6;
   TString mctag[nmc];
   mctag[0] = "diboson";
   mctag[1] = "ttbar";
   mctag[2] = "ST_tW";
   mctag[3] = "ST_t_channel";
   mctag[4] = "DYJetsToEEMuMu_M50";
   mctag[5] = "DYJetsToTauTau_M50";

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
      data_B->Add(h_B[i], -1.);
      data_C->Add(h_C[i], -1.);
      data_D->Add(h_D[i], -1.);
   }

   double Berr, Cerr, Derr;
   const double Bin = data_B->IntegralAndError(1, data_B->GetNbinsX()+1, Berr);
   const double Cin = data_C->IntegralAndError(1, data_C->GetNbinsX()+1, Cerr);
   const double Din = data_D->IntegralAndError(1, data_D->GetNbinsX()+1, Derr);
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
   TH1D * h_CoD = (TH1D*)data_C->Clone("h_CoD");
   h_CoD->Divide(data_D);
   h_CoD->GetYaxis()->SetTitle("C / D");

   // multiply the transfer factor to get the prediction
   TH1D * h_BCoD = (TH1D*)data_B->Clone("h_BCoD");
   h_BCoD->Scale(CoD);
   //h_BCoD->Multiply(h_CoD);
   h_BCoD->GetYaxis()->SetTitle("B * ( C / D )");

   TCanvas * c = new TCanvas("c", channel, 400, 400);
   h_CoD->Draw("PE");
   h_CoD->GetYaxis()->SetTitle("C / D");
   h_CoD->SetStats(0);
   h_CoD->SetMinimum(0.);
   h_CoD->SetMaximum(0.65);
   h_CoD->SetMarkerStyle(20);
   
   TLine * lineup = new TLine(h_CoD->GetBinLowEdge(1), CoD+CoDerr, h_CoD->GetBinLowEdge(h_CoD->GetNbinsX()+1), CoD+CoDerr);
   lineup->SetLineStyle(1);
   lineup->SetLineColor(1);
   TLine * linedown = new TLine(h_CoD->GetBinLowEdge(1), CoD-CoDerr, h_CoD->GetBinLowEdge(h_CoD->GetNbinsX()+1), CoD-CoDerr);
   linedown->SetLineStyle(1);
   linedown->SetLineColor(1);
   lineup->Draw();
   linedown->Draw();

   c->SaveAs("./plots/CoD."+channel+".pdf");
 
   // save those histograms to a root file
   char outfname[100];
   if (year==0) {
      sprintf(outfname, "./outputHists/ABCD_%s.root", channel.Data());
   } else {
      sprintf(outfname, "./outputHists/ABCD_%s_%d.root", channel.Data(), year);
   }
   TFile * f_qcd = new TFile(outfname, "RECREATE");
   data_B->Write("h_B");
   data_C->Write("h_C");
   data_D->Write("h_D");
   h_BCoD->Write("h_A");
   h_CoD->Write("h_CoD");
   //f_qcd->Close();
   return f_qcd;
}

void plotControlRegions(const TString channel, const int year=0)
{
   std::cout << "plotControlRegions()" << std::endl;
   const double ymin = 1.;
   const double ymax = 1000.;

   char infdata[100];
   if (year==0) {
      sprintf(infdata, "./outputHists/%s_%s.root", channel.Data(), channel.Data());
   } else {
      sprintf(infdata, "./outputHists/%s_%s_%d.root", channel.Data(), channel.Data(), year);
   }
   TFile *f_data = TFile::Open(infdata);
   TH1D * h_data_B = (TH1D*)f_data->Get("h_B");
   TH1D * h_data_C = (TH1D*)f_data->Get("h_C");
   TH1D * h_data_D = (TH1D*)f_data->Get("h_D");
   h_data_B->SetMarkerStyle(20);
   h_data_C->SetMarkerStyle(20);
   h_data_D->SetMarkerStyle(20);

   const int nsig = 2;
   TString sigtag[nsig];
   sigtag[0] = "Taustar_m375";
   sigtag[1] = "Taustar_m750";
   TString siglabels[nsig];
   siglabels[0] = "#tau* 375";
   siglabels[1] = "#tau* 750";
   const int sigcolz[nsig] = {95, 96};
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

   const int nmc = 6;
   TString mctag[nmc];
   mctag[0] = "diboson";
   mctag[1] = "ttbar";
   mctag[2] = "ST_tW";
   mctag[3] = "ST_t_channel";
   mctag[4] = "DYJetsToEEMuMu_M50";
   mctag[5] = "DYJetsToTauTau_M50";
 
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

   THStack * s_A = new THStack("s_A", "");
   char titleA[100];
   sprintf(titleA, "A;%s;", h_mc_A[0]->GetXaxis()->GetTitle());
   s_A->SetTitle(titleA);
   for (int i = 0; i < nmc; ++i) s_A->Add(h_mc_A[i]);
   TFile *f_ABCD = makeABCDHists(channel, year);
   TH1D * h_ABCD_A = (TH1D*)f_ABCD->Get("h_A");
   h_ABCD_A->SetFillColor(95);
   s_A->Add(h_ABCD_A);

   THStack * s_B = new THStack("s_B", "");
   char titleB[100];
   sprintf(titleB, "B;%s;", h_mc_B[0]->GetXaxis()->GetTitle());
   s_B->SetTitle(titleB);
   for (int i = 0; i < nmc; ++i) s_B->Add(h_mc_B[i]);

   THStack * s_C = new THStack("s_C", "");
   char titleC[100];
   sprintf(titleC, "C;%s;", h_mc_C[0]->GetXaxis()->GetTitle());
   s_C->SetTitle(titleC);
   for (int i = 0; i < nmc; ++i) s_C->Add(h_mc_C[i]);

   THStack * s_D = new THStack("s_D", "");
   char titleD[100];
   sprintf(titleD, "D;%s;", h_mc_D[0]->GetXaxis()->GetTitle());
   s_D->SetTitle(titleD);
   for (int i = 0; i < nmc; ++i) s_D->Add(h_mc_D[i]);

   TLegend * lA = new TLegend(0.4, 0.7, 0.875, 0.875);
   lA->SetBorderSize(0);
   lA->SetNColumns(2);
   for (int i = 0; i < nmc; ++i) lA->AddEntry(h_mc_A[i], labels[i], "F");
   lA->AddEntry(h_ABCD_A, "B*(C/D)", "F");
   lA->AddEntry(h_sig_A[0], siglabels[0], "L");
   lA->AddEntry(h_sig_A[1], siglabels[1], "L");

   TLegend * l = new TLegend(0.4, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   for (int i = 0; i < nmc; ++i) l->AddEntry(h_mc_B[i], labels[i], "F");
   l->AddEntry(h_data_B, "data", "P");
   l->AddEntry(h_sig_B[0], siglabels[0], "L");
   l->AddEntry(h_sig_B[1], siglabels[1], "L");

   TCanvas * c = new TCanvas("c_plotControlRegions", channel, 800, 800);
   c->Divide(2,2);

   TPad * p1 = (TPad*)c->cd(1);
   s_A->Draw("HIST");
   p1->SetLogy();
   s_A->SetMinimum(ymin);
   s_A->SetMaximum(ymax);
   h_sig_A[0]->Draw("HIST, E, SAME");
   h_sig_A[1]->Draw("HIST, E, SAME");
   lA->Draw(); 

   TPad * p2 = (TPad*)c->cd(2);
   s_B->Draw("HIST");
   h_data_B->Draw("PE, SAME"); 
   p2->SetLogy();
   s_B->SetMinimum(ymin);
   s_B->SetMaximum(ymax);
   h_sig_B[0]->Draw("HIST, E, SAME");
   h_sig_B[1]->Draw("HIST, E, SAME");
   l->Draw();

   TPad * p3 = (TPad*)c->cd(3);
   s_C->Draw("HIST");
   h_data_C->Draw("PE, SAME");
   p3->SetLogy();
   s_C->SetMinimum(ymin);
   s_C->SetMaximum(ymax);
   h_sig_C[0]->Draw("HIST, E, SAME");
   h_sig_C[1]->Draw("HIST, E, SAME");
   l->Draw();

   TPad * p4 = (TPad*)c->cd(4);
   s_D->Draw("HIST");
   h_data_D->Draw("PE, SAME");
   p4->SetLogy();
   s_D->SetMinimum(ymin);
   s_D->SetMaximum(ymax);
   h_sig_D[0]->Draw("HIST, E, SAME");
   h_sig_D[1]->Draw("HIST, E, SAME");
   l->Draw();

   c->SaveAs("./plots/cr."+channel+".pdf");
}

void makeAllHists(const TString channel="Electron", const int year=2018)
{
   runPoint("Taustar_m375",         channel, year, true, false);
   runPoint("Taustar_m750",         channel, year, true, false);
   //runPoint("VBFHToTauTau",         channel, year, true, false);
   //runPoint("GluGluHToTauTau",      channel, year, true, false);
   runPoint("WW",                   channel, year, true, false);
   runPoint("WZ",                   channel, year, true, false);
   runPoint("ZZ",                   channel, year, true, false);
   //runPoint("EWKZ",                 channel, year, true, false);
   runPoint("TTTo2L2Nu",            channel, year, true, false);
   runPoint("TTToSemiLeptonic",     channel, year, true, false);
   runPoint("TTToSemiLeptonic_1",    channel, year, true, false);
   runPoint("ST_tW_top",            channel, year, true, false);
   runPoint("ST_tW_antitop",        channel, year, true, false);
   runPoint("ST_t_channel_antitop", channel, year, true, false);
   runPoint("ST_t_channel_top",     channel, year, true, false);
   runPoint("DYJetsToEEMuMu_M50",   channel, year, true, false);
   runPoint("DYJetsToTauTau_M50",   channel, year, true, false);
   runPoint("WJetsToLNu",           channel, year, true, false);

   const bool blindA = true;

   if (channel=="Muon") {
      if (year==2018) {
         runPoint("MuonA", channel, year, false, blindA);
         runPoint("MuonB", channel, year, false, blindA);
         runPoint("MuonC", channel, year, false, blindA);
         runPoint("MuonD", channel, year, false, blindA);
      }
      if (year==2017) {
         runPoint("MuonB", channel, year, false, blindA);
         runPoint("MuonC", channel, year, false, blindA);
         runPoint("MuonD", channel, year, false, blindA);
         runPoint("MuonE", channel, year, false, blindA);
         runPoint("MuonF", channel, year, false, blindA);
      }
      if (year==2016) {
         runPoint("MuonB", channel, year, false, blindA);
         runPoint("MuonC", channel, year, false, blindA);
         runPoint("MuonD", channel, year, false, blindA);
         runPoint("MuonE", channel, year, false, blindA);
         runPoint("MuonF", channel, year, false, blindA);
         runPoint("MuonG", channel, year, false, blindA);
         runPoint("MuonH", channel, year, false, blindA);
      }
   }
   if (channel=="Electron") {
      if (year==2018) {
         runPoint("ElectronA", channel, year, false, blindA);
         runPoint("ElectronB", channel, year, false, blindA);
         runPoint("ElectronC", channel, year, false, blindA);
         runPoint("ElectronD", channel, year, false, blindA);
      }
      if (year==2017) {
         runPoint("ElectronB", channel, year, false, blindA);
         runPoint("ElectronC", channel, year, false, blindA);
         runPoint("ElectronD", channel, year, false, blindA);
         runPoint("ElectronE", channel, year, false, blindA);
         runPoint("ElectronF", channel, year, false, blindA);
      }
      if (year==2016) {
         runPoint("ElectronB", channel, year, false, blindA);
         runPoint("ElectronC", channel, year, false, blindA);
         runPoint("ElectronD", channel, year, false, blindA);
         runPoint("ElectronE", channel, year, false, blindA);
         runPoint("ElectronF", channel, year, false, blindA);
         runPoint("ElectronG", channel, year, false, blindA);
         runPoint("ElectronH", channel, year, false, blindA);
      }
   }
   if (channel=="Tau") {
      if (year==2018) {
         runPoint("TauA", channel, year, false, blindA);
         runPoint("TauB", channel, year, false, blindA);
         runPoint("TauC", channel, year, false, blindA);
         runPoint("TauD", channel, year, false, blindA);
      }
      if (year==2017) {
         runPoint("TauB", channel, year, false, blindA);
         runPoint("TauC", channel, year, false, blindA);
         runPoint("TauD", channel, year, false, blindA);
         runPoint("TauE", channel, year, false, blindA);
         runPoint("TauF", channel, year, false, blindA);
      }
      if (year==2016) {
         runPoint("TauB", channel, year, false, blindA);
         runPoint("TauC", channel, year, false, blindA);
         runPoint("TauD", channel, year, false, blindA);
         runPoint("TauE", channel, year, false, blindA);
         runPoint("TauF", channel, year, false, blindA);
         runPoint("TauG", channel, year, false, blindA);
         runPoint("TauH", channel, year, false, blindA);
      }
   }

}

void yields_ZTauTau(const TString channel="Electron")
{
   //makeAllHists(channel, 2016);
   //makeAllHists(channel, 2017);
   makeAllHists(channel, 2018);
}

