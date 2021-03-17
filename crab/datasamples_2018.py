import json

data = {}
data['people'] = []
#lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
lumiMask = 'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'

data['people'].append({
   'name': 'Muon_2018A',
   'inputDataset': '/SingleMuon/Run2018A-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'nFiles': '147',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Muon_2018B',
   'inputDataset': '/SingleMuon/Run2018B-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'nFiles': '63',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Muon_2018C',
   'inputDataset': '/SingleMuon/Run2018C-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'nFiles': '71',
   'lumiMask': lumiMask,
})

data['people'].append({
   'name': 'Muon_2018D',
   'inputDataset': '/SingleMuon/Run2018D-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'nFiles': '328',
   'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'Electron_2018A',
    'inputDataset': '/EGamma/Run2018A-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '221',
    'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'Electron_2018B',
    'inputDataset': '/EGamma/Run2018B-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '82',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Electron_2018C',
    'inputDataset': '/EGamma/Run2018C-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD', #PRODUCTION
    'nFiles': '68',
    'lumiMask': lumiMask,
})

data['people'].append({
    'name': 'Electron_2018D',
    'inputDataset': '/EGamma/Run2018D-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '404', #396 jobs
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Tau_2018A',
    'inputDataset': '/Tau/Run2018A-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '38',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Tau_2018B',
    'inputDataset': '/Tau/Run2018B-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '20',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Tau_2018C',
    'inputDataset': '/Tau/Run2018C-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '28',
    'lumiMask': lumiMask, 
})

data['people'].append({
    'name': 'Tau_2018D',
    'inputDataset': '/Tau/Run2018D-UL2018_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '158', #2 droppped from lumi?
    'lumiMask': lumiMask,
})

with open('datasamples_2018.json', 'w') as outfile:
   json.dump(data, outfile)
