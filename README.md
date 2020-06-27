# Tau HATS@LPC
useful links:
* indico agenda: https://indico.cern.ch/event/917686/
* DeepTau documentation: http://cms.cern.ch/iCMS/analysisadmin/cadilines?line=TAU-20-001
* Tau ID twiki for Run2: https://twiki.cern.ch/CMS/TauIDRecommendationForRun2

### Install CMSSW and clone NanoAODTools
```
cmsrel CMSSW_10_2_18  
cd /CMSSW_10_2_18/src/  
cmsenv  
git clone --single-branch --branch tauHats https://github.com/fojensen/nanoAOD-tools.git  
scram build -j 4
```

# DeepTau tagging efficiencies

## tagging efficiencies in MC, using truth information

### signal efficiency in WJetsToLNu MC
```
cd $CMSSW_BASE/src/PhysicsTools/NanoAODTools/analysis/
root
.L eff.c+
eff(true)
```

### mistag rate in QCD MC
```
cd $CMSSW_BASE/src/PhysicsTools/NanoAODTools/analysis/
root
.L eff.c+
eff(false)
```

### roc curve
```
cd $CMSSW_BASE/src/PhysicsTools/NanoAODTools/analysis/
root roc.c+
```

## mistag rate in W->#ell#nu events

### submit jobs to crab
preselection is seen here: https://github.com/fojensen/nanoAOD-tools/blob/tauHats/crab/crab_script.py#L21-L27
```
cd $CMSSW_BASE/src/PhysicsTools/NanoAODTools/crab/
python samples.py
python submitToCrab.py
```
... let jobs run ...

### hadd the job output and splitDY
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

### calculate the mistag rate
```
cd /CMSSW_10_2_18/src/PhysicsTools/NanoAODTools/analysis/
root jetFake.c+
```

# Z->tautau->tau_{mu}tau_{h} analysis

## install Higgs Combine, follow recipe here:
https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/

## plot visible mass, extract (inclusive) expected yields
```
root makeHists.c+
```

## run combine to calculate significance
first, update datacard.txt with expected yields
```
combine -d datacard.txt -M Significance
```

