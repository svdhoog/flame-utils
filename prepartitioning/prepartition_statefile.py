#!/usr/bin/env python
# $Id: prepartition_statefile.py 1713 2009-04-16 14:32:59Z lsc $
# 
# Copyright (c) 2009 STFC Rutherford Appleton Laboratory 
# Author: Lee-Shawn Chin 
# Date  : Mar 2009
#
# Description: 
#    Reorders the agent definitions in input 0.xml file such that the 
#    we get an optimised grouping of agents (based on <dim1> and <dim2>)
#    across processors when the round-robin partitioning is used
# 
import re
import os
import sys

tempfile_format = "tempfile_%s.xml"
key_format = "%s-%s"

def warn(message):
    print >> sys.stderr, "Warning: %s" %message

def error(message):
    print >> sys.stderr, "Error: %s" %message
    sys.exit(1)

def get_agent_str_from_file(file):
    
    buffer = []
    line = file.readline()
    while line.strip()[:9] != "</xagent>":
        buffer.append(line)
        line = file.readline()
    
    buffer.append(line)
    return "".join(buffer)
    
# Check and retrieve input args
if len(sys.argv) != 6:
    error("Usage: %s <infile.xml> <outfile.xml> <dis1> <dis2> <proc_count>" % sys.argv[0])
infilename  = sys.argv[1]
outfilename = sys.argv[2]
dis1        = sys.argv[3]
dis2        = sys.argv[4]
pcount      = int(sys.argv[5])
 
# first, open input file.
try:
    infile = open(infilename, "r")
except:
    error("Unable to read file %s" % infilename)

print "* Parsing %s" % infilename

# Start processing the input file
agent_total = 0
agent_type_count = {}
partid1 = ""
partid2 = ""
filelist = {}
re_part1 = re.compile("\s*<%s>(.+)</%s>" % (dis1, dis1))
re_part2 = re.compile("\s*<%s>(.+)</%s>" % (dis2, dis2))
buffer    = []
prebuffer = []
line = infile.readline()
while (line[:8] != "<xagent>"): # scan lines till first <xagent> tag
    prebuffer.append(line)
    line = infile.readline()
    
buffer.append(line) # insert first xagent line
for line in infile: # continue till end of file
    if line[:9] == "</xagent>":
        buffer.append(line)
        agent_total = agent_total + 1
        
        # quick check
        if partid1 == "": 
            error("Found agent with no <%s>"%dis1)
        if partid2 == "": 
            error("Found agent with no <%s>"%dis2)
    
        # store in the right temp file
        key = key_format % (partid1, partid2)
        if not key in filelist.keys():
            tfilename = tempfile_format % key
            print " - Creating temp file - %s" % tfilename
            filelist[key] = open(tfilename, "w")
            agent_type_count[key] = 0
        
        filelist[key].write("".join(buffer))
        agent_type_count[key] += 1
        
        buffer = [] # reset buffer
        partid = "" # reset partid
        continue
    
    elif line.strip()[:len(dis1)+2] == "<%s>"%dis1:
        # grep the partition id
        match = re_part1.match(line)
        if not match: error("Something's wrong with my regex. Panic!")
        partid1 = match.group(1)
 
    elif line.strip()[:len(dis2)+2] == "<%s>"%dis2:
        # grep the partition id
        match = re_part2.match(line)
        if not match: error("Something's wrong with my regex. Panic!")
        partid2 = match.group(1)   
        
    # carry on
    buffer.append(line) # buffer this line

# close all files
infile.close()
for i in filelist.keys():
    filelist[i].close()

print ""
print "* Figuring out partitions"
print "   :: Agent count     = %d" % agent_total
print "   :: Requested proc  = %d" % pcount
agents_per_proc = agent_total / pcount
if (agent_total % pcount) != 0: agents_per_proc = agents_per_proc + 1
print "   :: Agents per proc ~= %d" % agents_per_proc
print "   :: Agent tally by <%s>-<%s>" % (dis1,dis2)

# generate array of agent types sorted by count (descending)
atypes = []
for k,v in agent_type_count.items(): atypes.append( (v,k) )
atypes.sort()     # sort by count
atypes.reverse()  # in reverse order
for c,t in atypes:
    print "     + %s = %d" % (t, c)

# First, calculate exact number of agents on each proc
p_actual_count = [agents_per_proc for i in xrange(pcount)]
extra = (pcount*agents_per_proc) - agent_total
for i in xrange(1,extra + 1):
    p_actual_count[pcount - i] = p_actual_count[pcount - i] - 1

# determine what each proc should contain
print "   :: Agent distribution by processors"
proc_content = [ {} for i in xrange(pcount)]
p_cur = 0
space_rem = p_actual_count[p_cur]
for c,t in atypes:
    # fill as many procs as possible with this agent type
    while c >= space_rem:
        proc_content[p_cur][t] = space_rem # fill it up
        p_cur = p_cur + 1 # next proc
        c = c - space_rem
        if p_cur < pcount: space_rem = p_actual_count[p_cur] # reset value
        
    
    if c > 0:
        proc_content[p_cur][t] = c
        space_rem = space_rem - c

for i in xrange(len(proc_content)):
    print "     + P%d = " % i,
    print str(proc_content[i])[1:-1]


## Great! We now have agents of different discriminators in different files
## and the other non-agent tags stashed away in prebuffer[]

print ""
print "* Creating %s"%outfilename
try:
    outfile = open(outfilename, "w")
except:
    error("Unable to open %s for writing" % outfilename)

# write out prebuffer
outfile.write("".join(prebuffer))
prebuffer = [] # regain some memory
    
# Open all temp files in read-only mode
for i in filelist.keys():
    tfilename = tempfile_format % i
    print " - Loading %s" % tfilename
    try:
        filelist[i] = open(tfilename, "r")
    except:
        error("Could not read %s. That's strange... " % tfilename)

print " - Interleaving agents so round-robin will place them where we want"
for i in xrange(agent_total):
    # select an agent type (round-robin)
    target_p = i % pcount

    # pick an agent type
    agent_type = proc_content[target_p].keys()[0]
    
    # decrement list
    if proc_content[target_p][agent_type] == 1: 
        del proc_content[target_p][agent_type]
    else: 
        proc_content[target_p][agent_type] -= 1
        
    # grab one from the appropriate file, write to outfile
    outfile.write(get_agent_str_from_file(filelist[agent_type]))


outfile.write("</states>\n")
outfile.close()

print "* Cleaning up the mess we made"    
# close temp files then delete them
for i in filelist.keys():
    filelist[i].close() # close file
    tfilename = tempfile_format % i
    print " - Deleting %s" % tfilename
    os.remove(tfilename)
