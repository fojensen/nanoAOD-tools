import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR

class JetProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("JetProducer_nJet", "I")
        self.out.branch("JetProducer_nBJetL", "I")
        self.out.branch("JetProducer_nBJetM", "I")
        self.out.branch("JetProducer_nBJetT", "I")
        self.out.branch("JetProducer_HT", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
 
        taus = Collection(event, "Tau")
        muons = Collection(event, "Muon")
        electrons = Collection(event, "Electron")
        photons = Collection(event, "Photon")
        jets = Collection(event, "Jet")

        JetProducer_nJet = 0
        JetProducer_HT = 0
        #https://twiki.cern.ch/CMS/BtagRecommendation102X
        JetProducer_nBJetL = JetProducer_nBJetM = JetProducer_nBJetT = 0

        for jet in jets:
            if jet.pt>=20. and abs(jet.eta)<2.5 and (4&jet.jetId):
                dr_1 = dr_2 = dr_3 = 9

                if event.MuTau_MuIdx>=0 and event.MuTau_TauIdx>=0:
                    dr_1 = deltaR(jet, muons[event.MuTau_MuIdx])
                    dr_2 = deltaR(jet, taus[event.MuTau_TauIdx])
                    if event.MuTau_PhotonIdx>=0:
                        dr_3 = deltaR(jet, photons[event.MuTau_PhotonIdx])

                if event.ElTau_ElIdx>=0 and event.ElTau_TauIdx>=0:
                    dr_1 = deltaR(jet, electrons[event.ElTau_ElIdx])
                    dr_2 = deltaR(jet, taus[event.ElTau_TauIdx])
                    if event.ElTau_PhotonIdx>=0:
                        dr_3 = deltaR(jet, photons[event.ElTau_PhotonIdx])

                if event.TauTau_Tau0Idx>=0 and event.TauTau_Tau1Idx>=0:
                    dr_1 = deltaR(jet, taus[event.TauTau_Tau0Idx])
                    dr_2 = deltaR(jet, taus[event.TauTau_Tau1Idx])
                    if event.TauTau_PhotonIdx>=0:
                        dr_3 = deltaR(jet, photons[event.TauTau_PhotonIdx])

                if event.MuMu_Mu1Idx>=0 and event.MuMu_Mu2Idx>=0:
                    dr_1 = deltaR(jet, muons[event.MuMu_Mu1Idx])
                    dr_2 = deltaR(jet, muons[event.MuMu_Mu2Idx])
                    if event.MuMu_PhotonIdx>=0:
                        dr_3 = deltaR(jet, photons[event.MuMu_PhotonIdx])

                if dr_1>=0.4 and dr_2>=0.4 and dr_3>=0.4:
                    JetProducer_nJet = JetProducer_nJet + 1
                    JetProducer_HT += jet.pt
                    if jet.btagDeepB>=0.1241:
                        JetProducer_nBJetL = JetProducer_nBJetL + 1
                        if jet.btagDeepB>=0.4184:
                            JetProducer_nBJetM = JetProducer_nBJetM + 1
                            if jet.btagDeepB>=0.7527:
                                JetProducer_nBJetT = JetProducer_nBJetT + 1
       
        self.out.fillBranch("JetProducer_nBJetL", JetProducer_nBJetL)
        self.out.fillBranch("JetProducer_nBJetM", JetProducer_nBJetM)
        self.out.fillBranch("JetProducer_nBJetT", JetProducer_nBJetT)
        self.out.fillBranch("JetProducer_nJet", JetProducer_nJet)
        self.out.fillBranch("JetProducer_HT", JetProducer_HT)
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

JetProducerConstr = lambda : JetProducer(
)

