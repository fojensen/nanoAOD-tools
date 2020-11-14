#include <TLine.h>
#include <THStack.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TLegend.h>
#include <iostream>

double addOverflow(TH1D * h)
{
   const int n = h->GetNbinsX();
   const double o = h->GetBinContent(n+1);
   if (o>0.) {
      const double oerr = h->GetBinError(n+1);
      const double y = h->GetBinContent(n);
      const double yerr = h->GetBinError(n);
      h->SetBinContent(n+1, 0.);
      h->SetBinError(n+1, 0.);
      h->SetBinContent(n, o+y);
      const double err = sqrt((oerr*oerr)+(yerr*yerr));
      std::cout << "   overflow: " << o << " +- " << oerr << "; lastbin: " << y << " +- " << yerr << "; new lastbin: " << o+y << " +- " << err << std::endl;
      
   }
   return o;
}

void runPoint(TH1D * h, const TString var, const TCut baseline, const bool isSig=true)
{
   std::cout << "*** beginning " << h->GetName() << " ***" << std::endl;
   // *** INCLUSIVE *** //
   h->SetStats(0);
   const TCut regionA = "MuTauGamma_qq==-1 &&  (64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionB = "MuTauGamma_qq==+1 &&  (64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionC = "MuTauGamma_qq==-1 && !(64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionD = "MuTauGamma_qq==+1 && !(64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionCuts[4] = {regionA, regionB, regionC, regionD};

   // *** FILL MC HISTOGRAMS *** //

   const int nmc = 9;
   TH1D *h_mc[4][nmc][2];
   TH1D *h_mc_sum[4][2];
   const TString titles[4] = {"A", "B", "C", "D"};
   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 2; ++j) {
         char hname[100];
         sprintf(hname, "h_mc_sum_%d_%d", i, j);
         h_mc_sum[i][j] = (TH1D*)h->Clone(hname);
         h_mc_sum[i][j]->SetTitle(titles[i]);
      }
   }
   const TCut genCuts[2] = {"Sum$(Tau_genPartFlav==5)==1 && Sum$(Muon_genPartFlav==15)==1", "!(Sum$(Tau_genPartFlav==5)==1 && Sum$(Muon_genPartFlav==15)==1)"};
   TString mcWeights[4];
   mcWeights[0] = "59725.419 * xsWeight * MuTauGamma_TauSFmuo * MuTauGamma_TauSFele * MuTauGamma_MuSFId * MuTauGamma_MuSFIso[1] * MuTauGamma_MuSFTrigger * MuTauGamma_TauSFjet[6]";
   mcWeights[1] = "59725.419 * xsWeight * MuTauGamma_TauSFmuo * MuTauGamma_TauSFele * MuTauGamma_MuSFId * MuTauGamma_MuSFIso[1] * MuTauGamma_MuSFTrigger * MuTauGamma_TauSFjet[6]";
   mcWeights[2] = "59725.419 * xsWeight * MuTauGamma_TauSFmuo * MuTauGamma_TauSFele * MuTauGamma_MuSFId * MuTauGamma_MuSFIso[1] * MuTauGamma_MuSFTrigger";
   mcWeights[3] = "59725.419 * xsWeight * MuTauGamma_TauSFmuo * MuTauGamma_TauSFele * MuTauGamma_MuSFId * MuTauGamma_MuSFIso[1] * MuTauGamma_MuSFTrigger";
   //for (int i = 0; i < 4; ++i) mcWeights[i] = mcWeights[i] + " * puWeight";

   TString mctags[nmc];
   int col[nmc];
   TString labels[nmc];
   mctags[0] = "ZZ";                   col[0] = 52;  labels[0] = "ZZ";
   mctags[1] = "WZ";                   col[1] = 53;  labels[1] = "WZ";
   mctags[2] = "WW";                   col[2] = 54;  labels[2] = "WW";
   mctags[3] = "ST_tW";                col[3] = 209; labels[3] = "tW";
   mctags[4] = "TTToSemiLeptonic";     col[4] = 210; labels[4] = "t#bar{t} #rightarrow l#nu2q";
   mctags[5] = "TTTo2L2Nu";            col[5] = 211; labels[5] = "t#bar{t} #rightarrow 2l2#nu";
   mctags[6] = "EWKZ2Jets_ZToLL_M-50"; col[6] = 96;  labels[6] = "EWKZ50";
   mctags[7] = "DYJetsToLL_M-10to50";  col[7] = 97;  labels[7] = "DY10to50";
   mctags[8] = "DYJetsToLL_M-50";      col[8] = 98;  labels[8] = "DY50";   

   for (int i = 0; i < nmc; ++i) {
      char fname[100];
      sprintf(fname, "./outputData_2018/%s.root", mctags[i].Data());
      TFile * f = TFile::Open(fname);
      TTree * t = (TTree*)f->Get("Events"); 
      for (int j = 0; j < 4; ++j) {
         for (int k = 0; k < 2; ++k) {
            char hname[100];
            //sprintf(hname, "h_%s_%s_%d", mctags[i].Data(), titles[j].Data(), k);
            sprintf(hname, "h_mc_%s_%s_%d", titles[j].Data(), mctags[i].Data(), k);
            h_mc[j][i][k] = (TH1D*)h->Clone(hname);
            char cutString[2000];
            sprintf(cutString, "%s * ( %s && %s && %s )", mcWeights[j].Data(), TString(regionCuts[j]).Data(), TString(genCuts[k]).Data(), TString(baseline).Data());
            std::cout << "project onto " << h_mc[j][i][k]->GetName() << std::endl;
            const int n = t->Project(h_mc[j][i][k]->GetName(), var, cutString);
            std::cout << "   " << n << " events in project." << std::endl;
            addOverflow(h_mc[j][i][k]);
            h_mc[j][i][k]->SetFillColor(col[i]);
            h_mc[j][i][k]->SetTitle(titles[j]);
            h_mc_sum[j][k]->Add(h_mc[j][i][k]);
         }
      }
   }

   // *** FILL SIGNAL HISTOGRAMS *** //
   const int nsig = 11;
   TString sigtag[nsig] = {"m250", "m375", "m500", "m625", "m750", "m1000", "m1250", "m1500", "m1750", "m2000", "m5000"};
   TH1D * h_sig[4][nsig];
   const int col_sig[nsig] = {91, 93, 93, 94, 95};
   for (int i = 0; i < nsig; ++i) {
      char fname[100];
      sprintf(fname, "./outputData_2018/Taustar_%s.root", sigtag[i].Data());
      TFile * f = TFile::Open(fname);
      TTree * t = (TTree*)f->Get("Events");
      for (int j = 0; j < 4; ++j) {
         char hname[100];
         sprintf(hname, "h_sig_%s_%s", titles[j].Data(), sigtag[i].Data());
         h_sig[j][i] = (TH1D*)h->Clone(hname);
         h_sig[j][i]->SetTitle(titles[j]);
         h_sig[j][i]->SetLineWidth(2);
         h_sig[j][i]->SetLineColor(col_sig[i]);
         h_sig[j][i]->SetLineStyle(2);
         char cuts[1000];
         sprintf(cuts, "%s * ( %s && %s )", mcWeights[j].Data(), TString(regionCuts[j]).Data(), TString(baseline).Data());
         std::cout << "project onto " << h_sig[j][i]->GetName() << std::endl;
         const int n = t->Project(h_sig[j][i]->GetName(), var, cuts);
         std::cout << "   " << n << " events in project." << std::endl;
         addOverflow(h_sig[j][i]);
      }
   }

   // *** FILL DATA HISTOGRAMS *** //
   TH1D * h_data[4];
   TFile * f_data = TFile::Open("./outputData_2018/SingleMuon.root");
   TTree * t_data = (TTree*)f_data->Get("Events");
   double datamax = 0.;
   for (int i = 0; i < 4; ++i) {
      if (i==0 && isSig) continue;
      h_data[i] = (TH1D*)h->Clone("h_data_"+TString::Itoa(i, 10));
      h_data[i]->SetMarkerStyle(20);
      h_data[i]->SetTitle(titles[i]);
      h_data[i]->SetLineWidth(2);
      h_data[i]->SetLineColor(1);
      std::cout << "project onto " << h_data[i]->GetName() << std::endl;
      const double y = t_data->Project(h_data[i]->GetName(), var, TString(regionCuts[i]&&baseline).Data());
      std::cout << "   " << y << " events in project." << std::endl;
      addOverflow(h_data[i]);
      if (y>datamax) datamax = y;
   }
   for (int i = 0; i < 4; ++i) {
      if (i==0 && isSig) continue;
      datamax<100 ? h_data[i]->SetMinimum(0.1) : h_data[i]->SetMinimum(10.);
      const double max = pow(10, 1+ceil(log10(datamax)));
      h_data[i]->SetMaximum(max);
   }

    // *** FILL EMBEDDED HISTOGRAMS *** //
   TH1D *h_emb[4];
   TString embWeights[4];
   embWeights[0] = "genWeight * m_sel_trg_ratio * m_sel_idEmb_ratio_1 * m_sel_idEmb_ratio_2 * m_iso_binned_embed_kit_ratio * m_id_embed_kit_ratio * m_trg24_27_embed_kit_ratio * MuTauGamma_trkEff * MuTauGamma_TauSFjet[6]";
   embWeights[1] = "genWeight * m_sel_trg_ratio * m_sel_idEmb_ratio_1 * m_sel_idEmb_ratio_2 * m_iso_binned_embed_kit_ratio * m_id_embed_kit_ratio * m_trg24_27_embed_kit_ratio * MuTauGamma_trkEff * MuTauGamma_TauSFjet[6]";
   embWeights[2] = "genWeight * m_sel_trg_ratio * m_sel_idEmb_ratio_1 * m_sel_idEmb_ratio_2 * m_iso_binned_embed_kit_ratio * m_id_embed_kit_ratio * m_trg24_27_embed_kit_ratio * MuTauGamma_trkEff";
   embWeights[3] = "genWeight * m_sel_trg_ratio * m_sel_idEmb_ratio_1 * m_sel_idEmb_ratio_2 * m_iso_binned_embed_kit_ratio * m_id_embed_kit_ratio * m_trg24_27_embed_kit_ratio * MuTauGamma_trkEff";

   TFile * f_emb = TFile::Open("./outputData_2018/Embedded.root");
   TTree * t_emb = (TTree*)f_emb->Get("Events");
   TFile * f_emb_sf = TFile::Open("./Embedded/Embedded_0_-1.root");
   TTree * t_emb_sf = (TTree*)f_emb_sf->Get("mt_nominal/ntuple");
   t_emb->AddFriend(t_emb_sf);
   double embmax = 0.;
   for (int i = 0; i < 4; ++i) {
      char buffer[100];
      sprintf(buffer, "h_emb_%s", titles[i].Data());
      h_emb[i] = (TH1D*)h->Clone(buffer);
      h_emb[i]->SetMarkerStyle(20);
      h_emb[i]->SetFillColor(7);
      h_emb[i]->SetTitle(titles[i]);
      char cutString[1000];
      sprintf(cutString, "%s * ( %s && %s)", embWeights[i].Data(), TString(regionCuts[i]).Data(), TString(baseline).Data());
      std::cout << "project onto " << h_emb[i]->GetName() << "." << std::endl;
      const int n = t_emb->Project(h_emb[i]->GetName(), var, cutString);
      std::cout << "   " << n << " events in project." << std::endl;
      addOverflow(h_emb[i]);
      const double y = h_emb[i]->Integral();
      if (y>embmax) embmax = y;
   }
   for (int i = 0; i <4; ++i) {
      datamax<100 ? h_emb[i]->SetMinimum(0.1) : h_emb[i]->SetMinimum(10.);
      const double max = pow(10, 1+ceil(log10(embmax)));
      h_emb[i]->SetMaximum(max);
   }


   // *** BCD PREDICTION *** //
   TH1D * h_bkgsub[4];
   for (int i = 0; i < 4; ++i) {
      if (i==0 && isSig) continue;
      h_bkgsub[i] = (TH1D*)h_data[i]->Clone("h_bkgsub_"+TString::Itoa(i, 10));
      h_bkgsub[i]->SetTitle(titles[i]);
      for (int j = 0; j < nmc; ++j) {
         h_bkgsub[i]->Add(h_mc[i][j][1], -1.);
      }
      h_bkgsub[i]->Add(h_emb[i], -1.);
      h_bkgsub[i]->SetLineColor(209);
      h_bkgsub[i]->SetLineWidth(2);
   }

   //const TString rlabels[4] = {"A", "B", "C", "D"};
   //for (int i = 1; i < 4; ++i) {
   //   std::cout << "   " << rlabels[i] << std::endl;
   //   for (int j = 1; j <= h->GetNbinsX(); ++j) {
   //      std::cout << h_data[i]->GetBinContent(j) << std::endl;
   //   }
   //}

   TH1D * h_CoD = (TH1D*)h_bkgsub[2]->Clone("h_CoD");
   h_CoD->SetTitle("");
   h_CoD->Divide(h_bkgsub[3]);
   TH1D * h_BCoD = (TH1D*)h_CoD->Clone("h_BCoD");
   h_BCoD->SetTitle(titles[0]);
   h_BCoD->Multiply(h_bkgsub[1]);
   const double CoD_inc = (h_bkgsub[2]->Integral())/(h_bkgsub[3]->Integral());
   TH1D * h_BCoD_inc = (TH1D*)h_bkgsub[1]->Clone("h_BCoD_inc");
   h_BCoD_inc->Scale(CoD_inc);
   h_BCoD_inc->SetLineColor(207);
   h_BCoD_inc->SetMarkerColor(207);

   std::cout << "data B: " << h_data[1]->GetBinContent(3) << std::endl;
   std::cout << "data C: " << h_data[2]->GetBinContent(3) << std::endl;
   std::cout << "data D: " << h_data[3]->GetBinContent(3) << std::endl;

   std::cout << "bkgsub B: " << h_bkgsub[1]->GetBinContent(3) << std::endl;
   std::cout << "bkgsub C: " << h_bkgsub[2]->GetBinContent(3) << std::endl;
   std::cout << "bkgsub D: " << h_bkgsub[3]->GetBinContent(3) << std::endl;

   std::cout << "emb B: " << h_emb[1]->GetBinContent(3) << std::endl;
   std::cout << "emb C: " << h_emb[2]->GetBinContent(3) << std::endl;
   std::cout << "emb D: " << h_emb[3]->GetBinContent(3) << std::endl;

   std::cout << "mc_sum B: " << h_mc_sum[1][1]->GetBinContent(3) << std::endl;
   std::cout << "mc_sum C: " << h_mc_sum[2][1]->GetBinContent(3) << std::endl;
   std::cout << "mc_sum D: " << h_mc_sum[3][1]->GetBinContent(3) << std::endl;

   h_BCoD->SetFillColor(6);
   h_BCoD->GetYaxis()->SetTitle("prediction");
   datamax<100 ? h_BCoD->SetMinimum(0.1) : h_BCoD->SetMinimum(10.);
   const double max = pow(10, 1+ceil(log10(datamax)));
   h_BCoD->SetMaximum(max);
   h_BCoD->SetLineColor(209);
   h_BCoD->SetMarkerColor(209);

   // MAKE PLOTS

   TCanvas * c1 = new TCanvas("c1_"+TString(h->GetName()), "c1", 1200, 800);
   c1->Divide(3, 2);
   
   TPad * p1 = (TPad*)c1->cd(1);
   p1->SetLogy();
   h_BCoD->Draw("PE");
   h_BCoD_inc->Draw("PE, SAME");
   TLegend * legleg1 = new TLegend(0.25, 0.75, 0.875, 0.875);
   legleg1->SetBorderSize(0);
   legleg1->SetNColumns(2);
   legleg1->AddEntry(h_BCoD, "binned", "P");
   legleg1->AddEntry(h_BCoD_inc, "inclusive", "P");
   legleg1->Draw();

   TLegend * legleg = new TLegend(0.25, 0.75, 0.875, 0.875);
   legleg->SetNColumns(2);
   legleg->SetBorderSize(0);
   legleg->AddEntry(h_data[1], "data", "L");
   legleg->AddEntry(h_bkgsub[1], "data - bkg", "L");
   //legleg->AddEntry(h_sig[0][0], "#tau* 250", "L");
   legleg->AddEntry(h_sig[0][3], "#tau* 625", "L");

   TPad * p2 = (TPad*)c1->cd(2);
   h_data[1]->Draw("HIST, E");
   h_bkgsub[1]->Draw("HIST, E, SAME");
   h_sig[1][0]->Draw("HIST, E, SAME");
   //h_sig[1][3]->Draw("HIST, E, SAME");
   h_data[1]->Draw("HIST, E, SAME");
   legleg->Draw();
   p2->SetLogy();

   TPad * p4 = (TPad*)c1->cd(4);
   h_data[2]->Draw("HIST, E");
   h_bkgsub[2]->Draw("HIST, E, SAME");
   h_sig[2][0]->Draw("HIST, E, SAME");
   //h_sig[2][3]->Draw("HIST, E, SAME");
   h_data[2]->Draw("HIST, E, SAME");
   legleg->Draw();
   p4->SetLogy();

   TPad * p5 = (TPad*)c1->cd(5);
   h_data[3]->Draw("HIST, E");
   h_bkgsub[3]->Draw("HIST, E, SAME");
   h_sig[3][0]->Draw("HIST, E, SAME");
   //h_sig[3][3]->Draw("HIST, E, SAME");
   h_data[3]->Draw("HIST, E, SAME");
   legleg->Draw();
   p5->SetLogy();

   c1->cd(6);
   h_CoD->Draw("PE");
   //h_CoD->SetMinimum(0.);
   //h_CoD->SetMaximum(3.);
   h_CoD->SetMarkerColor(1);
   h_CoD->SetLineColor(1);
   h_CoD->GetYaxis()->SetTitle("C / D");

   TLine * l = new TLine(h->GetBinLowEdge(1), CoD_inc, h->GetBinLowEdge(h->GetNbinsX()+1), CoD_inc);
   l->SetLineStyle(2);
   l->Draw();

   c1->SaveAs("./plots/fullstudy."+TString(h->GetName())+".bcd.pdf");

   // *** MC COMPOSITION OF EMBEDDED *** //
   THStack * s_emb[4];
   TH1D * r_emb[4];
   for (int i = 0; i < 4; ++i) {
      char hname[100];
      sprintf(hname, "r_emb_%d", i);
      r_emb[i] = (TH1D*)h_emb[i]->Clone(hname);
      r_emb[i]->Divide(h_mc_sum[i][0]);
      r_emb[i]->GetYaxis()->SetTitle("embedded / mc");
      s_emb[i] = new THStack();
      char title[100];
      sprintf(title, ";%s;%s", h->GetXaxis()->GetTitle(), h->GetYaxis()->GetTitle());
      s_emb[i]->SetTitle(title);
      for (int j = 0; j < nmc; ++j) {
         s_emb[i]->Add(h_mc[i][j][0]);
      }
   }

   TLegend * leg = new TLegend(0.25, 0.75, 0.875, 0.875);
   leg->SetBorderSize(0);
   leg->SetNColumns(3);
   for (int i = 0; i < nmc; ++i) leg->AddEntry(h_mc[0][i][0], labels[i], "F");
   leg->AddEntry(h_emb[0], "embedded", "P");

   TCanvas * c2 = new TCanvas("c2_"+TString(h->GetName()), "c2", 1600, 800);
   c2->Divide(4, 2);
   for (int i = 0; i < 4; ++i) {
      TPad * p = (TPad*)c2->cd(i+1);
      h_emb[i]->Draw("PE");
      s_emb[i]->Draw("HIST, SAME");
      h_emb[i]->Draw("PE, SAME");
      leg->Draw();
      p->SetLogy();
   }
   for (int i = 0; i < 4; ++i) {
      TPad * p = (TPad*)c2->cd(i+5);
      r_emb[i]->Draw("PE");
      r_emb[i]->SetMinimum(0.);
      r_emb[i]->SetMaximum(2.);
   }
   c2->SaveAs("./plots/fullstudy."+TString(h->GetName())+".emb.pdf");

   TCanvas * c4 = new TCanvas("c4_"+TString(h->GetName()), "c4", 400, 400);
   h_emb[0]->Draw("PE");
   s_emb[0]->Draw("HIST, SAME");
   h_emb[0]->Draw("PE, SAME");
   leg->Draw();
   c4->SetLogy();
   c4->SaveAs("./plots/fullstudy."+TString(h->GetName())+".embsigonly.pdf");

   // *** EMBEDDED APPLIED TO DATA *** ///
   THStack * s_data[4];
   for (int i = 0; i < 4; ++i) {
      s_data[i] = new THStack();
      char title[100];
      sprintf(title, "%s;%s;%s", titles[i].Data(), h->GetXaxis()->GetTitle(), h->GetYaxis()->GetTitle());
      s_data[i]->SetTitle(title); 
      for (int j = 0; j < nmc; ++j) {
         s_data[i]->Add(h_mc[i][j][1]);
      }
      //s_data[i]->Add(h_emb[i]);
      datamax<100 ? s_data[i]->SetMinimum(0.1) : s_data[i]->SetMinimum(10.);
      const double max = pow(10, 1+ceil(log10(datamax)));
      s_data[i]->SetMaximum(max);
   }
   h_BCoD->SetLineColor(1);
   h_BCoD->SetLineWidth(1);
   s_data[0]->Add(h_BCoD); //importantline
   for (int i = 0; i < 4; ++i) s_data[i]->Add(h_emb[i]);

   TH1D * h_mcemb_sum[4];
   for (int i = 0; i < 4; ++i) {
      h_mcemb_sum[i] = (TH1D*)h->Clone("h_mcemb_sum_"+labels[i]);
      for (int j = 0; j < nmc; ++j) h_mcemb_sum[i]->Add(h_mc[i][j][1]);
      h_mcemb_sum[i]->Add(h_emb[i]);
   }
 
   TH1D * h_mcembjet_sum_A = (TH1D*)h_mcemb_sum[0]->Clone("h_mcembjet_sum_A");
   h_mcembjet_sum_A->Add(h_BCoD);

   TH1D * r_data[4];
   for (int i = 0; i < 4; ++i) {
      if (isSig && i==0) continue;
      r_data[i] = (TH1D*)h_data[i]->Clone("r_data_"+labels[i]);
      r_data[i]->Divide(h_mcemb_sum[i]);
      r_data[i]->SetMarkerStyle(24);
      r_data[i]->SetMarkerColor(1);
      r_data[i]->SetLineColor(1);
      r_data[i]->GetYaxis()->SetTitle("data / expected bkg");
   }

   TH1D * r_data_jet_A;
   if (!isSig) {
      r_data_jet_A = (TH1D*)h_data[0]->Clone("r_data_jet");
      r_data_jet_A->Divide(h_mcembjet_sum_A);
      r_data_jet_A->SetMarkerStyle(28);
      r_data_jet_A->SetMarkerColor(1);
      r_data_jet_A->SetLineColor(1);
      r_data_jet_A->GetYaxis()->SetTitle("data / expected bkg");
   }

/*   TCanvas * c3;
   if (!isSig) {
      c3 = new TCanvas("c3_"+TString(h->GetName()), "c3", 800, 400);
      c3->Divide(2, 1);
   } else {
      c3 = new TCanvas("c3_"+TString(h->GetName()), "c3", 400, 400);
   }
   TPad * p3 = (TPad*)c3->cd(1);
   p3->SetLogy();
   if (!isSig) {
      h_data[0]->Draw("PE");
      s_data[0]->Draw("HIST, SAME");
      datamax<100 ? h_data[0]->SetMinimum(0.1) : h_data[0]->SetMinimum(1.);
      const double max = pow(10, 1+ceil(log10(datamax)));
      h_data[0]->SetMaximum(max);
      s_data[0]->SetMaximum(max);
      datamax<100 ? s_data[0]->SetMinimum(0.1) : s_data[0]->SetMinimum(1.);
      h_data[0]->Draw("PE, SAME");
   } else {
      s_data[0]->Draw("HIST");
      datamax<100 ? s_data[0]->SetMinimum(0.1) : s_data[0]->SetMinimum(1.);
      const double max = pow(10, 1+ceil(log10(datamax)));
      s_data[0]->SetMaximum(max);
   }
   h_sig[0][0]->Draw("HIST, E, SAME");
   h_sig[1][0]->Draw("HIST, E, SAME");
   if (!isSig) h_data[0]->Draw("PE, SAME");
   if (!isSig) {
      c3->cd(2);
      r_data->Draw("PE");
      r_data_jet->Draw("PE, SAME");
      r_data->SetMinimum(0.);
      r_data->SetMaximum(2.);
      TLegend * leg_r = new TLegend(0.25, 0.2, 0.875, 0.3);
      leg_r->SetBorderSize(0);
      leg_r->SetNColumns(2);
      leg_r->AddEntry(r_data, "mc+emb", "P");
      leg_r->AddEntry(r_data_jet, "mc+emb+jet", "P");
      leg_r->Draw();
   }
   c3->SaveAs("./plots/fullstudy."+TString(h->GetName())+".signal.pdf");*/

   TCanvas * c3 = new TCanvas("c3_"+TString(h->GetName()), "c3", 800, 800);

   TLegend * leg2 = new TLegend(0.25, 0.75, 0.875, 0.875);
   leg2->SetBorderSize(0);
   leg2->SetNColumns(3);
   for (int i = 0; i < nmc; ++i) leg2->AddEntry(h_mc[0][i][0], labels[i], "F");
   //leg2->AddEntry(h_BCoD, "multi-jet", "F");
   leg2->AddEntry(h_emb[1], "embedded", "F");
   leg2->AddEntry(h_sig[1][0], "#tau* 250", "L");
   //leg2->AddEntry(h_sig[1][3], "#tau* 625", "L");
   leg2->AddEntry(h_data[1], "observed", "P");

   TLegend * leg22 = (TLegend*)leg2->Clone();
   leg22->AddEntry(h_BCoD, "multi-jet", "F");

   TLegend * theleg[4] = {leg22, leg2, leg2, leg2};

   c3->Divide(2, 2);
   for (int i = 0; i < 4; ++i) {
      TPad * p = (TPad*)c3->cd(i+1);
      s_data[i]->Draw("HIST");
      h_sig[i][0]->Draw("HIST, E, SAME");
      //h_sig[i][3]->Draw("HIST, E, SAME");
      theleg[i]->Draw();
      p->SetLogy();
      if (isSig && i==0) continue;
      h_data[i]->Draw("PE, SAME");
   }

   c3->SaveAs("./plots/fullstudy."+TString(h->GetName())+".abcd.pdf");

   TCanvas * c5 = new TCanvas("c5", "c5", 400, 400);
   s_data[0]->Draw("HIST");
   h_sig[0][0]->Draw("HIST, E, SAME");
   //h_sig[0][3]->Draw("HIST, E, SAME");
   theleg[0]->Draw();
   c5->SetLogy();
   if (!isSig) h_data[0]->Draw("PE, SAME");
   c5->SaveAs("./plots/fullstudy."+TString(h->GetName())+".sigonly.pdf");

   TFile * fout = new TFile("./outputHists_2018/yields."+TString(h->GetName())+".root", "RECREATE");
   for (int i = 0; i < 4; ++i) {
      h_emb[i]->Write();
      if (!(isSig&&i==0)) h_data[i]->Write();
      for (int j = 0; j < nsig; ++j) {
         h_sig[i][j]->Write();
      }
      for (int j = 0; j < nmc; ++j) {
         for (int k = 0; k < 2; ++k) {
            h_mc[i][j][k]->Write();
         }
      }
   }
   h_BCoD->Write();
   h_CoD->Write();
   fout->Close();
}

void fullStudy()
{
   TCut baseline = "1>0";

   baseline = baseline && TCut("MuTauGamma_havePair>0");
   //baseline = baseline && TCut("MuMuGamma_havePair==0");
   baseline = baseline && TCut("Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=2)<2");
   baseline = baseline && TCut("MuTauGamma_trigger");
   baseline = baseline && TCut("(16&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx]) && Muon_pfIsoId[MuTauGamma_MuIdx]>=2");
   baseline = baseline && TCut("Tau_decayMode[MuTauGamma_TauIdx]!=5 && Tau_decayMode[MuTauGamma_TauIdx]!=6");
   //baseline = baseline && TCut("Tau_pt[MuTauGamma_TauIdx]>=30. && MuTauGamma_MuTauDeltaR>=0.5");
   
   //baseline = baseline && TCut("MuTauGamma_mt<40.");
   //baseline = baseline && TCut("MuTauGamma_haveTriplet==0 || (MuTauGamma_haveTriplet>0 && Photon_pt[MuTauGamma_PhotonIdx]<100.)");
   //baseline = baseline && TCut("JetProducer_nBJetT>0||MuTauGamma_MuTauMass<91.1876||(Muon_pfIsoId[MuTauGamma_MuIdx]<4 && Muon_pfIsoId[MuTauGamma_MuIdx]>=2)");

   baseline = baseline && TCut("Muon_pfIsoId[MuTauGamma_MuIdx]>=4");
   baseline = baseline && TCut("JetProducer_nBJetT==0");
   baseline = baseline && TCut("MuTauGamma_MuTauMass>=91.1876"); 
   baseline = baseline && TCut("MuTauGamma_haveTriplet>0 && Photon_pt[MuTauGamma_PhotonIdx]>=100.");

   baseline = baseline && TCut("Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter");

   //TH1D * h_unitbin = new TH1D("h_unitbin", ";the unit bin;events", 1,0.5, 1.5);
   //runPoint(h_unitbin, "1.", baseline, false);

   //TH1D * h_MuTauMass = new TH1D("h_MuTauMass", ";#mu+#tau_{h} visible mass [GeV];events / 10 GeV", 20., 0., 200.);
   //runPoint(h_MuTauMass, "MuTauGamma_MuTauMass", baseline, false);

  // TH1D * h_nBJetT = new TH1D("h_nBJetT", ";# of b-tagged jets;events / 1", 4, -0.5, 3.5);
  // runPoint(h_nBJetT, "JetProducer_nBJetT", baseline, false);

   //TH1D * h_mt = new TH1D("h_mt", ";m_{T} [GeV];events / 10 GeV", 10, 0., 100.);
   //runPoint(h_mt, "MuTauGamma_mt", baseline, false);

   //TH1D * h_nBJetM = new TH1D("h_nBJetM", ";# of b-tagged jets;events / 1", 4, -0.5, 3.5);
   //runPoint(h_nBJetM, "JetProducer_nBJetM", baseline, false);

   //TH1D * h_nJet = new TH1D("h_nJet", ";# of jets;events / 1", 10, -0.5, 9.5);
   //runPoint(h_nJet, "JetProducer_nJet", baseline, false);
   
   TH1D * h_MET = new TH1D("h_MET", ";MET [GeV];events / 75 GeV", 5, 0., 375.);
   runPoint(h_MET, "MET_pt", baseline, true);

   TH1D * h_METsig = new TH1D("h_METsig", ";MET significance;events / 1", 10, 0., 10.);
   runPoint(h_METsig, "MET_significance", baseline, true);

   //TH1D * h_npv = new TH1D("h_npv", ";PV_npvsGood;events / 2", 50, -0.5, 99.5);
   //runPoint(h_npv, "PV_npvsGood", baseline, false);

   /*
   TH1D * h_decayMode = new TH1D("h_decayMode", ";#tau_{h} decay mode;events / 1", 13, -0.5, 12.5);
   runPoint(h_decayMode, "Tau_decayMode[MuTauGamma_TauIdx]", baseline, false);*/

   //TH1D * h_photonpt = new TH1D("h_photonpt", ";photon p_{T} [GeV];events / 50 GeV", 10, 0., 500.);
   //runPoint(h_nJet, "Photon_pt[MuTauGamma_PhotonIdx]", baseline, true);

   //TH1D * h_photonpt_low = new TH1D("h_photonpt_low", ";photon p_{T} [GeV];events / 10 GeV;", 5, 0., 50.);
   //runPoint(h_photonpt_low, "Photon_pt[MuTauGamma_PhotonIdx]", baseline, true);

 //   TH1D * h_minmass = new TH1D("h_minmass_s", ";min collinear mass [GeV];events / 200 GeV", 5, 0., 1000.);
   // runPoint(h_minmass, "TMath::Min(MuTauGamma_MuGammaCollinearMass, MuTauGamma_TauGammaCollinearMass)", baseline, true);
      
  // TH1D * h_bin0 = new TH1D("h_bin0_s", ";mass bin;events / bin", 5, -0.5, 4.5);
//   runPoint(h_bin0, "abcdRegion[0]", baseline, true);

 //  TH1D * h_bin3 = new TH1D("h_bin3_v", ";mass bin;events / bin", 5, -0.5, 4.5);
   //runPoint(h_bin3, "abcdRegion[3]", baseline, true);

   // TH1D * maxmass = new TH1D("maxmass_s", ";max collinear mass [GeV];events / 400 GeV", 5, 0., 2000.);
 //   runPoint(maxmass, "TMath::Max(MuTauGamma_MuGammaCollinearMass, MuTauGamma_TauGammaCollinearMass)", baseline, true);
}

