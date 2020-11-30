#!/usr/bin/env bash

set -e

cd /root
ls
pwd
./install-gtest.sh
mkdir build
cd build
cmake .. -DBoost_NO_BOOST_CMAKE=TRUE
make -j 8
