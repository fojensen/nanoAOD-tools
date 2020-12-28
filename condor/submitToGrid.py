username = "fojensen"

import json
import os

#make ui
import datetime as dt
a = dt.datetime.now()
ui = int(a.strftime('%Y%m%d%H%M%S'))

condordir = "condor_project_%s" % ui
if not os.path.isdir(condordir):
    os.system("mkdir %s" % condordir)
    os.system("eos root://cmseos.fnal.gov mkdir /store/user/fojensen/ZLongExercise_%s" % ui)
else :
    print("directory %s exists" % condordir)
    exit()

## prepare working area for job ##
os.chdir("%s/src" % os.getenv("CMSSW_BASE"))
#tar NanoAODTools
cmdtar = "tar -zcvf PhysicsTools_%s.tgz --exclude='*.root' --exclude='*.pdf' --exclude='*.pyc' --exclude='PhysicsTools/NanoAODTools/crab/crab_projects' --exclude='PhysicsTools/NanoAODTools/.git' --exclude='PhysicsTools/NanoAODTools/condor' PhysicsTools" % ui
os.system(cmdtar)
#copy it to eos
cmdeos = "xrdcp -f PhysicsTools_%s.tgz root://cmseos.fnal.gov//store/user/%s/ZLongExercise_%s" % (ui, username, ui)
os.system(cmdeos)
#move it to your projects directory
cmdmv = "mv PhysicsTools_%s.tgz ./PhysicsTools/NanoAODTools/condor/%s" % (ui, condordir)
os.system(cmdmv)
os.chdir("%s/src/PhysicsTools/NanoAODTools/condor" % os.getenv("CMSSW_BASE"))

inputDatasets = ['DYJetsToLL_M50', 'TTJets', 'WJetsToLNu', 'QCD_Pt20toInf_MuEnrichedPt15']
inputDatasets += ['SingleMuon_2018A', 'SingleMuon_2018B', 'SingleMuon_2018C', 'SingleMuon_2018D_1', 'SingleMuon_2018D_2']
inputDatasets += ['EGamma_2018A', 'EGamma_2018B', 'EGamma_2018C', 'EGamma_2018D_1', 'EGamma_2018D_2']
inputDatasets += ['Tau_2018A', 'Tau_2018B', 'Tau_2018C', 'Tau_2018D_1', 'Tau_2018D_2']

for dataset in inputDatasets:
    print("%s_%s" % (dataset, ui))

    f_bash = open("%s/condor_%s_%s.sh" % (condordir, dataset, ui), "w+")
    f_bash.write('#!/bin/bash\n')
    f_bash.write('echo "Starting condor job on " `date` #Date/time of start of job\n')
    f_bash.write('echo "Running on: `uname -a`" #Condor job is running on this node\n')
    f_bash.write('echo "System software: `cat /etc/redhat-release`" #Operating System on that node\n')
    f_bash.write('source /cvmfs/cms.cern.ch/cmsset_default.sh\n')
    f_bash.write('scramv1 project CMSSW CMSSW_10_6_19 # cmsrel is an alias not on the workers\n')
    f_bash.write('cd CMSSW_10_6_19/src/\n')
    f_bash.write('eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers\n')
    f_bash.write('xrdcp -s root://cmseos.fnal.gov//store/user/%s/ZLongExercise_%s/PhysicsTools_%s.tgz .\n' % (username, ui, ui))
    f_bash.write('tar -xvf PhysicsTools_%s.tgz\n' % ui)
    f_bash.write('cd PhysicsTools/NanoAODTools\n')
    f_bash.write('scram b\n')
    f_bash.write('cd ./crab/\n')
    f_bash.write('python crab_script.py root://cmseos.fnal.gov//store/user/fojensen/cmsdasskims/%s.root\n' % dataset)
    f_bash.write('xrdcp -f tree.root root://cmseos.fnal.gov//store/user/%s/ZLongExercise_%s/%s_Processed.root\n' % (username, ui, dataset))
    f_bash.write('echo "Ending condor job on " `date` #Date/time of end of job\n')
    f_bash.close()

    f_jdl = open("%s/condor_%s_%s.jdl" % (condordir, dataset, ui), "w+")
    f_jdl.write('universe = vanilla\n')
    f_jdl.write('Executable = %s/condor_%s_%s.sh\n' % (condordir, dataset, ui))
    f_jdl.write('should_transfer_files = YES\n')
    f_jdl.write('when_to_transfer_output = ON_EXIT\n')
    f_jdl.write('Output = %s/condor_%s_%s.stdout\n' % (condordir, dataset, ui))
    f_jdl.write('Error = %s/condor_%s_%s.stderr\n' % (condordir, dataset, ui))
    f_jdl.write('Log = %s/condor_%s_%s.log\n' % (condordir, dataset, ui))
    f_jdl.write('Queue 1\n')
    f_jdl.close()

    os.system("condor_submit %s/condor_%s_%s.jdl" % (condordir, dataset, ui))

print("\n")
print("*** condor_project directory: %s\n" % condordir)