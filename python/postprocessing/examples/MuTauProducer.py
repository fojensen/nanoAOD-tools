import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaPhi
from ROOT import TLorentzVector
import math

class MuTauProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("MuTauProducer_nGoodMuon", "I")
        self.out.branch("MuTauProducer_nGoodTau", "I")
        self.out.branch("MuTauProducer_HavePair", "I")
        self.out.branch("MuTauProducer_qq", "I")
        self.out.branch("MuTauProducer_MuIdx", "I")
        self.out.branch("MuTauProducer_TauIdx", "I")
        self.out.branch("MuTauProducer_mT", "F")
        self.out.branch("MuTauProducer_MuTauVisMass", "F")
        #self.out.branch("MuTauProducer_MuTauColMass", "F")
        self.out.branch("MuTauProducer_MuTauPt", "F")
        self.out.branch("MuTauProducer_MuTauEta", "F")
        self.out.branch("MuTauProducer_MuTauPhi", "F")
        self.out.branch("MuTauProducer_MuTauDeltaPhi", "F")
        self.out.branch("MuTauProducer_MuMetDeltaPhi", "F")
        self.out.branch("MuTauProducer_nJet", "I")
        self.out.branch("MuTauProducer_nBJetM", "I")
        self.out.branch("MuTauProducer_nBJetT", "I")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #print "beginning MuTauProducer"

        HavePair = 0
        qq = 0
        MuIdx = -1
        TauIdx = -1
        mT = 0
        MuTauVisMass = 0
        MuTauPt = MuTauEta = MuTauPhi = 0
        #MuTauColMass = 0
        MuTauDeltaPhi = 0
        MuMetDeltaPhi = 0
        nJet = 0
        nBJetM = 0
        nBJetT = 0
        
        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        muons = Collection(event, "Muon")
        taus = Collection(event, "Tau")
        jets = Collection(event, "Jet") 
 
        #https://twiki.cern.ch/CMS/SWGuideMuonIdRun2 
        goodMuonIdx = []
        for i, mu in enumerate(muons):
            muonID = mu.tightId and mu.pfIsoId>=2
            if mu.pt>=27. and abs(mu.eta)<2.4 and muonID:
                goodMuonIdx.append(i)
        nGoodMuon = len(goodMuonIdx)

        #https://twiki.cern.ch/CMS/TauIDRecommendationForRun2
        goodTauIdx = []
        for i, tau in enumerate(taus):
            tauID = (8&tau.idDeepTau2017v2p1VSmu) and (128&tau.idDeepTau2017v2p1VSe) and not (tau.decayMode==5 or tau.decayMode==6)
            if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                goodTauIdx.append(i)
        nGoodTau = len(goodTauIdx)
 
        for jet in jets:
            if jet.pt>=20. and abs(jet.eta)<2.5 and (4&jet.jetId):
                isIso = True
                for i, muon in enumerate(muons):
                    if i in goodMuonIdx:
                        if abs(deltaPhi(jet, muon))<0.4:
                            isIso = False
                for i, tau in enumerate(taus):
                    if i in goodTauIdx:
                        if abs(deltaPhi(jet, tau))<0.4:
                            isIso = False
                if isIso:
                   nJet = nJet+1
                   #https://twiki.cern.ch/CMS/BtagRecommendation102X
                   #if jet.btagDeepB>=0.1241:
                   #nBJetL = nBJetL + 1
                   if jet.btagDeepB>=0.4184:
                      nBJetM = nBJetM+1
                      if jet.btagDeepB>=0.7527:
                          nBJetT = nBJetT+1

        for i, mu in enumerate(muons):
            if i in goodMuonIdx:
                for j, tau in enumerate(taus):
                    if j in goodTauIdx:
                        if abs(deltaPhi(mu, tau))>=0.4:
                            if HavePair==0: #choose highest pT tau
                                MuTauDeltaPhi = deltaPhi(mu, tau)
                                MuMetDeltaPhi = deltaPhi(mu.phi, event.MET_phi)
                                qq = mu.charge*tau.charge
                                MuIdx = i
                                TauIdx = j
                                MuTauVisMass = (mu.p4()+tau.p4()).M()
                                MuTauPt =  (mu.p4()+tau.p4()).Pt()
                                MuTauEta =  (mu.p4()+tau.p4()).Eta()
                                mT = 2. * event.MET_pt * mu.pt * (1-math.cos(deltaPhi(event.MET_phi, mu.phi)))
                                mT = math.sqrt(mT)
                                ### collinear mass
                                if tau.phi != mu.phi:
                                    cos0M = math.cos(deltaPhi(tau.phi, event.MET_phi));
                                    cos1M = math.cos(deltaPhi(mu.phi, event.MET_phi));
                                    cos01 = math.cos(deltaPhi(tau.phi, mu.phi));
                                    nu0mag = event.MET_pt * (cos0M-cos1M*cos01) / (1.-cos01*cos01);
                                    nu1mag = (event.MET_pt*cos1M) - (nu0mag*cos01);
                                    nu0 = TLorentzVector()
                                    nu1 = TLorentzVector()
                                    nu0.SetPtEtaPhiM(nu0mag, tau.eta, tau.phi, 0.)
                                    nu1.SetPtEtaPhiM(nu1mag, mu.eta, mu.phi, 0.)
                                    MuTauColMass = (mu.p4()+nu0+tau.p4()+nu1).M()
 
                            HavePair = HavePair + 1

        if not HavePair:
            return False

        self.out.fillBranch("MuTauProducer_HavePair", HavePair)
        self.out.fillBranch("MuTauProducer_qq", qq)
        self.out.fillBranch("MuTauProducer_MuIdx", MuIdx)
        self.out.fillBranch("MuTauProducer_TauIdx", TauIdx)
        self.out.fillBranch("MuTauProducer_mT", mT)
        self.out.fillBranch("MuTauProducer_MuTauVisMass", MuTauVisMass)
        self.out.fillBranch("MuTauProducer_MuTauPt", MuTauPt)
        #self.out.fillBranch("MuTauProducer_MuTauColMass", MuTauColMass)
        self.out.fillBranch("MuTauProducer_MuTauDeltaPhi", MuTauDeltaPhi)
        self.out.fillBranch("MuTauProducer_MuMetDeltaPhi", MuMetDeltaPhi)
        self.out.fillBranch("MuTauProducer_nGoodMuon", nGoodMuon)
        self.out.fillBranch("MuTauProducer_nGoodTau", nGoodTau)
        self.out.fillBranch("MuTauProducer_nJet", nJet)
        self.out.fillBranch("MuTauProducer_nBJetM", nBJetM)
        self.out.fillBranch("MuTauProducer_nBJetT", nBJetT)
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuTauProducerConstr = lambda : MuTauProducer(
)

