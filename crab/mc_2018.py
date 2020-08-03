import json

data = {}
data['people'] = []
isMC_ = True

#data['people'].append({
#   'name': 'WJetsToLNu',
#   'inputDataset': '/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents': '71026861',
#   'nFiles': '44',
#   'isMC': isMC_,
#   'xs': '61526.7',
#})

#data['people'].append({
#   'name': 'WGToLNuG',
#   'inputDataset': '/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv6-Nano25Oct2019_102X_upgrade2018_realistic_v20-v1/NANOAODSIM',
#   'nEvents': '6012425',
#   'nFiles': '8',
#   'isMC': isMC_,
#   'xs': '405.271',
#})

#data['people'].append({
#   'name' : 'W1JetsToLNu',
#   'inputDataset' : '/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents' : '51082776',
#   'nFiles': '30',
#   'isMC': isMC_,
#   'xs': ''
#})

#data['people'].append({
#   'name' : 'W2JetsToLNu',
#   'inputDataset' : '/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents' : '23290710',
#   'nFiles': '57',
#   'isMC': isMC_,
#   'xs': ''
#})

#data['people'].append({
#   'name' : 'W3JetsToLNu',
#   'inputDataset' : '/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents' : '14508481',
#   'nFiles': '82',
#   'isMC': isMC_,
#   'xs': ''
#})

#data['people'].append({
#   'name' : 'W4JetsToLNu',
#   'inputDataset' : '/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents' : '10082747',
#   'nFiles': '68',
#   'isMC': isMC_,
#   'xs': ''
#})

#data['people'].append({
#    'name': 'QCD_Pt-20toInf_MuEnrichedPt15',
#    'inputDataset': '/QCD_Pt-20toInf_MuEnrichedPt15_TuneCP5_13TeV_pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#    'nEvents': '22165320',
#    'nFiles': '38',
#    'isMC': isMC_,
#    'xs': ''
#})

#data['people'].append({
#   'name': 'WJetsToLNu_0J',
#   'inputDataset': '/WJetsToLNu_0J_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents': '192192460',
#   'nFiles': '98',
#   'isMC': isMC_,
#   'xs': '',
#})

#data['people'].append({
#   'name': 'WJetsToLNu_1J',
#   'inputDataset': '/WJetsToLNu_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents': '171428065',
#   'nFiles': '97',
##   'isMC': isMC_,
#   'xs': '',
#})

#data['people'].append({
#   'name': 'WJetsToLNu_2J',
#   'inputDataset': '/WJetsToLNu_2J_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents': '97596251',
#   'nFiles': '64',
#   'isMC': isMC_,
#   'xs': '',
#})

#data['people'].append({
#   'name': 'DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8',
#   'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents': '997561',
#   'nFiles': '6',
#   'isMC': isMC_,
#   'xs': '6077.22',
#})

#data['people'].append({
#   'name': 'DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_ext2',
#   'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1/NANOAODSIM',
#   'nEvents': '193119590',
#   'nFiles': '201',
#   'isMC': isMC_,
#   'xs': '6077.22',
#})

#data['people'].append({
#   'name': 'DYJetsToLL_M-50_TuneCH3_13TeV-madgraphMLM-herwig7',
#   'inputDataset': '/DYJetsToLL_M-50_TuneCH3_13TeV-madgraphMLM-herwig7/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents': '28430338',
#   'nFiles': '19',
#   'isMC': isMC_,
#   'xs': '6077.22',
#})

#data['people'].append({
#   'name': 'TTJets',
#   'inputDataset': '/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents': '10244307',
#   'nFiles': '53',
#   'isMC': isMC_,
#   'xs': '831.76',
#})

data['people'].append({
   'name': 'TTTo2L2Nu',
   'inputDataset': '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '64310000',
   'nFiles': '60',
   'isMC': isMC_,
   'xs': '88.29',
})

#data['people'].append({
#   'name': 'TTToSemiLeptonic',
#   'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents': '100790000',
#   'nFiles': '94',
#   'isMC': isMC_,
#   'xs': '365.34',
#})

#data['people'].append({
#   'name': 'TTToSemiLeptonic_ext3',
#   'inputDataset': '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext3-v1/NANOAODSIM',
#   'nEvents': '199829998',
#   'nFiles': '151',
#   'isMC': isMC_,
#   'xs': '365.34',
#})

data['people'].append({
   'name': 'WW',
   'inputDataset': '/WW_TuneCP5_13TeV-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '7850000',
   'nFiles': '21',
   'isMC': isMC_,
   'xs': '51.723',
})

data['people'].append({
   'name': 'WZ',
   'inputDataset': '/WZ_TuneCP5_13TeV-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '3885000',
   'nFiles': '6',
   'isMC': isMC_,
   'xs': '47.13',
})

data['people'].append({
   'name': 'ZZ',
   'inputDataset': '/ZZ_TuneCP5_13TeV-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '1979000',
   'nFiles': '3',
   'isMC': isMC_,
   'xs': '16.523',
})

#data['people'].append({
#   'name': 'DYJetsToLL_M-100to200',
#   'inputDataset': '/DYJetsToLL_M-100to200_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
#   'nEvents': '14255862',
#   'nFiles': '15',
#   'isMC': isMC_,
#   'xs': '',
#})

data['people'].append({
   'name': 'DYJetsToLL_M-10to50',
   'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '39392062',
   'nFiles': '27',
   'isMC': isMC_,
   'xs': '',
})

data['people'].append({
   'name': 'DYJetsToLL_M-10to50_ext1',
   'inputDataset': '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1/NANOAODSIM',
   'nEvents': '46976952',
   'nFiles': '79',
   'isMC': isMC_,
   'xs': '',
})

data['people'].append({
   'name': 'DYJetsToLL_M-50',
   'inputDataset': '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '100194597',
   'nFiles': '57',
   'isMC': isMC_,
   'xs': '6077.22',
})

data['people'].append({
   'name': 'DY1JetsToLL_M-50',
   'inputDataset': '/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '68898175',
   'nFiles': '97',
   'isMC': isMC_,
   'xs': '',
})

data['people'].append({
   'name': 'DY2JetsToLL_M-50',
   'inputDataset': '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '20456037',
   'nFiles': '13',
   'isMC': isMC_,
   'xs': '',
})

data['people'].append({
   'name': 'DY3JetsToLL_M-50',
   'inputDataset': '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '5652357',
   'nFiles': '38',
   'isMC': isMC_,
   'xs': '',
})

data['people'].append({
   'name': 'DY4JetsToLL_M-50',
   'inputDataset': '/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1/NANOAODSIM',
   'nEvents': '2809978',
   'nFiles': '38',
   'isMC': isMC_,
   'xs': '',
})

with open('mc_2018.json', 'w') as outfile:
   json.dump(data, outfile)

