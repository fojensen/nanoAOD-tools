import json

data = {}
data['people'] = []
isMC_ = True

data['people'].append({
    'name': 'Taustar_m375_2016',
    'inputDataset': '/Taustar_TauG_L10000_m375_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '0.01546',
})

data['people'].append({
    'name': 'Taustar_m750_2016',
    'inputDataset': '/Taustar_TauG_L10000_m750_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '15',
    'isMC': isMC_,
    'xs': '0.007024',
})

with open('sigsamples_2016.json', 'w') as outfile:
   json.dump(data, outfile)

