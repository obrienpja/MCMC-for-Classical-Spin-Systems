#!/usr/bin/env bash

set -e

cd /root
ls
pwd
mkdir build
cd build
cmake ..
make -j 8