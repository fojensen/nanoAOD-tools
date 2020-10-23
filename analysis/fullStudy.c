#include <THStack.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TLegend.h>
#include <iostream>

void fullStudy()
{
   // *** INCLUSIVE *** //
   std::cout << "// *** INCLUSIVE *** //" << std::endl;

   //TH1D * h = new TH1D("h", ";#mu+#tau_{h} visible mass [GeV];events / 20 GeV", 10, 0., 200.);
   //const TString var = "MuTauGamma_MuTauMass";

   //TH1D * h = new TH1D("h", ";# of b-tagged jets;events / 1", 4, -0.5, 3.5);
   //const TString var = "JetProducer_nBJetT";

   TH1D * h = new TH1D("h", ";m_{T} [GeV];events / 10 GeV", 10, 0., 100.);
   const TString var = "MuTauGamma_mt";

   h->SetStats(0);

   TCut baseline = "MuTauGamma_havePair>0 && MuTauGamma_trigger && Muon_pfIsoId[MuTauGamma_MuIdx]>=4 && (16&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   //const TCut mumuVeto = "MuMuGamma_havePair==0";
   //const TCut Wveto = "MuTauGamma_mt<40.";
   const TCut Wveto = "1>0";
   const TCut mumuVeto = "Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_pfIsoId>=2 && Muon_mediumId)<2";
   const TCut photonVeto = "MuTauGamma_haveTriplet==0 || (MuTauGamma_haveTriplet>0 && Photon_pt[MuTauGamma_PhotonIdx]<50.)";
   const TCut filters = "Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter";
   baseline = baseline && mumuVeto && photonVeto && filters && Wveto;

   const TCut regionA = "MuTauGamma_qq==-1 &&  (64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionB = "MuTauGamma_qq==+1 &&  (64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionC = "MuTauGamma_qq==-1 && !(64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionD = "MuTauGamma_qq==+1 && !(64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionCuts[4] = {baseline&&regionA, baseline&&regionB, baseline&&regionC, baseline&&regionD};

   // *** FILL MC HISTOGRAMS *** //
   std::cout << "// *** FILL MC HISTOGRAMS *** //" << std::endl;

   const int nmc = 9;
   TH1D *h_mc[nmc][4][2];
   TH1D *h_mc_sum[4][2];
   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 2; ++j) {
         char hname[100];
         sprintf(hname, "h_mc_sum_%d_%d", i, j);
         h_mc_sum[i][j] = (TH1D*)h->Clone(hname);
      }
   }
   const TCut genCuts[2] = {"Sum$(Tau_genPartFlav==5)==1 && Sum$(Muon_genPartFlav==15)==1", "!(Sum$(Tau_genPartFlav==5)==1 && Sum$(Muon_genPartFlav==15)==1)"};
   TString mcWeights[4];
   mcWeights[0] = "59725.419 * xsWeight * puWeight * MuTauGamma_TauSFmuo * MuTauGamma_TauSFele * MuTauGamma_MuSFId * MuTauGamma_MuSFIso[1] * MuTauGamma_MuSFTrigger * MuTauGamma_TauSFjet[6]";
   mcWeights[1] = "59725.419 * xsWeight * puWeight * MuTauGamma_TauSFmuo * MuTauGamma_TauSFele * MuTauGamma_MuSFId * MuTauGamma_MuSFIso[1] * MuTauGamma_MuSFTrigger * MuTauGamma_TauSFjet[6]";
   mcWeights[2] = "59725.419 * xsWeight * puWeight * MuTauGamma_TauSFmuo * MuTauGamma_TauSFele * MuTauGamma_MuSFId * MuTauGamma_MuSFIso[1] * MuTauGamma_MuSFTrigger";
   mcWeights[3] = "59725.419 * xsWeight * puWeight * MuTauGamma_TauSFmuo * MuTauGamma_TauSFele * MuTauGamma_MuSFId * MuTauGamma_MuSFIso[1] * MuTauGamma_MuSFTrigger";

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
      std::cout << mctags[i] << std::endl;
      char fname[100];
      sprintf(fname, "./outputData_2018/%s.root", mctags[i].Data());
      TFile * f = TFile::Open(fname);
      TTree * t = (TTree*)f->Get("Events");
      for (int j = 0; j < 4; ++j) {
         for (int k = 0; k < 2; ++k) {
            char hname[100];
            sprintf(hname, "h_%s_%d_%d", mctags[i].Data(), j, k);
            h_mc[i][j][k] = (TH1D*)h->Clone(hname);
            char cutString[1000];
            sprintf(cutString, "%s * ( %s && %s )", mcWeights[j].Data(), TString(genCuts[k]).Data(), TString(regionCuts[j]).Data());
            t->Project(hname, var, cutString);
            h_mc[i][j][k]->SetFillColor(col[i]);
            h_mc_sum[j][k]->Add(h_mc[i][j][k]);
         }
      }
   }

   // *** FILL SIGNAL HISTOGRAMS *** //
   const TString sigtags[2] = {"Taustar_m250", "Taustar_m500"};
   TH1D * h_sig[2][4];
   const int col_sig[2] = {40, 45};
   for (int i = 0; i < 2; ++i) {
      char fname[100];
      sprintf(fname, "./outputData_2018/%s.root", sigtags[i].Data());
      TFile * f = TFile::Open(fname);
      TTree * t = (TTree*)f->Get("Events");
      for (int j = 0; j < 4; ++j) {
         char hname[100];
         sprintf(hname, "h_sig_%d_%d", i, j);
         h_sig[i][j] = (TH1D*)h->Clone(hname);
         h_sig[i][j]->SetLineColor(col_sig[i]);
         h_sig[i][j]->SetLineWidth(2);
         char cuts[1000];
         sprintf(cuts, "%s * ( %s )", mcWeights[j].Data(), TString(regionCuts[j]).Data());
         t->Project(h_sig[i][j]->GetName(), var, cuts);
      }
   }

   // *** FILL EMBEDDED HISTOGRAMS *** //
   std::cout << "// *** FILL EMBEDDED HISTOGRAMS *** //" << std::endl;
   TH1D *h_emb[4];
   TString embWeights[4];
   embWeights[0] = "genWeight * m_sel_trg_ratio * m_sel_idEmb_ratio_1 * m_sel_idEmb_ratio_2 * m_iso_binned_embed_kit_ratio * m_id_embed_kit_ratio * m_trg24_27_embed_kit_ratio * MuTauGamma_trkEff * MuTauGamma_TauSFjet[6]";
   embWeights[1] = "genWeight * m_sel_trg_ratio * m_sel_idEmb_ratio_1 * m_sel_idEmb_ratio_2 * m_iso_binned_embed_kit_ratio * m_id_embed_kit_ratio * m_trg24_27_embed_kit_ratio * MuTauGamma_trkEff * MuTauGamma_TauSFjet[6]";
   embWeights[2] = "genWeight * m_sel_trg_ratio * m_sel_idEmb_ratio_1 * m_sel_idEmb_ratio_2 * m_iso_binned_embed_kit_ratio * m_id_embed_kit_ratio * m_trg24_27_embed_kit_ratio * MuTauGamma_trkEff";
   embWeights[3] = "genWeight * m_sel_trg_ratio * m_sel_idEmb_ratio_1 * m_sel_idEmb_ratio_2 * m_iso_binned_embed_kit_ratio * m_id_embed_kit_ratio * m_trg24_27_embed_kit_ratio * MuTauGamma_trkEff";

   TFile * f_emb = TFile::Open("./outputData_2018/Embedded.root");
   TTree * t_emb = (TTree*)f_emb->Get("Events");
   TFile * f_emb_sf = TFile::Open("./Embedded_2018/Embedded_2018_0_-1.root");
   TTree * t_emb_sf = (TTree*)f_emb_sf->Get("mt_nominal/ntuple");
   t_emb->AddFriend(t_emb_sf);
   double embmax = 0.;
   for (int i = 0; i < 4; ++i) {
      h_emb[i] = (TH1D*)h->Clone("h_emb_"+TString::Itoa(i, 10));
      h_emb[i]->SetMarkerStyle(20);
      h_emb[i]->SetFillColor(7);
      char cutString[1000];
      sprintf(cutString, "%s * ( %s )", embWeights[i].Data(), TString(regionCuts[i]).Data()); 
      t_emb->Project(h_emb[i]->GetName(), var, cutString);
      const double y = h_emb[i]->Integral();
      if (y>embmax) embmax = y;
   }

   // *** FILL DATA HISTOGRAMS *** //
   std::cout << "// *** FILL DATA HISTOGRAMS *** //" << std::endl;
   TH1D * h_data[4];
   TFile * f_data = TFile::Open("./outputData_2018/SingleMuon.root");
   TTree * t_data = (TTree*)f_data->Get("Events");
   double datamax = 0.;
   for (int i = 0; i < 4; ++i) {
      h_data[i] = (TH1D*)h->Clone("h_data_"+TString::Itoa(i, 10));
      h_data[i]->SetMarkerStyle(20);
      const double y = t_data->Project(h_data[i]->GetName(), var, TString(regionCuts[i]).Data());
      if (y>datamax) datamax = y;
   }

   // *** MC COMPOSITION OF EMBEDDED *** //
   std::cout << "// *** MC COMPOSITION OF EMBEDDED *** //" << std::endl;
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
   }
   for (int i = 0; i < nmc; ++i) {
      for (int j = 0; j < 4; ++j) {
         s_emb[j]->Add(h_mc[i][j][0]);
      }
   }

   TLegend * leg = new TLegend(0.25, 0.7, 0.875, 0.875);
   leg->SetBorderSize(0);
   leg->SetNColumns(3);
   for (int i = 0; i < nmc; ++i) leg->AddEntry(h_mc[i][0][0], labels[i], "F");
   leg->AddEntry(h_emb[0], "embedded", "P");

   TCanvas * c_emb = new TCanvas("c_emb", "", 1600, 800);
   c_emb->Divide(4, 2);
   for (int i = 0; i < 4; ++i) {
      TPad * p = (TPad*)c_emb->cd(i+1);
      h_emb[i]->Draw("PE");
      s_emb[i]->Draw("HIST, SAME");
      leg->Draw();
      embmax<100 ? h_emb[i]->SetMinimum(0.1) : h_emb[i]->SetMinimum(1.);
      const double max = pow(10, ceil(log10(embmax)));
      h_emb[i]->SetMaximum(max);
      p->SetLogy();
   }

   for (int i = 0; i < 4; ++i) {
      TPad * p = (TPad*)c_emb->cd(i+5);
      r_emb[i]->Draw("PE");
      r_emb[i]->SetMinimum(0.);
      r_emb[i]->SetMaximum(2.);
   }

   // *** EMBEDDED APPLIED TO DATA *** ///

   THStack * s_data[4];
   TH1D * h_mcemb_sum[4];
   for (int i = 0; i < 4; ++i) {
      s_data[i] = new THStack();
      for (int j = 0; j < nmc; ++j) {
         s_data[i]->Add(h_mc[j][i][1]);
      }
      s_data[i]->Add(h_emb[i]);
      h_mcemb_sum[i] = (TH1D*)h_mc_sum[i][1]->Clone("h_mcemb_sum_"+TString::Itoa(i, 10));
      h_mcemb_sum[i]->Add(h_emb[i]);
   }
 
   TH1D * r_data[4];
   for (int i = 0; i < 4; ++i) {
      r_data[i] = (TH1D*)h_data[i]->Clone("r_data_"+TString::Itoa(i, 10));
      r_data[i]->Divide(h_mcemb_sum[i]);
      r_data[i]->GetYaxis()->SetTitle("data / expected bkg");
   }

   TCanvas * c_data = new TCanvas("c_data", "", 1600, 800);
   c_data->Divide(4, 2);

   TLegend * leg2 = new TLegend(0.25, 0.7, 0.875, 0.875);
   leg2->SetBorderSize(0);
   leg2->SetNColumns(3);
   for (int i = 0; i < nmc; ++i) leg2->AddEntry(h_mc[i][0][0], labels[i], "F");
   leg2->AddEntry(h_emb[0], "embedded", "F");
   leg2->AddEntry(h_sig[0][0], "#tau* 250", "L");
   leg2->AddEntry(h_sig[1][0], "#tau* 500", "L");

   for (int i = 0; i < 4; ++i) {
      TPad * p = (TPad*)c_data->cd(i+1);
      h_data[i]->Draw("PE");
      s_data[i]->Draw("HIST, SAME");
      h_sig[0][i]->Draw("HIST, E, SAME");
      h_sig[1][i]->Draw("HIST, E, SAME");
      leg2->Draw();

      datamax<100 ? h_data[i]->SetMinimum(0.1) : h_data[i]->SetMinimum(1.);
      const double max = pow(10, ceil(log10(datamax)));
      h_data[i]->SetMaximum(max);
      p->SetLogy();
   }
   for (int i = 0; i < 4; ++i) {
      TPad * p = (TPad*)c_data->cd(i+5);
      r_data[i]->Draw("PE");
      r_data[i]->SetMinimum(0.);
      r_data[i]->SetMaximum(2.);
   }
}

