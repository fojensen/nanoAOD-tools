import json

data = {}
data['people'] = []
isMC_ = True
year = '2017'

data['people'].append({
    'name': 'DYJetsToLL_M50_2017',
    'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '102486448',
    'nFiles': '72',
    'isMC': isMC_,
    'xs': '6077.22',
    'year': year
})

data['people'].append({
    'name': 'DY1JetsToLL_M50_2017',
    'inputDataset': '/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '66096393',
    'nFiles': '45',
    'isMC': isMC_,
    'xs': '1112.14',
    'year': year
})

data['people'].append({
    'name': 'DY2JetsToLL_M50_2017',
    'inputDataset': '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM', 
    'nEvents': '28389776',
    'nFiles': '25',
    'isMC': isMC_,
    'xs': '344.987',
    'year': year
})

data['people'].append({
    'name': 'DY3JetsToLL_M50_2017',
    'inputDataset': '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '17510095',
    'nFiles': '19',
    'isMC': isMC_,
    'xs': '102.468',
    'year': year
})

data['people'].append({
    'name': 'DY4JetsToLL_M50_2017',
    'inputDataset': '/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '7575236',
    'nFiles': '12',
    'isMC': isMC_,
    'xs': '48.8496',
    'year': year
})

data['people'].append({
    'name': 'TTToSemiLeptonic_2017',
    'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '114058500',
    'nFiles': '119',
    'isMC': isMC_,
    'xs': '365.34',
    'year': year
})

data['people'].append({
    'name': 'TTTo2L2Nu_2017', 
    'inputDataset': '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '106978000',
    'nFiles': '85',
    'isMC': isMC_,
    'xs': '88.29',
    'year': year
})

data['people'].append({
    'name': 'ST_tW_antitop_2017',
    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '9191369',
    'nFiles': '15',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf
    'year': year
})

data['people'].append({
    'name': 'ST_tW_top_2017',
    'inputDataset': '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '10041965',
    'nFiles': '14',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf 35.85 * (1-(1-3*0.105)**2)
    'year': year
})

data['people'].append({
    'name' : 'ST_t_channel_top_2017',
    'inputDataset': '/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '5473400',
    'nFiles': '11',
    'isMC': isMC_,
    'xs': '136.0', #https://arxiv.org/pdf/1812.10514.pdf 35.85 * (1-(1-3*0.105)**2)
    'year': year
})

data['people'].append({
    'name' : 'ST_t_channel_antitop_2017',
    'inputDataset': '/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '3695100',
    'nFiles': '8',
    'isMC': isMC_,
    'xs': '81.0', #https://arxiv.org/pdf/1812.10514.pdf
    'year': year
})

data['people'].append({
    'name': 'WW_2017',
    'inputDataset': '/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '15883000',
    'nFiles': '30',
    'isMC': isMC_,
    'xs': '51.723', #ra2b:51.723
    'year': year
})

data['people'].append({
    'name': 'WZ_2017',
    'inputDataset': '/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '7898000',
    'nFiles': '18',
    'isMC': isMC_,
    'xs': '47.13', #ra2b:47.13;
    'year': year
})

#data['people'].append({
#    'name': 'ZZ_2017',
#    'inputDataset': '',
#    'nEvents': '',
#    'isMC': isMC_,
#    'xs': '16.523', #ra2b: 16.523;
#})

data['people'].append({
   'name' : 'WJetsToLNu_2017',
   'inputDataset': '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'nEvents': '81254459',
   'nFiles': '42',
   'isMC': isMC_,
   'xs': '61526.7',
   'year': year
})

data['people'].append({
   'name' : 'W1JetsToLNu_2017',
   'inputDataset': '/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'nEvents': '47954631',
   'nFiles': '41',
   'isMC': isMC_,
   'xs': '10432.3',
   'year': year
})

data['people'].append({
   'name' : 'W2JetsToLNu_2017',
   'inputDataset': '/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'nEvents': '28616461',
   'nFiles': '26',
   'isMC': isMC_,
   'xs': '3191.76',
   'year': year
})

data['people'].append({
   'name' : 'W3JetsToLNu_2017',
   'inputDataset': '/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'nEvents': '18903448',
   'nFiles': '21',
   'isMC': isMC_,
   'xs': '948.761',
   'year': year
})

data['people'].append({
   'name' : 'W4JetsToLNu_2017',
   'inputDataset': '/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'nEvents': '17418488',
   'nFiles': '22',
   'isMC': isMC_,
   'xs': '448.896',
   'year': year
})

#data['people'].append({
#    'name': 'EWKZ2Jets_ZToLL_M50',
#    'inputDataset': '',
#    'nEvents': '',
#    'isMC': isMC_,
#    'xs': '4.0',
#})

#data['people'].append({
#    'name' : 'GluGluHToTauTau',
#    'inputDataset': '',
#    'nEvents': '',
#    'isMC': isMC_,
#    'xs': '2.8',
#})

#data['people'].append({
#    'name' : 'VBFHToTauTau',
#    'inputDataset': '',
#    'nEvents': '',
#    'isMC': isMC_,
#    'xs': '0.2',
#})

data['people'].append({
    'name': 'GluGluHToZG_2017',
    'inputDataset': '/GluGluHToZG_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '400000',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '0.074358',
    'year': year
})

data['people'].append({
    'name': 'VBFHToZG_2017',
    'inputDataset': '/VBFHToZG_M-125_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '200000',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '0.0057834',
    'year': year
})

with open('mcsamples_2017.json', 'w') as outfile:
   json.dump(data, outfile)
