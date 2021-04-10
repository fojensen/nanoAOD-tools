import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaPhi

class ZProducer(Module):
    def __init__(self, applyFilter_):
        self.applyFilter__ = applyFilter_
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("EE_HavePair", "O")
        self.out.branch("EE_Mass", "F")
        self.out.branch("MuMu_HavePair", "O")
        self.out.branch("MuMu_Mass", "F")
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass

    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        EE_HavePair = MuMu_HavePair = False
        EE_Mass = MuMu_Mass = 0

        electrons = Collection(event, "Electron")
        for e1 in electrons:
            for e2 in electrons:
                if e1.charge*e2.charge<0:
                    if e1.pt>=12. and abs(e1.eta)<2.5 and e1.mvaFall17V2noIso_WP90:
                        if e2.pt>=12. and abs(e2.eta)<2.5 and e2.mvaFall17V2noIso_WP90:
                            if abs(deltaPhi(e1, e2))>=0.28284271 and abs(e1.eta-e2.eta)>=0.28284271:
                                EE_Mass = (e1.p4()+e2.p4()).M()
                                if self.applyFilter__ and EE_Mass>=50.: return False
                                EE_HavePair = True

        muons = Collection(event, "Muon")
        for mu1 in muons:
            for mu2 in muons:
                if mu1.charge*mu2.charge<0:
                    if mu1.pt>=8. and abs(mu1.eta)<2.4 and mu1.mediumId:
                        if mu2.pt>=8. and abs(mu2.eta)<2.4 and mu2.mediumId:
                            if abs(deltaPhi(mu1, mu2))>=0.28284271 and abs(mu1.eta-mu2.eta)>=0.28284271:
                                MuMu_Mass = (mu1.p4()+mu2.p4()).M()
                                if self.applyFilter__ and MuMu_Mass>=50.: return False
                                MuMu_HavePair = True

        self.out.fillBranch("EE_HavePair", EE_HavePair)
        self.out.fillBranch("EE_Mass", EE_Mass)
        self.out.fillBranch("MuMu_HavePair", MuMu_HavePair)
        self.out.fillBranch("MuMu_Mass", MuMu_Mass)

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ZProducerConstr = lambda applyFilter : ZProducer(
    applyFilter_ = applyFilter
)

