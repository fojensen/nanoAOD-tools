#!/bin/bash

mkdir -p /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/W2016
cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/W2016
cp processDY.c /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/W2016
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/W2016

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/"

python haddnano.py W01234JetsToLNu_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_2016/210322_190138/0000/ | grep \.root`
xrdcp -f W01234JetsToLNu_2016.root ${OUTPUTDIR}

python haddnano.py W1JetsToLNu_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_01042021/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W1JetsToLNu_2016/210402_024323/0000/ | grep \.root`
xrdcp -f W1JetsToLNu_2016.root ${OUTPUTDIR}

python haddnano.py W2JetsToLNu_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_01042021/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W2JetsToLNu_2016/210402_024414/0000/ | grep \.root`
xrdcp -f W2JetsToLNu_2016.root ${OUTPUTDIR}

python haddnano.py W3JetsToLNu_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_01042021/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W3JetsToLNu_2016/210402_024507/0000/ | grep \.root`
xrdcp -f W3JetsToLNu_2016.root ${OUTPUTDIR}

python haddnano.py W4JetsToLNu_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_01042021/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_W4JetsToLNu_2016/210402_024558/0000/ | grep \.root`
xrdcp -f W4JetsToLNu_2016.root ${OUTPUTDIR}

python haddnano.py WJetsToLNu_2016.root W01234JetsToLNu_2016.root W1JetsToLNu_2016.root W2JetsToLNu_2016.root W3JetsToLNu_2016.root W4JetsToLNu_2016.root
root -q 'processDY.c+("WJetsToLNu", 2016)'
xrdcp -f WJetsToLNu_2016.root ${OUTPUTDIR}

rm W01234JetsToLNu_2016.root
rm W1JetsToLNu_2016.root
rm W2JetsToLNu_2016.root
rm W3JetsToLNu_2016.root
rm W4JetsToLNu_2016.root
rm WJetsToLNu_2016.root

cd /uscms_data/d3/fojensen/excitedTau_28022021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
