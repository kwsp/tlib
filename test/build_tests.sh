#!/bin/bash
cmake -B build
cmake --build build -j
cp ./build/compile_commands.json .
