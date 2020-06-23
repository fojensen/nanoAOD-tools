import json

data = {}
data['people'] = []

data['people'].append({
   'name': 'SingleMuon_Run2018D',
   'das': '/SingleMuon/Run2018D-Nano25Oct2019-v1/NANOAOD',
   'lumiMask': 'Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt',
   'nEvents': '513867253',
   'nFiles': '252',
})

data['people'].append({
   'name': 'TTJets',
   'das': '/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv6-Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/NANOAODSIM',
   'nEvents': '10244307',
   'nFiles': '13',
   'isMC': True,
   'xs': '831.76',
})

data['people'].append({
   'name': 'WJetsToLNu',
   'das': '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv6-Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/NANOAODSIM',
   'nEvents': '70454125',
   'nFiles': '50',
   'xs': '61334.9', 
})

data['people'].append({
   'name': 'DYJetsToLL_M-50',
   'das': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv6-Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/NANOAODSIM',
   'nEvents': '100194597',
   'nFiles': '58',
   'xs': '6025.2', 
})
#data['people'].append({
#    'name': 'QCD_Pt_30to50',
#    'das': '/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIIAutumn18NanoAODv6-Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/NANOAODSIM',
#    'nEvents': '18872000',
#    'nFiles': '11',
#    'xs': '19046100.',
#})

with open('samples.json', 'w') as outfile:
   json.dump(data, outfile)

