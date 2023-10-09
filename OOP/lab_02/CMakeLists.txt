cmake_minimum_required(VERSION 3.10)
project(Lab02)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(four four.h four.cpp)

add_executable(lab_02 main.cpp four.cpp)


enable_testing()
add_executable(tests02 test.cpp four.cpp)
target_link_libraries(tests02 ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests02)