#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_08032020/"

#python haddnano.py TauA_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2018A/210308_183349/0000/ | grep \.root`
#xrdcp -f TauA_2018.root ${OUTPUTDIR}
#rm TauA_2018.root

#python haddnano.py TauB_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2018B/210308_183431/0000/ | grep \.root`
#xrdcp -f TauB_2018.root ${OUTPUTDIR}
#rm Taub_2018.root

#python haddnano.py TauC_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2018C/210308_183516/0000/ | grep \.root`
#xrdcp -f TauC_2018.root ${OUTPUTDIR}
#rm TauC_2018.root

#python haddnano.py TauD_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2018D/210308_183601/0000/ | grep \.root`
#xrdcp -f TauD_2018.root ${OUTPUTDIR}
#rm TauD_2018.root

#python haddnano.py TauB_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2017B/210308_185002/0000/ | grep \.root`
#xrdcp -f TauB_2017.root ${OUTPUTDIR}
#rm TauB_2017.root

#python haddnano.py TauC_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2017C/210308_185045/0000/ | grep \.root`
#xrdcp -f TauC_2017.root ${OUTPUTDIR}
#rm TauC_2017.root

#python haddnano.py TauD_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2017D/210308_185141/0000/ | grep \.root`
#xrdcp -f TauD_2017.root ${OUTPUTDIR}
#rm TauD_2017.root

#python haddnano.py TauE_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2017E_rsb/210309_021607/0000/ | grep \.root`
#xrdcp -f TauE_2017.root ${OUTPUTDIR}
#rm TauE_2017.root

python haddnano.py TauF_2017.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2017F/210308_185308/0000/ | grep \.root`
xrdcp -f TauF_2017.root ${OUTPUTDIR}
rm TauF_2017.root

#python haddnano.py TauB_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2016B_ver2_HIPM/210308_191215/0000/ | grep \.root`
#xrdcp -f TauB_2016.root ${OUTPUTDIR}
#rm TauB_2016.root

#python haddnano.py TauC_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2016C/210308_191257/0000/ | grep \.root`
#xrdcp -f TauC_2016.root ${OUTPUTDIR}
#rm TauC_2016.root

#python haddnano.py TauD_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2016D/210308_191341/0000/ | grep \.root`
#xrdcp -f TauD_2016.root ${OUTPUTDIR}
#rm TauD_2016.root

#python haddnano.py TauE_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2016E/210308_191425/0000/ | grep \.root`
#xrdcp -f TauE_2016.root ${OUTPUTDIR}
#rm TauE_2016.root

python haddnano.py TauF_HIPM_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2016F_HIPM/210308_191508/0000/ | grep \.root`
#xrdcp -f TauF_HIPM_2016.root ${OUTPUTDIR}
#rm TauF_HIPM_2016.root
python haddnano.py TauF_v2_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2016F_v2/210308_191633/0000/ | grep \.root`
#xrdcp -f TauF_v2_2016.root ${OUTPUTDIR}
#rm TauF_v2_2016.root
python haddnano.py TauF_2016.root TauF_HIPM_2016.root TauF_v2_2016.root
xrdcp -f TauF_2016.root ${OUTPUTDIR}
rm TauF_HIPM_2016.root
rm TauF_v2_2016.root
rm TauF_2016.root

#python haddnano.py TauG_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2016G/210308_191716/0000/ | grep \.root`
#xrdcp -f TauG_2016.root ${OUTPUTDIR}
#rm TauG_2016.root

#python haddnano.py TauH_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_08032020/Tau/crab_Tau_2016H/210308_191758/0000/ | grep \.root`
#xrdcp -f TauH_2016.root ${OUTPUTDIR}
#rm TauH_2016.root

cd /uscms_data/d3/fojensen/excitedTau_28022021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
