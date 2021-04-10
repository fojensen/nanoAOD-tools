#!/bin/bash

cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_10042021/"

python haddnano.py WW_2018.root `xrdfsls -u | grep \.root`
xrdcp -f WW_2018.root ${OUTPUTDIR}
rm WW_2018.root

python haddnano.py WZ_2018.root `xrdfsls -u | grep \.root`
xrdcp -f WZ_2018.root ${OUTPUTDIR}
rm WZ_2018.root

python haddnano.py ZZ_2018.root `xrdfsls -u | grep \.root`
xrdcp -f ZZ_2018.root ${OUTPUTDIR}
rm ZZ_2018.root

python haddnano.py ST_tW_antitop_2018.root `xrdfsls -u | grep \.root`
xrdcp -f ST_tW_antitop_2018.root ${OUTPUTDIR}
rm ST_tW_antitop_2018.root

python haddnano.py ST_tW_top_2018.root `xrdfsls -u | grep \.root`
xrdcp -f ST_tW_top_2018.root ${OUTPUTDIR}
rm ST_tW_top_2018.root

python haddnano.py ST_t_channel_top_2018.root `xrdfsls -u | grep \.root`
xrdcp -f ST_t_channel_top_2018.root ${OUTPUTDIR}
rm ST_t_channel_top_2018.root

python haddnano.py ST_t_channel_antitop_2018.root `xrdfsls -u | grep \.root`
xrdcp -f ST_t_channel_antitop_2018.root ${OUTPUTDIR}
rm ST_t_channel_antitop_2018.root

python haddnano.py Taustar_m250_2018.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m250_2018.root ${OUTPUTDIR}
rm Taustar_m250_2018.root

python haddnano.py Taustar_m625_2018.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m625_2018.root ${OUTPUTDIR}
rm Taustar_m625_2018.root

python haddnano.py TTTo2L2Nu_2018.root `xrdfsls -u | grep \.root`
xrdcp -f TTTo2L2Nu_2018.root ${OUTPUTDIR}
rm TTTo2L2Nu_2018.root

python haddnano.py TTToSemiLeptonic_2018.root `xrdfsls -u | grep \.root` 
xrdcp -f TTToSemiLeptonic_2018.root ${OUTPUTDIR}
rm TTToSemiLeptonic_2018.root

cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis
