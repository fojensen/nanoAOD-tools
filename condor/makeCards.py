import os

channels = ["Electron", "Muon", "Tau"]
#masses = [175, 250, 375, 500, 625, 750, 1000, 1250, 1500, 1750, 2000, 2500, 3000, 3500, 4000, 4500, 5000]
masses = [1750]

for mass in masses:
    for channel in channels:
        f = open("%s_m%d_A.txt" % (channel, mass), "w+")
        f.write("imax 1 number of bins\n")
        f.write("jmax 2 number of processes minus 1\n")
        f.write("kmax *\n")
        f.write("--------------------------------------------\n")
        f.write("shapes sig  A %s_m%d.root h_Taustar_m%d_A   \n" % (channel, mass, mass))
        f.write("shapes bkg1 A %s_m%d.root h_mcsum_A       \n" % (channel, mass))
        f.write("shapes bkg2 A %s_m%d.root h_BCoD_inc        \n" % (channel, mass))
        f.write("shapes data_obs A %s_m%d.root h_bps_0p1_inc \n" % (channel, mass))
        f.write("observation -1\n")
        f.write("--------------------------------------\n")
        f.write("bin              A      A      A      \n")
        f.write("process          sig    bkg1   bkg2   \n")
        f.write("process          0      1      2      \n")
        f.write("rate             -1     -1     -1      \n")
        f.write("--------------------------------------\n")
        f.write("trigger lnN      1.023  1.023  1.023  \n")
        f.write("lumi lnN         1.023  1.023  1.023  \n")
        f.write("%s_bkg2_A rateParam A bkg2 (@0*@1/@2) %s_bkg2_B,%s_bkg2_C,%s_bkg2_D\n" % (channel,channel,channel,channel))
        f.close()
        for region in ["B", "C", "D"]:
            f = open("%s_m%d_%s.txt" % (channel, mass, region), "w+")
            f.write("imax 1 number of bins\n")
            f.write("jmax 2 number of processes minus 1\n")
            f.write("kmax *\n")
            f.write("--------------------------------------------\n")
            f.write("shapes sig  %s %s_m%d.root h_Taustar_m%d_%s \n" % (region, channel, mass, mass, region))
            f.write("shapes bkg1 %s %s_m%d.root h_mcsum_%s     \n" % (region, channel, mass, region))
            f.write("shapes bkg2 %s %s_m%d.root h_ABCD_%s        \n" % (region, channel, mass, region))
            f.write("shapes data_obs %s %s_m%d.root h_data_%s    \n" % (region, channel, mass, region))
            f.write("observation -1\n")
            f.write("------------------------------------\n")
            f.write("bin              %s     %s     %s   \n" % (region, region, region))
            f.write("process          sig    bkg1   bkg2 \n")
            f.write("process          0      1      2    \n")
            f.write("rate             -1     -1     -1   \n")
            f.write("------------------------------------\n")
            f.write("trigger lnN      1.023  1.023 1.023 \n")
            f.write("lumi lnN         1.023  1.023 1.023 \n")
            f.write("%s_bkg2_%s rateParam %s bkg2 1 [0,3]\n" %(channel,region,region))
            f.close()

        #cmd="combineCards.py %s_A=%s_m%d_A.txt %s_B=%s_m%d_B.txt %s_C=%s_m%d_C.txt %s_D=%s_m%d_D.txt > %s_m%d.txt" % (channel,channel,mass,channel,channel,mass,channel,channel,mass,channel,channel,mass,channel,mass)
        cmd="combineCards.py A=%s_m%d_A.txt B=%s_m%d_B.txt C=%s_m%d_C.txt D=%s_m%d_D.txt > %s_m%d.txt" % (channel,mass,channel,mass,channel,mass,channel,mass,channel,mass)
        os.system(cmd)

    cmd="combineCards.py Electron=Electron_m%d.txt Muon=Muon_m%d.txt Tau=Tau_m%d.txt > AllChannels_m%d.txt" % (mass,mass,mass,mass)
    os.system(cmd)

    #cmd="combine -M AsymptoticLimits %s_m%d.txt -m %d" % (channel, mass, mass)   
    #cmd="combine -M HybridNew datacard_counting_part2.txt --LHCmode LHC-limits -n .part4B --saveHybridResult --fork 0"
    cmd = "combine -M HybridNew AllChannels_m%d.txt --LHCmode LHC-limits -n .part4B --saveHybridResult --fork 0 -m %d" % (mass, mass)
    os.system(cmd)
