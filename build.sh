#!/bin/bash

source /etc/environment
unset LD_LIBRARY_PATH

mkdir -p src/resources/scripts
cp -r scripts/* src/resources/scripts

qmake
make -j4
