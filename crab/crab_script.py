import sys
print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)

import datetime
now = datetime.datetime.now()
print ("Start date and time : ")
print (now.strftime("%Y-%m-%d %H:%M:%S"))

#!/usr/bin/env python
import os
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 

year='2018'
isMC = True
isEmb = False

if isMC and isEmb:
    print("you cant have it both ways")
    isMC = False
    isEmb = False

#this takes care of converting the input files from CRAB
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles
if not isMC and not isEmb:
   from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import runsAndLumis

#f = open("../analysis/filelists/DYJetsToLL_M-50.list", "r")
#content = f.read()
#content_list = content.splitlines()
#f.close()
#mystring = "root://cmsxrootd.fnal.gov//"
#testfile = [mystring+s for s in content_list]
#print testfile

testfile = [
    #"file:7FEC7B94-611C-364A-9A12-B9BD43C01EC3.root"
    #"root://cmsxrootd.fnal.gov///store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m250_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/7FEC7B94-611C-364A-9A12-B9BD43C01EC3.root"
    #"root://131.225.204.161:1094//eos/uscms/store/user/fojensen/EmbeddedSamples_26052020/Embedded_2018A.root"
    #"root://131.225.204.161:1094//eos/uscms/store/user/fojensen/EmbeddedSamples_26052020/Embedded_2018B.root"
    #"root://131.225.204.161:1094//eos/uscms/store/user/fojensen/EmbeddedSamples_26052020/Embedded_2018C.root"
    #"root://131.225.204.161:1094//eos/uscms/store/user/fojensen/EmbeddedSamples_26052020/Embedded_2018D.root"
    #"file:myNanoProdData2018D_NANO_12.root"
    #"root://cmsxrootd.fnal.gov//store/mc/RunIISummer16NanoAODv7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/NANOAODSIM/PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8_ext1-v1/260000/C36F8EE3-710B-1749-9326-C23D6E9B38E3.root",
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIFall17NanoAODv7/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/PU2017RECOSIMstep_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/130000/00716E48-1312-7146-98D4-CF055CBCBB8A.root"
    "file:31A7B7AE-7141-3440-9F00-D15B50210894.root"
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/70000/31A7B7AE-7141-3440-9F00-D15B50210894.root"
    #"root://cmsxrootd.fnal.gov//store/data/Run2018C/SingleMuon/NANOAOD/02Apr2020-v1/20000/FE8412D1-3B14-3B40-A510-9B671F4FC248.root"   
]
print testfile

cut_Mu = "(Sum$(Muon_pt>=27. && TMath::Abs(Muon_eta)<2.4 && Muon_mediumId && Muon_pfIsoId>=2)>0)"
cut_Electron = "(Sum$(Electron_pt>=32. && TMath::Abs(Electron_eta)<2.5 && Electron_mvaFall17V2Iso_WP90)==0)"
cut_Tau = "(Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe) && (Tau_decayMode!=5&&Tau_decayMode!=6))>0)"
cut_ = cut_Tau + " && " + cut_Mu + " && " + cut_Electron
#cut_ = "1>0"
print cut_

from PhysicsTools.NanoAODTools.postprocessing.examples.MuTauGammaProducer import MuTauGammaProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.MuMuGammaProducer import MuMuGammaProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.JetProducer import JetProducerConstr
modules_ = [MuTauGammaProducerConstr(isMC, isEmb, year), MuMuGammaProducerConstr(), JetProducerConstr()]
if isEmb:
    from PhysicsTools.NanoAODTools.postprocessing.examples.GenTauProducer import GenTauProducer
    modules_.append(GenTauProducer())

if isMC:
    from PhysicsTools.NanoAODTools.postprocessing.modules.btv.btagSFProducer import *
    if year=="2016":
        from PhysicsTools.NanoAODTools.postprocessing.modules.common.puWeightProducer import puWeight_2016 as puWeight
        modules_.append(btagSFProducer("Legacy2016", "deepcsv"))
    elif year=="2017":
        from PhysicsTools.NanoAODTools.postprocessing.modules.common.puWeightProducer import puWeight_2017 as puWeight
        modules_.append(btagSFProducer("2017", "deepcsv"))
    elif year=="2018":
        from PhysicsTools.NanoAODTools.postprocessing.modules.common.puWeightProducer import puWeight_2018 as puWeight
        modules_.append(btagSFProducer("2018", "deepcsv"))
    else:
        print("You must select a year!")
    modules_.append(puWeight())

p=PostProcessor(
    outputDir = "./",
    #inputFiles = inputFiles(),
    inputFiles = testfile,
    cut = cut_,
    modules = modules_,
    provenance = True,
    fwkJobReport = True,
    #maxEntries = 10000,
    #haddFileName = "Embedded_2018A.root",
    #haddFileName = "Embedded_2018B.root",
    #haddFileName = "Embedded_2018C.root",
    #haddFileName = "Embedded_2018D.root",
    #jsonInput = runsAndLumis(),
    #jsonInput = "Cert_271036-284044_13TeV_ReReco_07Aug2017_Collisions16_JSON.txt",
    #jsonInput = "Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt",
    #jsonInput = "Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt",
    outputbranchsel = "keep_and_drop.txt"
)
p.run()

then = datetime.datetime.now()
print ("Finish date and time : ")
print (then.strftime("%Y-%m-%d %H:%M:%S"))

