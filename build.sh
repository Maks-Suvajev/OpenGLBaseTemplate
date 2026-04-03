#!/bin/bash

# Basic build and clean functionality



if [[ "$1" == "clean" || "$1" == "--clean" || "$1" == "-clean" || "$1" == "-c" || "$1" == "--c" ]]; then

	echo "Performing clean build"
	rm -rf build
	rm -rf bin

	echo "Making new build folder"
	mkdir build
fi

echo "cd build"
cd build
echo "Running cmake"
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build .

exit 0


