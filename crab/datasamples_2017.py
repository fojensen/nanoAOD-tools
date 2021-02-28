import json

data = {}
data['people'] = []
lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'

data['people'].append({
   'name': 'SingleMuon_Run2017B',
   'inputDataset': '/SingleMuon/Run2017B-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleMuon_Run2017C',
   'inputDataset': '/SingleMuon/Run2017C-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleMuon_Run2017D',
   'inputDataset': '/SingleMuon/Run2017D-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleMuon_Run2017E',
   'inputDataset': '/SingleMuon/Run2017E-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'SingleMuon_2017F',
    'inputDataset': '/SingleMuon/Run2017F-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask,
})

#data['people'].append({
#    'name': 'SingleMuon_2017G',
#    'inputDataset': '/SingleMuon/Run2017G-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
#    'lumiMask': lumiMask, 
#})

#data['people'].append({
#    'name': 'SingleMuon_2017H',
#    'inputDataset': '/SingleMuon/Run2017H-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
#    'lumiMask': lumiMask,
#})

data['people'].append({
   'name': 'SingleElectron_Run2017B',
   'inputDataset': '/SingleElectron/Run2017B-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleElectron_Run2017C',
   'inputDataset': '/SingleElectron/Run2017C-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleElectron_Run2017D',
   'inputDataset': '/SingleElectron/Run2017D-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleElectron_Run2017E',
   'inputDataset': '/SingleElectron/Run2017E-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'SingleElectron_2017F',
    'inputDataset': '/SingleElectron/Run2017F-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Tau_Run2017B',
   'inputDataset': '/Tau/Run2017B-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Tau_Run2017C',
   'inputDataset': '/Tau/Run2017C-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Tau_Run2017D',
   'inputDataset': '/Tau/Run2017D-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Tau_Run2017E',
   'inputDataset': '/Tau/Run2017E-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'Tau_2017F',
    'inputDataset': '/Tau/Run2017F-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask,
})

with open('datasamples_2017.json', 'w') as outfile:
   json.dump(data, outfile)
