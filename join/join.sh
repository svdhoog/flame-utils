#!/bin/sh

if [ $# == 0 ]; then
  echo Usage: $0 iterations_directory number_of_nodes
  exit 1
fi

for file in ${1}/node0-*
do
  iteration=${file##${1}/node*-}
  iteration=${iteration%%.xml}
  echo Iteration $iteration
  cat ${1}/node0-${iteration}.xml > ${1}/${iteration}.xml
  for (( i = 1 ; i < ${2} ; i++ ))
  do
    cat ${1}/node${i}-${iteration}.xml >> ${1}/${iteration}.xml
  done
done
