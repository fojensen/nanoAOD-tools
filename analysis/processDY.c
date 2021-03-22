#include <TCut.h>
#include <TLine.h>
#include <TChain.h>
#include <iostream>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <fstream>
#include <TTree.h>

void findWeights(const int year)
{
   std::cout << "year: " << year << std::endl;
   const double xs_inc = 6077.22;

   double n[5];
   if (year==2016) n[0]=68830677.0; n[1]=65712864.; n[2]=28446811.; n[3]=18845701.; n[4]=7538537.;
   if (year==2017) n[0]=102486448.; n[1]=66096393.; n[2]=28389776.; n[3]=17510095.; n[4]=7575236.;
   if (year==2018) n[0]=98433266.0; n[1]=65679725.; n[2]=28280407.; n[3]=19021176.; n[4]=7581874.;

   TString inlist;
   if (year==2016) inlist="DYJetsToLL_M50_2016.list";
   if (year==2017) inlist="DYJetsToLL_M50_2017.list";
   if (year==2018) inlist="DYJetsToLL_M50_2018.list";
 
   TH1D * h = new TH1D("h", ";LHE_Njets;events / 1", 6, -0.5, 5.5);
   h->SetLineWidth(2);
 
   std::ifstream infile(inlist);
   std::string line;
   double ntotinc = 0;
   //int nmax = 0;
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
      TTree * t = (TTree*)f->Get("Events");
      h->SetDirectory(f);
      ntotinc += t->Project("+h", "LHE_Njets");
      // delete the file
      char cmd_delete[1000];
      sprintf(cmd_delete, "rm /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/%s", fname);
      std::cout << cmd_delete << std::endl;
      system(cmd_delete);
      //++nmax;
      //if (nmax==5) break;
   }
   if (ntotinc!=n[0]) std::cout << "missing some entries!" << std::endl;

   double f[5], ferr[5];
   double ninc[5];
   double xs[5], xserr[5];
   for (int i = 0; i < 5; ++i) {
      ninc[i] = h->GetBinContent(i+1);
      f[i] = ninc[i]/ntotinc;
      ferr[i] = f[i] * sqrt((1./ninc[i])+(1./ntotinc));
      xs[i] = xs_inc * f[i];
      xserr[i] = xs_inc * ferr[i];
   }

   double ntot[5];
   double xs_weight[5];
   ntot[0] = ninc[0]; //0jets
   ntot[1] = ninc[1] + n[1]; //1jet
   ntot[2] = ninc[2] + n[2]; //2jet
   ntot[3] = ninc[3] + n[3]; //3jet
   ntot[4] = ninc[4] + n[4]; //4jet
   for (int i = 0; i < 5; ++i) xs_weight[i] = xs[i] / ntot[i];

   for (int i = 0; i < 5; ++i) {
      std::cout << "LHE_Njets: " << i << std::endl;
      std::cout << "   fraction of inclusive: " << f[i] << "+-" << ferr[i] << std::endl;
      std::cout << "   xs: " << xs[i] << "+-" << xserr[i] << std::endl;
      std::cout << "   events in inclusive: " << ninc[i] << std::endl;
      std::cout << "   events in binned: " << n[i] << std::endl;
      std::cout << "   total events: " << ntot[i] << std::endl;
      std::cout << "   xs_weight: " << xs_weight[i] << std::endl;
   }

   /*std::cout << "a" << std::endl;
   h->SetDirectory(0);
   std::cout << "b" << std::endl;
   TCanvas * c = new TCanvas("c", year, 800, 400);
   std::cout << "c" << std::endl;
   c->Divide(2,1);
   std::cout << "d" << std::endl;
   TPad * p1 = (TPad*)c->cd(1);
   std::cout << "e" << std::endl;
   h->Draw("HIST, E");
   std::cout << "f" << std::endl;
   p1->SetLogy();
   std::cout << "g" << std::endl;
   TPad * p2 = (TPad*)c->cd(2);
   std::cout << "h" << std::endl;
   h->DrawNormalized("HIST, TEXT, E");
   std::cout << "i" << std::endl;
   p2->SetLogy();
   std::cout << "j" << std::endl;*/
}

void processDY(const int year, const bool dotautau)
{
   std::cout << "processDY " << year << " " << dotautau << std::endl;
   TChain * c = new TChain("Events");
   const TString tags[5] = {"DYJetsToLL_M50", "DY1JetsToLL_M50", "DY2JetsToLL_M50", "DY3JetsToLL_M50", "DY4JetsToLL_M50"}; 
   for (int i = 0; i < 5; ++i) {
      char infile[200];
      sprintf(infile, "./%s_%d.root", tags[i].Data(), year);
      c->Add(infile);
   }

   const TCut tautau = "Sum$(TMath::Abs(GenPart_pdgId)==15 && GenPart_genPartIdxMother>=0 && GenPart_pdgId[GenPart_genPartIdxMother]==23)>=2";
   TCut cut;
   dotautau ? cut=tautau : cut=!tautau;

   char outfile[100];
   if (dotautau) {
      sprintf(outfile, "./DYJetsToTauTau_M50_%d.root", year);
   } else {
      sprintf(outfile, "./DYJetsToEEMuMu_M50_%d.root", year);
   }
   std::cout << outfile << std::endl;
   TFile * f = new TFile(outfile, "RECREATE");
   TTree * t = (TTree*)c->CopyTree(cut);

   UChar_t LHE_Njets;
   t->SetBranchAddress("LHE_Njets", &LHE_Njets);
   
   double w[5];
   if (year==2016) w[0]=8.82923e-05; w[1]=1.39305e-05; w[2]=1.06292e-05; w[3]=4.98874e-06; w[4]=5.9883e-06;
   if (year==2017) w[0]=5.92978e-05; w[1]=1.32271e-05; w[2]=1.01341e-05; w[3]=4.95732e-06; w[4]=5.81179e-06;
   if (year==2018) w[0]=6.17395e-05; w[1]=1.33982e-05; w[2]=1.02245e-05; w[3]=4.99379e-06; w[4]=5.84469e-06;

   double xsWeight_DY;
   TBranch * b_xsWeight_DY = t->Branch("xsWeight_DY", &xsWeight_DY, "xsWeight_DY/D");

   const int n = t->GetEntries();
   for (int i = 0; i < n; ++i) {
      if (i%100000==0) {
         std::cout << "event: " << i << ", " << double(i)/double(n) << "pc of total" << std::endl;
      }
      t->GetEntry(i);
      //std::cout << " LHE_Njets: " << (int)LHE_Njets << std::endl;
      xsWeight_DY = w[(int)LHE_Njets];
      //std::cout << " xsWeight_DY: " << xsWeight_DY << std::endl;
      b_xsWeight_DY->Fill();
   }

   t->Write();
   f->Close();
   std::cout << "all done" << std::endl;
}

void validate(const int year)
{
   char inbuffer[100];
   sprintf(inbuffer, "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_20032021/DYJetsToLL_M50_%d.root", year);
   TFile * f = TFile::Open(inbuffer);
   TTree * c_inc = (TTree*)f->Get("Events");

   TH1D * h_inc = new TH1D("h_inc", ";LHE_Njets;events / 1", 6, -0.5, 5.5);
   h_inc->Sumw2();
   c_inc->Project("h_inc", "LHE_Njets", "xsWeight * (1>0)");

   TH1D * h_stitch = new TH1D("h_stitch", "", 6, -0.5, 5.5);
   h_stitch->Sumw2();

   //const TString tags[5] = {"DYJetsToLL_M50", "DY1JetsToLL_M50", "DY2JetsToLL_M50", "DY3JetsToLL_M50", "DY4JetsToLL_M50"};
   const TString tags[2] = {"DYJetsToTauTau_M50", "DYJetsToEEMuMu_M50"};
   for (int i = 0; i < 2; ++i) {
      char buffer[100];
      sprintf(buffer, "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_20032021/%s_%d.root", tags[i].Data(), year);
      TFile * ftemp = TFile::Open(buffer);
      TTree * ctemp = (TTree*)ftemp->Get("Events");
      h_stitch->SetDirectory(ftemp);
      ctemp->Project("+h_stitch", "LHE_Njets", "xsWeight_DY * (1>0)");
   }

   TH1D * r = (TH1D*)h_stitch->Clone("r");
   r->Divide(h_inc);
   r->SetTitle(";LHE_Njets;combined / inclusive");
   for (int i = 0; i < 6; ++i) {
      std::cout << "LHE_NJets: " << i << std::endl;
      std::cout << "   stitch: " << h_stitch->GetBinContent(i+1) << " +- " << h_stitch->GetBinError(i+1) << std::endl;
      std::cout << "   inc: " << h_inc->GetBinContent(i+1) << " +- " << h_inc->GetBinError(i+1) << std::endl;
      std::cout << "   stitch/inc: " << r->GetBinContent(i+1) << " +- " << r->GetBinError(i+1) << std::endl;
   }

   TCanvas * c = new TCanvas("c", TString::Itoa(year, 10), 800, 400);
   c->Divide(2, 1);
   TPad * p1 = (TPad*)c->cd(1);
   h_inc->SetLineWidth(2);
   h_inc->SetStats(0);
   h_inc->SetLineColor(6);
   h_inc->Draw("HIST, E");
   h_stitch->SetLineWidth(2);
   h_stitch->SetLineColor(7);
   h_stitch->Draw("HIST, E, SAME");
   h_inc->SetMinimum(0.1);
   h_inc->SetMaximum(1000.);
   p1->SetLogy();

   TLegend * l = new TLegend(0.6, 0.7, 0.875, 0.875);
   l->SetBorderSize(0);
   l->AddEntry(h_stitch, "combined", "L");
   l->AddEntry(h_inc, "inclusive", "L");
   l->Draw();

   c->cd(2);
   r->SetMarkerStyle(20);
   r->Draw("PE");
   r->SetMinimum(0.85);
   r->SetLineColor(602);
   r->SetMaximum(1.25);
   r->SetStats(0);
   TLine * line = new TLine(-0.5, 1., 5.5, 1.);
   line->SetLineStyle(2);
   line->SetLineColor(2);
   line->Draw();
   char savetag[100];
   sprintf(savetag, "./plots/validateStitching_%d.pdf", year);
   c->SaveAs(savetag);
}

/*void addDYWeight(const int year)
{
   addbranch("DYJetsToLL_M50", year);
   addbranch("DY1JetsToLL_M50", year);
   addbranch("DY2JetsToLL_M50", year);
   addbranch("DY3JetsToLL_M50", year);
   addbranch("DY4JetsToLL_M50", year);
   validate(year);
}*/

