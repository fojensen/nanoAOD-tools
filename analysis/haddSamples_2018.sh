#python ../scripts/haddnano.py ./outputData/ `xrdfsls -u | grep \.root`

python ../scripts/haddnano.py ./outputData_2018/SingleMuon_2018A.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/SingleMuon_2018B.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/SingleMuon_2018C.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/SingleMuon_2018D.root `xrdfsls -u  | grep \.root`

python ../scripts/haddnano.py DYJetsToLL_M-10to50.1.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py DYJetsToLL_M-10to50.2.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/DYJetsToLL_M-10to50.root DYJetsToLL_M-10to50.1.root DYJetsToLL_M-10to50.2.root
rm DYJetsToLL_M-10to50.1.root
rm DYJetsToLL_M-10to50.2.root

python ../scripts/haddnano.py ./outputData_2018/DY01234JetsToLL_M-50.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/DY1JetsToLL_M-50.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/DY2JetsToLL_M-50.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/DY3JetsToLL_M-50.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/DY4JetsToLL_M-50.root `xrdfsls -u  | grep \.root`

python ../scripts/haddnano.py ./outputData_2018/TTTo2L2Nu.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py TTToSemiLeptonic.1.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py TTToSemiLeptonic.2.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/TTToSemiLeptonic.root TTToSemiLeptonic.1.root TTToSemiLeptonic.2.root
rm TTToSemiLeptonic.1.root
rm TTToSemiLeptonic.2.root

python ../scripts/haddnano.py ./outputData_2018/ST_tW_antitop.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/ST_tW_top.root `xrdfsls -u  | grep \.root`

python ../scripts/haddnano.py ./outputData_2018/WW.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/WZ.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/ZZ.root `xrdfsls -u  | grep \.root`

python ../scripts/haddnano.py ./outputData_2018/EWKZ2Jets_ZToLL_M-50.root `xrdfsls -u | grep \.root`

python ../scripts/haddnano.py ./outputData_2018/Taustar_m250.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/Taustar_m375.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/Taustar_m500.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/Taustar_m625.root `xrdfsls -u  | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/Taustar_m750.root `xrdfsls -u  | grep \.root`

python ../scripts/haddnano.py ./outputData_2018/WGToLNuG.root `xrdfsls -u | grep \.root`
python ../scripts/haddnano.py ./outputData_2018/QCD_Pt-20toInf_MuEnrichedPt15.root `xrdfsls -u | grep \.root`

