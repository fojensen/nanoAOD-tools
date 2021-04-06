#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/"

python haddnano.py WW_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/WW_TuneCP5_13TeV-pythia8/crab_WW_2016/210322_185804/0000/ | grep \.root`
xrdcp -f WW_2016.root ${OUTPUTDIR}
rm WW_2016.root

python haddnano.py WZ_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/WZ_TuneCP5_13TeV-pythia8/crab_WZ_2016/210322_185925/0000/ | grep \.root`
xrdcp -f WZ_2016.root ${OUTPUTDIR}
rm WZ_2016.root

python haddnano.py ZZ_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ZZ_TuneCP5_13TeV-pythia8/crab_ZZ_2016/210322_190026/0000/ | grep \.root`
xrdcp -f ZZ_2016.root ${OUTPUTDIR}
rm ZZ_2016.root

python haddnano.py TTTo2L2Nu_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_TTTo2L2Nu_2016/210322_184451/0000/ | grep \.root`
xrdcp -f TTTo2L2Nu_2016.root ${OUTPUTDIR}
rm TTTo2L2Nu_2016.root

python haddnano.py TTToSemiLeptonic_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_2016_rsb/210322_201510/0000/ | grep \.root`
xrdcp -f TTToSemiLeptonic_2016.root ${OUTPUTDIR}
rm TTToSemiLeptonic_2016.root

python haddnano.py ST_tW_antitop_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_antitop_2016/210322_184723/0000/ | grep \.root`
xrdcp -f ST_tW_antitop_2016.root ${OUTPUTDIR}
rm ST_tW_antitop_2016.root

python haddnano.py ST_tW_top_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_top_2016/210322_185011/0000/ | grep \.root`
xrdcp -f ST_tW_top_2016.root ${OUTPUTDIR}
rm ST_tW_top_2016.root

python haddnano.py ST_t_channel_top_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_t_channel_top_2016/210322_185324/0000/ | grep \.root`
xrdcp -f ST_t_channel_top_2016.root ${OUTPUTDIR}
rm ST_t_channel_top_2016.root

python haddnano.py ST_t_channel_antitop_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_t_channel_antitop_2016/210322_185646/0000/ | grep \.root`
xrdcp -f ST_t_channel_antitop_2016.root ${OUTPUTDIR}
rm ST_t_channel_antitop_2016.root

python haddnano.py Taustar_m375_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Taustar_TauG_L10000_m375_13TeV_pythia8/crab_Taustar_m375_2016/210322_184656/0000/ | grep \.root`
xrdcp -f Taustar_m375_2016.root ${OUTPUTDIR}
rm Taustar_m375_2016.root

python haddnano.py Taustar_m750_2016.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Taustar_TauG_L10000_m750_13TeV_pythia8/crab_Taustar_m750_2016/210322_185511/0000/ |  grep \.root`
xrdcp -f Taustar_m750_2016.root ${OUTPUTDIR}
rm Taustar_m750_2016.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
