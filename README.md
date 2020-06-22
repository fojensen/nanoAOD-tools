# Install CMSSW and clone NanoAODTools
cmsrel CMSSW_10_2_18
cd CMSSW_10_2_18/src/
cmsenv

git clone --single-branch --branch tauHats https://github.com/fojensen/nanoAOD-tools.git
scram build -j 4


