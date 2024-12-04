cmake_minimum_required(VERSION 3.10)

# Название проекта
project(Lab5 LANGUAGES CXX)

# Установите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основной исполняемый файл
add_executable(Lab5 main.cpp)

# Включить отладочные сообщения при необходимости
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Build type: Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
    message("Build type: Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

# Добавление флагов компилятора (опционально, в зависимости от платформы)
if(MSVC)
    target_compile_options(Lab5 PRIVATE /W4)
else()
    target_compile_options(Lab5 PRIVATE -Wall -Wextra -pedantic)
endif()

# Убедитесь, что библиотеки линкаются правильно (если используются дополнительные зависимости)
target_link_libraries(Lab5 PRIVATE)

# Сообщение об успешной настройке
message("Configuration done. Ready to build Lab5.")
