#!/bin/bash

# Default action is to build
action="build"

# Check for command-line arguments
if [ "$#" -eq 1 ]; then
  if [ "$1" == "clean" ]; then
    action="clean"
  fi
fi

# Set up build directory
build_dir="build"
mkdir -p $build_dir
cd $build_dir

# Perform the requested action
case $action in
  build)
    cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../arm-none-eabi-gcc.cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build . -- -j 4
    ;;
  clean)
    cmake --build . --target clean
    ;;
  *)
    echo "Unknown action: $action"
    exit 1
    ;;
esac

# Return to the original directory if needed
cd ..