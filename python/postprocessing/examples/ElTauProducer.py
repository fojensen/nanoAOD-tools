import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi
#from ROOT import TLorentzVector
import math

class ElTauProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("ElTau_HavePair", "I")
        self.out.branch("ElTau_qq", "I")
        self.out.branch("ElTau_ElIdx", "I")
        self.out.branch("ElTau_TauIdx", "I")
        self.out.branch("ElTau_mT", "F")
        self.out.branch("ElTau_Mass", "F")
        self.out.branch("ElTau_Pt", "F")
        self.out.branch("ElTau_DeltaR", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #print "beginning MuTauProducer"

        HavePair = 0
        qq = 0
        ElIdx = -1
        TauIdx = -1
        mT = 0
        Mass = 0
        Pt = 0
        DeltaR = 0
 
        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        electrons = Collection(event, "Electron")
        taus = Collection(event, "Tau")
 
        #https://twiki.cern.ch/CMS/SWGuideMuonIdRun2 
        goodElectronIdx = []
        for i, el in enumerate(electrons):
            elID = el.mvaFall17V2Iso_WP90
            if abs(el.eta)<2.5 and elID:
                goodElectronIdx.append(i)
        nGoodElectron = len(goodElectronIdx)

        #https://twiki.cern.ch/CMS/TauIDRecommendationForRun2
        goodTauIdx = []
        for i, tau in enumerate(taus):
            tauID = (1&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (128&tau.idDeepTau2017v2p1VSe) and not (tau.decayMode==5 or tau.decayMode==6)
            if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                goodTauIdx.append(i)
        nGoodTau = len(goodTauIdx)

        maxtauiso = 0
        maxelectronpt = 0
        for i, el in enumerate(electrons):
            if i in goodElectronIdx:
                for j, tau in enumerate(taus):
                    if j in goodTauIdx:
                        if deltaR(el, tau)>=0.4:
                             if el.pt>=maxelectronpt and tau.idDeepTau2017v2p1VSjet>=maxtauiso:
                                 DeltaR = deltaR(el, tau)
                                 qq = el.charge*tau.charge
                                 ElIdx = i
                                 TauIdx = j
                                 Mass = (el.p4()+tau.p4()).M()
                                 Pt =  (el.p4()+tau.p4()).Pt()
                                 HavePair = HavePair + 1
                                 mT = 2. * event.MET_pt * el.pt * (1-math.cos(deltaPhi(event.MET_phi, el.phi)))
                                 mT = math.sqrt(mT)
                                 maxtauiso = tau.idDeepTau2017v2p1VSjet
                                 maxelectronpt = el.pt

        self.out.fillBranch("ElTau_HavePair", HavePair)
        self.out.fillBranch("ElTau_qq", qq)
        self.out.fillBranch("ElTau_ElIdx", ElIdx)
        self.out.fillBranch("ElTau_TauIdx", TauIdx)
        self.out.fillBranch("ElTau_mT", mT)
        self.out.fillBranch("ElTau_Mass", Mass)
        self.out.fillBranch("ElTau_Pt", Pt)
        self.out.fillBranch("ElTau_DeltaR", DeltaR)
        return True, ElIdx, TauIdx

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ElTauProducerConstr = lambda : ElTauProducer(
)

