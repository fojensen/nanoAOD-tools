import FWCore.ParameterSet.Config as cms

process = cms.Process("analysis")

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('/store/mc/RunIIAutumn18MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/80000/E735CB65-684E-284D-B8A7-195842816F43.root')
)

process.maxEvents = cms.untracked.PSet(
   input = cms.untracked.int32(10)
)

process.options = cms.untracked.PSet(
   wantSummary = cms.untracked.bool(True),
)
#process.Tracer = cms.Service("Tracer")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleTreeDrawer",
   src = cms.InputTag("prunedGenParticles"),
   printP4 = cms.untracked.bool(False),
   printPtEtaPhi = cms.untracked.bool(False),
   printVertex = cms.untracked.bool(False),
   printStatus = cms.untracked.bool(True),
   printIndex = cms.untracked.bool(False),
   #status = cms.untracked.vint32(3),
)

process.p = cms.Path(
   process.printTree
)

