import os

channels = ["Muon", "Electron", "Tau", "MuonEG"]
#masses = [175, 250, 375, 500, 625, 750, 1000, 1250, 1500, 2000, 2500]
masses = [500]

for mass in masses:

   f = open("MuTau_m%d_A.txt" % mass, "w+")
   f.write("imax 1 number of bins\n")
   f.write("jmax 2 number of processes minus 1\n")
   f.write("kmax *\n")
   f.write("-------------------------------------------------------\n")
   f.write("shapes sig A tree_m%d.root h_Taustar_m%d_A\n" % (mass, mass))
   f.write("shapes bkg1 A tree_m%d.root h_mcsum_A\n" % mass)
   f.write("shapes bkg2 A tree_m%d.root h_BCoD_inc\n" % mass)
   f.write("shapes data_obs A tree_m%d.root h_bkgsum_inc\n" % mass)
   f.write("observation -1\n")
   f.write("--------------------------------------------------------\n")
   f.write("bin              A          A         A\n")
   f.write("process          sig        bkg1      bkg2\n")
   f.write("process          0          1         2\n")
   f.write("rate             -1         -1        -1\n")
   f.write("--------------------------------------------------------\n")
   f.write("trigger lnN      1.023      1.023     -\n")
   f.write("lumi lnN         1.023      1.023     -\n")
   f.write("bkg2_A rateParam A bkg2 (@0*@1/@2) bkg2_B,bkg2_C,bkg2_D\n")
   f.close()

   for region in ["B", "C", "D"]:
      f = open("MuTau_m%d_%s.txt" % (mass, region), "w+")
      f.write("imax 1 number of bins\n")
      f.write("jmax 2 number of processes minus 1\n")
      f.write("kmax *\n")
      f.write("-------------------------------------------------------\n")
      f.write("shapes sig %s tree_m%d.root h_Taustar_m%d_%s\n" % (region, mass, mass, region))
      f.write("shapes bkg1 %s tree_m%d.root h_mcsum_%s\n" % (region, mass, region)) 
      f.write("shapes bkg2 %s tree_m%d.root h_ABCD_%s\n" % (region, mass, region))
      f.write("shapes data_obs %s tree_m%d.root h_data_%s\n" % (region, mass, region))
      f.write("observation -1\n")
      f.write("--------------------------------------------------------\n")
      f.write("bin              %s         %s        %s\n" %(region, region, region))
      f.write("process          sig        bkg1      bkg2\n")
      f.write("process          0          1         2\n")
      f.write("rate             -1         -1        -1\n")
      f.write("--------------------------------------------------------\n")
      f.write("trigger lnN      1.023      1.023     -\n")
      f.write("lumi lnN         1.023      1.023     -\n")
      f.write("bkg2_%s rateParam %s bkg2 1 [0,10]\n" %(region, region))
      f.close()

   cmd="combineCards.py regionA=MuTau_m%d_A.txt regionB=MuTau_m%d_B.txt regionC=MuTau_m%d_C.txt regionD=MuTau_m%d_D.txt > MuTau_m%d.txt" % (mass,mass,mass,mass,mass)
   os.system(cmd)

