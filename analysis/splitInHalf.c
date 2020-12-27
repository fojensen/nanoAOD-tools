#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <TCut.h>

void runPoint(const TString intag)
{
   std::cout << intag << std::endl;
   char infile[1000];
   sprintf(infile, "root://cmseos.fnal.gov///store/user/fojensen/cmsdasskims/%s.root", intag.Data());
   TFile * f_in = TFile::Open(infile);
   TTree * t_in = (TTree*)f_in->Get("Events");

   const TCut cut1 = "run>=320394 && run<=322180";
   const TCut cut2 = "run>=322181 && run<=325273";

   const double n = t_in->GetEntries();
   const double n1 = t_in->GetEntries(cut1);
   const double n2 = t_in->GetEntries(cut2);

   std::cout << "   total entries: " << n << std::endl;
   std::cout << "   total entries in file 1: " << n1 << std::endl;
   std::cout << "   f1: " << n1/n << std::endl;
   std::cout << "   total entries in file 2: " << n2 << std::endl;
   std::cout << "   f2: " << n2/n << std::endl;

   const int nmiss = n-n1-n2;
   std::cout << "   total missing entries: " << nmiss << std::endl;
   if (nmiss) return;

   char f1name[1000];
   sprintf(f1name, "%s_1.root", intag.Data());
   TFile * f1 = new TFile(f1name, "RECREATE");
   std::cout << "   t_in->CopyTree(cut1)" << std::endl;
   TTree * t1 = (TTree*)t_in->CopyTree(cut1);
   t1->Write();
   f1->Close();

   char f2name[1000];
   sprintf(f2name, "%s_2.root", intag.Data());
   TFile * f2 = new TFile(f2name, "RECREATE");
   std::cout << "   t_in->CopyTree(cut2)" << std::endl;
   TTree * t2 = (TTree*)t_in->CopyTree(cut2);
   t2->Write();
   f2->Close();
}

void splitInHalf()
{
   //runPoint("SingleMuon_2018D");
   //runPoint("EGamma_2018D");
   runPoint("Tau_2018D");
}

