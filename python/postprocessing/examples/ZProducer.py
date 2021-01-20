import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR

class ZProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("ZProducer_MuMuHavePair", "I")
        self.out.branch("ZProducer_MuMuMass", "F")
        self.out.branch("ZProducer_EEHavePair", "I")
        self.out.branch("ZProducer_EEMass", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #print "beginning ZProducer"

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#Electron
        EEHavePair = 0
        EEMass = 0.
        electrons = Collection(event, "Electron")
        for i, e1 in enumerate(electrons):
            for j, e2 in enumerate(electrons):
                if i>j:
                    e1Id = e1.mvaFall17V2Iso_WP90
                    if e1.pt>=12. and abs(e1.eta)<2.5 and e1Id:
                        e2Id = e2.mvaFall17V2Iso_WP90
                        if e2.pt>=12. and abs(e2.eta)<2.5 and e2Id:
                            if (e1.charge*e2.charge<0 and deltaR(e1, e2)>=0.1):
                                EEMass = (e1.p4()+e2.p4()).M()
                                EEHavePair = EEHavePair+1
        if EEMass>=50.:
            return False

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#Muon
        MuMuHavePair = 0
        MuMuMass = 0.
        muons = Collection(event, "Muon")
        for i, mu1 in enumerate(muons):
            for j, mu2 in enumerate(muons):
                if i>j:
                    mu1Id = mu1.mediumId and mu1.pfIsoId>=2
                    if mu1.pt>=8. and abs(mu1.eta)<2.4 and mu1Id:
                        mu2Id = mu2.mediumId and mu2.pfIsoId>=2
                        if mu2.pt>=8. and abs(mu2.eta)<2.4 and mu2Id:
                            if (mu1.charge*mu2.charge<0 and deltaR(mu1, mu2)>=0.1):
                                MuMuMass = (mu1.p4()+mu2.p4()).M()
                                MuMuHavePair = MuMuHavePair+1
        if MuMuMass>=50.:
             return False

        self.out.fillBranch("ZProducer_EEHavePair", EEHavePair)
        self.out.fillBranch("ZProducer_EEMass", EEMass)
        self.out.fillBranch("ZProducer_MuMuHavePair", MuMuHavePair)
        self.out.fillBranch("ZProducer_MuMuMass", MuMuMass)
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ZProducerConstr = lambda : ZProducer(
)

