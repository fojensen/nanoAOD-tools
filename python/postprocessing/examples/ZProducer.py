import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

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
        #print "beginning MuMuProducer"

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        MuMuHavePair = 0
        MuMuMass = 0
        muons = Collection(event, "Muon")
        for mu1 in muons:
            mu1Id = mu1.mediumId and mu1.pfIsoId>=2
            if mu1.pt>=10. and abs(mu1.eta)<2.4 and mu1Id:
                for mu2 in muons:
                    mu2Id = mu2.mediumId and mu2.pfIsoId>=2
                    if mu2.pt>=10. and abs(mu2.eta)<2.4 and mu2Id:
                        if (mu1.charge*mu2.charge)<0:
                            MuMuMass = (mu1.p4()+mu2.p4()).M()
                            MuMuHavePair = MuMuHavePair+1

        self.out.fillBranch("ZProducer_MuMuHavePair", MuMuHavePair)
        self.out.fillBranch("ZProducer_MuMuMass", MuMuMass)

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        EEHavePair = 0
        EEMass = 0
        electrons = Collection(event, "Electron")
        for e1 in electrons:
            e1Id = e1.mvaFall17V2Iso_WP90
            if e1.pt>=10. and abs(e1.eta)<2.5 and e1Id:
                for e2 in electrons:
                    e2Id = e2.mvaFall17V2Iso_WP90
                    if e2.pt>=10. and abs(e2.eta)<2.5 and e2Id:
                        if (e1.charge*e2.charge)<0:
                            EEMass = (e1.p4()+e2.p4()).M()
                            EEHavePair = EEHavePair+1

        self.out.fillBranch("ZProducer_EEHavePair", EEHavePair)
        self.out.fillBranch("ZProducer_EEMass", EEMass)

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ZProducerConstr = lambda : ZProducer(
)

