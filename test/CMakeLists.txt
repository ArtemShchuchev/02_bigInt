# Тесты Catch2
### add_subdirectory(../Catch2 Catch2-build)
find_package(Catch2 3 REQUIRED)
## 		These tests need their own main
set(TEST_NAME tests) # Даю имя выходному файлу тестов
add_executable(${TEST_NAME}
	test.cpp
	../BigInteger/big_integer.h
	../BigInteger/big_integer.cpp)
target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2)

add_test(NAME MyTest COMMAND ${TEST_NAME})

#[[ if (Visual Studio)
	настройка на стандарт с++17 ]]
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()
