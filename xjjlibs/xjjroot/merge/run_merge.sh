#!/bin/bash

skim=1
ntotal=10

## ifs
inputdirs=(
    /eos/cms/store/group/phys_heavyions/wangj/L1PbPb2022/crab_forest_20220512_HIForward_HIRun2018A_HIZeroBiasv1_run327327
    # /export/d00/scratch/jwang/L1PbPb2021/crab_L1_20200322_HIZeroBiasReducedFormat_HIRun2018A_v1_2,
    # /eos/cms/store/group/phys_heavyions/mitaylor/L1MenuStudies/HIForward/ZeroBias_HIRun2018A_MiniAOD_Run326776_v1_1240_HF_14_19_v1/220905_223546/0000/,/eos/cms/store/group/phys_heavyions/wangj/L1PbPb2022/ZeroBias_HIRun2018A_MiniAOD_Run326776_v1_1240_HF_14_19_v1/
)

########################################
## >>> do not change lines below >>>  ##
########################################

tmp=$(date +%y%m%d%H%M%S)
cp merge.cc merge_${tmp}.cc
g++ merge_${tmp}.cc $(root-config --libs --cflags) -I$HOME -g -o merge_${tmp}.exe || exit 1

for i in ${inputdirs[@]}
do
    IFS=','; parse=($i); unset IFS;
    
    inputdir=${parse[0]}
    [[ ! -d $inputdir ]] && { echo -e "\e[31;1mBad input:\e[0m $inputdir." ; continue ; }

    outputdir=${parse[1]}
    IFS='/'; subdir=($inputdir); unset IFS;
    request=${subdir[${#subdir[@]}-1]}
    [[ x${outputdir} == x ]] && primedir=${inputdir%%${request}*} || primedir=$outputdir

    ## ======================================== #

    filelist=filelist_${request}.txt
    [[ -f $filelist ]] && rm $filelist

    ls $inputdir/*.root -d > $filelist

    set -x
    output=${primedir}/${request}_merge.root 
    set +x
    willrun=1
    [[ -f $output ]] && {
        echo "error: output $output exits. "
        echo "remove output? (y/n):"
        rewrite=
        while [[ $rewrite != 'y' && $rewrite != 'n' ]]
        do
            read rewrite
            if [[ $rewrite == 'y' ]] ; then { echo "$output removed" ; rm $output ; } ;
            elif [[ $rewrite == 'n' ]] ; then { echo "please change output file name" ; willrun=0 ; } ;
            else { echo "please input y/n" ; } ; fi ;
        done
    }

    [[ $willrun -eq 0 ]] && continue
    [[ ${1:-0} -eq 1 ]] && { ./merge_${tmp}.exe $output $filelist $skim $ntotal; }
done

rm merge_${tmp}.exe
rm merge_${tmp}.cc
