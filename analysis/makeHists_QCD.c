#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <TH1D.h>
#include <TFile.h>

TFile * makeHists_QCD(const TString histname="h_vismass")
{
   TH1D * h_data[4];
   TFile * f_data = TFile::Open("./outputHists_2018/SingleMuon.root");
   for (int i = 0; i < 4; ++i) {
      if (i==0) continue;
      char buffer[100];
      sprintf(buffer, "%s_%d", histname.Data(), i);
      h_data[i] = (TH1D*)f_data->Get(buffer);
   }

   TH1D * h_emb[4];
   TFile * f_emb = TFile::Open("./outputHists_2018/Embedded.root");
   for (int i = 0; i < 4; ++i) {
      char buffer[100];
      sprintf(buffer, "%s_%d", histname.Data(), i);
      h_emb[i] = (TH1D*)f_emb->Get(buffer);   
   }

   const int nmc = 9;
   TH1D * h_mc[4][nmc];
   TString mctags[nmc];
   int col[nmc];
   TString labels[nmc];
   mctags[0] = "ZZ";                   col[0] = 51; labels[0] = "ZZ";
   mctags[1] = "WZ";                   col[1] = 56; labels[1] = "WZ";
   mctags[2] = "WW";                   col[2] = 61; labels[2] = "WW";
   mctags[3] = "ST_tW";                col[3] = 66; labels[3] = "tW";
   mctags[4] = "TTToSemiLeptonic";     col[4] = 76; labels[4] = "t#bar{t} 1l";
   mctags[5] = "TTTo2L2Nu";            col[5] = 71; labels[5] = "t#bar{t} 2l";
   mctags[6] = "DYJetsToLL_M-10to50";  col[6] = 81; labels[6] = "DY10to50";
   mctags[7] = "EWKZ2Jets_ZToLL_M-50"; col[7] = 86; labels[7] = "EWKZ50";
   mctags[8] = "DYJetsToLL_M-50";      col[8] = 91; labels[8] = "DY50";
   //mctags[9] = "WGToLNuG";             col[9] = 1;  labels[9] = "WGToLNuG";
   for (int i = 0; i < nmc; ++i) {
      char fname[100];
      sprintf(fname, "./outputHists_2018/%s_bkg.root", mctags[i].Data());
      TFile * f = TFile::Open(fname);
      for (int j = 0; j < 4; ++j) {
         char hname[100];
         sprintf(hname, "%s_%d", histname.Data(), j);
         h_mc[j][i] = (TH1D*)f->Get(hname);
      }
   }

   TFile * fout = new TFile("./outputHists_2018/QCD.root", "RECREATE");
   TH1D * h_bkgsub[4];
   for (int i = 0; i < 4; ++i) {
      if (i==0) continue;
      h_bkgsub[i] = (TH1D*)h_data[i]->Clone("h_bkgsub_"+TString::Itoa(i, 10));
      h_bkgsub[i]->Add(h_emb[i], -1.);
      for (int j = 0; j < nmc; ++j) {
         h_bkgsub[i]->Add(h_mc[i][j], -1.);
      }
   }

   for (int i = 1; i < 4; ++i) {
      for (int j = 1; j < h_bkgsub[i]->GetNbinsX()+1; ++j) {
         if (h_bkgsub[i]->GetBinContent(j)<0) {
            std::cout << "negative yields!" << std::endl;
            std::cout << "hist " << i << ", bin" << j << std::endl;
            std::cout << "data: " << h_data[i]->GetBinContent(j) << std::endl;
            std::cout << "emb: " << h_emb[i]->GetBinContent(j) << "+-" << h_emb[i]->GetBinError(j) << std::endl;
            std::cout << "mc: " << std::endl;
            for (int k = 0; k < nmc; ++k) {
               std::cout << "mc " << k << " " << h_mc[i][k]->GetBinContent(j) << "+-" << h_mc[i][k]->GetBinError(j) << std::endl;
            }
         }
      }
   }
   
   TH1D * h_CoD = (TH1D*)h_bkgsub[2]->Clone("h_CoD");
   h_CoD->GetYaxis()->SetTitle("C / D");
   h_CoD->Divide(h_bkgsub[3]);
   for (int i = 1; i < h_CoD->GetNbinsX()+1; ++i) {
      if (h_CoD->GetBinContent(i)<0.) {
         std::cout << "negative ratio!" << std::endl;
         std::cout << "bin: " << i << std::endl;
         std::cout << h_CoD->GetBinContent(i) << std::endl;
      }
   }
   
   TH1D *h_BCoD = (TH1D*)h_CoD->Clone("h_BCoD");
   h_BCoD->GetYaxis()->SetTitle("B * (C/D)");
   h_BCoD->Multiply(h_bkgsub[1]);

   TCanvas * c = new TCanvas("c", "", 800, 800);
   c->Divide(2,2);

   TLegend * l = new TLegend(0.5, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->AddEntry(h_data[1], "raw data", "L");
   l->AddEntry(h_bkgsub[1], "data - bkg", "L");

   for (int i = 0; i < 4; ++i) {
      if (i==0) continue;
      TPad * p = (TPad*)c->cd(i+1);   
      h_bkgsub[i]->SetLineWidth(2);
      h_bkgsub[i]->SetLineColor(6+i);
      h_bkgsub[i]->SetMinimum(0.1);
      h_bkgsub[i]->SetMaximum(25.);
      h_bkgsub[i]->SetStats(0);
      h_bkgsub[i]->Draw("HIST, E, SAME");
      h_bkgsub[i]->SetLineColor(8);
      h_data[i]->Draw("HIST, E, SAME");
      h_data[i]->SetLineWidth(2);
      h_data[i]->SetLineColor(9);
      l->Draw();
      p->SetLogy();
   }

 //  h_bkgsub[1]->Write(histname+"_1");
 //  h_bkgsub[2]->Write(histname+"_2");
 //  h_bkgsub[3]->Write(histname+"_3");
 //  h_CoD->Write();
 //  h_BCoD->Write(histname+"_0");
 //  fout->Close();
 //  return fout;

   TCanvas * c2 = new TCanvas("c2", "", 800, 400);
   c2->Divide(2, 1);
   c2->cd(1);
   h_CoD->Draw("PE");
   h_CoD->SetStats(0);
   c2->cd(2);
   h_BCoD->Draw("PE");
   h_BCoD->SetStats(0);  
   return 0;
}

