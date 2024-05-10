#!/bin/bash
mkdir build

cd build
cmake ../
cmake --build .

valgrind ./PDE2dBF 5   5   > bf5_5.txt
valgrind ./PDE2dBF 5   25  > bf5_25.txt
./PDE2dBF 25  5   > bf25_5.txt
./PDE2dBF 10  100 > bf10_100.txt
./PDE2dBF 20  400 > bf20_400.txt

valgrind ./PDE2dNZF 5 5 > nzf5_5.txt
valgrind ./PDE2dNZF 5 25 > nzf5_25.txt
valgrind ./PDE2dNZF 25 5 > nzf25_5.txt
./PDE2dNZF 10  100 > nzf10_100.txt
./PDE2dNZF 20  400 > nzf20_400.txt