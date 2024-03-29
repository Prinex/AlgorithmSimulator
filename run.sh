#!/bin/bash

SFML_WIN=./SFML_Win/
SFML_MAC=./SFML_macOS/
SFML_LINUX=./SFML_Linux/

# unzip SFML library using a separate script
if [ ! -d "$SFML_WIN" ] && [ ! -d "$SFML_MAC" ] && [ ! -d "$SFML_LINUX" ]; then
    chmod 777 ./setupSFML.sh
	./setupSFML.sh
fi

# build the project using another separate script
./build.sh

# building the project
# run the project accordingly to the OS' specified above
cd build

if [[ "$OSTYPE" == "msys"* ]]; then
	cmake --build .
elif [[ "$OSTYPE" == "linux"* ]]; then
	make
elif [[ "$OSTYPE" == "darwin"* ]]; then
    make all
fi

# if running from an executable file
# the font files need to be present where 
# the build file is
cd ..	
cp -r ./design ./build/bin/

# run the project using the executable file
echo "Running..."
if [[ "$OSTYPE" == "msys"* ]]; then
	cd ./build/bin/debug/
	./AlgorithmSimulator.exe
elif [[ "$OSTYPE" == "linux"* ]]; then
	cd ./build/bin/
	./AlgorithmSimulator
elif [[ "$OSTYPE" == "darwin"* ]]; then
    cd ./build/bin/
    ./AlgorithmSimulator
fi

