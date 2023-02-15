FROM ubuntu:20.04
MAINTAINER Grigory Markin "gmn@eacg.de"

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    git \
    cmake

RUN mkdir -p /var/pyminr/pyminr
WORKDIR /var/pyminr

COPY src src/
COPY include include/
COPY CMakeLists.txt ./
COPY build.sh ./

RUN /bin/chmod 755 build.sh

ENTRYPOINT ./build.sh