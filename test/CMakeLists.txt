# Тесты Catch2
cmake_minimum_required(VERSION 3.5)
project(TestLib)
### add_subdirectory(../Catch2 Catch2-build)
find_package(Catch2 3 REQUIRED)
## 		These tests need their own main
set(TEST_NAME tests) # Даю имя тестам
add_executable(${TEST_NAME}
	test.cpp
	../BigInteger/big_integer.h
	../BigInteger/big_integer.cpp)
target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2)

add_test(NAME MyTest COMMAND ${TEST_NAME})

# if (Visual Studio)
# настраиваю в качестве запускаемого проекта
# настройка на стандарт с++17
if(MSVC)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TEST_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()
