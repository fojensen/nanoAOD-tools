#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TCut.h>
#include "addOverflow.h"

void drawWeights()
{
   TFile * f = TFile::Open("./outputData/Embedded_2018.root");
   TTree * t = (TTree*)f->Get("Events");
   TH1D * h = new TH1D("h", ";genWeight;events / .02", 15, 0., 0.3);
   const TCut cut = "MuTauGamma_havePair==1 && MuMuGamma_havePair==0";
   t->Project("h", "genWeight", cut);
   addOverflow(h);

   TCanvas * c = new TCanvas("c", "", 400, 400);
   h->SetLineWidth(2);
   h->Draw("HIST, E");
   c->SaveAs("./plots/embeddedweights.pdf");
   c->SetLogy();
   h->SetMinimum(1.);
   h->SetMaximum(100000000.);
}
