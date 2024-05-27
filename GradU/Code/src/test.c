#include <stdio.h>
#include <stdlib.h>

#include "graduSolver.h"

double k(double x, double y){
    return 1;
}

double u0(double x, double y) {
    return sin(M_PI * x) * sin(M_PI * y);
}


int main(int argc, char *argv[]){
        double x = 0;
    double y = 0;
    double t = 0;
    int N_x = 4;
    int N = 5;
    double h = 1./(double)(N_x-1);
    double tau = 1./(double)N;
    int G = 1;

    double *Umatrix;
    double *Dmatrix;
    double *Cmatrix;
    double *LastMemory;
    double *bmemory;
    double *U    ; 
    double *Unext; 
    double *netmemory;
    double *fmemory;
    double *net;
    double *umemory;
    double *phimemory;
    double *uijn;

    N_x = 5;
    N = 100;

        if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\nN_x N\n");
        printf("N_x for x and y\n N for time\n");
        return -1;
    }

    N_x = atoi(argv[1]);
    N = atoi(argv[2]);

            if (N < 1 || N_x < 3)
    {
        printf("Wrong parameters, must be:\n");
        printf("N >= 3 M >= 3\n");
        return -1;
    }

    h = 1./(double)(N_x-1);
    tau = 1./(double)N;

    Umatrix   = (double *)malloc(N_x * N_x * sizeof(double));
    Dmatrix   = (double *)malloc(N_x * N_x * sizeof(double));
    U         = (double *)malloc(N_x * N_x * sizeof(double));
    Unext     = (double *)malloc(N_x * N_x * sizeof(double));
    Cmatrix   = (double *)malloc(N_x * N_x * sizeof(double));
    LastMemory = (double *)malloc(N_x * N_x * sizeof(double));
    bmemory = (double *)malloc(N_x * N_x * sizeof(double));
    uijn      = (double *)malloc(N_x * N_x * N * sizeof(double));

    for(int i = 0; i < N_x * N_x; i++){
        Umatrix[i] = 0; 
        Dmatrix[i] = 0; 
        Cmatrix[i] = 0; 
        LastMemory[i] = 0;
        U[i] = 0;
    }
    for(int i = 0; i < N * N_x * N_x; i++)
        uijn[i] = 0;
    

    netmemory = (double *)malloc((N_x + 5) * sizeof(double));
    fmemory   = (double *)malloc((N_x + 5) * sizeof(double));
    net       = (double *)malloc((N_x + 5) * sizeof(double));
    umemory   = (double *)malloc((N_x + 5) * sizeof(double));
    phimemory = (double *)malloc((N_x + 5) * sizeof(double));
    // printf("tau %lf h %lf \n\n", tau, h); 

    for(int i = 1; i < N_x + 1; i++){
        for(int j = 1; j < N_x + 1; j++){
            U[e(i, j, N_x)] = sin(M_PI * (i-1) * h) * sin(M_PI * (j-1) * h);
            // printf("%lf ", U[e(i, j, N_x)]);
        }
    }

    for(int j = 0; j < N_x * N_x; j++) U[j] = j;
    // for(int i = 0; i < N_x * N_x; i++){
    //         U[i] = i * i;
    // }

    // solveByR(1.0, h, tau, Umatrix, U, Dmatrix, Cmatrix, fmemory, umemory, phimemory);
    // multAb_kfunc(tau, h, k, Umatrix, Dmatrix);

    // double error = 0;
    // for(int i = 2; i < N_x; i++){
    //     for(int j = 2; j < N_x; j++){
    //         error += (Dmatrix[e(i, j, N_x)] - U[e(i, j, N_x)]) * (Dmatrix[e(i, j, N_x)] - U[e(i, j, N_x)]);
    //         printf("%lf %lf\n", Dmatrix[e(i, j, N_x)], U[e(i, j, N_x)]);
    //     }
    // }

    // printf("%lf \n", error / (N_x * N_x));

    solvePDEgradu(uijn, N, N_x, k, u0, bmemory, LastMemory, Dmatrix, Cmatrix, fmemory, umemory, phimemory);

    for(int n = 1; n < N + 1; n++){
        for(int i = 1; i < N_x + 1; i++){
            for(int j = 1; j < N_x + 1; j++){
                printf("%lf %lf %lf %lf %lf\n", tau * (n-1), (i-1) * h, (j-1) * h, uijn[c(i, j, n, N_x)], exp(- 2. * M_PI * M_PI * tau * (n-1)) * u0((i-1) * h, (j-1) * h));
            }
        }
        }

    // for(int i = 0; i < N_x * N_x; i++) LastMemory[i] = i * i;
    // multAb_kfunc(tau, h, k, LastMemory, bmemory);
    // for(int i = 0; i < N_x * N_x; i++) printf("%lf ", LastMemory[i] );
    //  printf("\n" );
    //  for(int i = 0; i < N_x * N_x; i++) printf("%lf ", bmemory[i] );
    //  printf("\n" );


free(Umatrix);
free(Dmatrix);
free(Cmatrix);
free(LastMemory);
free(bmemory);
free(U);
free(Unext);
free(netmemory);
free(fmemory);
free(net);
free(umemory);
free(phimemory);
free(uijn);
}