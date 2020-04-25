#!/usr/bin/env python
# $Id: analyse_model.py 1676 2009-04-01 13:03:48Z lsc $
# 
# Copyright (c) 2009 STFC Rutherford Appleton Laboratory 
# Author: Lee-Shawn Chin 
# Date  : Mar 2009
#
# Description: Parse XMML file to obtain information on messages.
#              If XMML file contains nested models, they will be parsed too.
#
# Usage: ./analyse_model.py <path/to/model.xml>
#
import re
import os
import sys
from xml.dom import minidom
from xml.parsers.expat import ExpatError

def warn(mesg):
    print >>sys.stderr, ">>>>> (Warning): %s" % mesg

def error(mesg):
    print >>sys.stderr, ">>>>> (Error): %s" % mesg
    sys.exit(1)

def getText(node):
    if len(node.childNodes) != 1 or node.childNodes[0].nodeType != node.TEXT_NODE:
        error("getText() routine used on non-text XML node")
    return node.childNodes[0].data.strip()

def getSortedList(unsorted_dict):
    a = []
    for k,v in unsorted_dict.items(): a.append((v,k))
    a.sort()
    a.reverse()    
    return a
        
def getSortedAgentList(agent_dict):
    a = []
    for agent in agent_dict: 
        a.append((agent_dict[agent]["size"],agent))
    a.sort()
    a.reverse()    
    return a
        
        
re_isarray = re.compile(".+\[(\d+)\]")
def get_array_size(string):

    match = re_isarray.match(string)
    if match:
        return int(match.group(1))
    else:
        return 1

# get input arguments
if len(sys.argv) != 2:
    print >>sys.stderr, "Usage: %s <model.xml>" % sys.argv[0]
    sys.exit(0)

# input file becomes first input file
xml_filelist = [sys.argv[1]]

# store sizes of datatypes
dt = {}
dt["int"]    = 4 # start off with the basic datatypes
dt["double"] = 8 # start off with the basic datatypes

# datatypes with dynamic arrays cannot be used in messages
dt_with_dynarray = []

# store sizes of messages
msg = {}
msg_invalid = []

# store agent info
agent = {}

# keep processing files until we're done
while len(xml_filelist) > 0:
    
    filename = xml_filelist.pop()
    dirname = os.path.dirname(filename)
    print "* Loading model file: %s" % filename
    
    # load xml file
    try:
        dom = minidom.parse(filename)
    except IOError:
        error("Unable to read input file (%s)" % filename)
    except ExpatError:
        error("Invalid XML file (%s)" % filename)
    
    
    # detect nested models. add to file list.
    nodes = dom.getElementsByTagName("model")
    for node in nodes:
        status = getText(node.getElementsByTagName("enabled")[0])
        if status != "true": continue
        
        # look for nested models
        modelfile = getText(node.getElementsByTagName("file")[0])
        new_filename = os.path.join(dirname, modelfile) # since path is relative
        print ("  - Found nested model : %s" % new_filename)
        xml_filelist.append(new_filename)
    del(nodes) # free memory
    
    # look for datatypes
    datatypes = dom.getElementsByTagName("dataType")
    for d in datatypes:
        dname = getText(d.getElementsByTagName("name")[0])
        if dname in dt.keys(): error("Datatype (%s) redefined" % dname)
        print "  - Found datatype : %s" % dname
        
        # look for variables in datatype
        esize = 0
        elements = d.getElementsByTagName("variable")
        for elem in elements:
            etype = getText(elem.getElementsByTagName("type")[0])
            ename = getText(elem.getElementsByTagName("name")[0])
            #print ("    + (%s) %s" % (etype, ename))
            
            # get size of this var type
            if etype not in dt.keys(): 
                if etype in dt_with_dynarray:
                    warn("%s uses %s which contains dynamic arrays and cannot be used for messages" % (dname, etype))
                    esize = -999
                    break
                if etype[-6:] == "_array" and etype[:-6] in dt.keys():
                    warn("%s is a dynamic array. %s should not be used in messages" % (etype, dname))
                    esize = -999
                    break
                else: error("Unknown data type : %s" % etype) 
            size_temp = dt[etype]
            
            # get the array size if it's an array
            mul = get_array_size(ename)
            # accumulate size
            esize += size_temp * mul
            
        # register new datatype
        if esize == -999: dt_with_dynarray.append(dname)
        else: dt[dname] = esize    
    del(datatypes) # free memory
    
    # Look for messages
    messages = dom.getElementsByTagName("message")
    for m in messages:
        mname = getText(m.getElementsByTagName("name")[0])
        if mname in msg.keys(): error ("Message (%s) redefined" % mname)
        print "  - Found message : %s" % mname
        
        # look for variables in message
        esize = 0
        elements = m.getElementsByTagName("variable")
        for elem in elements:
            etype = getText(elem.getElementsByTagName("type")[0])
            ename = getText(elem.getElementsByTagName("name")[0])
            #print ("    + (%s) %s" % (etype, ename))
            
            # get size of this var type
            if etype not in dt.keys(): 
                if (etype[-6:] == "_array" and etype[:-6] in dt.keys()) or etype in dt_with_dynarray:
                    warn("Dynamic array used. Message marked as INVALID!")
                    esize = -999
                    break
                else: error("Unknown data type : %s" % etype)
            size_temp = dt[etype]
            
            # get the array size if it's an array
            mul = get_array_size(ename)
            # accumulate size
            esize += size_temp * mul
        
        if esize == -999: msg_invalid.append(mname)
        else: msg[mname] = esize
    del(messages)# free memory
    
    # look for agents
    agents = dom.getElementsByTagName("xagent")
    for a in agents:
        aname = getText(a.getElementsByTagName("name")[0])
        
        if aname in agent.keys(): # flame supports split definitions of agents
            print "  - Found duplicate agent definition (%s). Merging." % aname
        else: print "  - Found agent : %s" % aname
        
        # determine agent size
        esize = 0
        elements = a.getElementsByTagName("variable")
        for elem in elements:
            etype = getText(elem.getElementsByTagName("type")[0])
            ename = getText(elem.getElementsByTagName("name")[0])
            #print ("    + (%s) %s" % (etype, ename))
            
            # get size of this var type
            if etype not in dt.keys(): 
                if etype[-6:] == "_array" and etype[:-6] in dt.keys():
                    warn("Dynamic array used (%s). Agent marked as 'non-migratable' with unspecified size!" % etype)
                    esize = -999
                    break
                elif etype in dt_with_dynarray:
                    warn("Datatype with dynamic array used (%s). Agent marked as 'non-migratable' with unspecified size!" % etype)
                    esize = -999
                    break
                elif etype[-6:] == "_array" and etype[:-6] in dt_with_dynarray:
                    warn("Great... Dynamic array of a datatype with dynamic array used (%s). Agent DEFINITELY marked as 'non-migratable' with unspecified size!" % etype)
                    esize = -999
                    break
                else: error("Unknown data type : %s" % etype)
            size_temp = dt[etype]
            
            # get the array size if it's an array
            mul = get_array_size(ename)
            # accumulate size
            esize += size_temp * mul
        del(elements)
        
        # find output messages
        outmsg = []
        outputs = a.getElementsByTagName("output")
        for output in outputs:
            mname = getText(output.getElementsByTagName("messageName")[0])
            #if mname not in msg: error("Unknown message type - %s" % mname)
            outmsg.append(mname)
        del(outputs)
        
        # find input messages
        inmsg = []
        filterdata = []
        inputs = a.getElementsByTagName("input")
        for input in inputs:
            msgname = getText(input.getElementsByTagName("messageName")[0])
            #if mname not in msg: error("Unknown message type - %s" % mname)
            inmsg.append(msgname)
            
            filters = input.getElementsByTagName("filter")
            for filter in filters:
                
                valuetags = filter.getElementsByTagName("value")
                for value in valuetags:
                    vtext = getText(value)
                    if vtext[:2] == "a.":
                        amem = vtext[2:]
                        filterdata.append((amem,msgname))
                del(valuetags)
            del(filters)

                                
        del(inputs)
        
        # add agent into to list
        if aname in agent.keys(): # merge agent definition
            if agent[aname]["size"] == -999 or esize == -999: 
                agent[aname]["size"] = -999
            else: agent[aname]["size"] += esize
            agent[aname]["msgout"].extend(outmsg)
            agent[aname]["msgin"].extend(inmsg)
            agent[aname]["filters"].extend(filterdata)
        else: # new agent
            agent_data = {}
            agent_data["size"]    = esize
            agent_data["msgout"]  = outmsg
            agent_data["msgin"]   = inmsg
            agent_data["filters"] = filterdata
            agent[aname] = agent_data
         
    # free memory
    dom.unlink()

print ""
print "------------------------------------------------------------"

# -------------- basic Datatype info -------------------------------
print ""
print "Datatypes:"
print "---------"

sd = getSortedList(dt)
for v,k in sd: print " (%5d Bytes) %s" % (v,k)
for k in dt_with_dynarray: print " ( Dyn Memory) %s" % k
dt_max_size,dt_max_name = sd[0]


# -------------- basic Message info -------------------------------

print ""
print "Message list:"
print "-------------"
msg_t   = 0
sm = getSortedList(msg)
msg_maxlen = 0
for v,k in sm:
    print " (%5d Bytes) %s" % (v,k)
    msg_t += v
    msg_maxlen = max(msg_maxlen, len(k))
msg_max_size,msg_max_name = sm[0]
msg_min_size,msg_min_name = sm[len(sm)-1]

if len(msg_invalid) != 0:
    print "\n Note: The following messages are invalid (uses dynamic arrays) ",
    print "and not included in the stats above: %s" % ", ".join(msg_invalid)
    
    
# -------------- basic Agent info -------------------------------
print ""
print "Agent list:"
print "----------"
agent_with_dyn_mem = 0
agent_maxlen = 0
for v,k in getSortedAgentList(agent):
    if v != -999: print " (%5d Bytes) (M:%2d,%2d) %s" % \
                          (v,len(agent[k]["msgin"]), len(agent[k]["msgout"]),k)
    else:
        agent_with_dyn_mem += 1
        print " ( Dyn Memory) (M:%2d,%2d) %s" % \
                (len(agent[k]["msgin"]), len(agent[k]["msgout"]), k)
    
    agent_maxlen = max(agent_maxlen, len(k))


# -------------- Message movement by agent -------------------------------
m_recipient = {} # recipients by message
m_sender    = {} # sender(s) by message
for a in agent.keys(): 
    for inm in agent[a]["msgin"]:
        try: m_recipient[inm].append(a)
        except KeyError: m_recipient[inm] = [a]
    for outm in agent[a]["msgout"]:
        try: m_sender[outm].append(a)
        except KeyError: m_sender[outm] = [a]
        
m_with_no_recipient = 0
m_with_no_sender = 0
m_used = []
print ""
print "Message I/O by agents"
print "---------------------"
for a in agent.keys(): # for each agent
    print "* %s" % a
    
    filtered = []
    for mem,ms in agent[a]["filters"]: filtered.append(ms)
     
    for outm in agent[a]["msgout"]:
        if outm not in m_used: m_used.append(outm)
        dash = "-"
        if outm in m_recipient.keys(): 
            rec = ", ".join(m_recipient[outm])
        else:
            m_with_no_recipient += 1 
            rec = "[        ]"                                     
        print "     |%s( %s )%s> %s" % (dash*2, outm, dash*(msg_maxlen - len(outm) + 3), rec)
    for inm in agent[a]["msgin"]:
        if inm not in m_used: m_used.append(inm)
        dash = "-"
        arrow = "<"
        if inm in m_sender.keys(): 
            sender = ", ".join(m_sender[inm])
        else:
            m_with_no_sender += 1 
            sender = "[        ]"     
            dash = "."
            arrow = "."
        if inm in filtered: filter = "F"
        else: filter = " "
        print "   %s %s%s( %s )%s| %s" % (filter, arrow,dash*(msg_maxlen - len(inm)+3),inm, dash*2, sender)
    print ""
    

# -------------- basic Filters info -------------------------------
print ""
print "Filters:"
print "--------"
mla = 0
mlm = 0
mlx = 0
fcount = 0
fdis = {}
for a in agent.keys(): 
    for mem,ms in agent[a]["filters"]:
        mla = max(mla, len(a))
        mlx = max(mlx, len(mem))
        mlm = max(mlm, len(ms))
        fcount += 1
        try: fdis[mem] += 1
        except KeyError: fdis[mem] = 1
        
for a in agent.keys():
    for mem,ms in agent[a]["filters"]:
        print " Message %s\"%s\" filtered on %s%s -> %s" % (" "*(mlm-len(ms)),ms," "*(mla - len(a)),a,mem)
extra = []
print ""
for v,k in getSortedList(fdis): extra.append("(%s x %d)" % (k, v))
print " Filter keys: %s" % ", ".join(extra)
print ""

# -------------- Communication graph -------------------------------


acount = len(agent)
aindex = {} # mapping of agent name to array index
aname = []
id = 0
for a in agent.keys(): 
    aindex[a] = id
    id += 1
    aname.append(a)
    
# create  adjacency matrix to represent communication graph
comm = [[0 for i in xrange(acount)] for j in xrange(acount)] 
#comm_send = [[0 for i in xrange(acount)] for j in xrange(acount)] 
#comm_recv = [[0 for i in xrange(acount)] for j in xrange(acount)] 

for a in agent.keys():
    for inm in agent[a]["msgin"]: # for each incoming message
        if inm not in m_sender.keys(): continue # No one sending this message
        senders = m_sender[inm]
        for sender in senders: # for each sender of this message
            #comm[aindex[a]][aindex[sender]] += 1
            comm[aindex[sender]][aindex[a]] += 1
            #comm_recv[aindex[a]][aindex[sender]] += 1
            #comm_send[aindex[sender]][aindex[a]] += 1

            
print ""
print "Communication Graph:"
print "--------------------"


offset_str = "%s " % (" " * (agent_maxlen + 5))
divider = "%s%s" % (offset_str, "-" * (4*acount + 3))

print ""
label = "Message Destination"
gap = (agent_maxlen/2 * 3) - (len(label)/2)
print "%s%s %s %s" % (offset_str, "." * gap, label, "." * gap)
print offset_str,
for i in xrange(acount): print "%3d" % i,
print ""
print divider
for i in xrange(acount):
    print "%s%s  %2d |" % (" "*(agent_maxlen - len(aname[i])), aname[i], i),
    for v in comm[i]: print "%3d" % v,
    print "  |"
print divider

print ""
for i in xrange(acount):
    buffer = []
    for id in xrange(acount):
        if comm[i][id] != 0 or comm[id][i]: buffer.append(aname[id])
    print "%s%s <-> %s" % (" " * (agent_maxlen - len(aname[i])), aname[i], ", ".join(buffer))
                          
# -------------- Summary stats -------------------------------
print ""
print "Summary:"
print "-------"
print "Total datatypes          = %d" % (len(dt) + len(dt_with_dynarray))
print "Datatypes with dyn array = %d" % len(dt_with_dynarray)
print "Largest datatype         = %d Bytes (%s)" % (dt_max_size, dt_max_name)
print "Smallest datatype        = 4 Bytes (int)"

print ""
print "Total Number of messages = %d" % len(msg)
print "Average size of message  = %.2f Bytes" % (float(msg_t) / len(msg))
print "Largest message          = %d Bytes (%s)" % (msg_max_size,msg_max_name)
print "Smallest message         = %d Bytes (%s)" % (msg_min_size,msg_min_name)
print "Messages with filters    = %d" % fcount

print ""
print "Message types actually used by model (sent AND received) = %d" % \
          (len(m_used) - m_with_no_sender - m_with_no_recipient)
print "Message types received but never sent = %d" % m_with_no_sender
print "Message types send but never received = %d" % m_with_no_recipient
print "Message types that were never used    = %d" % (len(msg) - len(m_used))

print ""
print "Total Number of agents   = %d" % len(agent)
print "Agents with dyn memory   = %d" % agent_with_dyn_mem
