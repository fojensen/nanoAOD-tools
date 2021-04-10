import json

data = {}
data['people'] = []
#lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
lumiMask = 'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
year = '2016'

#dataset dataset=/*/*UL2016_MiniAODv1_NanoAODv2*/NANOAOD status=*

#data['people'].append({
#    'name': 'Muon_2016B',
#    'inputDataset': '/SingleMuon/Run2016B-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD', #INVALID
#    'nFiles': '',
#    'lumiMask': lumiMask,
#})

data['people'].append({
    'name': 'Muon_2016B_ver1_HIPM',
    'inputDataset': '/SingleMuon/Run2016B-ver1_HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD', #no lumis to process
    'nFiles': '6',
    'lumiMask': lumiMask,
    'year': '2016'
})

data['people'].append({
    'name': 'Muon_2016B_ver2_HIPM',
    'inputDataset': '/SingleMuon/Run2016B-ver2_HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '59',
    'lumiMask': lumiMask,
    'year': '2016'
})

data['people'].append({
    'name': 'Muon_2016C',
    'inputDataset': '/SingleMuon/Run2016C-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '46',
    'lumiMask': lumiMask,
    'year': '2016'
})

#data['people'].append({
#   'name': 'Muon_2016C',
#   'inputDataset': '/SingleMuon/Run2016C-UL2016_MiniAODv1_NanoAODv2-v2/NANOAOD', #INVALID
#   'nFiles': '',
#   'lumiMask': lumiMask,
#}) 

data['people'].append({
   'name': 'Muon_2016D',
   'inputDataset': '/SingleMuon/Run2016D-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'nFiles': '57',
   'lumiMask': lumiMask,
   'year': '2016'
})

data['people'].append({
    'name': 'Muon_2016E',
    'inputDataset': '/SingleMuon/Run2016E-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '52',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Muon_2016F_HIPM',
    'inputDataset': '/SingleMuon/Run2016F-HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '28',
    'lumiMask': lumiMask,
    'year': year
})

#data['people'].append({
#    'name': 'Muon_2016F_v1',
#    'inputDataset': '/SingleMuon/Run2016F-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD', #INVALID
#    'nFiles': '37',
#    'lumiMask': lumiMask,
#}) 

#data['people'].append({
#    'name': 'Muon_2016F_v2',
#    'inputDataset': '/SingleMuon/Run2016F-UL2016_MiniAODv1_NanoAODv2-v2/NANOAOD', #INVALID
#    'nFiles': '',
#    'lumiMask': lumiMask,
#})

#data['people'].append({
#    'name': 'Muon_2016F_v3',
#    'inputDataset': '/SingleMuon/Run2016F-UL2016_MiniAODv1_NanoAODv2-v3/NANOAOD', #INVALID
#    'nFiles': '',
#    'lumiMask': lumiMask,
#})

data['people'].append({
    'name': 'Muon_2016F_v4',
    'inputDataset': '/SingleMuon/Run2016F-UL2016_MiniAODv1_NanoAODv2-v4/NANOAOD',
    'nFiles': '8',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Muon_2016G',
    'inputDataset': '/SingleMuon/Run2016G-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '86',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Muon_2016H',
    'inputDataset': '/SingleMuon/Run2016H-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '82',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2016B_ver1_HIPM',
    'inputDataset': '/SingleElectron/Run2016B-ver1_HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',#nojobsaftersplitting
    'nFiles': '1',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2016B_ver2_HIPM',
    'inputDataset': '/SingleElectron/Run2016B-ver2_HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '122',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2016C',
    'inputDataset': '/SingleElectron/Run2016C-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '61',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2016D',
    'inputDataset': '/SingleElectron/Run2016D-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '81',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2016E',
    'inputDataset': '/SingleElectron/Run2016E-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '68',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2016F_HIPM',
    'inputDataset': '/SingleElectron/Run2016F-HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '41',
    'lumiMask': lumiMask,
    'year': year
})

#data['people'].append({
#    'name': 'Electron_2016F_v1',
#    'inputDataset': '/SingleElectron/Run2016F-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',#INVALID
#    'nFiles': '35',
#    'lumiMask': lumiMask,
#})

data['people'].append({
    'name': 'Electron_2016F_v2',
    'inputDataset': '/SingleElectron/Run2016F-UL2016_MiniAODv1_NanoAODv2-v2/NANOAOD',
    'nFiles': '6',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2016G',
    'inputDataset': '/SingleElectron/Run2016G-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '70',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Electron_2016H',
    'inputDataset': '/SingleElectron/Run2016H-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '76',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2016B_ver1_HIPM',
    'inputDataset': '/Tau/Run2016B-ver1_HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD', #nojobsafterlumi
    'nFiles': '1',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2016B_ver2_HIPM',
    'inputDataset': '/Tau/Run2016B-ver2_HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '47',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2016C',
    'inputDataset': '/Tau/Run2016C-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '29',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2016D',
    'inputDataset': '/Tau/Run2016D-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '44',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2016E',
    'inputDataset': '/Tau/Run2016E-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '39',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2016F_HIPM',
    'inputDataset': '/Tau/Run2016F-HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '29',
    'lumiMask': lumiMask,
    'year': year
})

#data['people'].append({
#    'name': 'Tau_2016F_v1',
#    'inputDataset': '/Tau/Run2016F-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',#INVALID
#    'nFiles': '27',
#    'lumiMask': lumiMask,
#})

data['people'].append({
    'name': 'Tau_2016F_v2',
    'inputDataset': '/Tau/Run2016F-UL2016_MiniAODv1_NanoAODv2-v2/NANOAOD',
    'nFiles': '8',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2016G',
    'inputDataset': '/Tau/Run2016G-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '53',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'Tau_2016H',
    'inputDataset': '/Tau/Run2016H-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '55',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'MuonEG_2016B_ver1_HIPM',
    'inputDataset': '/MuonEG/Run2016B-ver1_HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '3',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'MuonEG_2016B_ver2_HIPM',
    'inputDataset': '/MuonEG/Run2016B-ver2_HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '27',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'MuonEG_2016C',
    'inputDataset': '/MuonEG/Run2016C-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '12',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'MuonEG_2016D',
    'inputDataset': '/MuonEG/Run2016D-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '20',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'MuonEG_2016E',
    'inputDataset': '/MuonEG/Run2016E-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '20',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'MuonEG_2016F_HIPM',
    'inputDataset': '/MuonEG/Run2016F-HIPM_UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '10',
    'lumiMask': lumiMask,
    'year': year
})

#data['people'].append({
#    'name': 'MuonEG_2016F_v1',
#    'inputDataset': '/MuonEG/Run2016F-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
#    'nFiles': '', # INVALID
#    'lumiMask': lumiMask,
#    'year': year
#})

data['people'].append({
    'name': 'MuonEG_2016F_v2',
    'inputDataset': '/MuonEG/Run2016F-UL2016_MiniAODv1_NanoAODv2-v2/NANOAOD',
    'nFiles': '2',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'MuonEG_2016G',
    'inputDataset': '/MuonEG/Run2016G-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '29',
    'lumiMask': lumiMask,
    'year': year
})

data['people'].append({
    'name': 'MuonEG_2016H',
    'inputDataset': '/MuonEG/Run2016H-UL2016_MiniAODv1_NanoAODv2-v1/NANOAOD',
    'nFiles': '24',
    'lumiMask': lumiMask,
    'year': year
})

with open('datasamples_2016.json', 'w') as outfile:
   json.dump(data, outfile)
