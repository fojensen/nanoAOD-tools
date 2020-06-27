# Tau HATS@LPC
https://indico.cern.ch/event/917686/

## Install CMSSW and clone NanoAODTools
```
cmsrel CMSSW_10_2_18  
cd /CMSSW_10_2_18/src/  
cmsenv  
git clone --single-branch --branch tauHats https://github.com/fojensen/nanoAOD-tools.git  
scram build -j 4
```

### tau ID efficiency and mistag rate in MC, using truth information

#### calculate the signal efficiency in WJetsToLNu MC
```
cd /CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/analysis/
root
.L eff.c+
eff(true)
```

#### calculate the signal efficiency in QCD MC
```
cd /CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/analysis/
root
.L eff.c+
eff(false)
```

#### calculate the roc curve
```
cd /CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/analysis/
root roc.c+
```

## tau ID mistag rate in data

### submit jobs to crab
preselection is seen here: https://github.com/fojensen/nanoAOD-tools/blob/tauHats/crab/crab_script.py#L21-L27
```
cd /CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/crab/
python samples.py
python submitToCrab.py
```
... let jobs run ...

#### hadd the job output and splitDY
you need to manually add the correct path from eos into haddSamples.sh
```
cd /CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/analysis/
source haddSamples.sh
```

### make stack plots
```
cd /CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/analysis/
root makeStackPlots.c+
```

### calculate the fake rate
```
cd /CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/analysis/
root jetFake.c+
```

# Z->tautau->tau_{mu}tau_{h} analysis

### install Higgs Combine, follow recipe here:
https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/

### plot visible mass, extract (inclusive) expected yields
```
root makeHists.c+
```

### run combine to calculate significance
first, update datacard.txt with expected yields
```
combine -d datacard.txt -M Significance
```

