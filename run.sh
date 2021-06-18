#!/bin/sh

cd build
make
cd ..
cd ./bin
echo "Running..."

./AlgorithmSimulator.exe