#include <stdio.h>
#include <stdlib.h>

void WriteTriangulation(int N, double Lx, double Ly, FILE *out);

double Integrate(int N, double (*f)(double, double));