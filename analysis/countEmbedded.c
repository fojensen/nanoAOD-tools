#include <TFile.h>
#include <TTree.h>
#include <iostream>

void countEmbedded()
{
   const TString tags[5] = {"Embedded_2018", "Embedded_2018A", "Embedded_2018B", "Embedded_2018C", "Embedded_2018D"};
   const double l[5] =  {59725.419, 14027.047, 7060.622, 6894.771, 31742.979};
   double n[5] = {0., 0., 0., 0., 0.};
   double f[5] = {0., 0., 0., 0., 0.};
   for (int i = 0; i < 5; ++i) {
      TFile * file = TFile::Open("./outputData/"+tags[i]+".root");
      TTree * tree = (TTree*)file->Get("Events");
      n[i] = tree->GetEntries("MuTauGamma_havePair==1 && MuMuGamma_havePair==0");
      f[i] = n[i]/l[i];
      std::cout << tags[i] << std::endl;
      std::cout << "   # of events: " << n[i] << "; lumi: " << l[i] << std::endl;
      std::cout << "   events / lumi: " << f[i] << std::endl;
   }
}
