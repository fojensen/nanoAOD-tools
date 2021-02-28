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

TFile * makeHists(const TString nametag, const TString datatag, const std::vector<TString> filelist, const bool isMC=false, const TCut specialcuts="1>0")
{
   std::cout << "makeHists() " << nametag << " " << datatag << std::endl;
   
   TH1D * h = new TH1D("h_"+nametag, ";visible mass [GeV];events / 10 GeV", 25, 0., 250.);
   //TH1D * h = new TH1D("h_"+nametag, ";mass window?;events", 2, -0.5, 1.5);
 
   // load in your input trees  
   TChain t("Events");
   for (auto i = filelist.begin(); i != filelist.end(); ++i) {
      std::cout << "   Adding " << *i << std::endl;
      if (isMC) {
         t.Add("./outputData/" + *i + ".root");
      } else {
         t.Add(*i + ".root");
      }
   }

   TString var, xtitle;
   TCut baseline, regionA, regionB, regionC, regionD;

   baseline = TCut("MuMu_HavePair==0 || (MuMu_HavePair==1 && MuMu_Mass<50.)");
   baseline = baseline && TCut("JetProducer_nBJetM==0");
   baseline = baseline && TCut("EE_HavePair==0 || (EE_HavePair==1 && EE_Mass<50.)");

   if (datatag=="EGamma") {
   // e + tauh
   //var = "ElTau_Mass";
   var = "TMath::Min(ElTau_ElCollMass, ElTau_TauCollMass)";
   //var = "(ElTau_ElCollMass>=400.&&ElTau_ElCollMass<600.)||(ElTau_TauCollMass>=400.&&ElTau_TauCollMass<600.) ? 1 : 0";
   xtitle = "e+#tau_{h} visible mass [GeV]";
   baseline = "ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]<75.";
   baseline = baseline && TCut("HLT_Ele32_WPTight_Gsf && Electron_mvaFall17V2Iso_WP90[ElTau_ElIdx]");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==1");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=4)==0");
   //baseline = baseline && TCut("ElTau_mT<50.");
   regionA = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (64&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(64&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionC = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (64&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(64&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   }

   if (datatag=="SingleMuon") {
   // mu + tauh 
   var = "MuTau_Mass";
   var = "TMath::Min(MuTau_MuCollMass, MuTau_TauCollMass)";
   //var = "(MuTau_MuCollMass>=400.&&MuTau_MuCollMass<600.)||(MuTau_TauCollMass>=400.&&MuTau_TauCollMass<600.) ? 1 : 0";
   xtitle = "#mu+#tau_{h} visible mass [GeV]";
   baseline = "MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]<75.";
   baseline = baseline && TCut("(HLT_IsoMu24||HLT_IsoMu27) && Muon_pfIsoId[MuTau_MuIdx]>=4");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=4)==1");
   //baseline = baseline && TCut("MuTau_mT<50.");
   regionA = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (64&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(64&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionC = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (64&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(64&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   }

   if (datatag=="Tau") {
   // tauh + tauh
   var = "TauTau_Mass";
   var = "TMath::Min(TauTau_Tau0CollMass, TauTau_Tau1CollMass)";
   //var = "(TauTau_Tau0CollMass>=400.&&TauTau_Tau0CollMass<600.)||(TauTau_Tau1CollMass>=400.&&TauTau_Tau1CollMass<600.) ? 1 : 0";
   xtitle = "#tau_{h}+#tau_{h} visible mass [GeV]";
   baseline = "TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]<75.";
   baseline = baseline && TCut("TauTau_Trigger");
   baseline = baseline && TCut("Tau_pt[TauTau_Tau0Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1 && Tau_pt[TauTau_Tau1Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=4)==0");
   const TCut tau0pass = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) &&  (64&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
   const TCut tau0fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && !(64&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
   const TCut tau1pass = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) &&  (64&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
   const TCut tau1fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && !(64&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
   regionA = TCut("TauTau_qq==-1") &&  (tau0pass&&tau1pass);
   regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   regionC = TCut("TauTau_qq==+1") &&  (tau0pass&&tau1pass);
   regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   }

   if (isMC) baseline = baseline && specialcuts;

   const TString cutA = TString(baseline && regionA);
   const TString cutB = TString(baseline && regionB);
   const TString cutC = TString(baseline && regionC);
   const TString cutD = TString(baseline && regionD);

   char bufferA[2000], bufferB[2000], bufferC[2000], bufferD[2000];
   if (isMC) {
      //if (nametag=="DYJetsToEEMuMu_M50"||nametag=="DYJetsToTauTau_M50") {
      //   sprintf(bufferA, "59725.419 * xsWeight_DY * (%s)", cutA.Data());
      //   sprintf(bufferB, "59725.419 * xsWeight_DY * (%s)", cutB.Data());
      //   sprintf(bufferC, "59725.419 * xsWeight_DY * (%s)", cutC.Data());
      //   sprintf(bufferD, "59725.419 * xsWeight_DY * (%s)", cutD.Data());
      //} else {
         sprintf(bufferA, "59725.419 * xsWeight * (%s)", cutA.Data());
         sprintf(bufferB, "59725.419 * xsWeight * (%s)", cutB.Data());
         sprintf(bufferC, "59725.419 * xsWeight * (%s)", cutC.Data());
         sprintf(bufferD, "59725.419 * xsWeight * (%s)", cutD.Data());
      //}
   } else {
      sprintf(bufferA, "%s", cutA.Data());
      sprintf(bufferB, "%s", cutB.Data());
      sprintf(bufferC, "%s", cutC.Data());
      sprintf(bufferD, "%s", cutD.Data());
   }

   // define the histogram to visualize the data in
   TH1D * h_A = (TH1D*)h->Clone("h_A_"+nametag);
   TH1D * h_B = (TH1D*)h->Clone("h_B_"+nametag);
   TH1D * h_C = (TH1D*)h->Clone("h_C_"+nametag);
   TH1D * h_D = (TH1D*)h->Clone("h_D_"+nametag);

   // fill the histograms
   std::cout << "   filling " << h_A->GetName() << std::endl;
   const int n_A = t.Project(h_A->GetName(), var, bufferA);
   std::cout << "   filling " << h_B->GetName() << std::endl;
   const int n_B = t.Project(h_B->GetName(), var, bufferB);
   std::cout << "   filling " << h_C->GetName()  << std::endl;
   const int n_C = t.Project(h_C->GetName(), var, bufferC);
   std::cout << "   filling " << h_D->GetName() << std::endl;
   const int n_D = t.Project(h_D->GetName(), var, bufferD);
   std::cout << "   all Project finished." << std::endl;
  
    // get the inclusive yields
   double e_A, e_B, e_C, e_D;
   const double i_A = h_A->IntegralAndError(1, h->GetNbinsX()+1, e_A);
   const double i_B = h_B->IntegralAndError(1, h->GetNbinsX()+1, e_B);
   const double i_C = h_C->IntegralAndError(1, h->GetNbinsX()+1, e_C);
   const double i_D = h_D->IntegralAndError(1, h->GetNbinsX()+1, e_D);

   std::cout << "   region; yield; mc events, 1/sqrt" << std::endl; 
   std::cout << "   A; " << i_A << "+-" << e_A << "; " << n_A << ", " << 1./sqrt(n_A) << std::endl;
   std::cout << "   B; " << i_B << "+-" << e_B << "; " << n_B << ", " << 1./sqrt(n_B) << std::endl;
   std::cout << "   C; " << i_C << "+-" << e_C << "; " << n_C << ", " << 1./sqrt(n_C) << std::endl;
   std::cout << "   D; " << i_D << "+-" << e_D << "; " << n_D << ", " << 1./sqrt(n_D) << std::endl;

   //save those histograms
   TFile * f_out = new TFile("./outputHists/"+nametag+"."+datatag+".root", "RECREATE");
   h_A->Write("h_A");
   h_B->Write("h_B");
   h_C->Write("h_C");
   h_D->Write("h_D");
   f_out->Close();
   return f_out;
}

TFile * makeABCDHists(const TString datatag)
{
   std::cout << "makeABCDHists()" << std::endl;
   TFile * f_data = TFile::Open("./outputHists/"+datatag+"."+datatag+".root");
   TH1D * data_B = (TH1D*)f_data->Get("h_B");
   TH1D * data_C = (TH1D*)f_data->Get("h_C");
   TH1D * data_D = (TH1D*)f_data->Get("h_D");

   const int nmc = 7;
   TString mctag[nmc];
   mctag[0] = "HToTauTau";
   mctag[1] = "EWK";
   mctag[2] = "TTbar";
   mctag[3] = "ST";
   mctag[4] = "DYJetsToLL_M10";
   mctag[5] = "DYJetsToEEMuMu_M50";
   mctag[6] = "DYJetsToTauTau_M50";

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

   TCanvas * c = new TCanvas("c_makeABCDHists", datatag, 400, 400);
   h_CoD->Draw("PE");
   h_CoD->GetYaxis()->SetTitle("C / D");
   h_CoD->SetStats(0);
   h_CoD->SetMinimum(0.);
   h_CoD->SetMaximum(0.65);
   h_CoD->SetMarkerStyle(20);
   c->SaveAs("./plots/CoD."+datatag+".pdf");
 
   // save those histograms to a root file
   TFile * f_qcd = new TFile("./outputHists/ABCD."+datatag+".root", "RECREATE");
   data_B->Write("h_B");
   data_C->Write("h_C");
   data_D->Write("h_D");
   h_BCoD->Write("h_A");
   h_CoD->Write("h_CoD");
   f_qcd->Close();
   return f_qcd;
}


void plotControlRegions(const TString datatag)
{
   std::cout << "plotControlRegions()" << std::endl;
   const double ymin = 1.;
   const double ymax = 10000.;

   TFile *f_data = TFile::Open("./outputHists/"+datatag+"."+datatag+".root");
   TH1D * h_data_B = (TH1D*)f_data->Get("h_B");
   TH1D * h_data_C = (TH1D*)f_data->Get("h_C");
   TH1D * h_data_D = (TH1D*)f_data->Get("h_D");
   h_data_B->SetMarkerStyle(20);
   h_data_C->SetMarkerStyle(20);
   h_data_D->SetMarkerStyle(20);

   const int nsig = 2;
   TString sigtag[nsig];
   sigtag[0] = "Taustar_m250";
   sigtag[1] = "Taustar_m1000";
   TString siglabels[nsig];
   siglabels[0] = "#tau* 250";
   siglabels[1] = "#tau* 1000";
   int sigcolz[nsig] = {2, 3};
   TH1D *h_sig_B[nsig], *h_sig_C[nsig], *h_sig_D[nsig];
   for (int i = 0; i < nsig; ++i) {
      TFile * f = TFile::Open("./outputHists/"+sigtag[i]+"."+datatag+".root");
      h_sig_B[i] = (TH1D*)f->Get("h_B");
      h_sig_C[i] = (TH1D*)f->Get("h_C");
      h_sig_D[i] = (TH1D*)f->Get("h_D");
      h_sig_B[i]->SetFillColor(sigcolz[i]);
      h_sig_B[i]->SetLineStyle(2);
      h_sig_C[i]->SetFillColor(sigcolz[i]);
      h_sig_B[i]->SetLineStyle(2);
      h_sig_D[i]->SetFillColor(sigcolz[i]);
      h_sig_D[i]->SetLineStyle(2);
   }

   const int nmc = 7;
   TString mctag[nmc];
   mctag[0] = "HToTauTau";
   mctag[1] = "EWK";
   mctag[2] = "TTbar";
   mctag[3] = "ST";
   mctag[4] = "DYJetsToLL_M10";
   mctag[5] = "DYJetsToEEMuMu_M50";
   mctag[6] = "DYJetsToTauTau_M50";
 
   TString labels[nmc];
   labels[0] = "H#rightarrow#tau#tau";
   labels[1] = "Electroweak";
   labels[2] = "t#bar{t}";
   labels[3] = "single-top";
   labels[4] = "Z/#gamma^{*} #rightarrow ll (10to50)";
   labels[5] = "Z/#gamma^{*} #rightarrow ee,#mu#mu";
   labels[6] = "Z/#gamma^{*} #rightarrow #tau#tau";

   int colz[nmc];
   colz[0] = 2;
   colz[1] = 3;
   colz[2] = 4;
   colz[3] = 5;
   colz[4] = 6;
   colz[5] = 7;
   colz[6] = 8;

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
   l->AddEntry(h_sig_B[0], siglabels[0], "L");
   l->AddEntry(h_sig_B[1], siglabels[1], "L");

   TCanvas * c = new TCanvas("c_plotControlRegions", datatag, 800, 800);
   c->Divide(2,2);

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

   c->SaveAs("./plots/cr."+datatag+".pdf");
}

void yields_ZTauTau(const TString datatag="Tau")
{
   /*TString var, xtitle;
   TCut baseline, regionA, regionB, regionC, regionD;

   if (datatag=="EGamma") {
   // e + tauh
   var = "ElTau_Mass";
   //var = "(ElTau_ElCollMass>=400.&&ElTau_ElCollMass<600.)||(ElTau_TauCollMass>=400.&&ElTau_TauCollMass<600.) ? 1 : 0";
   xtitle = "e+#tau_{h} visible mass [GeV]";
   baseline = "ElTau_HaveTriplet>0 && Photon_pt[ElTau_PhotonIdx]<50.";
   baseline = baseline && TCut("HLT_Ele32_WPTight_Gsf && Electron_mvaFall17V2Iso_WP80[ElTau_ElIdx]");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP80)==1");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
   //baseline = baseline && TCut("ElTau_mT<50.");
   regionA = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionB = "ElTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionC = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   regionD = "ElTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[ElTau_TauIdx])";
   }

   if (datatag=="SingleMuon") {
   // mu + tauh 
   var = "MuTau_Mass";
   xtitle = "#mu+#tau_{h} visible mass [GeV]";
   baseline = "MuTau_HaveTriplet>0 && Photon_pt[MuTau_PhotonIdx]<50.";
   baseline = baseline && TCut("(HLT_IsoMu24||HLT_IsoMu27) && Muon_pfIsoId[MuTau_MuIdx]>=4");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP80)==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==1");
   baseline = baseline && TCut("MuTau_mT<50.");
   regionA = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionB = "MuTau_qq==-1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionC = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   regionD = "MuTau_qq==+1 && (8&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx]) && !(32&Tau_idDeepTau2017v2p1VSjet[MuTau_TauIdx])";
   }

   if (datatag=="Tau") {
   // tauh + tauh
   var = "TauTau_Mass";
   //var = "(TauTau_Tau0CollMass>=400.&&TauTau_Tau0CollMass<600.)||(TauTau_Tau1CollMass>=400.&&TauTau_Tau1CollMass<600.) ? 1 : 0";
   xtitle = "#tau_{h}+#tau_{h} visible mass [GeV]";
   baseline = "TauTau_HaveTriplet>0 && Photon_pt[TauTau_PhotonIdx]<50.";
   //baseline = baseline && TCut("TauTau_Mass>=100.");
   baseline = baseline && TCut("TauTau_Trigger");
   baseline = baseline && TCut("Tau_pt[TauTau_Tau0Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau0Idx])<2.1 && Tau_pt[TauTau_Tau1Idx]>=35. && TMath::Abs(Tau_eta[TauTau_Tau1Idx])<2.1");
   baseline = baseline && TCut("Sum$(Electron_pt>=12. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP80)==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=8. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=4)==0");
   const TCut tau0pass = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
   const TCut tau0fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau0Idx])";
   const TCut tau1pass = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) &&  (32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
   const TCut tau1fail = "(8&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx]) && !(32&Tau_idDeepTau2017v2p1VSjet[TauTau_Tau1Idx])";
   regionA = TCut("TauTau_qq==-1") &&  (tau0pass&&tau1pass);
   regionB = TCut("TauTau_qq==-1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   regionC = TCut("TauTau_qq==+1") &&  (tau0pass&&tau1pass);
   regionD = TCut("TauTau_qq==+1") && ((tau0pass&&tau1fail)||(tau0fail&&tau1pass));
   }

   baseline = baseline && TCut("JetProducer_nBJetM==0");
   baseline = baseline && TCut("ZProducer_EEHavePair==0 && ZProducer_MuMuHavePair==0");

   const TString cutA = TString(baseline && regionA);
   const TString cutB = TString(baseline && regionB);
   const TString cutC = TString(baseline && regionC);
   const TString cutD = TString(baseline && regionD);*/

   const double ymin = 1.;
   const double ymax = 10000.;

   const int nsig = 2;
   TString sigtag[nsig];
   TString siglabels[nsig];
   sigtag[0] = "Taustar_m250";
   sigtag[1] = "Taustar_m1000";
   siglabels[0] = "#tau* 250";
   siglabels[1] = "#tau* 1000";
   std::vector<TString> siglists[nsig];
   siglists[0].push_back("Taustar_m250");
   siglists[1].push_back("Taustar_m1000");
   TH1D *h_sig[nsig];
 
   for (int i = 0; i < nsig; ++i) {
      TFile * f = makeHists(sigtag[i], datatag, siglists[i], true);
   }
   for (int i = 0; i < nsig; ++i) {
      TFile * f = TFile::Open("./outputHists/"+sigtag[i]+"."+datatag+".root");
      h_sig[i] = (TH1D*)f->Get("h_A");
      h_sig[i]->SetLineStyle(2);
   }

   const int nmc = 7;
   TString mctag[nmc];
   mctag[0] = "HToTauTau";
   mctag[1] = "EWK";
   mctag[2] = "TTbar";
   mctag[3] = "ST";
   mctag[4] = "DYJetsToLL_M10";
   mctag[5] = "DYJetsToEEMuMu_M50";
   mctag[6] = "DYJetsToTauTau_M50";
 
   TString labels[nmc];
   labels[0] = "H#rightarrow#tau#tau";
   labels[1] = "Electroweak";
   labels[2] = "t#bar{t}";
   labels[3] = "single-top";
   labels[4] = "Z/#gamma^{*} #rightarrow ll m10to50";
   labels[5] = "Z/#gamma^{*} #rightarrow ee,#mu#mu";
   labels[6] = "Z/#gamma^{*} #rightarrow #tau#tau";

   std::vector<TString> filelists[nmc];
   filelists[0].push_back("VBFHToTauTau"); filelists[0].push_back("GluGluHToTauTau");
   filelists[1].push_back("WW"); filelists[1].push_back("WZ"); filelists[1].push_back("ZZ"); filelists[1].push_back("EWKZ");
   filelists[2].push_back("TTTo2L2Nu"); filelists[2].push_back("TTToSemileptonic"); filelists[2].push_back("TTToSemileptonic_ext3");
   filelists[3].push_back("ST_tW_top"); filelists[3].push_back("ST_tW_antitop"); filelists[3].push_back("ST_t_channel_antitop"); filelists[3].push_back("ST_t_channel_top");
   filelists[4].push_back("DYJetsToLL_M10");
   filelists[5].push_back("DYJetsToLL_M50");// filelists[5].push_back("DYNJetsToLL_M50");
   filelists[6].push_back("DYJetsToLL_M50");// filelists[6].push_back("DYNJetsToLL_M50");

   TCut specialcuts[nmc];
   for (int i = 0; i < nmc; ++i) specialcuts[i] = TCut("1>0");
   const TCut tautau = "Sum$(TMath::Abs(GenPart_pdgId)==15 && GenPart_genPartIdxMother>=0 && GenPart_pdgId[GenPart_genPartIdxMother]==23)>=2";
   specialcuts[5] = !tautau;
   specialcuts[6] = tautau;

   int colz[nmc];
   colz[0] = 2;
   colz[1] = 3;
   colz[2] = 4;
   colz[3] = 5;
   colz[4] = 6;
   colz[5] = 7;
   colz[6] = 8;

   //fill the ABCD histograms for data
   std::vector<TString> dataset;
 
   const TString eostag = "root://131.225.204.165:1094//store/user/fojensen/cmsdas_25022020/";
   if (datatag=="SingleMuon") {
      dataset.push_back(eostag+"SingleMuon_A");
      dataset.push_back(eostag+"SingleMuon_B");
      dataset.push_back(eostag+"SingleMuon_C");
      dataset.push_back(eostag+"SingleMuon_D");
   }
   if (datatag=="EGamma") {
      dataset.push_back(eostag+"EGamma_A");
      dataset.push_back(eostag+"EGamma_B");
      dataset.push_back(eostag+"EGamma_C");
      dataset.push_back(eostag+"EGamma_D");
   }
   if (datatag=="Tau") {
      dataset.push_back(eostag+"Tau_A");
      dataset.push_back(eostag+"Tau_B");
      dataset.push_back(eostag+"Tau_C");
      dataset.push_back(eostag+"Tau_D");
   }

   makeHists(datatag, datatag, dataset, false);
   TFile *f_data = TFile::Open("./outputHists/"+datatag+"."+datatag+".root");
   TH1D * h_data = (TH1D*)f_data->Get("h_A");

   //fill the ABCD histograms for MC
   for (int i = 0; i < nmc; ++i) makeHists(mctag[i], datatag, filelists[i], true, specialcuts[i]);
   double samplesum = 0.;

   TH1D * h_mc[nmc];
   for (int i = 0; i < nmc; ++i) {
      TFile * f = TFile::Open("./outputHists/"+mctag[i]+"."+datatag+".root");
      h_mc[i] = (TH1D*)f->Get("h_A");
      h_mc[i]->SetFillColor(colz[i]);
      samplesum += h_mc[i]->Integral(1, h_mc[i]->GetNbinsX()+1);
   }

   makeABCDHists(datatag);
 
   TFile * f_ABCD = TFile::Open("./outputHists/ABCD."+datatag+".root");
   TH1D * h_ABCD = (TH1D*)f_ABCD->Get("h_A");
   samplesum += h_ABCD->Integral(1, h_ABCD->GetNbinsX()+1);
   h_ABCD->SetFillColor(6);

   TH1D * r = (TH1D*)h_ABCD->Clone("r");
   for (int i = 0; i < nmc; ++i) {
      r->Add(h_mc[i]);
   }
   r->Divide(h_data, r);

   for (int i = 0; i < nmc; ++i) {
      std::cout << mctag[i] << std::endl;
      double mcerr = 0.;
      const double mcint = h_mc[i]->IntegralAndError(1, h_mc[i]->GetNbinsX()+1, mcerr);
      std::cout << "   IntegralAndError(): " << mcint << "+-" << mcerr << "; ferr=" << mcerr/mcint << std::endl;
      std::cout << "   fraction of total:" << mcint/samplesum << std::endl;
      std::cout << "   GetEntries(): " << h_mc[i]->GetEntries() << std::endl;
      std::cout << "   whole histogram Integral(): " << h_mc[i]->Integral() << std::endl;
   }

  for (int i = 0; i < nsig; ++i) {
      std::cout << sigtag[i] << std::endl;
      double sigerr = 0.;
      const double sigint = h_sig[i]->IntegralAndError(1, h_sig[i]->GetNbinsX()+1, sigerr);
      std::cout << "   IntegralAndError(): " << sigint << "+-" << sigerr << "; ferr=" << sigerr/sigint << std::endl;
      std::cout << "   GetEntries(): " << h_sig[i]->GetEntries() << std::endl;
      std::cout << "   whole histogram Integral(): " << h_sig[i]->Integral() << std::endl;
   }

   std::cout << "ABCD" << std::endl;
   double abcderr = 0;
   const double abcdint = h_ABCD->IntegralAndError(1, h_ABCD->GetNbinsX()+1, abcderr);
   std::cout << "   IntegralAndError(): " << abcdint << "+-" << abcderr << "; ferr=" << abcderr/abcdint << std::endl;
   std::cout << "   fraction of total: " << abcdint/samplesum << std::endl;
   std::cout << "   GetEntries(): " << h_ABCD->GetEntries() << std::endl;
   std::cout << "   whole histogram Integral(): " << h_ABCD->Integral() << std::endl;
 
   std::cout << "Data" << std::endl;
   double dataerr = 0;
   const double dataint = h_data->IntegralAndError(1, h_data->GetNbinsX(), dataerr);
   std::cout << "   IntegralAndError(): " << dataint << "+-" << dataerr << "; ferr=" << dataerr/dataint << std::endl;
   std::cout << "   GetEntries() +- sqrt(): " << h_data->GetEntries() << "+-" << sqrt(h_data->GetEntries()) << std::endl;
   std::cout << "   whole histogram Integral(): " << h_data->Integral() << std::endl;

   THStack * s = new THStack("s", "");
   s->SetTitle(h_data->GetTitle());
   for (int i = 0; i < nmc; ++i) {
      s->Add(h_mc[i]);
   }
   s->Add(h_ABCD);

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

   h_sig[0]->SetLineColor(2);
   h_sig[0]->Draw("HIST, E, SAME");
   h_sig[1]->SetLineColor(3);
   h_sig[1]->Draw("HIST, E, SAME");

   TLegend * l = new TLegend(0.4, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->SetNColumns(2);
   for (int i = 0; i < nmc; ++i) l->AddEntry(h_mc[i], labels[i], "F");
   l->AddEntry(h_ABCD, "ABCD", "F");
   l->AddEntry(h_data, "data", "P");
   l->AddEntry(h_sig[0], siglabels[0], "L");
   l->AddEntry(h_sig[1], siglabels[1], "L");
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

