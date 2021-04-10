#include <TFile.h>
#include <TTree.h>
#include <iostream>
void bskim(const TString infile, const TString outfile)
{
   std::cout << "bskim()" << std::endl;
   TFile * fin = TFile::Open(infile);
   TTree * tin = (TTree*)fin->Get("Events");
   TFile * fout = new TFile(outfile, "RECREATE");
   std::cout << "   CopyTree()" << std::endl;
   TTree * tout = (TTree*)tin->CopyTree("JetProducer_nBJetT==0");
   std::cout << "   Write()" << std::endl;
   tout->Write();
   fout->Close();
}
