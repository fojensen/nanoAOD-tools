import json

data = {}
data['people'] = []
isMC_ = True

data['people'].append({
    'name': 'DYJetsToLL_M50_2018',
    'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '98433266',
    'nFiles': '53',
    'isMC': isMC_,
    'xs': '6077.22',
})

data['people'].append({
    'name': 'DY1JetsToLL_M50_2018',
    'inputDataset': '/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '65679725',
    'nFiles': '41',
    'isMC': isMC_,
    'xs': '1178.3',
})

data['people'].append({
    'name': 'DY2JetsToLL_M50_2018',
    'inputDataset': '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '28280407',
    'nFiles': '22',
    'isMC': isMC_,
    'xs': '387.3',
})

data['people'].append({
    'name': 'DY3JetsToLL_M50_2018',
    'inputDataset': '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM ',
    'nEvents': '19021176',
    'nFiles': '18',
    'isMC': isMC_,
    'xs': '118.4',
})

data['people'].append({
    'name': 'DY4JetsToLL_M50_2018',
    'inputDataset': '/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '7581874',
    'nFiles': '12',
    'isMC': isMC_,
    'xs': '63.7',
})

data['people'].append({
    'name': 'TTToSemiLeptonic_2018',
    'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '486770000',
    'nFiles' : '465',
    'isMC': isMC_,
    'xs': '365.34',
})

data['people'].append({
    'name': 'TTTo2L2Nu_2018',
    'inputDataset': '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '148470000',
    'nFiles' : '181',
    'isMC': isMC_,
    'xs': '88.29',
})

data['people'].append({
    'name': 'ST_tW_antitop_2018',
    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '9125752',
    'nFiles': '10',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf 
})

data['people'].append({
    'name': 'ST_tW_top_2018',
    'inputDataset': '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '10064364',
    'nFiles': '13',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf 35.85 * (1-(1-3*0.105)**2)
})

data['people'].append({
    'name' : 'ST_t_channel_top_2018',
    'inputDataset': '/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '5640600',
    'nFiles': '7',
    'isMC': isMC_,
    'xs': '136.0', #https://arxiv.org/pdf/1812.10514.pdf 35.85 * (1-(1-3*0.105)**2)
})

data['people'].append({
    'name' : 'ST_t_channel_antitop_2018',
    'inputDataset': '/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '3736700',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '81.0', #https://arxiv.org/pdf/1812.10514.pdf
})

data['people'].append({
    'name': 'WW_2018',
    'inputDataset': '/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '15670000',
    'nFiles' : '21',
    'isMC': isMC_,
    'xs': '51.723', #ra2b:51.723
})

data['people'].append({
    'name': 'WZ_2018',
    'inputDataset': '/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '7986000',
    'nFiles': '21',
    'isMC': isMC_,
    'xs': '47.13', #ra2b:47.13; 
})

data['people'].append({
    'name': 'ZZ_2018',
    'inputDataset': '/ZZ_TuneCP5_13TeV-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '2000000',
    'nFiles': '4',
    'isMC': isMC_,
    'xs': '16.523', #ra2b: 16.523;
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

with open('mcsamples_2018.json', 'w') as outfile:
   json.dump(data, outfile)
