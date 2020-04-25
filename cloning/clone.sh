#!/bin/bash
#
# Script to clone 0.xml to make bigger populations
#
# Arguments:
#   $1 - The original 0.xml
#   $2 - Number of times to clone (per node if 5th argument is supplied)
#   $3 - New 0.xml file
#   $4 - -j if files are to be joined. -r if you want region partitioned input files. Otherwise use <import>
#   $5 - Number of nodes if -r used (Optional, if not set then number of nodes = number of clones+1.)
# echo $0 $1 $2 $3 $4 $5

if [ -e clone_parallel ]; then
  echo "Will do parallel cloning"
  echo
elif [ -e clone_serial ]; then
  echo "Will do serial cloning"
  echo
else
  echo
  echo "Neither clone_serial nor clone_parallel are available to do the cloning."
  echo "Run \"make serial\" or \"make parallel\" (requires MPI) to create one of these programs."
  echo
  exit 0
fi

if [ x$5 != "x" ]; then
  let "num_nodes = $5"
  let "clones_per_node = $2"
  let "num_regions = $num_nodes * $clones_per_node"
else
  let "num_nodes = $2 + 1"
  let "clones_per_node = 1"
  let "num_regions = $num_nodes"
fi

#echo "cg:" $num_regions, $num_nodes

# Work out the increment to add to agent ids for each clone
increment=`grep "<xagent" "$1" | wc -l`

echo "Initial 0.xml contains $increment agents"

# Link initial 0.xml to fixed file so clone_* can read it
ln -sf $1 0.xml

# If clone_parallel exists and is executable use that with mpirun
# otherwise run clone_serial many times
if [ -x clone_parallel ]; then
  if [ $num_regions -le 20 ]; then
    mpirun -np $num_regions ./clone_parallel $increment
  else
    let "remain = $num_regions % 20"
    let "div = $num_regions/20"
    for i in `seq 1 $div`
    do
      echo Do i^th lot of 20 - $i
      let "offset = (i - 1) * 20"
      mpirun -np 20 ./clone_parallel $increment $offset
    done
    echo Do remaining $remain
    let "offset = $div * 20"
    mpirun -np $remain ./clone_parallel $increment $offset
  fi
elif [ -x clone_serial ]; then
  let "times = $num_regions - 1"
  for i in `seq 0 $times`
  do
    echo "Clone iteration $i"
    ./clone_serial $increment $i
  done
fi

# If -r option supplied then copy the extra stuff from original 0.xml to tmp1
# tmp1 is added to 0_* later
if [ x$4 != "x" ] && [ $4 = "-r" ]; then
  sed -n '1,/<\/environment>/p' "$1" > tmp1
  # Fix the <total_regions> tag
  sed "s/<total_regions>[0-9]<\/total_regions>/<total_regions>$num_regions<\/total_regions>/g" tmp1 > tmp
  mv tmp tmp1
fi

# Copying first set of cloned agents to new 0.xml but remove last </states> line
sed -e '/<\/states>/d' < 0_0.xml > $3

# Fix the <total_regions> tag
sed "s/<total_regions>[0-9]<\/total_regions>/<total_regions>$num_regions<\/total_regions>/g" $3 > tmp
mv tmp $3
cp $3 0_0.xml

# If -j option supplied then add other data
if [ x$4 != "x" ] && [ $4 = "-j" ]; then
  for i in `seq 1 $2`
  do
    echo "Add cloned data $i"
    cat 0_$i.xml >> $3
  done
  # Put the final tag back
  echo "</states>" >> $3
  rm 0_[0-9]*.xml
  echo New 0.xml contains `grep "<xagent" "$3" | wc -l` agents
elif [ x$4 != "x" ] && [ $4 = "-r" ]; then
  rm -f node*
  let "num_agents = 0"
  let "limit = $num_nodes - 1"
  for i in `seq 0 $limit`
  do
    if [ $i -gt 0 ]; then cat tmp1 > node$i-0.xml; fi
    for j in `seq 1 $clones_per_node`
    do
      let "k = i * $clones_per_node + j - 1"
      let "r = i * $clones_per_node + j"
      sed "s/<list_of_regions>{1}<\/list_of_regions>/<list_of_regions>{$r}<\/list_of_regions>/g" 0_$k.xml > tmp
      cat tmp >> node$i-0.xml
      #cat 0_$k.xml >> node$i-0.xml
    done
    let "num_agents = $num_agents + `grep "<xagent" node$i-0.xml | wc -l`"
    echo "</states>" >> node$i-0.xml
  done
  mkdir ${num_regions}R_$5P
  mv node* ${num_regions}R_$5P
  rm 0_[0-9]*.xml tmp1 tmp $3
  echo New 0.xml contains $num_agents agents
else
  echo "Adding <import> sections"
  echo "<imports>" >> $3
  num_agents=`grep "<xagent" "$3" | wc -l`
  for i in `seq 1 $2`
  do
    echo "<import>
<location>./0_$i.xml</location>
<format>xml</format>
<type>agent</type>
</import>" >> $3
    let "num_agents = $num_agents + `grep "<xagent" 0_$i.xml | wc -l`"
  done
  echo "</imports>" >> $3
  # Put the final tag back
  echo "</states>" >> $3
  echo New 0.xml contains $num_agents agents
  rm 0_0.xml
fi

rm 0.xml
