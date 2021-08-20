#!/bin/sh

# building the project
# run the project accordingly to the OS' specified above
cd build

if [[ $(find ./build/bin/Debug/ -name 'AlgorithmSimulator.exe') = AlgorithmSimulator.exe ]]; then
	cd ./build/bin/
	./AlgorithmSimulator.exe
elif [[ "$OSTYPE" == "msys"* ]]; then
	cmake --build .
elif [[ "$OSTYPE" == "linux"* ]]; then
	make
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
	./AlgorithmSimulator.exe
fi

