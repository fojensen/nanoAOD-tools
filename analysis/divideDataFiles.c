#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <TCut.h>

void runPoint(const TString intag, const int nchunks)
{
   std::cout << intag << std::endl;
   char infile[1000];
   sprintf(infile, "root://cmseos.fnal.gov///store/user/fojensen/cmsdasskims/%s.root", intag.Data());
   TFile * f_in = TFile::Open(infile);
   TTree * t_in = (TTree*)f_in->Get("Events");
   const double n = t_in->GetEntries();
   std::cout << "   total entries: " << n << std::endl;
   std::cout << "   request to split by: " << nchunks << std::endl;
   int width = n / nchunks;
   std::cout << "   entries per file: " << width << std::endl;

   int ntrees[nchunks];
   int nsum = 0;

   for (int i = 0; i < nchunks; ++i) {
      std::cout << "   now beginning chunk " << i << std::endl;

      char fname[100];
      sprintf(fname, "%s_%d.root", intag.Data(), i);
      TFile * f = new TFile(fname, "RECREATE");

      int nentries = width;
      int firstentry = width*i;
      if (i==nchunks-1) nentries = n;
      std::cout << "      nentries=" << nentries << std::endl;
      std::cout << "      firstentry=" << firstentry << std::endl;
      TTree * t = (TTree*)t_in->CopyTree("", "", nentries, firstentry);

      ntrees[i] = t->GetEntries();
      std::cout << "      contains " << ntrees[i] << " entries." << std::endl;
      t->Write();
      f->Close();
      nsum += ntrees[i];

      char cmdcp[1000];
      sprintf(cmdcp, "xrdcp -f %s root://cmseos.fnal.gov///store/user/fojensen/cmsdasskims/", fname);
      system(cmdcp);

      char cmdrm[1000];
      sprintf(cmdrm, "rm %s", fname);
      system(cmdrm);
   }

   std::cout << "   total in all trees:" << nsum << std::endl;
   const int nmiss = n - nsum;
   std::cout << "   missing entries: " << nmiss << std::endl;
}

void divideDataFiles()
{
   //runPoint("QCD_Pt20toInf_MuEnrichedPt15", 3);

   //runPoint("SingleMuon_2018A", 2);
   //runPoint("SingleMuon_2018B", 2);
   //runPoint("SingleMuon_2018C", 2);
   //runPoint("SingleMuon_2018D", 2);   
  
   runPoint("EGamma_2018A", 4);
   //runPoint("EGamma_2018B", 3);
   //runPoint("EGamma_2018C", 3);
   runPoint("EGamma_2018D", 5);
 
   //runPoint("Tau_2018A", 2);
   //runPoint("Tau_2018B", 2);
   //runPoint("Tau_2018C", 2);
   //runPoint("Tau_2018D", 3);
}

