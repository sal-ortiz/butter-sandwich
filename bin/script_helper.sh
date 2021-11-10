#!/bin/bash

APP_START_TIME=$(date +%s%N | cut -b1-13)

EXITCODE_SUCCESS=0
EXITCODE_FAILURE=1

USER_PATH="$( pwd )"
ROOT_PATH="$( readlink --canonicalize $(dirname $0)/.. )"

BIN_PATH="$ROOT_PATH/bin"
CFG_PATH="$ROOT_PATH/cfg"
SRC_PATH="$ROOT_PATH/lib"
LOG_PATH="$ROOT_PATH/log"
BUILD_PATH=$ROOT_PATH/build

requires_lib() {
  TARG_LIB=$1
  TARG_STR="#include <$TARG_LIB>"

  RETVAL=$( ack "$TARG_STR" $SRC_PATH | head -n 1 )

  echo -n $RETVAL
}

#configure_environment(){
#  if [ -z $CFG_PATH ]; then   CFG_PATH="$ROOT_PATH/cfg";    fi
#
#  config_file=$CFG_PATH/$( basename ${0}.cfg)
#  if [ -r $config_file ]; then    source "$config_file";    fi
#
#} # function configure_environment()

initialize() {
  if [ ! -d $LOG_PATH ]; then   mkdir $LOG_PATH;    fi
  if [ ! -d $BUILD_PATH ]; then   mkdir $BUILD_PATH;    fi

  if [ -z $NASM_BIN ]; then   NASM_BIN=$(which nasm);   fi
  if [ -z $GCC_BIN ]; then    GCC_BIN=$(which g++);   fi
}

start_time() {
  echo -n ${APP_START_TIME}ms
}
run_time() {
  echo -n "+$(($(date +%s%N | cut -b1-13)-APP_START_TIME))ms"
} # function run_time()


#configure_environment   # autoconfigure.


