#!/bin/bash

mkdir -p game/build
cd game/build

cmake ..
make

if [ $? -eq 0 ]; then
    echo "Build successful, running the game..."
    ./game
else
    echo "Build failed."
fi

