cmake_minimum_required(VERSION 3.6)
project(PDE2dBF)

add_executable(PDE2dBF src/2dFourierApprox.c src/PDE2dSolver.c src/tests/BasicFunctionTest.c)
add_executable(PDE2dNZF src/2dFourierApprox.c src/PDE2dSolver.c src/tests/Nonzerof.c)
add_executable(PDE2dsol src/2dFourierApprox.c src/PDE2dSolver.c src/tests/NonzerofSolution.c)

target_link_libraries(PDE2dBF m)
target_link_libraries(PDE2dNZF m)
target_link_libraries(PDE2dsol m)

