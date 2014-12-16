#!/bin/bash

CONFIG=config_pps_cern2012_09_2fei4_geoid88.cfg
#for RUN in `seq 72653 72708`;
RUN=72653
#do
if [[ -s ./native/run0${RUN}.raw ]] 
 then 
#../../jobsub.py --config=${CONFIG} converter $RUN
#../../jobsub.py --config=${CONFIG} clustering $RUN
#../../jobsub.py --config=${CONFIG} hitmaker $RUN
#../../jobsub.py --config=${CONFIG} align $RUN
../../jobsub.py --config=${CONFIG} fitter $RUN
else
  echo "No good file found"
fi
#done
