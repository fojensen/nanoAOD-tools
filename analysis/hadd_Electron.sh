#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/"

python haddnano.py ElectronA_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/EGamma/crab_Electron_2018A/210322_180825/0000/ | grep \.root`
python haddnano.py ElectronB_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/EGamma/crab_Electron_2018B/210322_181005/0000/ | grep \.root`
python haddnano.py ElectronC_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/EGamma/crab_Electron_2018C_rsb/210322_191358/0000/ | grep \.root`
python haddnano.py ElectronD_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/EGamma/crab_Electron_2018D/210322_181244/0000/ | grep \.root`
xrdcp -f ElectronA_2018.root ${OUTPUTDIR}
xrdcp -f ElectronB_2018.root ${OUTPUTDIR}
xrdcp -f ElectronC_2018.root ${OUTPUTDIR}
xrdcp -f ElectronD_2018.root ${OUTPUTDIR}
rm Electron*_2018.root

python haddnano.py ElectronB_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2017B/210322_180959/0000/ | grep \.root`
python haddnano.py ElectronC_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2017C/210322_181120/0000/ | grep \.root`
python haddnano.py ElectronD_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2017D/210322_181222/0000/ | grep \.root`
python haddnano.py ElectronE_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2017E/210322_181345/0000/ | grep \.root`
python haddnano.py ElectronF_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2017F/210322_181520/0000/ | grep \.root`
xrdcp -f ElectronB_2017.root ${OUTPUTDIR}
xrdcp -f ElectronC_2017.root ${OUTPUTDIR}
xrdcp -f ElectronD_2017.root ${OUTPUTDIR}
xrdcp -f ElectronE_2017.root ${OUTPUTDIR}
xrdcp -f ElectronF_2017.root ${OUTPUTDIR}
rm Electron*_2017.root

python haddnano.py ElectronB_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2016B_ver2_HIPM/210322_181531/0000/ | grep \.root`
python haddnano.py ElectronC_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2016C/210322_181648/0000/ | grep \.root`
python haddnano.py ElectronD_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2016D/210322_181807/0000/ | grep \.root`
python haddnano.py ElectronE_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2016E/210322_181909/0000/ | grep \.root`
python haddnano.py ElectronF_HIPM_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2016F_HIPM/210322_182008/0000/ | grep \.root`
python haddnano.py ElectronF_v2_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2016F_v2/210322_182110/0000/ | grep \.root`
python haddnano.py ElectronF_2016.root ElectronF_HIPM_2016.root ElectronF_v2_2016.root
python haddnano.py ElectronG_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2016G/210322_182206/0000/ | grep \.root`
python haddnano.py ElectronH_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/SingleElectron/crab_Electron_2016H/210322_182302/0000/ | grep \.root`
xrdcp -f ElectronB_2016.root ${OUTPUTDIR}
xrdcp -f ElectronC_2016.root ${OUTPUTDIR}
xrdcp -f ElectronD_2016.root ${OUTPUTDIR}
xrdcp -f ElectronE_2016.root ${OUTPUTDIR}
xrdcp -f ElectronF_2016.root ${OUTPUTDIR}
xrdcp -f ElectronG_2016.root ${OUTPUTDIR}
xrdcp -f ElectronH_2016.root ${OUTPUTDIR}
rm Electron*_2016.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
