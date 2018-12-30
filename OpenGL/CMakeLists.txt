cmake_minimum_required(VERSION 3.10)
project(OpenGL C)
find_package(OpenGL REQUIRED)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(OpenGL ${SOURCE_FILES})
target_link_libraries( OpenGL ${OPENGL_LIBRARY} )
