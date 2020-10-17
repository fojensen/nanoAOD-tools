import json

data = {}
data['people'] = []
isMC_ = True
year_ = "2016"

'''data['people'].append({
    'name': 'DYJetsToLL_M-10to50',
    'inputDataset': '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '34909242',
    'nFiles': '26',
    'isMC': isMC_,
    'xs': '18610.',
    'year': year_
})

data['people'].append({
    'name': 'DYJetsToLL_M-50_ext1',
    'inputDataset': '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '49748967',
    'nFiles': '33',
    'isMC': isMC_,
    'xs': '18610.',
    'year': year_
})

data['people'].append({
    'name': 'DYJetsToLL_M-50_ext2',
    'inputDataset': '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8_ext2-v1/NANOAODSIM',
    'nEvents': '93007332',
    'nFiles': '70',
    'isMC': isMC_,
    'xs': '6077.22',
    'year': year_
})

data['people'].append({
    'name': 'DY1JetsToLL_M-50',
    'inputDataset': '/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '63730337',
    'nFiles': '41',
    'isMC': isMC_,
    'xs': '1007.57668',
    'year': year_
})

data['people'].append({
    'name': 'DY2JetsToLL_M-50',  
    'inputDataset': '/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '19879279',
    'nFiles': '18',
    'isMC': isMC_,
    'xs': '344.336324',
    'year': year_
})

data['people'].append({
    'name': 'DY3JetsToLL_M-50',
    'inputDataset': '/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '5857441',
    'nFiles': '7',
    'isMC': isMC_,
    'xs': '125.267478',
    'year': year_
})

data['people'].append({
    'name': 'DY4JetsToLL_M-50',
    'inputDataset': '/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '4197868',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '71.1999878',
    'year': year_
})

data['people'].append({
    'name': 'TTTo2L2Nu',
    'inputDataset': '/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '67860400',
    'nFiles': '119',
    'isMC': isMC_,
    'xs': '88.29',
    'year': year_
})

data['people'].append({
    'name': 'ST_tW_antitop_5f_NoFullyHadronicDecays',
    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIISummer16NanoAODv7-Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '10240710',
    'nFiles': '11',
    'isMC': isMC_,
    'xs': '',
    'year': year_
})

data['people'].append({
    'name': 'ST_tW_top_5f_NoFullyHadronicDecays',
    'inputDataset': '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/RunIISummer16NanoAODv7-Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '1019598',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '',
    'year': year_
})

data['people'].append({
    'name': 'WW',
    'inputDataset': '/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '994012',
    'nFiles': '1',
    'isMC': isMC_,
    'xs': '51.723',
    'year': year_
})

data['people'].append({
    'name': 'WW_ext1',
    'inputDataset': '/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '6988168',
    'nFiles': '7',
    'isMC': isMC_,
    'xs': '51.723',
    'year': year_
})

data['people'].append({
    'name': 'WZ',
    'inputDataset': '/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '1000000',
    'nFiles': '4',
    'isMC': isMC_,
    'xs': '47.13',
    'year': year_
})

data['people'].append({
    'name': 'WZ_ext1',
    'inputDataset': '/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '2997571',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '47.13',
    'year': year_
})

data['people'].append({
    'name': 'ZZ',
    'inputDataset': '/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '990064',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '16.523',
    'year': year_
})

data['people'].append({
    'name': 'ZZ_ext1',
    'inputDataset': '/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '998034',
    'nFikes': '1',
    'isMC': isMC_,
    'xs': '16.523',
    'year': year_
})

data['people'].append({
    'name': 'EWKZ2Jets_ZToLL_M-50',
    'inputDataset': '/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '150000',
    'nFiles': '2',
    'isMC': isMC_,
    'xs': '4.321',
    'year': year_
})

data['people'].append({
    'name': 'EWKZ2Jets_ZToLL_M-50_ext1',
    'inputDataset': '/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8_ext1-v1/NANOAODSIM',
    'nEvents': '150000',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '4.321',
    'year': year_
})

data['people'].append({
    'name': 'EWKZ2Jets_ZToLL_M-50_ext2',
    'inputDataset': '/EWKZ2Jets_ZToLL_M-50_13TeV-madgraph-pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8_ext2-v1/NANOAODSIM',
    'nEvents': '699451',
    'nFiles': '1',
    'isMC': isMC_,
    'xs': '4.321',
    'year': year_
})
'''
data['people'].append({
    'name': 'Taustar_m500',
    'inputDataset': '/Taustar_TauG_L10000_m500_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '1.',
    'year': year_,
})

data['people'].append({
    'name': 'Taustar_m625',
    'inputDataset': '/Taustar_TauG_L10000_m625_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '1.',
    'year': year_,
})

data['people'].append({
    'name': 'Taustar_m750',
    'inputDataset': '/Taustar_TauG_L10000_m750_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '15',
    'isMC': isMC_,
    'xs': '1.',
    'year': year_,
})

data['people'].append({
    'name': 'Taustar_m1250',
    'inputDataset': '/Taustar_TauG_L10000_m1250_13TeV_pythia8/RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/NANOAODSIM',
    'nEvents': '50000',
    'nFiles': '5',
    'isMC': isMC_,
    'xs': '1.',
    'year': year_,
})

with open('mc_2016.json', 'w') as outfile:
   json.dump(data, outfile)

