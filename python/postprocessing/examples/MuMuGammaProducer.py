import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi
from ROOT import TLorentzVector
#import math

class MuMuGammaProducer(Module):
    def __init__(self, isMC_):
        self.isMC__ = isMC_
        #if isMC:
        #    from MuonPOG.MuonSFs.MuonSFTool import MuonSFTool
        #    muonSFTool = MuonSFTool() 
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("MuMuGamma_havePair", "I")
        self.out.branch("MuMuGamma_Mu0Idx", "I")
        self.out.branch("MuMuGamma_Mu1Idx", "I")
        self.out.branch("MuMuGamma_MuMuDeltaR", "F")
        self.out.branch("MuMuGamma_MuMuDeltaPhi", "F")
        self.out.branch("MuMuGamma_MuMuMass", "F")
        self.out.branch("MuMuGamma_MuMuPt", "F")
        self.out.branch("MuMuGamma_MuMuEta", "F")
        self.out.branch("MuMuGamma_MuMuPhi", "F")
        self.out.branch("MuMuGamma_haveTriplet", "I")
        self.out.branch("MuMuGamma_PhotonIdx", "I")
        self.out.branch("MuMuGamma_MuMuGammaMass", "F")
        self.out.branch("MuMuGamma_Mu0GammaDeltaR", "F")
        self.out.branch("MuMuGamma_Mu1GammaDeltaR", "F")
        self.out.branch("MuMuGamma_Mu0GammaDeltaPhi", "F")
        self.out.branch("MuMuGamma_Mu1GammaDeltaPhi", "F")
        self.out.branch("MuMuGamma_MuMuGammaDeltaR", "F")
        self.out.branch("MuMuGamma_MuMuGammaDeltaPhi", "F")
        if self.isMC__:
            self.out.branch("MuMuGamma_Mu0SFId", "F")
            self.out.branch("MuMuGamma_Mu0SFIso", "F")
            self.out.branch("MuMuGamma_Mu1SFId", "F")
            self.out.branch("MuMuGamma_Mu1SFIso", "F")
            self.out.branch("MuMuGamma_MuSFTrigger", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        muons = Collection(event, "Muon")
        #fsrphotons = Collection(event, "FsrPhoton")

        photons = Collection(event, "Photon")
        goodPhotonIdx = []
        for i, photon in enumerate(photons):
            photonID = photon.mvaID_WP90 and photon.electronVeto
            if photon.pt>=32. and abs(photon.eta)<2.5 and photonID:
                goodPhotonIdx.append(i)
        nPhoton = len(goodPhotonIdx)

        havePair = 0
        Mu0Idx = Mu1Idx = -1
        MuMuDeltaR = MuMuDeltaPhi = 0
        MuMuMass = MuMuPt = MuMuEta = MuMuPhi = 0
        haveTriplet = 0
        PhotonIdx = -1
        MuMuGammaMass = 0
        #MuMuFsrMass = 0
        Mu0GammaDeltaR = Mu1GammaDeltaR = 0
        Mu0GammaDeltaPhi = Mu1GammaDeltaPhi = 0
        MuMuGammaDeltaR = MuMuGammaDeltaPhi = 0
        if self.isMC__:
           Mu0SFId = Mu0SFIso = 0
           Mu1SFId = Mu1SFIso = 0
           MuSFTrigger = 0
 
        for i, mu0 in enumerate(muons):
            mu0ID = mu0.mediumId and mu0.pfIsoId>=2
            if mu0.pt>=27. and abs(mu0.eta)<2.4 and mu0ID:
                for j, mu1 in enumerate(muons):
                    mu1ID = mu1.mediumId and mu1.pfIsoId>=2
                    if mu1.pt>=10. and abs(mu1.eta)<2.4 and mu1ID:
                        if mu0.charge*mu1.charge<0:
                           MuMuDeltaEta = mu0.eta-mu1.eta
                           MuMuDeltaPhi = deltaPhi(mu0, mu1)
                           if abs(MuMuDeltaPhi)>=0.2:
                                havePair = havePair + 1
                                MuMuDeltaR = deltaR(mu0, mu1)
                                MuMuMass = (mu0.p4()+mu1.p4()).M()
                                MuMuPt =   (mu0.p4()+mu1.p4()).Pt()
                                MuMuEta =  (mu0.p4()+mu1.p4()).Eta()
                                MuMuPhi =  (mu0.p4()+mu1.p4()).Phi()
                                Mu0Idx = i
                                Mu1Idx = j
                                if mu1.pt>mu0.pt:
                                    Mu0Idx = j
                                    Mu1Idx = i
                                if self.isMC__:
                                    Mu0SFId = muonSFTool.getSF_TightID(mu0.pt, mu0.eta)
                                    Mu0SFIso = muonSFTool.getSF_ISO_TightID(mu0.pt, mu0.eta, 6)
                                    Mu1SFId = muonSFTool.getSF_MediumID(mu1.pt, mu1.eta)
                                    Mu1SFIso = muonSFTool.getSF_ISO_MediumID(mu1.pt, mu1.eta, 2)
                                    MuSFTrigger = muonSFTool.getSF_Trigger(mu0.pt, mu0.eta)
                                    if mu1.pt>=mu0.pt and mu1.pfIsoId>=mu0.pfIsoId:
                                        MuSFTrigger = muonSFTool.getSF_Trigger(mu1.pt, mu1.eta)
                           
                                for k, photon in enumerate(photons):
                                    if k in goodPhotonIdx:
                                        Mu0GammaDeltaPhi = deltaPhi(mu0, photon)
                                        Mu0GammaDeltaEta = mu0.eta-photon.eta
                                        Mu1GammaDeltaPhi = deltaPhi(mu0, photon)
                                        Mu1GammaDeltaEta = mu1.eta-photon.eta 
                                        isIso =           abs(Mu0GammaDeltaPhi)>=0.3
                                        isIso = isIso and abs(Mu1GammaDeltaPhi)>=0.3
                                        #isIso = True
                                        if isIso:
                                            haveTriplet = haveTriplet + 1
                                            PhotonIdx = k
                                            Mu0GammaDeltaR = deltaR(mu0, photon)
                                            Mu1GammaDeltaR = deltaR(mu1, photon)
                                            Z = mu0.p4()+mu1.p4()
                                            MuMuGammaDeltaR = deltaR(Z.Eta(), Z.Phi(), photon.eta, photon.phi)
                                            MuMuGammaDeltaPhi = deltaPhi(Z.Phi(), photon.phi)
                                            MuMuGammaMass = (mu0.p4()+mu1.p4()+photon.p4()).M()

        self.out.fillBranch("MuMuGamma_havePair", havePair)
        self.out.fillBranch("MuMuGamma_Mu0Idx", Mu0Idx)
        self.out.fillBranch("MuMuGamma_Mu1Idx", Mu1Idx)
        self.out.fillBranch("MuMuGamma_MuMuMass", MuMuMass)
        self.out.fillBranch("MuMuGamma_MuMuPt", MuMuPt)
        self.out.fillBranch("MuMuGamma_MuMuEta", MuMuEta)
        self.out.fillBranch("MuMuGamma_MuMuPhi", MuMuPhi)
        self.out.fillBranch("MuMuGamma_MuMuDeltaR", MuMuDeltaR)
        self.out.fillBranch("MuMuGamma_MuMuDeltaPhi", MuMuDeltaPhi)
        
        self.out.fillBranch("MuMuGamma_haveTriplet", haveTriplet)
        self.out.fillBranch("MuMuGamma_PhotonIdx", PhotonIdx)
        self.out.fillBranch("MuMuGamma_MuMuGammaMass", MuMuGammaMass)
        self.out.fillBranch("MuMuGamma_Mu0GammaDeltaR", Mu0GammaDeltaR)
        self.out.fillBranch("MuMuGamma_Mu1GammaDeltaR", Mu1GammaDeltaR)
        self.out.fillBranch("MuMuGamma_Mu0GammaDeltaPhi", Mu0GammaDeltaPhi)
        self.out.fillBranch("MuMuGamma_Mu1GammaDeltaPhi", Mu1GammaDeltaPhi)
        self.out.fillBranch("MuMuGamma_MuMuGammaDeltaR", MuMuGammaDeltaR)
        self.out.fillBranch("MuMuGamma_MuMuGammaDeltaPhi", MuMuGammaDeltaPhi)

        if self.isMC__:
           self.out.fillBranch("MuMuGamma_Mu0SFId", Mu0SFId)
           self.out.fillBranch("MuMuGamma_Mu0SFIso", Mu0SFIso)
           self.out.fillBranch("MuMuGamma_Mu1SFId", Mu1SFId)
           self.out.fillBranch("MuMuGamma_Mu1SFIso", Mu1SFIso)
           self.out.fillBranch("MuMuGamma_MuSFTrigger", MuSFTrigger)

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuMuGammaProducerConstr = lambda isMC : MuMuGammaProducer(
    isMC_ = isMC
)

