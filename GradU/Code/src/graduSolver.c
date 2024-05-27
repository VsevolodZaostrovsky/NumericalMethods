#include "graduSolver.h"
#include <stdio.h>



void multAb_kfunc(double tau, double h, double (*k)(double, double), double * b, double * ans)
{
    int N_x = (int)(1. / (h)) + 1;
    double h2rev  = 1. / (h * h);
    double taurev = 1. / tau;

    for(int i = 1; i < N_x + 1; i++) {
        for(int j = 1; j < N_x + 1; j++){
            if (i == 1 || i == N_x || j == 1 || j == N_x) ans[e(i, j, N_x)] = 0 * b[e(i, j, N_x)];
            else if (j == 1) ans[e(i, j, N_x)] = b[e(i, j, N_x)] * (
                    taurev + (
                        k((i-1) * h + h * 0.5, (j-1) * h) 
                      + k((i-1) * h - h * 0.5, (j-1) * h)
                      + k((i-1) * h          , (j-1) * h + h * 0.5)
                      + k((i-1) * h          , (j-1) * h - h * 0.5)
                        ) * h2rev
                    ) 
                    -(
                        b[e(i + 1, j    , N_x)] * k((i-1) * h + h * 0.5, (j-1) * h) 
                      + b[e(i - 1, j    , N_x)] * k((i-1) * h - h * 0.5, (j-1) * h)
                      + b[e(i    , j + 1, N_x)] * k((i-1) * h          , (j-1) * h + h * 0.5)
                    //   + b[e(i    , j - 1, N_x)] * k((i-1) * h          , (j-1) * h - h * 0.5)
                    ) * h2rev;
            else if (j == N_x ) ans[e(i, j, N_x)] = b[e(i, j, N_x)] * (
                    taurev + (
                        k((i-1) * h + h * 0.5, (j-1) * h) 
                      + k((i-1) * h - h * 0.5, (j-1) * h)
                      + k((i-1) * h          , (j-1) * h + h * 0.5)
                      + k((i-1) * h          , (j-1) * h - h * 0.5)
                        ) * h2rev
                    ) 
                    -(
                        b[e(i + 1, j    , N_x)] * k((i-1) * h + h * 0.5, (j-1) * h) 
                      + b[e(i - 1, j    , N_x)] * k((i-1) * h - h * 0.5, (j-1) * h)
                    //   + b[e(i    , j + 1, N_x)] * k((i-1) * h          , (j-1) * h + h * 0.5)
                      + b[e(i    , j - 1, N_x)] * k((i-1) * h          , (j-1) * h - h * 0.5)
                    ) * h2rev;
            else 
                ans[e(i, j, N_x)] = b[e(i, j, N_x)] * (
                    taurev + (
                        k((i-1) * h + h * 0.5, (j-1) * h) 
                      + k((i-1) * h - h * 0.5, (j-1) * h)
                      + k((i-1) * h          , (j-1) * h + h * 0.5)
                      + k((i-1) * h          , (j-1) * h - h * 0.5)
                        ) * h2rev
                    ) 
                    -(
                        b[e(i + 1, j    , N_x)] * k((i-1) * h + h * 0.5, (j-1) * h) 
                      + b[e(i - 1, j    , N_x)] * k((i-1) * h - h * 0.5, (j-1) * h)
                      + b[e(i    , j + 1, N_x)] * k((i-1) * h          , (j-1) * h + h * 0.5)
                      + b[e(i    , j - 1, N_x)] * k((i-1) * h          , (j-1) * h - h * 0.5)
                    ) * h2rev;
        }
    }
}

void DfromRight(double * Umatrix, double h, double tau,  double *Dmatrix, double *Cmatrix,
                           double *fmemory, double *umemory, double *phimemory){
    int N_x = (int)(1. / (h)) + 1;
    FullDMatrix(Cmatrix, Umatrix, N_x, umemory, phimemory);
    FullCMatrix(Cmatrix, Dmatrix, N_x, fmemory, umemory, phimemory);
    // printf("Fourier:\n"); for(int i = 0; i < N_x * N_x; i++) printf("%lf ", Dmatrix[i]); printf("\n");
}

void CFromD(double * C, double * D, double h, double tau) 
{
    int N_x = (int)(1. / (h)) + 1;
    double sinPih_n = 0;
    double sinPih_m = 0;

    for (int n = 1; n < N_x + 1; ++n)
    {
        for (int m = 1; m < N_x + 1; ++m)
        {
            if (n == 1 || n == N_x || m == 1 || m == N_x)
                C[e(n, m, N_x)] = 0;
            else {
                sinPih_n = sin(M_PI * (double)(n-1) * h * 0.5);
                sinPih_m = sin(M_PI * (double)(m-1) * h * 0.5);
                // C[e(n, m, N)] = D[e(n, m, N)] / (4 * (sinPih_n * sinPih_n + sinPih_m * sinPih_m) / (h * h) + 1. / tau);
                C[e(n, m, N_x)] = D[e(n, m, N_x)] / (4 / (h * h) * (sinPih_n * sinPih_n + sinPih_m * sinPih_m) + 1. / tau );
            }
        }
    }
}

void solveByR(double k, double h, double tau, // параметры, определяющие систему, которую нужно решить
              double * u,                     // сюда будет записан ответ
              double *RightPart,              // массив, содержащий правую часть уравнения
              double *Dmatrix, double *Cmatrix, double *fmemory, double *umemory, 
              double *phimemory){
                int N_x = (int)(1. / (h)) + 1;
                DfromRight(RightPart, h, tau, Dmatrix, Cmatrix, fmemory, umemory, phimemory);
                CFromD(Cmatrix, Dmatrix, h, tau); 
                // printf("RightPart: \n");for(int i = 0; i < N_x * N_x; i++) printf("%lf ", RightPart[i]); printf("\n");
                CalcFourierMatrix(u, Cmatrix, N_x);
                // printf("Ans: \n");for(int i = 0; i < N_x * N_x; i++) printf("%lf ", u[i]); printf("\n");
              }

void UnextFromU(double * Unext, double * U, double tau, double h, double (*k)(double, double), 
    double * bmemory, double * LastMemory,
    double *Dmatrix, double *Cmatrix, double *fmemory, double *umemory, double *phimemory){
        int N_x = (int)(1. / (h)) + 1;
        double k_const = (k(0.25, 0.25) + k(0.5, 0.5) + k(0.75, 0.75)) / 3.;
        double theta = 0.9;
        double error = 10;
        int iterations = 0;

        while(iterations < 1000 && error > 0.000001){
        error = 0;
        multAb_kfunc(tau, h, k, LastMemory, bmemory);
        for(int i = 0; i < N_x * N_x; i++) bmemory[i] = U[i] / tau - bmemory[i];

        solveByR(k_const, h, tau, Unext, bmemory, Dmatrix, Cmatrix, fmemory, umemory, phimemory);

        for(int i = 0; i < N_x * N_x; i++) {
            Unext[i] = LastMemory[i] + theta * Unext[i];
            LastMemory[i] = Unext[i];
        }
        multAb_kfunc(tau, h, k, LastMemory, bmemory);
        
        for(int i = 0; i < N_x * N_x; i++) error += (U[i] / tau - bmemory[i]) * (U[i] / tau - bmemory[i]);
        
        iterations++;
        // printf("iter %d error %lf\n", iterations, error);
        }
        // if (iterations > 10) printf("iter %d error %lf\n", iterations, error);
    }

void solvePDEgradu(double * uijn, int N, int N_x, double (*k)(double, double), double (*u0)(double, double), double * bmemory, double * LastMemory,
    double *Dmatrix, double *Cmatrix, double *fmemory, double *umemory, double *phimemory)
    {
    double h = 1./(double)(N_x-1);
    double tau = 1./(double)N;
    // printf("\ntotal %d\n", N);
    
    for(int i = 1; i < N_x + 1; i++){
        for(int j = 1; j < N_x + 1; j++){
            uijn[e(i, j, N_x)] = u0((i - 1) * h, (j - 1) * h);
        }
    }

    for (int G = 1; G < N; G++)
    {
        // printf("ok iter %d\n", G);
        UnextFromU(uijn + G * N_x * N_x, uijn + (G - 1) * N_x * N_x, tau, h, k, bmemory, LastMemory, Dmatrix, Cmatrix, fmemory, umemory, phimemory);
    }
    }
