import json

data = {}
data['people'] = []
isMC_ = True
year = '2016'

data['people'].append({
    'name': 'Taustar_m175_2016',
    'inputDataset': '/Taustar_TauG_L10000_m175_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '0.02888',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m250_2016',
    'inputDataset': '/Taustar_TauG_L10000_m250_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '49500',
    'nFiles': '11',
    'isMC': isMC_,
    'xs': '0.02135',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m375_2016',
    'inputDataset': '/Taustar_TauG_L10000_m375_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '0.01546',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m500_2016',
    'inputDataset': '/Taustar_TauG_L10000_m500_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '0.01177',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m625_2016',
    'inputDataset': '/Taustar_TauG_L10000_m625_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '0.009072',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m750_2016',
    'inputDataset': '/Taustar_TauG_L10000_m750_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '15',
    'isMC': isMC_,
    'xs': '0.007024',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m1000_2016',
    'inputDataset': '/Taustar_TauG_L10000_m1000_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '7',
    'isMC': isMC_,
    'xs': '0.004236',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m1250_2016',
    'inputDataset': '/Taustar_TauG_L10000_m1250_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '0.002554',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m1500_2016',
    'inputDataset': '/Taustar_TauG_L10000_m1500_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '9',
    'isMC': isMC_,
    'xs': '0.001522',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m1750_2016',
    'inputDataset': '/Taustar_TauG_L10000_m1750_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '7',
    'isMC': isMC_,
    'xs': '0.0009048',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m2000_2016',
    'inputDataset': '/Taustar_TauG_L10000_m2000_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '16',
    'isMC': isMC_,
    'xs': '0.0005328',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m5000_2016',
    'inputDataset': '/Taustar_TauG_L10000_m5000_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '13',
    'isMC': isMC_,
    'xs': '1.178e-06',
    'year': year
})

with open('sigsamples_2016.json', 'w') as outfile:
   json.dump(data, outfile)

