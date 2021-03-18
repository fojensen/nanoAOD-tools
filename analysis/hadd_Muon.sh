#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_08032020/"

#python haddnano.py MuonA_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2018A/210308_182759/0000/ | grep \.root`
#xrdcp -f MuonA_2018.root ${OUTPUTDIR}
#rm MuonA_2018.root

#python haddnano.py MuonB_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2018B/210308_182843/0000/ | grep \.root`
#xrdcp -f MuonB_2018.root ${OUTPUTDIR}
#rm MuonB_2018.root

#python haddnano.py MuonC_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2018C/210308_182927/0000/ | grep \.root`
#xrdcp -f MuonC_2018.root ${OUTPUTDIR}
#rm MuonC_2018.root

#python haddnano.py MuonD_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2018D/210308_183013/0000/ | grep \.root`
#xrdcp -f MuonD_2018.root ${OUTPUTDIR}
#rm MuonD_2018.root

#python haddnano.py MuonB_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2017B/210308_184020/0000/ | grep \.root`
#xrdcp -f MuonB_2017.root ${OUTPUTDIR}
#rm MuonB_2017.root

#python haddnano.py MuonC_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2017C_allowvalid/210308_193428/0000/ | grep \.root`
#xrdcp -f MuonC_2017.root ${OUTPUTDIR}
#rm MuonC_2017.root

#python haddnano.py MuonD_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2017D/210308_184146/0000/ | grep \.root`
#xrdcp -f MuonD_2017.root ${OUTPUTDIR}
#rm MuonD_2017.root

#python haddnano.py MuonE_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2017E/210308_184247/0000/ | grep \.root`
#xrdcp -f MuonE_2017.root ${OUTPUTDIR}
#rm MuonE_2017.root

python haddnano.py MuonF_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2017F/210308_184331/0000/ | grep \.root`
xrdcp -f MuonF_2017.root ${OUTPUTDIR}
rm MuonF_2017.root

#python haddnano.py MuonB_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2016B_ver2_HIPM/210308_185752/0000/ | grep \.root`
#xrdcp -f MuonB_2016.root ${OUTPUTDIR}
#rm MuonB_2016.root

#python haddnano.py MuonC_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2016C/210308_185834/0000/ | grep \.root`
#xrdcp -f MuonC_2016.root ${OUTPUTDIR}
#rm MuonC_2016.root

#python haddnano.py MuonD_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2016D/210308_185916/0000/ | grep \.root`
#xrdcp -f MuonD_2016.root ${OUTPUTDIR}
#rm MuonD_2016.root

#python haddnano.py MuonE_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2016E/210308_185959/0000/ | grep \.root`
#xrdcp -f MuonE_2016.root ${OUTPUTDIR}
#rm MuonE_2016.root

python haddnano.py MuonF_HIPM_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2016F_HIPM/210308_190042/0000/ | grep \.root`
#xrdcp -f MuonF_HIPM_2016.root ${OUTPUTDIR}
#rm MuonF_HIPM_2016.root
python haddnano.py MuonF_v4_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2016F_v4/210308_190211/0000/ | grep \.root`
#xrdcp -f MuonF_v4_2016.root ${OUTPUTDIR}
#rm MuonF_v4_2016F.root
python haddnano.py MuonF_2016.root MuonF_HIPM_2016.root MuonF_v4_2016.root
xrdcp -f MuonF_2016.root ${OUTPUTDIR}
rm MuonF_HIPM_2016.root
rm MuonF_v4_2016.root
rm MuonF_2016.root

#python haddnano.py MuonG_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2016G/210308_190254/0000/ | grep \.root`
#xrdcp -f MuonG_2016.root ${OUTPUTDIR}
#rm MuonG_2016.root

#python haddnano.py MuonH_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleMuon/crab_Muon_2016H/210308_190337/0000/ | grep \.root`
#xrdcp -f MuonH_2016.root ${OUTPUTDIR}
#rm MuonH_2016.root

cd /uscms_data/d3/fojensen/excitedTau_28022021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
