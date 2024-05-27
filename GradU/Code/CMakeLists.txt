cmake_minimum_required(VERSION 3.6)
project(gradu)

add_executable(gradu src/2dFourierApprox.c src/graduSolver.c src/tests/test.c)
add_executable(gradu2 src/2dFourierApprox.c src/graduSolver.c src/tests/test2.c)

target_link_libraries(gradu m)
target_link_libraries(gradu2 m)

