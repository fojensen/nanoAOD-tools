import datetime
then = datetime.datetime.now()
print ("Start date and time: ", then.strftime("%Y-%m-%d %H:%M:%S"))

#!/usr/bin/env python
import os
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 

#this takes care of converting the input files from CRAB
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles#,runsAndLumis

#testfile = [
    #"root://cmsxrootd.fnal.gov///store/data/Run2018D/SingleMuon/NANOAOD/Nano25Oct2019-v1/100000/76BEBA77-9DDB-8144-A183-5842729F006D.root"
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/C00024AD-3D0D-DE45-949F-E56A81BDDCA7.root" # small DY file
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/109AFD23-2019-E447-8070-8FA4B9203018.root" # large DY file
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/9E6A9BA6-C187-0F4E-8A45-01B2F2F33E11.root", #small W file
    #"root://cmsxrootd.fnal.gov///store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root" #large W file
    #"root://cmsxrootd.fnal.gov//store/user/fojensen/EmbeddedSamples_08052020/Embedded_2018D.root"
#]
#print testfile

cut_TT = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (1&Tau_idDeepTau2017v2p1VSmu) && (1&Tau_idDeepTau2017v2p1VSe))>=2"
cut_ET = "Sum$(TMath::Abs(Electron_eta)<2.5  && Electron_pt>=12. && Electron_mvaFall17V2Iso_WPL)>0 && Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (1&Tau_idDeepTau2017v2p1VSmu) && (1&Tau_idDeepTau2017v2p1VSe))>0"
cut_MT = "Sum$(TMath::Abs(Muon_eta)<2.4 && Muon_pt>=8. && Muon_looseId && Muon_pfIsoId>=1)>0 && Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (1&Tau_idDeepTau2017v2p1VSmu) && (1&Tau_idDeepTau2017v2p1VSe))>0"
#cut_EM = "Sum$(TMath::Abs(Electron_eta)<2.5 && Electron_pt>=12. && Electron_mvaFall17V2Iso_WPL)>0 && Sum$(TMath::Abs(Muon_eta)<2.4 && Muon_pt>=8. && Muon_looseId && Muon_pfIsoId>=1)>0"
#https://twiki.cern.ch/CMS/MissingETOptionalFiltersRun2
cut_Flag = "(Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter)"

cut_ = "("+ cut_TT + " || " + cut_ET + " || " + cut_MT + ") && " + cut_Flag
print cut_

from PhysicsTools.NanoAODTools.postprocessing.examples.MuTauProducer import MuTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ZProducer import ZProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.JetProducer import JetProducerConstr
modules_ = [MuTauProducerConstr(), ZProducerConstr(), JetProducerConstr()]

#isMC = True
#if isMC:
    #from PhysicsTools.NanoAODTools.postprocessing.modules.common.puWeightProducer import puWeight_2018
    #modules_.append(puWeight_2018())

p=PostProcessor(
    outputDir = "./",
    inputFiles = inputFiles(),
    #inputFiles = testfile,
    cut = cut_,
    modules = modules_,
    #maxEntries = 100000,
    provenance = True,
    fwkJobReport = True,
    #jsonInput = runsAndLumis(),
    outputbranchsel = "keep_and_drop.txt"
)
p.run()

now = datetime.datetime.now()
print ("Finish date and time: ", now.strftime("%Y-%m-%d %H:%M:%S"))
duration = now - then
print ("Total seconds elapsed: ", duration.total_seconds())

