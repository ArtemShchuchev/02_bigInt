cmake_minimum_required(VERSION 3.2)
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
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_IMPLIB_RELEASE ${MYLIB_PATH}/Win/Release/SecFun_lib.lib)
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_LOCATION_RELEASE ${MYLIB_PATH}/Win/Release/SecFun_lib.dll)
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_IMPLIB_DEBUG ${MYLIB_PATH}/Win/Debug/SecFun_lib.lib)
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_LOCATION_DEBUG ${MYLIB_PATH}/Win/Debug/SecFun_lib.dll)
# Двух конфигураций ниже - нет, но без добавления этих строк, сыпет Варнингами
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_IMPLIB_MINSIZEREL " ")
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_IMPLIB_RELWITHDEBINFO " ")
# Копирование DLL файла в папку с .exe
add_custom_command(
        TARGET ${OUTPUT_NAME} POST_BUILD    # PRE_BUILD | PRE_LINK | POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${OUTPUT_NAME}>
				$<TARGET_FILE_DIR:${OUTPUT_NAME}>
		COMMAND_EXPAND_LISTS
        COMMENT "-= Copying dll file to work folder =-")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")  # Для Linux
#set(CMAKE_BUILD_TYPE Debug)
#SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_LOCATION_RELEASE "${MYLIB_PATH}/Linux/Release/libSecFun_lib.so")
#SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_LOCATION_DEBUG "${MYLIB_PATH}/Linux/Debug/libSecFun_lib.so")
SET_PROPERTY(TARGET SecFun_lib PROPERTY IMPORTED_LOCATION "${MYLIB_PATH}/Linux/Release/libSecFun_lib.so")
else()
message(FATAL_ERROR "Unknow OS")
endif()

#[[ Тесты Catch2
    Инструкция enable_testing неявно объявляет опцию
    BUILD_TESTING, по умолчанию BUILD_TESTING=OFF.
    Вызывайте `cmake -D BUILD_TESTING=ON projectdir`
    из командной строки, если хотите собирать тесты.
    или расскоментируй строку ниже ]]
#option(BUILD_TESTING "Build the testing tree." ON)
enable_testing()
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

#[[ if (Visual Studio)
	настраиваю в качестве запускаемого проекта
	настройка на стандарт с++17 ]]
if(MSVC)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${OUTPUT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else()
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()
