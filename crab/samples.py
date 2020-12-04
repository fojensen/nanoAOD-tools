import json

data = {}
data['people'] = []

data['people'].append({
    'name': 'SingleMuon_Run2018D',
    'das': '/SingleMuon/Run2018D-Nano02Dec2019_12Nov2019_UL2018-v2/NANOAOD',
    'lumiMask': 'Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt',
    'nEvents': '513909894',
    'nFiles': '395',
})

data['people'].append({
    'name': 'TTJets',
    'das': '/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2/NANOAODSIM',
    'nEvents': '148740576',
    'nFiles': '716',
    'isMC': True,
    'xs': '831.76',
})

data['people'].append({
    'name': 'WJetsToLNu',
    'das': '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v1/NANOAODSIM',
    'nEvents': '56999392',
    'nFiles': '27',
    'isMC': True,
    'xs': '61334.9', 
})

data['people'].append({
    'name': 'DYJetsToLL_M-50',
    'das': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v1/NANOAODSIM',
    'nEvents': '104017741',
    'nFiles': '57',
    'isMC': True,
    'xs': '6025.2', 
})

data['people'].append({
    'name': 'QCD_Pt_30to50',
    'das': '/QCD_Pt_30to50_TuneCP5_13TeV_pythia8/RunIISummer19UL18NanoAOD-PUForMUOVal_106X_upgrade2018_realistic_v11_L1v1-v3/NANOAODSIM',
    'nEvents': '19976600',
    'nFiles': '146',
    'isMC': True,
    'xs': '19046100.',
})

#/WZ_TuneCP5_13TeV-pythia8/RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2/NANOAODSIM
#/WW_TuneCP5_13TeV-pythia8/RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2/NANOAODSIM
#/ZZ_TuneCP5_13TeV-pythia8/RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2/NANOAODSIM
#/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v1/NANOAODSIM
#/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL18NanoAOD-106X_upgrade2018_realistic_v11_L1v1-v2/NANOAODSIM

with open('samples.json', 'w') as outfile:
   json.dump(data, outfile)

