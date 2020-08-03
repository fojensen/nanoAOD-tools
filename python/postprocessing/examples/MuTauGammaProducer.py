import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi
from ROOT import TLorentzVector, TVector2
import math

#from TauPOG.TauIDSFs.TauIDSFTool import TauIDSFTool
#tauSFTool_jet = TauIDSFTool('2018ReReco','DeepTau2017v2p1VSjet','VVTight')
#tauSFTool_ele = TauIDSFTool('2018ReReco','DeepTau2017v2p1VSe','VVTight')
#tauSFTool_muo = TauIDSFTool('2018ReReco','DeepTau2017v2p1VSmu','Tight')
#from TauPOG.TauIDSFs.TauIDSFTool import TauESTool
#testool_jet = TauESTool('2018ReReco','DeepTau2017v2p1VSjet')
#from TauPOG.TauIDSFs.TauIDSFTool import TauFESTool
#testool_ele = TauFESTool('2018ReReco','DeepTau2017v2p1VSe')

#from MuonPOG.MuonSFs.MuonSFTool import MuonSFTool
#muonSFTool = MuonSFTool()

class MuTauGammaProducer(Module):
    def __init__(self, isMC_):
        self.isMC__ = isMC_
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("MuTauGamma_havePair", "I")
        self.out.branch("MuTauGamma_qq", "I")
        self.out.branch("MuTauGamma_MuIdx", "I")
        self.out.branch("MuTauGamma_TauIdx", "I")
        self.out.branch("MuTauGamma_mt", "F")
        self.out.branch("MuTauGamma_mtg", "F")
        self.out.branch("MuTauGamma_MuTauMass", "F")
        self.out.branch("MuTauGamma_MuTauGammaMass", "F")
        self.out.branch("MuTauGamma_MuTauGammaCollinearMass", "F")
        self.out.branch("MuTauGamma_MuTauDeltaR", "F")
        self.out.branch("MuTauGamma_MuTauDeltaPhi", "F")
        self.out.branch("MuTauGamma_MuTauDeltaEta", "F")
        self.out.branch("MuTauGamma_MuTauCollinearMass", "F")
        self.out.branch("MuTauGamma_haveTriplet", "I")
        self.out.branch("MuTauGamma_PhotonIdx", "I")
        self.out.branch("MuTauGamma_MuGammaCollinearMass", "F")
        self.out.branch("MuTauGamma_TauGammaCollinearMass", "F")
        self.out.branch("MuTauGamma_ClosestCollinearMass", "F")
        self.out.branch("MuTauGamma_FurthestCollinearMass", "F")
        self.out.branch("MuTauGamma_transversemass", "F")
        self.out.branch("MuTauGamma_MuGammaDeltaR", "F")
        self.out.branch("MuTauGamma_MuGammaDeltaPhi", "F")
        self.out.branch("MuTauGamma_MuGammaDeltaEta", "F")
        self.out.branch("MuTauGamma_TauGammaDeltaR", "F")
        self.out.branch("MuTauGamma_TauGammaDeltaPhi", "F")
        self.out.branch("MuTauGamma_TauGammaDeltaEta", "F")
        self.out.branch("MuTauGamma_nGoodMuon", "I")
        self.out.branch("MuTauGamma_nGoodTau", "I")
        self.out.branch("MuTauGamma_nGoodPhoton", "I")
        if self.isMC__:
            self.out.branch("MuTauGamma_TauSFjet", "F")
            #self.out.branch("MuTauGammaProducer_TauSFele", "F")
            self.out.branch("MuTauGamma_TauSFmuo", "F")
            self.out.branch("MuTauGamma_TauESjet", "F")
            #self.out.branch("MuTauGammaProducer_TauESele", "F")
            self.out.branch("MuTauGamma_MuSFId", "F")
            self.out.branch("MuTauGamma_MuSFIso", "F")
            self.out.branch("MuTauGamma_MuSFTrigger", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        if self.isMC__:
            TauSFjet = TauSFmuo = 0
            TauESjet = 0
            MuSFId = MuSFIso = MuSFTrigger = 0

        havePair = 0
        qq = 0
        MuIdx = -1
        TauIdx = -1
        mt = 0
        mtg = 0
        MuTauMass = 0
        MuTauCollinearMass = 0
        MuTauDeltaR = 0
        MuTauDeltaPhi = 0
        MuTauDeltaEta = 0
        haveTriplet = 0
        PhotonIdx = -1
        MuGammaCollinearMass = 0
        TauGammaCollinearMass = 0 
        MuTauGammaCollinearMass = 0
        MuTauGammaMass = 0
        ClosestCollinearMass = 0
        FurthestCollinearMass = 0
        MuGammaDeltaR = 0
        MuGammaDeltaPhi = 0
        MuGammaDeltaEta = 0
        TauGammaDeltaR = 0
        TauGammaDeltaPhi = 0
        TauGammaDeltaEta = 0
        nGoodMuon = 0
        nGoodTau = 0
        nGoodPhoton = 0
        transversemass = 0

        photons = Collection(event, "Photon")
        muons = Collection(event, "Muon")
        taus = Collection(event, "Tau") 
  
        goodMuonIdx = []
        for i, mu in enumerate(muons):
            muonID = mu.mediumId and mu.pfIsoId>=4
            if mu.pt>=27. and abs(mu.eta)<2.4 and muonID:
                goodMuonIdx.append(i)
        nGoodMuon = len(goodMuonIdx)

        goodTauIdx = []
        for i, tau in enumerate(taus):
            tauID = (8&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu)
            tauID = tauID and not (tau.decayMode==5 or tau.decayMode==6)
            if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                goodTauIdx.append(i)
        nGoodTau = len(goodTauIdx)

        goodPhotonIdx = []
        for i, photon in enumerate(photons):
            photonID = photon.mvaID_WP90 and photon.electronVeto
            if photon.pt>=32. and abs(photon.eta)<2.5 and photonID:
                goodPhotonIdx.append(i)
        nGoodPhoton = len(goodPhotonIdx)

        maxtauiso = 0
        maxmuiso = 0
        for i, mu in enumerate(muons):
            if i in goodMuonIdx:
                for j, tau in enumerate(taus):
                    if j in goodTauIdx:
                        if abs(deltaPhi(mu.phi, tau.phi))>=0.3:
                            havePair = havePair+1
                            if tau.idDeepTau2017v2p1VSjet>maxtauiso: # select most isolated tau
                                if mu.pfIsoId>maxmuiso: # select most isolated muon
                                    maxtauiso = tau.idDeepTau2017v2p1VSjet
                                    maxmuiso = mu.pfIsoId
                                    MuIdx = i
                                    TauIdx = j
                                    qq = mu.charge*tau.charge
                                    MuTauMass = (mu.p4()+tau.p4()).M()
                                    MuTauDeltaR = deltaR(mu, tau)
                                    mt = 2. * event.MET_pt * mu.pt * (1-math.cos(deltaPhi(event.MET_phi, mu.phi)))
                                    mt = math.sqrt(mt)
                              
                                    #collinear approximation 
                                    nu0 = TLorentzVector()
                                    nu1 = TLorentzVector()
                                    cos0M = math.cos(deltaPhi(tau.phi, event.MET_phi));
                                    cos1M = math.cos(deltaPhi(mu.phi, event.MET_phi));
                                    cos01 = math.cos(deltaPhi(tau.phi, mu.phi));
                                    nu0mag = event.MET_pt * (cos0M-cos1M*cos01) / (1.-cos01*cos01);
                                    nu1mag = (event.MET_pt*cos1M) - (nu0mag*cos01);
                                    nu0.SetPtEtaPhiM(nu0mag, tau.eta, tau.phi, 0.)
                                    nu1.SetPtEtaPhiM(nu1mag, mu.eta, mu.phi, 0.)
                                    MuTauCollinearMass = (mu.p4()+nu0+tau.p4()+nu1).M()

                                    maxphotonpt = 0
                                    for k, photon in enumerate(photons):
                                        if k in goodPhotonIdx:
                                            isIso = abs(deltaPhi(mu, photon))>=0.3 and abs(deltaPhi(tau, photon))>=0.3
                                            if isIso:
                                                haveTriplet = haveTriplet+1
                                                if photon.pt>maxphotonpt: #select highest pt photon
                                                    PhotonIdx = k
                                                    maxphotonpt = photon.pt
                                                    MuGammaDeltaPhi = deltaPhi(mu.phi, photon.phi)
                                                    MuGammaDeltaEta = mu.eta-photon.eta
                                                    TauGammaDeltaPhi = deltaPhi(tau.phi, photon.phi)
                                                    TauGammaDeltaEta = tau.eta-photon.eta
                                                    #print i, j, k, mu.pt, tau.pt, photon.pt
                                                    MuGammaDeltaR = deltaR(mu, photon)
                                                    TauGammaDeltaR = deltaR(tau, photon)
                                                    TauGammaCollinearMass = (tau.p4()+nu0+photon.p4()).M()
                                                    MuGammaCollinearMass = (mu.p4()+nu1+photon.p4()).M()
                                                    MuTauGammaMass = (tau.p4()+mu.p4()+photon.p4()).M()
                                                    metv = TVector2()
                                                    metv.SetMagPhi(event.MET_pt, event.MET_phi)
                                                    gammav = TVector2()
                                                    gammav.SetMagPhi(photon.pt, photon.phi)   
                                                    tauv = TVector2()
                                                    tauv.SetMagPhi(tau.pt, tau.phi)
                                                    muv = TVector2()
                                                    muv.SetMagPhi(mu.pt, mu.phi) 
                                                    sumv = gammav+metv+tauv+muv
                                                    transversemass = sumv.Mod()
                                                    MuTauGammaCollinearMass = (tau.p4()+nu0+mu.p4()+nu1+photon.p4()).M()
                                                    mtg = 2. * event.MET_pt * (mu.p4()+photon.p4()).Pt() * (1-math.cos(deltaPhi(event.MET_phi, (mu.p4()+photon.p4()).Phi())))
                                                    mtg = math.sqrt(mtg)
                                                    if deltaR(mu, photon) < deltaR(tau, photon):
                                                        ClosestCollinearMass = MuGammaCollinearMass
                                                        FurthestCollinearMass = TauGammaCollinearMass
                                                    else :
                                                        ClosestCollinearMass = TauGammaCollinearMass
                                                        FurthestCollinearMass = MuGammaCollinearMass
 
        #print "haveTriplet: ", haveTriplet 
        self.out.fillBranch("MuTauGamma_havePair", havePair)
        self.out.fillBranch("MuTauGamma_qq", qq)
        self.out.fillBranch("MuTauGamma_MuIdx", MuIdx)
        self.out.fillBranch("MuTauGamma_TauIdx", TauIdx)
        self.out.fillBranch("MuTauGamma_mt", mt)
        self.out.fillBranch("MuTauGamma_mtg", mtg)
        self.out.fillBranch("MuTauGamma_MuTauMass", MuTauMass)
        self.out.fillBranch("MuTauGamma_MuTauCollinearMass", MuTauCollinearMass)
        self.out.fillBranch("MuTauGamma_MuTauDeltaR", MuTauDeltaR)
        self.out.fillBranch("MuTauGamma_MuTauDeltaPhi", MuTauDeltaPhi)
        self.out.fillBranch("MuTauGamma_MuTauDeltaEta", MuTauDeltaEta)
        self.out.fillBranch("MuTauGamma_haveTriplet", haveTriplet)
        self.out.fillBranch("MuTauGamma_PhotonIdx", PhotonIdx)
        self.out.fillBranch("MuTauGamma_MuGammaCollinearMass", MuGammaCollinearMass)
        self.out.fillBranch("MuTauGamma_TauGammaCollinearMass", TauGammaCollinearMass)
        self.out.fillBranch("MuTauGamma_MuTauGammaCollinearMass", MuTauGammaCollinearMass)
        self.out.fillBranch("MuTauGamma_MuTauGammaMass", MuTauGammaMass)
        self.out.fillBranch("MuTauGamma_ClosestCollinearMass", ClosestCollinearMass)
        self.out.fillBranch("MuTauGamma_FurthestCollinearMass", FurthestCollinearMass)
        self.out.fillBranch("MuTauGamma_MuGammaDeltaR", MuGammaDeltaR)
        self.out.fillBranch("MuTauGamma_MuGammaDeltaPhi", MuGammaDeltaPhi)
        self.out.fillBranch("MuTauGamma_MuGammaDeltaEta", MuGammaDeltaEta)
        self.out.fillBranch("MuTauGamma_TauGammaDeltaR", TauGammaDeltaR)
        self.out.fillBranch("MuTauGamma_TauGammaDeltaPhi", TauGammaDeltaPhi)
        self.out.fillBranch("MuTauGamma_TauGammaDeltaEta", TauGammaDeltaEta)
        self.out.fillBranch("MuTauGamma_nGoodMuon", nGoodMuon)
        self.out.fillBranch("MuTauGamma_nGoodTau", nGoodTau)
        self.out.fillBranch("MuTauGamma_nGoodPhoton", nGoodPhoton)
        self.out.fillBranch("MuTauGamma_transversemass", transversemass)
 
        if self.isMC__:
            self.out.fillBranch("MuTauGamma_TauSFjet", TauSFjet)
            #self.out.fillBranch("MuTauGammaProducer_TauSFele", TauSFele)
            self.out.fillBranch("MuTauGamma_TauSFmuo", TauSFmuo)
            self.out.fillBranch("MuTauGamma_TauESjet", TauESjet)
            #self.out.fillBranch("MuTauGammaProducer_TauESele", TauESele)
            self.out.fillBranch("MuTauGamma_MuSFId", MuSFId)
            self.out.fillBranch("MuTauGamma_MuSFIso", MuSFIso)
            self.out.fillBranch("MuTauGamma_MuSFTrigger", MuSFTrigger)   
   
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuTauGammaProducerConstr = lambda isMC : MuTauGammaProducer(
    isMC_ = isMC
)

