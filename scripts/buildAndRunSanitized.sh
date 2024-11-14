#!/bin/bash

mkdir -p game/build
cd game/build

cmake .. -DCMAKE_CXX_FLAGS="-fsanitize=address" -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"
make

if [ $? -eq 0 ]; then
    echo "Build successful with AddressSanitizer, running the game..."
    export MallocNanoZone=0  # Disable nano allocator on macOS for ASan compatibility
    ./game
else
    echo "Build failed."
fi

