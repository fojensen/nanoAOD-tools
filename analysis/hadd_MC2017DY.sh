#!/bin/bash

mkdir -p /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2017
cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2017
cp processDY.c /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2017
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2017

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/"

python haddnano.py DYJetsToLLM10_2017.root `xrdfsls -u | grep \.root`
xrdcp -f DYJetsToLL_M10_2016.root ${OUTPUTDIR}

python haddnano.py DYJetsToLL_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M50_2017/210322_183517/0000/ | grep \.root`
xrdcp -f DYJetsToLL_2017.root ${OUTPUTDIR}

python haddnano.py DY1JetsToLL_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY1JetsToLL_M50_2017/210322_183639/0000/ | grep \.root`
xrdcp -f DY1JetsToLL_2017.root ${OUTPUTDIR}

python haddnano.py DY2JetsToLL_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY2JetsToLL_M50_2017/210322_183805/0000/ | grep \.root`
xrdcp -f DY2JetsToLL_2017.root ${OUTPUTDIR}

python haddnano.py DY3JetsToLL_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY3JetsToLL_M50_2017/210322_183945/0000/ | grep \.root`
xrdcp -f DY3JetsToLL_2017.root ${OUTPUTDIR}

python haddnano.py DY4JetsToLL_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY4JetsToLL_M50_2017/210322_184211/0000/ | grep \.root`
xrdcp -f DY4JetsToLL_2017.root ${OUTPUTDIR}

root -q 'processDY.c+("DYJetsToLL", 2017)'
xrdcp -f DYJetsToTauTau_2017.root ${OUTPUTDIR}
xrdcp -f DYJetsToEEMuMu_2017.root ${OUTPUTDIR}
rm *.root
cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
