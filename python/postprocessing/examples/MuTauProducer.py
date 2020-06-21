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
        self.out.branch("MuTauProducer_VisMass", "F")
        self.out.branch("MuTauProducer_DeltaPhi", "F")
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
        VisMass = 0
        DeltaPhi = 0
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
            muonID = mu.tightId and mu.pfIsoId>=6
            if mu.pt>=27. and abs(mu.eta)<2.4 and muonID:
                goodMuonIdx.append(i)
        nGoodMuon = len(goodMuonIdx)

        #https://twiki.cern.ch/CMS/TauIDRecommendationForRun2
        goodTauIdx = []
        for i, tau in enumerate(taus):
            #tauID = True
            tauID = (8&tau.idDeepTau2017v2p1VSmu) and (128&tau.idDeepTau2017v2p1VSe) and not (tau.decayMode==5||tau.decayMode==6)
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
                                DeltaPhi = deltaPhi(mu, tau)
                                qq = mu.charge*tau.charge
                                MuIdx = i
                                TauIdx = j
                                VisMass = (mu.p4()+tau.p4()).M()
                                mT = 2. * event.MET_pt * mu.pt * (1-math.cos(deltaPhi(event.MET_phi, mu.phi)))
                                mT = math.sqrt(mT)
                            HavePair = HavePair + 1

        if not HavePair:
            #print "ending MuTauProducer, return False"
            return False
        self.out.fillBranch("MuTauProducer_HavePair", HavePair)
        self.out.fillBranch("MuTauProducer_qq", qq)
        self.out.fillBranch("MuTauProducer_MuIdx", MuIdx)
        self.out.fillBranch("MuTauProducer_TauIdx", TauIdx)
        self.out.fillBranch("MuTauProducer_mT", mT)
        self.out.fillBranch("MuTauProducer_VisMass", VisMass)
        self.out.fillBranch("MuTauProducer_DeltaPhi", DeltaPhi)
        self.out.fillBranch("MuTauProducer_nGoodMuon", nGoodMuon)
        self.out.fillBranch("MuTauProducer_nGoodTau", nGoodTau)
        self.out.fillBranch("MuTauProducer_nJet", nJet)
        self.out.fillBranch("MuTauProducer_nBJetM", nBJetM)
        self.out.fillBranch("MuTauProducer_nBJetT", nBJetT)
        #print "ending MuTauProducer, return True"
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuTauProducerConstr = lambda : MuTauProducer(
)

