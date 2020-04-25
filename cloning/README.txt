# Script to clone 0.xml to make bigger populations
# Author: David Worth, STFC

Usage: 
./clone.sh base_0.xml number_of_clones new_0.xml [-j|-r] [number of nodes]

Arguments:
   $1 - The original 0.xml
   $2 - Number of times to clone
   $3 - New 0.xml file (ignored with -r option)
   $4 - -j if files are to be joined OR -r if you want region partitioned input files. Otherwise use <import>
   $5 - Number of nodes if -r used (Optional, if not set then number of nodes = number of clones+1.)


Example 1:
 ./clone.sh 0_eurace_minimal.xml 2 0_clone2.xml -j

Will clone 0_eurace_minimal.xml twice and put the clones along with the original data to 0_clone2.xml.

Example 2:
 ./clone.sh 0_markers.xml 2 fred.xml -r 2

Will clone 0_markers.xml making 2 copies of the original data for each of 2 nodes. There will therefore be
4 regions in total, 2 in node0-0.xml and 2 in node1-0.xml.

DESCRIPTION

Compiling
Use 'make' to compile in serial, or use 'make parallel' to compile parallel code.

Cloning
This cloning code works with the clone.sh script both in serial or parallel versions of the code.
If the parallel code is used, the cloning algorithm uses multiple processes to create the cloned populations.
After all cloned regions are created, the script can join the files to one file using the -j optional argument.

Agent list
The list of agent names (agent types) to be cloned should be in agent_list.txt, one type name per
line.

The example in test_0.xml and test_agent_list.txt should help you to understand what's required of the 
initial 0.xml and agent_list.txt.

The code is pretty well commented if you need to change it. If you want
to use the old household cloning (cloning household agents only), edit clone_serial.c and clone_parallel.c to
uncomment the clone_households line and comment out the clone_region line.


