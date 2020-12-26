import json
import os

#inputDatasets = ['DYJetsToLL_M50', 'TTJets', 'WJetsToLNu']
#inputDatasets += ['SingleMuon_2018A', 'SingleMuon_2018B', 'SingleMuon_2018C', 'SingleMuon_2018D']
inputDatasets = ['EGamma_2018A', 'EGamma_2018B', 'EGamma_2018C', 'EGamma_2018D']
inputDatasets += ['Tau_2018A', 'Tau_2018B', 'Tau_2018C', 'Tau_2018D']

for dataset in inputDatasets:
    print dataset

    f_bash = open("condor_%s.sh" % dataset, "w+") 
    f_bash.write('#!/bin/bash\n')
    f_bash.write('echo "Starting job on " `date` #Date/time of start of job\n')
    f_bash.write('echo "Running on: `uname -a`" #Condor job is running on this node\n')
    f_bash.write('echo "System software: `cat /etc/redhat-release`" #Operating System on that node\n')
    f_bash.write('source /cvmfs/cms.cern.ch/cmsset_default.sh\n')
    f_bash.write('scramv1 project CMSSW CMSSW_10_6_19 # cmsrel is an alias not on the workers\n')
    f_bash.write('cd CMSSW_10_6_19/src/\n')
    f_bash.write('eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers\n')
    f_bash.write('xrdcp -s root://cmseos.fnal.gov//store/user/fojensen/PhysicsTools.tgz .\n')
    f_bash.write('tar zxvf PhysicsTools.tgz\n')
    f_bash.write('cd PhysicsTools/NanoAODTools\n')
    f_bash.write('scram b\n')
    f_bash.write('cd ./crab/\n')
    f_bash.write('python crab_script.py root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/%s.root\n' % dataset)
    f_bash.write('xrdcp tree.root root://cmseos.fnal.gov//store/user/fojensen/ZTauTauProcessedFiles/%s_Processed.root\n' % dataset)
    f_bash.write('echo "Ending job on " `date` #Date/time of end of job\n')
    f_bash.close()

    f_jdl = open("condor_%s.jdl" % dataset, "w+")
    f_jdl.write('universe = vanilla\n')
    f_jdl.write('Executable = condor_%s.sh\n' % dataset)
    f_jdl.write('should_transfer_files = YES\n')
    f_jdl.write('when_to_transfer_output = ON_EXIT\n')
    f_jdl.write('Output = condor_%s.stdout\n' % dataset)
    f_jdl.write('Error = condor_%s.stderr\n' % dataset)
    f_jdl.write('Log = condor_%s.log\n' % dataset)
    f_jdl.write('Queue 1\n')
    f_jdl.close()

    os.system("condor_submit condor_%s.jdl" % dataset)

