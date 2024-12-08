#!/bin/bash

mkdir -p gameEngine/build
cd gameEngine/build

cmake ..
make

if [ $? -eq 0 ]; then
    echo "Build successful, running tests..."
    ./tests
else
    echo "Build failed."
fi

