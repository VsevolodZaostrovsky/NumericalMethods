#!/bin/bash
cd ..
mkdir build

cd build
cmake ../
cmake --build .

valgrind ./PDE 100 100 > h100t100.txt
valgrind ./PDE 200 200 > h200t200.txt
valgrind ./PDE 300 300 > h300t300.txt
valgrind ./PDE 400 400 > h400t400.txt
valgrind ./PDE 500 500 > h500t500.txt

valgrind ./PDE 10 100 > h10t100.txt
valgrind ./PDE 20 400 > h20t400.txt
valgrind ./PDE 30 900 > h30t900.txt