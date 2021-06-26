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
        #e+tau
        self.out.branch("ETauSF_TauE", "F")
        self.out.branch("ETauSF_TauMu", "F")
        self.out.branch("ETauSF_TauJet", "F")
        self.out.branch("ETauSF_EReco", "F")
        self.out.branch("ETauSF_EID", "F")
        self.out.branch("ETauSF_Trigger", "F")
        #mu+tau
        self.out.branch("MuTauSF_TauE", "F")
        self.out.branch("MuTauSF_TauMu", "F")
        self.out.branch("MuTauSF_TauJet", "F")
        self.out.branch("MuTauSF_MuId", "F")
        self.out.branch("MuTauSF_MuIso", "F")
        self.out.branch("MuTauSF_Trigger", "F")
        #tau+tau
        self.out.branch("TauTauSF_Tau0E", "F")
        self.out.branch("TauTauSF_Tau0Mu", "F")
        self.out.branch("TauTauSF_Tau0Jet", "F")
        self.out.branch("TauTauSF_Tau1E", "F")
        self.out.branch("TauTauSF_Tau1Mu", "F")
        self.out.branch("TauTauSF_Tau1Jet", "F")
        self.out.branch("TauTauSF_Trigger", "F")
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
 
        taus = Collection(event, "Tau")
        muons = Collection(event, "Muon")
        electrons = Collection(event, "Electron")
        photons = Collection(event, "Photon")

        ETauSF_TauE = ETauSF_TauMu = ETauSF_TauJet = 1
        ETauSF_EReco = ETauSF_EID = ETauSF_Trigger = 1
        MuTauSF_TauE = MuTauSF_TauMu = MuTauSF_TauJet = 1
        MuTauSF_MuId = MuTauSF_MuIso = MuTauSF_Trigger = 1
        TauTauSF_Tau0E = TauTauSF_Tau0Mu = TauTauSF_Tau0Jet = 1
        TauTauSF_Tau1E = TauTauSF_Tau1Mu = TauTauSF_Tau1Jet = 1
        TauTauSF_Trigger = 1

        if event.MuTau_MuIdx>=0 and event.MuTau_TauIdx>=0:
            if event.MuTau_PhotonIdx>=0:
                pass
        if event.ETau_EIdx>=0 and event.ETau_TauIdx>=0:
            if event.ETau_PhotonIdx>=0:
                pass
        if event.TauTau_Tau0Idx>=0 and event.TauTau_Tau1Idx>=0:
            if event.TauTau_PhotonIdx>=0:
                pass

        self.out.fillBranch("ETauSF_TauE", ETauSF_TauE)
        self.out.fillBranch("ETauSF_TauMu", ETauSF_TauMu)
        self.out.fillBranch("ETauSF_TauJet", ETauSF_TauJet)
        self.out.fillBranch("ETauSF_EReco", ETauSF_EReco)
        self.out.fillBranch("ETauSF_EID", ETauSF_EID)
        self.out.fillBranch("ETauSF_Trigger", ETauSF_Trigger)
        self.out.fillBranch("MuTauSF_TauE", MuTauSF_TauE)
        self.out.fillBranch("MuTauSF_TauMu", MuTauSF_TauMu)
        self.out.fillBranch("MuTauSF_TauJet", MuTauSF_TauJet)
        self.out.fillBranch("MuTauSF_MuId", MuTauSF_MuId)
        self.out.fillBranch("MuTauSF_MuIso", MuTauSF_MuIso)
        self.out.fillBranch("MuTauSF_Trigger", MuTauSF_Trigger)
        self.out.fillBranch("TauTauSF_Tau0E", TauTauSF_Tau0E)
        self.out.fillBranch("TauTauSF_Tau0Mu", TauTauSF_Tau0Mu)
        self.out.fillBranch("TauTauSF_Tau0Jet", TauTauSF_Tau0Jet)
        self.out.fillBranch("TauTauSF_Tau1E", TauTauSF_Tau1E)
        self.out.fillBranch("TauTauSF_Tau1Mu", TauTauSF_Tau1Mu)
        self.out.fillBranch("TauTauSF_Tau1Jet", TauTauSF_Tau1Jet)
        self.out.fillBranch("TauTauSF_Trigger", TauTauSF_Trigger)
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

SFProducerConstr = lambda year: SFProducer(
    year_ = year
)

