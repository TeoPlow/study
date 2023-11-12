cmake_minimum_required(VERSION 3.10)
project(Lab_03)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
add_subdirectory(third_party/googletest)
 
add_executable(figure main.cpp trapeze.cpp square.cpp rectangle.cpp array.cpp)
add_executable(tests tests.cpp trapeze.cpp square.cpp rectangle.cpp array.cpp)
 
target_link_libraries(tests PRIVATE GTest::gtest_main)
include(GoogleTest)
 

gtest_discover_tests(tests)