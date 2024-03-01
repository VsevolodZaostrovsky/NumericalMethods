cmake_minimum_required(VERSION 3.6)
project(DiffEq)

SET(MYCOMPILE_FLAGS "-W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align \
-Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors \
-Wunused -Wuninitialized \
--param inline-unit-growth=1000000 --param max-inline-insns-single=10000000 \
--param large-function-growth=10000000 -O3")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MYCOMPILE_FLAGS}")

set(SOURCE_FILES src/main.c)
add_executable(DiffEq ${SOURCE_FILES})

target_link_libraries(DiffEq PRIVATE m)