#!/bin/bash

mkdir -p /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2017
cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2017
cp processDY.c /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2017
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2017

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_10042021/"

python haddnano.py DYJetsToLLM10_2017.root `xrdfsls -u | grep \.root`
xrdcp -f DYJetsToLLM10_2017.root ${OUTPUTDIR}

python haddnano.py DYJetsToLL_2017.root `xrdfsls -u | grep \.root`
xrdcp -f DYJetsToLL_2017.root ${OUTPUTDIR}

python haddnano.py DY1JetsToLL_2017.root `xrdfsls -u | grep \.root`
xrdcp -f DY1JetsToLL_2017.root ${OUTPUTDIR}

python haddnano.py DY2JetsToLL_2017.root `xrdfsls -u | grep \.root`
xrdcp -f DY2JetsToLL_2017.root ${OUTPUTDIR}

python haddnano.py DY3JetsToLL_2017.root `xrdfsls -u | grep \.root`
xrdcp -f DY3JetsToLL_2017.root ${OUTPUTDIR}

python haddnano.py DY4JetsToLL_2017.root `xrdfsls -u | grep \.root`
xrdcp -f DY4JetsToLL_2017.root ${OUTPUTDIR}

root -q 'processDY.c+("DYJetsToLL", 2017)'
xrdcp -f DYJetsToTauTau_2017.root ${OUTPUTDIR}
xrdcp -f DYJetsToEEMuMu_2017.root ${OUTPUTDIR}

rm DYJetsTo*_2017.root
cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
