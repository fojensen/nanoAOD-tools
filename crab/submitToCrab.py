import math
import json
import os
import time

#year = '2016'
#infile = 'mc_2016.json'
#infile = 'data_2016.json'

#year = '2017'
#infile = 'mc_2017.json'
#infile = 'data_2017.json'

year = '2018'
#infile = 'mc_2018.json'
infile = 'data_2018.json'
#infile = 'embedded_2018.json'

with open(infile) as json_file:

   data = json.load(json_file)
 
   for p in data['people']:
      f = open("./crabSubmits/"+p['name']+"_"+year+".py","w+")
      
      f.write("import CRABClient\n")
      f.write("from WMCore.Configuration import Configuration\n")
      f.write("config = Configuration()\n")
      f.write("\n")
      
      f.write("config.section_('General')\n")
      f.write("config.General.requestName='ExcitingAnalyzer_"+p['name']+"_"+year+"'\n")
      f.write("config.General.workArea='crab_projects'\n")
      f.write("config.General.transferOutputs=True\n")
      f.write("config.General.transferLogs=True\n")
      f.write("\n")
      
      f.write("config.section_('JobType')\n")
      f.write("config.JobType.pluginName='Analysis'\n")
      f.write("config.JobType.psetName='PSet.py'\n")
      f.write("config.JobType.scriptExe='crab_script.sh'\n")
      f.write("config.JobType.inputFiles=['keep_and_drop.txt', 'crab_script.py', '../scripts/haddnano.py']\n")
      f.write("config.JobType.sendPythonFolder=True\n")
      f.write("config.JobType.allowUndistributedCMSSW=True\n")
      f.write("\n")
   
      f.write("config.section_('Data')\n")
      f.write("config.Data.inputDataset='"+p['inputDataset']+"'\n")
      if 'lumiMask' in p:
          f.write("config.Data.lumiMask='"+p['lumiMask']+"'\n")
          #f.write("config.Data.splitting='Automatic'\n")
      #else:
      f.write("config.Data.splitting='FileBased'\n")
      #f.write("config.Data.unitsPerJob=1\n") 
      nFiles = p['nFiles']
      fpj = float(nFiles) / 10000
      fpj = int(math.ceil(fpj))
      f.write("config.Data.unitsPerJob=%d\n" % fpj)

      f.write("config.Data.inputDBS='global'\n")
      #f.write("config.Data.inputDBS='phys03'\n")
      f.write("config.Data.outLFNDirBase='/store/user/fjensen/excitedTau_17102020/'\n")
      f.write("config.Data.publication=False\n")
      f.write("\n")

      f.write("config.section_('Site')\n")
      f.write("config.Site.storageSite='T3_US_FNALLPC'\n")
      f.close()
     
      os.system("crab submit -c " + f.name)

