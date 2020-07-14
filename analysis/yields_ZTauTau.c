#include <iostream>
#include <THStack.h>
#include <TCut.h>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>

double addOverflow(TH1D * h)
{
   const int n = h->GetNbinsX();
   const double o = h->GetBinContent(n+1);
   h->AddBinContent(n, o);
   h->SetBinContent(n+1, 0.);
   h->SetBinError(n+1, 0.);
   return o;
}

TFile * makeHists(const TString tag, const double weight=0.)
{
   std::cout << tag << std::endl;
   char infile[1000];
   //sprintf(infile, "root://cmseos.fnal.gov//store/user/hats/2020/Tau/%s.root", tag.Data());
   sprintf(infile, "./outputData/%s.root", tag.Data());
   TFile * f_in = TFile::Open(infile);
   TTree * t = (TTree*)f_in->Get("Events");

   TCut baseline = "MuMuProducer_HavePair==0 && MuTauProducer_HavePair==1";
   baseline = baseline && TCut("128&Tau_idDeepTau2017v2p1VSjet[MuTauProducer_TauIdx]");
   baseline = baseline && TCut("MuTauProducer_mT<40.");
   baseline = baseline && TCut("MuTauProducer_nBJetT==0");

   const TCut regionA = "MuTauProducer_qq==-1 && Muon_pfIsoId[MuTauProducer_MuIdx]>=4";
   const TCut regionB = "MuTauProducer_qq==+1 && Muon_pfIsoId[MuTauProducer_MuIdx]>=4";
   const TCut regionC = "MuTauProducer_qq==-1 && Muon_pfIsoId[MuTauProducer_MuIdx]<4";
   const TCut regionD = "MuTauProducer_qq==+1 && Muon_pfIsoId[MuTauProducer_MuIdx]<4";
  
   char bufferA[1000], bufferB[1000], bufferC[1000], bufferD[1000];
   
   if (weight) {
      sprintf(bufferA, "%f * (%s)", weight, TString(baseline && regionA).Data());
      sprintf(bufferB, "%f * (%s)", weight, TString(baseline && regionB).Data());
      sprintf(bufferC, "%f * (%s)", weight, TString(baseline && regionC).Data());
      sprintf(bufferD, "%f * (%s)", weight, TString(baseline && regionD).Data());
   } else {
      sprintf(bufferA, "%s", TString(baseline && regionA).Data());
      sprintf(bufferB, "%s", TString(baseline && regionB).Data());
      sprintf(bufferC, "%s", TString(baseline && regionC).Data());
      sprintf(bufferD, "%s", TString(baseline && regionD).Data());
   }

   const TString var = "MuTauProducer_MuTauVisMass";
   TH1D * h_A = new TH1D("h_A", ";#mu+#tau_{h} visible mass [GeV];events / 25 GeV", 12, 0., 300.);
   TH1D * h_B = (TH1D*)h_A->Clone("h_B");
   TH1D * h_C = (TH1D*)h_A->Clone("h_C");
   TH1D * h_D = (TH1D*)h_A->Clone("h_D");

   const int n_A = t->Project(h_A->GetName(), var, bufferA);
   const int n_B = t->Project(h_B->GetName(), var, bufferB);
   const int n_C = t->Project(h_C->GetName(), var, bufferC);
   const int n_D = t->Project(h_D->GetName(), var, bufferD);

   const double i_A = h_A->Integral();
   const double i_B = h_B->Integral();
   const double i_C = h_C->Integral();
   const double i_D = h_D->Integral();

   std::cout << "   region | yield | mc events" << std::endl; 
   std::cout << "   A " << i_A << " " << n_A << std::endl;
   std::cout << "   B " << i_B << " " << n_B << std::endl;
   std::cout << "   C " << i_C << " " << n_C << std::endl;
   std::cout << "   D " << i_D << " " << n_D << std::endl;

   TFile * f_out = new TFile("./outputHists/"+tag+".root", "RECREATE");
   h_A->Write();
   h_B->Write();
   h_C->Write();
   h_D->Write();
   f_out->Close();
   return f_out;
}

TFile * makeQCDHists()
{
   std::cout << "QCD" << std::endl;
   TFile * f_data = TFile::Open("./outputHists/SingleMuon_2018D.root");
   //TH1D * data_A = (TH1D*)f_data->Get("h_A");
   TH1D * data_B = (TH1D*)f_data->Get("h_B");
   TH1D * data_C = (TH1D*)f_data->Get("h_C");
   TH1D * data_D = (TH1D*)f_data->Get("h_D");
   
   TFile * f_WJetsToLNu = TFile::Open("./outputHists/WJetsToLNu.root");
   //TH1D * WJetsToLNu_A = (TH1D*)f_WJetsToLNu->Get("h_A");
   TH1D * WJetsToLNu_B = (TH1D*)f_WJetsToLNu->Get("h_B");
   TH1D * WJetsToLNu_C = (TH1D*)f_WJetsToLNu->Get("h_C");
   TH1D * WJetsToLNu_D = (TH1D*)f_WJetsToLNu->Get("h_D");

   TFile * f_TTJets = TFile::Open("./outputHists/TTJets.root");
   //TH1D * TTJets_A = (TH1D*)f_TTJets->Get("h_A");
   TH1D * TTJets_B = (TH1D*)f_TTJets->Get("h_B");
   TH1D * TTJets_C = (TH1D*)f_TTJets->Get("h_C");
   TH1D * TTJets_D = (TH1D*)f_TTJets->Get("h_D");

   TFile * f_DYJetsToEEMuMu = TFile::Open("./outputHists/DYJetsToEEMuMu_M-50.root");
   //TH1D * DYJetsToEEMuMu_A = (TH1D*)f_DYJetsToEEMuMu->Get("h_A");
   TH1D * DYJetsToEEMuMu_B = (TH1D*)f_DYJetsToEEMuMu->Get("h_B");
   TH1D * DYJetsToEEMuMu_C = (TH1D*)f_DYJetsToEEMuMu->Get("h_C");
   TH1D * DYJetsToEEMuMu_D = (TH1D*)f_DYJetsToEEMuMu->Get("h_D");

   TFile * f_DYJetsToTauTau = TFile::Open("./outputHists/DYJetsToTauTau_M-50.root");
   //TH1D * DYJetsToTauTau_A = (TH1D*)f_DYJetsToTauTau->Get("h_A");
   TH1D * DYJetsToTauTau_B = (TH1D*)f_DYJetsToTauTau->Get("h_B");
   TH1D * DYJetsToTauTau_C = (TH1D*)f_DYJetsToTauTau->Get("h_C");
   TH1D * DYJetsToTauTau_D = (TH1D*)f_DYJetsToTauTau->Get("h_D");

   data_B->Add(TTJets_B, -1.);
   data_B->Add(DYJetsToEEMuMu_B, -1.);
   data_B->Add(DYJetsToTauTau_B, -1.);
   data_B->Add(WJetsToLNu_B, -1.);

   data_C->Add(TTJets_C, -1.);
   data_C->Add(DYJetsToEEMuMu_C, -1.);
   data_C->Add(DYJetsToTauTau_C, -1.);
   data_C->Add(WJetsToLNu_C, -1.);

   data_D->Add(TTJets_D, -1.);
   data_D->Add(DYJetsToEEMuMu_D, -1.);
   data_D->Add(DYJetsToTauTau_D, -1.);
   data_D->Add(WJetsToLNu_D, -1.);

   double B, Berr;
   B = data_B->IntegralAndError(1, data_B->GetNbinsX()+1, Berr);
   double C, Cerr;
   C = data_C->IntegralAndError(1, data_C->GetNbinsX()+1, Cerr);
   double D, Derr;
   D = data_D->IntegralAndError(1, data_D->GetNbinsX()+1, Derr);
   const double CoD = C/D;
   const double CoDerr = CoD * sqrt((Berr/B)*(Berr/B)+(Cerr/C)*(Cerr/C));
   const double BCoD = B * CoD;
   const double errBCoD = BCoD * sqrt((Berr/B)*(Berr/B)+(CoDerr/CoD)*(CoDerr/CoD));
   std::cout << "inclusive transfer factor: " << CoD << " +- " << CoDerr << std::endl;

   TH1D * h_CoD = (TH1D*)data_C->Clone("h_CoD");
   h_CoD->Divide(data_D);

   TH1D * h_QCD = (TH1D*)data_B->Clone("h_QCD");
   h_QCD->Scale(CoD);
   //h_QCD->Multiply(h_CoD);
   
   TFile * f_qcd = new TFile("./outputHists/QCD.root", "RECREATE");
   h_QCD->Write("h_A");
   data_B->Write("h_B");
   data_C->Write("h_C");
   data_D->Write("h_D");
   h_CoD->Write("h_CoD");
   f_qcd->Close();
   return f_qcd;
}

void plotControlRegions()
{
   const double lumi = 31742.979;
   double xsweight[4];
   xsweight[0] = lumi * 831.76 / 10244307.;
   xsweight[1] = lumi * 61334.9 / 70454125.;
   xsweight[2] = lumi * 6025.2 / 100194597.;
   xsweight[3] = lumi * 6025.2 / 100194597.;

   TFile *f_SingleMuon_2018D = TFile::Open("./outputHists/SingleMuon_2018D.root");
   TH1D * h_SingleMuon_2018D_B = (TH1D*)f_SingleMuon_2018D->Get("h_B");
   h_SingleMuon_2018D_B->SetMarkerStyle(20);
   TH1D * h_SingleMuon_2018D_C = (TH1D*)f_SingleMuon_2018D->Get("h_C");
   h_SingleMuon_2018D_C->SetMarkerStyle(20);
   TH1D * h_SingleMuon_2018D_D = (TH1D*)f_SingleMuon_2018D->Get("h_D");
   h_SingleMuon_2018D_D->SetMarkerStyle(20);

   TFile * f_TTJets = TFile::Open("./outputHists/TTJets.root");
   TH1D * h_TTJets_B = (TH1D*)f_TTJets->Get("h_B");
   TH1D * h_TTJets_C = (TH1D*)f_TTJets->Get("h_C");
   TH1D * h_TTJets_D = (TH1D*)f_TTJets->Get("h_D");
   h_TTJets_B->SetFillColor(2);
   h_TTJets_C->SetFillColor(2);
   h_TTJets_D->SetFillColor(2);

   TFile * f_WJetsToLNu = TFile::Open("./outputHists/WJetsToLNu.root");
   TH1D * h_WJetsToLNu_B = (TH1D*)f_WJetsToLNu->Get("h_B");
   TH1D * h_WJetsToLNu_C = (TH1D*)f_WJetsToLNu->Get("h_C");
   TH1D * h_WJetsToLNu_D = (TH1D*)f_WJetsToLNu->Get("h_D");
   h_WJetsToLNu_B->SetFillColor(3);
   h_WJetsToLNu_C->SetFillColor(3);
   h_WJetsToLNu_D->SetFillColor(3);

   TFile * f_DYJetsToEEMuMu = TFile::Open("./outputHists/DYJetsToEEMuMu_M-50.root");
   TH1D * h_DYJetsToEEMuMu_B = (TH1D*)f_DYJetsToEEMuMu->Get("h_B");
   TH1D * h_DYJetsToEEMuMu_C = (TH1D*)f_DYJetsToEEMuMu->Get("h_C");
   TH1D * h_DYJetsToEEMuMu_D = (TH1D*)f_DYJetsToEEMuMu->Get("h_D");
   h_DYJetsToEEMuMu_B->SetFillColor(4);
   h_DYJetsToEEMuMu_C->SetFillColor(4);
   h_DYJetsToEEMuMu_D->SetFillColor(4);
  
   TFile * f_DYJetsToTauTau = TFile::Open("./outputHists/DYJetsToTauTau_M-50.root");
   TH1D * h_DYJetsToTauTau_B = (TH1D*)f_DYJetsToTauTau->Get("h_B");
   TH1D * h_DYJetsToTauTau_C = (TH1D*)f_DYJetsToTauTau->Get("h_C");
   TH1D * h_DYJetsToTauTau_D = (TH1D*)f_DYJetsToTauTau->Get("h_D");
   h_DYJetsToTauTau_B->SetFillColor(5);
   h_DYJetsToTauTau_C->SetFillColor(5);
   h_DYJetsToTauTau_D->SetFillColor(5);

   THStack * s_B = new THStack("s_B", "");
   s_B->SetTitle("B;#mu+#tau_{h} visible mass [GeV];events / 25 GeV");
   s_B->Add(h_TTJets_B);
   s_B->Add(h_WJetsToLNu_B);
   s_B->Add(h_DYJetsToEEMuMu_B);
   s_B->Add(h_DYJetsToTauTau_B);   

   THStack * s_C = new THStack("s_C", "");
   s_C->SetTitle("C;#mu+#tau_{h} visible mass [GeV];events / 25 GeV");
   s_C->Add(h_TTJets_C);
   s_C->Add(h_WJetsToLNu_C);
   s_C->Add(h_DYJetsToEEMuMu_C);
   s_C->Add(h_DYJetsToTauTau_C);

   THStack * s_D = new THStack("s_D", "");
   s_D->SetTitle("D;#mu+#tau_{h} visible mass [GeV];events / 25 GeV");
   s_D->Add(h_TTJets_D);
   s_D->Add(h_WJetsToLNu_D);
   s_D->Add(h_DYJetsToEEMuMu_D);
   s_D->Add(h_DYJetsToTauTau_D);
   
   TLegend * l = new TLegend(0.5, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   l->AddEntry(h_TTJets_B, "t#bar{t}", "F");
   l->AddEntry(h_WJetsToLNu_B, "W#rightarrow#ell#nu", "F");
   l->AddEntry(h_DYJetsToEEMuMu_B, "Z#rightarrow ee, #mu#mu", "F");
   l->AddEntry(h_DYJetsToTauTau_B, "Z#rightarrow #tau#tau", "F");
   l->AddEntry(h_SingleMuon_2018D_B, "data", "P");

   TCanvas * c = new TCanvas("c_cr", "", 800, 800);
   c->Divide(2,2);

   TPad * p2 = (TPad*)c->cd(2);
   s_B->Draw("HIST");
   h_SingleMuon_2018D_B->Draw("PE, SAME"); 
   p2->SetLogy();
   s_B->SetMinimum(1.);
   s_B->SetMaximum(10000.);
   l->Draw();

   TPad * p3 = (TPad*)c->cd(3);
   s_C->Draw("HIST");
   h_SingleMuon_2018D_C->Draw("PE, SAME");
   p3->SetLogy();
   s_C->SetMinimum(1.);
   s_C->SetMaximum(10000.);
   l->Draw();

   TPad * p4 = (TPad*)c->cd(4);
   s_D->Draw("HIST");
   h_SingleMuon_2018D_C->Draw("PE, SAME");
   p4->SetLogy();
   s_D->SetMinimum(1.);
   s_D->SetMaximum(10000.);
   l->Draw();

   c->SaveAs("./plots/cr.pdf");  

}

void yields_ZTauTau()
{
   makeHists("SingleMuon_2018D");

   const double lumi = 31742.979;
   double xsweight[4];
   xsweight[0] = lumi * 831.76 / 10244307.;
   xsweight[1] = lumi * 61334.9 / 70454125.;
   xsweight[2] = lumi * 6025.2 / 100194597.;
   xsweight[3] = lumi * 6025.2 / 100194597.;
   makeHists("TTJets", xsweight[0]);
   makeHists("WJetsToLNu", xsweight[1]);
   makeHists("DYJetsToEEMuMu_M-50", xsweight[2]);
   makeHists("DYJetsToTauTau_M-50", xsweight[3]);
   makeQCDHists();

   TFile *f_SingleMuon_2018D = TFile::Open("./outputHists/SingleMuon_2018D.root");
   TH1D * h_SingleMuon_2018D = (TH1D*)f_SingleMuon_2018D->Get("h_A");
   h_SingleMuon_2018D->SetMarkerStyle(20);

   double mcsum = 0.;

   TFile * f_TTJets = TFile::Open("./outputHists/TTJets.root");
   TH1D * h_TTJets = (TH1D*)f_TTJets->Get("h_A");
   h_TTJets->SetFillColor(2);
   mcsum += h_TTJets->Integral();

   TFile * f_QCD = TFile::Open("./outputHists/QCD.root");
   TH1D * h_QCD = (TH1D*)f_QCD->Get("h_A");
   h_QCD->SetFillColor(6);
   mcsum += h_QCD->Integral();
   
   TFile * f_WJetsToLNu = TFile::Open("./outputHists/WJetsToLNu.root");
   TH1D * h_WJetsToLNu = (TH1D*)f_WJetsToLNu->Get("h_A");
   h_WJetsToLNu->SetFillColor(3);
   mcsum += h_WJetsToLNu->Integral();

   TFile * f_DYJetsToEEMuMu = TFile::Open("./outputHists/DYJetsToEEMuMu_M-50.root");
   TH1D * h_DYJetsToEEMuMu = (TH1D*)f_DYJetsToEEMuMu->Get("h_A");
   h_DYJetsToEEMuMu->SetFillColor(4);
   mcsum += h_DYJetsToEEMuMu->Integral();
  
   TFile * f_DYJetsToTauTau = TFile::Open("./outputHists/DYJetsToTauTau_M-50.root");
   TH1D * h_DYJetsToTauTau = (TH1D*)f_DYJetsToTauTau->Get("h_A");
   h_DYJetsToTauTau->SetFillColor(5);
   mcsum += h_DYJetsToTauTau->Integral();

   std::cout << "fractions of expected background: " << std::endl;
   std::cout << "   TTJets: " << h_TTJets->Integral()/mcsum << std::endl;
   std::cout << "   QCD: " << h_QCD->Integral()/mcsum << std::endl;
   std::cout << "   WJetsToLNu: " << h_WJetsToLNu->Integral()/mcsum << std::endl;
   std::cout << "   DYJetsToEEMuMu: " << h_DYJetsToEEMuMu->Integral()/mcsum << std::endl;
   std::cout << "   DYJetsToTauTau: " << h_DYJetsToTauTau->Integral()/mcsum << std::endl;
 
   TCanvas * c = new TCanvas("c_ZMuTauVisibleMass", "", 400, 400);
   h_SingleMuon_2018D->Draw("P, E");
   THStack * s = new THStack("s", "");
   s->SetTitle(h_SingleMuon_2018D->GetTitle());
   s->Add(h_TTJets);
   s->Add(h_QCD);
   s->Add(h_WJetsToLNu);
   s->Add(h_DYJetsToEEMuMu);
   s->Add(h_DYJetsToTauTau);
   s->Draw("HIST, SAME");
   h_SingleMuon_2018D->Draw("PE, SAME");
   c->SetLogy();
   h_SingleMuon_2018D->SetStats(0);
   h_SingleMuon_2018D->SetMinimum(10.);
   h_SingleMuon_2018D->SetMaximum(1000000.);

   TLegend * l = new TLegend(0.5, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   l->AddEntry(h_TTJets, "t#bar{t}", "F");
   l->AddEntry(h_QCD, "QCD", "F");
   l->AddEntry(h_WJetsToLNu, "W#rightarrow#ell#nu", "F");
   l->AddEntry(h_DYJetsToEEMuMu, "Z#rightarrow ee, #mu#mu", "F");
   l->AddEntry(h_DYJetsToTauTau, "Z#rightarrow #tau#tau", "F");
   l->AddEntry(h_SingleMuon_2018D, "data", "P");
   l->Draw();

   c->SaveAs("./plots/ZMuTauVisibleMass.pdf");

   plotControlRegions();
}

