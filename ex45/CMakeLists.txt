cmake_minimum_required(VERSION 3.23)
project(ex45 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex45 main.c)

target_link_libraries(ex45 m)