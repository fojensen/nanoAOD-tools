python ../scripts/haddnano.py ./outputData/SingleMuon_2018D.root `xrdfsls -u /store/user/fojensen/tauHats_22062020/SingleMuon/crab_tauHats_SingleMuon_Run2018D/200622_235531/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/TTJets.root `xrdfsls -u /store/user/fojensen/tauHats_20062020/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_TTJets/200622_032814/0000/ | grep \.root` 
python ../scripts/haddnano.py ./outputData/WJetsToLNu.root `xrdfsls -u /store/user/fojensen/tauHats_20062020/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_WJetsToLNu/200622_032910/0000/ | grep \.root` 
python ../scripts/haddnano.py ./outputData/DYJetsToLL_M-50.root `xrdfsls -u /store/user/fojensen/tauHats_20062020/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_DYJetsToLL_M-50/200622_033004/0000/ | grep \.root`
root splitDY.c+
