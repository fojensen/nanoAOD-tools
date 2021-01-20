#include <TLine.h>
#include <iostream>
#include <THStack.h>
#include <TCut.h>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>

double addOverflow(TH1D * h)
{
   const int n = h->GetNbinsX();
   const double o = h->GetBinContent(n+1);
   if (!o) return 0.;
   std::cout << "Adding overflow to " << h->GetName() << std::endl;

   //before
   std::cout << "   GetEntries() =  " << h->GetEntries() <<  std::endl;
   std::cout << "   GetBinContent(n+1) = " << o << " +- " << h->GetBinError(n+1) << std::endl;
   std::cout << "   GetBinContent(n) = " << h->GetBinContent(n) << " +- " << h->GetBinError(n) << std::endl;

   std::cout << "   ...adjust the numbers..." << std::endl;   
   h->AddBinContent(n, o);
   h->SetBinContent(n+1, 0.);
   h->SetBinError(n+1, 0.);
   
   //after
   std::cout << "   GetEntries() = " << h->GetEntries() << std::endl;
   std::cout << "   GetBinContent(n+1) = " << h->GetBinContent(n+1) << " +- " << h->GetBinError(n+1) << std::endl;
   std::cout << "   GetBinContent(n) =  " << h->GetBinContent(n) << " +- " << h->GetBinError(n) << std::endl;

   return o;
}

TFile * makeHists(const TString tag, const TString cuttag, const std::vector<TString> filelist, const bool isMC=false)
{
   std::cout << "makeHists() " << tag << std::endl;
   
   TH1D * h = new TH1D("h_"+tag, ";visible mass [GeV];events / 10 GeV", 25, 0., 250.);
 
   // load in your input trees  
   TChain * t = new TChain("Events");
   for (auto i = filelist.begin(); i != filelist.end(); ++i) {
      t->Add("./outputData/" + *i + ".root");
   }

   TCut baseline;
   TString xtitle;
   TCut regionA, regionB, regionC, regionD;
   TString var;  
 
   if (cuttag=="EGamma") {
   // e + tauh
   var = "ElTau_Mass";
   xtitle = "e+#tau_{h} visible mass [GeV]";
   baseline = "ElTau_HavePair>0 && JetProducer_nBJetM==0";
   baseline = baseline && TCut("ZProducer_EEHavePair==0 && ZProducer_MuMuHavePair==0");
   baseline = baseline && TCut("HLT_Ele32_WPTight_Gsf && Electron_mvaFall17V2Iso_WP80[ElTau_ElIdx]");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP80)==1");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
   baseline = baseline && TCut("ElTau_mT<40.");
   regionA = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionC = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   }

   if (cuttag=="SingleMuon") {
   // mu + tauh 
   var = "MuTau_Mass";
   xtitle = "#mu+#tau_{h} visible mass [GeV]";
   baseline = "MuTau_HavePair>0 && JetProducer_nBJetM==0";
   baseline = baseline && TCut("ZProducer_EEHavePair==0 && ZProducer_MuMuHavePair==0");
   baseline = baseline && TCut("(HLT_IsoMu24||HLT_IsoMu27) && Muon_pfIsoId[MuTau_MuIdx]>=4");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP80)==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
   baseline = baseline && TCut("MuTau_mT<40.");
   regionA = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionC = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   }

   if (cuttag=="Tau") {
   // tauh + tauh
   var = "TauTau_Mass";
   xtitle = "#tau_{h}+#tau_{h} visible mass [GeV]";
   baseline = "TauTau_HavePair>0 && JetProducer_nBJetM==0";
   baseline = baseline && TCut("ZProducer_EEHavePair==0 && ZProducer_MuMuHavePair==0");
   baseline = baseline && TCut("TauTau_Trigger");
   baseline = baseline && TCut("Tau_pt[TauTau_Tau0Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1 && Tau_pt[TauTau_Tau1Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
   baseline = baseline && TCut("Sum$(Electon_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP80)==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
   const TCut tau0pass = "32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]";
   const TCut tau0fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
   const TCut tau1pass = "32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]";
   const TCut tau1fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
   regionA = TCut("TauTau_qq==-1") &&  (tau0pass&&tau1pass);
   regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   regionC = TCut("TauTau_qq==+1") &&  (tau0pass&&tau1pass);
   regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   }

   const TString cutA = TString(baseline && regionA);
   const TString cutB = TString(baseline && regionB);
   const TString cutC = TString(baseline && regionC);
   const TString cutD = TString(baseline && regionD);
   char bufferA[1000], bufferB[1000], bufferC[1000], bufferD[1000];
   if (isMC) {
      sprintf(bufferA, "59725.419 * xsWeight * (%s)", cutA.Data());
      sprintf(bufferB, "59725.419 * xsWeight * (%s)", cutB.Data());
      sprintf(bufferC, "59725.419 * xsWeight * (%s)", cutC.Data());
      sprintf(bufferD, "59725.419 * xsWeight * (%s)", cutD.Data());
   } else {
      sprintf(bufferA, "%s", cutA.Data());
      sprintf(bufferB, "%s", cutB.Data());
      sprintf(bufferC, "%s", cutC.Data());
      sprintf(bufferD, "%s", cutD.Data());
   }

   // define the histogram to visualize the data in
   TH1D * h_A = (TH1D*)h->Clone("h_A_"+tag);
   TH1D * h_B = (TH1D*)h->Clone("h_B_"+tag);
   TH1D * h_C = (TH1D*)h->Clone("h_C_"+tag);
   TH1D * h_D = (TH1D*)h->Clone("h_D_"+tag);

   // fill the histograms
   const int n_A = t->Project(h_A->GetName(), var, bufferA);
   const int n_B = t->Project(h_B->GetName(), var, bufferB);
   const int n_C = t->Project(h_C->GetName(), var, bufferC);
   const int n_D = t->Project(h_D->GetName(), var, bufferD);

   // get the inclusive yields
   const double i_A = h_A->Integral();
   const double i_B = h_B->Integral();
   const double i_C = h_C->Integral();
   const double i_D = h_D->Integral();

   std::cout << "   region | yield | mc events" << std::endl; 
   std::cout << "   A " << i_A << " " << n_A << std::endl;
   std::cout << "   B " << i_B << " " << n_B << std::endl;
   std::cout << "   C " << i_C << " " << n_C << std::endl;
   std::cout << "   D " << i_D << " " << n_D << std::endl;

   //save those histograms
   TFile * f_out = new TFile("./outputHists/"+tag+"."+cuttag+".root", "RECREATE");
   h_A->Write("h_A");
   h_B->Write("h_B");
   h_C->Write("h_C");
   h_D->Write("h_D");
   f_out->Close();
   return f_out;
}

TFile * makeQCDHists(const TString datatag)
{
   std::cout << "makeQCDHists()" << std::endl;
   std::cout << "QCD" << std::endl;
   TFile * f_data = TFile::Open("./outputHists/"+datatag+"."+datatag+".root");
   TH1D * data_B = (TH1D*)f_data->Get("h_B");
   TH1D * data_C = (TH1D*)f_data->Get("h_C");
   TH1D * data_D = (TH1D*)f_data->Get("h_D");

   const int nmc = 6;
   TString mctag[nmc];
   mctag[0] = "HToTauTau";
   mctag[1] = "TTJets";
   mctag[2] = "EWK";
   mctag[3] = "WJetsToLNu";
   mctag[4] = "DYJetsToEEMuMu_M50";
   mctag[5] = "DYJetsToTauTau_M50";

   TH1D *h_A[nmc], *h_B[nmc], *h_C[nmc], *h_D[nmc];
   for (int i = 0; i < nmc; ++i) {
      char fname[100];
      sprintf(fname, "./outputHists/%s.%s.root", mctag[i].Data(), datatag.Data());
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

   const double B = data_B->GetEntries();
   const double C = data_C->GetEntries();
   const double D = data_D->GetEntries();
   const double CoD = C/D;
   const double CoDerr = CoD * sqrt((1./B)+(1./C));
   const double BCoD = B * CoD;
   const double BCoDerr = BCoD * sqrt( (1./B) + (CoDerr/CoD)*(CoDerr/CoD) );
   std::cout << "inclusive transfer factor: " << CoD << " +- " << CoDerr << std::endl;
   std::cout << "inclusive prediction: " << BCoD << " +- " << BCoDerr << std::endl;

   // calculate the C/D transfer factor
   TH1D * h_CoD = (TH1D*)data_C->Clone("h_CoD");
   h_CoD->Divide(data_D);
   h_CoD->GetYaxis()->SetTitle("C / D");

   // multiply the transfer factor to get the prediction
   TH1D * h_QCD = (TH1D*)data_B->Clone("h_QCD");
   h_QCD->Scale(CoD);
   //h_QCD->Multiply(h_CoD);
   h_QCD->GetYaxis()->SetTitle("B * ( C / D )");

   TCanvas * c = new TCanvas("c_makeQCDHists", datatag, 400, 400);
   h_CoD->Draw("PE");
   h_CoD->GetYaxis()->SetTitle("C / D");
   h_CoD->SetStats(0);
   h_CoD->SetMinimum(0.);
   h_CoD->SetMaximum(0.65);
   h_CoD->SetMarkerStyle(20);
   c->SaveAs("./plots/CoD."+datatag+".pdf");
 
   // save those histograms to a root file
   TFile * f_qcd = new TFile("./outputHists/QCD."+datatag+".root", "RECREATE");
   h_QCD->Write("h_A");
   data_B->Write("h_B");
   data_C->Write("h_C");
   data_D->Write("h_D");
   h_CoD->Write("h_CoD");
   f_qcd->Close();
   return f_qcd;
}

void plotControlRegions(const TString datatag)
{
   std::cout << "plotControlRegions()" << std::endl;
   const double ymin = 1.e2;
   const double ymax = 1.e6;

   TFile *f_data = TFile::Open("./outputHists/"+datatag+"."+datatag+".root");
   TH1D * h_data_B = (TH1D*)f_data->Get("h_B");
   TH1D * h_data_C = (TH1D*)f_data->Get("h_C");
   TH1D * h_data_D = (TH1D*)f_data->Get("h_D");
   h_data_B->SetMarkerStyle(20);
   h_data_C->SetMarkerStyle(20);
   h_data_D->SetMarkerStyle(20);

   int nmc = 6;
   TString mctag[nmc];
   mctag[0] = "HToTauTau";
   mctag[1] = "TTJets";
   mctag[2] = "EWK";
   mctag[3] = "WJetsToLNu";
   mctag[4] = "DYJetsToEEMuMu_M50";
   mctag[5] = "DYJetsToTauTau_M50";
 
   TString labels[nmc];
   labels[0] = "H#rightarrow#tau#tau";
   labels[1] = "t#bar{t}";
   labels[2] = "Electroweak";
   labels[3] = "W#rightarrowl#nu";
   labels[4] = "Z/#gamma^{*} #rightarrow ee,#mu#mu";
   labels[5] = "Z/#gamma^{*} #rightarrow #tau#tau";

   int colz[nmc];
   colz[0] = 28;
   colz[1] = 9;
   colz[2] = 224;
   colz[3] = 224;
   colz[4] = 78;
   colz[5] = 92;

   // extract histograms from the root file
   TH1D *h_mc_B[nmc], *h_mc_C[nmc], *h_mc_D[nmc];
   for (int i = 0; i < nmc; ++i) {
      TFile * f = TFile::Open("./outputHists/"+mctag[i]+"."+datatag+".root");
      h_mc_B[i] = (TH1D*)f->Get("h_B");
      h_mc_C[i] = (TH1D*)f->Get("h_C");
      h_mc_D[i] = (TH1D*)f->Get("h_D");
      h_mc_B[i]->SetFillColor(colz[i]);
      h_mc_C[i]->SetFillColor(colz[i]);
      h_mc_D[i]->SetFillColor(colz[i]);
   }

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

   TLegend * l = new TLegend(0.5, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   for (int i = 0; i < nmc; ++i) l->AddEntry(h_mc_B[i], labels[i], "F");
   l->AddEntry(h_data_B, "data", "P");

   TCanvas * c = new TCanvas("c_plotControlRegions", datatag, 800, 800);
   c->Divide(2,2);

   TPad * p2 = (TPad*)c->cd(2);
   s_B->Draw("HIST");
   h_data_B->Draw("PE, SAME"); 
   p2->SetLogy();
   s_B->SetMinimum(ymin);
   s_B->SetMaximum(ymax);
   l->Draw();

   TPad * p3 = (TPad*)c->cd(3);
   s_C->Draw("HIST");
   h_data_C->Draw("PE, SAME");
   p3->SetLogy();
   s_C->SetMinimum(ymin);
   s_C->SetMaximum(ymax);
   l->Draw();

   TPad * p4 = (TPad*)c->cd(4);
   s_D->Draw("HIST");
   h_data_C->Draw("PE, SAME");
   p4->SetLogy();
   s_D->SetMinimum(ymin);
   s_D->SetMaximum(ymax);
   l->Draw();

   c->SaveAs("./plots/cr."+datatag+".pdf");
}

void yields_ZTauTau(const TString datatag="SingleMuon")
{
   const double ymin = 1.e2;
   const double ymax = 1.e6;

   int nmc = 6;
   TString mctag[nmc];
   mctag[0] = "HToTauTau";
   mctag[1] = "TTJets";
   mctag[2] = "EWK";
   mctag[3] = "WJetsToLNu";
   mctag[4] = "DYJetsToEEMuMu_M50";
   mctag[5] = "DYJetsToTauTau_M50";
 
   TString labels[nmc];
   labels[0] = "H#rightarrow#tau#tau";
   labels[1] = "t#bar{t}";
   labels[2] = "Electroweak";
   labels[3] = "W#rightarrowl#nu";
   labels[4] = "Z/#gamma^{*} #rightarrow ee,#mu#mu";
   labels[5] = "Z/#gamma^{*} #rightarrow #tau#tau";

   std::vector<TString> filelists[nmc];
   filelists[0].push_back("VBFHToTauTau"); filelists[0].push_back("GluGluHToTauTau");
   filelists[1].push_back("TTJets");
   filelists[2].push_back("WW"); filelists[1].push_back("WZ"); filelists[1].push_back("ZZ"); filelists[1].push_back("EWKZ");
   filelists[3].push_back("WJetsToLNu");
   filelists[4].push_back("DYJetsToEEMuMu_M50");
   filelists[5].push_back("DYJetsToTauTau_M50");

   int colz[nmc];
   colz[0] = 28;
   colz[1] = 9;
   colz[2] = 224;
   colz[3] = 224;
   colz[4] = 78;
   colz[5] = 92;

   //fill the ABCD histograms for data
   std::vector<TString> dataset;
   
   if (datatag=="SingleMuon") {
      dataset.push_back("SingleMuon_A"); dataset.push_back("SingleMuon_B"); dataset.push_back("SingleMuon_C"); dataset.push_back("SingleMuon_D");
   }
   if (datatag=="EGamma") {
      dataset.push_back("EGamma_A"); dataset.push_back("EGamma_B"); dataset.push_back("EGamma_C"); dataset.push_back("EGamma_D");
   }
   if (datatag=="Tau") {
      dataset.push_back("Tau_A"); dataset.push_back("Tau_B"); dataset.push_back("Tau_C"); dataset.push_back("Tau_D");
   }
   
   makeHists(datatag, datatag, dataset, false);
   TFile *f_data = TFile::Open("./outputHists/"+datatag+"."+datatag+".root");
   TH1D * h_data = (TH1D*)f_data->Get("h_A");
   
   //fill the ABCD histograms for MC
   for (int i = 0; i < nmc; ++i) makeHists(mctag[i], datatag, filelists[i], true);
   double samplesum = 0.;

   TH1D * h_mc[nmc];
   for (int i = 0; i < nmc; ++i) {
      TFile * f = TFile::Open("./outputHists/"+mctag[i]+"."+datatag+".root");
      h_mc[i] = (TH1D*)f->Get("h_A");
      h_mc[i]->SetFillColor(colz[i]);
      samplesum += h_mc[i]->Integral();
   }

   makeQCDHists(datatag);
   //std::vector<TString> datasetqcd;
   //datasetqcd.push_back("QCD_Mu15");
   //makeHists("QCD", datatag, datasetqcd, true);
   
   TFile * f_QCD = TFile::Open("./outputHists/QCD."+datatag+".root");
   TH1D * h_QCD = (TH1D*)f_QCD->Get("h_A");
   samplesum += h_QCD->Integral();
   h_QCD->SetFillColor(6);   

   TH1D * r = (TH1D*)h_QCD->Clone("r");
   for (int i = 0; i < nmc; ++i) {
      r->Add(h_mc[i]);
   }
   r->Divide(h_data, r);
   
   for (int i = 0; i < nmc; ++i) {
      std::cout << mctag[i] << std::endl;
      std::cout << "   Integral(): " << h_mc[i]->Integral() << "; fraction of total:" << h_mc[i]->Integral()/samplesum << std::endl;
      std::cout << "   GetEntries(): " << h_mc[i]->GetEntries() << std::endl;
   }
   std::cout << "QCD" << std::endl;
   std::cout << "   Integral(): " << h_QCD->Integral() << "; fraction of total: " << h_QCD->Integral()/samplesum << std::endl;
   std::cout << "   GetEntries(): " << h_QCD->GetEntries() << std::endl;
 
   std::cout << "Data" << std::endl;
   std::cout << "   Integral(): " << h_data->Integral() << std::endl;
   std::cout << "   GetEntries(): " << h_data->GetEntries() << std::endl;

   THStack * s = new THStack("s", "");
   s->SetTitle(h_data->GetTitle());
   for (int i = 0; i < nmc; ++i) {
      s->Add(h_mc[i]);
   }
   s->Add(h_QCD);

   TCanvas * c = new TCanvas("c_yieldsZTauTau", datatag, 800, 400);
   c->Divide(2, 1);

   TPad * p1 = (TPad*)c->cd(1);
   h_data->SetMarkerStyle(20);
   h_data->SetMinimum(ymin);
   h_data->SetMaximum(ymax);
   h_data->Draw("P, E");
   h_data->SetStats(0);
   h_data->SetMinimum(ymin);
   h_data->SetMaximum(ymax);
   p1->SetLogy();
   s->Draw("HIST, SAME");
   s->SetMinimum(ymin);
   s->SetMaximum(ymax);
   h_data->Draw("P, E, SAME");

   TLegend * l = new TLegend(0.4, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   for (int i = 0; i < nmc; ++i) l->AddEntry(h_mc[i], labels[i], "F");
   l->AddEntry(h_QCD, "QCD", "F");
   l->AddEntry(h_data, "data", "P");
   l->Draw();

   c->cd(2);
   r->Draw("PE");
   r->SetMinimum(0);
   r->SetMaximum(2.);
   r->GetYaxis()->SetTitle("data / prediction");
   TLine * line = new TLine(h_data->GetBinLowEdge(1), 1., h_data->GetBinLowEdge(h_data->GetNbinsX()+1), 1.);
   line->SetLineStyle(2);
   line->Draw();
   r->SetMarkerStyle(20);
   r->SetStats(0);

   c->SaveAs("./plots/VisibleMass."+datatag+".pdf");

   plotControlRegions(datatag);
}

