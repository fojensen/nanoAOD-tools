#include <TH1D.h>
#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TLegend.h>
#include "addOverflow.h"

void photonCount()
{
   double n_mumu = 0;
   double n_mutau = 0;
  
   const TCut mumuchannel = "Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_genPartFlav==1)==2";
   const TCut mutauchannel = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_genPartFlav==5)==1 && Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_genPartFlav==15)==1";
   const TString nphotons = "Sum$(Photon_pt>=32. && TMath::Abs(Photon_eta)<2.5 && Photon_genPartFlav==1)";

   TH1D * h_mumu = new TH1D("h_mumu", ";# of photons;events / 1", 3, -0.5, 2.5);
   h_mumu->SetLineWidth(2);
   h_mumu->SetStats(0);
   h_mumu->Sumw2();
   TH1D * h_mutau = (TH1D*)h_mumu->Clone("h_mutau");

   std::ifstream infile("./filelists/DYJetsToLL_M-50.list");
   std::string line;
   int nfiles = 0;
   while (std::getline(infile, line)) {
      std::cout << "file " << nfiles  << ": " << line << std::endl;
      char buffer[10000];
      sprintf(buffer, "root://cmsxrootd.fnal.gov//%s", line.c_str());
      TFile * f = TFile::Open(buffer);
      TTree * t = (TTree*)f->Get("Events");

      TH1D temp_mumu("temp_mumu", "", 3, -0.5, 2.5);
      n_mumu += t->Project("temp_mumu", nphotons, mumuchannel);
      h_mumu->Add(&temp_mumu);
      
      TH1D temp_mutau("temp_mutau", "", 3, -0.5, 2.5);
      n_mutau += t->Project("temp_mutau", nphotons, mutauchannel);
      h_mutau->Add(&temp_mutau);

      ++nfiles;
      //if (nfiles==2) break;
   }
   std::cout << "# of input files: " << nfiles << std::endl;

   addOverflow(h_mumu);
   addOverflow(h_mutau);

   h_mumu->Scale(1./n_mumu);
   h_mutau->Scale(1./n_mutau);

   TCanvas * c = new TCanvas("c", "", 800, 400);
   c->Divide(2, 1);
   
   TPad * p1 = (TPad*)c->cd(1);
   h_mumu->SetLineWidth(2);
   h_mumu->SetLineColor(7);
   h_mutau->SetLineWidth(2);
   h_mutau->SetLineColor(8);
   h_mumu->Draw("HIST, E");
   h_mumu->SetMaximum(1.);
   h_mumu->SetMinimum(0.00001);
   h_mutau->Draw("HIST, SAME, E");
   p1->SetLogy();

   TLegend * l = new TLegend(0.5, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->AddEntry(h_mumu->GetName(), "#mu#mu", "L");
   l->AddEntry(h_mutau->GetName(), "#mu#tau_{h}", "L");
   l->Draw();

   c->cd(2);
   TH1D * r = (TH1D*)h_mutau->Clone("r");
   r->Divide(h_mumu);
   r->SetLineColor(602);
   r->SetMarkerStyle(20);
   r->Draw("PE");
   r->SetTitle(";# of photons;#mu#tau_{h} / #mu#mu");

   std::cout << r->GetBinContent(2) << " +- " << r->GetBinError(2) << std::endl;

   c->SaveAs("./plots/ratios.pdf");
}

