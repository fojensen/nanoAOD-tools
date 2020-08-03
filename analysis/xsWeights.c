#include <iostream>
#include <TFile.h>
#include <TTree.h>

void runPoint(const TString tag, const double n, const double xs)
{
   std::cout << "Adding xsWeight to " << tag << std::endl;
   char buffer[100];
   sprintf(buffer, "./outputData/%s.root", tag.Data());
   TFile * f = TFile::Open(buffer, "UPDATE");

   TTree * t = (TTree*)f->Get("Events");
   if (t->GetEntries()==0) {
      std::cout << "   no entries!" << std::endl;
      return;
   }
   
   if (t->GetBranch("xsWeight")) {
      std::cout << "   xsWeight is already present!" << std::endl;
      return;
   }

   std::cout << "   Total number entries in the (skimmed) input chain: " << t->GetEntries() << std::endl;
   std::cout << "   Input xs: " << xs << std::endl;
   double xsWeight = xs/n;
   std::cout << "   xsWeight: " << xsWeight << std::endl;
   std::cout << " @ 59725.419: " << 59725.419 * xsWeight << std::endl;
   TBranch * b_xsWeight = t->Branch("xsWeight", &xsWeight, "xsWeight/D");
   for (int i = 0; i < t->GetEntries(); ++i) {
      b_xsWeight->Fill();
   }
   std::cout << "   Total number of entries in the output tree: " << t->GetEntries() << std::endl;
   t->Write();
   f->Close();
}

//https://github.com/RazorCMS/RazorAnalyzer/blob/master/data/xSections.dat
//https://twiki.cern.ch/CMS/SummaryTable1G25ns
//https://github.com/TreeMaker/TreeMaker/blob/Run2_2017/WeightProducer/python/MCSampleValues.py
void xsWeights()
{
   //runPoint("WJetsToLNu", 71026861., 61526.7);//ra2b
   //runPoint("W1JetsToLNu", 51082776., 9299.1671);
   //runPoint("W2JetsToLNu", 23290710., 3171.68357);
   //runPoint("W3JetsToLNu", 14508481., 1112.59086);
   //runPoint("W4JetsToLNu", 10082747., 627.274341);
   //runPoint("WGToLNuG", 6012425., 405.271);
  
   runPoint("DYJetsToLL_M-10to50", 46976952.+39392062., 18610.);
   runPoint("DY01234JetsToLL_M-50", 100194597., 6077.22);//ra2b
   runPoint("DY1JetsToLL_M-50", 68898175., 998.95199);
   runPoint("DY2JetsToLL_M-50", 20456037., 341.388862);
   runPoint("DY3JetsToLL_M-50", 5652357., 124.195209);
   runPoint("DY4JetsToLL_M-50", 2809978., 70.5905277);
   //runPoint("ZGToLLG_01J_5f", 13946364., 55.53);

   //runPoint("TTJets", 10244307, 831.76); //ra2b 
   //runPoint("TTToHadronic", 131024000.+199524000., 377.96);//ra2b
   //runPoint("TTToSemiLeptonic", 100790000.+199829998., 365.34);//ra2b
   runPoint("TTTo2L2Nu", 64310000., 88.29);//ra2b
  
   //runPoint("TTGJets", 4691915., 3.697); //ra2b
   //runPoint("TTGamma_Hadronic", 5819000.+4940000., 1.7086);
   //runPoint("TTGamma_SingleLept", 11806000., 0.7028+0.7053);  
   //runPoint("TTGamma_SingleLeptFromTbar", 4945000., 0.7028); //ra2b
   //runPoint("TTGamma_SingleLeptFromT", 4840000., 0.7053); //ra2b
   //runPoint("TTGamma_Dilept", 5968000.+4940000., 0.5799); // ra2b

   //runPoint("ST_t-channel_top_5f", 5903676., 136.02);
   //runPoint("ST_t-channel_antitop_5f", 3955024., 80.95);
   //runPoint("ST_tW_top_5f_inclusiveDecays", 9598000., 34.91);//ra2b
   //runPoint("ST_tW_antitop_5f_inclusiveDecays", 7623000., 34.97);//ra2b

   runPoint("WW", 7850000., 51.723);//ra2b
   runPoint("WZ", 3885000., 47.13);//ra2b
   runPoint("ZZ", 1979000., 16.523);//ra2b

   //runPoint("Taustar_m175", 3765., 0.0177*1.285);
   runPoint("Taustar_m250", 9800., 0.0177*1.285);
   runPoint("Taustar_m1000", 10000., 4.069e-3*1.270);
}

