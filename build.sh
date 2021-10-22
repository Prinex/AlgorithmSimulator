#!/bin/bash

echo "Building the project..."
rm -rf build
rm -rf bin
rm -rf lib

mkdir build
cd build
# build the project accordingly to the OS' specified above
if [[ "$OSTYPE" == "msys"* ]]; then
	cmake .. -G "Visual Studio 16 2019"
elif [[ "$OSTYPE" == "linux"* ]]; then
	cmake .. -G "Unix Makefiles"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_OSX_ARCHITECTURES=arm64 ..
else
	echo "Invalid option"
fi
