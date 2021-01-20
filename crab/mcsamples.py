import json

data = {}
data['people'] = []

isMC_ = True
year_ = 2018

data['people'].append({
    'name': 'DYJetsToLL_M10to50',
    'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '86369014', #39392062+46976952
    'nFiles': '27',
    'isMC': isMC_,
    'xs': '22634.0',
    'year': year_
})

data['people'].append({
    'name': 'DYJetsToLL_M10to50_ext1',
    'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1/NANOAODSIM',
    'nEvents': '86369014', #39392062+46976952
    'nFiles': '79',
    'isMC': isMC_,
    'xs': '22634.0',
    'year': year_
})

data['people'].append({
    'name': 'DYJetsToLL_M50',
    'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '100194597',
    'nFiles': '57',
    'isMC': isMC_,
    'xs': '5765.4',
    'year': year_
})

data['people'].append({
    'name': 'DY1JetsToLL_M50',
    'inputDataset': '/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '68898175',
    'nFiles': '97',
    'isMC': isMC_,
    'xs': '1178.3',
    'year': year_
})

data['people'].append({
    'name': 'DY2JetsToLL_M50',
    'inputDataset': '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'isMC': isMC_,
    'nEvents': '20456037',
    'nFiles': '13',
    'isMC': isMC_,
    'xs': '387.3',
    'year': year_
})

data['people'].append({
    'name': 'DY3JetsToLL_M50',
    'inputDataset': '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '5652357',
    'nFiles': '38',
    'isMC': isMC_,
    'xs': '118.4',
    'year': year_
})

data['people'].append({
    'name': 'DY4JetsToLL_M50',
    'inputDataset': '/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '2809978',
    'nFiles': '38',
    'isMC': isMC_,
    'xs': '63.7',
    'year': year_
})

data['people'].append({
    'name': 'TTJets',
    'inputDataset': '/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '10244307',
    'nFiles': '53',
    'isMC': isMC_,
    'xs': '831.8', #says TT in ztautau
    'year': year_
})

data['people'].append({
    'name': 'TTTo2L2Nu',
    'inputDataset': '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '64310000',
    'nFiles': '60',
    'isMC': isMC_,
    'xs': '88.29', #ra2b:88.29
    'year': year_
})

data['people'].append({
    'name': 'TTToSemileptonic',
    'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '300619998', #100790000+199829998
    'nFiles': '94',
    'isMC': isMC_,
    'xs': '365.34', #ra2b:365.34
    'year': year_
})

data['people'].append({
    'name': 'TTToSemileptonic_ext3',
    'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext3-v1/NANOAODSIM',
    'nEvents': '300619998', #100790000+199829998
    'nFiles': '151',
    'isMC': isMC_,
    'xs': '365.34', #ra2b:365.34
    'year': year_
})

data['people'].append({
    'name': 'ST_tW_antitop',
    'inputDataset': '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_EXT_102X_upgrade2018_realistic_v21_ext1-v1/NANOAODSIM',
    'nEvents': '1086487',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '34.97', #ra2b:34.97
    'year': year_
})

data['people'].append({
    'name': 'ST_tW_top',
    'inputDataset': '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_EXT_102X_upgrade2018_realistic_v21_ext1-v1/NANOAODSIM',
    'nEvents': '1085847',
    'nFiles': '9',
    'isMC': isMC_,
    'xs': '34.91', #ra2b:34.91
    'year': year_
})

data['people'].append({
    'name': 'WW',
    'inputDataset': '/WW_TuneCP5_13TeV-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '7850000',
    'nFiles': '21',
    'isMC': isMC_,
    'xs': '51.723', #ra2b:51.723
    'year': year_
})

data['people'].append({
    'name': 'WZ',
    'inputDataset': '/WZ_TuneCP5_13TeV-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '3885000',
    'nFiles': '6',
    'isMC': isMC_,
    'xs': '47.13', #ra2b:47.13; 
    'year': year_
})

data['people'].append({
    'name': 'ZZ',
    'inputDataset': '/ZZ_TuneCP5_13TeV-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '1979000',
    'nFiles': '3',
    'isMC': isMC_,
    'xs': '16.523', #ra2b: 16.523;
    'year': year_
})

data['people'].append({
    'name': 'EWKZ2Jets_ZToLL_M50',
    'inputDataset': '/EWKZ2Jets_ZToLL_M-50_TuneCP5_PSweights_13TeV-madgraph-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '928000',
    'nFiles': '2',
    'isMC': isMC_,
    'xs': '4.0',
    'year': year_
})

data['people'].append({
    'name': 'QCD_Mu15',
    'inputDataset': '/QCD_Pt-20toInf_MuEnrichedPt15_TuneCP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '22165320',
    'nFiles': '38',
    'isMC': isMC_,
    'xs': '239400.0', #SummaryTable1G25ns: 239400.0
    'year': year_,
})

data['people'].append({
    'name': 'WJetsToLNu',
    'inputDataset': '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '71026861',
    'nFiles': '44',
    'isMC': isMC_,
    'xs': '61526.7',
    'year': year_,
})

data['people'].append({
    'name': 'W1JetsToLNu',
    'inputDataset': '/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '51082776',
    'nFiles': '30',
    'isMC': isMC_,
    'xs': '11778.4',
    'year': year_,
})

data['people'].append({
    'name': 'W2JetsToLNu',
    'inputDataset': '/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '23290710',
    'nFiles': '57',
    'isMC': isMC_,
    'xs': '3840.2',
    'year': year_,
})

data['people'].append({
    'name': 'W3JetsToLNu',
    'inputDataset': '/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '14508481',
    'nFiles': '82',
    'isMC': isMC_,
    'xs': '1166.0',
    'year': year_,
})

data['people'].append({
    'name': 'W4JetsToLNu',
    'inputDataset': '/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '10082747',
    'nFiles': '68',
    'isMC': isMC_,
    'xs': '593.1',
    'year': year_,
})

data['people'].append({
    'name' : 'GluGluHToTauTau',
    'inputDataset': '/GluGluHToTauTau_M125_13TeV_powheg_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
    'nEvents': '12575000',
    'nFiles': '24',
    'isMC': isMC_,
    'xs': '2.8',
    'year': year_,
})

data['people'].append({
    'name' : 'VBFHToTauTau',
    'inputDataset': '/VBFHToTauTau_M125_13TeV_powheg_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1/NANOAODSIM',
    'nEvents': '3000000',
    'nFiles': '35',
    'isMC': isMC_,
    'xs': '0.2',
    'year': year_,
})

with open('mcsamples.json', 'w') as outfile:
   json.dump(data, outfile)
