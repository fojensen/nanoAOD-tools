import datetime
now = datetime.datetime.now()
print ("Start date and time : ")
print (now.strftime("%Y-%m-%d %H:%M:%S"))

#!/usr/bin/env python
import os
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 

#this takes care of converting the input files from CRAB
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles,runsAndLumis

testfile = [
    "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/E78C9017-BB6E-FE48-BA37-E059AEA79CD3.root"
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/250000/8969BAAF-2D11-7449-A180-97850997CD0A.root",
#    "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root" 
    #"file:E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root"
]
print testfile

cut_Mu = "(Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_tightId && Muon_pfIsoId>=6)>0)"
cut_Trigger = "(HLT_IsoMu24||HLT_IsoMu27)"
cut_Tau = "(Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && (8&Tau_idDeepTau2017v2p1VSmu) && (128&Tau_idDeepTau2017v2p1VSe) && !(Tau_decayMode==5||Tau_decayMode==6))>0)"
cut_Electron = "(Sum$(Electron_pt>=20. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V1Iso_WPL)==0)"
cut_Flag = "(Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter)"
cut_ = cut_Mu + " && " + cut_Trigger + " && " + cut_Tau + " && " + cut_Electron + " && " + cut_Flag
print cut_

from PhysicsTools.NanoAODTools.postprocessing.examples.MuTauProducer import MuTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.MuMuProducer import MuMuProducerConstr
modules_ = [MuTauProducerConstr(), MuMuProducerConstr()]

isMC = True
if isMC:
   from PhysicsTools.NanoAODTools.postprocessing.modules.common.puWeightProducer import puWeight_2018
   modules_.append(puWeight_2018())

p=PostProcessor(
    outputDir = "./",
#    inputFiles = inputFiles(),
    inputFiles = testfile,
    cut = cut_,
    modules = modules_,
    maxEntries = 100000,
    provenance = True,
    fwkJobReport = True,
    #haddFileName = "DYJetsToLL_M-50.root",
    jsonInput = runsAndLumis(),
    outputbranchsel = "keep_and_drop.txt"
)
p.run()

then = datetime.datetime.now()
print ("Finish date and time : ")
print (then.strftime("%Y-%m-%d %H:%M:%S"))

