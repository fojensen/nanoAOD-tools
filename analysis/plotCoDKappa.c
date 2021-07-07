#include <iostream>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TLine.h>

void plotCoDKappa_unblind(const TString channel)
{
   TGraphErrors * g_CoD_1p = new TGraphErrors(12);
   TGraphErrors * g_CoD_3p = new TGraphErrors(12);
   TGraphErrors * g_kappa_1p = new TGraphErrors(12);
   TGraphErrors * g_kappa_3p = new TGraphErrors(12);

   for (int i = 0; i < 12; ++i) {
      std::cout << "point i: " << i << std::endl;
      char fname[20];
      sprintf(fname, "../condor/%s_m%d_unblind.root", channel.Data(), 10*i);
      std::cout << "   opening file: " << fname << std::endl;    
      TFile * f = TFile::Open(fname);
      if (!f) {
         std::cout << "file not found!" << std::endl;
         continue;
      }
      const double pt = i*10.;
      std::cout << "   pt: " << pt << std::endl;
      TH1D * h_CoD = (TH1D*)f->Get("h_CoD");
      if (!h_CoD) {
         std::cout << "   h_CoD not found!" << std::endl;
         continue;
      }
      const double CoD_1p = h_CoD->GetBinContent(2);
      const double CoDerr_1p = h_CoD->GetBinError(2);
      const double CoD_3p = h_CoD->GetBinContent(4);
      const double CoDerr_3p = h_CoD->GetBinError(4);
      std::cout << "   CoD_1p: " << CoD_1p << "+-" << CoDerr_1p << std::endl;
      std::cout << "   CoD_3p: " << CoD_3p << "+-" << CoDerr_3p << std::endl; 
      g_CoD_1p->SetPoint(i, pt, CoD_1p);
      g_CoD_1p->SetPointError(i, 0., CoDerr_1p);
      g_CoD_3p->SetPoint(i, pt, CoD_3p);
      g_CoD_3p->SetPointError(i, 0., CoDerr_3p);
      char title[20];
      sprintf(title, "%s;%s;%s", h_CoD->GetTitle(), "minimum photon p_{T} [GeV]", "C / D");
      g_CoD_1p->SetTitle(title);
   
      TH1D * h_kappa = (TH1D*)f->Get("h_kappa");
      const double kappa_1p = h_kappa->GetBinContent(2);
      const double kappaerr_1p = h_kappa->GetBinError(2);
      const double kappa_3p = h_kappa->GetBinContent(4);
      const double kappaerr_3p = h_kappa->GetBinError(4);
      g_kappa_1p->SetPoint(i, pt, kappa_1p);
      g_kappa_1p->SetPointError(i, 0., kappaerr_1p);
      g_kappa_3p->SetPoint(i, pt, kappa_3p);
      g_kappa_3p->SetPointError(i, 0., kappaerr_3p);
      std::cout << "   kappa_1p: " << kappa_1p << "+-" << kappaerr_1p << std::endl;
      std::cout << "   kappa_3p: " << kappa_3p << "+-" << kappaerr_3p << std::endl;
      char title2[20];
      sprintf(title2, "%s;%s;%s", h_CoD->GetTitle(), "minimum photon p_{T} [GeV]", "#kappa");
      g_kappa_1p->SetTitle(title2);
   }

   TCanvas * c = new TCanvas("c_"+channel+"_unblind", "unblind", 800, 400);
   c->Divide(2, 1);
  
   c->cd(1);
   g_CoD_1p->SetMarkerColor(6);
   g_CoD_1p->SetMarkerStyle(7);
   g_CoD_1p->SetLineColor(6);
   g_CoD_3p->SetMarkerColor(7);
   g_CoD_3p->SetMarkerStyle(7);
   g_CoD_3p->SetLineColor(7);
   g_CoD_1p->Draw("APE");
   g_CoD_3p->Draw("PE, SAME");
   g_CoD_1p->SetMinimum(0.);
   g_CoD_1p->SetMaximum(1.);

   TLegend * l = new TLegend(0.3, 0.8, 0.875, 0.875);
   l->SetNColumns(2);
   l->SetBorderSize(0);
   l->AddEntry(g_CoD_1p, "1-prong", "P");
   l->AddEntry(g_CoD_3p, "3-prong", "P");
   l->Draw();

   c->cd(2);
   g_kappa_1p->SetMarkerColor(6);
   g_kappa_1p->SetMarkerStyle(7);
   g_kappa_1p->SetLineColor(6);
   g_kappa_1p->Draw("APE");
   g_kappa_1p->SetMinimum(0.);
   g_kappa_1p->SetMaximum(2.);

   g_kappa_3p->SetMarkerColor(7);
   g_kappa_3p->SetMarkerStyle(7);
   g_kappa_3p->SetLineColor(7);
   g_kappa_3p->Draw("PE, SAME");
   l->Draw();

   TLine * line = new TLine(-0.5, 1., 3.5, 1.);
   line->SetLineStyle(2);
   line->Draw();

   char savetag[20];
   sprintf(savetag, "./plots/%s_CoDKappa_unblind.pdf", channel.Data());
   c->SaveAs(savetag);
}

void plotCoDKappa_blind(const TString channel)
{
   TGraphErrors * g_CoD_1p = new TGraphErrors(12);
   TGraphErrors * g_CoD_3p = new TGraphErrors(12);

   for (int i = 0; i < 12; ++i) {
      std::cout << "i: " << i << std::endl;
      char fname[20];
      sprintf(fname, "../condor/%s_m%d_blind.root", channel.Data(), 10*i); 
      std::cout << "   opening file: " << fname << std::endl;
      TFile * f = TFile::Open(fname);
      if (!f) {
         std::cout << "   file not found!" << std::endl;
         continue;
      }
      const double pt = i*10;
      std::cout << "   pt: " << pt << std::endl;

      TH1D * h_CoD = (TH1D*)f->Get("h_CoD");
      if (!h_CoD) {
         std::cout << "   h_CoD is not found!" << std::endl;
         continue;
      }
      const double CoD_1p = h_CoD->GetBinContent(2);
      const double CoDerr_1p = h_CoD->GetBinError(2);
      const double CoD_3p = h_CoD->GetBinContent(4);
      const double CoDerr_3p = h_CoD->GetBinError(4);
      std::cout << "   CoD_1p: " << CoD_1p << "+-" << CoDerr_1p << std::endl;
      std::cout << "   CoD_3p: " << CoD_3p << "+-" << CoDerr_3p << std::endl;
      char title[20];
      sprintf(title, "%s;%s;%s", h_CoD->GetTitle(), "minimum photon p_{T} [GeV]", "C / D");
      g_CoD_1p->SetTitle(title);
      g_CoD_3p->SetTitle(title);
      g_CoD_1p->SetPoint(i, pt, CoD_1p);
      g_CoD_1p->SetPointError(i, 0., CoDerr_1p);
      g_CoD_3p->SetPoint(i, pt, CoD_3p);
      g_CoD_3p->SetPointError(i, 0., CoDerr_3p);
   }

   TCanvas * c = new TCanvas("c_"+channel+"_blind", "blind", 400, 400);
 
   g_CoD_3p->SetMarkerColor(6);
   g_CoD_3p->SetMarkerStyle(7);
   g_CoD_3p->SetLineColor(6);

   g_CoD_1p->SetMarkerColor(7);
   g_CoD_1p->SetMarkerStyle(7);
   g_CoD_1p->SetLineColor(7);
   g_CoD_1p->SetMinimum(0.);
   g_CoD_1p->SetMaximum(1.);

   g_CoD_1p->Draw("APE");
   g_CoD_3p->Draw("PE, SAME");

   TLegend * l = new TLegend(0.3, 0.8, 0.875, 0.875);
   l->SetNColumns(2);
   l->SetBorderSize(0);
   l->AddEntry(g_CoD_1p, "1-prong", "P");
   l->AddEntry(g_CoD_3p, "3-prong", "P");
   l->Draw();

   TLine * line = new TLine(-0.5, 1., 3.5, 1.);
   line->SetLineStyle(2);
   line->Draw();

   char savetag[20];
   sprintf(savetag, "./plots/%s_CoD_blind.pdf", channel.Data());
   c->SaveAs(savetag);
}

