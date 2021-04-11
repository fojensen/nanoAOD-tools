#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_10042021/"

python haddnano.py MuonA_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_10042021/SingleMuon/crab_Muon_2018A/210410_212355/0000/ | grep \.root`
python haddnano.py MuonB_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_10042021/SingleMuon/crab_Muon_2018B/210410_212514/0000/ | grep \.root`
python haddnano.py MuonC_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_10042021/SingleMuon/crab_Muon_2018C/210410_212611/0000/ | grep \.root`
python haddnano.py MuonD_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_10042021/SingleMuon/crab_Muon_2018D/210410_212707/0000/ | grep \.root`
xrdcp -f MuonA_2018.root ${OUTPUTDIR}
xrdcp -f MuonB_2018.root ${OUTPUTDIR}
xrdcp -f MuonC_2018.root ${OUTPUTDIR}
xrdcp -f MuonD_2018.root ${OUTPUTDIR}
rm Muon*_2018.root

python haddnano.py MuonB_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_10042021/SingleMuon/crab_Muon_2017B/210410_212341/0000/ | grep \.root`
python haddnano.py MuonC_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_10042021/SingleMuon/crab_Muon_2017C/210410_212501/0000/ | grep \.root`
python haddnano.py MuonD_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_10042021/SingleMuon/crab_Muon_2017D/210410_212631/0000/ | grep \.root`
python haddnano.py MuonE_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_10042021/SingleMuon/crab_Muon_2017E/210410_212749/0000/ | grep \.root`
python haddnano.py MuonF_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_10042021/SingleMuon/crab_Muon_2017F/210410_212852/0000/ | grep \.root`
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
