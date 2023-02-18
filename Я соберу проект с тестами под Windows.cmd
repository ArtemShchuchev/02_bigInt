cmake -S . -B build -D BUILD_TESTING=ON
cd build
cmake --build . --config debug
debug\bigInt.exe
test\debug\tests.exe
ctest -C debug
pause
