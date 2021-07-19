#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>

void makeWHists(const TString channel="Electron")
{
   char fname[20];
   sprintf(fname, "%s_m0_unblind.root", channel.Data());
   TFile * f = TFile::Open(fname);
     
   TH1D * h_C = (TH1D*)((TH1D*)f->Get("h_mcsum_C"))->Clone("h_mcsum_C");
   h_C->SetLineWidth(2);
   TH1D * h_D = (TH1D*)((TH1D*)f->Get("h_mcsum_D"))->Clone("h_mcsum_D");
   h_D->SetLineWidth(2);

   TH1D * h_CoD = (TH1D*)h_C->Clone("h_CoD");
   h_CoD->Divide(h_D);

   TCanvas * c = new TCanvas("c_"+channel, channel, 800, 400);
   c->Divide(2, 1);
   c->cd(2);
   h_CoD->Draw("PE");
   h_CoD->SetStats(0);
   h_CoD->SetTitle("");
   h_CoD->SetMinimum(0.);
   h_CoD->SetMaximum(1.5);
   c->cd(1);
   h_C->SetLineColor(6);
   h_C->SetTitle("");
   h_C->SetMinimum(0);
   h_C->SetMaximum(2. * TMath::Max(h_C->GetMaximum(), h_D->GetMaximum()));
   h_C->Draw("HIST, E");
   h_D->SetLineColor(7);
   h_D->Draw("HIST, E, SAME");
   h_C->SetStats(0);

   TLegend * l = new TLegend(0.4, 0.8, 0.875, 0.875);
   l->SetNColumns(2);
   l->AddEntry(h_C, "C", "L");
   l->AddEntry(h_D, "D", "L");
   l->SetBorderSize(0);
   l->Draw();

   char cname[20];
   sprintf(cname, "%s_m0_unblind.pdf", channel.Data());
   c->SaveAs(cname);

   const double cod1p = h_CoD->GetBinContent(2);
   const double cod1pe = h_CoD->GetBinError(2);
   const double cod3p = h_CoD->GetBinContent(4);
   const double cod3pe = h_CoD->GetBinError(4);
   std::cout << "1-prong fake rate: " << cod1p << " +- " << cod1pe << std::endl;
   std::cout << "3-prong fake rate: " << cod3p << " +- " << cod3pe << std::endl;
}

