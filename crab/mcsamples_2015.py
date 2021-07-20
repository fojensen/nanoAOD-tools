import json

data = {}
data['people'] = []
isMC_ = True
year = '2015'

data['people'].append({
    'name': 'DYJetsToLL_M10to50_2015',
    'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '32305345',
    'nFiles': '16',
    'isMC': isMC_,
    'xs': '18610.',
    'year': year,
})

data['people'].append({
    'name': 'DYJetsToLL_M50_2015',
    'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '96862861',
    'nFiles': '51',
    'isMC': isMC_,
    'xs': '6077.22',
    'year': year
})

"""data['people'].append({
    'name': 'DY1JetsToLL_M50_2015',
    'inputDataset': '',
    'nEvents': '',
    'nFiles': 0',
    'isMC': isMC_,
    'xs': '1112.14',
    'year': year
})

data['people'].append({
    'name': 'DY2JetsToLL_M50_2015',
    'inputDataset': '',
    'nEvents': '',
    'nFiles': '',
    'isMC': isMC_,
    'xs': '344.987',
    'year': year
})

data['people'].append({
    'name': 'DY3JetsToLL_M50_2015',
    'inputDataset': '',
    'nEvents': '',
    'nFiles': '',
    'isMC': isMC_,
    'xs': '102.468',
    'year': year
})

data['people'].append({
    'name': 'DY4JetsToLL_M50_2015',
    'inputDataset': '',
    'nEvents': '',
    'nFiles': '',
    'isMC': isMC_,
    'xs': '48.8496',
    'year': year
})"""

data['people'].append({
    'name': 'TTToSemiLeptonic_2015',
    'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '138169000',
    'nFiles': '236',
    'isMC': isMC_,
    'xs': '365.34',
    'year': year,
})

data['people'].append({
    'name': 'TTTo2L2Nu_2015',
    'inputDataset': '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '41364000',
    'nFiles': '102',
    'isMC': isMC_,
    'xs': '88.29',
    'year': year,
})

data['people'].append({
    'name': 'ST_tW_antitop_2015',
    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '3411747',
    'nFiles': '11',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf
    'year': year
})

data['people'].append({
    'name': 'ST_tW_top_2015',
    'inputDataset': '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v2/NANOAODSIM',
    'nEvents': '3294673',
    'nFiles': '25',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf 35.85 * (1-(1-3*0.105)**2)
    'year': year
})

data['people'].append({
    'name' : 'ST_t_channel_top_2015',
    'inputDataset': '/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '56860000',
    'nFiles': '40',
    'isMC': isMC_,
    'xs': '136.0', #https://arxiv.org/pdf/1812.10514.pdf 35.85 * (1-(1-3*0.105)**2)
    'year': year
})

data['people'].append({
    'name' : 'ST_t_channel_antitop_2015',
    'inputDataset': '/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '31046000',
    'nFiles': '21',
    'isMC': isMC_,
    'xs': '81.0', #https://arxiv.org/pdf/1812.10514.pdf
    'year': year
})

data['people'].append({
    'name': 'WW_2015',
    'inputDataset': '/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '15919000',
    'nFiles': '18',
    'isMC': isMC_,
    'xs': '51.723',
    'year': year
})

data['people'].append({
    'name': 'WZ_2015',
    'inputDataset': '/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '7907000',
    'nFiles': '19',
    'isMC': isMC_,
    'xs': '47.13',
    'year': year
})

data['people'].append({
    'name': 'ZZ_2015',
    'inputDataset': '/ZZ_TuneCP5_13TeV-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '1270000',
    'nFiles': '10',
    'isMC': isMC_,
    'xs': '16.523',
    'year': year
})

data['people'].append({
    'name': 'ZZTo2L2Nu_2015',
    'inputDataset': '/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '17625000',
    'nFiles': '14',
    'isMC': isMC_,
    'xs': '0.5644',
    'year': year
})

data['people'].append({
    'name' : 'WGToLNuG_2015',
    'inputDataset': '/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
    'nEvents': '9987331',
    'nFiles': '9',
    'isMC': isMC_,
    'xs': '489.0',
    'year': year
})

data['people'].append({
   'name' : 'WJetsToLNu_2015',
   'inputDataset': '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
   'nEvents': '81327193',
   'nFiles': '70',
   'isMC': isMC_,
   'xs': '61526.7',
   'year': year
})

data['people'].append({
   'name' : 'W1JetsToLNu_2015',
   'inputDataset': '/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
   'nEvents': '47788364',
   'nFiles': '34',
   'isMC': isMC_,
   'xs': '10432.3',
   'year': year
})

data['people'].append({
   'name' : 'W2JetsToLNu_2015',
   'inputDataset': '/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
   'nEvents': '27635126',
   'nFiles': '21',
   'isMC': isMC_,
   'xs': '3191.76',
   'year': year
})

data['people'].append({
   'name' : 'W3JetsToLNu_2015',
   'inputDataset': '/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
   'nEvents': '18460582',
   'nFiles': '20',
   'isMC': isMC_,
   'xs': '948.761',
   'year': year
})

data['people'].append({
   'name' : 'W4JetsToLNu_2015',
   'inputDataset': '/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL16NanoAODAPVv2-106X_mcRun2_asymptotic_preVFP_v9-v1/NANOAODSIM',
   'nEvents': '9385004',
   'nFiles': '11',
   'isMC': isMC_,
   'xs': '448.896',
   'year': year
})

#data['people'].append({
#    'name': 'EWKZ2Jets_ZToLL_M50_2015',
#    'inputDataset': '',
#    'nEvents': '',
#    'nFiles': '',
#    'isMC': isMC_,
#    'xs': '4.0',
#})

#data['people'].append({
#    'name' : 'GluGluHToTauTau_2015',
#    'inputDataset': '',
#    'nEvents': '',
#    'nFiles': '',
#    'isMC': isMC_,
#    'xs': '2.8',
#})

#data['people'].append({
#    'name' : 'VBFHToTauTau_2015',
#    'inputDataset': '',
#    'nEvents': '',
#    'nFiles': '',
#    'isMC': isMC_,
#    'xs': '0.2',
#})

#data['people'].append({
#    'name': 'GluGluHToZG_2015',
#    'inputDataset': '',
#    'nEvents': '',
#    'nFiles': '',
#    'isMC': isMC_,
#    'xs': '0.074358',
#    'year': year
#})

#data['people'].append({
#    'name': 'VBFHToZG_2015',
#    'inputDataset': '',
#    'nEvents': '',
#    'nFiles': '',
#    'isMC': isMC_,
#    'xs': '0.0057834',
#    'year': year
#})

with open('mcsamples_2015.json', 'w') as outfile:
  json.dump(data, outfile)
