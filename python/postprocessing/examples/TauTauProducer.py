import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi
from ROOT import TLorentzVector
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
        self.out.branch("TauTau_CollMass", "F")
        self.out.branch("TauTau_Pt", "F")
        self.out.branch("TauTau_DeltaR", "F")
        self.out.branch("TauTau_Trigger", "O")
        self.out.branch("TauTau_HaveTriplet", "I")
        self.out.branch("TauTau_PhotonIdx", "I")
        self.out.branch("TauTau_Tau0CollMass", "F")
        self.out.branch("TauTau_Tau1CollMass", "F")
        self.out.branch("TauTau_MinCollMass", "F")
        self.out.branch("TauTau_MaxCollMass", "F")
        self.out.branch("TauTau_TTGCollMass", "F")

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
        HaveTriplet = 0
        PhotonIdx = -1
        Tau0CollMass = Tau1CollMass = CollMass = 0
        MinCollMass = MaxCollMass = 0
        TTGCollMass = 0
 
        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        taus = Collection(event, "Tau")
        photons = Collection(event, "Photon")
 
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

        maxtau0iso = 0
        maxtau1iso = 0
        maxphotonpt = 0
        for i, tau0 in enumerate(taus):
            if i in goodTauIdx:
                for j, tau1 in enumerate(taus):
                    if j in goodTauIdx:
                        if i>j:
                            if abs(deltaPhi(tau0, tau1))>=0.28284271 and abs(tau0.eta-tau1.eta)>=0.28284271:
                                 if (tau0.idDeepTau2017v2p1VSjet>=maxtau0iso) and (tau1.idDeepTau2017v2p1VSjet>=maxtau1iso):
                                     DeltaR = deltaR(tau0, tau1)
                                     qq = tau0.charge*tau1.charge
                                     Tau0Idx = i
                                     Tau1Idx = j
                                     Mass = (tau0.p4()+tau1.p4()).M()
                                     Pt =   (tau0.p4()+tau1.p4()).Pt()
                                     HavePair = HavePair + 1
                                     maxtau0iso = tau0.idDeepTau2017v2p1VSjet
                                     maxtau1iso = tau1.idDeepTau2017v2p1VSjet

                                     #collinear approximation 
                                     nu0 = TLorentzVector()
                                     nu1 = TLorentzVector()
                                     cos0M = math.cos(deltaPhi(tau0.phi, event.MET_phi))
                                     cos1M = math.cos(deltaPhi(tau1.phi, event.MET_phi))
                                     cos01 = math.cos(deltaPhi(tau0.phi, tau1.phi))
                                     nu0mag = event.MET_pt * (cos0M-cos1M*cos01) / (1.-cos01*cos01)
                                     nu1mag = (event.MET_pt*cos1M) - (nu0mag*cos01)
                                     nu0.SetPtEtaPhiM(nu0mag, tau0.eta, tau0.phi, 0.)
                                     nu1.SetPtEtaPhiM(nu1mag, tau1.eta, tau1.phi, 0.)
                                     CollMass = (tau0.p4()+tau1.p4()+nu0+nu1).M()

                                     for k, photon in enumerate(photons):
                                         if k in goodPhotonIdx:
                                             if abs(deltaPhi(tau0, photon))>=0.28284271 and abs(deltaPhi(tau1, photon))>=0.28284271:
                                                 if abs(tau0.eta-photon.eta)>=0.28284271 and abs(tau1.eta-photon.eta)>=0.28284271:
                                                     if photon.pt>=maxphotonpt:
                                                         HaveTriplet = HaveTriplet+1
                                                         maxphotonpt = photon.pt
                                                         PhotonIdx = k
                                                         Tau0CollMass = (tau0.p4()+nu0+photon.p4()).M()
                                                         Tau1CollMass = (tau1.p4()+nu1+photon.p4()).M()
                                                         MinCollMass = min(Tau0CollMass, Tau1CollMass)
                                                         MaxCollMass = max(Tau0CollMass, Tau1CollMass)
                                                         TTGCollMass = (tau0.p4()+nu0+tau1.p4()+nu1+photon.p4()).M()

        Trigger = False
        #
        if hasattr(event, "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg"):         Trigger = Trigger or event.HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg
        #
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg"):         Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg"):         Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg"):  Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg"):          Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg"):  Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg"):          Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg
        #
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg"):         Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg"):         Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg"):  Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg"):          Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg"):  Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg"):          Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg

        self.out.fillBranch("TauTau_HavePair", HavePair)
        self.out.fillBranch("TauTau_qq", qq)
        self.out.fillBranch("TauTau_Tau0Idx", Tau0Idx)
        self.out.fillBranch("TauTau_Tau1Idx", Tau1Idx)
        self.out.fillBranch("TauTau_Mass", Mass)
        self.out.fillBranch("TauTau_CollMass", CollMass)
        self.out.fillBranch("TauTau_Pt", Pt)
        self.out.fillBranch("TauTau_DeltaR", DeltaR)
        self.out.fillBranch("TauTau_Trigger", Trigger)
        self.out.fillBranch("TauTau_HaveTriplet", HaveTriplet)
        self.out.fillBranch("TauTau_PhotonIdx", PhotonIdx)
        self.out.fillBranch("TauTau_Tau0CollMass", Tau0CollMass)
        self.out.fillBranch("TauTau_Tau1CollMass", Tau1CollMass)
        self.out.fillBranch("TauTau_MinCollMass", MinCollMass)
        self.out.fillBranch("TauTau_MaxCollMass", MaxCollMass)
        self.out.fillBranch("TauTau_TTGCollMass", TTGCollMass)
        return True, Tau0Idx, Tau1Idx, PhotonIdx

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

TauTauProducerConstr = lambda : TauTauProducer(
)

