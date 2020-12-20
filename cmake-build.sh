#!/bin/bash

mkdir -p src/resources/scripts
cp -r scripts/* src/resources/scripts

mkdir -p build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
