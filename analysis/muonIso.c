#include <TCut.h>
#include <iostream>
#include <fstream>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>

void muonIso(const int year)
{
   TH1D * h = new TH1D("h", ";Muon_pfIsoId;events / 1", 7, -0.5, 6.5);
   h->SetLineWidth(2);

   char inlist[100];
   sprintf(inlist, "./filelists/DYJetsToLL_%d.list", year); 
   std::ifstream infile(inlist);
   std::string line;
   double n_events = 0;
   int n_files = 0;
   while (std::getline(infile, line)) {
      // download the file
      char cmd_download[1000];
      sprintf(cmd_download, "xrdcp root://cmsxrootd.fnal.gov//%s /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/", line.c_str());
      std::cout << cmd_download << std::endl;
      system(cmd_download);
      // do the work
      const char * fname = basename(line.c_str());
      char infile[100];
      sprintf(infile, "/uscmst1b_scratch/lpc1/3DayLifetime/fojensen/%s", fname);
      TFile * f = TFile::Open(infile);
      TTree * t_ = (TTree*)f->Get("Events");
      const TCut skimMu = "Sum$(TMath::Abs(Muon_eta)<2.4 && Muon_pt>=26. && Muon_tightId && Muon_pfIsoId>=4)==1";
      const TCut skimTau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (8&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))==1";
      const TCut skimPhoton = "Sum$(TMath::Abs(Photon_eta)<2.5 && (Photon_isScEtaEB||Photon_isScEtaEE) && (Photon_electronVeto||!Photon_pixelSeed) && Photon_mvaID_WP90)>0";
      TTree * t = (TTree*)t_->CopyTree(skimMu&&skimTau&&skimPhoton);
      h->SetDirectory(f);
      n_events += t->Project("+h", "Muon_pfIsoId", "Muon_mediumId && TMath::Abs(Muon_eta)<2.4 && Muon_genPartFlav==1");
      // delete the file
      char cmd_delete[1000];
      sprintf(cmd_delete, "rm /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/%s", fname);
      std::cout << cmd_delete << std::endl;
      system(cmd_delete);
      ++n_files;
      if (n_events>=1000.) break;
   }
   std::cout << "number of files processed: " << n_files << std::endl;
   std::cout << "number of entries processed: " << n_events << std::endl;

   TCanvas * c = new TCanvas("c", "", 400, 400);
   h->Scale(1./h->Integral());
   h->SetMinimum(0.01);
   h->SetMaximum(1.);
   h->SetStats("e");
   c->SetLogy();
   h->Draw("HIST, E");
}

