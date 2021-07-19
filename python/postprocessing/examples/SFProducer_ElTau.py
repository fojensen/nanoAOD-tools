import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from TauPOG.TauIDSFs.TauIDSFTool import TauIDSFTool

class SFProducer_ElTau(Module):
    def __init__(self, year_):
        self.year__ = year_
        #print "chosen year %d" % self.year__

        if self.year__==2015 or self.year__==2016:
            tauTag= '2016Legacy'
        elif self.year__==2017:
            tauTag= '2017ReReco'
        elif self.year__==2018:
            tauTag= '2018ReReco'
        else :
            print "Funny year is chosen!"
        isEmb_ = False
        self.tauIDSFTool_jet_Loose = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','Loose', False, isEmb_)
        self.tauIDSFTool_jet_Tight = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','Tight', False, isEmb_)
        self.tauIDSFTool_ele = TauIDSFTool(tauTag,'DeepTau2017v2p1VSe','Tight', False, isEmb_)
        self.tauIDSFTool_muo = TauIDSFTool(tauTag,'DeepTau2017v2p1VSmu','Tight', False, isEmb_)

    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        #all arrays for up down variations
        #e+tau
        self.out.branch("ElTauSF_TauE", "F", 3, None, None)
        self.out.branch("ElTauSF_TauMu", "F", 3, None, None)
        self.out.branch("ElTauSF_TauJetLoose", "F", 3, None, None)
        self.out.branch("ElTauSF_TauJetTight", "F", 3, None, None)
        self.out.branch("ElTauSF_ElReco", "F")
        self.out.branch("ElTauSF_ElID", "F")
        self.out.branch("ElTauSF_Trigger", "F")
        self.out.branch("ElTauSF_PhotonID", "F")
        self.out.branch("ElTauSF_PhotonPSV", "F")
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        ElReco = ElID = Trigger = 1
        TauE = [1, 1, 1]
        TauMu = [1, 1, 1]
        TauJetLoose = [1, 1, 1]
        TauJetTight = [1, 1, 1]
        PhotonID = PhotonPSV = 1

        if event.ElTau_ElIdx>=0 and event.ElTau_TauIdx>=0:
            electrons = Collection(event, "Electron")
            taus = Collection(event, "Tau")
            tau = taus[event.ElTau_TauIdx]
            TauJetLoose = self.tauIDSFTool_jet_Loose.getSFvsPT(tau.pt, tau.genPartFlav, 'All')
            TauJetTight = self.tauIDSFTool_jet_Tight.getSFvsPT(tau.pt, tau.genPartFlav, 'All')
            TauE = self.tauIDSFTool_ele.getSFvsEta(tau.eta, tau.genPartFlav, 'All')
            TauMu = self.tauIDSFTool_muo.getSFvsEta(tau.eta, tau.genPartFlav, 'All')
            if event.ElTau_PhotonIdx>=0:
                photons = Collection(event, "Photon")

        self.out.fillBranch("ElTauSF_TauE", TauE)
        self.out.fillBranch("ElTauSF_TauMu", TauMu)
        self.out.fillBranch("ElTauSF_TauJetLoose", TauJetLoose)
        self.out.fillBranch("ElTauSF_TauJetTight", TauJetTight)
        self.out.fillBranch("ElTauSF_ElReco", ElReco)
        self.out.fillBranch("ElTauSF_ElID", ElID)
        self.out.fillBranch("ElTauSF_Trigger", Trigger)
        self.out.fillBranch("ElTauSF_PhotonID", PhotonID)
        self.out.fillBranch("ElTauSF_PhotonPSV", PhotonPSV)

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

SFProducerConstr_ElTau = lambda year: SFProducer_ElTau(
    year_ = year
)

