#!/bin/bash
cd ..
mkdir build

cd build
cmake ../
cmake --build .

rm *.txt

./PDE_bb_r 100 100 > bbr_h100t100.txt
./PDE_bb 100 100 > bb_h100t100.txt