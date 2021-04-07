import os
for filename in os.listdir("./crab_projects/"):
    print("doing %s" % filename)
    filename = "crab status ./crab_projects/" + filename
    #filename = "crab resubmit ./crab_projects/" + filename
    #filename = "crab kill ./crab_projects/" + filename
    os.system(filename)
