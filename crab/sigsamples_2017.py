import json

data = {}
data['people'] = []
isMC_ = True

data['people'].append({
    'name': 'Taustar_m375_2017',
    'inputDataset': '/Taustar_TauG_L10000_m375_CP5_13TeV_pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '1',
    'isMC': isMC_,
    'xs': '0.01546',
})

data['people'].append({
    'name': 'Taustar_m750_2017',
    'inputDataset': '/Taustar_TauG_L10000_m750_CP5_13TeV_pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '12',
    'isMC': isMC_,
    'xs': '0.007024',
})

with open('sigsamples_2017.json', 'w') as outfile:
   json.dump(data, outfile)

