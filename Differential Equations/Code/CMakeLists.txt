cmake_minimum_required(VERSION 3.6)
project(DiffEq)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 ")

set(SOURCE_FILES src/main.c)
add_executable(DiffEq ${SOURCE_FILES})

target_link_libraries(DiffEq PRIVATE m)