#include <stdio.h>
#include <stdlib.h>

#include "Solution.h"

double u(double x, double y)
{
    return x * (1 - x) * y * (1 - y);
}
 
void PrintMatrix(double * Matrix, int N) {
    for(int k = 0; k < N*N; k++) {
        if (k % N == 0) { printf("\n"); }
        printf("%10.5lf ", (Matrix + k)[0]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int N = 6;
    double x = 0;
    double y = 0;

    double * Umatrix;
    double * Dmatrix;
    double * Cmatrix;

    double * netmemory;
    double * fmemory;
    double * net;
    double * umemory;
    double * phimemory;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("x y \n");
        return -1;
    }

    x = atof(argv[1]); // левая
    y = atof(argv[2]);

    Umatrix = (double *)malloc((N) * (N) * sizeof(double));
    Dmatrix = (double *)malloc((N) * (N) * sizeof(double));
    Cmatrix = (double *)malloc((N) * (N) * sizeof(double));

    netmemory = (double *)malloc((N + 5) * sizeof(double));
    fmemory = (double *)malloc((N + 5) * sizeof(double));
    net = (double *)malloc((N + 5) * sizeof(double));
    umemory = (double *)malloc((N + 5) * sizeof(double));
    phimemory = (double *)malloc((N + 5) * sizeof(double));

    GenerateNet(net, N - 1);
    printf("\n Umatrix: \n");
    FullUMatrix(Umatrix, N, net, u);
    PrintMatrix(Umatrix, N);

    printf("\n Dmatrix: \n");
    FullDMatrix(Dmatrix, Umatrix, N, umemory, phimemory);
    PrintMatrix(Dmatrix, N);

    printf("\n Cmatrix: \n");
    FullCMatrix(Dmatrix, Cmatrix, N, fmemory, umemory, phimemory);
    PrintMatrix(Cmatrix, N);

//    printf("\n Cmatrix: \n");
//    PrintMatrix(Cmatrix, N);

    printf("net:\n");

    for(int h = 0; h < N; ++h) {
        printf("%lf ", net[h]);
    }
    printf("\n"); 
    for(int h = 1; h < N; h++) {
        printf("%lf ", FourierCompute(Cmatrix + 2*N, N, net[h]));
    }
    printf("\n"); 

    
/*    for(int h = 1; h < N; h++) {
        printf("%lf ", FourierCompute(Dmatrix + 2*N, N, net[h]));
    }
    printf("\n"); */

/*
    printf("\n Umatrix: \n");
    PrintMatrix(Umatrix, N);
    printf("\n Dmatrix: \n");
    PrintMatrix(Dmatrix, N);
    printf("\n Cmatrix: \n");
    PrintMatrix(Cmatrix, N);
*/
    printf("Answer: %10.10lf \n\n", Calc2DFourier(Cmatrix, N, x, y));

    free(Umatrix);
    free(Dmatrix);
    free(Cmatrix);

    free(netmemory);
    free(fmemory);
    free(net);
    free(umemory);
    free(phimemory);

    return 0;
}