cmake_minimum_required(VERSION 3.6)
project(PDE)

add_executable(PDE src/SweepMethod.c src/PDE.c)

target_link_libraries(PDE m)

