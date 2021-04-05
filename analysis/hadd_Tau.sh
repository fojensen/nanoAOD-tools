#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/"

python haddnano.py TauA_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018A/210322_181352/0000/ | grep \.root`
python haddnano.py TauB_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018B/210322_181524/0000/ | grep \.root`
python haddnano.py TauC_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018C/210322_181644/0000/ | grep \.root`
python haddnano.py TauD_2018.0.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \0.root`
python haddnano.py TauD_2018.1.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \1.root`
python haddnano.py TauD_2018.2.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \2.root`
python haddnano.py TauD_2018.3.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \3.root`
python haddnano.py TauD_2018.4.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \4.root`
python haddnano.py TauD_2018.5.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \5.root`
python haddnano.py TauD_2018.6.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \6.root`
python haddnano.py TauD_2018.7.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \7.root`
python haddnano.py TauD_2018.8.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \8.root`
python haddnano.py TauD_2018.9.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2018D/210322_181804/0000/ | grep \9.root`
python haddnano.py TauD_2018.root TauD_2018.0.root TauD_2018.1.root TauD_2018.2.root TauD_2018.3.root TauD_2018.4.root TauD_2018.5.root TauD_2018.6.root TauD_2018.7.root TauD_2018.8.root TauD_2018.9.root
xrdcp -f TauA_2018.root ${OUTPUTDIR}
xrdcp -f TauB_2018.root ${OUTPUTDIR}
xrdcp -f TauC_2018.root ${OUTPUTDIR}
xrdcp -f TauD_2018.root ${OUTPUTDIR}
rm Tau*_2018.root
rm TauD_2018.*.root

python haddnano.py TauB_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2017B/210322_181637/0000/ | grep \.root`
python haddnano.py TauC_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2017C/210322_181756/0000/ | grep \.root`
python haddnano.py TauD_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2017D/210322_181857/0000/ | grep \.root`
python haddnano.py TauE_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2017E/210322_181957/0000/ | grep \.root`
python haddnano.py TauF_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2017F/210322_182101/0000/ | grep \.root`
xrdcp -f TauB_2017.root ${OUTPUTDIR}
xrdcp -f TauC_2017.root ${OUTPUTDIR}
xrdcp -f TauD_2017.root ${OUTPUTDIR}
xrdcp -f TauE_2017.root ${OUTPUTDIR}
xrdcp -f TauF_2017.root ${OUTPUTDIR}
rm Tau*_2017.root

python haddnano.py TauB_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2016B_ver2_HIPM/210322_182517/0000/ | grep \.root`
python haddnano.py TauC_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2016C/210322_182627/0000/ | grep \.root`
python haddnano.py TauD_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2016D/210322_182732/0000/ | grep \.root`
python haddnano.py TauE_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2016E/210322_182838/0000/ | grep \.root`
python haddnano.py TauF_HIPM_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2016F_HIPM/210322_182938/0000/ | grep \.root`
python haddnano.py TauF_v2_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2016F_v2/210322_183032/0000/ | grep \.root`
python haddnano.py TauF_2016.root TauF_HIPM_2016.root TauF_v2_2016.root
python haddnano.py TauG_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2016G/210322_183127/0000/ | grep \.root`
python haddnano.py TauH_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Tau/crab_Tau_2016H/210322_183220/0000/ | grep \.root`
xrdcp -f TauB_2016.root ${OUTPUTDIR}
xrdcp -f TauC_2016.root ${OUTPUTDIR}
xrdcp -f TauD_2016.root ${OUTPUTDIR}
xrdcp -f TauE_2016.root ${OUTPUTDIR}
xrdcp -f TauF_2016.root ${OUTPUTDIR}
xrdcp -f TauG_2016.root ${OUTPUTDIR}
xrdcp -f TauH_2016.root ${OUTPUTDIR}
rm Tau*_2016.root

cd /uscms_data/d3/fojensen/excitedTau_28022021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis/
