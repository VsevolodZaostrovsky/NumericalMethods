#include "2dFourierApprox.h"
#include <math.h>


#define c(i, j, n, N) ((n - 1) * N * N + (j - 1) * N + i - 1)

void solvePDE2d(double (*u0)(double, double),
                double (*f)(double, double, double), 
                int N_x, int N,
                // все массивы ниже - память, необходимая программе 
                double * uijn, 
                double *Umatrix, double *Dmatrix, double *Cmatrix,
                double *net, double *fmemory, double *netmemory, double *umemory, double *phimemory);


// следующие функции внутренние:
void CFromDandLayer(double * C, double * D, double * LastLayer, double h, double tau);

void Dfromf(double (*f)(double, double, double), double h, double tau, int G,
                           double *Umatrix, double *Dmatrix, double *Cmatrix,
                           double *fmemory, double *umemory, double *phimemory);