import ROOT
import math
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection 
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import deltaPhi

class ZVeto(Module):
    def __init__(self):
        pass
    def beginJob(self):
        pass
    def endJob(self):
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass

    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#Electron
        electrons = Collection(event, "Electron")
        for e1 in electrons:
            if e1.pt>=12. and abs(e1.eta)<2.5 and e1.mvaFall17V2Iso_WP90:
                for e2 in electrons:
                    if e2.pt>=12. and abs(e2.eta)<2.5 and e2.mvaFall17V2Iso_WP90:
                        if e1.charge*e2.charge<0:
                            if abs(deltaPhi(e1, e2))>=0.28284271 and abs(e1.eta-e2.eta)>=0.28284271:
                                EEMass = (e1.p4()+e2.p4()).M()
                                if EEMass>=50.:
                                    return False

        #https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#Muon
        muons = Collection(event, "Muon")
        for mu1 in muons:
            if mu1.pt>=8. and abs(mu1.eta)<2.4 and mu1.looseId and mu1.pfIsoId>=2:
                for mu2 in muons:
                    if mu2.pt>=8. and abs(mu2.eta)<2.4 and mu2.looseId and mu2.pfIsoId>=2:
                        if mu1.charge*mu2.charge<0:
                            if abs(deltaPhi(mu1, mu2))>=0.28284271 and abs(mu1.eta-mu2.eta)>=0.28284271:
                                MuMuMass = (mu1.p4()+mu2.p4()).M()
                                if MuMuMass>=50.:
                                    return False

        return True

# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ZVetoConstr = lambda : ZVeto(
)

