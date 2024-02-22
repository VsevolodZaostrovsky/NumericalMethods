cmake_minimum_required(VERSION 3.6)
project(RungeKutt)

set(SOURCE_FILES src/Scheme.c src/Useful.c)
add_executable(t1 ${SOURCE_FILES} src/t1.c)
add_executable(t2 ${SOURCE_FILES} src/t2.c)
add_executable(t3 ${SOURCE_FILES} src/t3.c)
add_executable(t4 ${SOURCE_FILES} src/t4.c)
add_executable(t5 ${SOURCE_FILES} src/t5.c)
add_executable(sol ${SOURCE_FILES} src/solution.c)

target_link_libraries(t1 m)
target_link_libraries(t2 m)
target_link_libraries(t3 m)
target_link_libraries(t4 m)
target_link_libraries(t5 m)
target_link_libraries(sol m)

