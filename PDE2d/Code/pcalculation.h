#include <stdio.h>
#include <stdlib.h>
#include "2dFourierApprox.c"

double u(double x, double y);

double mod(double x);

double UniNorm01(double (*f)(double, double), double (*u)(double, double), int N);

void WriteSkrypt(int N, char *testfilename, FILE *out);

void WriteNorm(double *lognorms, double *loghs, int N, FILE *out);