import json

data = {}
data['people'] = []
#lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
lumiMask = 'Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
year = '2017'

data['people'].append({
   'name': 'Muon_2017B',
   'inputDataset': '/SingleMuon/Run2017B-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'nFiles': '110',
   'lumiMask': lumiMask,
   'year': year
})

data['people'].append({
    'name': 'Muon_2017C',
    'inputDataset': '/SingleMuon/Run2017C-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '139',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Muon_2017D',
    'inputDataset': '/SingleMuon/Run2017D-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '58',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Muon_2017E',
    'inputDataset': '/SingleMuon/Run2017E-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '124',
    'lumiMask': lumiMask,
    'year': year
})

#data['people'].append({
#    'name': 'Muon_2017F',
#    'inputDataset': '/SingleMuon/Run2017F-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD', #INVALID
#    'nFiles': '',
#    'lumiMask': lumiMask,
#})

data['people'].append({
    'name': 'Muon_2017F',
    'inputDataset': '/SingleMuon/Run2017F-UL2017_MiniAODv1_NanoAODv2-v2/NANOAOD',
    'nFiles': '174',
    'lumiMask': lumiMask,
    'year': year
})

#data['people'].append({
#    'name': 'Muon_2017G',
#    'inputDataset': '/SingleMuon/Run2017G-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD', #for what?
#    'nFiles': '174',
#    'lumiMask': lumiMask, 
#})

#data['people'].append({
#    'name': 'Muon_2017H',
#    'inputDataset': '/SingleMuon/Run2017H-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD', #for what?
#    'nFiles': '35',
#    'lumiMask': lumiMask,
#})

data['people'].append({
    'name': 'Electron_2017B',
    'inputDataset': '/SingleElectron/Run2017B-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '53',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2017C',
    'inputDataset': '/SingleElectron/Run2017C-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '96',
    'lumiMask': lumiMask,
    'year': year
})

#data['people'].append({
#   'name': 'Electron_2017C',
#   'inputDataset': '/SingleElectron/Run2017C-UL2017_MiniAODv1_NanoAODv2-v2/NANOAOD', #INVALID
#   'lumiMask': lumiMask,
#})

#data['people'].append({
#   'name': 'Electron_2017C',
#   'inputDataset': '/SingleElectron/Run2017C-UL2017_MiniAODv1_NanoAODv2-v3/NANOAOD', #INVALID
#   'lumiMask': lumiMask,
#})

data['people'].append({
    'name': 'Electron_2017D',
    'inputDataset': '/SingleElectron/Run2017D-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '38',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2017E',
    'inputDataset': '/SingleElectron/Run2017E-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '90',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2017F',
    'inputDataset': '/SingleElectron/Run2017F-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '117',
    'lumiMask': lumiMask,
    'year': year
})

#data['people'].append({
#    'name': 'Electron_2017F',
#    'inputDataset': '/SingleElectron/Run2017F-UL2017_MiniAODv1_NanoAODv2-v2/NANOAOD', #INVALID
#    'nFiles': '',
#    'lumiMask': lumiMask,
#})

data['people'].append({
    'name': 'Tau_2017B',
    'inputDataset': '/Tau/Run2017B-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '36',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2017C',
    'inputDataset': '/Tau/Run2017C-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '59',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2017D',
    'inputDataset': '/Tau/Run2017D-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '19',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2017E',
    'inputDataset': '/Tau/Run2017E-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '38',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2017F',
    'inputDataset': '/Tau/Run2017F-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '75',
    'lumiMask': lumiMask,
    'year': year
})

with open('datasamples_2017.json', 'w') as outfile:
   json.dump(data, outfile)
