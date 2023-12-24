cmake_minimum_required(VERSION 3.10)
project(Lab07)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab_07
    main.cpp
    observer.cpp
    factory.cpp
    NPC.cpp
    squirrel.cpp
    pegas.cpp
    knight.cpp)
