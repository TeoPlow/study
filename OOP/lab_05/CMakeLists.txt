cmake_minimum_required(VERSION 3.10)
project(Lab_03)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/googletest)

add_executable(main main.cpp)
add_executable(test tests.cpp)

target_link_libraries(test PRIVATE GTest::gtest_main)
include(GoogleTest)

gtest_discover_tests(test)