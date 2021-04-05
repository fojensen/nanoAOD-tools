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

void findXS(const TString process, const int year)
{
   std::cout << "process: " << process << std::endl;
   std::cout << "year: " << year << std::endl;
   TString inlist; 
   double xs_inc; 

   if (process=="DYJetsToLL") {
      if (year==2016) inlist="DYJetsToLL_2016.list";
      if (year==2017) inlist="DYJetsToLL_2017.list";
      if (year==2018) inlist="DYJetsToLL_2018.list";
      if (year==0) inlist = "DYJetsToLL.list";
      xs_inc = 6077.22;
   }
   if (process=="WJetsToLNu") {
      if (year==2016) inlist="WJetsToLNu_2016.list";
      if (year==2017) inlist="WJetsToLNu_2017.list";
      if (year==2018) inlist="WJetsToLNu_2018.list";
      if (year==0) inlist="WJetsToLNu.list";
      xs_inc = 61526.7;     
   }

   TH1D * h = new TH1D("h", ";LHE_Njets;events / 1", 6, -0.5, 5.5);
   h->SetLineWidth(2);
 
   std::ifstream infile("./filelists/"+inlist);
   std::string line;
   double ntotinc = 0;
   int nfiles = 0;
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
      ++nfiles;
   }
   std::cout << "number of files processed: " << nfiles << std::endl;
   std::cout << "number of entries processed: " << ntotinc << std::endl;

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

   for (int i = 0; i < 5; ++i) {
      std::cout << "LHE_Njets: " << i << std::endl;
      std::cout << "   number of events: " << ninc[i] << std::endl;
      std::cout << "   fraction of inclusive: " << f[i] << "+-" << ferr[i] << std::endl;
      std::cout << "   xs: " << xs[i] << "+-" << xserr[i] << std::endl;
   }
}

void findWeights(const TString process, const int year)
{
   std::cout << "process: " << process << "; year: " << year << std::endl;

   double n_incsum = 0.;
   double xs_inc = 0.;
   double n_b[5];

   if (process=="DYJetsToLL") {
      if (year==2016) n_incsum=68830677.0; n_b[0]=0.; n_b[1]=65712864.; n_b[2]=28446811.; n_b[3]=18845701.; n_b[4]=7538537.;
      if (year==2017) n_incsum=102486448.; n_b[0]=0.; n_b[1]=66096393.; n_b[2]=28389776.; n_b[3]=17510095.; n_b[4]=7575236.;
      if (year==2018) n_incsum=98433266.0; n_b[0]=0.; n_b[1]=65679725.; n_b[2]=28280407.; n_b[3]=19021176.; n_b[4]=7581874.;
      xs_inc = 6077.22;
   }
   if (process=="WJetsToLNu") {
      if (year==2016) n_incsum=88463979.; n_b[0]=0.; n_b[1]=48443131.; n_b[2]=28745846.; n_b[3]=18859350.; n_b[4]=9216091.0;
      if (year==2017) n_incsum=81254459.; n_b[0]=0.; n_b[1]=47954631.; n_b[2]=28616461.; n_b[3]=18903448.; n_b[4]=17418488.;
      if (year==2018) n_incsum=83009353.; n_b[0]=0.; n_b[1]=47698594.; n_b[2]=27570500.; n_b[3]=14932443.; n_b[4]=12416620.;
      xs_inc = 61526.7;
   }

   TH1D * h = new TH1D("h", ";LHE_Njets;events / 1", 6, -0.5, 5.5);
   h->SetLineWidth(2);

   char inlist[100];
   sprintf(inlist, "./filelists/%s_%d.list", process.Data(), year); 
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
      TTree * t = (TTree*)f->Get("Events");
      h->SetDirectory(f);
      n_events += t->Project("+h", "LHE_Njets");
      // delete the file
      char cmd_delete[1000];
      sprintf(cmd_delete, "rm /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/%s", fname);
      std::cout << cmd_delete << std::endl;
      system(cmd_delete);
      ++n_files;
   }
   std::cout << "number of files processed: " << n_files << std::endl;
   std::cout << "number of entries processed: " << n_events << std::endl;
   if (n_events!=n_incsum) std::cout << "missing some entries!" << std::endl;

   double f[5], f_err[5];
   double n_i[5];
   double xs[5], xs_err[5];
   for (int i = 0; i < 5; ++i) {
      n_i[i] = h->GetBinContent(i+1);
      f[i] = n_i[i] /n_incsum;
      f_err[i] = f[i] * sqrt((1./n_i[i])+(1./n_incsum));
      xs[i] = xs_inc * f[i];
      xs_err[i] = xs_inc * f_err[i];
   }

   double ntot[5];
   double xs_weight[5];
   for (int i = 0; i < 5; ++i) ntot[i] = n_i[i] + n_b[i];
   for (int i = 0; i < 5; ++i) xs_weight[i] = xs[i] / ntot[i];

   for (int i = 0; i < 5; ++i) {
      std::cout << "LHE_Njets: " << i << std::endl;
      std::cout << "   fraction of inclusive: " << f[i] << "+-" << f_err[i] << std::endl;
      std::cout << "   xs: " << xs[i] << "+-" << xs_err[i] << std::endl;
      std::cout << "   events in inclusive: " << n_i[i] << std::endl;
      std::cout << "   events in binned: " << n_b[i] << std::endl;
      std::cout << "   total events: " << ntot[i] << std::endl;
      std::cout << "   xs_weight: " << xs_weight[i] << std::endl;
   }
/*
   std::cout << "a" << std::endl;
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

void copyTree(const int year, const bool dotautau)
{
   std::cout << "copyTree(): " << year << ", " << dotautau << std::endl;
   TChain * c = new TChain("Events");
   const TString tags[5] = {"DYJetsToLL", "DY1JetsToLL", "DY2JetsToLL", "DY3JetsToLL", "DY4JetsToLL"}; 
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
      sprintf(outfile, "./DYJetsToTauTau_%d.root", year);
   } else {
      sprintf(outfile, "./DYJetsToEEMuMu_%d.root", year);
   }
   TFile * f = new TFile(outfile, "RECREATE");
   TTree * t = (TTree*)c->CopyTree(cut);
   t->Write();
   f->Close();
   std::cout << "end copyTree()" << std::endl;
}

void addBranch(const TString process, const int year, const TString infile)
{
   std::cout << "addBranch(): " << process << ", " << year << ", " << infile << std::endl;
   //TFile * f = new TFile(infile, "UPDATE"); 
   TFile * f = TFile::Open(infile, "UPDATE");
   TTree * t = (TTree*)f->Get("Events");

   UChar_t LHE_Njets;
   t->SetBranchAddress("LHE_Njets", &LHE_Njets);

   float w[5];
   if (process=="DYJetsToLL") {
      if (year==2016) w[0]=8.82923e-05; w[1]=1.39305e-05; w[2]=1.06292e-05; w[3]=4.98874e-06; w[4]=5.9883e-06;
      if (year==2017) w[0]=5.92978e-05; w[1]=1.32271e-05; w[2]=1.01341e-05; w[3]=4.95732e-06; w[4]=5.81179e-06;
      if (year==2018) w[0]=6.17395e-05; w[1]=1.33982e-05; w[2]=1.02245e-05; w[3]=4.99379e-06; w[4]=5.84469e-06;
   }
   if (process=="WJetsToLNu") {
      if (year==2016) w[0]=0.0006955;   w[1]=0.000164053; w[2]=9.74127e-05; w[3]=5.77409e-05; w[4]=3.40824e-05;
      if (year==2017) w[0]=0.00075721;  w[1]=0.000170994; w[2]=0.000101388; w[3]=5.88834e-05; w[4]=3.46565e-05;
      if (year==2018) w[0]=0.000741202; w[1]=0.000170172; w[2]=0.000101162; w[3]=5.87754e-05; w[4]=3.46281e-05;
   }

   float xsWeight_Njets;
   TBranch * b_xsWeight_Njets = t->Branch("xsWeight_Njets", &xsWeight_Njets, "xsWeight_Njets/F");

   const int n = t->GetEntries();
   for (int i = 0; i < n; ++i) {
      if (i%100000==0) {
         std::cout << "event: " << i << ", " << float(i)/float(n) << "pc of total" << std::endl;
      }
      t->GetEntry(i);
      xsWeight_Njets = w[(int)LHE_Njets];
      b_xsWeight_Njets->Fill();
   }
   t->Write();
   f->Close();
   std::cout << "end addBranch()" << std::endl;
}

void validate(const TString process, const int year)
{
   char inbuffer[100];
   //sprintf(inbuffer, "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/DYJetsToLL_M50_%d.root", year);
 
   if (process=="DYJetsToLL") {
      sprintf(inbuffer, "./DYJetsToLL_%d.root", year);
   }
   if (process=="WJetsToLNu") {
       sprintf(inbuffer, "./WJetsToLNu_%d.root", year);
   }
   TFile * f = TFile::Open(inbuffer);
   TTree * c_inc = (TTree*)f->Get("Events");

   TH1D * h_inc = new TH1D("h_inc", ";LHE_Njets;events / 1", 6, -0.5, 5.5);
   h_inc->Sumw2();
   const int n_inc = c_inc->Project("h_inc", "LHE_Njets", "xsWeight * (1>0)");
   std::cout << "entries in inclusive projection: " << n_inc << std::endl;

   TH1D * h_stitch = new TH1D("h_stitch", "", 6, -0.5, 5.5);
   h_stitch->Sumw2();

   //const TString tags[5] = {"DYJetsToLL_M50", "DY1JetsToLL_M50", "DY2JetsToLL_M50", "DY3JetsToLL_M50", "DY4JetsToLL_M50"};
   //const TString tags[2] = {"DYJetsToTauTau_M50", "DYJetsToEEMuMu_M50"};
   /*for (int i = 0; i < 2; ++i) {
      char buffer[100];
      //sprintf(buffer, "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/%s_%d.root", tags[i].Data(), year);
      sprintf(buffer, "./%s_%d.root", tags[i].Data(), year);
      TFile * ftemp = TFile::Open(buffer);
      TTree * ctemp = (TTree*)ftemp->Get("Events");
      h_stitch->SetDirectory(ftemp);
      const int n = ctemp->Project("+h_stitch", "LHE_Njets", "xsWeight_DY * (1>0)");
      std::cout << "entries in projection " << i << ": " << n << std::endl;
   }*/

   TChain * c_stitch = new TChain("Events");
   if (process=="DYJetsToLL") {
      char in1[100];
      sprintf(in1, "DYJetsToTauTau_%d.root", year);
      c_stitch->Add(in1);
      char in2[100];
      sprintf(in2, "DYJetsToEEMuMu_%d.root", year);
      c_stitch->Add(in2);
   }
   if (process=="WJetsToLNu") {
      char inf[100];
      sprintf(inf, "WJetsToLNuFull_%d.root", year);
      c_stitch->Add(inf);
   }
   const int n = c_stitch->Project("+h_stitch", "LHE_Njets", "xsWeight_Njets * (1>0)");
   std::cout << "entries in projection: " << n << std::endl;

   TH1D * r = (TH1D*)h_stitch->Clone("r");
   r->Divide(h_inc);
   r->SetTitle(";LHE_Njets;combined / inclusive");
   for (int i = 0; i < 6; ++i) {
      std::cout << "LHE_NJets: " << h_stitch->GetBinCenter(i+1) << ", " << h_inc->GetBinCenter(i+1) << std::endl;
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

void processDY(const TString process, const int year)
{
   if (process=="DYJetsToLL") {
      copyTree(year, true);
      char inname1[100];
      sprintf(inname1, "DYJetsToTauTau_%d.root", year);
      addBranch(process, year, inname1);
      copyTree(year, false);
      char inname2[100];
      sprintf(inname2, "DYJetsToEEMuMu_%d.root", year);
      addBranch(process, year, inname2);
   }
   if (process=="WJetsToLNu") {
      char inname[100];
      sprintf(inname, "WJetsToLNu_%d.root", year);
      addBranch("WJetsToLNu", year, inname);
   }
   validate(process, year);
}

