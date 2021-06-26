cp ../scripts/haddnano.py /uscmst1b_scratch/lpc1/3DayLifetime/fojensen/
cd /uscmst1b_scratch/lpc1/3DayLifetime/fojensen

setenv OUTPUTDIR "root://cmseos.fnal.gov//store/user/fojensen/cmsdas_26042021/"

python haddnano.py Taustar_m175_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m175_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m250_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m250_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m375_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m375_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m500_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m500_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m625_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m625_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m750_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m750_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m1000_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m1000_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m1250_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m1250_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m1500_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m1500_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m1750_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m1750_2017.root ${OUTPUTDIR}

python haddnano.py Taustar_m2000_2017.root `xrdfsls -u | grep \.root`
xrdcp -f Taustar_m2000_2017.root ${OUTPUTDIR}

rm Taustar_m*_2017.root
cd /uscms_data/d3/fojensen/excitedTau_06042021/CMSSW_10_6_20/src/PhysicsTools/NanoAODTools/analysis