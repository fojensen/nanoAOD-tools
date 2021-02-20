username = "fojensen"
#runfile = "./python/postprocessing/examples/example_postproc.py"
runfile = "./crab/crab_script.py"

import json
import os

#make ui
import datetime as dt
a = dt.datetime.now()
ui = int(a.strftime('%d%H%M%S'))

condordir = "condor_project_%s" % ui
if not os.path.isdir(condordir):
    os.system("mkdir %s" % condordir)
    os.system("eos root://cmseos.fnal.gov mkdir /store/user/%s/processedEmbedded_%s" % (username, ui))
else :
    print("directory %s exists" % condordir)
    exit()

## prepare working area for job ##
os.chdir("%s/src" % os.getenv("CMSSW_BASE"))
#tar NanoAODTools
cmdtar = "tar -zcvf PhysicsTools_%s.tgz --exclude='*.root' --exclude='*.pdf' --exclude='*.pyc' --exclude='PhysicsTools/NanoAODTools/crab/crab_projects' --exclude='PhysicsTools/NanoAODTools/.git' --exclude='PhysicsTools/NanoAODTools/condor' PhysicsTools" % ui
os.system(cmdtar)
#copy it to eos
cmdeos = "xrdcp -f PhysicsTools_%s.tgz root://cmseos.fnal.gov//store/user/%s/processedEmbedded_%s" % (ui, username, ui)
os.system(cmdeos)
#move it to your projects directory
cmdmv = "mv PhysicsTools_%s.tgz ./PhysicsTools/NanoAODTools/condor/%s" % (ui, condordir)
os.system(cmdmv)
os.chdir("%s/src/PhysicsTools/NanoAODTools/condor" % os.getenv("CMSSW_BASE"))

inputDatasets  = ['Embedding2018A_ElTauFinalState', 'Embedding2018B_ElTauFinalState', 'Embedding2018C_ElTauFinalState', 'Embedding2018D_ElTauFinalState_0', 'Embedding2018D_ElTauFinalState_1', 'Embedding2018D_ElTauFinalState_2']
inputDatasets += ['Embedding2018A_MuTauFinalState', 'Embedding2018B_MuTauFinalState', 'Embedding2018C_MuTauFinalState', 'Embedding2018D_MuTauFinalState_0', 'Embedding2018D_MuTauFinalState_1', 'Embedding2018D_MuTauFinalState_2']
inputDatasets += ['Embedding2018A_TauTauFinalState', 'Embedding2018B_TauTauFinalState', 'Embedding2018C_TauTauFinalState', 'Embedding2018D_TauTauFinalState_0', 'Embedding2018D_TauTauFinalState_1', 'Embedding2018D_TauTauFinalState_2']

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
    #f_bash.write('should be in src; pwd, ls:\n')
    #f_bash.write('pwd\n')
    #f_bash.write('ls\n')
    f_bash.write('xrdcp -s root://cmseos.fnal.gov//store/user/%s/processedEmbedded_%s/PhysicsTools_%s.tgz .\n' % (username, ui, ui))
    f_bash.write('tar -xvf PhysicsTools_%s.tgz\n' % ui)
    f_bash.write('cd PhysicsTools/NanoAODTools\n')
    f_bash.write('scram b\n')
    #f_bash.write('should be in NanoAODTools; pwd, ls:\n')
    #f_bash.write('pwd\n')
    #f_bash.write('ls\n')
    f_bash.write('python %s root://cmseos.fnal.gov//store/user/fojensen/embeddedSamples/%s.root\n' % (runfile, dataset))
    f_bash.write('xrdcp -f tree.root root://cmseos.fnal.gov//store/user/%s/processedEmbedded_%s/%s_Processed.root\n' % (username, ui, dataset))
    f_bash.write('echo "Ending condor job on " `date` #Date/time of end of job\n')
    f_bash.close()

    f_jdl = open("%s/condor_%s_%s.jdl" % (condordir, dataset, ui), "w+")
    f_jdl.write('universe = vanilla\n')
    f_jdl.write('Executable = %s/condor_%s_%s.sh\n' % (condordir, dataset, ui))
    f_jdl.write('request_memory = 5000\n')
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

