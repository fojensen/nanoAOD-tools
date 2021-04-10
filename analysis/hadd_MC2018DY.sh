#!/bin/bash

mkdir -p /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2018
cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2018
cp processDY.c /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2018
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2018

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_10042021/"

python haddnano.py DYJetsToLLM10_2018.root `xrdfsls -u | grep \.root`
xrdcp -f DYJetsToLLM10_2018.root ${OUTPUTDIR}

python haddnano.py DYJetsToLL_2018.root `xrdfsls -u | grep \.root`
xrdcp -f DYJetsToLL_2018.root ${OUTPUTDIR}

python haddnano.py DY1JetsToLL_2018.root `xrdfsls -u | grep \.root`
xrdcp -f DY1JetsToLL_2018.root ${OUTPUTDIR}

python haddnano.py DY2JetsToLL_2018.root `xrdfsls -u | grep \.root`
xrdcp -f DY2JetsToLL_2018.root ${OUTPUTDIR}

python haddnano.py DY3JetsToLL_2018.root `xrdfsls -u | grep \.root`
xrdcp -f DY3JetsToLL_2018.root ${OUTPUTDIR}

python haddnano.py DY4JetsToLL_2018.root `xrdfsls -u | grep \.root`
xrdcp -f DY4JetsToLL_2018.root ${OUTPUTDIR}

root -q 'processDY.c+("DYJetsToLL", 2018)'
xrdcp -f DYJetsToTauTau_2018.root ${OUTPUTDIR}
xrdcp -f DYJetsToEEMuMu_2018.root ${OUTPUTDIR}

rm DYJetsTo*_2018.root
cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
