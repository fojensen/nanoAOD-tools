python haddnano.py DYJetsToLL_M50.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/crab_cmsdas_DYJetsToLL_M-50/201224_062006/0000/ | grep \.root`
xrdcp -f DYJetsToLL_M50.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm DYJetsToLL_M50.root

python haddnano.py TTJets.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/crab_cmsdas_TTJets/201224_062108/0000/ | grep \.root`
xrdcp -f TTJets.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm TTJets.root

python haddnano.py WJetsToLNu.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_cmsdas_WJetsToLNu/201224_062310/0000/ | grep \.root`
xrdcp -f WJetsToLNu.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm WJetsToLNu.root

python haddnano.py QCD_Pt20toInf_MuEnrichedPt15.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/QCD_Pt-20toInf_MuEnrichedPt15_TuneCP5_13TeV_pythia8/crab_cmsdas_QCD_Pt-20toInf_MuEnrichedPt15/201224_062210/0000/ | grep \.root`
xrdcp -f QCD_Pt20toInf_MuEnrichedPt15.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm QCD_Pt20toInf_MuEnrichedPt15.root

python haddnano.py SingleMuon_2018A.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/SingleMuon/crab_cmsdas_SingleMuon_Run2018A/201224_082919/0000/ | grep \.root`
xrdcp -f SingleMuon_2018A.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm SingleMuon_2018A.root

python haddnano.py SingleMuon_2018B.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/SingleMuon/crab_cmsdas_SingleMuon_Run2018B/201224_083017/0000/ | grep \.root`
xrdcp -f SingleMuon_2018B.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm SingleMuon_2018B.root

python haddnano.py SingleMuon_2018C.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/SingleMuon/crab_cmsdas_SingleMuon_Run2018C/201224_083116/0000/ | grep \.root`
xrdcp -f SingleMuon_2018C.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm SingleMuon_2018C.root

python haddnano.py SingleMuon_2018D.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/SingleMuon/crab_cmsdas_SingleMuon_Run2018D/201223_235004/0000/ | grep \.root`
xrdcp -f SingleMuon_2018D.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm SingleMuon_2018D.root

python haddnano.py EGamma_2018A.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/EGamma/crab_cmsdas_EGamma_Run2018A/201224_083215/0000/ | grep \.root`
xrdcp -f EGamma_2018A.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm EGamma_2018A.root

python haddnano.py EGamma_2018B.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/EGamma/crab_cmsdas_EGamma_Run2018B/201224_083312/0000/ | grep \.root`
xrdcp -f EGamma_2018B.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm EGamma_2018B.root

python haddnano.py EGamma_2018C.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/EGamma/crab_cmsdas_EGamma_Run2018C/201224_083411/0000/ | grep \.root`
xrdcp -f EGamma_2018C.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm EGamma_2018C.root

python haddnano.py EGamma_2018D.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/EGamma/crab_cmsdas_EGamma_Run2018D/201223_235103/0000/ | grep \.root`
xrdcp -f EGamma_2018D.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm EGamma_2018D.root

python haddnano.py Tau_2018A.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/Tau/crab_cmsdas_Tau_Run2018A/201224_083509/0000/ | grep \.root`
xrdcp -f Tau_2018A.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm Tau_2018A.root

python haddnano.py Tau_2018B.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/Tau/crab_cmsdas_Tau_Run2018B/201224_083606/0000/ | grep \.root`
xrdcp -f Tau_2018B.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm Tau_2018B.root

python haddnano.py Tau_2018C.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/Tau/crab_cmsdas_Tau_Run2018C/201224_083704/0000/ | grep \.root`
xrdcp -f Tau_2018C.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm Tau_2018C.root

python haddnano.py Tau_2018D.root `xrdfsls -u /store/user/fojensen/cmsdas_23122020/Tau/crab_cmsdas_Tau_Run2018D/201223_235201/0000/ | grep \.root`
xrdcp -f Tau_2018D.root root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/
rm Tau_2018D.root
