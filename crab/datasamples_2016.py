import json

data = {}
data['people'] = []
lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'

data['people'].append({
   'name': 'SingleMuon_2016B',
   'inputDataset': '/SingleMuon/Run2016B-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleMuon_2016C',
   'inputDataset': '/SingleMuon/Run2016C-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleMuon_2016D',
   'inputDataset': '/SingleMuon/Run2016D-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleMuon_2016E',
   'inputDataset': '/SingleMuon/Run2016E-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'SingleMuon_2016F',
    'inputDataset': '/SingleMuon/Run2016F-UL2016_MiniAODv1_NanoAODv2-v4/NANOAOD',
    'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'SingleMuon_2016G',
    'inputDataset': '/SingleMuon/Run2016G-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'SingleMuon_2016H',
    'inputDataset': '/SingleMuon/Run2016H-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleElectron_2016B',
   'inputDataset': '/SingleElectron/Run2016B-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD', #nonexistent
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleElectron_2016C',
   'inputDataset': '/SingleElectron/Run2016C-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleElectron_2016D',
   'inputDataset': '/SingleElectron/Run2016D-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleElectron_2016E',
   'inputDataset': '/SingleElectron/Run2016E-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'SingleElectron_2016F',
    'inputDataset': '/SingleElectron/Run2016F-UL2016_MiniAODv1_NanoAODv2-v2/NANOAOD',
    'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'SingleElectron_2016G',
    'inputDataset': '/SingleElectron/Run2016G-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'SingleElectron_2016H',
    'inputDataset': '/SingleElectron/Run2016H-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Tau_2016B',
   'inputDataset': '/Tau/Run2016B-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD', #nonexistent
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Tau_2016C',
   'inputDataset': '/Tau/Run2016C-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Tau_2016D',
   'inputDataset': '/Tau/Run2016D-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Tau_2016E',
   'inputDataset': '/SingleElectron/Run2016E-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'Tau_2016F',
    'inputDataset': '/Tau/Run2016F-UL2016_MiniAODv1_NanoAODv2-v2/NANOAOD',
    'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'Tau_2016G',
    'inputDataset': '/Tau/Run2016G-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Tau_2016H',
    'inputDataset': '/Tau/Run2016H-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask,
})

with open('datasamples_2016.json', 'w') as outfile:
   json.dump(data, outfile)
