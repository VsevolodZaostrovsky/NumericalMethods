cmake_minimum_required(VERSION 3.6)
project(PDE)

add_executable(PDE ../src/SweepMethod.c src/PDE.c)
add_executable(PDE_bb ../src/SweepMethod.c src/PDEBadType.c)
add_executable(PDE_bb_r ../src/SweepMethod.c src/PDEBadTypeR.c)

target_link_libraries(PDE m)
target_link_libraries(PDE_bb m)
target_link_libraries(PDE_bb_r m)

