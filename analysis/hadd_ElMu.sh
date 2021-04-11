#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_10042021/"

python haddnano.py ElMuA_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuB_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuC_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuD_2018.root `xrdfsls -u  | grep \.root`
xrdcp -f ElMuA_2018.root ${OUTPUTDIR}
xrdcp -f ElMuB_2018.root ${OUTPUTDIR}
xrdcp -f ElMuC_2018.root ${OUTPUTDIR}
xrdcp -f ElMuD_2018.root ${OUTPUTDIR}
rm ElMu*_2018.root

python haddnano.py ElMuB_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuC_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuD_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuE_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuF_2017.root `xrdfsls -u  | grep \.root`
xrdcp -f ElMuB_2017.root ${OUTPUTDIR}
xrdcp -f ElMuC_2017.root ${OUTPUTDIR}
xrdcp -f ElMuD_2017.root ${OUTPUTDIR}
xrdcp -f ElMuE_2017.root ${OUTPUTDIR}
xrdcp -f ElMuF_2017.root ${OUTPUTDIR}
rm ElMu*_2017.root

python haddnano.py ElMuB_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuC_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuD_2016.root `xrdfsls -u | grep \.root`
python haddnano.py ElMuE_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuF_HIPM_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuF_v2_2016.root `xrdfsls -u | grep \.root`
python haddnano.py ElMuF_2016.root ElMuF_HIPM_2016.root ElMuF_v2_2016.root
python haddnano.py ElMuG_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py ElMuH_2016.root `xrdfsls -u  | grep \.root`
xrdcp -f ElMuB_2016.root ${OUTPUTDIR}
xrdcp -f ElMuC_2016.root ${OUTPUTDIR}
xrdcp -f ElMuD_2016.root ${OUTPUTDIR}
xrdcp -f ElMuE_2016.root ${OUTPUTDIR}
xrdcp -f ElMuF_2016.root ${OUTPUTDIR}
xrdcp -f ElMuG_2016.root ${OUTPUTDIR}
xrdcp -f ElMuH_2016.root ${OUTPUTDIR}
rm ElMu*_2016.root

cd /uscms_data/d3/fojensen/excitedElMu_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis/
