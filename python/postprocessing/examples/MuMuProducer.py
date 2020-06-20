import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

class MuMuProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("MuMuProducer_HavePair", "I")
        self.out.branch("MuMuProducer_Mass", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #print "beginning MuMuProducer"

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html
        HavePair = 0
        Mass = 0
        #https://twiki.cern.ch/CMS/SWGuideMuonIdRun2 
        muons = Collection(event, "Muon")
        for mu1 in muons:
            mu1Id = mu1.tightId and mu1.pfIsoId>=4
            if mu1.pt>=27. and abs(mu1.eta)<2.4 and mu1Id:
                for mu2 in muons:
                    mu2Id = mu2.mediumId and mu2.pfIsoId>=2
                    if mu2.pt>=20. and abs(mu2.eta)<2.4 and mu2Id:
                        if (mu1.charge*mu2.charge)<0:
                            Mass = (mu1.p4()+mu2.p4()).M()
                            HavePair = HavePair+1

        #if HavePair:
        #    return False
        self.out.fillBranch("MuMuProducer_HavePair", HavePair)
        self.out.fillBranch("MuMuProducer_Mass", Mass)
        #print "ending MuMuProducer, return True"
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

MuMuProducerConstr = lambda : MuMuProducer(
)

