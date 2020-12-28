import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi
#from ROOT import TLorentzVector
import math

class TauTauProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("TauTau_HavePair", "I")
        self.out.branch("TauTau_qq", "I")
        self.out.branch("TauTau_Tau0Idx", "I")
        self.out.branch("TauTau_Tau1Idx", "I")
        self.out.branch("TauTau_mT", "F")
        self.out.branch("TauTau_Mass", "F")
        self.out.branch("TauTau_Pt", "F")
        self.out.branch("TauTau_DeltaR", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #print "beginning MuTauProducer"

        HavePair = 0
        qq = 0
        Tau0Idx = -1
        Tau1Idx = -1
        mT = 0
        Mass = 0
        Pt = 0
        DeltaR = 0
 
        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        taus = Collection(event, "Tau")
 
        #https://twiki.cern.ch/CMS/TauIDRecommendationForRun2
        goodTauIdx = []
        for i, tau in enumerate(taus):
            tauID = (1&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (128&tau.idDeepTau2017v2p1VSe) and not (tau.decayMode==5 or tau.decayMode==6)
            if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                goodTauIdx.append(i)
        nGoodTau = len(goodTauIdx)

        maxtau0iso = 0
        maxtau1iso = 0
        for i, tau0 in enumerate(taus):
            if i in goodTauIdx:
                for j, tau1 in enumerate(taus):
                    if j in goodTauIdx:
                        if deltaR(tau0, tau1)>=0.4:
                             if (tau0.idDeepTau2017v2p1VSjet>=maxtau0iso) and (tau1.idDeepTau2017v2p1VSjet>=maxtau1iso):
                                 DeltaR = deltaR(tau0, tau1)
                                 qq = tau0.charge*tau1.charge
                                 Tau0Idx = i
                                 Tau1Idx = j
                                 Mass = (tau0.p4()+tau1.p4()).M()
                                 Pt =  (tau0.p4()+tau1.p4()).Pt()
                                 HavePair = HavePair + 1
                                 maxtau0iso0 = tau0.idDeepTau2017v2p1VSjet
                                 maxatau1iso = tau1.idDeepTau2017v2p1VSjet

        self.out.fillBranch("TauTau_HavePair", HavePair)
        self.out.fillBranch("TauTau_qq", qq)
        self.out.fillBranch("TauTau_Tau0Idx", Tau0Idx)
        self.out.fillBranch("TauTau_Tau1Idx", Tau1Idx)
        self.out.fillBranch("TauTau_Mass", Mass)
        self.out.fillBranch("TauTau_Pt", Pt)
        self.out.fillBranch("TauTau_DeltaR", DeltaR)
        return True, Tau0Idx, Tau1Idx

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

TauTauProducerConstr = lambda : TauTauProducer(
)

