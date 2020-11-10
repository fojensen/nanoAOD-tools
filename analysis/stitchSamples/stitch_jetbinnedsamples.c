#include <TLine.h>
#include <TChain.h>
#include <iostream>
#include <TH1D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

void getXS()
{
   // WJetsToLNu
   //const double xs_inc = 61334.9;
   //const double n_inc_tot_ = 70454125.;
   //const TString infile = "root://cmsxrootd.fnal.gov//store/user/fojensen/W01234JetsToLNu_nocuts.root";
   //const double n[5] = {0., 51082776., 23290710., 14508481., 10082747.};

   //DYJetsToLL_M-50
   const float xs_inc = 6077.22;
   const int n_inc_tot_ = 100194597;
   const TString infile = "root://cmsxrootd.fnal.gov//store/user/fojensen/DY01234JetsToLL_nocuts.root";
   //const TString infile = "/eos/uscms/store/user/fojensen/DY01234JetsToLL_nocuts.root";
   const float n[5] = {0., 68898175., 20456037., 5652357., 2809978.};

   TChain c("Events");
   c.Add(infile);
   TH1D * h = new TH1D("h", ";LHE_Njets;generated events / bin", 5, -0.5, 4.5);
   
   const double n_inc_tot = c.Project("h", "LHE_Njets");
   if (n_inc_tot!=n_inc_tot_) {
      std::cout << "You don't have the whole dataset!" << std::endl;
      std::cout << "You have: " << n_inc_tot << "; you need: " << n_inc_tot_ << " ("<< n_inc_tot/n_inc_tot_ << "%)" << std::endl;
   }

   double n_inc[5];
   double xs[5];
   double f[5];
   for (int i = 0; i < 5; ++i) {
      n_inc[i] = h->GetBinContent(i+1);
      f[i] = n_inc[i]/n_inc_tot;
      const double ferr = f[i] * sqrt((1./n_inc[i])+(1./n_inc_tot));
      xs[i] = xs_inc * f[i];
      const double xserr = xs_inc * ferr;
      std::cout << "LHE_Njets: " << i << "; yield: " << n_inc[i] << "; fraction: " << f[i] << "+-" << ferr << "; xs: " << xs[i] << "+-" << xserr << std::endl;
   }

   double ntot[5];
   for (int i = 0; i < 5; ++i) ntot[i] = n_inc[i]+n[i];
   
   double xs_weight[5];
   for (int i = 0; i < 5; ++i) {
      xs_weight[i] = xs[i] / ntot[i];
      //std::cout << "LHE_Njets: " << i << "; xs_weight: " <<  printf("%12.12f", xs_weight[i]) << std::endl;
      std::cout << "LHE_Njets: " << i << "; xs_weight: " << xs_weight[i] << std::endl;
   }

}

void stitch_jetbinnedsamples(const TString year)
{
   //DYJetsToLL
   const TString files[5] = {"DY01234JetsToLL_M-50", "DY1JetsToLL_M-50", "DY2JetsToLL_M-50", "DY3JetsToLL_M-50", "DY4JetsToLL_M-50"};
   
   const double w[5] = {6.06542e-05, 1.17831e-05, 1.31763e-05, 1.62313e-05, 1.78722e-05};
   const TString outputFile = "../outputData_"+year+"/DYJetsToLL_M-50.root";

   TChain * c = new TChain("Events");
   for (int i = 0; i < 5; ++i) {
      char buffer[100];
      sprintf(buffer, "../outputData_%s/%s.root", year.Data(), files[i].Data());
      c->Add(buffer);
      std::cout << c->GetEntries() << std::endl;
   }
   std::cout << "entries in the input chain: " << c->GetEntries() << std::endl;   

   TFile * f = new TFile(outputFile, "RECREATE");
   TTree * t = c->CopyTree("1>0");
   std::cout << "entries in the copied tree: " << t->GetEntries() << std::endl;

   double xsWeight;
   TBranch * b_xsWeight = t->Branch("xsWeight", &xsWeight, "xsWeight/D");
   UChar_t LHE_Njets;
   t->SetBranchAddress("LHE_Njets", &LHE_Njets);

   for (int i = 0; i < t->GetEntries(); ++i) {
      t->GetEntry(i);
      xsWeight = w[LHE_Njets];
      b_xsWeight->Fill();
   }

   t->Write();
   f->Close();
}

void validate()
{
   //WJetsToLNu
   //const TString files[2] = {"../outputData/W01234JetsToLNu.root", "../outputData/WJetsToLNu.root"};

   //DYJetsToLL
   const TString files[2] = {"../outputData_2018/DY01234JetsToLL_M-50.root", "../outputData_2018/DYJetsToLL_M-50.root"};

   TChain c_inc("Events");
   std::cout << "Adding " << files[0] << std::endl;
   c_inc.Add(files[0]);
   TH1D * h_inc = new TH1D("h_inc", ";LHE_Njets;events / 1", 6, -0.5, 5.5);
   h_inc->Sumw2();
   const int n_inc = c_inc.Project("h_inc", "LHE_Njets", "59725.419 * xsWeight * (1>0)");
  
   std::cout << c_inc.GetEntries() << " entries in the inclusive tree" << std::endl; 
   std::cout << n_inc << " entries in the inclusive projection." << std::endl;

   TChain c_stitch("Events");
   std::cout << "Adding " << files[1] << std::endl;
   c_stitch.Add(files[1]);
   TH1D * h_stitch = new TH1D("h_stitch", "", 6, -0.5, 5.5);
   h_stitch->Sumw2();
   const int n_stitch = c_stitch.Project("h_stitch", "LHE_Njets", "59725.419 * xsWeight * (1>0)");
   std::cout << c_stitch.GetEntries() << " entries in the stitched tree" << std::endl;
   std::cout << n_stitch << " entries in the stitched projection." << std::endl;

   TH1D * r = (TH1D*)h_stitch->Clone("r");
   r->Divide(h_inc);
   r->SetTitle(";LHE_Njets;combined / inclusive");
   for (int i = 0; i < r->GetNbinsX(); ++i) {
      std::cout << "LHE_NJets " << i << std::endl;
      std::cout << "   stitch: " << h_stitch->GetBinContent(i+1) << std::endl;
      std::cout << "   inc: " << h_inc->GetBinContent(i+1) << std::endl;
      std::cout << r->GetBinContent(i+1) << " +- " << r->GetBinError(i+1) << std::endl;
   }

   TCanvas * c = new TCanvas("c", "", 800, 400);
   c->Divide(2, 1);
   TPad * p1 = (TPad*)c->cd(1);
   h_inc->SetLineWidth(2);
   h_inc->SetStats(0);
   h_inc->SetLineColor(6);
   h_inc->Draw("HIST, E");
   h_stitch->SetLineWidth(2);
   h_stitch->SetLineColor(7);
   h_stitch->Draw("HIST, E, SAME");
   h_inc->SetMinimum(1000.);
   h_inc->SetMaximum(1e7);
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
   c->SaveAs("./validateStitching.pdf");
}

