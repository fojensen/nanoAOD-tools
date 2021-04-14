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
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/QCD_HT50to100_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/70000/73AF8628-CE5C-7141-B091-BBBCF3BF4333.root",
    #"root://cmsxrootd.fnal.gov//store/data/Run2018D/SingleMuon/NANOAOD/Nano25Oct2019-v1/100000/76BEBA77-9DDB-8144-A183-5842729F006D.root"
#    "root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/C00024AD-3D0D-DE45-949F-E56A81BDDCA7.root" # small DY file
    #"C00024AD-3D0D-DE45-949F-E56A81BDDCA7.root"
    #"109AFD23-2019-E447-8070-8FA4B9203018.root"
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv7/Taustar_TauG_L10000_m500_CP5_13TeV_pythia8/NANOAODSIM/Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/130000/B97EF17B-4634-EB45-8776-BF8CAE1E634A.root"
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/260000/109AFD23-2019-E447-8070-8FA4B9203018.root" # large DY file
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/9E6A9BA6-C187-0F4E-8A45-01B2F2F33E11.root", #small W file
    #"root://cmsxrootd.fnal.gov//store/mc/RunIIAutumn18NanoAODv6/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/20000/E0FBA990-ABF5-3C4D-BCB3-9FCB6F0FFCB3.root" #large W file
    #"root://cmsxrootd.fnal.gov//store/user/fojensen/cmsdasskims/SingleMuon_2018D.root"
    #"root://cmsxrootd.fnal.gov///store/data/Run2018B/Tau/NANOAOD/02Apr2020-v1/230000/11DA3B70-C65C-6E48-8303-F704F59206C9.root"
    #"root://cmsxrootd.fnal.gov///store/data/Run2018D/Tau/NANOAOD/02Apr2020-v2/30000/0EB2A440-1B6A-C34D-87CD-EE60CCC96950.root"
    #"root://cmsxrootd.fnal.gov///store/mc/RunIISummer19UL17NanoAODv2/GluGluHToZG_M-125_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_mc2017_realistic_v8-v1/280000/D235C5DD-0FF0-E24E-B10C-3B563C9ABEC5.root"
#]
#print testfile

cut_TauTau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>=2"
#cut_Tau    = "Sum$(Tau_pt>=180. && TMath::Abs(Tau_eta)<2.1 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>=1"
#cut_TauMET = "Sum$(Tau_pt>=50.0 && TMath::Abs(Tau_eta)<2.1 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>=1 && MET_pt>=90."
cut_EleTau = "Sum$(TMath::Abs(Electron_eta)<2.5 && Electron_pt>=24. && Electron_mvaFall17V2Iso_WP90)>0 && Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (32&Tau_idDeepTau2017v2p1VSe))>0"
cut_MuoTau = "Sum$(TMath::Abs(Muon_eta)<2.4 && Muon_pt>=19. && Muon_tightId && Muon_pfIsoId>=2)>0 && Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>0"
cut_Photon = "Sum$(TMath::Abs(Photon_eta)<2.5 && (Photon_isScEtaEB||Photon_isScEtaEE) && (Photon_electronVeto||!Photon_pixelSeed) && Photon_mvaID_WP90 && Photon_pt>=175.)>0"
cut_EleMuo = "Sum$(TMath::Abs(Electron_eta)<2.5 && Electron_pt>=12. && (Electron_mvaFall17V2Iso_WP90||Electron_mvaFall17V2noIso_WP90))>0 && Sum$(TMath::Abs(Muon_eta)<2.4 && Muon_pt>=8. && Muon_tightId && Muon_pfIsoId>=2)>0"
#https://twiki.cern.ch/CMS/MissingETOptionalFiltersRun2
#cut_Tau = "Sum$(Tau_pt>=20. && TMath::Abs(Tau_eta)<2.3 && Tau_decayMode!=5 && Tau_decayMode!=6 && (1&Tau_idDeepTau2017v2p1VSjet) && (8&Tau_idDeepTau2017v2p1VSmu) && (4&Tau_idDeepTau2017v2p1VSe))>0"
#cut_Photon = "Sum$(TMath::Abs(Photon_eta)<2.5 && (Photon_isScEtaEB||Photon_isScEtaEE) && (Photon_electronVeto||!Photon_pixelSeed) && Photon_mvaID_WP90)>0"
cut_Flag = "(Flag_goodVertices && Flag_globalSuperTightHalo2016Filter && Flag_HBHENoiseFilter && Flag_HBHENoiseIsoFilter && Flag_EcalDeadCellTriggerPrimitiveFilter && Flag_BadPFMuonFilter)"
cut_ = "(" + cut_TauTau + " || " + cut_EleTau + " || " + cut_MuoTau + " || " + cut_Photon + " || " + cut_EleMuo + ") && " + cut_Flag
#cut_ = "(" + cut_Tau + " && " + cut_Photon + " && " + cut_Flag + ")"
#cut_ = "(" + cut_Tau + " && " + cut_Photon + " && " + cut_Flag + ")"
print cut_
#cut_ = "1>0"

#from PhysicsTools.NanoAODTools.postprocessing.examples.EEProducer import EEProducerConstr
#from PhysicsTools.NanoAODTools.postprocessing.examples.MuMuProducer import MuMuProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ElTauProducer import ElTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.MuTauProducer import MuTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.TauTauProducer import TauTauProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.JetProducer import JetProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ZProducer import ZProducerConstr
from PhysicsTools.NanoAODTools.postprocessing.examples.ElMuProducer import ElMuProducerConstr


applyZVeto = True
applyBVeto = True
modules_ = [ZProducerConstr(applyZVeto), MuTauProducerConstr(), ElTauProducerConstr(), TauTauProducerConstr(), ElMuProducerConstr(), JetProducerConstr(year, applyBVeto)]

#interactive
#if len(sys.argv)==3:
#    w = float(sys.argv[2])
#    print ("will run xsWeightProducer: %f" % w)
#    from PhysicsTools.NanoAODTools.postprocessing.examples.xsWeightProducer import xsWeightProducer
#    modules_ += [xsWeightProducer(w)]

#crab
if len(sys.argv)==4:
    w = eval(str(sys.argv[3])[5:])
    print ("will run xsWeightProducer: %f" % w)
    from PhysicsTools.NanoAODTools.postprocessing.examples.xsWeightProducer import xsWeightProducer
    modules_ += [xsWeightProducer(w)]

p=PostProcessor(
    outputDir = "./",
    inputFiles = inputFiles(),
    #inputFiles = testfile,
    cut = cut_,
    modules = modules_,
    #maxEntries = 1000,
    provenance = True,
    fwkJobReport = True,
    jsonInput = runsAndLumis(),
    #jsonInput = "Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt",
    outputbranchsel = "keep_and_drop.txt"
    #histFileName = "myhists.root",
    #histDirName = "histdir"    
)
p.run()

now = datetime.datetime.now()
print ("Finish date and time: ", now.strftime("%Y-%m-%d %H:%M:%S"))
duration = now - then
print ("Total seconds elapsed: ", duration.total_seconds())
