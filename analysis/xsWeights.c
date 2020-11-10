#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

double getWeight(const int nPV, TH1D * h, TH1D *htemp)
{
   const int bin = htemp->Fill(nPV);
   const double sf = h->GetBinContent(bin);  
   return sf;
}

void runPoint(const TString tag, const double n, const double xs, const TString year)
{
   TFile * f_sf = TFile::Open("f_sf.root");
   TH1D * h_sf_ = (TH1D*)f_sf->Get("h_sf");
   TH1D * h_sf = (TH1D*)h_sf_->Clone("h_sf");
   TH1D * h_sftemp = (TH1D*)h_sf_->Clone("h_sftemp");
   //delete f_sf;

   std::cout << h_sf->GetEntries() << std::endl;

   std::cout << "Adding xsWeight to " << tag << std::endl;

   char buffer[100];
   sprintf(buffer, "./outputData_%s/%s.root", year.Data(), tag.Data());
   std::cout << buffer << std::endl;
   TFile * f = TFile::Open(buffer, "UPDATE");

   TTree * t = (TTree*)f->Get("Events");
   if (t->GetEntries()==0) {
      std::cout << "   no entries!" << std::endl;
      return;
   }
   
   if (t->GetBranch("xsWeight") || t->GetBranch("puWeight_emb")) {
      std::cout << "   xsWeight or puWeight is already present!" << std::endl;
   //if (t->GetBranch("xsWeight")) {
      std::cout << "   xsWeight is already present!" << std::endl;
      return;
   }

   std::cout << "   Total number entries in the (skimmed) input chain: " << t->GetEntries() << std::endl;
   std::cout << "   Input xs: " << xs << std::endl;
   double xsWeight = xs/n;
   double puWeight_emb = -1.;
   Int_t PV_npvsGood = 0;
   t->SetBranchAddress("PV_npvsGood", &PV_npvsGood);
   std::cout << "   xsWeight: " << xsWeight << std::endl;
   std::cout << " @ 59725.419: " << 59725.419 * xsWeight << "; " <<  59725.419 * xsWeight * t->GetEntries() << std::endl;
   TBranch * b_xsWeight = t->Branch("xsWeight", &xsWeight, "xsWeight/D");
   TBranch * b_puWeight_emb = t->Branch("puWeight_emb", &puWeight_emb, "puWeight_emb/D");
   for (int i = 0; i < t->GetEntries(); ++i) {
      t->GetEntry(i);
      b_xsWeight->Fill();
      puWeight_emb = getWeight(PV_npvsGood, h_sf, h_sftemp);
      b_puWeight_emb->Fill();
   }
   std::cout << "   Total number of entries in the output tree: " << t->GetEntries() << std::endl;
   t->Write();
   f->Close();
}

//https://github.com/RazorCMS/RazorAnalyzer/blob/master/data/xSections.dat
//https://twiki.cern.ch/CMS/SummaryTable1G25ns
//https://github.com/TreeMaker/TreeMaker/blob/Run2_2017/WeightProducer/python/MCSampleValues.py
void xsWeights_2016()
{
   const TString year = "2016";
   runPoint("DYJetsToLL_M-10to50", 34909242+49748967, 18610., year); //https://twiki.cern.ch/CMS/SummaryTable1G25ns#DY_Z
   runPoint("DY01234JetsToLL_M-50", 49748967+93007332, 6077.22, year); //ra2b
   runPoint("DY1JetsToLL_M-50", 63730337, 1007.58, year);
   runPoint("DY2JetsToLL_M-50", 19879279, 344.336, year);
   runPoint("DY3JetsToLL_M-50", 5857441, 125.267, year);
   runPoint("DY4JetsToLL_M-50", 4197868, 71.2, year);
   runPoint("TTTo2L2Nu", 67860400, 88.29, year); //ra2b
   runPoint("ST_tW_antitop", 10240710, 38.06*0.530775, year); //ra2b
   runPoint("ST_tW_top", 1019598, 38.09*0.530775, year); //ra2b
   runPoint("WW", 994012+6988168, 51.723, year); //ra2b
   runPoint("WZ", 1000000+2997571, 47.13, year); //ra2b
   runPoint("ZZ", 990064+998034, 16.523, year); //ra2b
   runPoint("EWKZ2Jets_ZToLL_M-50", 150000+150000+699451, 3.998, year); //https://cds.cern.ch/record/2647950/files/TS2018_028_2.pdf

   runPoint("Taustar_m250", 50000, 1, year);   
   runPoint("Taustar_m375", 50000, 1, year);
   runPoint("Taustar_m500", 50000, 1, year);
   runPoint("Taustar_m625", 50000, 1, year);
   //runPoint("Taustar_m750", 50000, 1, year);
}

void xsWeights_2017()
{
   const TString year = "2017";
   runPoint("DYJetsToLL_M-10to50", 39521230+39536839, 18610., year);
   runPoint("DY01234JetsToLL_M-50", 47990369+49011552, 6077.22, year);
   runPoint("DY1JetsToLL_M-50", 42331295+33669127, 1007.58, year);
   runPoint("DY2JetsToLL_M-50", 88895+9701595, 344.336, year);
   runPoint("DY3JetsToLL_M-50", 5748466+1149467, 125.267, year);
   runPoint("DY4JetsToLL_M-50", 4328648, 71.2, year);
   runPoint("TTTo2L2Nu", 9000000, 88.29, year);
   runPoint("ST_tW_antitop", 5635539, 34.97*0.530775, year);
   runPoint("ST_tW_top", 4955102, 34.91*0.530775, year);
   runPoint("WW", 7765828, 51.723, year);
   runPoint("WZ", 3928630, 47.13, year);
   runPoint("ZZ", 1949768, 16.523, year);
   runPoint("EWKZ2Jets_ZToLL_M-50", 952504, 3.998, year);

   runPoint("Taustar_m375", 50000, 1, year);
   runPoint("Taustar_m500", 50000, 1, year);
   runPoint("Taustar_m1000", 50000, 1, year);
   runPoint("Taustar_m1250", 50000, 1, year);
}

void xsWeights_2018()
{
   const TString year = "2018";
   runPoint("DYJetsToLL_M-10to50", 39392062+46976952, 18610., year);
   runPoint("DY01234JetsToLL_M-50", 100194597, 6077.22, year);
   runPoint("DY1JetsToLL_M-50", 68898175, 1007.58, year);
   runPoint("DY2JetsToLL_M-50", 20456037, 344.336, year);
   runPoint("DY3JetsToLL_M-50", 5652357, 125.267, year);
   runPoint("DY4JetsToLL_M-50", 2809978, 71.2, year);
   runPoint("TTTo2L2Nu", 64310000, 88.29, year);
   runPoint("TTToSemiLeptonic", 199829998.+100790000., 365.34, year);
   runPoint("ST_tW_antitop", 1086487, 34.97*0.530775, year); 
   runPoint("ST_tW_top", 1085847., 34.91*0.530775, year);
   runPoint("WW", 7850000., 51.723, year);
   runPoint("WZ", 3885000., 47.13, year);
   runPoint("ZZ", 1979000., 16.523, year);
   runPoint("EWKZ2Jets_ZToLL_M-50", 928000., 3.998, year);

   runPoint("WGToLNuG", 6108186., 463.9, year); 
   runPoint("QCD_Pt-20toInf_MuEnrichedPt15", 22165320., 239400.0, year);

   runPoint("Taustar_m250", 50000, 0.02135, year);
   runPoint("Taustar_m375", 50000, 0.01546, year);
   runPoint("Taustar_m500", 50000, 0.01177, year);
   runPoint("Taustar_m625", 50000, 0.009072, year);
   runPoint("Taustar_m750", 50000, 0.007024, year);
   runPoint("Taustar_m1000", 50000, 0.004236, year);
   runPoint("Taustar_m1250", 50000, 0.002554, year);
   runPoint("Taustar_m1500", 50000, 0.001522, year);
   runPoint("Taustar_m1750", 50000, 0.0009048, year);
   runPoint("Taustar_m2000", 50000, 0.0005328, year);
   runPoint("Taustar_m5000", 50000, 1.178e-06, year);
}

void xsWeights()
{
   //xsWeights_2016();
   //xsWeights_2017();
   xsWeights_2018();
}

