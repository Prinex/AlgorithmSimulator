#!/bin/sh

echo "Choose a build option: "
echo "1. Build the project using VS 16 2019 x64"
echo "2. Build the project using MinGW Makefiles on either Linux or Windows."
echo "2. Build the project using Unix Makefiles."

read OPTION

echo "Building the project..."
rm -rf build
rm -rf bin
rm -rf lib

mkdir build
cd build

if [ $OPTION == 1 ]
then
	cmake .. -G "Visual Studio 16 2019"
elif [ $OPTION == 2 ]
then
	cmake .. -G "MinGW Makefiles"
elif [ $OPTION == 3 ]
then
	cmake .. -G "Unix Makefiles"
else
	echo "Invalid option"
fi