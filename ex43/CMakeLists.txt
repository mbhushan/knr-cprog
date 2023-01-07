cmake_minimum_required(VERSION 3.23)
project(ex43 C)

set(CMAKE_C_STANDARD 99)
add_executable(ex43 main.c)

target_link_libraries(ex43 m)
