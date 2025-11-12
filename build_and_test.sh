#!/bin/bash

mkdir build
cd build

cmake ..
make
cmake --install .

../bin/trumpf_zadanie_rekrutacyjne_test

cd ../test
./test.sh

cd ../build