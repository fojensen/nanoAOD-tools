#include <THStack.h>
#include <TLine.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TCut.h>
#include <iostream>
#include <TH1D.h>
#include <TLegend.h>
#include "addOverflow.h"

void runPoint(TH1D * h, const TString var)
{
   TCut baseline = "MuTauGamma_havePair==1 && MuMuGamma_havePair==0 && (HLT_IsoMu24||HLT_IsoMu27||HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1)";
   const TCut ss = "MuTauGamma_qq==+1";
   const TCut os = "MuTauGamma_qq==-1";
   const TCut isotau = "(64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   TCut antiisotau = "(8&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   //baseline = baseline && TCut("MuTauGamma_haveTriplet==1");

   const TCut regionA = os && isotau;
   const TCut regionB = ss && isotau;
   const TCut regionC = os && antiisotau;
   const TCut regionD = ss && antiisotau;
   const TCut cuts[4] = {regionA&&baseline, regionB&&baseline, regionC&&baseline, regionD&&baseline};
   const TString titles[4] = {"A", "B", "C", "D"};

   char cutsMC[4][1000];
   for (int i = 0; i < 4; ++i) {
      sprintf(cutsMC[i], "59725.419 * xsWeight * (%s && Sum$(TMath::Abs(GenPart_pdgId)==15 && (8192&GenPart_statusFlags))>=2)", TString(cuts[i]).Data());
   }
   
   char cutsEmbedded[4][1000];
   for (int i = 0; i < 4; ++i) {
      sprintf(cutsEmbedded[i], "genWeight * (%s)", TString(cuts[i]).Data());
   }

   TH1D * h_sum[4];
   for (int i = 0; i < 4; ++i) h_sum[i] = (TH1D*)h->Clone("h_sum");
   THStack * stack[4];
   for (int i = 0; i < 4; ++i) {
      stack[i] = new THStack();
      char title[100];
      sprintf(title, "%s;%s;%s", titles[i].Data(), h->GetXaxis()->GetTitle(), h->GetYaxis()->GetTitle());
      stack[i]->SetTitle(title);
   }
 
   TFile * f_ZZ = TFile::Open("./outputData/ZZ.root");
   TTree * t_ZZ = (TTree*)f_ZZ->Get("Events");
   TH1D * h_ZZ[4];
   std::cout << "ZZ" << std::endl;
   for (int i = 0; i < 4; ++i) {
      h_ZZ[i] = (TH1D*)h->Clone("h_ZZ_"+TString::Itoa(i, 10));
      std::cout << "   " << t_ZZ->Project(h_ZZ[i]->GetName(), var, cutsMC[i]) << " mc events." << std::endl;
      addOverflow(h_ZZ[i]);
      h_sum[i]->Add(h_ZZ[i]);
      h_ZZ[i]->SetFillColor(9);
      stack[i]->Add(h_ZZ[i]);
      std::cout << "h_ZZ: " << h_ZZ[i]->Integral() << std::endl;
   }
 
   TFile * f_WZ = TFile::Open("./outputData/WZ.root");
   TTree * t_WZ = (TTree*)f_WZ->Get("Events");
   TH1D * h_WZ[4];
   std::cout << "WZ" << std::endl;
   for (int i = 0; i < 4; ++i) {
      h_WZ[i] = (TH1D*)h->Clone("h_WZ_"+TString::Itoa(i, 10));
      std::cout << "   " << t_WZ->Project(h_WZ[i]->GetName(), var, cutsMC[i]) << " mc events." << std::endl;
      addOverflow(h_WZ[i]);
      h_sum[i]->Add(h_WZ[i]);
      h_WZ[i]->SetFillColor(8);
      stack[i]->Add(h_WZ[i]);
      std::cout << "   h_WZ: " << h_WZ[i]->Integral() << std::endl;
   }

   TFile * f_WW = TFile::Open("./outputData/WW.root");
   TTree * t_WW = (TTree*)f_WW->Get("Events");
   TH1D * h_WW[4];
   std::cout << "WW" << std::endl;
   for (int i = 0; i < 4; ++i) {
      h_WW[i] = (TH1D*)h->Clone("h_WW_"+TString::Itoa(i, 10));
      std::cout << "   " << t_WW->Project(h_WW[i]->GetName(), var, cutsMC[i]) << " mc events." << std::endl;
      addOverflow(h_WW[i]);
      h_sum[i]->Add(h_WW[i]);
      h_WW[i]->SetFillColor(7);
      stack[i]->Add(h_WW[i]);
      std::cout << "   h_WW: " << h_WW[i]->Integral() << std::endl;
   }

   TFile * f_TTTo2L2Nu = TFile::Open("./outputData/TTTo2L2Nu.root");
   TTree * t_TTTo2L2Nu = (TTree*)f_TTTo2L2Nu->Get("Events");
   TH1D * h_TTTo2L2Nu[4];
   std::cout << "TTTo2L2Nu" << std::endl;
   for (int i = 0; i < 4; ++i) {
      h_TTTo2L2Nu[i] = (TH1D*)h->Clone("h_TTTo2L2Nu_"+TString::Itoa(i, 10));
      std::cout << "   " << t_TTTo2L2Nu->Project(h_TTTo2L2Nu[i]->GetName(), var, cutsMC[i]) << " mc events." << std::endl;
      addOverflow(h_TTTo2L2Nu[i]);
      h_sum[i]->Add(h_TTTo2L2Nu[i]);
      h_TTTo2L2Nu[i]->SetFillColor(6);
      stack[i]->Add(h_TTTo2L2Nu[i]);
      std::cout << "   h_TTTo2L2Nu: " << h_TTTo2L2Nu[i]->Integral() << std::endl;
   }  

   TFile * f_DYJetsToLL_M10 = TFile::Open("./outputData/DYJetsToLL_M-10to50.root");
   TTree * t_DYJetsToLL_M10 = (TTree*)f_DYJetsToLL_M10->Get("Events");
   TH1D * h_DYJetsToLL_M10[4];
   std::cout << "DYJetsToLL_M-50_M10" << std::endl;
   for (int i = 0; i < 4; ++i) {
      h_DYJetsToLL_M10[i] = (TH1D*)h->Clone("h_DYJetsToLL_M10_"+TString::Itoa(i, 10));
      std::cout << "   " << t_DYJetsToLL_M10->Project(h_DYJetsToLL_M10[i]->GetName(), var, cutsMC[i]) << " mc events." << std::endl;
      addOverflow(h_DYJetsToLL_M10[i]);
      h_sum[i]->Add(h_DYJetsToLL_M10[i]);
      h_DYJetsToLL_M10[i]->SetFillColor(97);
      stack[i]->Add(h_DYJetsToLL_M10[i]);
      std::cout << "   h_DYJetsToLL_M10: " << h_DYJetsToLL_M10[i]->Integral() << std::endl;
   }
 
   TFile * f_DYJetsToLL = TFile::Open("./outputData/DYJetsToLL_M-50.root");
   TTree * t_DYJetsToLL = (TTree*)f_DYJetsToLL->Get("Events");
   TH1D * h_DYJetsToLL[4];
   std::cout << "DYJetsToLL_M-50" << std::endl;
   for (int i = 0; i < 4; ++i) {
      h_DYJetsToLL[i] = (TH1D*)h->Clone("h_DYJetsToLL_"+TString::Itoa(i, 10));
      std::cout << "   " << t_DYJetsToLL->Project(h_DYJetsToLL[i]->GetName(), var, cutsMC[i]) << " mc events." << std::endl;
      addOverflow(h_DYJetsToLL[i]);
      h_sum[i]->Add(h_DYJetsToLL[i]);
      h_DYJetsToLL[i]->SetFillColor(96);
      stack[i]->Add(h_DYJetsToLL[i]);
      std::cout << "   h_DYJetsToLL: " << h_DYJetsToLL[i]->Integral() << std::endl;
   }

   TFile * f_Embedded = TFile::Open("./outputData/Embedded_2018.root");
   TTree * t_Embedded = (TTree*)f_Embedded->Get("Events");
   TH1D * h_Embedded[4];
   std::cout << "Embedded" << std::endl;
   for (int i = 0; i < 4; ++i) {
      h_Embedded[i] = (TH1D*)h->Clone("h_Embedded_"+TString::Itoa(i, 10));
      std::cout << "   " << t_Embedded->Project(h_Embedded[i]->GetName(), var, cutsEmbedded[i]) << " Embedded events." << std::endl;
      addOverflow(h_Embedded[i]);
      std::cout << "   h_Embedded: " << h_Embedded[i]->Integral() << std::endl;
      char buffer[1000];
      sprintf(buffer, "%s;%s;%s", titles[i].Data(), h->GetXaxis()->GetTitle(), h->GetYaxis()->GetTitle());
      h_Embedded[i]->SetTitle(buffer);
   }

   TH1D * r[4];
   for (int i = 0; i < 4; ++i) {
      r[i] = (TH1D*)h_Embedded[i]->Clone("r_"+TString::Itoa(i, 10));
      r[i]->Divide(h_sum[i]);
      char buffer[1000];
      sprintf(buffer, "%s;%s;embedded / mc", titles[i].Data(), h->GetXaxis()->GetTitle());
      r[i]->SetTitle(buffer);
   }

   TCanvas * c = new TCanvas("c_"+TString(h->GetName()), var, 1600, 800);
   c->Divide(4, 2);

   TLegend * leg = new TLegend(0.25, 0.75, 0.875, 0.875);
   leg->SetBorderSize(0);
   leg->SetNColumns(2);
   leg->AddEntry(h_ZZ[0], "ZZ", "F");
   leg->AddEntry(h_WZ[0], "WZ", "F");
   leg->AddEntry(h_WW[0], "WW", "F");
   leg->AddEntry(h_TTTo2L2Nu[0], "TTTo2L2Nu", "F");
   leg->AddEntry(h_DYJetsToLL_M10[0], "DYJetsToLL_M-10to50", "F");
   leg->AddEntry(h_DYJetsToLL[0], "DYJetsToLL_M-50", "F");
   leg->AddEntry(h_Embedded[0], "Embedded", "P");

   for (int i = 0; i < 4; ++i) {
      TPad * p = (TPad*)c->cd(1+i);
      h_Embedded[i]->SetMarkerStyle(20);
      h_Embedded[i]->Draw("PE");
      stack[i]->SetMinimum(1.);
      stack[i]->SetMaximum(10000000.);
      stack[i]->Draw("HIST");
      h_Embedded[i]->Draw("PE, SAME");
      leg->Draw();
      p->SetLogy();
   }

   TLine * lin = new TLine(h->GetBinLowEdge(1), 1., h->GetBinLowEdge(h->GetNbinsX()+1), 1.);
   lin->SetLineStyle(2); 
   for (int i = 0; i < 4; ++i) {
      c->cd(5+i);
      r[i]->Draw("PE");
      r[i]->SetMarkerStyle(20);
      r[i]->SetTitle(titles[i]);
      r[i]->SetStats(0);
      r[i]->SetMinimum(0.);
      r[i]->SetMaximum(2.);
      lin->Draw();
   }

   c->SaveAs("./plots/embedded."+TString(h->GetName())+".pdf");
}

void embeddedStudy()
{
   TH1D h_nBJetT("h_nBJetT", ";# of b-jets (tight);events / 1", 4, -0.5, 3.5);
   runPoint(&h_nBJetT, "JetProducer_nBJetT");

   TH1D h_VisibleMass("h_VisibleMass", ";visible mass (#mu+#tau_{h}) [GeV];events / 25 GeV", 10, 0., 250.); 
   runPoint(&h_VisibleMass, "MuTauGamma_MuTauMass");

   TH1D h_mt("h_mt", ";m_{T} (#mu, MET) [GeV];events / 20 GeV", 10, 0., 200.);
   runPoint(&h_mt, "MuTauGamma_mt");

   TH1D h_unitbin("h_unitbin", ";the unit bin;events", 1, -0.5, 0.5);
   runPoint(&h_unitbin, "0.");

   //TH1D h_photonpt("h_photonPt", ";p_{T} [GeV];events / 25 GeV", 8, 32., 232.);
   //runPoint(&h_photonpt, "Photon_pt[MuTauGamma_PhotonIdx]");
 
   //const int n = 4;
   //const double x[n+1] = {0., 100., 200., 300., 500.}; 
   //TH1D h_mincolmass("h_mincolmass", ";min collinear mass [GeV];events / bin", n, x);
   //runPoint(&h_mincolmass, "TMath::Min(MuTauGamma_MuGammaCollinearMass, MuTauGamma_TauGammaCollinearMass)"); 
}

