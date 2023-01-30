# Тесты Catch2
### add_subdirectory(../Catch2 Catch2-build)
find_package(Catch2 3 REQUIRED)
## 		These tests need their own main
add_executable(test test.cpp ../BigInteger/big_integer.h ../BigInteger/big_integer.cpp)
target_link_libraries(test PRIVATE Catch2::Catch2)

enable_testing()
add_test(NAME MyAwesomeTest COMMAND test)

# if (Visual Studio)
# настраиваю в качестве запускаемого проекта
# настройка на стандарт с++17
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()
