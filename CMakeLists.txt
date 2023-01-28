cmake_minimum_required(VERSION 3.5)
project(02_bigInt VERSION 1.0 LANGUAGES CXX)

set(OUTPUT_NAME bigInt)
set(HEADERS BigInteger/big_integer.h)
set(SOURCES main.cpp BigInteger/big_integer.cpp)


add_library(SecFun_lib SHARED IMPORTED)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")    # Для Windows
set(MYLIB_PATH ${PROJECT_SOURCE_DIR}/SecondFunk)
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_IMPLIB ${MYLIB_PATH}/SecFun_lib.lib)

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")  # Для Linux
set(MYLIB_PATH ${PROJECT_SOURCE_DIR}/exeProg)
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_LOCATION ${MYLIB_PATH}/libSecFun_lib.so)

else()
message(FATAL_ERROR "Unknow OS")
endif()

# добавляет путь для подключения #include
#include_directories(${MYLIB_PATH})

set(OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/exeProg)
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")

add_executable(${OUTPUT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${OUTPUT_NAME} PRIVATE SecFun_lib)


# if (Visual Studio)
# настраиваю в качестве запускаемого проекта
# настройка на стандарт с++17
if(MSVC)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${OUTPUT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()


### add_subdirectory(../Catch2 Catch2-build)
find_package(Catch2 3 REQUIRED)
## 		These tests need their own main
add_executable(test test/test.cpp BigInteger/big_integer.h BigInteger/big_integer.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2)
