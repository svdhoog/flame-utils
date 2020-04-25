#!/usr/bin/env python
# $Id: check_message_consistency.py 1746 2009-05-05 16:31:58Z lsc $
# 
# Copyright (c) 2009 STFC Rutherford Appleton Laboratory 
# Author: Lee-Shawn Chin 
# Date  : Mar 2009
#
# Description: Parse XMML file to obtain information on message I/O and compare
#              them against the usage in *.c files
#
# Usage: ./check_message_consistency.py <path/to/model.xml>
#
import re
import os
import sys
from xml.dom import minidom
from xml.parsers.expat import ExpatError

# If builtin "set" datatype not available (pre Python2.3) load the sets module
try: dummy = set()
except NameError: from sets import Set as set

VERBOSE = False

def report(msg):
    if VERBOSE: print msg
    
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

# get input arguments
if len(sys.argv) != 2:
    print >>sys.stderr, "Usage: %s <model.xml>" % sys.argv[0]
    sys.exit(0)

# input file becomes first input file
xml_filelist = [sys.argv[1]]
c_filelist = []
filelist_all = []

# store agent info
agent = {}
funclist = {}

# keep processing files until we're done
while len(xml_filelist) > 0:
    
    filename = xml_filelist.pop()
    filelist_all.append(filename)
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
    
    # detect function files. add to file list.
    pnodes = dom.getElementsByTagName("functionFiles")
    for pnode in pnodes:
        nodes = pnode.getElementsByTagName("file")
        for node in nodes:
            cfile = getText(node)
            print( "  - Found function file : %s" % os.path.join(dirname, cfile) )
            c_filelist.append(os.path.join(dirname,cfile))
    del(nodes) # free memory
    del(pnodes) # free memory
    

    # look for agents
    agents = dom.getElementsByTagName("xagent")
    for a in agents:
        aname = getText(a.getElementsByTagName("name")[0])
        
        if aname in agent.keys(): # flame supports split definitions of agents
            report( "  - Found duplicate agent definition (%s). Merging." % aname )
        else: report( "  - Found agent : %s" % aname )
        
        # detect functions
        funcnodes = a.getElementsByTagName("function")
        for fnodes in funcnodes:
            fname = getText(fnodes.getElementsByTagName("name")[0])
            if fname in funclist.keys(): 
                report( "    * Duplicate Function: %s" % fname )
                report( "       .... (checking consistency) ..." )
            else:
                report( "    * Function: %s" % fname )
                
            input = []
            output = []
            
            # find input messages for this func
            mnodes = fnodes.getElementsByTagName("input")
            for mnode in mnodes:
                mname = getText(mnode.getElementsByTagName("messageName")[0])
                report( "                  <-- %s" % mname )
                input.append(mname.lower())
            input.sort()
            del(mnodes)
            
            # find output messages for this func
            mnodes = fnodes.getElementsByTagName("output")
            for mnode in mnodes:
                mname = getText(mnode.getElementsByTagName("messageName")[0])
                report( "                  --> %s" % mname )
                output.append(mname.lower())
            output.sort()
            del(mnodes)
            
            if fname not in funclist.keys(): # new func
                funclist[fname] = {}
                funclist[fname]["files"]  = [filename]
                funclist[fname]["agent"]  = [aname]
                funclist[fname]["input"]  = input
                funclist[fname]["output"] = output
            else: # redefinition. check consistency
                
                if input != funclist[fname]["input"] or \
                   output != funclist[fname]["output"]:
                    error("message i/o definition mismatched for function %s" % fname)
                else:
                    if aname not in funclist[fname]["agent"]: 
                        funclist[fname]["agent"].append(aname)
                        funclist[fname]["files"].append(filename)
        del(funcnodes)
filelist_all.extend(c_filelist)
basepath = os.path.commonprefix(filelist_all)
del(filelist_all)

#print funclist
#print c_filelist

# ---------------------- now, time to read functions ---------------------------------
# The following is a quick copy-paste from parse_code_for_messages.py
# It should be rewritten as a separate obj and called here.
# ... maybe next time...

# Prepare out function database and helper routines
F = {}

# interesting tokens
itok = ["{", "}", "/*", "*/", "(", ")", "=", "[", "]"]
# keywords for "<keyword>( ... ) {}" constructs
c_keywords = [ "if", "for", "while", "else", "switch", "return", "sizeof"]
# regex for acceptable function name
re_valid_func = re.compile("^[a-zA-Z_]\w+$")
re_addmsg_func = re.compile("add_(\w+)_message")
re_getmsg_func = re.compile("get_first_(\w+)_message")
re_readmsg_func = re.compile("START_(\w+)_MESSAGE_LOOP")
# magic functions
magic_funcs = ["idle"]

def prep_F(func):
    global F
    if func not in F.keys():
        F[func] = {}
        F[func]["file"] = "" # C file
        F[func]["calls"] = [] # functions called
        F[func]["sends"] = [] # messages sent
        F[func]["reads"] = [] # messages read
        
def add_to_F(func, field, value):
    #prep_F(func)
    if type(value) == type([]): # if array given
        for v in value:
            if v not in F[func][field]: F[func][field].append(v)
    else: 
        if value not in F[func][field]: F[func][field].append(value)
    
def recursively_search_for_sends(func, depth):
    global F, funclist
    
    MAX_DEPTH = 10 # just in case users use recursion as well
    if depth > MAX_DEPTH: 
        warn("Maximum recursion depth met. Going no further")
        return []
    
    outmsg = []
    
    for fcall in F[func]["calls"]:
        if fcall == func: continue # ignore recursion by users
        
        if fcall[:4] == "add_" and fcall[-8:] == "_message":
            match = re_addmsg_func.match(fcall)
            if match: 
                outmsg.append(match.group(1).lower())
                continue
            
        if fcall in F.keys() and fcall not in funclist.keys(): 
            outmsg.extend(recursively_search_for_sends(fcall, depth+1))
    
    return outmsg

def recursively_search_for_reads(func, depth):
    global F, funclist
    
    MAX_DEPTH = 10 # just in case users use recursion as well
    if depth > MAX_DEPTH: 
        warn("Maximum recursion depth met. Going no further")
        return []
    
    inmsg = []
    
    for fcall in F[func]["calls"]:
        if fcall == func: continue # ignore recursion by users
        if fcall in funclist.keys(): continue 
        
        if fcall[:4] == "get_" and fcall[-8:] == "_message":
            match = re_getmsg_func.match(fcall)
            if match: 
                inmsg.append(match.group(1).lower())
                continue
            
        if fcall not in F.keys(): continue
        
        inmsg.extend(F[fcall]["reads"])
        

            
        if fcall in F.keys(): 
            inmsg.extend(recursively_search_for_reads(fcall, depth+1))
    
    return inmsg



for filename in c_filelist:
    
    print "* Reading function file %s" % filename
    try: file = open(filename, "r")
    except: error("Could not read file %s" % filename)
    
    # ------------------------- first pass ------------------------------
    # read file and store content as array of tokens
    # - empty lines are ignored
    # - #.+ lines are ignored
    # - C++ style comments ("//.*") are removed
    # - keywords specified in itok should be stored as separate tokens
    # - commas are converted to spaces
    # - semi-colons are removed
    
    tokens = []
    nextline = file.readline()
    while nextline:
        line = nextline
        nextline = file.readline()
        
        line = line.strip()
        
        if not line: continue # ignore empty lines
        if line[0] == "#": continue # ignore includes and #defines
        
        # trim C++ style comments
        index = line.find("//")
        if index != -1: line = line[:index]
        if not line: continue 
        
        # decorate out tokens before splitting
        for tok in itok: line = line.replace(tok, " %s "%tok)
        line = line.replace(",", " ") # turn commas into spaces
        line = line.replace(";", "") # don't bother about semi-colons
        
        tokens.extend(line.split())
        
    file.close()
    
    # ------------------------- second pass --------------------------------
    # Run through tokens backwards and 
    # a) remove multi-line comments
    # b) squash function_name ( x, y, z) to a single "function_name()" token
    # c) reduce C constructs such as "if (..) { ... }" to "if { ... }" 
    
    in_comment = False
    in_paren   = False
    for i in xrange(len(tokens) -1 ,-1,-1): # go backwards!!
        
        if in_comment:
            if tokens[i] == "/*": in_comment = False # comment end
            del(tokens[i]) # yes, delete the "/*" as well
        elif in_paren:
            if tokens[i] == "(": 
                in_paren = False # parenthesis ends
                if i > 0 and tokens[i-1] not in c_keywords: 
                    tokens[i-1] = "%s()" % tokens[i-1]
                del(tokens[i])
    
            else: del(tokens[i]) # delete only stuff inside parenthesis. 
        else:
            
            if tokens[i] == "*/": # start of comment
                in_comment = True
                del(tokens[i])
                continue
            elif tokens[i] == ")":
                in_paren = True
                del(tokens[i])
                continue
    
    
    
    
    # -------------------------- third pass ------------------------------- 
    # Detect boundaries for function definitions and do the following:
    # - Call graph build based on xxx() tokens found
    # - message reads detected based on START_*_MESSAGE_LOOP calls
    
    in_func_depth = 0
    fname = ""
    
    for i in xrange(len(tokens)):
        token = tokens[i]
        
        if token == "}": 
            in_func_depth -= 1
            continue
        elif token == "{":
            in_func_depth += 1
            continue
        
        if in_func_depth > 0: # within a function definition
    
            if token[-2:] == "()": # function call found
                func = token[:-2]
                valid = re_valid_func.match(func)
                if valid:
                    report( "    + Calls function : %s()" % func )
                    add_to_F(fname, "calls", func)
            
            elif token[:6] == "START_" and token[-13:] == "_MESSAGE_LOOP":
                 match = re_readmsg_func.match(token)
                 if match:
                     msg = match.group(1).lower()
                     report( "    + Reads message  : %s" % msg )
                     add_to_F(fname, "reads", msg)
            
            elif tokens[i+1] == "(":
                valid = re_valid_func.match(token)
                if valid:
                    report( "    + Calls function : %s()" % token )
                    add_to_F(fname, "calls", token)
        
        # outside a function definition
        elif token[-2:] == "()" and tokens[i+1] == "{": 
            fname = token[:-2] # found new function
            while fname[:1] == "*": fname = fname[1:]
            report( " -  Found %s" % fname )
            prep_F(fname)
            F[fname]["file"] = filename
         
# trim "calls" entries to just those defined by modellers
#for func in F.keys():
#    for fcalled in F[func]["calls"]:
#        if fcalled not in F.keys():
#            F[func]["calls"].remove(fcalled)
                                 
# Remove 'magic' functions provided by framework
for f in magic_funcs:
    if f in funclist.keys(): del(funclist[f])

# detect message sent/received by sub-routines
for f in F.keys():
    add_to_F(f, "sends", recursively_search_for_sends(f, 0))
    add_to_F(f, "reads", recursively_search_for_reads(f, 0))
    F[f]["sends"].sort()
    F[f]["reads"].sort()

# remove non-model functions
#for f in F.keys():
#    if f not in funclist.keys(): del(F[f])
    
# trim paths
for f in F.keys(): F[f]["file"] = F[f]["file"][len(basepath):]
for f in funclist.keys(): 
    if len(funclist[f]["files"]) > 0:
        array = funclist[f]["files"]
        funclist[f]["files"] = map(lambda x: x[len(basepath):], array)
        del(array)
    
# Now start looking for problems...
count = 0
print "\n--------------------------------------------------------------"
print "\nAnalysing model definition and function code for problems ..."

func_undefined = []
for f in funclist.keys():
    if f not in F.keys(): 
        func_undefined.append(f)
        del(funclist[f])
        
if len(func_undefined) != 0:
    count += 1
    print "\n%d. The following functions were defined in XMML but not implemented" % count
    for f in func_undefined:
        print "    - %s" % f

IN=0
OUT=1
def print_conflict_table(xmml_array, code_array, direction):
    prebuffer = " "*6
    prebuffer_diff = "  --> "
    joint = list(set.union(set(xmml_array), set(code_array)))
    maxlen = 30 # minimum column width
    for s in joint: maxlen = max(maxlen, len(s))
    none = "#" * maxlen
    
    # just in case, probably not necessary
    joint.sort()
    
    if direction == IN: 
        label1 = "XMML (input) "
        label2 = "Code (reads) "
    else:               
        label1 = "XMML (output)"
        label2 = "Code (adds)  "
    
    gapf = " " * ((maxlen - 6) / 2)
    gapb = " " *(maxlen - ((maxlen - 6) / 2) - 13)
    print ""
    print "%s%s" % (prebuffer, "=" * (maxlen*2 + 4))
    print "%s%s%s%s | %s%s" % (prebuffer, gapf, label1, gapb, gapf, label2)
    print "%s%s" % (prebuffer, "-" * (maxlen*2 + 4))
    for f in joint:
        
        preb = prebuffer
        
        if f in xmml_array: label1 = f
        else: 
            label1 = none
            preb = prebuffer_diff
        
        if f in code_array: label2 = f
        else: 
            label2 = none
            preb = prebuffer_diff
        
        gap = " "*(maxlen - len(label1))
        print "%s%s%s | %s" % (preb, label1, gap, label2)
    print "%s%s" % (prebuffer, "=" * (maxlen*2 + 4))
    #print ""
    
       
msent = []
mrecv = []
csent = []
crecv = []
msgsrc = {}
msgdst = {}

func_all = F.keys()
func_all.extend(funclist.keys())
func_all = set(func_all) # cast to set so we get unique values

for f in funclist.keys():
    model = funclist[f]
    ccode = F[f]
    if model["input"] != ccode["reads"]:
        count += 1
        print "\n\n%d. Mismatching function INPUT for [%s]: %s()" % (count, ", ".join(model["agent"]), f)
        print_conflict_table(model["input"], ccode["reads"], IN)
        print "      XMML File: %s" % ", ".join(model["files"])
        print "      Code File: %s" % ccode["file"]
    if model["output"] != ccode["sends"]:
        count += 1
        print "\n\n%d. Mismatching function OUTPUT for [%s]: %s()" % (count, ", ".join(model["agent"]), f)
        print_conflict_table(model["output"], ccode["sends"], OUT)
        print "      XMML File: %s" % ", ".join(model["files"])
        print "      Code File: %s" % ccode["file"]
        found = True

    msent.extend(model["output"])
    mrecv.extend(model["input"])
    csent.extend(ccode["sends"])
    crecv.extend(ccode["reads"])
    
    for m in model["input"]:
        try: 
            if f not in msgdst[m]: msgdst[m].append(f)
        except KeyError: 
            msgdst[m] = [f]
    for m in model["output"]:
        try: 
            if f not in msgsrc[m]: msgsrc[m].append(f)
        except KeyError: 
            msgsrc[m] = [f]
    for m in ccode["reads"]:
        try: 
            if f not in msgdst[m]: msgdst[m].append(f)
        except KeyError: 
            msgdst[m] = [f]
    for m in ccode["sends"]:
        try: 
            if f not in msgsrc[m]: msgsrc[m].append(f)
        except KeyError: 
            msgsrc[m] = [f]
    

# check for message sent but not read, or vice versa (based on XMML)
msent = set(msent) # convert to set to remove duplicates
mrecv = set(mrecv) # convert to set to remove duplicates
csent = set(csent) # convert to set to remove duplicates
crecv = set(crecv) # convert to set to remove duplicates
sent = set.union(msent, csent) # all sent messages
recv = set.union(mrecv, crecv) # all received messages


def print_incomplete_comm_list(msg):
    global msent, mrecv, csent, crecv
    global msgsrc, msgdst
    global funclist, F
   
    none = " ########## NONE ##########" 
    src_xmml = []
    dst_xmml = []
    src_code = []
    dst_code = []
    
    try: fsrc = msgsrc[msg]
    except KeyError: fsrc = []
        
    try: fdst = msgdst[msg]
    except KeyError: fdst = []

    for f in fsrc:
        model = funclist[f]
        ccode = F[f]
        if msg in model["output"]: src_xmml.append(f)
        if msg in ccode["sends"]: src_code.append(f)
    if len(src_xmml) == 0: src_xmml_str = none
    else: src_xmml_str = ", ".join(src_xmml)
    if len(src_code) == 0: src_code_str = none
    else: src_code_str = ", ".join(src_code)
    
    for f in fdst:
        model = funclist[f]
        ccode = F[f]
        if msg in model["input"]: dst_xmml.append(f)
        if msg in ccode["reads"]: dst_code.append(f)
    if len(dst_xmml) == 0: dst_xmml_str = none
    else: dst_xmml_str = ", ".join(dst_xmml)
    if len(dst_code) == 0: dst_code_str = none
    else: dst_code_str = ", ".join(dst_code)
    
    
    gap = " " * 3
    filelist_format = "%s    (%s): %s"
    print "\n%s* Based on model definition (XMML):" % gap
    print "%s  - Sent by: %s" % (gap, src_xmml_str)
    print "%s  - Read by: %s" % (gap, dst_xmml_str)
    if len(src_xmml) + len(dst_xmml) != 0:
        #print "%s  - Defined in:" % gap
        for f in src_xmml: print filelist_format % (gap, f, ", ".join(funclist[f]["files"]))
        for f in dst_xmml: print filelist_format % (gap, f, ", ".join(funclist[f]["files"]))
    
    print "\n%s* Based on agent function implementation (Code):" % gap
    print "%s  - Sent by: %s" % (gap, src_code_str)
    print "%s  - Read by: %s" % (gap, dst_code_str)
    if len(src_code) + len(dst_code) != 0:
        #print "%s  - Defined in:" % gap
        for f in src_code: print filelist_format % (gap, f, F[f]["file"])
        for f in dst_code: print filelist_format % (gap, f, F[f]["file"])
    

    

for m in sent:
    if m not in recv: # sent, not received
        count += 1
        print "\n\n%d. Message sent but NOT RECEIVED: %s" % (count, m)
        print_incomplete_comm_list(m)

for m in recv:
    if m not in sent: # received, not sent
        count += 1
        print "\n\n%d. Message received but NOT SENT: %s" % (count, m)
        print_incomplete_comm_list(m)

# TODO

if not count: print "(none found)"
else: print "\n\n!!!! (%d problems found) !!!!" % count

