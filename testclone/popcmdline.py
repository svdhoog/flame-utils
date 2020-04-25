import sys,pickle
from poplib import *
if __name__=="__main__":
    try:
        setDebugValue(1)
    except:setDebug(1)
    try:
        popfile=sys.argv[1]
        zerofile=sys.argv[2]
    except:
        print "usage:\n %s popfile 0.xml"%sys.argv[0]
        sys.exit()
    pop=pickle.load(open(popfile,"rb"))
    globalSetNumRegions(pop.numregions)
    global popguinumregions
    popguinumregions=pop.numregions
    pop.instantiate(open(zerofile,"w"))
    print "POPULATION IS SUCCESSFULLY CREATED IN ",zerofile
