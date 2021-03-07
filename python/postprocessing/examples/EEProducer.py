import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR, deltaPhi

class EEProducer(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("EE_HavePair", "I")
        self.out.branch("EE_Mass", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #print "beginning ZProducer"

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#Electron
        HavePair = 0
        Mass = 0.
        electrons = Collection(event, "Electron")
        for i, e1 in enumerate(electrons):
            for j, e2 in enumerate(electrons):
                if i>j:
                    e1Id = e1.mvaFall17V2Iso_WP90
                    if e1.pt>=12. and abs(e1.eta)<2.5 and e1Id:
                        e2Id = e2.mvaFall17V2Iso_WP90
                        if e2.pt>=12. and abs(e2.eta)<2.5 and e2Id:
                            if e1.charge*e2.charge<0:
                                if abs(deltaPhi(e1, e2))>=0.28284271 and abs(e1.eta-e2.eta)>=0.28284271:
                                    Mass = (e1.p4()+e2.p4()).M()
                                    HavePair = HavePair+1
        if Mass>=50.:
            return False

        self.out.fillBranch("EE_HavePair", HavePair)
        self.out.fillBranch("EE_Mass", Mass)
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

EEProducerConstr = lambda : EEProducer(
)

