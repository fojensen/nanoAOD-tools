import json

data = {}
data['people'] = []
isMC_ = True
year = '2018'

data['people'].append({
    'name': 'Taustar_m175_2018',
    'inputDataset': '/Taustar_TauG_L10000_m175_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '0.02888',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m250_2018',
    'inputDataset': '/Taustar_TauG_L10000_m250_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '1',
    'isMC': isMC_,
    'xs': '0.02135',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m375_2018',
    'inputDataset': '/Taustar_TauG_L10000_m375_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '7',
    'isMC': isMC_,
    'xs': '0.01546',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m500_2018',
    'inputDataset': '/Taustar_TauG_L10000_m500_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '8',
    'isMC': isMC_,
    'xs': '0.01177',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m625_2018',
    'inputDataset': '/Taustar_TauG_L10000_m625_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '2',
    'isMC': isMC_,
    'xs': '0.009072',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m750_2018',
    'inputDataset': '/Taustar_TauG_L10000_m750_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '0.007024',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m1000_2018',
    'inputDataset': '/Taustar_TauG_L10000_m1000_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '0.004236',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m1250_2018',
    'inputDataset': '/Taustar_TauG_L10000_m1250_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '0.002554',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m1500_2018',
    'inputDataset': '/Taustar_TauG_L10000_m1500_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '0.001522',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m1750_2018',
    'inputDataset': '/Taustar_TauG_L10000_m1750_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '0.0009048',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m2000_2018',
    'inputDataset': '/Taustar_TauG_L10000_m2000_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '9',
    'isMC': isMC_,
    'xs': '0.0005328',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m2500_2018',
    'inputDataset': '/Taustar_TauG_L10000_m2500_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '4',
    'isMC': isMC_,
    'xs': '0.0001862',
    'year': year
})

data['people'].append({
    'name': 'Taustar_m5000_2018',
    'inputDataset': '/Taustar_TauG_L10000_m5000_CP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '1.178e-06',
    'year': year
})

with open('sigsamples_2018.json', 'w') as outfile:
   json.dump(data, outfile)

