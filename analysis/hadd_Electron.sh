#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_08032020/"

#python haddnano.py ElectronA_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/EGamma/crab_Electron_2018A/210308_183056/0000/ | grep \.root`
#xrdcp -f ElectronA_2018.root ${OUTPUTDIR}
#rm ElectronA_2018.root

#python haddnano.py ElectronB_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/EGamma/crab_Electron_2018B/210308_183139/0000/ | grep \.root`
#xrdcp -f ElectronB_2018.root ${OUTPUTDIR}
#rm ElectronB_2018.root

#python haddnano.py ElectronC_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/EGamma/crab_Electron_2018C_allowvalid/210308_193222/0000/ | grep \.root`
#xrdcp -f ElectronC_2018.root ${OUTPUTDIR}
#rm ElectronC_2018.root

#python haddnano.py ElectronD_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/EGamma/crab_Electron_2018D/210308_183306/0000/ | grep \.root`
#xrdcp -f ElectronD_2018.root ${OUTPUTDIR}
#rm ElectronD_2018.root

#python haddnano.py ElectronB_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2017B/210308_184542/0000/ | grep \.root`
#xrdcp -f ElectronB_2017.root ${OUTPUTDIR}
#rm ElectronB_2017.root

#python haddnano.py ElectronC_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2017C/210308_184646/0000/ | grep \.root`
#xrdcp -f ElectronC_2017.root ${OUTPUTDIR}
#rm ElectronC_2017.root

#python haddnano.py ElectronD_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2017D/210308_184743/0000/  | grep \.root`
#xrdcp -f ElectronD_2017.root ${OUTPUTDIR}
#rm ElectronD_2017.root

#python haddnano.py ElectronE_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2017E/210308_184826/0000/ | grep \.root`
#xrdcp -f ElectronE_2017.root ${OUTPUTDIR}
#rm ElectronE_2017.root

#python haddnano.py ElectronF_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2017F/210308_184918/0000/ | grep \.root`
#xrdcp -f ElectronF_2017.root ${OUTPUTDIR}
#rm ElectronF_2017.root

#python haddnano.py ElectronB_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2016B_ver2_HIPM_allowvalid/210308_193659/0000/ | grep \.root`
#xrdcp -f ElectronB_2016.root ${OUTPUTDIR}
#rm ElectronB_2016.root

#python haddnano.py ElectronC_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2016C/210308_190549/0000/ | grep \.root`
#xrdcp -f ElectronC_2016.root ${OUTPUTDIR}
#rm ElectronC_2016.root

#python haddnano.py ElectronD_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2016D/210308_190632/0000/ | grep \.root`
#xrdcp -f ElectronD_2016.root ${OUTPUTDIR}
#rm ElectronD_2016.root

#python haddnano.py ElectronE_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2016E/210308_190715/0000/ | grep \.root`
#xrdcp -f ElectronE_2016.root ${OUTPUTDIR}
#rm ElectronE_2016.root

python haddnano.py ElectronF_HIPM_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2016F_HIPM/210308_190758/0000/ | grep \.root`
#xrdcp -f ElectronF_HIPM_2016.root ${OUTPUTDIR}
#rm ElectronF_HIPM_2016.root
python haddnano.py ElectronF_v2_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2016F_v2/210308_190923/0000/ | grep \.root`
#xrdcp -f ElectronF_v2_2016.root ${OUTPUTDIR}
#rm ElectronF_v2_2016.root
python haddnano.py ElectronF_2016.root ElectronF_HIPM_2016.root ElectronF_v2_2016.root
xrdcp -f ElectronF_2016.root ${OUTPUTDIR}
rm ElectronF_HIPM_2016.root
rm ElectronF_v2_2016.root
rm ElectronF_2016.root

#python haddnano.py ElectronG_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2016G/210308_191006/0000/ | grep \.root`
#xrdcp -f ElectronG_2016.root ${OUTPUTDIR}
#rm ElectronG_2016.root

#python haddnano.py ElectronH_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/SingleElectron/crab_Electron_2016H/210308_191049/0000/ | grep \.root`
#xrdcp -f ElectronH_2016.root ${OUTPUTDIR}
#rm ElectronH_2016.root

cd /uscms_data/d3/fojensen/excitedTau_28022021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
