#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
LIB_DIR="$SCRIPT_DIR/pyminr/lib"

mkdir -p "$LIB_DIR"

docker build -t minr_build .
docker run -it --rm -v "$LIB_DIR":/var/pyminr/pyminr/lib minr_build
docker image rm minr_build