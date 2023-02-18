#!/bin/bash
cmake -S . -B build -D BUILD_TESTING=ON
cd build
cmake --build . --config debug
./bigInt
./test/tests
ctest -C debug
exec $SHELL
