import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from TauPOG.TauIDSFs.TauIDSFTool import TauIDSFTool

class SFProducer_TauTau(Module):
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
        self.tauIDSFTool_jet_Loose = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','Loose', True, isEmb_)
        self.tauIDSFTool_jet_Tight = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','Tight', True, isEmb_)
        self.tauIDSFTool_ele = TauIDSFTool(tauTag,'DeepTau2017v2p1VSe','VLoose', False, isEmb_)
        self.tauIDSFTool_muo = TauIDSFTool(tauTag,'DeepTau2017v2p1VSmu','Tight', False, isEmb_)

    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        #all arrays for up down variations
        self.out.branch("TauTauSF_Tau0E", "F", 3, None, None)
        self.out.branch("TauTauSF_Tau0Mu", "F", 3, None, None)
        self.out.branch("TauTauSF_Tau0JetLoose", "F", 3, None, None)
        self.out.branch("TauTauSF_Tau0JetTight", "F", 3, None, None)
        self.out.branch("TauTauSF_Tau1E", "F", 3, None, None)
        self.out.branch("TauTauSF_Tau1Mu", "F", 3, None, None)
        self.out.branch("TauTauSF_Tau1JetLoose", "F", 3, None, None)
        self.out.branch("TauTauSF_Tau1JetTight", "F", 3, None, None)

        self.out.branch("TauTauSF_Trigger", "F")
        self.out.branch("TauTauSF_PhotonID", "F")
        self.out.branch("TauTauSF_PhotonCSEV", "F")
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
 
        Trigger = 1
        PhotonID = PhotonCSEV = 1

        Tau0E = [1, 1, 1]
        Tau0Mu = [1, 1, 1]
        Tau0JetLoose = [1, 1, 1]
        Tau0JetTight = [1, 1, 1]
        Tau1E = [1, 1, 1]
        Tau1Mu = [1, 1, 1]
        Tau1JetLoose = [1, 1, 1]
        Tau1JetTight = [1, 1, 1]

        if event.TauTau_Tau0Idx>=0 and event.TauTau_Tau1Idx>=0:
            taus = Collection(event, "Tau")
            ###
            tau0 = taus[event.TauTau_Tau0Idx]
            Tau0JetLoose = self.tauIDSFTool_jet_Loose.getSFvsDM(tau0.pt, tau0.decayMode, tau0.genPartFlav, 'All')
            Tau0JetTight = self.tauIDSFTool_jet_Tight.getSFvsDM(tau0.pt, tau0.decayMode, tau0.genPartFlav, 'All')
            Tau0E = self.tauIDSFTool_ele.getSFvsEta(tau0.eta, tau0.genPartFlav, 'All')
            Tau0Mu = self.tauIDSFTool_muo.getSFvsEta(tau0.eta, tau0.genPartFlav, 'All')
            ###
            tau1 = taus[event.TauTau_Tau1Idx]
            Tau1JetLoose = self.tauIDSFTool_jet_Loose.getSFvsDM(tau1.pt, tau1.decayMode, tau1.genPartFlav, 'All')
            Tau1JetTight = self.tauIDSFTool_jet_Tight.getSFvsDM(tau1.pt, tau1.decayMode, tau1.genPartFlav, 'All') 
            Tau1E = self.tauIDSFTool_ele.getSFvsEta(tau1.eta, tau1.genPartFlav, 'All')
            Tau1Mu = self.tauIDSFTool_muo.getSFvsEta(tau1.eta, tau1.genPartFlav, 'All')
            ###
            if event.TauTau_PhotonIdx>=0:
                photons = Collection(event, "Photon")

        self.out.fillBranch("TauTauSF_Tau0E", Tau0E)
        self.out.fillBranch("TauTauSF_Tau0Mu", Tau0Mu)
        self.out.fillBranch("TauTauSF_Tau0JetLoose", Tau0JetLoose)
        self.out.fillBranch("TauTauSF_Tau0JetTight", Tau0JetTight)
        self.out.fillBranch("TauTauSF_Tau1E", Tau1E)
        self.out.fillBranch("TauTauSF_Tau1Mu", Tau1Mu)
        self.out.fillBranch("TauTauSF_Tau1JetLoose", Tau1JetLoose)
        self.out.fillBranch("TauTauSF_Tau1JetTight", Tau1JetTight)
        self.out.fillBranch("TauTauSF_Trigger", Trigger)
        self.out.fillBranch("TauTauSF_PhotonID", PhotonID)
        self.out.fillBranch("TauTauSF_PhotonCSEV", PhotonCSEV)
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

SFProducerConstr_TauTau = lambda year: SFProducer_TauTau(
    year_ = year
)

