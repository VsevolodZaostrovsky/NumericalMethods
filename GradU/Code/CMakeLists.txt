cmake_minimum_required(VERSION 3.6)
project(gradu)

add_executable(gradu src/2dFourierApprox.c src/PDE2dSolver.c src/graduSolver.c src/test.c)

target_link_libraries(gradu m)

