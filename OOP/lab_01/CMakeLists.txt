cmake_minimum_required(VERSION 3.10)
project(gtest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp palindrom.cpp)


enable_testing()
add_executable(Tests Tests.cpp  palindrom.cpp)
target_link_libraries(Tests ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND Tests)