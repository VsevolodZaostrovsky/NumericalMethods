cmake_minimum_required(VERSION 3.10)

project(DiffEq)

add_library(libs libs.c)
add_executable(DiffEq src/main.c)