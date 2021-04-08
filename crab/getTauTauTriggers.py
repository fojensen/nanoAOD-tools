import ROOT as r
#filename='/store/data/Run2016B/Tau/NANOAOD/ver2_HIPM_UL2016_MiniAODv1_NanoAODv2-v1/230000/0A1E42DB-0058-554D-8FEA-A0AB285994F3.root'
#filename='/store/data/Run2016E/Tau/NANOAOD/UL2016_MiniAODv1_NanoAODv2-v1/270000/0DF382D2-5FB0-0140-825E-ED940DBF92E9.root'
filename='/store/data/Run2016H/Tau/NANOAOD/UL2016_MiniAODv1_NanoAODv2-v1/260000/63A9B29E-0840-F645-994D-886B2A61879B.root'
#filename='/store/data/Run2017B/Tau/NANOAOD/UL2017_MiniAODv1_NanoAODv2-v1/270000/027F2E5D-15F8-1F4A-BBEC-22C97DF7C165.root'
#filename='/store/data/Run2017F/Tau/NANOAOD/UL2017_MiniAODv1_NanoAODv2-v1/270000/49D499EE-862D-0941-9DA0-DA6ACF371D86.root'
#filename='/store/data/Run2018A/Tau/NANOAOD/UL2018_MiniAODv1_NanoAODv2-v1/280000/0055C475-632C-734F-B151-5B5DCE947647.root'
#filename='/store/data/Run2018D/Tau/NANOAOD/UL2018_MiniAODv1_NanoAODv2-v1/00000/E41EF50B-2961-C649-A341-AE5B1D92E5E3.root'

f = r.TFile.Open('root://cmsxrootd.fnal.gov//'+filename)
tree = f.Get("Events")
thelist = tree.GetListOfBranches()
thething = thelist.Print()
print thething
