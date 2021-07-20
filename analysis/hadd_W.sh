#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_19072021/"

python haddnano.py WJetsToLNu_2015.root `xrdfsls -u  | grep \.root`
xrdcp -f WJetsToLNu_2015.root ${OUTPUTDIR}
rm WJetsToLNu_2015.root

python haddnano.py WJetsToLNu_2016.root `xrdfsls -u  | grep \.root`
xrdcp -f WJetsToLNu_2016.root ${OUTPUTDIR}
rm WJetsToLNu_2016.root

python haddnano.py WJetsToLNu_2017.root `xrdfsls -u  | grep \.root`
xrdcp -f WJetsToLNu_2017.root ${OUTPUTDIR}
rm WJetsToLNu_2017.root

python haddnano.py WJetsToLNu_2018.root `xrdfsls -u  | grep \.root`
xrdcp -f WJetsToLNu_2018.root ${OUTPUTDIR}
rm WJetsToLNu_2018.root

python haddnano.py WGToLNuG_2015.root `xrdfsls -u  | grep \.root`
xrdcp -f WGToLNuG_2015.root ${OUTPUTDIR}
rm WGToLNuG_2015.root

python haddnano.py WGToLNuG_2016.root `xrdfsls -u  | grep \.root`
xrdcp -f WGToLNuG_2016.root ${OUTPUTDIR}
rm WGToLNuG_2016.root

python haddnano.py WGToLNuG_2017.root `xrdfsls -u  | grep \.root`
xrdcp -f WGToLNuG_2017.root ${OUTPUTDIR}
rm WGToLNuG_2017.root

python haddnano.py WGToLNuG_2018.root `xrdfsls -u  | grep \.root`
xrdcp -f WGToLNuG_2018.root ${OUTPUTDIR}
rm WGToLNuG_2018.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
