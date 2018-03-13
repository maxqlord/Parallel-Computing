cmake_minimum_required(VERSION 3.9)
project(RayTracing C)

set(CMAKE_C_STANDARD 99)

add_executable(RayTracing main.c initRay.c shadow.c movie.c)