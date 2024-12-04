#!/bin/bash

PROJECT_NAME="alsa_wrapper"
SRC_DIR="."
BUILD_DIR="./build"

CXX=g++
CXXFLAGS="-std=c++17 -Wall -Wextra"
LDFLAGS="-lasound"

mkdir -p "$BUILD_DIR"

echo "Compiling project..."
$CXX $CXXFLAGS src/main.cpp src/alsa_manager.cpp src/card.cpp src/device.cpp src/exceptions/alsa_exception.cpp -o "$BUILD_DIR/$PROJECT_NAME" $LDFLAGS || exit 1

echo "Build finished!"