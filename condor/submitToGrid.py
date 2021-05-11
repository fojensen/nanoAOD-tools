import json
import os

#import datetime as dt
#a = dt.datetime.now()
#ui = int(a.strftime('%d%H%M%S'))
#condordir = "condor_project_%s" % ui
#if not os.path.isdir(condordir):
#    os.system("mkdir %s" % condordir)
#else :
#    print("directory %s exists" % condordir)
#    exit()

masses = [175, 250, 375, 500, 625, 750, 1000, 1250, 1500, 1750, 2000, 2500, 3000, 3500, 4000, 4500, 5000]
#masses = [250]
channels = ['Electron', 'Muon', 'Tau', 'MuonEG']
#channels = ['Tau']

for mass in masses:
    for channel in channels:
        print("%s %d" % (channel, mass))
        shname = "condor.%s_m%d.sh" % (channel, mass)
        f_bash = open(shname, "w+")
        f_bash.write('#!/bin/bash\n')
        f_bash.write('echo "Starting condor job on " `date` #Date/time of start of job\n')
        f_bash.write('echo "Running on: `uname -a`" #Condor job is running on this node\n')
        f_bash.write('echo "System software: `cat /etc/redhat-release`" #Operating System on that node\n')
        f_bash.write('source /cvmfs/cms.cern.ch/cmsset_default.sh\n')
        f_bash.write('scramv1 project CMSSW CMSSW_10_6_19 # cmsrel is an alias not on the workers\n')
        f_bash.write('cd CMSSW_10_6_19/src/\n')
        f_bash.write('eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers\n')
        f_bash.write('echo $CMSSW_BASE "is the CMSSW we created on the local worker node"\n')
        f_bash.write('cd ${_CONDOR_SCRATCH_DIR}\n')
        f_bash.write('pwd\n')
        cmd1 = "root -b 'runAllWrapper.c+(\"%s\", %d, true)'" % (channel, mass)
        f_bash.write(cmd1+'\n')
        f_bash.write('echo "Ending condor job on " `date` #Date/time of end of job\n')
        f_bash.close()

        jdlname = "condor.%s_m%d.jdl" % (channel, mass)
        f_jdl = open(jdlname, "w+")
        f_jdl.write('universe = vanilla\n')
        f_jdl.write('Executable = %s\n' % (shname))
        if channel=="Tau": f_jdl.write('request_memory = 5000\n')
        f_jdl.write('Should_Transfer_Files = YES\n')
        f_jdl.write('Transfer_Input_Files = ../analysis/runAllWrapper.c, ../analysis/addOverflow.h\n')
        f_jdl.write('Transfer_Output_Files = %s_m%d.root, %s_m%d.pdf\n' % (channel, mass, channel, mass))
        f_jdl.write('WhenToTransferOutput = ON_EXIT\n')
        f_jdl.write('Output = condor.%s_m%d.stdout\n' % (channel, mass))
        f_jdl.write('Error = condor.%s_m%d.stderr\n' % (channel, mass))
        f_jdl.write('Log = condor.%s_m%d.log\n' % (channel, mass))
        f_jdl.write('Queue 1\n')
        f_jdl.close()
        os.system("condor_submit %s" % jdlname)

os.system("condor_q")
