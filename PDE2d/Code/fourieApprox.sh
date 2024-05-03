#!/bin/bash
gcc main.c 2dFourierApprox.c -lm -o app
gcc pcalculation.c -lm -o nm

./app 6 approx.txt
./nm  6 error.txt

chmod +x printAll.gpi
./printAll.gpi

chmod +x printDependence.gpi
./printDependence.gpi