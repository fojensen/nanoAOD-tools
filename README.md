#Tau HATS@LPC
ttps://indico.cern.ch/event/917686/


## Install CMSSW and clone NanoAODTools
```
cmsrel CMSSW_10_2_18  
cd CMSSW_10_2_18/src/  
cmsenv  

git clone --single-branch --branch tauHats https://github.com/fojensen/nanoAOD-tools.git  
scram build -j 4
```

## tau ID efficiency
###using truth information, calculate the signal efficiency in WJetsToLNu MC
```
root
.L eff.c+
eff(true);
###using truth information, calculate the signal efficiency in QCD MC

