import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi
from ROOT import TLorentzVector, TVector3
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
        self.out.branch("MuTau_HavePair", "I")
        self.out.branch("MuTau_qq", "I")
        self.out.branch("MuTau_MuIdx", "I")
        self.out.branch("MuTau_TauIdx", "I")
        self.out.branch("MuTau_mT", "F")
        self.out.branch("MuTau_Mass", "F")
        self.out.branch("MuTau_CollMass", "F")
        self.out.branch("MuTau_Pt", "F")
        self.out.branch("MuTau_DeltaR", "F")
        self.out.branch("MuTau_Trigger", "O")
        self.out.branch("MuTau_HaveTriplet", "I")
        self.out.branch("MuTau_PhotonIdx", "I")
        self.out.branch("MuTau_MuCollMass", "F")
        self.out.branch("MuTau_TauCollMass", "F")
        self.out.branch("MuTau_MinCollMass", "F")
        self.out.branch("MuTau_MaxCollMass", "F")
        self.out.branch("MuTau_IsInside", "O")

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
        Mass = 0
        IsInside = False
        Pt = 0
        DeltaR = 0
        HaveTriplet = 0
        PhotonIdx = -1
        TauCollMass = MuCollMass = CollMass = 0
        MinCollMass = MaxCollMass = 0

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        muons = Collection(event, "Muon")
        taus = Collection(event, "Tau")
        photons = Collection(event, "Photon")

        #https://twiki.cern.ch/CMS/SWGuideMuonIdRun2 
        goodMuonIdx = []
        for i, mu in enumerate(muons):
            muonID = mu.tightId
            if mu.pt>=24. and abs(mu.eta)<2.4 and muonID:
                goodMuonIdx.append(i)

        #https://twiki.cern.ch/CMS/TauIDRecommendationForRun2
        goodTauIdx = []
        for i, tau in enumerate(taus):
            tauID = (1&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (4&tau.idDeepTau2017v2p1VSe) and not (tau.decayMode==5 or tau.decayMode==6)
            if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                goodTauIdx.append(i)

        goodPhotonIdx = []
        for i, photon in enumerate(photons):
            photonID = photon.electronVeto and photon.mvaID_WP90 and (photon.isScEtaEB or photon.isScEtaEE)
            if abs(photon.eta)<2.5 and photonID:
                goodPhotonIdx.append(i)

        maxtauiso = 0
        maxmuiso = 0
        maxphotonpt = 0
        for i, mu in enumerate(muons):
            if i in goodMuonIdx:
                for j, tau in enumerate(taus):
                    if j in goodTauIdx:
                        if abs(deltaPhi(mu, tau))>=0.28284271 and abs(mu.eta-tau.eta)>=0.28284271:
                             if (mu.pfIsoId>=maxmuiso) and (tau.idDeepTau2017v2p1VSjet>=maxtauiso):
                                 DeltaR = deltaR(mu, tau)
                                 qq = mu.charge*tau.charge
                                 MuIdx = i
                                 TauIdx = j
                                 Mass = (mu.p4()+tau.p4()).M()
                                 Pt =  (mu.p4()+tau.p4()).Pt()
                                 HavePair = HavePair + 1
                                 mT = 2. * event.MET_pt * mu.pt * (1.-math.cos(deltaPhi(event.MET_phi, mu.phi)))
                                 mT = math.sqrt(mT)
                                 maxtauiso = tau.idDeepTau2017v2p1VSjet
                                 maxmuiso = mu.pfIsoId
   
                                 Tauv3 = TVector3()
                                 Tauv3.SetPtEtaPhi(tau.pt, 0., tau.phi)
                                 METv3 = TVector3()
                                 METv3.SetPtEtaPhi(event.MET_pt, 0., event.MET_phi)
                                 Muv3 = TVector3()
                                 Muv3.SetPtEtaPhi(mu.pt, 0., mu.phi)
                                 IsInside = False
                                 tauxmet = Tauv3.Cross(METv3)
                                 tauxmu = Tauv3.Cross(Muv3)
                                 muxmet = Muv3.Cross(METv3)
                                 muxtau = Muv3.Cross(Tauv3)
                                 if (tauxmet.Dot(tauxmu)>=0 and muxmet.Dot(muxtau)>=0):
                                     IsInside = True

                                 #collinear approximation 
                                 nu0 = TLorentzVector()
                                 nu1 = TLorentzVector()
                                 cos0M = math.cos(deltaPhi(tau.phi, event.MET_phi))
                                 cos1M = math.cos(deltaPhi(mu.phi, event.MET_phi))
                                 cos01 = math.cos(deltaPhi(tau.phi, mu.phi))
                                 nu0mag = event.MET_pt * (cos0M-cos1M*cos01) / (1.-cos01*cos01)
                                 nu1mag = (event.MET_pt*cos1M) - (nu0mag*cos01)
                                 nu0.SetPtEtaPhiM(nu0mag, tau.eta, tau.phi, 0.)
                                 nu1.SetPtEtaPhiM(nu1mag, mu.eta, mu.phi, 0.)
                                 CollMass = (mu.p4()+tau.p4()+nu0+nu1).M()
 
                                 for k, photon in enumerate(photons):
                                     if k in goodPhotonIdx:
                                         if abs(deltaPhi(mu, photon))>=0.28284271 and abs(deltaPhi(tau, photon))>=0.28284271:
                                             if abs(mu.eta-photon.eta)>=0.28284271 and abs(tau.eta-photon.eta)>=0.28284271:
                                                 if photon.pt>=maxphotonpt:
                                                     HaveTriplet = HaveTriplet+1
                                                     maxphotonpt = photon.pt
                                                     PhotonIdx = k
                                                     TauCollMass = (tau.p4()+nu0+photon.p4()).M()
                                                     MuCollMass = (mu.p4()+nu1+photon.p4()).M()
                                                     MinCollMass = min(TauCollMass, MuCollMass)
                                                     MaxCollMass = max(TauCollMass, MuCollMass)

        Trigger = False
        #2016
        if hasattr(event, "HLT_IsoMu24"): Trigger = Trigger or event.HLT_IsoMu24
        if hasattr(event, "HLT_IsoTkMu24"): Trigger = Trigger or event.HLT_IsoTkMu24
        #2017
        if hasattr(event, "HLT_IsoMu27"): Trigger = Trigger or event.HLT_IsoMu27
        #if hasattr(event, "HLT_IsoMu24"): Trigger = Trigger or event.HLT_IsoMu24
        #2018
        #if hasattr(event, "HLT_IsoMu27"): Trigger = Trigger or event.HLT_IsoMu27
        #if hasattr(event, "HLT_IsoMu24"): Trigger = Trigger or event.HLT_IsoMu24

        self.out.fillBranch("MuTau_HavePair", HavePair)
        self.out.fillBranch("MuTau_qq", qq)
        self.out.fillBranch("MuTau_MuIdx", MuIdx)
        self.out.fillBranch("MuTau_TauIdx", TauIdx)
        self.out.fillBranch("MuTau_mT", mT)
        self.out.fillBranch("MuTau_CollMass", CollMass)
        self.out.fillBranch("MuTau_Mass", Mass)
        self.out.fillBranch("MuTau_Pt", Pt)
        self.out.fillBranch("MuTau_IsInside", IsInside)
        self.out.fillBranch("MuTau_DeltaR", DeltaR)
        self.out.fillBranch("MuTau_Trigger", Trigger)
        self.out.fillBranch("MuTau_HaveTriplet", HaveTriplet)
        self.out.fillBranch("MuTau_PhotonIdx", PhotonIdx)
        self.out.fillBranch("MuTau_TauCollMass", TauCollMass)
        self.out.fillBranch("MuTau_MuCollMass", MuCollMass)
        self.out.fillBranch("MuTau_MinCollMass", MinCollMass)
        self.out.fillBranch("MuTau_MaxCollMass", MaxCollMass)
 
        return True, MuIdx, TauIdx, PhotonIdx

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuTauProducerConstr = lambda : MuTauProducer(
)

