#!/bin/bash
OLDIFS=$IFS
IFS=";"

_now=$(date +"%m_%d_%Y_%H_%M_%S_%N")
_file="./results/nomad_$_now.txt"

while read Qtot ElevAmont
do
    echo $Qtot $ElevAmont > $_file
    echo $Qtot $ElevAmont > param_bb.txt
    nomad ./param.txt >> $_file
    _now=$(date +"%m_%d_%Y_%H_%M_%S_%N")
    _file="./results/nomad_$_now.txt"
    echo -n .
done < $1
IFS=$OLDIFS
