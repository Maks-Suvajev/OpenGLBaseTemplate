#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"

if [[ "$1" == "clean" || "$1" == "--clean" || "$1" == "-clean" || "$1" == "-c" || "$1" == "--c" ]]; then
    echo "Performing clean build"
    rm -rf "$BUILD_DIR"
    rm -rf "$SCRIPT_DIR/bin"
fi

mkdir -p "$BUILD_DIR"

cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
                                       -DCMAKE_BUILD_TYPE=Debug \
                                        -DCMAKE_VERBOSE_MAKEFILE=ON -G "MinGW Makefiles" \
                                        -DCMAKE_PREFIX_PATH="C:/Qt/6.10.2/mingw_64"\

cmake --build "$BUILD_DIR" -- -j$(nproc)

exit 0