import datetime

now = datetime.datetime.now()
print ("Start date and time : ")
print (now.strftime("%Y-%m-%d %H:%M:%S"))

#!/usr/bin/env python
import os
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 

#this takes care of converting the input files from CRAB
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles,runsAndLumis

isMC = True
#isMC = False

#testfile = [
#    "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/100000/C09BEBE1-F278-D64B-B631-A6D2E4918719.root"
#    "root://cmseos.fnal.gov///store/user/fojensen/EmbeddedSamples_08052020/Embedded_2018A.root"
#    "root://cmseos.fnal.gov///store/user/fojensen/EmbeddedSamples_08052020/Embedded_2018B.root"
#    "root://cmseos.fnal.gov///store/user/fojensen/EmbeddedSamples_08052020/Embedded_2018C.root"
#    "root://cmseos.fnal.gov///store/user/fojensen/EmbeddedSamples_08052020/Embedded_2018D.root"
#    "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1/60000/76356B6A-C1A8-714B-8793-F7BDA4C38DDE.root"
#    "root://cmseos.fnal.gov//store/user/fojensen/EmbeddedSamples_08052020/Taustar_m2000.root",
#    "/uscms_data/d3/twelton/WorkingArea/CMSSW_10_2_16/src/NanoAOD/Taustar_TauG_L10000_m1000_13TeV_pythia8_NanoAOD.root",
#    "root://cmsxrootd.fnal.gov///store/mc/RunIISummer16NanoAODv7/Taustar_TauG_L10000_m2000_13TeV_pythia8/NANOAODSIM/PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/30000/5DC20A25-E33D-024E-9BE9-38A0AD7EE9A8.root"
 #   "root://cmseos.fnal.gov//store/user/twelton/Taustar_TauG_L10000_m250_13TeV_pythia8_NanoAOD/Taustar_TauG_L10000_m250_13TeV_pythia8_GEN-SIM/Taustar_TauG_L10000_m250_13TeV_pythia8_NanoAOD/200324_011356/0000/test_1.root"
#]
#print testfile

cut_Mu = "(Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=2)>0)"
cut_Trigger = "(HLT_IsoMu24||HLT_IsoMu27||HLT_Mu50||HLT_OldMu100||HLT_TkMu100||HLT_IsoMu20_eta2p1_LooseChargedIsoPFTauHPS27_eta2p1_CrossL1||HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1)"
cut_Electron = "(Sum$(Electron_pt>=32. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP80)==0)"
cut_Photon = "(Sum$(Photon_pt>=32. && TMath::Abs(Photon_eta)<2.5 && Photon_mvaID_WP90 && Photon_electronVeto)>0)"
cut_Tau = "(Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && (8&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (Tau_decayMode!=5&&Tau_decayMode!=6))>0)"
cut_Flag = "(Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter)"
cut_ = cut_Mu + " && " + cut_Trigger + " && " + cut_Electron + " && " + cut_Photon + " && " + cut_Tau + " && " + cut_Flag
#cut_ = "1>0"
print cut_

from PhysicsTools.NanoAODTools.postprocessing.examples.MuMuGammaProducer import MuMuGammaProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.MuTauGammaProducer import MuTauGammaProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.JetProducer import JetProducerConstr
modules_ = [MuMuGammaProducerConstr(isMC), MuTauGammaProducerConstr(isMC), JetProducerConstr()]

if isMC:
    from PhysicsTools.NanoAODTools.postprocessing.modules.common.puWeightProducer import puWeight_2018
    modules_.append(puWeight_2018())
    #from PhysicsTools.NanoAODTools.postprocessing.modules.btv.btagSFProducer import *
    #modules_.append(btagSFProducer("2018", "deepcsv"))

p=PostProcessor(
    outputDir = "./",
    inputFiles = inputFiles(),
    #inputFiles = testfile,
    cut = cut_,
    modules = modules_,
    provenance = True,
    fwkJobReport = True,
    #maxEntries = 10000,
    #haddFileName = "Embedded_2018D.root",
    #jsonInput = runsAndLumis(),
    #jsonInput = "Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt",
    #outputbranchsel = "keep_and_drop.txt"
)
p.run()

then = datetime.datetime.now()
print ("Finish date and time : ")
print (then.strftime("%Y-%m-%d %H:%M:%S"))

