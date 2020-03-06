import json
import os

#infile = 'data_2018.json'
infile = 'mc_2018.json'

with open(infile) as json_file:

   data = json.load(json_file)
   
   for p in data['people']:
      f = open("./crabSubmits/"+p['name']+".py","w+")
      
      f.write("from WMCore.Configuration import Configuration\n")
      f.write("from CRABClient.UserUtilities import config, getUsernameFromSiteDB\n")

      f.write("config = config()\n")
      f.write("\n")
      
      f.write("config.section_('General')\n")
      f.write("config.General.requestName = 'ExcitingAnalyzer_"+p['name']+"'\n")
      f.write("config.General.workArea = 'crab_projects'\n")
      f.write("config.General.transferOutputs = True\n")
      f.write("config.General.transferLogs = True\n")
      f.write("\n")
      
      f.write("config.section_('JobType')\n")
      f.write("config.JobType.pluginName = 'Analysis'\n")
      f.write("config.JobType.psetName = 'PSet.py'\n")
      f.write("config.JobType.scriptExe = 'crab_script.sh'\n")
 #     if 'isMC' in p:
  #       if p['isMC']==True:
   #         pyCfgParams = []
    #        pyCfgParams.append('isMC=True')
     #       xsWeight = eval(p['xs'])/eval(p['nEvents'])
#            pyCfgParams.append('xsWeight='+str(xsWeight))
      #      f.write("config.JobType.pyCfgParams = " + str(pyCfgParams) + "\n")
      f.write("config.JobType.inputFiles = ['keep_and_drop.txt', 'crab_script.py', '../scripts/haddnano.py']\n")
      f.write("config.JobType.sendPythonFolder=True\n")
      f.write("\n")
   
      f.write("config.section_('Data')\n")
      if 'json' in p:
         f.write("config.Data.lumiMask='Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'\n")
      f.write("config.Data.inputDataset = '"+p['das']+"'\n")
      f.write("config.Data.inputDBS='global'\n")
      #f.write("config.Data.splitting='Automatic'\n")
      f.write("config.Data.splitting = 'FileBased'\n")
      f.write("config.Data.unitsPerJob = 1\n")
      f.write("config.Data.outLFNDirBase = '/store/user/fjensen/ExcitingAnalyzer_vA'\n")
      f.write("config.Data.publication = False\n")
      f.write("\n")

      f.write("config.section_('Site')\n")
      f.write("config.Site.storageSite = 'T3_US_FNALLPC'\n")
      f.write("\n")

      f.close()

      # actually submit jobs or not
      os.system("crab submit -c " + f.name)
      #os.system("crab submit -c " + f.name + " --dryrun")

