cmake_minimum_required(VERSION 3.8)
project(mpiDemo)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES mpiDemo.c)
add_executable(mpiDemo ${SOURCE_FILES})