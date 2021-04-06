#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_22032021/"

python haddnano.py WW_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/WW_TuneCP5_13TeV-pythia8/crab_WW_2018/210322_190015/0000/ | grep \.root`
xrdcp -f WW_2018.root ${OUTPUTDIR}
rm WW_2018.root

python haddnano.py WZ_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/WZ_TuneCP5_13TeV-pythia8/crab_WZ_2018/210322_190129/0000/ | grep \.root`
xrdcp -f WZ_2018.root ${OUTPUTDIR}
rm WZ_2018.root

python haddnano.py ZZ_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ZZ_TuneCP5_13TeV-pythia8/crab_ZZ_2018/210322_190227/0000/ | grep \.root`
xrdcp -f ZZ_2018.root ${OUTPUTDIR}
rm ZZ_2018.root

python haddnano.py TTTo2L2Nu_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_TTTo2L2Nu_2018/210322_184949/0000/ | grep \.root`
xrdcp -f TTTo2L2Nu_2018.root ${OUTPUTDIR}
rm TTTo2L2Nu_2018.root

python haddnano.py TTToSemiLeptonic_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_2018/210322_184719/0000/ | grep \.root`
xrdcp -f TTToSemiLeptonic_2018.root ${OUTPUTDIR}
rm TTToSemiLeptonic_2018.root

python haddnano.py ST_tW_antitop_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_antitop_2018/210322_185230/0000/ | grep \.root`
xrdcp -f ST_tW_antitop_2018.root ${OUTPUTDIR}
rm ST_tW_antitop_2018.root

python haddnano.py ST_tW_top_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_tW_top_2018/210322_185516/0000/ | grep \.root`
xrdcp -f ST_tW_top_2018.root ${OUTPUTDIR}
rm ST_tW_top_2018.root

python haddnano.py ST_t_channel_top_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_t_channel_top_2018/210322_185722/0000/ | grep \.root`
xrdcp -f ST_t_channel_top_2018.root ${OUTPUTDIR}
rm ST_t_channel_top_2018.root

python haddnano.py ST_t_channel_antitop_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/crab_ST_t_channel_antitop_2018/210322_185911/0000/ | grep \.root`
xrdcp -f ST_t_channel_antitop_2018.root ${OUTPUTDIR}
rm ST_t_channel_antitop_2018.root

python haddnano.py Taustar_m375_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Taustar_TauG_L10000_m375_CP5_13TeV_pythia8/crab_Taustar_m375_2018/210322_184517/0000/ | grep \.root`
xrdcp -f Taustar_m375_2018.root ${OUTPUTDIR}
rm Taustar_m375_2018.root

python haddnano.py Taustar_m750_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/Taustar_TauG_L10000_m750_CP5_13TeV_pythia8/crab_Taustar_m750_2018_rsb/210322_202506/0000/ | grep \.root`
xrdcp -f Taustar_m750_2018.root ${OUTPUTDIR}
rm Taustar_m750_2018.root

python haddnano.py QCD_Mu15_2018.root `xrdfsls -u /store/user/fojensen/cmsdas_22032021/QCD_Pt-20toInf_MuEnrichedPt15_TuneCP5_13TeV_pythia8/crab_QCD_Mu15_2018/210322_190322/0000/ | grep \.root`
xrdcp -f QCD_Mu15_2018.root ${OUTPUTDIR}
rm QCD_Mu15_2018.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
