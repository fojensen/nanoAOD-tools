import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaPhi, deltaR
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
        self.out.branch("TauTau_Tau0nProng", "I")
        self.out.branch("TauTau_Tau1nProng", "I")
        self.out.branch("TauTau_mT", "F")
        self.out.branch("TauTau_Mass", "F")
        self.out.branch("TauTau_CollMass", "F")
        self.out.branch("TauTau_Pt", "F")
        self.out.branch("TauTau_TauTauDR", "F")
        self.out.branch("TauTau_Trigger", "O")
        self.out.branch("TauTau_HaveTriplet", "I")
        self.out.branch("TauTau_Tau0GammaDR", "F")
        self.out.branch("TauTau_Tau1GammaDR", "F")
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
        #print "beginning TauTauProducer"

        HavePair = 0
        qq = 0
        Tau0Idx = -1
        Tau1Idx = -1
        mT = 0
        Mass = 0
        Pt = 0
        TauTauDR = 0
        HaveTriplet = 0
        Tau0GammaDR = Tau1GammaDR = 0
        PhotonIdx = -1
        Tau0CollMass = Tau1CollMass = CollMass = 0
        MinCollMass = MaxCollMass = 0
        TTGCollMass = 0
        Tau0nProng = Tau1nProng = 0
 
        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        taus = Collection(event, "Tau")
        photons = Collection(event, "Photon")
 
        #https://twiki.cern.ch/CMS/TauIDRecommendationForRun2
        goodTauIdx = []
        for i, tau in enumerate(taus):
            tauID = (1&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (4&tau.idDeepTau2017v2p1VSe) and not (tau.decayMode==5 or tau.decayMode==6)
            if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                goodTauIdx.append(i)
        #if len(goodTauIdx)==0:
        #    for i, tau in enumerate(taus):
        #        tauID = (1&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (4&tau.idDeepTau2017v2p1VSe)
        #        if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
        #            goodTauIdx.append(i)

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
                        #if i>j:
                        if tau0.idDeepTau2017v2p1VSjet >= tau1.idDeepTau2017v2p1VSjet: #is this right?
                            if abs(deltaPhi(tau0, tau1))>=0.28284271 and abs(tau0.eta-tau1.eta)>=0.28284271:
                                 if (tau0.idDeepTau2017v2p1VSjet>=maxtau0iso) and (tau1.idDeepTau2017v2p1VSjet>=maxtau1iso):
                                     TauTauDR = deltaR(tau0, tau1)
                                     qq = tau0.charge*tau1.charge
                                     Tau0Idx = i
                                     Tau1Idx = j
                                     if tau0.decayMode==0  or tau0.decayMode==1  or tau0.decayMode==2:  Tau0nProng = 1
                                     if tau0.decayMode==10 or tau0.decayMode==11 or tau0.decayMode==12: Tau0nProng = 3
                                     if tau1.decayMode==0  or tau1.decayMode==1  or tau1.decayMode==2:  Tau1nProng = 1
                                     if tau1.decayMode==10 or tau1.decayMode==11 or tau1.decayMode==12: Tau1nProng = 3
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
                                                         Tau0GammaDR = deltaR(tau0, photon)
                                                         Tau1GammaDR = deltaR(tau1, photon)
                                                         HaveTriplet = HaveTriplet+1
                                                         maxphotonpt = photon.pt
                                                         PhotonIdx = k
                                                         Tau0CollMass = (tau0.p4()+nu0+photon.p4()).M()
                                                         Tau1CollMass = (tau1.p4()+nu1+photon.p4()).M()
                                                         MinCollMass = min(Tau0CollMass, Tau1CollMass)
                                                         MaxCollMass = max(Tau0CollMass, Tau1CollMass)
                                                         TTGCollMass = (tau0.p4()+nu0+tau1.p4()+nu1+photon.p4()).M()

        Trigger = False
        #2016B, 2016E
        if hasattr(event, "HLT_DoubleMediumIsoPFTau32_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumIsoPFTau32_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumIsoPFTau40_Trk1_eta2p1_Reg
        #2016H
        if hasattr(event, "HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightCombinedIsoPFTau35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1"): Trigger = Trigger or event.HLT_DoubleMediumCombinedIsoPFTau40_Trk1_eta2p1
        if hasattr(event, "HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1"): Trigger = Trigger or event.HLT_DoubleTightCombinedIsoPFTau40_Trk1_eta2p1
        #2017B, 2017F, 2018A(lacks Loose)
        if hasattr(event, "HLT_DoubleLooseChargedIsoPFTau35_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleLooseChargedIsoPFTau35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleLooseChargedIsoPFTau40_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleLooseChargedIsoPFTau40_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleLooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleLooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleLooseChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleLooseChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg
        #2018D
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTauHPS35_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_eta2p1_Reg
        if hasattr(event, "HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleMediumChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg
        if hasattr(event, "HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg"): Trigger = Trigger or event.HLT_DoubleTightChargedIsoPFTauHPS40_Trk1_TightID_eta2p1_Reg
 
        self.out.fillBranch("TauTau_HavePair", HavePair)
        self.out.fillBranch("TauTau_qq", qq)
        self.out.fillBranch("TauTau_Tau0Idx", Tau0Idx)
        self.out.fillBranch("TauTau_Tau0nProng", Tau0nProng)
        self.out.fillBranch("TauTau_Tau1nProng", Tau1nProng)
        self.out.fillBranch("TauTau_Tau1Idx", Tau1Idx)
        self.out.fillBranch("TauTau_Mass", Mass)
        self.out.fillBranch("TauTau_CollMass", CollMass)
        self.out.fillBranch("TauTau_Pt", Pt)
        self.out.fillBranch("TauTau_TauTauDR", TauTauDR)
        self.out.fillBranch("TauTau_Trigger", Trigger)
        self.out.fillBranch("TauTau_HaveTriplet", HaveTriplet)
        self.out.fillBranch("TauTau_Tau0GammaDR", Tau0GammaDR)
        self.out.fillBranch("TauTau_Tau1GammaDR", Tau1GammaDR)
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

