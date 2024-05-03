#!/bin/bash
echo "Compilation of prog started"

gcc main.c 2dFourierApprox.c -lm -o app
gcc pcalculation.c -lm -o nm

echo "Compilation of prog complited"

echo "Approximation test started"
valgrind ./app 6 approx.txt
valgrind ./nm  6 error.txt
echo ""
echo ""
echo "Approximation test complited"
echo "See the results in the file \"approx.txt\" where:"
echo "columns 1 and 2: (x_i, y_i) - coordinates of the net point"
echo "column 3: the value of the approximation"
echo "column 4: the value of the original function"
echo ""
echo ""
chmod +x printAll.gpi
./printAll.gpi

chmod +x printDependence.gpi
./printDependence.gpi
echo "see the directory \"Images\" for the picture approx with:"
echo "graph of the function and the approximation \"approx.txt.png\""
echo "graph with the conv order \"error.txt.png\""