#!/bin/bash

PROJECT_NAME="alsa_wrapper"
SRC_DIR="."
BUILD_DIR="./build"

CXX=g++
CXXFLAGS="-std=c++17 -Wall -Wextra"
LDFLAGS="-lasound"

mkdir -p "$BUILD_DIR"

echo "Compiling project..."
$CXX $CXXFLAGS src/main.cpp -o "$BUILD_DIR/$PROJECT_NAME" $LDFLAGS || exit 1

echo "Build finished!"