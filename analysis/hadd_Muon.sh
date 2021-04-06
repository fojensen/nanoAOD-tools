#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/"

python haddnano.py MuonA_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2018A/210322_180313/0000/ | grep \.root`
python haddnano.py MuonB_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2018B/210322_180438/0000/ | grep \.root`
python haddnano.py MuonC_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2018C/210322_180600/0000/ | grep \.root`
python haddnano.py MuonD_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2018D/210322_180655/0000/ | grep \.root`
xrdcp -f MuonA_2018.root ${OUTPUTDIR}
xrdcp -f MuonB_2018.root ${OUTPUTDIR}
xrdcp -f MuonC_2018.root ${OUTPUTDIR}
xrdcp -f MuonD_2018.root ${OUTPUTDIR}
rm Muon*_2018.root

#this doesnt work for some reason python haddnano.py MuonB_2017B.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \.root`
#workaround...
python haddnano.py Muon_2017B_0.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \0.root`
python haddnano.py Muon_2017B_1.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \1.root`
python haddnano.py Muon_2017B_2.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \2.root`
python haddnano.py Muon_2017B_3.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \3.root`
python haddnano.py Muon_2017B_4.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \4.root`
python haddnano.py Muon_2017B_5.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \5.root`
python haddnano.py Muon_2017B_6.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \6.root`
python haddnano.py Muon_2017B_7.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \7.root`
python haddnano.py Muon_2017B_8.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \8.root`
python haddnano.py Muon_2017B_9.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017B/210322_180305/0000/ | grep \9.root`
python haddnano.py MuonB_2017.root Muon_2017B_0.root Muon_2017B_1.root Muon_2017B_2.root Muon_2017B_3.root Muon_2017B_4.root Muon_2017B_5.root Muon_2017B_6.root Muon_2017B_7.root Muon_2017B_8.root Muon_2017B_9.root
python haddnano.py MuonC_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017C/210322_180434/0000/ | grep \.root`
python haddnano.py MuonD_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017D/210322_180539/0000/ | grep \.root`
python haddnano.py MuonE_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017E/210322_180640/0000/ | grep \.root`
python haddnano.py MuonF_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2017F/210322_180820/0000/ | grep \.root`
xrdcp -f MuonB_2017.root ${OUTPUTDIR}
xrdcp -f MuonC_2017.root ${OUTPUTDIR}
xrdcp -f MuonD_2017.root ${OUTPUTDIR}
xrdcp -f MuonE_2017.root ${OUTPUTDIR}
xrdcp -f MuonF_2017.root ${OUTPUTDIR}
rm Muon*_2017.root
rm MuonB_2017.*.root

python haddnano.py MuonB_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2016B_ver2_HIPM_rsb/210322_201020/0000/ | grep \.root`
python haddnano.py MuonC_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2016C/210322_180508/0000/ | grep \.root`
python haddnano.py MuonD_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2016D/210322_180627/0000/ | grep \.root`
python haddnano.py MuonE_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2016E/210322_180805/0000/ | grep \.root`
python haddnano.py MuonF_HIPM_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2016F_HIPM/210322_180907/0000/ | grep \.root`
python haddnano.py MuonF_v4_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2016F_v4/210322_181020/0000/ | grep \.root`
python haddnano.py MuonF_2016.root MuonF_HIPM_2016.root MuonF_v4_2016.root
python haddnano.py MuonG_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2016G/210322_181151/0000/ | grep \.root`
python haddnano.py MuonH_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleMuon/crab_Muon_2016H/210322_181321/0000/ | grep \.root`
xrdcp -f MuonB_2016.root ${OUTPUTDIR}
xrdcp -f MuonC_2016.root ${OUTPUTDIR}
xrdcp -f MuonD_2016.root ${OUTPUTDIR}
xrdcp -f MuonE_2016.root ${OUTPUTDIR}
xrdcp -f MuonF_2016.root ${OUTPUTDIR}
xrdcp -f MuonG_2016.root ${OUTPUTDIR}
xrdcp -f MuonH_2016.root ${OUTPUTDIR}
rm Muon*_2016.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
