import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi
from ROOT import TLorentzVector
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
        self.out.branch("ElTau_CollMass", "F")
        self.out.branch("ElTau_Pt", "F")
        self.out.branch("ElTau_DeltaR", "F")
        self.out.branch("ElTau_Trigger", "O")
        self.out.branch("ElTau_HaveTriplet", "I")
        self.out.branch("ElTau_PhotonIdx", "I")
        self.out.branch("ElTau_ElCollMass", "F")
        self.out.branch("ElTau_TauCollMass", "F")
        self.out.branch("ElTau_MinCollMass", "F")
        self.out.branch("ElTau_MaxCollMass", "F")
        self.out.branch("ElTau_ElGammaDeltaR", "F")
        self.out.branch("ElTau_TauGammaDeltaR", "F")
        self.out.branch("ElTau_ETGCollMass", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #print "beginning ElTauProducer"

        HavePair = 0
        qq = 0
        ElIdx = -1
        TauIdx = -1
        mT = 0
        Mass = 0
        Pt = 0
        DeltaR = 0
        HaveTriplet = 0
        PhotonIdx = -1
        TauCollMass = ElCollMass = CollMass = 0
        ElGammaDeltaR = TauGammaDeltaR = 0
        MinCollMass = MaxCollMass = 0
        ETGCollMass = 0
 
        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        electrons = Collection(event, "Electron")
        taus = Collection(event, "Tau")
        photons = Collection(event, "Photon")
 
        #https://twiki.cern.ch/CMS/SWGuideMuonIdRun2 
        goodElectronIdx = []
        for i, el in enumerate(electrons):
            elID = 1>0
            if el.pt>=27. and abs(el.eta)<2.5 and elID:
                goodElectronIdx.append(i)

        #https://twiki.cern.ch/CMS/TauIDRecommendationForRun2
        goodTauIdx = []
        for i, tau in enumerate(taus):
            tauID = (1&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (4&tau.idDeepTau2017v2p1VSe) and not (tau.decayMode==5 or tau.decayMode==6)
            if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                goodTauIdx.append(i)

        goodPhotonIdx = []
        for i, photon in enumerate(photons):
            photonID = photon.mvaID_WP90 and (photon.isScEtaEB or photon.isScEtaEE)
            photonID = photonID and not photon.pixelSeed
            #photonID = photonID and photon.electronVeto
            if abs(photon.eta)<2.5 and photonID:
                goodPhotonIdx.append(i)

        maxtauiso = 0
        maxelectronid = -1
        maxphotonpt = 0
        for i, el in enumerate(electrons):
            if i in goodElectronIdx:
                for j, tau in enumerate(taus):
                    if j in goodTauIdx:
                        if abs(deltaPhi(el, tau))>=0.28284271 and abs(el.eta-tau.eta)>=0.28284271:
                             if el.mvaFall17V2Iso>=maxelectronid and tau.idDeepTau2017v2p1VSjet>=maxtauiso:
                                 DeltaR = deltaR(el, tau)
                                 qq = el.charge*tau.charge
                                 ElIdx = i
                                 TauIdx = j
                                 Mass = (el.p4()+tau.p4()).M()
                                 Pt = (el.p4()+tau.p4()).Pt()
                                 HavePair = HavePair + 1
                                 mT = 2. * event.MET_pt * el.pt * (1.-math.cos(deltaPhi(event.MET_phi, el.phi)))
                                 mT = math.sqrt(mT)
                                 maxtauiso = tau.idDeepTau2017v2p1VSjet
                                 maxelectronid = el.mvaFall17V2Iso

                                 #collinear approximation 
                                 nu0 = TLorentzVector()
                                 nu1 = TLorentzVector()
                                 cos0M = math.cos(deltaPhi(tau.phi, event.MET_phi))
                                 cos1M = math.cos(deltaPhi(el.phi, event.MET_phi))
                                 cos01 = math.cos(deltaPhi(tau.phi, el.phi))
                                 nu0mag = event.MET_pt * (cos0M-cos1M*cos01) / (1.-cos01*cos01)
                                 nu1mag = (event.MET_pt*cos1M) - (nu0mag*cos01)
                                 nu0.SetPtEtaPhiM(nu0mag, tau.eta, tau.phi, 0.)
                                 nu1.SetPtEtaPhiM(nu1mag, el.eta, el.phi, 0.)
                                 CollMass = (el.p4()+tau.p4()+nu0+nu1).M()

                                 for k, photon in enumerate(photons):
                                     if k in goodPhotonIdx:
                                         if abs(deltaPhi(el, photon))>=0.28284271 and abs(deltaPhi(tau, photon))>=0.28284271:
                                             if abs(el.eta-photon.eta)>=0.28284271 and abs(tau.eta-photon.eta)>=0.28284271:
                                                 if photon.pt>=maxphotonpt:
                                                     HaveTriplet = HaveTriplet+1
                                                     maxphotonpt = photon.pt
                                                     PhotonIdx = k
                                                     TauCollMass = (tau.p4()+nu0+photon.p4()).M()
                                                     ElCollMass = (el.p4()+nu1+photon.p4()).M()
                                                     MinCollMass = min(TauCollMass, ElCollMass)
                                                     MaxCollMass = max(TauCollMass, ElCollMass)
                                                     ElGammaDeltaR = deltaR(el, photon)
                                                     TauGammaDeltaR = deltaR(tau, photon)
                                                     ETGCollMass = (tau.p4()+nu0+el.p4()+nu1+photon.p4()).M()

        Trigger = False
        #2016
        if hasattr(event, "HLT_Ele27_WPTight_Gsf"): Trigger = Trigger or event.HLT_Ele27_WPTight_Gsf
        if hasattr(event, "HLT_Ele25_eta2p1_WPTight_Gsf"): Trigger = Trigger or event.HLT_Ele25_eta2p1_WPTight_Gsf
        #2017
        if hasattr(event, "HLT_Ele32_WPTight_Gsf_L1DoubleEG"): Trigger = Trigger or event.HLT_Ele32_WPTight_Gsf_L1DoubleEG
        if hasattr(event, "HLT_Ele35_WPTight_Gsf"): Trigger = Trigger or event.HLT_Ele35_WPTight_Gsf
        #if hasattr(event, "HLT_Ele27_WPTight_Gsf"): Trigger = Trigger or event.HLT_Ele27_WPTight_Gsf
        if hasattr(event, "HLT_Ele32_WPTight_Gsf"): Trigger = Trigger or event.HLT_Ele32_WPTight_Gsf
        #2018
        #if hasattr(event, "HLT_Ele32_WPTight_Gsf"): Trigger = Trigger or event.HLT_Ele32_WPTight_Gsf

        self.out.fillBranch("ElTau_HavePair", HavePair)
        self.out.fillBranch("ElTau_qq", qq)
        self.out.fillBranch("ElTau_ElIdx", ElIdx)
        self.out.fillBranch("ElTau_TauIdx", TauIdx)
        self.out.fillBranch("ElTau_mT", mT)
        self.out.fillBranch("ElTau_Mass", Mass)
        self.out.fillBranch("ElTau_CollMass", CollMass)
        self.out.fillBranch("ElTau_Pt", Pt)
        self.out.fillBranch("ElTau_DeltaR", DeltaR)
        self.out.fillBranch("ElTau_Trigger", Trigger)
        self.out.fillBranch("ElTau_HaveTriplet", HaveTriplet)
        self.out.fillBranch("ElTau_PhotonIdx", PhotonIdx)
        self.out.fillBranch("ElTau_TauCollMass", TauCollMass)
        self.out.fillBranch("ElTau_ElCollMass", ElCollMass)
        self.out.fillBranch("ElTau_MinCollMass", MinCollMass)
        self.out.fillBranch("ElTau_MaxCollMass", MaxCollMass)
        self.out.fillBranch("ElTau_ElGammaDeltaR", ElGammaDeltaR)
        self.out.fillBranch("ElTau_TauGammaDeltaR", TauGammaDeltaR)
        self.out.fillBranch("ElTau_ETGCollMass", ETGCollMass)
        return True, ElIdx, TauIdx, PhotonIdx

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ElTauProducerConstr = lambda : ElTauProducer(
)

