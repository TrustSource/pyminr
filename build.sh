#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR="$(pwd)/build/cmake"

if [ -d "$BUILD_DIR" ]; then
  rm -rf $BUILD_DIR/*
else
  mkdir -p $BUILD_DIR
fi

cd $BUILD_DIR

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$SCRIPT_DIR/pyminr" "$SCRIPT_DIR"
make install