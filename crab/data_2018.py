import json

data = {}
data['people'] = []

lumiMask = 'Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'
year = '2018'
isMC = False
isEmb = False

data['people'].append({
   'name': 'SingleMuon_Run2018A',
   'inputDataset': '/SingleMuon/Run2018A-02Apr2020-v1/NANOAOD',
   'lumiMask': lumiMask,
   'year': year,
   'isMC': isMC,
   'isEmb': isEmb,
   'nFiles': '225',
})

data['people'].append({
   'name': 'SingleMuon_Run2018B',
   'inputDataset': '/SingleMuon/Run2018B-02Apr2020-v1/NANOAOD',
   'lumiMask': lumiMask,
   'year': year,
   'isMC': isMC,
   'isEmb': isEmb,
   'nFiles': '110',
})

data['people'].append({
   'name': 'SingleMuon_Run2018C',
   'inputDataset': '/SingleMuon/Run2018C-02Apr2020-v1/NANOAOD',
   'lumiMask': lumiMask,
   'year': year,
   'isMC': isMC,
   'isEmb': isEmb,
   'nFiles': '79',
})

data['people'].append({
   'name': 'SingleMuon_Run2018D',
   'inputDataset': '/SingleMuon/Run2018D-02Apr2020-v1/NANOAOD',
   'lumiMask': lumiMask,
   'year': year,
   'isMC': isMC,
   'isEmb': isEmb,
   'nFiles': '293',
})

with open('data_2018.json', 'w') as outfile:
   json.dump(data, outfile)
