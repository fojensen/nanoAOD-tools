#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_10042021/"

python haddnano.py TauA_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py TauB_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py TauC_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py TauD_2018.root `xrdfsls -u  | grep \.root`
xrdcp -f TauA_2018.root ${OUTPUTDIR}
xrdcp -f TauB_2018.root ${OUTPUTDIR}
xrdcp -f TauC_2018.root ${OUTPUTDIR}
xrdcp -f TauD_2018.root ${OUTPUTDIR}
rm Tau*_2018.root

python haddnano.py TauB_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py TauC_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py TauD_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py TauE_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py TauF_2017.root `xrdfsls -u  | grep \.root`
xrdcp -f TauB_2017.root ${OUTPUTDIR}
xrdcp -f TauC_2017.root ${OUTPUTDIR}
xrdcp -f TauD_2017.root ${OUTPUTDIR}
xrdcp -f TauE_2017.root ${OUTPUTDIR}
xrdcp -f TauF_2017.root ${OUTPUTDIR}
rm Tau*_2017.root

python haddnano.py TauB_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py TauC_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py TauD_2016.root `xrdfsls -u | grep \.root`
python haddnano.py TauE_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py TauF_HIPM_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py TauF_v2_2016.root `xrdfsls -u | grep \.root`
python haddnano.py TauF_2016.root TauF_HIPM_2016.root TauF_v2_2016.root
python haddnano.py TauG_2016.root `xrdfsls -u  | grep \.root`
python haddnano.py TauH_2016.root `xrdfsls -u  | grep \.root`
xrdcp -f TauB_2016.root ${OUTPUTDIR}
xrdcp -f TauC_2016.root ${OUTPUTDIR}
xrdcp -f TauD_2016.root ${OUTPUTDIR}
xrdcp -f TauE_2016.root ${OUTPUTDIR}
xrdcp -f TauF_2016.root ${OUTPUTDIR}
xrdcp -f TauG_2016.root ${OUTPUTDIR}
xrdcp -f TauH_2016.root ${OUTPUTDIR}
rm Tau*_2016.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis/
