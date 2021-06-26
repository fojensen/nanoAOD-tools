import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaPhi, deltaR
from ROOT import TLorentzVector
import math

class EMuProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("EMu_HavePair", "I")
        self.out.branch("EMu_qq", "I")
        self.out.branch("EMu_EIdx", "I")
        self.out.branch("EMu_MuIdx", "I")
        self.out.branch("EMu_Mass", "F")
        self.out.branch("EMu_CollMass", "F")
        self.out.branch("EMu_Pt", "F")
        self.out.branch("EMu_EMuDR", "F")
        self.out.branch("EMu_Trigger", "O")
        self.out.branch("EMu_HaveTriplet", "I")
        self.out.branch("EMu_EGammaDR", "F")
        self.out.branch("EMu_MuGammaDR", "F")
        self.out.branch("EMu_PhotonIdx", "I")
        self.out.branch("EMu_ECollMass", "F")
        self.out.branch("EMu_MuCollMass", "F")
        self.out.branch("EMu_MinCollMass", "F")
        self.out.branch("EMu_MaxCollMass", "F")
        self.out.branch("EMu_EMGCollMass", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #print "beginning EMuProducer"

        HavePair = 0
        qq = 0
        EIdx = -1
        MuIdx = -1
        Mass = 0
        Pt = 0
        EMuDR = 0
        HaveTriplet = 0
        EGammaDR = MuGammaDR = 0
        PhotonIdx = -1
        ECollMass = MuCollMass = CollMass = 0
        MinCollMass = MaxCollMass = 0
        EMGCollMass = 0

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        electrons = Collection(event, "Electron")
        muons = Collection(event, "Muon")
        photons = Collection(event, "Photon")

        #https://twiki.cern.ch/CMS/SWGuideMuonIdRun2 
        goodMuonIdx = []
        for i, mu in enumerate(muons):
            muonID = mu.tightId
            if mu.pt>=8. and abs(mu.eta)<2.4 and muonID:
                goodMuonIdx.append(i)

        goodElectronIdx = []
        for i, el in enumerate(electrons):
            elID = 1>0
            if el.pt>=12. and abs(el.eta)<2.5 and elID:
                goodElectronIdx.append(i)

        goodPhotonIdx = []
        for i, photon in enumerate(photons):
            photonID = photon.mvaID_WP90 and (photon.isScEtaEB or photon.isScEtaEE)
            photonID = photonID and not photon.pixelSeed
            if abs(photon.eta)<2.5 and photonID:
                goodPhotonIdx.append(i)

        maxmuiso = -1
        maxelectronid = -1
        maxphotonpt = 0
        for i, el in enumerate(electrons):
            if i in goodElectronIdx:
                for j, mu in enumerate(muons):
                    if j in goodMuonIdx:
                        if abs(deltaPhi(el, mu))>=0.28284271 and abs(el.eta-mu.eta)>=0.28284271:
                             if (mu.pfIsoId>=maxmuiso) and (el.mvaFall17V2Iso>=maxelectronid):
                                 HavePair = HavePair+1
                                 EMuDR = deltaR(el, mu)
                                 qq = el.charge*mu.charge
                                 EIdx = i
                                 MuIdx = j
                                 Mass = (el.p4()+mu.p4()).M()
                                 Pt =  (el.p4()+mu.p4()).Pt()
                                 HavePair = HavePair + 1
                                 maxelectronid = el.mvaFall17V2Iso
                                 maxmuiso = mu.pfIsoId

                                 #collinear approximation 
                                 nu0 = TLorentzVector()
                                 nu1 = TLorentzVector()
                                 cos0M = math.cos(deltaPhi(el.phi, event.MET_phi))
                                 cos1M = math.cos(deltaPhi(mu.phi, event.MET_phi))
                                 cos01 = math.cos(deltaPhi(el.phi, mu.phi))
                                 nu0mag = event.MET_pt * (cos0M-cos1M*cos01) / (1.-cos01*cos01)
                                 nu1mag = (event.MET_pt*cos1M) - (nu0mag*cos01)
                                 nu0.SetPtEtaPhiM(nu0mag, el.eta, el.phi, 0.)
                                 nu1.SetPtEtaPhiM(nu1mag, mu.eta, mu.phi, 0.)
                                 CollMass = (el.p4()+mu.p4()+nu0+nu1).M()

                                 for k, photon in enumerate(photons):
                                     if k in goodPhotonIdx:
                                         if abs(deltaPhi(el, photon))>=0.28284271 and abs(deltaPhi(mu, photon))>=0.28284271:
                                             if abs(el.eta-photon.eta)>=0.28284271 and abs(mu.eta-photon.eta)>=0.28284271:
                                                 if photon.pt>=maxphotonpt:
                                                     HaveTriplet = HaveTriplet+1
                                                     EGammaDR = deltaR(el, photon)
                                                     MuGammaDR = deltaR(mu, photon)
                                                     maxphotonpt = photon.pt
                                                     PhotonIdx = k
                                                     ECollMass = (el.p4()+nu0+photon.p4()).M()
                                                     MuCollMass = (mu.p4()+nu1+photon.p4()).M()
                                                     MinCollMass = min(ECollMass, MuCollMass)
                                                     MaxCollMass = max(ECollMass, MuCollMass)
                                                     EMGCollMass = (el.p4()+nu0+mu.p4()+nu1+photon.p4()).M()

        Trigger = False
        if hasattr(event, "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL"): Trigger = Trigger or event.HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL
        if hasattr(event, "HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_DZ"): Trigger = Trigger or event.HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_DZ
        if hasattr(event, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"): Trigger = Trigger or event.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL
        if hasattr(event, "HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"): Trigger = Trigger or event.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ
        if hasattr(event, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"): Trigger = Trigger or event.HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL
        if hasattr(event, "HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"): Trigger = Trigger or event.HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ
        if hasattr(event, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL"): Trigger = Trigger or event.HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL
        if hasattr(event, "HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ"): Trigger = Trigger or event.HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ
        if hasattr(event, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL"): Trigger = Trigger or event.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL
        if hasattr(event, "HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"): Trigger = Trigger or event.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ

        self.out.fillBranch("EMu_HavePair", HavePair)
        self.out.fillBranch("EMu_qq", qq)
        self.out.fillBranch("EMu_EIdx", EIdx)
        self.out.fillBranch("EMu_MuIdx", MuIdx)
        self.out.fillBranch("EMu_CollMass", CollMass)
        self.out.fillBranch("EMu_Mass", Mass)
        self.out.fillBranch("EMu_Pt", Pt)
        self.out.fillBranch("EMu_EMuDR", EMuDR)
        self.out.fillBranch("EMu_Trigger", Trigger)
        self.out.fillBranch("EMu_HaveTriplet", HaveTriplet)
        self.out.fillBranch("EMu_EGammaDR", EGammaDR)
        self.out.fillBranch("EMu_MuGammaDR", MuGammaDR)
        self.out.fillBranch("EMu_PhotonIdx", PhotonIdx)
        self.out.fillBranch("EMu_ECollMass", ECollMass)
        self.out.fillBranch("EMu_MuCollMass", MuCollMass)
        self.out.fillBranch("EMu_MinCollMass", MinCollMass)
        self.out.fillBranch("EMu_MaxCollMass", MaxCollMass)
        self.out.fillBranch("EMu_EMGCollMass", EMGCollMass)
 
        return True, EIdx, MuIdx, PhotonIdx

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

EMuProducerConstr = lambda : EMuProducer(
)
