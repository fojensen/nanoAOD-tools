#include <iostream>
#include <TCut.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include "addOverflow.h"
#include <TROOT.h>

void runPoint(const TString intag, const TString weights, const TCut extraCuts, const TString outtag, const bool isEmb=false)
{
   std::cout << outtag << std::endl;

   TCut baseline = "MuTauGamma_havePair>0 && MuTauGamma_trigger";
   //const TCut mumuVeto = "Sum$(Muon_pt>=10. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=2)<2";
   const TCut mumuVeto = "1>0";
   const TCut eVeto = "(Sum$(Electron_pt>=20. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0)";
   //const TCut WVeto = "MuTauGamma_mt<40.";
   const TCut W = "1>0";
   //const TCut topVeto = "JetProducer_nBJetT==0";
   const TCut topVeto = "1>0";
   //const TCut Z = "MuTauGamma_MuTauMass>=91.1876";
   const TCut Z = "1>0";
   //const TCut photonVeto = "MuTauGamma_haveTriplet==0 || (MuTauGamma_haveTriplet>0 && Photon_pt[MuTauGamma_PhotonIdx]<50.)";
   const TCut photon = "MuTauGamma_haveTriplet==1";
   //const TCut photon = "1>0";
   baseline = baseline && eVeto && mumuVeto && W && Z && topVeto && photon && extraCuts;

   TFile * fin = TFile::Open("./outputData_2018/"+intag+".root");
   TTree * tin = (TTree*)fin->Get("Events");
   std::cout << "   entries in input tree: " << tin->GetEntries() << std::endl;
   TTree * t;
   TTree * t_Embeddedsf;
   if (isEmb) {
      t = tin;
      TFile * f_Embeddedsf = TFile::Open("./Embedded_2018/Embedded_2018_0_-1.root");
      t_Embeddedsf = (TTree*)f_Embeddedsf->Get("mt_nominal/ntuple");
      t->AddFriend(t_Embeddedsf);
   } else {
      gROOT->cd();
      std::cout << "   now skim the tree" << std::endl;
      t = (TTree*)tin->CopyTree(baseline);
   }
   std::cout << "   entries in tree: " << t->GetEntries() << std::endl;

   const TCut regionA = "MuTauGamma_qq==-1 &&  (64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionB = "MuTauGamma_qq==+1 &&  (64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionC = "MuTauGamma_qq==-1 && !(64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   const TCut regionD = "MuTauGamma_qq==+1 && !(64&Tau_idDeepTau2017v2p1VSjet[MuTauGamma_TauIdx])";
   TCut cuts[4] = {baseline && regionA, baseline && regionB, baseline && regionC, baseline && regionD};

   //const TString titles[4] = {"A", "B", "C", "D"};
   const TString titles[4] = {"A: OS ISO", "B: SS ISO", "C: OS !ISO", "D: SS !ISO"};

   TFile * fout = new TFile("./outputHists_2018/"+outtag+".root", "RECREATE");
   TH1D *h_unit[4], *h_mt[4], *h_njets[4], *h_nbjetsM[4], *h_nbjetsT[4], *h_npv[4], *h_decayMode[4];
   TH1D *h_vispt[4], *h_vismass[4], *h_mutaudr[4];
   TH1D *h_minmass[4], *h_maxmass[4], *h_met[4];
   TH1D *h_musum[4], *h_esum[4];
   TH1D *h_photonpt[4];

   for (int i = 0; i < 4; ++i) {
      if (intag=="SingleMuon" && i==0) continue;
      std::cout << "   " << titles[i] << std::endl;
      const TString tag = TString::Itoa(i, 10);
      char buffer[3000];
      sprintf(buffer, "%s * ( %s )", weights.Data(), TString(cuts[i]).Data());
      //std::cout << buffer << std::endl;

      h_unit[i] = new TH1D("h_unit_"+tag, ";the unit bin;events", 1, 0.5, 1.5);
      const int n = t->Project(h_unit[i]->GetName(), "1.", buffer);
      std::cout << "      # of mc events: " << n << std::endl;
      std::cout << "      expected yield: " << h_unit[i]->Integral() << std::endl;

      h_vismass[i] = new TH1D("h_vismass_"+tag, titles[i]+";#mu+#tau_{h} visible mass [GeV];events / 10 GeV", 20, 0., 200.);
      t->Project(h_vismass[i]->GetName(), "MuTauGamma_MuTauMass", buffer);
      addOverflow(h_vismass[i]);

      h_vispt[i] = new TH1D("h_vispt_"+tag, titles[i]+";#mu+#tau_{h} p_{T} [GeV];events / 25 GeV", 12, 0., 300.);
      t->Project(h_vispt[i]->GetName(), "MuTauGamma_MuTauPt", buffer);
      addOverflow(h_vispt[i]);

      h_decayMode[i] = new TH1D("h_decayMode_"+tag, titles[i]+";#tau_{h} decay mode;events / bin", 12, -0.5, 11.5);
      t->Project(h_decayMode[i]->GetName(), "Tau_decayMode[MuTauGamma_TauIdx]", buffer);
      addOverflow(h_decayMode[i]);

      h_njets[i] = new TH1D("h_njets_"+tag, titles[i]+";# of jets;events / 1", 8, -0.5, 7.5);
      t->Project(h_njets[i]->GetName(), "JetProducer_nJet", buffer);
      addOverflow(h_njets[i]);

      h_nbjetsM[i] = new TH1D("h_nbjetsM_"+tag, titles[i]+";# of b-tagged jets (medium);events / 1", 5, -0.5, 4.5);
      t->Project(h_nbjetsM[i]->GetName(), "JetProducer_nBJetM", buffer);
      addOverflow(h_nbjetsM[i]);

      h_nbjetsT[i] = new TH1D("h_nbjetsT_"+tag, titles[i]+";# of b-tagged jets (tight);events / 1", 5, -0.5, 4.5);
      t->Project(h_nbjetsT[i]->GetName(), "JetProducer_nBJetT", buffer);
      addOverflow(h_nbjetsT[i]); 

      h_npv[i] = new TH1D("h_npv_"+tag, titles[i]+";PV_npvsGood;events / 5", 20, -0.5, 99.5);
      t->Project(h_npv[i]->GetName(), "PV_npvsGood", buffer);
      addOverflow(h_npv[i]);

      h_mt[i] = new TH1D("h_mt_"+tag, ";#mu+MET m_{T} [GeV];events / 25 GeV", 12, 0., 300.);
      t->Project(h_mt[i]->GetName(), "MuTauGamma_mt", buffer);
      addOverflow(h_mt[i]);

      h_met[i] = new TH1D("h_met_"+tag, ";MET [GeV];events / 25 GeV", 12, 0., 300.);
      t->Project(h_met[i]->GetName(), "MET_pt", buffer);
      addOverflow(h_met[i]);

      //const double minx[11] = {0., 1., 100., 200., 300., 400., 500., 600., 700., 800., 1000.};
      h_minmass[i] = new TH1D("h_minmass_"+tag, titles[i]+";min collinear mass [GeV];events / 200 GeV", 5, 0., 1000.);
      t->Project(h_minmass[i]->GetName(), "TMath::Min(MuTauGamma_MuGammaCollinearMass, MuTauGamma_TauGammaCollinearMass)", buffer);
      addOverflow(h_minmass[i]);

      //const double maxx[11] = {0., 1., 200., 400., 600., 800., 1000., 1200., 1400., 1600., 1000.};
      h_maxmass[i] = new TH1D("h_maxmass_"+tag, titles[i]+";max collinear mass [GeV];events / 200 GeV", 10, 0., 2000.);
      t->Project(h_maxmass[i]->GetName(), "TMath::Max(MuTauGamma_MuGammaCollinearMass, MuTauGamma_TauGammaCollinearMass)", buffer);
      addOverflow(h_maxmass[i]);

      h_mutaudr[i] = new TH1D("h_mutaudr_"+tag, titles[i]+";##DeltaR(#mu, #tau_{h});events / 0.2", 20, 0., 4.); 
      t->Project(h_mutaudr[i]->GetName(), "MuTauGamma_MuTauDeltaR", buffer);
      addOverflow(h_mutaudr[i]);

      h_musum[i] = new TH1D("h_musum_"+tag, titles[i]+";;", 4, -0.5, 3.5);
      t->Project(h_musum[i]->GetName(), "Sum$(Muon_genPartFlav==1)", buffer);
      addOverflow(h_musum[i]);

      h_esum[i] = new TH1D("h_esum_"+tag, titles[i]+";;", 4, -0.5, 3.5);
      t->Project(h_esum[i]->GetName(), "Sum$(Electron_genPartFlav==1)", buffer);
      addOverflow(h_esum[i]);

      //h_photonpt[i] = new TH1D("h_photonpt_"+tag, titles[i]+";photon p_{T} [GeV];events / 100 GeV", 10, 0., 1000.);
      //t->Project(h_photonpt[i]->GetName(), "Photon_pt[MuTauGamma_PhotonIdx]", buffer);
      //addOverflow(h_photonpt[i]);
   }
 

   fout->Write();
   fout->Close();
}

void makeHists()
{
   const TString sf_mc = "59725.419 * xsWeight * puWeight * MuTauGamma_TauSFjet * MuTauGamma_TauSFmuo * MuTauGamma_TauSFele * MuTauGamma_MuSFId * MuTauGamma_MuSFIso * MuTauGamma_MuSFTrigger";
   const TCut cut_sig = "Sum$(Tau_genPartFlav==5)==1 && Sum$(Muon_genPartFlav==15)==1";
 /*  runPoint("TTTo2L2Nu", sf_mc, cut_sig, "TTTo2L2Nu_emb");                       runPoint("TTTo2L2Nu", sf_mc, !cut_sig, "TTTo2L2Nu_bkg");
   runPoint("TTToSemiLeptonic", sf_mc, cut_sig, "TTToSemiLeptonic_emb");         runPoint("TTToSemiLeptonic", sf_mc, !cut_sig, "TTToSemiLeptonic_bkg");
   runPoint("ST_tW", sf_mc, cut_sig, "ST_tW_emb");                               runPoint("ST_tW", sf_mc, !cut_sig, "ST_tW_bkg");
   runPoint("DYJetsToLL_M-50", sf_mc, cut_sig, "DYJetsToLL_M-50_emb");           runPoint("DYJetsToLL_M-50", sf_mc, !cut_sig, "DYJetsToLL_M-50_bkg");
   runPoint("DYJetsToLL_M-10to50", sf_mc, cut_sig, "DYJetsToLL_M-10to50_emb");   runPoint("DYJetsToLL_M-10to50", sf_mc, !cut_sig, "DYJetsToLL_M-10to50_bkg");
   runPoint("EWKZ2Jets_ZToLL_M-50", sf_mc, cut_sig, "EWKZ2Jets_ZToLL_M-50_emb"); runPoint("EWKZ2Jets_ZToLL_M-50", sf_mc, !cut_sig, "EWKZ2Jets_ZToLL_M-50_bkg");
   runPoint("WW", sf_mc, cut_sig, "WW_emb");                                     runPoint("WW", sf_mc, !cut_sig, "WW_bkg");
   runPoint("WZ", sf_mc, cut_sig, "WZ_emb");                                     runPoint("WZ", sf_mc, !cut_sig, "WZ_bkg");
   runPoint("ZZ", sf_mc, cut_sig, "ZZ_emb");                                     runPoint("ZZ", sf_mc, !cut_sig, "ZZ_bkg");

   runPoint("WGToLNuG", sf_mc, cut_sig, "WGToLNuG_emb");  runPoint("WGToLNuG", sf_mc, !cut_sig, "WGToLNuG_bkg");
   runPoint("QCD_Pt-20toInf_MuEnrichedPt15", sf_mc, cut_sig, "QCD_Pt-20toInf_MuEnrichedPt15_emb");  runPoint("QCD_Pt-20toInf_MuEnrichedPt15", sf_mc, !cut_sig, "QCD_Pt-20toInf_MuEnrichedPt15_bkg");*/

   runPoint("Taustar_m250", sf_mc, "1>0", "Taustar_m250");
   runPoint("Taustar_m375", sf_mc, "1>0", "Taustar_m375");
   runPoint("Taustar_m500", sf_mc, "1>0", "Taustar_m500");
   runPoint("Taustar_m625", sf_mc, "1>0", "Taustar_m625");
   runPoint("Taustar_m750", sf_mc, "1>0", "Taustar_m750");
/*
   runPoint("SingleMuon", "1.", "1>0", "SingleMuon");

   const TString sf_emb = "genWeight * m_sel_trg_ratio * m_sel_idEmb_ratio_1 * m_sel_idEmb_ratio_2 * m_iso_binned_embed_kit_ratio * m_id_embed_kit_ratio * m_trg24_27_embed_kit_ratio * MuTauGamma_trkEff * MuTauGamma_TauSFjet";
   runPoint("Embedded", sf_emb, "1>0", "Embedded", true);*/
}

