cmake_minimum_required(VERSION 3.6)
project(2orderDE)

set(SOURCE_FILES src/FourierMethod.c)
add_executable(DiffEqFourier ${SOURCE_FILES} src/DiffEqFourier.c)
add_executable(DiffEqSweep ${SOURCE_FILES} src/SweepMethod.c src/DiffEqSweep.c)

target_link_libraries(DiffEqFourier m)
target_link_libraries(DiffEqSweep m)

