#Tau HATS@LPC
https://indico.cern.ch/event/917686/


## Install CMSSW and clone NanoAODTools

cmsrel CMSSW_10_2_18  
cd CMSSW_10_2_18/src/  
cmsenv  
git clone --single-branch --branch tauHats https://github.com/fojensen/nanoAOD-tools.git  
scram build -j 4

## tau ID efficiency and mistag rate in MC, using truth information
###calculate the signal efficiency in WJetsToLNu MC

cd CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/analysis
root
.L eff.c+
eff(true)
         
###calculate the signal efficiency in QCD MC
root
.L eff.c+
eff(false)

###calculate the roc curve
root roc.c+

## tau ID mistag rate in data

### submit jobs to crab

### make stack plots
root makeStackPlots.c+



