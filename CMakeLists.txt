cmake_minimum_required(VERSION 3.5)
project(02_bigInt VERSION 1.0 LANGUAGES CXX)

set(OUTPUT_NAME bigInt)
set(HEADERS BigInteger/big_integer.h)
set(SOURCES main.cpp BigInteger/big_integer.cpp)
set(MYLIB_PATH ${PROJECT_SOURCE_DIR}/SecondFunk)
# добавляет путь для подключения #include
#include_directories(${MYLIB_PATH})

add_executable(${OUTPUT_NAME} ${HEADERS} ${SOURCES})
add_library(SecFun_lib SHARED IMPORTED)
target_link_libraries(${OUTPUT_NAME} PRIVATE SecFun_lib)


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")    # Для Windows
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_IMPLIB ${MYLIB_PATH}/SecFun_lib.lib)
# Копирование DLL файла в папку с .exe
add_custom_command(
        TARGET ${OUTPUT_NAME} POST_BUILD    # PRE_BUILD | PRE_LINK | POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${MYLIB_PATH}/SecFun_lib.dll
                $<TARGET_FILE_DIR:${OUTPUT_NAME}>
                COMMENT "-= Copying dll file to work folder =-")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")  # Для Linux
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_LOCATION ${MYLIB_PATH}/libSecFun_lib.so)
else()
message(FATAL_ERROR "Unknow OS")
endif()



# Тесты Catch2
### add_subdirectory(../Catch2 Catch2-build)
find_package(Catch2 3 REQUIRED)
## 		These tests need their own main
add_executable(test test/test.cpp BigInteger/big_integer.h BigInteger/big_integer.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2)

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
