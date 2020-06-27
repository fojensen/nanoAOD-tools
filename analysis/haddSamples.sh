#python ../scripts/haddnano.py ./outputData/SingleMuon_2018D.root `xrdfsls -u /store/user/fojensen/tauHats_23062020/SingleMuon/crab_tauHats_SingleMuon_Run2018D/200624_001943/0000/ | grep \.root`
#python ../scripts/haddnano.py ./outputData/TTJets.root `xrdfsls -u /store/user/fojensen/tauHats_23062020/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_TTJets/200624_002047/0000/ | grep \.root` 
#python ../scripts/haddnano.py ./outputData/WJetsToLNu.root `xrdfsls -u /store/user/fojensen/tauHats_23062020/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_WJetsToLNu/200624_002152/0000/ | grep \.root` 
#python ../scripts/haddnano.py ./outputData/DYJetsToLL_M-50.root `xrdfsls -u /store/user/fojensen/tauHats_23062020/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_DYJetsToLL_M-50/200624_002256/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/DYJetsToLL_M-50.root `xrdfsls -u /store/user/fojensen/tauHats_23062020/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_tauHats_DY2nd_DYJetsToLL_M-50/200624_203929/0000/ | grep \.root`
root splitDY.c+
