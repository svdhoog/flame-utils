#!/bin/bash

#Set directories:
export BASE="$PWD/../.."

POP_GUI_DIR="$BASE/utils/popgui-0.7.14"
#SIM_DIR='path/to/its'
SIM_DIR="$BASE/Financial_Fragility_Network_Model_2.0"

#Select main executable:
MAIN_SD="main_sd" #serial debug
MAIN_SF="main_sf" #serial final
MAIN_PD="main_pd" #parallel debug
MAIN_PF="main_pf" #parallel production

TEST_CLONE_DIR="$BASE/utils/testclone"
CLONE_SCRIPT_DIR="$BASE/utils/cloning"
PREPARTITION_DIR="$BASE/utils/prepartitioning"
JOIN_DIR="$BASE/utils/join"

#Set parameters
NR_NODES=2 #nr of nodes to use for executing parallel code
NR_ITS=1000
NR_CLONES=2 #nr of clones to create, final POP size = (NR_CLONES + 1)*POP size



############################### TESTING SERIAL AND PARALLEL CODE RELATED CONTENT ###########################################################
#Standard command line instantiation:
#Create standard 0.xml from PopGUI (1 region)

#python popcmdline.py $SIM_DIR/its/0.pop $SIM_DIR/its/0_standard.xml >pop_standard_stdout.txt 2>pop_standard_stderr.txt
#python $POP_GUI_DIR/popcmdline.py $SIM_DIR/its/0.pop $SIM_DIR/its/0_standard.xml >pop_stdout.txt 2>pop_stderr.txt

cd $SIM_DIR

#using serial code
# Tested: OK
#./$MAIN_SD $NR_ITS ./its/0_standard.xml  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &
#./$MAIN_SD $NR_ITS ./its/0_standard.xml -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &

# Tested: Stuck!
#./$MAIN_SF $NR_ITS ./its/0_standard.xml  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &

# Tested: GETS STUCK!
#./$MAIN_SF $NR_ITS ./its/0_standard.xml  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &


#using parallel code
# -r: allocate agents to nodes according to round-robin algorithm (random allocation)
# -f: frequency of output

# Tested: Bus error (signal 7)
#mpiexec -n $NR_NODES ./$MAIN_PD $NR_ITS ./its/0_standard.xml  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &

# Tested:  Bus error (signal 7)
#mpiexec -n $NR_NODES ./$MAIN_PD $NR_ITS ./its/0_standard.xml -r -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &

# Tested: Bus error (signal 7)
#mpiexec -n $NR_NODES ./$MAIN_PF $NR_ITS ./its/0_standard.xml  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &

# Tested:  Bus error (signal 7)
#mpiexec -n $NR_NODES ./$MAIN_PF $NR_ITS ./its/0_standard.xml -r -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &
cd -

#Joining output after parallel execution:
#cd $JOIN_DIR
#bash join.sh $SIM_DIR/its $NR_NODES
#cd -


############################### CLONING RELATED CONTENT ###########################################################
#Add markers:
# NOTE: Set constant <xml_cloned>1</xml_cloned> in model.xml
# This is needed to correct the no of regions at run-time, checking if Eurostat->regions = size of region array.
# -r: "replaces" ID, REGION_ID, GOV_ID with markers (placeholders)
# Tags that are replaced:
# <id>: <REPLACE_ID_id>
# <gov_id>: <REPLACE_ID_gov_id> to ensure new households are linked to the government in the region
# <bank_id>: <REPLACE_ID_bank_id> to ensure new households are linked to the bank(s) in the region
# NOTE: If you do not want the <gov_id> to be updated do a search-replace in the 0_markers.xml file:
# <gov_id>REPLACE_ID_  with  <gov_id>

#python instantiate.py -r $SIM_DIR/its/0_for_cloning.pop $SIM_DIR/its/0_markers.xml >pop_markers_stdout.txt 2>pop_markers_stderr.txt
#python $POP_GUI_DIR/instantiate.py -r $SIM_DIR/its/0_for_cloning.pop $SIM_DIR/its/0_markers.xml


# Cloning based on regions: 
# NOTE: This will ADD REGIONS!
# From cloning README: "Will clone 0_markers.xml making $NR_CLONES copies of the original data for each of $NR_NODES nodes.
# There will therefore be $NR_CLONES*$NR_NODES regions in total, $NR_CLONES in node0-0.xml, in node1-0.xml ... nodeN-0.xml"
# NOTE: Requires uncommenting "clone_region" in C code and compile it: cloning/clone_serial.c, cloning/clone_parallel.c (clone_households is commented out)

# 1. Separate 0.xml files for all nodes: files are in cloning/{N1}R_{N2}P where {N1}=nr regions, {N2}=no procs
#cd $CLONE_SCRIPT_DIR
#bash clone.sh $SIM_DIR/its/0_markers.xml $NR_CLONES $SIM_DIR/its/0_cloned.xml -r $NR_NODES >${TEST_CLONE_DIR}/cloning_stdout.txt 2>${TEST_CLONE_DIR}/cloning_stderr.txt
#cd -

# 2. Joined into one 0.xml file:
#cd $CLONE_SCRIPT_DIR
#bash clone.sh $SIM_DIR/its/0_markers.xml $NR_CLONES $SIM_DIR/its/0_cloned.xml -r $NR_NODES -j >${TEST_CLONE_DIR}/cloning_stdout.txt 2>${TEST_CLONE_DIR}/cloning_stderr.txt
#cd -


#Cloning based on populations:
# NOTE: This will *only* clone households!
# NOTE: Requires uncommenting "clone_households" in C code and compile it: cloning/clone_serial.c, cloning/clone_parallel.c (clone_region is commented out)
# NOTE: -j joins all files
#cd $CLONE_SCRIPT_DIR
#bash clone.sh $SIM_DIR/its/0_markers.xml $NR_CLONES $SIM_DIR/its/0_cloned.xml -j  >${TEST_CLONE_DIR}/cloning_stdout.txt 2>${TEST_CLONE_DIR}/cloning_stderr.txt
#cd -


#Partitioning: Pre-partitiioning to 'force' a certain partitiioning across nodes
#Usage:
# python ./prepartition_statefile.py <infile.xml> <outfile.xml> <dis1> <dis2> <proc_count>
# dis1 = first agent memory type to partition on
# dis2 = second mem type to partition on
# proc_count = number of processors

#cd $PREPARTITION_DIR
#python prepartition_statefile.py $SIM_DIR/its/0_cloned.xml $SIM_DIR/its/0_partition.xml region_id name $NR_NODES >${TEST_CLONE_DIR}/prepartition_stdout.txt 2>${TEST_CLONE_DIR}/prepartition_stderr.txt
#cd -


#Simulation:
# NOTE: For parallel execution, you need to have mpi installed (openmpi or mpich2)

# Using region-based cloning: 0_partition.xml has cloned regions
#cd $SIM_DIR

#using parallel code
# -f: frequency of output
# -r: allocate agents to nodes according to round-robin algorithm (random allocation)
#mpirun -n $NR_NODES ./$MAIN $NR_ITS ./its/0_partition.xml -r -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &
#mpiexec -n $NR_NODES ./$MAIN $NR_ITS ./its/0_partition.xml -r -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &

#using serial code
#./$MAIN_SD $NR_ITS ./its/0_partition.xml -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &
#./$MAIN_SF $NR_ITS ./its/0_partition.xml -r -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &
#cd -


# Using population-based cloning: 0_cloned.xml has cloned populations
#cd $SIM_DIR

#using parallel code
# -f: frequency of output
# -r: allocate agents to nodes according to round-robin algorithm (random allocation)
#mpirun -n $NR_NODES ./$MAIN_PD $NR_ITS ./its/0_cloned.xml -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &
#mpiexec -n $NR_NODES ./$MAIN_PD $NR_ITS ./its/0_cloned.xml -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &
#mpiexec -n $NR_NODES ./$MAIN_PD $NR_ITS ./its/0_cloned.xml -r -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &

#using serial code
#./$MAIN_SD $NR_ITS ./its/0_cloned.xml -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &
#./$MAIN_SF $NR_ITS ./its/0_cloned.xml -f 20  >${TEST_CLONE_DIR}/run_stdout.txt 2>${TEST_CLONE_DIR}/run_stderr.txt &

#cd -

#Joining output:
#cd $JOIN_DIR
#bash join.sh $SIM_DIR/its $NR_NODES
#cd -
