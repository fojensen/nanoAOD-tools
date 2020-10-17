import json

data = {}
data['people'] = []
isMC_ = True
year_ = "2017"

'''data['people'].append({
    'name': 'DYJetsToLL_M-10to50',
    'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '39521230',
    'nFiles': '57',
    'isMC': isMC_,
    'xs': '18610.',
    'year': year_,
})

data['people'].append({
    'name': 'DYJetsToLL_M-10to50_ext1',
    'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '39536839',
    'nFiles': '77',
    'isMC': isMC_,
    'xs': '18610.',
    'year': year_
})

data['people'].append({
    'name': 'DYJetsToLL_M-50',
    'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017RECOSIMstep_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '47990369',
    'nFiles': '43',
    'isMC': isMC_,
    'xs': '6077.22',
    'year': year_
})

data['people'].append({
    'name': 'DYJetsToLL_M-50_ext1',
    'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017RECOSIMstep_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '49011552',
    'nFiles': '34',
    'isMC': isMC_,
    'xs': '6077.22',
    'year': year_
})

data['people'].append({
    'name': 'DY1JetsToLL_M-50',
    'inputDataset': '/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_new_pmx_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '42331295',
    'nFiles': '50',
    'isMC': isMC_,
    'xs': '1007.57668',
    'year': year_
})

data['people'].append({
    'name': 'DY1JetsToLL_M-50_ext1',
    'inputDataset': '/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_v3_102X_mc2017_realistic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '33669127',
    'nFiles': '53',
    'isMC': isMC_,
    'xs': '1007.57668',
    'year': year_
})

data['people'].append({
    'name': 'DY2JetsToLL_M-50',  
    'inputDataset': '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '88895',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '344.336324',
    'year': year_
})

data['people'].append({
    'name': 'DY2JetsToLL_M-50_ext1',
    'inputDataset': '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '9701595',
    'nFiles': '15',
    'isMC': isMC_,
    'xs': '344.336324',
    'year': year_
})

data['people'].append({
    'name': 'DY3JetsToLL_M-50',
    'inputDataset': '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '5748466',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '125.267478',
    'year': year_
})

data['people'].append({
    'name': 'DY3JetsToLL_M-50_ext1',
    'inputDataset': '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '1149467',
    'nFiles': '8',
    'isMC': isMC_,
    'xs': '125.267478',
    'year': year_
})

data['people'].append({
    'name': 'DY4JetsToLL_M-50',
    'inputDataset': '/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_v2_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '4328648',
    'nFiles': '12',
    'isMC': isMC_,
    'xs': '71.1999878',
    'year': year_
})

data['people'].append({
    'name': 'TTTo2L2Nu',
    'inputDataset': '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_new_pmx_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '9000000',
    'nFiles': '10',
    'isMC': isMC_,
    'xs': '88.29',
    'year': year_
})

data['people'].append({
    'name': 'ST_tW_antitop_5f_NoFullyHadronicDecays',
    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_new_pmx_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '5635539',
    'nFiles': '8',
    'isMC': isMC_,
    'xs': '',
    'year': year_
})

#data['people'].append({
#    'name': 'ST_tW_antitop_5f_NoFullyHadronicDecays_ext1',
#    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8_ext1-v1/NANOAODSIM',
#    'nEvents': '6127285',
#    'nFiles': '8',
#    'isMC': isMC_,
#    'xs': '',
#    'year': year_
#})

data['people'].append({
    'name': 'ST_tW_top_5f_NoFullyHadronicDecays',
    'inputDataset': '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_new_pmx_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '4955102',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '',
    'year': year_
})

data['people'].append({
    'name': 'WW',
    'inputDataset': '/WW_TuneCP5_13TeV-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '7765828',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '51.723',
    'year': year_
})

data['people'].append({
    'name': 'WZ',
    'inputDataset': '/WZ_TuneCP5_13TeV-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '3928630',
    'nFiles': '4',
    'isMC': isMC_,
    'xs': '47.13',
    'year': year_
})

data['people'].append({
    'name': 'ZZ',
    'inputDataset': '/ZZ_TuneCP5_13TeV-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '1949768',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '16.523',
    'year': year_
})

data['people'].append({
    'name': 'EWKZ2Jets_ZToLL_M-50',
    'inputDataset': '/EWKZ2Jets_ZToLL_M-50_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '952504',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '4.321',
    'year': year_
})
'''
data['people'].append({
    'name': 'Taustar_m375',
    'inputDataset': '/Taustar_TauG_L10000_m375_CP5_13TeV_pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '1',
    'isMC': isMC_,
    'xs': '1.',
    'year': year_,
})

data['people'].append({
    'name': 'Taustar_m500',
    'inputDataset': '/Taustar_TauG_L10000_m500_CP5_13TeV_pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '1',
    'isMC': isMC_,
    'xs': '1.',
    'year': year_,
})

data['people'].append({
    'name': 'Taustar_m1000',
    'inputDataset': '/Taustar_TauG_L10000_m1000_CP5_13TeV_pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '8',
    'isMC': isMC_,
    'xs': '1.',
    'year': year_,
})

data['people'].append({
    'name': 'Taustar_m1250',
    'inputDataset': '/Taustar_TauG_L10000_m1250_CP5_13TeV_pythia8/RunIIFall17NanoAODv7-PU2017_12Apr2018_Nano02Apr2020_102X_mc2017_realistic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '4',
    'isMC': isMC_,
    'xs': '1.',
    'year': year_,
})

with open('mc_2017.json', 'w') as outfile:
   json.dump(data, outfile)

