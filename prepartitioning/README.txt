Script to pre-partition the agents to 'fool' the round-robin algorithm.
Author: David Worth, STFC

Reorders the agents in a 0.xml file in such a way to obtain a partitioning based on two memory variables.

Usage: 
python ./prepartition_statefile.py <infile.xml> <outfile.xml> <dis1> <dis2> <proc_count>

Where:
dis1 = first agent memory type to partition on
dis2 = second mem type to partition on
proc_count = number of processors

Example:
python ./prepartition_statefile.py 0.xml new_0.xml region_id name 4
