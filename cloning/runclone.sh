#!/bin/bash
#./clone.sh base_0.xml number_of_clones new_0.xml [-j|-r] [number of nodes]

#Arguments:
#   $1 - The original 0.xml
#   $2 - Number of times to clone
#   $3 - New 0.xml file (ignored with -r option)
#   $4 - -j if files are to be joined OR -r if you want region partitioned input files. Otherwise use <import>
#   $5 - Number of nodes if -r used (Optional, if not set then number of nodes = number of clones+1.)

#./clone.sh base_0.xml number_of_clones new_0.xml -j

#Example with markers:
./clone.sh 0_small_ids.xml 1 0_cloned_2R.xml -j

#Example without markers: clone only households
#./clone.sh 0_small.xml 1 0_cloned_2R_hh.xml -j
