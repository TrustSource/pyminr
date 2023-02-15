#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR="$(pwd)/build/lib"
SETUP_SCRIPT="$SCRIPT_DIR/setup.py"

if [ -d "$BUILD_DIR" ]; then
  rm -rf $BUILD_DIR/*
fi

python3 "$SETUP_SCRIPT" bdist_wheel -p win_amd64 && rm -rf $BUILD_DIR/*
python3 "$SETUP_SCRIPT" bdist_wheel -p manylinux2014_x86_64 && rm -rf $BUILD_DIR/*
python3 "$SETUP_SCRIPT" bdist_wheel -p macosx_11_0_universal2 && rm -rf $BUILD_DIR/*