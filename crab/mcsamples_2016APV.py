import json

data = {}
data['people'] = []
isMC_ = True
year = '2016'

data['people'].append({
    'name': 'DYJetsToLL_M10to50_2016APV',
    'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '32305345',
    'nFiles': '16',
    'isMC': isMC_,
    'xs': '18610.',
    'year': year,
})

data['people'].append({
    'name': 'DYJetsToLL_M50_2016APV',
    'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '96862861',
    'nFiles': '51',
    'isMC': isMC_,
    'xs': '6077.22',
    'year': year
})

"""data['people'].append({
    'name': 'DY1JetsToLL_M50_2016',
    'inputDataset': '/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
    'nEvents': '65712864',
    'nFiles': '50',
    'isMC': isMC_,
    'xs': '1112.14',
    'year': year
})

data['people'].append({
    'name': 'DY2JetsToLL_M50_2016',
    'inputDataset': '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
    'nEvents': '28446811',
    'nFiles': '30',
    'isMC': isMC_,
    'xs': '344.987',
    'year': year
})

data['people'].append({
    'name': 'DY3JetsToLL_M50_2016',
    'inputDataset': '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
    'nEvents': '18845701',
    'nFiles': '21',
    'isMC': isMC_,
    'xs': '102.468',
    'year': year
})

data['people'].append({
    'name': 'DY4JetsToLL_M50_2016',
    'inputDataset': '/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
    'nEvents': '7538537',
    'nFiles': '13',
    'isMC': isMC_,
    'xs': '48.8496',
    'year': year
})"""

data['people'].append({
    'name': 'TTToSemiLeptonic_2016APV',
    'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '138169000',
    'nFiles': '236',
    'isMC': isMC_,
    'xs': '365.34',
    'year': year,
})

data['people'].append({
    'name': 'TTTo2L2Nu_2016APV', 
    'inputDataset': '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '41364000',
    'nFiles': '102',
    'isMC': isMC_,
    'xs': '88.29',
    'year': year,
})

data['people'].append({
    'name': 'ST_tW_antitop_2016APV',
    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '3411747',
    'nFiles': '11',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf
    'year': year
})

data['people'].append({
    'name': 'ST_tW_top_2016APV',
    'inputDataset': '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
    'nEvents': '3361253',
    'nFiles': '4',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf 35.85 * (1-(1-3*0.105)**2)
    'year': year
})

data['people'].append({
    'name' : 'ST_t_channel_top_2016APV',
    'inputDataset': '/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '56860000',
    'nFiles': '40',
    'isMC': isMC_,
    'xs': '136.0', #https://arxiv.org/pdf/1812.10514.pdf 35.85 * (1-(1-3*0.105)**2)
    'year': year
})

data['people'].append({
    'name' : 'ST_t_channel_antitop_2016APV',
    'inputDataset': '/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '31046000',
    'nFiles': '21',
    'isMC': isMC_,
    'xs': '81.0', #https://arxiv.org/pdf/1812.10514.pdf
    'year': year
})

data['people'].append({
    'name': 'WW_2016APV',
    'inputDataset': '/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '15919000',
    'nFiles': '18',
    'isMC': isMC_,
    'xs': '51.723',
    'year': year
})

data['people'].append({
    'name': 'WZ_2016APV',
    'inputDataset': '/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '7907000',
    'nFiles': '19',
    'isMC': isMC_,
    'xs': '47.13',
    'year': year
})

data['people'].append({
    'name': 'ZZ_2016APV',
    'inputDataset': '/ZZ_TuneCP5_13TeV-pythia8/RunIISummer19UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '2000000',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '16.523',
    'year': year
})

data['people'].append({
    'name': 'ZZTo2L2Nu_2016APV',
    'inputDataset': '/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '17625000',
    'nFiles': '14',
    'isMC': isMC_,
    'xs': '0.5644',
    'year': year
})

"""data['people'].append({
   'name' : 'WJetsToLNu_2016',
   'inputDataset': '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
   'nEvents': '88463979',
   'nFiles': '62',
   'isMC': isMC_,
   'xs': '61526.7',
   'year': year
})

data['people'].append({
   'name' : 'W1JetsToLNu_2016',
   'inputDataset': '/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
   'nEvents': '48443131',
   'nFiles': '34',
   'isMC': isMC_,
   'xs': '10432.3',
   'year': year
})

data['people'].append({
   'name' : 'W2JetsToLNu_2016',
   'inputDataset': '/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
   'nEvents': '28745846',
   'nFiles': '23',
   'isMC': isMC_,
   'xs': '3191.76',
   'year': year
})

data['people'].append({
   'name' : 'W3JetsToLNu_2016',
   'inputDataset': '/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
   'nEvents': '18859350',
   'nFiles': '17',
   'isMC': isMC_,
   'xs': '948.761',
   'year': year
})

data['people'].append({
   'name' : 'W4JetsToLNu_2016',
   'inputDataset': '/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODv2-106X_mcRun2_asymptotic_v15-v1/NANOAODSIM',
   'nEvents': '9216091',
   'nFiles': '10',
   'isMC': isMC_,
   'xs': '448.896',
   'year': year
})
"""
#data['people'].append({
#    'name': 'EWKZ2Jets_ZToLL_M50',
#    'inputDataset': '',
#    'nEvents': '',
#    'isMC': isMC_,
#    'xs': '4.0',
#})

#data['people'].append({
#    'name' : 'GluGluHToTauTau',
#    'inputDataset': '',
#    'nEvents': '',
#    'isMC': isMC_,
#    'xs': '2.8',
#})

#data['people'].append({
#    'name' : 'VBFHToTauTau',
#    'inputDataset': '',
#    'nEvents': '',
#    'isMC': isMC_,
#    'xs': '0.2',
#})

with open('mcsamples_2016APV.json', 'w') as outfile:
   json.dump(data, outfile)
