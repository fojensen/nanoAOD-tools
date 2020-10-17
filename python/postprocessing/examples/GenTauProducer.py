import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

class GenTauProducer(Module):
    def __init__(self):
        print "GenTauProducer init is being called."
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("GenTau_nGenTau", "I")
        self.out.branch("GenTau_gt1_pt", "F")
        self.out.branch("GenTau_gt1_eta", "F")
        self.out.branch("GenTau_gt2_pt", "F")
        self.out.branch("GenTau_gt2_eta", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        nGenTau = 0
        gt1_pt = gt1_eta = gt2_pt = gt2_eta = 0
        gens = Collection(event, "GenPart")
        for gen in gens:
            if abs(gen.pdgId)==15:
                if (8192&gen.statusFlags) and ((1&gen.statusFlags) or (128&gen.statusFlags) or (256&gen.statusFlags)):
                    if nGenTau==0:
                        gt1_pt = gen.pt
                        gt1_eta = gen.eta
                    if nGenTau==1:
                        gt2_pt = gen.pt
                        gt2_eta = gen.eta
                    nGenTau = nGenTau + 1 
        if nGenTau>2:
            print "nGenTau: ", nGenTau

        self.out.fillBranch("GenTau_nGenTau", nGenTau)
        self.out.fillBranch("GenTau_gt1_pt", gt1_pt)
        self.out.fillBranch("GenTau_gt1_eta", gt1_eta)
        self.out.fillBranch("GenTau_gt2_pt", gt2_pt)
        self.out.fillBranch("GenTau_gt2_eta", gt2_eta)
   
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed
GenTauProducerConstr = lambda : GenTauProducer()


