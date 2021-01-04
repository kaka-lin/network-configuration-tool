#!/bin/bash

mkdir -p src/resources/scripts
cp -r scripts/* src/resources/scripts

qmake
make -j4
