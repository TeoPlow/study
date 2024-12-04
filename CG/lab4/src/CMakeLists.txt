cmake_minimum_required(VERSION 3.10)
project(Lab4)

# Найти OpenGL
find_package(OpenGL REQUIRED)

# Найти SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Найти GLM
find_package(glm REQUIRED)

# Указать стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавить исполняемый файл
add_executable(Lab4 main.cpp)

# Указать директории для заголовков
target_include_directories(Lab4 PRIVATE 
    ${OPENGL_INCLUDE_DIRS} 
    ${GLM_INCLUDE_DIRS}  # Добавлен GLM
    /usr/include
)

# Связывание библиотек
target_link_libraries(Lab4 
    OpenGL::GL 
    GLEW 
    GLU 
    sfml-system 
    sfml-window 
    sfml-graphics
)
