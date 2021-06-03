import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaPhi, deltaR
from ROOT import TLorentzVector
import math

class ETauProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("ETau_HavePair", "I")
        self.out.branch("ETau_qq", "I")
        self.out.branch("ETau_EIdx", "I")
        self.out.branch("ETau_TauIdx", "I")
        self.out.branch("ETau_mT", "F")
        self.out.branch("ETau_Mass", "F")
        self.out.branch("ETau_CollMass", "F")
        self.out.branch("ETau_Pt", "F")
        self.out.branch("ETau_ETauDR", "F")
        self.out.branch("ETau_Trigger", "O")
        self.out.branch("ETau_HaveTriplet", "I")
        self.out.branch("ETau_EGammaDR", "F")
        self.out.branch("ETau_TauGammaDR", "F")
        self.out.branch("ETau_PhotonIdx", "I")
        self.out.branch("ETau_ECollMass", "F")
        self.out.branch("ETau_TauCollMass", "F")
        self.out.branch("ETau_MinCollMass", "F")
        self.out.branch("ETau_MaxCollMass", "F")
        self.out.branch("ETau_ETGCollMass", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #print "beginning ETauProducer"

        HavePair = 0
        qq = 0
        EIdx = -1
        TauIdx = -1
        mT = 0
        Mass = 0
        Pt = 0
        ETauDR = 0
        HaveTriplet = 0
        EGammaDR = TauGammaDR = 0
        PhotonIdx = -1
        TauCollMass = ECollMass = CollMass = 0
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
            tauID = (1&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (32&tau.idDeepTau2017v2p1VSe) and not (tau.decayMode==5 or tau.decayMode==6)
            if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                goodTauIdx.append(i)

        goodPhotonIdx = []
        for i, photon in enumerate(photons):
            photonID = photon.mvaID_WP90 and (photon.isScEtaEB or photon.isScEtaEE)
            photonID = photonID and not photon.pixelSeed
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
                                 ETauDR = deltaR(el, tau)
                                 qq = el.charge*tau.charge
                                 EIdx = i
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
                                                     ECollMass = (el.p4()+nu1+photon.p4()).M()
                                                     MinCollMass = min(TauCollMass, ECollMass)
                                                     MaxCollMass = max(TauCollMass, CollMass)
                                                     EGammaDR = deltaR(el, photon)
                                                     TauGammaDR = deltaR(tau, photon)
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

        self.out.fillBranch("ETau_HavePair", HavePair)
        self.out.fillBranch("ETau_qq", qq)
        self.out.fillBranch("ETau_EIdx", EIdx)
        self.out.fillBranch("ETau_TauIdx", TauIdx)
        self.out.fillBranch("ETau_mT", mT)
        self.out.fillBranch("ETau_Mass", Mass)
        self.out.fillBranch("ETau_CollMass", CollMass)
        self.out.fillBranch("ETau_Pt", Pt)
        self.out.fillBranch("ETau_ETauDR", ETauDR)
        self.out.fillBranch("ETau_Trigger", Trigger)
        self.out.fillBranch("ETau_HaveTriplet", HaveTriplet)
        self.out.fillBranch("ETau_PhotonIdx", PhotonIdx)
        self.out.fillBranch("ETau_TauCollMass", TauCollMass)
        self.out.fillBranch("ETau_ECollMass", ECollMass)
        self.out.fillBranch("ETau_MinCollMass", MinCollMass)
        self.out.fillBranch("ETau_MaxCollMass", MaxCollMass)
        self.out.fillBranch("ETau_EGammaDR", EGammaDR)
        self.out.fillBranch("ETau_TauGammaDR", TauGammaDR)
        self.out.fillBranch("ETau_ETGCollMass", ETGCollMass)
        return True, EIdx, TauIdx, PhotonIdx

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ETauProducerConstr = lambda : ETauProducer(
)

