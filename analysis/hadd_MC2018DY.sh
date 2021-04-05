#!/bin/bash

mkdir -p /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2018
cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2018
cp processDY.c /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2018
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/DY2018

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/"

python haddnano.py DYJetsToLL_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M50_2018/210322_183632/0000/ | grep \.root`
xrdcp -f DYJetsToLL_2018.root ${OUTPUTDIR}

python haddnano.py DY1JetsToLL_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY1JetsToLL_M50_2018/210322_183803/0000/ | grep \.root`
xrdcp -f DY1JetsToLL_2018.root ${OUTPUTDIR}

python haddnano.py DY2JetsToLL_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY2JetsToLL_M50_2018/210322_183945/0000/ | grep \.root`
xrdcp -f DY2JetsToLL_2018.root ${OUTPUTDIR}

python haddnano.py DY3JetsToLL_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY3JetsToLL_M50_2018/210322_184209/0000/ | grep \.root`
xrdcp -f DY3JetsToLL_2018.root ${OUTPUTDIR}

python haddnano.py DY4JetsToLL_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DY4JetsToLL_M50_2018/210322_184448/0000/ | grep \.root`
xrdcp -f DY4JetsToLL_2018.root ${OUTPUTDIR}

root -q 'processDY.c+("DYJetsToLL", 2018)'
xrdcp -f DYJetsToTauTau_2018.root ${OUTPUTDIR}
xrdcp -f DYJetsToEEMuMu_2018.root ${OUTPUTDIR}
rm DYJetsToLL_2018.root
rm DY1JetsToLL_2018.root
rm DY2JetsToLL_2018.root
rm DY3JetsToLL_2018.root
rm DY4JetsToLL_2018.root
cd /uscms_data/d3/fojensen/excitedTau_28022021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
