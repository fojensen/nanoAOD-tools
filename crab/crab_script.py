import datetime
then = datetime.datetime.now()
print ("Start date and time: ", then.strftime("%Y-%m-%d %H:%M:%S"))

import os
print "pwd: %s" % os.system("pwd")

from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 

import sys
print sys.argv
for arg in sys.argv:
    print arg

#interactive
#if len(sys.argv)<2:
#    print "missing year parameter!"
#year = int(sys.argv[1])

#crab
if len(sys.argv)<3:
    print "missing year parameter!"
year = int(sys.argv[2][5:])

print "chosen year: %d " % year

from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import runsAndLumis

#testfile = [
#    "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m250_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/7FEC7B94-611C-364A-9A12-B9BD43C01EC3.root"
#    "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m1000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/270000/1E3560C2-B140-F34F-B24D-E7A1AD26CEC2.root"
#    "root://cmsxrootd.fnal.gov///store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m5000_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/120000/44BFF07F-8D14-0347-B215-040F8D99B95B.root"
#    "root://cmsxrootd.fnal.gov///store/mc/RunIISummer20UL18NanoAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v15_L1v1-v1/270000/B10221E9-6482-0C41-84EF-61B6449CC19B.root"
#    "B10221E9-6482-0C41-84EF-61B6449CC19B.root"
#    "../analysis/sig_m1000_f0p1_fprime0p1.root"
#    "../analysis/sig_m1000_f1_fprime0p1.root"
#    "root://cmsxrootd.fnal.gov///store/mc/RunIISummer19UL16NanoAODAPVv2/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/106X_mcRun2_asymptotic_preVFP_v9-v1/00000/8BECFEF3-D180-C04C-B0AB-EE9197F2C8D1.root" 
#    "8BECFEF3-D180-C04C-B0AB-EE9197F2C8D1.root"
#    "04EB33AE-D912-664B-BBD5-18D6D8C16678.root"
#]
#print testfile

cut_ElTau = "Sum$(TMath::Abs(Electron_eta)<2.5 && Electron_pt>=27. && Electron_mvaFall17V2Iso_WP90)>0 && Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (32&Tau_idDeepTau2017v2p1VSe))>0"
cut_MuTau = "Sum$(TMath::Abs(Muon_eta)<2.4 && Muon_pt>=24. && Muon_tightId && Muon_pfIsoId>=4)>0 && Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>0"
cut_TauTau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>=2"
cut_ElMu = "Sum$(TMath::Abs(Electron_eta)<2.5 && Electron_pt>=23. && Electron_mvaFall17V2Iso_WP90)>0 && Sum$(TMath::Abs(Muon_eta)<2.4 && Muon_pt>=23. && Muon_tightId && Muon_pfIsoId>=4)>0"
#https://twiki.cern.ch/CMS/MissingETOptionalFiltersRun2
cut_Flag = "(Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter)"
#cut_ = "(" + cut_ElTau + " || " + cut_MuTau + " || " + cut_TauTau + " || " + cut_ElMu + ") && " + cut_Flag
cut_ = "(" + cut_ElTau + " || " + cut_MuTau + " || " + cut_TauTau + ") && " + cut_Flag
#cut_ = "1>0"
#print cut_

#from PhysicsTools.NanoAODTools.postprocessing.examples.EEProducer import EEProducerConstr
#from PhysicsTools.NanoAODTools.postprocessing.examples.MuMuProducer import MuMuProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ZProducer import ZProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ElTauProducer import ElTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.MuTauProducer import MuTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.TauTauProducer import TauTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ElMuProducer import ElMuProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.JetProducer import JetProducerConstr

applyZVeto = True
applyBVeto = False
modules_ = [ZProducerConstr(applyZVeto), ElTauProducerConstr(), MuTauProducerConstr(), TauTauProducerConstr(), ElMuProducerConstr(), JetProducerConstr(year, applyBVeto)]
#modules_ = [ZProducerConstr(applyZVeto)]

#interactive len(sys.argv)==3
#crab len(sys.argv)==4
if len(sys.argv)==3 or len(sys.argv)==4:
    if len(sys.argv)==3: w = float(sys.argv[2])
    if len(sys.argv)==4: w = eval(str(sys.argv[3])[5:])
    print ("will run xsWeightProducer: %f" % w)
    from PhysicsTools.NanoAODTools.postprocessing.examples.xsWeightProducer import xsWeightProducer
    modules_ += [xsWeightProducer(w)]
    from PhysicsTools.NanoAODTools.postprocessing.examples.SFProducer_ElTau import SFProducerConstr_ElTau
    from PhysicsTools.NanoAODTools.postprocessing.examples.SFProducer_MuTau import SFProducerConstr_MuTau
    from PhysicsTools.NanoAODTools.postprocessing.examples.SFProducer_TauTau import SFProducerConstr_TauTau
    modules_ += [SFProducerConstr_ElTau(year), SFProducerConstr_MuTau(year), SFProducerConstr_TauTau(year)]

p=PostProcessor(
    outputDir = "./",
    inputFiles = inputFiles(),
    #inputFiles = testfile,
    cut = cut_,
    modules = modules_,
    #maxEntries = 100000,
    provenance = True,
    fwkJobReport = True,
    #haddFileName = "ran_m1000_f0p1_fprime0p1.root",
    #haddFileName = "ran_m1000_f1_fprime0p1.root",
    #jsonInput = runsAndLumis(),
    #jsonInput = "Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt",
    outputbranchsel = "keep_and_drop.txt"
)
p.run()

now = datetime.datetime.now()
print ("Finish date and time: ", now.strftime("%Y-%m-%d %H:%M:%S"))
duration = now - then
print ("Total seconds elapsed: ", duration.total_seconds())
