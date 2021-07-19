import json

data = {}
data['people'] = []
isMC_ = True
year = "2018"

data['people'].append({
    'name': 'DYJetsToLL_M10to50_2018',
    'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '84761331',
    'nFiles': '38',
    'isMC': isMC_,
    'xs': '18610',
    'year': year,
})

data['people'].append({
    'name': 'DYJetsToLL_M50_2018',
    'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '98433266',
    'nFiles': '53',
    'isMC': isMC_,
    'xs': '6077.22',
    'year': year,
})

data['people'].append({
    'name': 'DY1JetsToLL_M50_2018',
    'inputDataset': '/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '65679725',
    'nFiles': '41',
    'isMC': isMC_,
    'xs': '1112.14',
    'year': year
})

data['people'].append({
    'name': 'DY2JetsToLL_M50_2018',
    'inputDataset': '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '28280407',
    'nFiles': '22',
    'isMC': isMC_,
    'xs': '344.987',
    'year': year
})

data['people'].append({
    'name': 'DY3JetsToLL_M50_2018',
    'inputDataset': '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '19021176',
    'nFiles': '18',
    'isMC': isMC_,
    'xs': '102.468',
    'year': year
})

data['people'].append({
    'name': 'DY4JetsToLL_M50_2018',
    'inputDataset': '/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '7581874',
    'nFiles': '12',
    'isMC': isMC_,
    'xs': '48.8496',
    'year': year
})

data['people'].append({
    'name': 'TTToSemiLeptonic_2018',
    'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '486770000',
    'nFiles': '465',
    'isMC': isMC_,
    'xs': '365.34',
    'year': year,
})

data['people'].append({
    'name': 'TTTo2L2Nu_2018',
    'inputDataset': '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '148470000',
    'nFiles' : '181',
    'isMC': isMC_,
    'xs': '88.29',
    'year': year,
})

data['people'].append({
    'name': 'ST_tW_antitop_2018',
    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '11695231',
    'nFiles': '10',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf
    'year': year
})

data['people'].append({
    'name': 'ST_tW_top_2018',
    'inputDataset': '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '11518444',
    'nFiles': '10',
    'isMC': isMC_,
    'xs': '19.02828375', #https://arxiv.org/pdf/1805.07399.pdf 35.85 * (1-(1-3*0.105)**2)
    'year': year
})

data['people'].append({
    'name' : 'ST_t_channel_top_2018',
    'inputDataset': '/ST_t-channel_top_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '5640600',
    'nFiles': '7',
    'isMC': isMC_,
    'xs': '136.0', #https://arxiv.org/pdf/1812.10514.pdf 35.85 * (1-(1-3*0.105)**2)
    'year': year
})

data['people'].append({
    'name' : 'ST_t_channel_antitop_2018',
    'inputDataset': '/ST_t-channel_antitop_5f_InclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '3736700',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '81.0', #https://arxiv.org/pdf/1812.10514.pdf
    'year': year
})

data['people'].append({
    'name': 'WW_2018',
    'inputDataset': '/WW_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '15670000',
    'nFiles' : '21',
    'isMC': isMC_,
    'xs': '51.723', #ra2b:51.723
    'year': year
})

data['people'].append({
    'name': 'WZ_2018',
    'inputDataset': '/WZ_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '7986000',
    'nFiles': '21',
    'isMC': isMC_,
    'xs': '47.13', #ra2b:47.13
    'year': year
})

data['people'].append({
    'name': 'ZZ_2018',
    'inputDataset': '/ZZ_TuneCP5_13TeV-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '3907000',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '16.523',
    'year': year
})

data['people'].append({
    'name': 'ZZTo2L2Nu_2018',
    'inputDataset': '/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '56812000',
    'nFiles': '35',
    'isMC': isMC_,
    'xs': '0.6008',
    'year': year
})

data['people'].append({
    'name' : 'WGToLNuG_2018',
    'inputDataset': '/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
    'nEvents': '9850083',
    'nFiles': '7',
    'isMC': isMC_,
    'xs': '489.0',
    'year': year
})

data['people'].append({
   'name' : 'WJetsToLNu_2018',
   'inputDataset': '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
   'nEvents': '83009353',
   'nFiles': '45',
   'isMC': isMC_,
   'xs': '61526.7',
   'year': year
})

data['people'].append({
   'name' : 'W1JetsToLNu_2018',
   'inputDataset': '/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
   'nEvents': '47698594',
   'nFiles': '47',
   'isMC': isMC_,
   'xs': '10432.3',
   'year': year
})

data['people'].append({
   'name' : 'W2JetsToLNu_2018',
   'inputDataset': '/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
   'nEvents': '27570500',
   'nFiles': '34',
   'isMC': isMC_,
   'xs': '3191.76',
   'year': year
})

data['people'].append({
   'name' : 'W3JetsToLNu_2018',
   'inputDataset': '/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
   'nEvents': '14932443',
   'nFiles': '15',
   'isMC': isMC_,
   'xs': '948.761',
   'year': year
})

data['people'].append({
   'name' : 'W4JetsToLNu_2018',
   'inputDataset': '/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v1/NANOAODSIM',
   'nEvents': '12416620',
   'nFiles': '17',
   'isMC': isMC_,
   'xs': '448.896',
   'year': year
})

"""
data['people'].append({
    'name': 'EWKZ2Jets_ZToLL_M50_2018',
    'inputDataset': '',
    'nEvents': '',
    'nFiles': '',
    'isMC': isMC_,
    'xs': '4.0',
})

data['people'].append({
    'name' : 'GluGluHToTauTau_2018',
    'inputDataset': '/GluGluHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v3/NANOAODSIM',
    'nEvents': '12918000',
    'nFiles': '86',
    'isMC': isMC_,
    'xs': '2.8',
})

data['people'].append({
    'name' : 'VBFHToTauTau_2018',
    'inputDataset': '/VBFHToTauTau_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18NanoAODv2-106X_upgrade2018_realistic_v15_L1v1-v2/NANOAODSIM',
    'nEvents': '2987000',
    'nFiles': '51',
    'isMC': isMC_,
    'xs': '0.2',
})

#data['people'].append({
#    'name': 'GluGluHToZG_2018',
#    'inputDataset': '',
#    'nEvents': '',
#    'nFiles': '',
#    'isMC': isMC_,
#    'xs': '0.074358',
#    'year': year
#})

#data['people'].append({
#    'name': 'VBFHToZG_2018',
#    'inputDataset': '',
#    'nEvents': '',
#    'nFiles': '',
#    'isMC': isMC_,
#    'xs': '0.0057834',
#    'year': year
#})
"""
data['people'].append({
    'name': 'QCD_Mu15_2018',
    'inputDataset': '/QCD_Pt-20toInf_MuEnrichedPt15_TuneCP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '22165320',
    'nFiles': '38',
    'isMC': isMC_,
    'xs': '239400.0',
    'year': year
})

with open('mcsamples_2018.json', 'w') as outfile:
   json.dump(data, outfile)
