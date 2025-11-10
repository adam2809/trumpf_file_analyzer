#!/bin/bash

mkdir build
cd build

cmake ..
make
cmake --install .

cd ..