import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

from TauPOG.TauIDSFs.TauIDSFTool import TauIDSFTool
from MuonPOG.MuonSFs.MuonSFTool import MuonSFTool

class SFProducer_MuTau(Module):
    def __init__(self, year_):
        self.year__ = year_
        #print "chosen year %d" % self.year__
        self.muonSFTool = MuonSFTool(self.year__)

        if self.year__==2015 or self.year__==2016:
            tautag = '2016Legacy'
        elif self.year__ == 2017:
            tauTag = '2017ReReco'
        elif self.year__ == 2018:
            tauTag = '2018ReReco'
        else :
            print "Funny year is chosen!"
        isEmb_ = False
        self.tauIDSFTool_jet_Loose = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','Loose', False, isEmb_)
        self.tauIDSFTool_jet_Tight = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','Tight', False, isEmb_)
        self.tauIDSFTool_ele = TauIDSFTool(tauTag,'DeepTau2017v2p1VSe','VLoose', False, isEmb_)
        self.tauIDSFTool_muo = TauIDSFTool(tauTag,'DeepTau2017v2p1VSmu','Tight', False, isEmb_)

    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        #mu+tau
        self.out.branch("MuTauSF_TauE", "F", 3, None, None)
        self.out.branch("MuTauSF_TauMu", "F", 3, None, None)
        self.out.branch("MuTauSF_TauJetLoose", "F", 3, None, None)
        self.out.branch("MuTauSF_TauJetTight", "F", 3, None, None)
        self.out.branch("MuTauSF_MuId", "F")
        self.out.branch("MuTauSF_MuIso", "F")
        self.out.branch("MuTauSF_Trigger", "F")
        self.out.branch("MuTauSF_PhotonID", "F")
        self.out.branch("MuTauSF_PhotonCSEV", "F")
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        MuId = MuIso = MuTrigger = 1
        TauE = [1, 1, 1]
        TauMu = [1, 1, 1]
        TauJetLoose = [1, 1, 1]
        TauJetTight = [1, 1, 1]
        PhotonID = PhotonCSEV = 1

        if event.MuTau_MuIdx>=0 and event.MuTau_TauIdx>=0:
           ###
           muons = Collection(event, "Muon")
           mu = muons[event.MuTau_MuIdx]
           MuIso = self.muonSFTool.getSF_ISO(mu.pt, mu.eta)
           MuId = self.muonSFTool.getSF_ID(mu.pt, mu.eta)
           MuTrigger = self.muonSFTool.getSF_TRIGGER(mu.pt, mu.eta)
           ###
           taus = Collection(event, "Tau")
           tau = taus[event.MuTau_TauIdx]
           TauJetLoose = self.tauIDSFTool_jet_Loose.getSFvsPT(tau.pt, tau.genPartFlav, 'All')
           TauJetTight = self.tauIDSFTool_jet_Tight.getSFvsPT(tau.pt, tau.genPartFlav, 'All')
           TauE = self.tauIDSFTool_ele.getSFvsEta(tau.eta, tau.genPartFlav, 'All')
           TauMu = self.tauIDSFTool_muo.getSFvsEta(tau.eta, tau.genPartFlav, 'All')
           ###
           if event.MuTau_PhotonIdx>=0:
              photons = Collection(event, "Photon")
              pass
        
        self.out.fillBranch("MuTauSF_TauE", TauE)
        self.out.fillBranch("MuTauSF_TauMu", TauMu)
        self.out.fillBranch("MuTauSF_TauJetLoose", TauJetLoose)
        self.out.fillBranch("MuTauSF_TauJetTight", TauJetTight)
        self.out.fillBranch("MuTauSF_MuId", MuId)
        self.out.fillBranch("MuTauSF_MuIso", MuIso)
        self.out.fillBranch("MuTauSF_Trigger", MuTrigger)
        self.out.fillBranch("MuTauSF_PhotonID", PhotonID)
        self.out.fillBranch("MuTauSF_PhotonCSEV", PhotonCSEV)
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

SFProducerConstr_MuTau = lambda year: SFProducer_MuTau(
    year_ = year
)

