import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi
from ROOT import TLorentzVector, TVector2
import math
from TauPOG.TauIDSFs.TauIDSFTool import TauIDSFTool
from MuonPOG.MuonSFs.MuonSFTool import MuonSFTool

class MuTauGammaProducer(Module):
    def __init__(self, isMC_, isEmb_, year_):
        print "init is being called"
        self.isMC__ = isMC_
        self.isEmb__ = isEmb_
        self.year__ = year_

        if self.isMC__ or self.isEmb__:
            self.muonSFTool = MuonSFTool(self.year__)
         
            if self.year__=="2016":
                tauTag= '2016Legacy'
            elif self.year__=="2017":
                tauTag= '2017ReReco'
            elif self.year__=="2018":
                tauTag= '2018ReReco'
            else :
                print "Funny year is chosen!"
            #(self, year, id, wp='Tight', dm=False, emb=False, otherVSlepWP=False, path=datapath, verbose=False)
            self.tauIDSFTool_jet_VVVLoose = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','VVVLoose', False,  isEmb_)
            self.tauIDSFTool_jet_VVLoose = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','VVLoose', False, isEmb_)
            self.tauIDSFTool_jet_VLoose = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','VLoose', False, isEmb_)
            self.tauIDSFTool_jet_Loose = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','Loose', False, isEmb_)
            self.tauIDSFTool_jet_Medium = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','Medium', False, isEmb_)
            self.tauIDSFTool_jet_Tight = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','Tight', False, isEmb_)
            self.tauIDSFTool_jet_VTight = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','VTight', False, isEmb_)
            self.tauIDSFTool_jet_VVTight = TauIDSFTool(tauTag,'DeepTau2017v2p1VSjet','VVTight', False, isEmb_)
            self.tauIDSFTool_muo = TauIDSFTool(tauTag,'DeepTau2017v2p1VSmu','Tight')
            self.tauIDSFTool_ele = TauIDSFTool(tauTag,'DeepTau2017v2p1VSe','VLoose')
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
        self.out.branch("MuTauGamma_MuTauPt", "F")
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
        self.out.branch("MuTauGamma_trigger", "O")
        self.out.branch("MuTauGamma_MuGammaMass", "F")
        self.out.branch("MuTauGamma_TauGammaMass", "F")
        if self.isMC__ or self.isEmb__:
            self.out.branch("MuTauGamma_TauSFjet", "F", 8, None, None)
        if self.isEmb__:
            self.out.branch("MuTauGamma_trkEff", "F")
            self.out.branch("MuTauGamma_gt1_pt", "F")
            self.out.branch("MuTauGamma_gt1_eta", "F")
            self.out.branch("MuTauGamma_gt2_pt", "F")
            self.out.branch("MuTauGamma_gt2_eta", "F")
            self.out.branch("MuTauGamma_nGenTau", "I")
        if self.isMC__:
            self.out.branch("MuTauGamma_MuSFId", "F")
            self.out.branch("MuTauGamma_MuSFIso", "F", 2, None, None)
            self.out.branch("MuTauGamma_MuSFTrigger", "F")
            self.out.branch("MuTauGamma_TauSFmuo", "F")
            self.out.branch("MuTauGamma_TauSFele", "F")
      

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        havePair = 0
        qq = 0
        MuIdx = -1
        TauIdx = -1
        mt = 0
        mtg = 0
        MuTauMass = MuTauPt = 0
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
        trigger = False
        MuGammaMass = TauGammaMass = 0
   
        photons = Collection(event, "Photon")
        muons = Collection(event, "Muon")
        taus = Collection(event, "Tau")

        if self.year__=="2016":
            trigger = event.HLT_IsoMu24 or event.HLT_IsoTkMu24
        elif self.year__=="2017":
            trigger = event.HLT_IsoMu27 or event.HLT_IsoMu24
        elif self.year__=="2018":
            trigger = event.HLT_IsoMu27 or event.HLT_IsoMu24

        if self.isMC__ or self.isEmb__:
            TauSFjet = [0, 0, 0, 0, 0, 0, 0, 0]
        if self.isEmb__:
            trkEff = 0
            nGenTau = 0
            gt1_pt = gt1_eta = gt2_pt = gt2_eta = 0
            gens = Collection(event, "GenPart")
            for gen in gens:
               if abs(gen.pdgId)==15 and (8192&gen.statusFlags):
                   if nGenTau==0:
                       gt1_pt = gen.pt
                       gt1_eta = gen.eta
                   if nGenTau==1:
                       gt2_pt = gen.pt
                       gt2_eta = gen.eta
                   nGenTau = nGenTau + 1

        if self.isMC__:
            MuSFId = MuSFTrigger = 0
            MuSFIso = [0, 0]
            TauSFmuo = TauSFele = 0

        goodMuonIdx = []
        for i, mu in enumerate(muons):
            muonID = mu.mediumId and mu.pfIsoId>=1
            if mu.pt>=27. and abs(mu.eta)<2.4 and muonID:
                goodMuonIdx.append(i)
        nGoodMuon = len(goodMuonIdx)

        goodTauIdx = []
        for i, tau in enumerate(taus):
            tauID = (1&tau.idDeepTau2017v2p1VSjet) and (8&tau.idDeepTau2017v2p1VSmu) and (4&tau.idDeepTau2017v2p1VSe)
            tauID = tauID and not (tau.decayMode==5 or tau.decayMode==6)
            if tau.pt>=20. and abs(tau.eta)<2.3 and tauID:
                goodTauIdx.append(i)
        nGoodTau = len(goodTauIdx)

        goodPhotonIdx = []
        for i, photon in enumerate(photons):
            photonID = photon.mvaID_WP90 and photon.electronVeto
            if abs(photon.eta)<2.5 and photonID: 
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
                                maxtauiso = tau.idDeepTau2017v2p1VSjet
                                TauIdx = j
                                if mu.pfIsoId>maxmuiso: # select most isolated muon
                                    maxmuiso = mu.pfIsoId
                                    MuIdx = i
                                    qq = mu.charge*tau.charge
                                    MuTauMass = (mu.p4()+tau.p4()).M()
                                    MuTauPt = (mu.p4()+tau.p4()).Pt()
                                    MuTauDeltaR = deltaR(mu, tau)
                                    MuTauDeltaPhi = deltaPhi(mu, tau)
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

                                    if self.isMC__ or self.isEmb__:
                                        TauSFjet[0] = self.tauIDSFTool_jet_VVVLoose.getSFvsPT(tau.pt, tau.genPartFlav)
                                        TauSFjet[1] =  self.tauIDSFTool_jet_VVLoose.getSFvsPT(tau.pt, tau.genPartFlav)
                                        TauSFjet[2] =   self.tauIDSFTool_jet_VLoose.getSFvsPT(tau.pt, tau.genPartFlav)     
                                        TauSFjet[3] =    self.tauIDSFTool_jet_Loose.getSFvsPT(tau.pt, tau.genPartFlav)
                                        TauSFjet[4] =   self.tauIDSFTool_jet_Medium.getSFvsPT(tau.pt, tau.genPartFlav)
                                        TauSFjet[5] =    self.tauIDSFTool_jet_Tight.getSFvsPT(tau.pt, tau.genPartFlav)
                                        TauSFjet[6] =   self.tauIDSFTool_jet_VTight.getSFvsPT(tau.pt, tau.genPartFlav)
                                        TauSFjet[7] =  self.tauIDSFTool_jet_VVTight.getSFvsPT(tau.pt, tau.genPartFlav)
                                    if self.isEmb__:
                                        if tau.decayMode==0: trkEff = 0.975
                                        if tau.decayMode==1: trkEff = 0.975*1.051
                                        if tau.decayMode==10: trkEff = 0.975*0.975*0.975
                                        if tau.decayMode==11: trkEff = 0.975*0.975*0.975
                                    if self.isMC__:
                                        MuSFIso[0] = self.muonSFTool.getSF_LooseRelIso_MediumID(mu.pt, mu.eta)
                                        MuSFIso[1] = self.muonSFTool.getSF_TightRelIso_MediumID(mu.pt, mu.eta)
                                        MuSFId = self.muonSFTool.getSF_MediumID(mu.pt, mu.eta)
                                        MuSFTrigger = self.muonSFTool.getSF_Trigger(mu.pt, mu.eta)
                                        TauSFmuo = self.tauIDSFTool_muo.getSFvsEta(tau.pt, tau.genPartFlav)
                                        TauSFele = self.tauIDSFTool_ele.getSFvsEta(tau.pt, tau.genPartFlav)

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
                                                    MuGammaDeltaR = deltaR(mu, photon)
                                                    TauGammaDeltaR = deltaR(tau, photon)
                                                    TauGammaCollinearMass = (tau.p4()+nu0+photon.p4()).M()
                                                    MuGammaCollinearMass = (mu.p4()+nu1+photon.p4()).M()
                                                    MuTauGammaMass = (tau.p4()+mu.p4()+photon.p4()).M()
                                                    TauGammaMass = (tau.p4()+photon.p4()).M()
                                                    MuGammaMass = (mu.p4()+photon.p4()).M()
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
 
        self.out.fillBranch("MuTauGamma_havePair", havePair)
        self.out.fillBranch("MuTauGamma_qq", qq)
        self.out.fillBranch("MuTauGamma_MuIdx", MuIdx)
        self.out.fillBranch("MuTauGamma_TauIdx", TauIdx)
        self.out.fillBranch("MuTauGamma_mt", mt)
        self.out.fillBranch("MuTauGamma_mtg", mtg)
        self.out.fillBranch("MuTauGamma_MuTauMass", MuTauMass)
        self.out.fillBranch("MuTauGamma_MuTauPt", MuTauPt)
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
        self.out.fillBranch("MuTauGamma_MuGammaMass", MuGammaMass)
        self.out.fillBranch("MuTauGamma_TauGammaMass", TauGammaMass)
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
        self.out.fillBranch("MuTauGamma_trigger", trigger)
 
        if self.isMC__ or self.isEmb__:
            self.out.fillBranch("MuTauGamma_TauSFjet", TauSFjet)
        if self.isEmb__:
            self.out.fillBranch("MuTauGamma_trkEff", trkEff)
            self.out.fillBranch("MuTauGamma_gt1_pt", gt1_pt)
            self.out.fillBranch("MuTauGamma_gt1_eta", gt1_eta)
            self.out.fillBranch("MuTauGamma_gt2_pt", gt2_pt)
            self.out.fillBranch("MuTauGamma_gt2_eta", gt2_eta)
            self.out.fillBranch("MuTauGamma_nGenTau", nGenTau)
        if self.isMC__:
            self.out.fillBranch("MuTauGamma_MuSFId", MuSFId)
            self.out.fillBranch("MuTauGamma_MuSFIso", MuSFIso)
            self.out.fillBranch("MuTauGamma_MuSFTrigger", MuSFTrigger) 
            self.out.fillBranch("MuTauGamma_TauSFmuo", TauSFmuo)
            self.out.fillBranch("MuTauGamma_TauSFele", TauSFele)
   
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuTauGammaProducerConstr = lambda isMC, isEmb, year : MuTauGammaProducer(
    isMC_ = isMC,
    isEmb_ = isEmb,
    year_ = year
)

