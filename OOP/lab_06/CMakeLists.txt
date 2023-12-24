cmake_minimum_required(VERSION 3.10)
project(Lab06)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_06 
    main.cpp
    observer.cpp
    factory.cpp
    NPC.cpp
    squirrel.cpp
    pegas.cpp
    knight.cpp)

enable_testing()
add_executable(
    tests06
    tests.cpp
    observer.cpp
    factory.cpp
    NPC.cpp
    squirrel.cpp
    pegas.cpp
    knight.cpp)

target_link_libraries(tests06 ${GTEST_LIBRARIES})

add_test(NAME TESTS COMMAND tests06)
