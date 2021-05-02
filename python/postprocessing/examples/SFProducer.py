import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

class SFProducer(Module):
    def __init__(self, year_):
        self.year__ = year_
        #print "chosen year %d" % self.year__
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        #all arrays for up down variations
        #mu+tau
        self.out.branch("MuTauSF_TauIso", "F")
        self.out.branch("MuTauSF_TauE", "F")
        self.out.branch("MuTauSF_TauMu", "F")
        self.out.branch("MuTauSF_MuId", "F")
        self.out.branch("MuTauSF_MuIso", "F")
        self.out.branch("MuTauSF_MuTrigger", "F")
        #e+tau
        self.out.branch("ETauSF_TauIso", "F")
        self.out.branch("ETauSF_TauE", "F")
        self.out.branch("ETauSF_TauMu", "F")
        #tau+tau
        self.out.branch("TauTauSF_Tau0Iso", "F")
        self.out.branch("TauTauSF_Tau0E", "F")
        self.out.branch("TauTauSF_Tau0Mu", "F")
        self.out.branch("TauTauSF_Tau1Iso", "F")
        self.out.branch("TauTauSF_Tau1E", "F")
        self.out.branch("TauTauSF_Tau1Mu", "F")
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
 
        taus = Collection(event, "Tau")
        muons = Collection(event, "Muon")
        electrons = Collection(event, "Electron")
        photons = Collection(event, "Photon")

        if event.MuTau_MuIdx>=0 and event.MuTau_TauIdx>=0:
            if event.MuTau_PhotonIdx>=0:
        if event.ElTau_ElIdx>=0 and event.ElTau_TauIdx>=0:
            if event.ElTau_PhotonIdx>=0:
        if event.TauTau_Tau0Idx>=0 and event.TauTau_Tau1Idx>=0:
            if event.TauTau_PhotonIdx>=0:
        if event.ElMu_ElIdx>=0 and event.ElMu_MuIdx>=0:
            if event.ElMu_PhotonIdx>=0:

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

JetProducerConstr = lambda year, applyVeto: JetProducer(
    year_ = year,
    applyVeto_ = applyVeto
)

