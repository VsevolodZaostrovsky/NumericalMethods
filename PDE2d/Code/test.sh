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

./PDE2dNZF 100 100 > nzf100_100.txt
./PDE2dNZF 150 150 > nzf100_100.txt
./PDE2dNZF 200 200 > nzf200_200.txt
./PDE2dNZF 250 250 > nzf200_200.txt


./PDE2dNZF 10 100 > nzf10_100.txt
./PDE2dNZF 20 400 > nzf20_400.txt
./PDE2dNZF 30 900 > nzf30_900.txt

./PDE2dsol 5 25   > nzf_sol5_25.txt
./PDE2dsol 30 900 > nzf_sol30_900.txt