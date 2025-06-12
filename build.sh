#!/bin/bash

# Basic build and clean functionality

if [[ "$1" == "build" || "$1" == "--build" || "$1" == "-build" || "$1" == "" ]]; then


	if [ -d "build/" ]; then
		echo "Deleting build folder"
		rm -rf build
	fi
	
	echo "Making new build folder"
	mkdir build
	echo "cd build"
	cd build 
	echo "Running cmake"
	cmake ..
	cmake --build .
	
elif [[ "$1" == "clean" || "$1" == "--clean" || "$1" == "-clean" || "$1" == "-c" || "$1" == "--c" ]]; then

	if [ -d "build/" ]; then
		echo "Deleting build folder"
		rm -rf build
	else
		echo "Already clean"
	fi
  
else
	echo "Dunno what happened"
	exit 1
  
fi

exit 0


