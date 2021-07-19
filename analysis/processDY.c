#include <iomanip>
#include <TH1D.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TCut.h>
#include <TChain.h>
#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <fstream>

void findXS(const int year)
{std::cout << "findXS(): " << year << std::endl;
   
   TString inlist; 

   /*const double xs_inc = 6077.22;
   if (year==2015) inlist="DYJetsToLL_2015.list";
   if (year==2016) inlist="DYJetsToLL_2016.list";
   if (year==2017) inlist="DYJetsToLL_2017.list";
   if (year==2018) inlist="DYJetsToLL_2018.list";
   if (year==0) inlist = "DYJetsToLL.list";*/

   const double xs_inc = 61526.7;  
   if (year==2015) inlist="WJetsToLNu_2015.list";
   if (year==2016) inlist="WJetsToLNu_2016.list";
   if (year==2017) inlist="WJetsToLNu_2017.list";
   if (year==2018) inlist="WJetsToLNu_2018.list";
   if (year==0) inlist = "WJetsToLNu.list";

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

void findXSAndWeight(const TString process, const int year)
{std::cout << "findXSAndWeight(): " << process << ", " <<  year << std::endl;

   double n_incsum = 0.;
   double n_b[5];
   double xs_inc = 0.;

   if (process=="DYJetsToLL") {
   xs_inc = 6077.22;
   if (year==2016) {
      n_incsum=104072004.;
      n_b[0]=0.;
      n_b[1]=65712864.;
      n_b[2]=28446811.;
      n_b[3]=18845701.;
      n_b[4]=7538537.;
   }
   if (year==2017) {
      n_incsum=102486448.;
      n_b[0]=0.;
      n_b[1]=66096393.;
      n_b[2]=28389776.;
      n_b[3]=17510095.;
      n_b[4]=7575236.;
   }
   if (year==2018) {
      n_incsum=98433266.0;
      n_b[0]=0.;
      n_b[1]=65679725.;
      n_b[2]=28280407.;
      n_b[3]=19021176.;
      n_b[4]=7581874.;
   }
   }
   if (process=="WJetsToLNu") {   
   xs_inc = 61526.7;
   if (year==2015) {
      n_incsum=81327193.;
      n_b[0]=0.;
      n_b[1]=47788364.;
      n_b[2]=27635126.;
      n_b[3]=18460582.;
      n_b[4]=9385004.;
   }
   if (year==2016) {
      n_incsum=81327193.;
      n_b[0]=0.;
      n_b[1]=48443131.;
      n_b[2]=28745846.;
      n_b[3]=18859350.;
      n_b[4]=9216091.;
   }
   if (year==2017) {
      n_incsum=81254459.;
      n_b[0]=0.;
      n_b[1]=47954631.;
      n_b[2]=28616461.;
      n_b[3]=18903448.;
      n_b[4]=17418488.;
   }
   if (year==2018) {
      n_incsum=83009353.;
      n_b[0]=0.;
      n_b[1]=47698594.;
      n_b[2]=27570500.;
      n_b[3]=14932443.;
      n_b[4]=12416620.;
   }
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
      std::cout << "starting file: " << n_files << std::endl;
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
   std::cout << "number of entries processed: " << std::setprecision(9) << n_events << std::endl;
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
      std::cout << "   events in inclusive: " << std::setprecision(9) << n_i[i] << std::endl;
      std::cout << "   events in binned: " << std::setprecision(9) << n_b[i] << std::endl;
      std::cout << "   total events: " << std::setprecision(9) << ntot[i] << std::endl;
      std::cout << "   xs_weight: " << xs_weight[i] << std::endl;
   }

   /*TCanvas * c = new TCanvas("c", year, 400, 400);
   h->SetMarkerSize(2);
   h->DrawNormalized("TEXT, E");
   char cname[100];
   sprintf(cname, "LHENjets_%d.pdf", year);
   c->SaveAs(cname);*/
}

void splitTree(const int year, const bool dotautau)
{std::cout << "splitTree(): " << year << ", " << dotautau << std::endl;

   TChain * c = new TChain("Events");
   const TString tags[5] = {"DYJetsToLL", "DY1JetsToLL", "DY2JetsToLL", "DY3JetsToLL", "DY4JetsToLL"}; 
   for (int i = 0; i < 5; ++i) {
      char infile[100];
      sprintf(infile, "./%s_%d.root", tags[i].Data(), year);
      c->Add(infile);
   }
   std::cout << "   entries in input chain: " << c->GetEntries() << std::endl;
   c->SetBranchStatus("xsWeight", 0);

   const TCut tautau = "Sum$(TMath::Abs(GenPart_pdgId)==15 && GenPart_genPartIdxMother>=0 && GenPart_pdgId[GenPart_genPartIdxMother]==23)>=2";
   //TCut cut;
   //dotautau ? cut=tautau : cut=!tautau;

   char outfile[100];
   if (dotautau) {
      sprintf(outfile, "./DYJetsToTauTau_%d.root", year);
   } else {
      sprintf(outfile, "./DYJetsToEEMuMu_%d.root", year);
   }
   TFile * f = new TFile(outfile, "RECREATE");

   //TTree * t = (TTree*)c->CopyTree(cut);
   TTree * t = (TTree*)c->CopyTree(dotautau ? tautau : !tautau);
   std::cout << "   entries in output tree: " << t->GetEntries() << std::endl;
   t->Write();
   f->Close();
}

/*void combineAndRemove(const int year)
{
   const TString tags[5] = {"DYJetsToLL", "DY1JetsToLL", "DY2JetsToLL", "DY3JetsToLL", "DY4JetsToLL"};
   TChain * cin = new TChain("Events");
   for (int i = 0; i < 1; ++i) {
      char infile[100];
      sprintf(infile, "%s_%d.root", tags[i].Data(), year); 
      cin->Add(infile);
   }
   
   cin->SetBranchStatus("xsWeight", 0);
   TTree * tout = cin->CloneTree(0);  
   fout->Write();
}
*/
/*void splitTreeDropBranch(const int year, const bool dotautau)
{std::cout << "splitTreeDropBranch(): " << year << ", " << dotautau << std::endl;

   const TString tags[5] = {"DYJetsToLL", "DY1JetsToLL", "DY2JetsToLL", "DY3JetsToLL", "DY4JetsToLL"};
   TChain * cin = new TChain("Events");
   for (int i = 0; i < 1; ++i) {
      char infile[100];
      sprintf(infile, "%s_%d.root", tags[i].Data(), year); 
      cin->Add(infile);
   }

   //char infile[100];
   //sprintf(infile, "DYJetsToLL_%d.ALL.root", year);
   //TFile * fin = TFile::Open(infile);
   //TTree * cin = (TTree*)fin->Get("Events");

   const double n = cin->GetEntries();
   std::cout << "entries in input chain: " << n << std::endl;

   cin->SetBranchStatus("xsWeight", 0);

   //UChar_t LHE_Njets;
   //cin->SetBranchAddress("LHE_Njets", &LHE_Njets);

   UInt_t nGenPart;
   Int_t GenPart_genPartIdxMother[100];
   Int_t GenPart_pdgId[100];
   cin->SetBranchAddress("nGenPart", &nGenPart);
   cin->SetBranchAddress("GenPart_genPartIdxMother", GenPart_genPartIdxMother);
   cin->SetBranchAddress("GenPart_pdgId", GenPart_pdgId);

char outfile[100];
   if (dotautau) {
      sprintf(outfile, "DYJetsToTauTau_%d.root", year);
   } else {
      sprintf(outfile, "DYJetsToEEMuMu_%d.root", year);
   }
   TFile * fout = new TFile(outfile, "RECREATE"); 

   std::cout << "start CloneTree" << std::endl;
   TTree * tout = cin->CloneTree(0);
   std::cout << "end CloneTree" << std::endl;
   //int nfill = 0;
   for (int i = 0; i < n; ++i) {
      //std::cout << "event: " << i << std::endl;
      if (i%100000==0) std::cout << "fraction complete: " << double(i)/n << std::endl;
      cin->GetEntry(i);
      //if (LHE_Njets>2) {
      int nGenTau = 0;  
      for (int j = 0; j < nGenPart; ++j) {
         if (TMath::Abs(GenPart_pdgId[j])==15) {
            if (GenPart_genPartIdxMother[j]>=0) {
               if (GenPart_pdgId[GenPart_genPartIdxMother[j]]==23) {
                  ++nGenTau;
               }
            }
         }
      }
      if ( (dotautau&&nGenTau>=2) || (!dotautau&&nGenTau<2) ) {
         tout->Fill();
         //++nfill;
         //std::cout << "   filling once" << std::endl;
      }
   }
   //std::cout << "nfill: " << nfill << std::endl;
   std::cout << "entries in output tree: " << tout->GetEntries() << std::endl;
   fout->Write();
   //fout->Close();
   std::cout << "end splitTreeDropBranch()" << std::endl;
}

void splitTree(const int year, const bool dotautau)
{std::cout << "splitTree(): " << year << ", " << dotautau << std::endl;

   TChain * c = new TChain("Events");
   const TString tags[5] = {"DYJetsToLL", "DY1JetsToLL", "DY2JetsToLL", "DY3JetsToLL", "DY4JetsToLL"}; 
   for (int i = 0; i < 5; ++i) {
      char infile[100];
      sprintf(infile, "./%s_%d.root", tags[i].Data(), year);
      //ifstream f(infile);
      //if (f.good()) c->Add(infile);
      //c->Add(infile);
      c->Add(infile);
   }
   std::cout << "   entries in input chain: " << c->GetEntries() << std::endl;

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
   std::cout << "   entries in output tree: " << t->GetEntries() << std::endl;
   t->Write();
   f->Close();
}

void addBranch(const TString infile, const int year)
{std::cout << "addBranch(): " << infile << ", " << year << std::endl;

   char fname[100];
   sprintf(fname, "%s_%d.root", infile.Data(), year);
   TFile * f = TFile::Open(fname, "UPDATE");
   TTree * t = (TTree*)f->Get("Events");

   UChar_t LHE_Njets;
   t->SetBranchAddress("LHE_Njets", &LHE_Njets);

   float w[5];
   if (year==2016) w[0]=8.82923e-05; w[1]=1.39305e-05; w[2]=1.06292e-05; w[3]=4.98874e-06; w[4]=5.9883e-06;
   if (year==2017) w[0]=5.92978e-05; w[1]=1.32271e-05; w[2]=1.01341e-05; w[3]=4.95732e-06; w[4]=5.81179e-06;
   if (year==2018) w[0]=6.17395e-05; w[1]=1.33982e-05; w[2]=1.02245e-05; w[3]=4.99379e-06; w[4]=5.84469e-06;

   float xsWeight;
   t->SetBranchAddress("xsWeight", &xsWeight);
   float xsWeight_inc;
   TBranch * b_xsWeight_inc = t->Branch("xsWeight_inc", &xsWeight_inc, "xsWeight_inc/F");

   const int n = t->GetEntries();
   for (int i = 0; i < n; ++i) {
      if (i%100000==0) {
         std::cout << "   beginning event: " << i << ", " << float(i)/float(n) << "pc of total" << std::endl;
      }
      t->GetEntry(i);
      xsWeight_inc = xsWeight;
      xsWeight = w[(int)LHE_Njets];
      t->Fill(); 
   }
   t->Write();
   f->Close();
}
*/
void addBranch(const int year, const bool dotautau)
{std::cout << "addBranch(): " << year << ", " << dotautau << std::endl;

   char fname[100];
   if (dotautau) {
      sprintf(fname, "DYJetsToTauTau_%d.root", year);
   } else {
      sprintf(fname, "DYJetsToEEMuMu_%d.root", year);
   }
   TFile * f = TFile::Open(fname, "UPDATE");
   TTree * t = (TTree*)f->Get("Events");
   const int n = t->GetEntries();
   std::cout << "   number of events in input tree: " << n << std::endl;

   UChar_t LHE_Njets;
   t->SetBranchAddress("LHE_Njets", &LHE_Njets);

   float w[5];
   if (year==2016) {
      w[0]=5.83943786e-05;
      w[1]=1.28863959e-05;
      w[2]=9.96373726e-06;
      w[3]=4.89242607e-06;
      w[4]=5.81820175e-06;
   }
   if (year==2017) {
      w[0]=5.92977913e-05;
      w[1]=1.31622501e-05;
      w[2]=1.0101692e-05;
      w[3]=5.3465484e-06;
      w[4]=5.81637947e-06;
   }
   if (year==2018) {
      w[0]=6.17394936e-05;
      w[1]=1.33982049e-05;
      w[2]=1.02245279e-05;
      w[3]=4.99378773e-06;
      w[4]=5.84468721e-06;
   }

   for (int i = 0; i < 5; ++i) {
      std::cout << "LHE_Njets " << i << "; weight: " << w[i] << std::endl;
   }

   float xsWeight;
   TBranch * b_xsWeight = t->Branch("xsWeight", &xsWeight, "xsWeight/F");

   for (int i = 0; i < n; ++i) {
      if (i%100000==0) {
         std::cout << "   beginning event: " << i << ", " << float(i)/float(n) << "pc of total" << std::endl;
      }
      //std::cout << "Event: " << i << std::endl;
      t->GetEntry(i);
      xsWeight = w[(int)LHE_Njets];
      b_xsWeight->Fill();
      //t->Fill();
   }
   t->Write();
   const int n2 = t->GetEntries();
   std::cout << "   number of events in output tree: " << n2 << std::endl;
   f->Close();
   std::cout << "end addBranch()" << std::endl;
}

void validate(const int year)
{std::cout << "validate(): " << year << std::endl;

   char inbuffer[100];
   //sprintf(inbuffer, "DYJetsToLL_%d.root", year);
   sprintf(inbuffer, "/eos/uscms/store/user/fojensen/cmsdas_16042021/DYJetsToLL_%d.root", year);
   TFile * f = TFile::Open(inbuffer);
   TTree * c_inc = (TTree*)f->Get("Events");

   TH1D * h_inc = new TH1D("h_inc", ";LHE_Njets;events / 1", 6, -0.5, 5.5);
   h_inc->Sumw2();
   std::cout << "project from inclusive sample:" << std::endl;
   const int n_inc = c_inc->Project("h_inc", "LHE_Njets", "xsWeight * (1>0)");
   std::cout << "   # of entries: " << n_inc << std::endl;

   char in1[100];
   sprintf(in1, "/eos/uscms/store/user/fojensen/cmsdas_16042021/DYJetsToTauTau_%d.root", year);
   TFile * f_tautau = TFile::Open(in1);
   TTree * t_tautau = (TTree*)f_tautau->Get("Events");
 
   char in2[100];
   sprintf(in2, "/eos/uscms/store/user/fojensen/cmsdas_16042021/DYJetsToEEMuMu_%d.root", year);
   TFile * f_eemumu = TFile::Open(in2);
   TTree * t_eemumu = (TTree*)f_eemumu->Get("Events");

   TH1D * h_stitch = new TH1D("h_stitch", "", 6, -0.5, 5.5);
   h_stitch->Sumw2();
   std::cout << "project from stitched sample:" << std::endl;
   const int n_tautau = t_tautau->Project("h_stitch", "LHE_Njets", "xsWeight * (1>0)");
   const int n_eemumu = t_eemumu->Project("+h_stitch", "LHE_Njets", "xsWeight * (1>0)");
   std::cout << "   # of tautau entries " << n_tautau << std::endl;
   std::cout << "   # of eemumu entries " << n_eemumu << std::endl;

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
   //r->SetMinimum(0.85);
   r->SetLineColor(602);
   //r->SetMaximum(1.25);
   r->SetStats(0);
   TLine * line = new TLine(-0.5, 1., 5.5, 1.);
   line->SetLineStyle(2);
   line->SetLineColor(2);
   line->Draw();
   char savetag[100];
   sprintf(savetag, "validateStitching_%d.pdf", year);
   c->SaveAs(savetag);
   std::cout << "end validate()" << std::endl;
}

void processDY(const int year)
{std::cout << "processDY(): " << year << std::endl;

   splitTree(year, false);
   addBranch(year, false);
   splitTree(year, true);
   addBranch(year, true);
   validate(year);
}

void processDY2015()
{
   splitTree(2015, false);
   splitTree(2015, true);
}
