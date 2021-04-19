import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaPhi

class JetProducer(Module):
    def __init__(self, year_, applyVeto_):
        self.year__ = year_
        self.applyVeto__ = applyVeto_
        self.wp = [0, 0, 0]
        #print "chosen year %d" % self.year__
        #https://twiki.cern.ch/CMS/BtagRecommendation2016Legacy
        if self.year__==2016:
            self.wp[0] = 0.2217
            self.wp[1] = 0.6321
            self.wp[2] = 0.8953
        #https://twiki.cern.ch/CMS/BtagRecommendation106XUL17
        elif self.year__==2017:
            self.wp[0] = 0.1355
            self.wp[1] = 0.4506
            self.wp[2] = 0.7738
        #https://twiki.cern.ch/CMS/BtagRecommendation106XUL18
        elif self.year__==2018: 
            self.wp[0] = 0.1208
            self.wp[1] = 0.4168
            self.wp[2] = 0.7665
        else :
            print "*** JetProducer: no year given! ***"
            self.wp[0] = 0.2217
            self.wp[1] = 0.6321
            self.wp[2] = 0.8953

    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("JetProducer_nJet", "I")
        self.out.branch("JetProducer_nJetinc", "I")
        self.out.branch("JetProducer_nBJetL", "I")
        self.out.branch("JetProducer_nBJetM", "I")
        self.out.branch("JetProducer_nBJetT", "I")
        self.out.branch("JetProducer_HT", "F")
        self.out.branch("JetProducer_HTinc", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
 
        taus = Collection(event, "Tau")
        muons = Collection(event, "Muon")
        electrons = Collection(event, "Electron")
        photons = Collection(event, "Photon")
        jets = Collection(event, "Jet")

        nJet = nJetinc = 0
        HT = HTinc = 0
        nBJetL = nBJetM = nBJetT = 0

        for jet in jets:
            if jet.pt>=20. and abs(jet.eta)<2.5 and (4&jet.jetId):
                dr_1 = dr_2 = dr_3 = False
                havePair = haveTriplet = False

                if event.MuTau_MuIdx>=0 and event.MuTau_TauIdx>=0:
                    havePair = True
                    mu = muons[event.MuTau_MuIdx]
                    tau = taus[event.MuTau_TauIdx]
                    dr_1 = abs(deltaPhi(jet, mu))>=0.28284271 and abs(jet.eta-mu.eta)>=0.28284271
                    dr_2 = abs(deltaPhi(jet, tau))>=0.28284271 and abs(jet.eta-tau.eta)>=0.28284271
                    if event.MuTau_PhotonIdx>=0:
                        havePair = False
                        haveTriplet = True
                        photon = photons[event.MuTau_PhotonIdx]
                        dr_3 = abs(deltaPhi(jet, photon))>=0.28284271 and abs(jet.eta-photon.eta)>=0.28284271

                if event.ElTau_ElIdx>=0 and event.ElTau_TauIdx>=0:
                    havePair = True
                    el = electrons[event.ElTau_ElIdx]
                    tau = taus[event.ElTau_TauIdx]
                    dr_1 = abs(deltaPhi(jet, el))>=0.28284271 and abs(jet.eta-el.eta)>=0.28284271
                    dr_2 = abs(deltaPhi(jet, tau))>=0.28284271 and abs(jet.eta-tau.eta)>=0.28284271
                    if event.ElTau_PhotonIdx>=0:
                        havePair = False
                        haveTriplet = True
                        photon = photons[event.ElTau_PhotonIdx]
                        dr_3 = abs(deltaPhi(jet, photon))>=0.28284271 and abs(jet.eta-photon.eta)>=0.28284271

                if event.TauTau_Tau0Idx>=0 and event.TauTau_Tau1Idx>=0:
                    havePair = True
                    tau0 = taus[event.TauTau_Tau0Idx]
                    tau1 = taus[event.TauTau_Tau1Idx]
                    dr_1 = abs(deltaPhi(jet, tau0))>=0.28284271 and abs(jet.eta-tau0.eta)>=0.28284271
                    dr_2 = abs(deltaPhi(jet, tau1))>=0.28284271 and abs(jet.eta-tau1.eta)>=0.28284271
                    if event.TauTau_PhotonIdx>=0:
                        havePair = False
                        haveTriplet = True
                        photon = photons[event.TauTau_PhotonIdx]
                        dr_3 = abs(deltaPhi(jet, photon))>=0.28284271 and abs(jet.eta-photon.eta)>=0.28284271

                if event.ElMu_ElIdx>=0 and event.ElMu_MuIdx>=0:
                    havePair = True
                    el = electrons[event.ElMu_ElIdx]
                    mu = muons[event.ElMu_MuIdx]
                    dr_1 = abs(deltaPhi(jet, el))>=0.28284271 and abs(jet.eta-el.eta)>=0.28284271
                    dr_2 = abs(deltaPhi(jet, mu))>=0.28284271 and abs(jet.eta-mu.eta)>=0.28284271
                    if event.ElMu_PhotonIdx>=0:
                        havePair = False
                        haveTriplet = True
                        photon = photons[event.ElMu_PhotonIdx]
                        dr_3 = abs(deltaPhi(jet, photon))>=0.28284271 and abs(jet.eta-photon.eta)>=0.28284271

                nJetinc = nJetinc + 1
                HTinc += jet.pt
                if (not havePair or not haveTriplet) or (havePair and dr_1 and dr_2) or (haveTriplet and dr_1 and dr_2 and dr_3):
                    nJet = nJet + 1
                    HT += jet.pt
                    if jet.btagDeepB >= self.wp[0]:
                        nBJetL = nBJetL + 1
                        if jet.btagDeepB >= self.wp[1]:
                            nBJetM = nBJetM + 1
                            if jet.btagDeepB >= self.wp[2]:
                                nBJetT = nBJetT + 1
                                if self.applyVeto__ and nBJetT>0: return False

        self.out.fillBranch("JetProducer_nBJetL", nBJetL)
        self.out.fillBranch("JetProducer_nBJetM", nBJetM)
        self.out.fillBranch("JetProducer_nBJetT", nBJetT)
        self.out.fillBranch("JetProducer_nJet", nJet)
        self.out.fillBranch("JetProducer_nJetinc", nJetinc)
        self.out.fillBranch("JetProducer_HT", HT)
        self.out.fillBranch("JetProducer_HTinc", HTinc)
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

JetProducerConstr = lambda year, applyVeto: JetProducer(
    year_ = year,
    applyVeto_ = applyVeto
)

