#!/bin/bash

FIGDIR=/afs/cern.ch/work/w/wangj/RECO2025/CMSSW_13_2_10/src/tracklet/analysis

[[ $# -eq 0 ]] && set -- "figs/"

for dir in "$@"
do
    # echo $dir

    dir=${dir%%"/"} # remove possible last slash
    lastdir=${dir##*/} # last directory
    subdir="./"${dir%%$lastdir}

    # echo $FIGDIR/$dir $subdir

    set -x
    scp -r wangj@lxplus.cern.ch:$FIGDIR/$dir $subdir
    set +x

done
