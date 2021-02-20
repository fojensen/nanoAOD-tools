import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
class xsWeightProducer(Module):
    def __init__(self, xsWeight_):
        #pass
        self.xsWeight = xsWeight_
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("xsWeight", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""
        #xsWeight = 1. 
        self.out.fillBranch("xsWeight", self.xsWeight)
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed


#xsWeightProducerConstr = lambda : xsWeightProducer(xsWeight
#)

