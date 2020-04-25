Script to join the output of runs that use multiple nodes.
Author: David Worth, STFC

Usage: ./join.sh <iterations_directory> <number_of_nodes>

Where:
iterations_directory = the directory containing the node*-n.xml files
number_of_nodes = number of processors

Example:
./join.sh ./its 4
