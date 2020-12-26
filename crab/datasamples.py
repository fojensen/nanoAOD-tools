import json

data = {}
data['people'] = []
lumiMask = 'Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'

data['people'].append({
   'name': 'SingleMuon_Run2018A',
   'inputDataset': '/SingleMuon/Run2018A-02Apr2020-v1/NANOAOD',
   'lumiMask': lumiMask,
   'nFiles': '225',
})

data['people'].append({
   'name': 'SingleMuon_Run2018B',
   'inputDataset': '/SingleMuon/Run2018B-02Apr2020-v1/NANOAOD',
   'lumiMask': lumiMask,
   'nFiles': '110',
})

data['people'].append({
   'name': 'SingleMuon_Run2018C',
   'inputDataset': '/SingleMuon/Run2018C-02Apr2020-v1/NANOAOD',
   'lumiMask': lumiMask,
   'nFiles': '79',
})

data['people'].append({
   'name': 'SingleMuon_Run2018D',
   'inputDataset': '/SingleMuon/Run2018D-02Apr2020-v1/NANOAOD',
   'lumiMask': lumiMask,
   'nFiles': '293',
})

data['people'].append({
    'name': 'EGamma_Run2018A',
    'inputDataset': '/EGamma/Run2018A-02Apr2020-v1/NANOAOD',
    'lumiMask': lumiMask,
    'nFiles': '255',
})

data['people'].append({
    'name': 'EGamma_Run2018B',
    'inputDataset': '/EGamma/Run2018B-02Apr2020-v1/NANOAOD',
    'lumiMask': lumiMask, 
    'nFiles': '100',
})

data['people'].append({
    'name': 'EGamma_Run2018C',
    'inputDataset': '/EGamma/Run2018C-02Apr2020-v1/NANOAOD',
    'lumiMask': lumiMask,
    'nFiles': '112',
})

data['people'].append({
    'name': 'EGamma_Run2018D',
    'inputDataset': '/EGamma/Run2018D-02Apr2020-v1/NANOAOD',
    'lumiMask': lumiMask, 
    'nFiles': '479',
})

data['people'].append({
    'name': 'Tau_Run2018A',
    'inputDataset': '/Tau/Run2018A-02Apr2020-v1/NANOAOD',
    'lumiMask': lumiMask, 
    'nFiles': '',
})

data['people'].append({
    'name': 'Tau_Run2018B',
    'inputDataset': '/Tau/Run2018B-02Apr2020-v1/NANOAOD',
    'lumiMask': lumiMask, 
    'nFiles': '',
})

data['people'].append({
    'name': 'Tau_Run2018C',
    'inputDataset': '/Tau/Run2018C-02Apr2020-v1/NANOAOD',
    'lumiMask': lumiMask, 
    'nFiles': '',
})

data['people'].append({
    'name': 'Tau_Run2018D',
    'inputDataset': '/Tau/Run2018D-02Apr2020-v2/NANOAOD',
    'lumiMask': lumiMask,
    'nFiles': '102',
})

with open('datasamples.json', 'w') as outfile:
   json.dump(data, outfile)
