#!/usr/bin/env bash

set -e

cd /root
ls
pwd
mkdir build
cd build
cmake .. -DBoost_NO_BOOST_CMAKE=TRUE
make -j 8