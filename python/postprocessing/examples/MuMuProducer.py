import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi

class MuMuProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("MuMu_HavePair", "I")
        self.out.branch("MuMu_Mass", "F")
        self.out.branch("MuMu_HaveTriplet", "I")
        self.out.branch("MuMu_MuMuGammaMass", "F")
        self.out.branch("MuMu_PhotonIdx", "I")
        self.out.branch("MuMu_Mu1Idx", "I")
        self.out.branch("MuMu_Mu2Idx", "I")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#Muon
        HavePair = 0
        Mass = 0.
        Mu1Idx = Mu2Idx = -1
        HaveTriplet = 0
        GammaMass = 0.
        PhotonIdx = -1

        muons = Collection(event, "Muon")

        photons = Collection(event, "Photon")
        goodPhotonIdx = []
        for i, photon in enumerate(photons):
            photonID = photon.electronVeto and photon.mvaID_WP90 and (photon.isScEtaEB or photon.isScEtaEE)
            if abs(photon.eta)<2.5 and photonID:
                goodPhotonIdx.append(i)

        maxphotonpt = 0
        for i, mu1 in enumerate(muons):
            for j, mu2 in enumerate(muons):
                if i>j:
                    mu1Id = mu1.mediumId and mu1.pfIsoId>=2
                    if mu1.pt>=8. and abs(mu1.eta)<2.4 and mu1Id:
                        mu2Id = mu2.mediumId and mu2.pfIsoId>=2
                        if mu2.pt>=8. and abs(mu2.eta)<2.4 and mu2Id:
                            if mu1.charge*mu2.charge<0:
                                mumudr = abs(deltaPhi(mu1, mu2))>=0.28284271 and abs(mu1.eta-mu2.eta)>=0.28284271
                                if mumudr:
                                    Mass = (mu1.p4()+mu2.p4()).M()
                                    HavePair = HavePair+1
                                    Mu1Idx = i
                                    Mu2Idx = j
                                    for k, photon in enumerate(photons):
                                        if k in goodPhotonIdx:
                                            mu1dr = abs(deltaPhi(mu1, photon))>=0.28284271 and abs(mu1.eta-photon.eta)>=0.28284271
                                            mu2dr = abs(deltaPhi(mu2, photon))>=0.28284271 and abs(mu2.eta-photon.eta)>=0.28284271
                                            if mu1dr and mu2dr:
                                                if photon.pt>=maxphotonpt:
                                                    HaveTriplet = HaveTriplet + 1
                                                    MuMuGammaMass = (mu1.p4()+mu2.p4()+photon.p4()).M()
                                                    maxphotonpt = photon.pt
                                                    PhotonIdx = k

        #if MuMuMass>=50.:
        #    return False

        self.out.fillBranch("MuMu_HavePair", HavePair)
        self.out.fillBranch("MuMu_Mass", Mass)
        self.out.fillBranch("MuMu_HaveTriplet", HaveTriplet)
        self.out.fillBranch("MuMu_MuMuGammaMass", GammaMass)
        self.out.fillBranch("MuMu_PhotonIdx", PhotonIdx)
        self.out.fillBranch("MuMu_Mu1Idx", Mu1Idx)
        self.out.fillBranch("MuMu_Mu2Idx", Mu2Idx)
        return True, Mu1Idx, Mu2Idx

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuMuProducerConstr = lambda : MuMuProducer(
)

