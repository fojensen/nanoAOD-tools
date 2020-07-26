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
 
        electrons = Collection(event, "Electron")
        taus = Collection(event, "Tau")
        muons = Collection(event, "Muon")
        photons = Collection(event, "Photon")
        jets = Collection(event, "Jet")

        JetProducer_nJet = 0
        #https://twiki.cern.ch/CMS/BtagRecommendation102X
        JetProducer_nBJetL = JetProducer_nBJetM = JetProducer_nBJetT = 0
        JetProducer_HT = 0

        for jet in jets:
            if jet.pt>=20. and abs(jet.eta)<2.5 and (4&jet.jetId):
                mindr_t = 9.
                for tau in taus:
                    tauID = (8&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu)
                    tauID = tauID and not (tau.decayMode==5 or tau.decayMode==6)
                    if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                        mindr_t_ = deltaR(jet, tau)
                        if mindr_t_ < mindr_t:
                           mindr_t = mindr_t_
                mindr_m = 9.
                for muon in muons:
                    muonID = muon.mediumId and muon.pfIsoId>=2
                    muonID = muon.pt>=27. and abs(muon.eta)<2.4 and muonID
                    if muonID:
                        mindr_m_ = deltaR(jet, muon)
                        if mindr_m_ < mindr_m:
                           mindr_m = mindr_m_
                mindr_g = 9.
                for photon in photons:
                    photonID =  photon.mvaID_WP90 and photon.electronVeto
                    if photon.pt>=32. and abs(photon.eta)<2.5 and photonID:
                        mindr_g_ = deltaR(jet, photon)
                        if mindr_g_ < mindr_g:
                           mindr_g = mindr_g_
                mindr_e = 9.
                for electron in electrons:
                    electronID = electron.mvaFall17V2Iso_WP90
                    if electron.pt>=32. and abs(electron.eta)<2.5 and electronID:
                        mindr_e_ = deltaR(electron, jet)
                        if mindr_e_ < mindr_e:
                            mindr_e = mindr_e

                if mindr_t>=0.4 and mindr_m>=0.4 and mindr_g>=0.4 and mindr_e>=0.4:
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

