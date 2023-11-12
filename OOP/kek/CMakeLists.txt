cmake_minimum_required(VERSION 3.10)
project(Lab_03)

# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_03 main.cpp square.cpp rectangle.cpp trapeze.cpp array.cpp)


# enable_testing()
# add_executable(tests Testcases.cpp figure.cpp)
# target_link_libraries(tests ${GTEST_LIBRARIES})

# add_test(NAME BASIC COMMAND tests)