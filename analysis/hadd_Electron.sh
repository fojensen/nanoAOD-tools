#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_11042021/"

python haddnano.py ElectronA_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronB_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronC_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronD_2018.root `xrdfsls -u  | grep \.root`
xrdcp -f ElectronA_2018.root ${OUTPUTDIR}
xrdcp -f ElectronB_2018.root ${OUTPUTDIR}
xrdcp -f ElectronC_2018.root ${OUTPUTDIR}
xrdcp -f ElectronD_2018.root ${OUTPUTDIR}
rm Electron*_2018.root

python haddnano.py ElectronB_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronC_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronD_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronE_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronF_2017.root `xrdfsls -u  | grep \.root`
xrdcp -f ElectronB_2017.root ${OUTPUTDIR}
xrdcp -f ElectronC_2017.root ${OUTPUTDIR}
xrdcp -f ElectronD_2017.root ${OUTPUTDIR}
xrdcp -f ElectronE_2017.root ${OUTPUTDIR}
xrdcp -f ElectronF_2017.root ${OUTPUTDIR}
rm Electron*_2017.root

python haddnano.py ElectronB_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronC_2016.root `xrdfsls -u | grep \.root`
python haddnano.py ElectronD_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronE_2016.root `xrdfsls -u | grep \.root`
python haddnano.py ElectronF_HIPM_2016.root `xrdfsls -u | grep \.root`
python haddnano.py ElectronF_v2_2016.root `xrdfsls -u | grep \.root`
python haddnano.py ElectronF_2016.root ElectronF_HIPM_2016.root ElectronF_v2_2016.root
python haddnano.py ElectronG_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py ElectronH_2016.root `xrdfsls -u  | grep \.root`
xrdcp -f ElectronB_2016.root ${OUTPUTDIR}
xrdcp -f ElectronC_2016.root ${OUTPUTDIR}
xrdcp -f ElectronD_2016.root ${OUTPUTDIR}
xrdcp -f ElectronE_2016.root ${OUTPUTDIR}
xrdcp -f ElectronF_2016.root ${OUTPUTDIR}
xrdcp -f ElectronG_2016.root ${OUTPUTDIR}
xrdcp -f ElectronH_2016.root ${OUTPUTDIR}
rm Electron*_2016.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
