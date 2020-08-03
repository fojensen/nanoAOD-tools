#python ./PhysicsTools/NanoAODTools/scripts/haddnano.py ./outputData/ `xrdfsls -u | grep \.root`

python ../scripts/haddnano.py ./outputData/SingleMuon_2018A.root `xrdfsls -u /store/user/fojensen/taustar_30072020/SingleMuon/crab_ExcitingAnalyzer_SingleMuon_Run2018A/200730_230209/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/SingleMuon_2018B.root `xrdfsls -u /store/user/fojensen/taustar_30072020/SingleMuon/crab_ExcitingAnalyzer_SingleMuon_Run2018B/200730_230258/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/SingleMuon_2018C.root `xrdfsls -u /store/user/fojensen/taustar_30072020/SingleMuon/crab_ExcitingAnalyzer_SingleMuon_Run2018C/200730_230349/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/SingleMuon_2018D.root `xrdfsls -u /store/user/fojensen/taustar_30072020/SingleMuon/crab_ExcitingAnalyzer_SingleMuon_Run2018D/200730_230439/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/SingleMuon_2018.root ./outputData/SingleMuon_2018A.root ./outputData/SingleMuon_2018B.root ./outputData/SingleMuon_2018C.root ./outputData/SingleMuon_2018D.root
