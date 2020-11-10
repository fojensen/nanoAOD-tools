import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi
#from ROOT import TLorentzVector

class MuMuGammaProducer(Module):
    def __init__(self):
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

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        muons = Collection(event, "Muon")

        photons = Collection(event, "Photon")
        goodPhotonIdx = []
        for i, photon in enumerate(photons):
            photonID = photon.mvaID_WP90 and photon.electronVeto
            if abs(photon.eta)<2.5 and photonID:
                goodPhotonIdx.append(i)
        nPhoton = len(goodPhotonIdx)

        havePair = 0
        Mu0Idx = Mu1Idx = -1
        MuMuDeltaR = MuMuDeltaPhi = 0
        MuMuMass = MuMuPt = MuMuEta = MuMuPhi = 0
        haveTriplet = 0
        PhotonIdx = -1
        MuMuGammaMass = 0
        Mu0GammaDeltaR = Mu1GammaDeltaR = 0
        Mu0GammaDeltaPhi = Mu1GammaDeltaPhi = 0
        MuMuGammaDeltaR = MuMuGammaDeltaPhi = 0

        for i, mu0 in enumerate(muons):
            for j, mu1 in enumerate(muons):
                if i>j:
                    if mu0.pt>=10. and abs(mu0.eta)<2.4 and mu0.mediumId and mu0.pfIsoId>=2:
                        if mu1.pt>=10. and abs(mu1.eta)<2.4 and mu1.mediumId and mu1.pfIsoId>=2:
                            if mu0.charge*mu1.charge<0:
                                havePair = havePair + 1
                                MuMuDeltaPhi = deltaPhi(mu0, mu1)
                                MuMuDeltaR = deltaR(mu0, mu1)
                                MuMuMass = (mu0.p4()+mu1.p4()).M()
                                MuMuPt =   (mu0.p4()+mu1.p4()).Pt()
                                MuMuEta =  (mu0.p4()+mu1.p4()).Eta()
                                MuMuPhi =  (mu0.p4()+mu1.p4()).Phi()
                                Mu0Idx = i
                                Mu1Idx = j
                                maxphotonpt = 0
                                for k, photon in enumerate(photons):
                                    if k in goodPhotonIdx:
                                        isIso = abs(deltaPhi(mu0, photon))>=0.3 and abs(deltaPhi(mu1, photon))>=0.3
                                        if isIso:
                                            haveTriplet = haveTriplet + 1
                                            if photon.pt>maxphotonpt:
                                                PhotonIdx = k
                                                maxphotonpt = photon.pt
                                                Mu0GammaDeltaPhi = deltaPhi(mu0, photon)
                                                Mu0GammaDeltaEta = mu0.eta-photon.eta
                                                Mu1GammaDeltaPhi = deltaPhi(mu0, photon)
                                                Mu1GammaDeltaEta = mu1.eta-photon.eta 
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

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuMuGammaProducerConstr = lambda : MuMuGammaProducer()

