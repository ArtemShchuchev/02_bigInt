cmake_minimum_required(VERSION 3.5)
project(02_bigInt VERSION 1.0 LANGUAGES CXX)
add_executable(bigInt
	main.cpp
	SecondFunk/SecondaryFunction.h SecondFunk/SecondaryFunction.cpp
	BigInteger/big_integer.h BigInteger/big_integer.cpp)



# if (Visual Studio)
# настраиваю в качестве запускаемого проекта
# настройка на стандарт с++17
if(MSVC)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT bigInt)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()




### add_subdirectory(../Catch2 Catch2-build)
find_package(Catch2 3 REQUIRED)
## 		These tests need their own main
add_executable(test test/test.cpp BigInteger/big_integer.h BigInteger/big_integer.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2)
