#include "PDE2dSolver.h"


void Dfromf(double (*f)(double, double, double), double h, double tau, int G,
                           double *Umatrix, double *Dmatrix, double *Cmatrix,
                           double *fmemory, double *netmemory, double *umemory, double *phimemory){
    

    
    int N_x = (int)(1. / (h)) + 1;

    // GenerateNet(net, N - 1);

    for (int i = 1; i < N_x + 1; ++i)
    {
        for (int j = 1; j < N_x + 1; ++j)
        {
            Umatrix[e(i, j, N_x)] = f(tau * (double)(G), h * (double)(i-1) , h * (double)(j-1));
        }
    }
    // printf("U:\n");
    // for (int i = 1; i < N + 1; ++i)
    // {
    //     for (int j = 1; j < N + 1; ++j)
    //     {
    //        printf("%lf ", Umatrix[e(i, j, N)]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    FullDMatrix(Dmatrix, Umatrix, N_x, umemory, phimemory);
    FullCMatrix(Dmatrix, Cmatrix, N_x, fmemory, umemory, phimemory);
}

void CFromDandLayer(double * C, double * D, double * LastLayer, double h, double tau) 
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
                C[e(n, m, N_x)] = (D[e(n, m, N_x)] + LastLayer[e(n, m, N_x)] / tau) / (4 / (h * h) * (sinPih_n * sinPih_n + sinPih_m * sinPih_m) + 1. / tau );
            }
        }
    }
}

// void FullZeroLayer(double * uijn, double (*u0)(double, double), double h) 
// {
//     int N = (int)(1. / (h)) + 1;
//     // printf("h=%lf N-x=%d\n", h, N);

//     for (int i = 1; i < N + 1; ++i)
//     {
//         for (int j = 1; j < N + 1; ++j)
//         {
//             if (i == 1 || i == N || j == 1 || j == N)
//                 uijn[e(i, j, N)] = 0;
//             else {
//                 uijn[e(i, j, N)] = u0((double)(i-1) * h, (double)(j-1) * h);
//             }
//         }
//     }
// }

// void printMatrix(double * matrix, int N){
//     for(int i = 1; i < N + 1; i++){
//             for(int j = 1; j < N + 1; j++){
//                 printf("%lf ", matrix[e(i, j, N)]);
//             }
//             printf("\n");
//         }
//         printf("\n");
// }

void solvePDE2d(double (*u0)(double, double),
                double (*f)(double, double, double), 
                int N_x, int N,
                // все массивы ниже - память, необходимая программе 
                double * uijn, // сюда будут записаны коэффициенты фурье решения
                double *Umatrix, double *Dmatrix, double *Cmatrix,
                double *net, double *fmemory, double *netmemory, double *umemory, double *phimemory)
                {
    double h = 1./(double)(N_x-1);
    double tau = 1./(double)N;
    
    FindFourierCoefs(Umatrix, Dmatrix, uijn, N_x, fmemory, net, u0, netmemory, umemory, phimemory);
    
    
    for (int G = 1; G < N; G++)
    {
        // printf("D from f: \n");
        Dfromf(f, h, tau, G, Umatrix, Dmatrix, Cmatrix, fmemory, netmemory, umemory, phimemory);
        // printMatrix(Cmatrix, N_x);
        // printf("Answer %d layer: \n", G);
        CFromDandLayer(uijn + G * N_x * N_x, Cmatrix, uijn + (G - 1) * N_x * N_x, h, tau);
        // printMatrix(uijn + G * N_x * N_x, N_x);

                }
        }
