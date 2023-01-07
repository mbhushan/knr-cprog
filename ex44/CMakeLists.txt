cmake_minimum_required(VERSION 3.23)
project(ex44 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex44 main.c)

target_link_libraries(ex44 m)