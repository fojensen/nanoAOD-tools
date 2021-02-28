import json

data = {}
data['people'] = []
lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'

data['people'].append({
   'name': 'SingleMuon_Run2018A',
   'inputDataset': '/SingleMuon/Run2018A-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleMuon_Run2018B',
   'inputDataset': '/SingleMuon/Run2018B-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleMuon_Run2018C',
   'inputDataset': '/SingleMuon/Run2018C-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'SingleMuon_Run2018D',
   'inputDataset': '/SingleMuon/Run2018D-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'EGamma_Run2018A',
    'inputDataset': '/EGamma/Run2018A-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'EGamma_Run2018B',
    'inputDataset': '/EGamma/Run2018B-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'EGamma_Run2018C',
    'inputDataset': '/EGamma/Run2018C-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'EGamma_Run2018D',
    'inputDataset': '/EGamma/Run2018D-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Tau_Run2018A',
    'inputDataset': '/Tau/Run2018A-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Tau_Run2018B',
    'inputDataset': '/Tau/Run2018B-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Tau_Run2018C',
    'inputDataset': '/Tau/Run2018C-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Tau_Run2018D',
    'inputDataset': '/Tau/Run2018D-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'lumiMask': lumiMask,
})

with open('datasamples_2018.json', 'w') as outfile:
   json.dump(data, outfile)
