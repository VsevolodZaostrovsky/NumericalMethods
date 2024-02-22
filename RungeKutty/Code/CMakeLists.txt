cmake_minimum_required(VERSION 3.6)
project(RungeKutt)

set(SOURCE_FILES src/Scheme.c src/Useful.c)
add_executable(test1 ${SOURCE_FILES} src/t1.c)
add_executable(test2 ${SOURCE_FILES} src/t2.c)
add_executable(test3 ${SOURCE_FILES} src/t3.c)
add_executable(sol ${SOURCE_FILES} src/solution.c)

target_link_libraries(test1 m)
target_link_libraries(test2 m)
target_link_libraries(test3 m)
target_link_libraries(sol m)

