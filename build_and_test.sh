#!/bin/bash

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Debug ..
make
cmake --install .

../bin/trumpf_zadanie_rekrutacyjne_test

cd ../test
./test.sh

cd ../build