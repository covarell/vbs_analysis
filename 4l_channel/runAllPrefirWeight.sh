#!/bin/bash 
fail_exit() { echo "$@" 1>&2; exit 1; } 

cd /afs/cern.ch/work/c/covarell/vbs2017/CMSSW_8_0_26_patch1new/src/vbs_analysis/4l_channel
export SCRAM_ARCH=slc7_amd64_gcc530

echo "Start of job on " `date`

source /cvmfs/cms.cern.ch/cmsset_default.sh

eval `scramv1 runtime -sh`

echo "I am here:"
pwd

root -q -b runAllPrefirWeight.c
