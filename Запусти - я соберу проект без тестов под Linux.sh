#!/bin/bash
cmake -S . -B build
cd build
cmake --build . --config debug
./bigInt
exec $SHELL
