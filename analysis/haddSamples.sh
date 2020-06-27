python ../scripts/haddnano.py ./outputData/SingleMuon_2018D.root `xrdfsls -u /store/user/fojensen/tauHats_27062020/SingleMuon/crab_tauHats_SingleMuon_Run2018D/200627_170754/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/TTJets.root `xrdfsls -u /store/user/fojensen/tauHats_27062020/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_TTJets/200627_170901/0000/ | grep \.root` 
python ../scripts/haddnano.py ./outputData/WJetsToLNu.root `xrdfsls -u /store/user/fojensen/tauHats_27062020/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_WJetsToLNu/200627_171004/0000/ | grep \.root` 
python ../scripts/haddnano.py ./outputData/DYJetsToLL_M-50.root `xrdfsls -u /store/user/fojensen/tauHats_27062020/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_DYJetsToLL_M-50/200627_171116/0000/ | grep \.root`
root splitDY.c+
