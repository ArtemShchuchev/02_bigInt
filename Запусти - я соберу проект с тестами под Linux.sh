cmake -S . -B build -D BUILD_TESTING=ON
cd build
cmake --build . --config debug
./bigInt
./tests
ctest -C debug
pause
