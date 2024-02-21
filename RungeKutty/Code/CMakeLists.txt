cmake_minimum_required(VERSION 3.6)
project(DiffEq)

# add_library(Schemes src/Scheme.c src/Schem.c)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 ")

set(SOURCE_FILES src/Scheme.c src/Useful.c)
add_executable(test1 ${SOURCE_FILES} src/t1.c)
# add_executable(test2 SOURCE_FILES src/t2.c)
# add_executable(test3 SOURCE_FILES src/t3.c)

target_link_libraries(test1 PRIVATE m)