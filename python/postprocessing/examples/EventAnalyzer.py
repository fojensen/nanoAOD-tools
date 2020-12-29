import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
#from PhysicsTools.NanoAODTools.postprocessing.tools import deltaR
#https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html

class EventAnalyzer(Module):
    def __init__(self):
        self.writeHistFile=True
    def beginJob(self,histFile=None,histDirName=None):
        Module.beginJob(self,histFile,histDirName) 
        self.h_HT = ROOT.TH1F('h_HT', ';HT;events / 50 GeV', 10, 0, 500)
        self.addObject(self.h_HT)
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):

        self.out = wrappedOutputTree
        self.out.branch("eventAnalyzer_nJets", "I")
        self.out.branch("eventAnalyzer_nBJets", "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
   
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#Muon
        jets = Collection(event, "Jet")
        eventAnalyzer_nJets = eventAnalyzer_nBJets = 0
        HT = 0
        for jet in jets:
           if jet.pt>=20. and abs(jet.eta)<2.5:
               ++eventAnalyzer_nJets
               HT += jet.pt
               #https://twiki.cern.ch/CMS/BtagRecommendation102X 
               if jet.btagDeepB>=0.1241: 
                   ++eventAnalyzer_nBJets

        ##if eventAnalyzer_nBJets==0: return False

        self.h_HT.Fill(HT)

        self.out.fillBranch("eventAnalyzer_nJets", eventAnalyzer_nJets)
        self.out.fillBranch("eventAnalyzer_nBJets", eventAnalyzer_nBJets)
 
        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

EventAnalyzerConstr = lambda : EventAnalyzer(
)

