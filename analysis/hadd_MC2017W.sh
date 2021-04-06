#!/bin/bash

mkdir -p /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/W2017
cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/W2017
cp processDY.c /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/W2017
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/W2017

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/"

python haddnano.py W01234JetsToLNu_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_2017/210322_190100/0000/ | grep \.root`
xrdcp -f W01234JetsToLNu_2017.root ${OUTPUTDIR}

python haddnano.py W1JetsToLNu_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_01042021/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W1JetsToLNu_2017/210402_024720/0000/ | grep \.root`
xrdcp -f W1JetsToLNu_2017.root ${OUTPUTDIR}

python haddnano.py W2JetsToLNu_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_01042021/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W2JetsToLNu_2017/210402_024812/0000/ | grep \.root`
xrdcp -f W2JetsToLNu_2017.root ${OUTPUTDIR}

python haddnano.py W3JetsToLNu_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_01042021/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W3JetsToLNu_2017/210402_024904/0000/ | grep \.root`
xrdcp -f W3JetsToLNu_2017.root ${OUTPUTDIR}

python haddnano.py W4JetsToLNu_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_01042021/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W4JetsToLNu_2017/210402_024956/0000/ | grep \.root`
xrdcp -f W4JetsToLNu_2017.root ${OUTPUTDIR}

python haddnano.py WJetsToLNu_2017.root W01234JetsToLNu_2017.root W1JetsToLNu_2017.root W2JetsToLNu_2017.root W3JetsToLNu_2017.root W4JetsToLNu_2017.root
root -q 'processDY.c+("WJetsToLNu", 2017)'
xrdcp -f WJetsToLNu_2017.root ${OUTPUTDIR}

rm W01234JetsToLNu_2017.root
rm W1JetsToLNu_2017.root
rm W2JetsToLNu_2017.root
rm W3JetsToLNu_2017.root
rm W4JetsToLNu_2017.root
rm WJetsToLNu_2017.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
