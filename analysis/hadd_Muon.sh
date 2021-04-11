#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_10042021/"

python haddnano.py MuonA_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py MuonB_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py MuonC_2018.root `xrdfsls -u  | grep \.root`
python haddnano.py MuonD_2018.root `xrdfsls -u  | grep \.root`
xrdcp -f MuonA_2018.root ${OUTPUTDIR}
xrdcp -f MuonB_2018.root ${OUTPUTDIR}
xrdcp -f MuonC_2018.root ${OUTPUTDIR}
xrdcp -f MuonD_2018.root ${OUTPUTDIR}
rm Muon*_2018.root

python haddnano.py MuonB_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py MuonC_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py MuonD_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py MuonE_2017.root `xrdfsls -u  | grep \.root`
python haddnano.py MuonF_2017.root `xrdfsls -u  | grep \.root`
xrdcp -f MuonB_2017.root ${OUTPUTDIR}
xrdcp -f MuonC_2017.root ${OUTPUTDIR}
xrdcp -f MuonD_2017.root ${OUTPUTDIR}
xrdcp -f MuonE_2017.root ${OUTPUTDIR}
xrdcp -f MuonF_2017.root ${OUTPUTDIR}
rm Muon*_2017.root


python haddnano.py MuonB_2016.root `xrdfsls -u | grep \.root`
python haddnano.py MuonC_2016.root `xrdfsls -u | grep \.root`
python haddnano.py MuonD_2016.root `xrdfsls -u | grep \.root`
python haddnano.py MuonE_2016.root `xrdfsls -u | grep \.root`
python haddnano.py MuonF_HIPM_2016.root `xrdfsls -u | grep \.root`
python haddnano.py MuonF_v4_2016.root `xrdfsls -u | grep \.root`
python haddnano.py MuonF_2016.root MuonF_HIPM_2016.root MuonF_v4_2016.root
python haddnano.py MuonG_2016.root `xrdfsls -u | grep \.root`
python haddnano.py MuonH_2016.root `xrdfsls -u | grep \.root`
xrdcp -f MuonB_2016.root ${OUTPUTDIR}
xrdcp -f MuonC_2016.root ${OUTPUTDIR}
xrdcp -f MuonD_2016.root ${OUTPUTDIR}
xrdcp -f MuonE_2016.root ${OUTPUTDIR}
xrdcp -f MuonF_2016.root ${OUTPUTDIR}
xrdcp -f MuonG_2016.root ${OUTPUTDIR}
xrdcp -f MuonH_2016.root ${OUTPUTDIR}
rm Muon*_2016.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
