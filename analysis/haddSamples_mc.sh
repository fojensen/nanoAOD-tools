#python ../scripts/haddnano.py ./outputData/ `xrdfsls -u | grep \.root`

python ../scripts/haddnano.py ./outputData/DY01234JetsToLL_M-50.root `xrdfsls -u /store/user/fojensen/taustar_01082020/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ExcitingAnalyzer_DYJetsToLL_M-50/200801_183116/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/DY1JetsToLL_M-50.root `xrdfsls -u /store/user/fojensen/taustar_01082020/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ExcitingAnalyzer_DY1JetsToLL_M-50/200801_183518/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/DY2JetsToLL_M-50.root `xrdfsls -u /store/user/fojensen/taustar_01082020/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ExcitingAnalyzer_DY2JetsToLL_M-50/200801_183608/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/DY3JetsToLL_M-50.root `xrdfsls -u /store/user/fojensen/taustar_01082020/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ExcitingAnalyzer_DY3JetsToLL_M-50/200801_183657/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/DY4JetsToLL_M-50.root `xrdfsls -u /store/user/fojensen/taustar_01082020/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ExcitingAnalyzer_DY4JetsToLL_M-50/200801_183745/0000/ | grep \.root`

python ../scripts/haddnano.py ./outputData/DYJetsToLL_M-10to50.1.root `xrdfsls -u /store/user/fojensen/taustar_01082020/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ExcitingAnalyzer_DYJetsToLL_M-10to50/200801_224907/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/DYJetsToLL_M-10to50.2.root `xrdfsls -u /store/user/fojensen/taustar_01082020/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_ExcitingAnalyzer_DYJetsToLL_M-10to50_ext1/200801_232339/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/DYJetsToLL_M-10to50.root ./outputData/DYJetsToLL_M-10to50.1.root ./outputData/DYJetsToLL_M-10to50.2.root
rm ./outputData/DYJetsToLL_M-10to50.1.root
rm ./outputData/DYJetsToLL_M-10to50.2.root

python ../scripts/haddnano.py ./outputData/TTTo2L2Nu.root `xrdfsls -u /store/user/fojensen/taustar_01082020/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/crab_ExcitingAnalyzer_TTTo2L2Nu/200801_183204/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/WW.root `xrdfsls -u /store/user/fojensen/taustar_01082020/WW_TuneCP5_13TeV-pythia8/crab_ExcitingAnalyzer_WW/200801_183253/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/WZ.root `xrdfsls -u /store/user/fojensen/taustar_01082020/WZ_TuneCP5_13TeV-pythia8/crab_ExcitingAnalyzer_WZ/200801_183341/0000/ | grep \.root`
python ../scripts/haddnano.py ./outputData/ZZ.root `xrdfsls -u /store/user/fojensen/taustar_01082020/ZZ_TuneCP5_13TeV-pythia8/crab_ExcitingAnalyzer_ZZ/200801_183430/0000/ | grep \.root`

