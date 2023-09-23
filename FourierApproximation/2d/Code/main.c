#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "Solution.h"

double u(double x, double y)
{
    return x * (1 - x) * y * (1 - y);
}

void PrintMatrix(double *Matrix, int N)
{
    for (int k = 0; k < N * N; k++)
    {
        if (k % N == 0)
        {
            printf("\n");
        }
        printf("%20.15lf ", (Matrix + k)[0]);
    }
    printf("\n");
}

void WriteSkrypt(int N, char *testfilename, FILE *out)
{

    fprintf(out, "#! /usr/bin/gnuplot -persist\n");
    fprintf(out, "set terminal png size 1000,1000 enhanced font \"Helvetica Bold, 20\"\n");
    fprintf(out, "set output \"%s.png\"\n\n", testfilename);

    fprintf(out, "set style line 1 lt 1 linecolor rgb \"red\" lw 1 pt 1\n");
    fprintf(out, "set style line 2 lt 1 linecolor rgb \"blue\" lw 1 pt 1\n");

    //    fprintf(out, "set yrange [0:5]");
    fprintf(out, "set xrange [0:1]\n");

    fprintf(out, "set title \"%s - %d knots \"\n", testfilename, N);

    fprintf(out, "set grid\n\n");

    fprintf(out, "splot  \"%s\" using 1:2:3 ls 1 title \"Interpolation Fourier Row\", ", testfilename);
    fprintf(out, "\"%s\" using 1:2:4 ls 2 title \"Original function\", ", testfilename);
}

void WriteResult(double *net, double *Cmatrix, int N, double (*u)(double, double), FILE *out)
{
    double xi, yi;
    double xi1, yi1;
    double xi2, yi2;

    for (int i = 1; i < N - 1; ++i)
    {
        for (int j = 1; j < N - 1; ++j)
        {
            xi = net[i];
            yi = net[j];
            fprintf(out, "%20.15lf %20.15lf %20.15lf %20.15lf \n", xi, yi, Calc2DFourier(Cmatrix, N, xi, yi), u(xi, yi));
            xi1 = 2 * xi / 3 + net[i + 1] / 3;
            yi1 = 2 * yi / 3 + net[j + 1] / 3;
            fprintf(out, "%20.15lf %20.15lf %20.15lf %20.15lf \n", xi1, yi1, Calc2DFourier(Cmatrix, N, xi1, yi1), u(xi1, yi1));
            xi2 = xi / 3 + 2 * net[i + 1] / 3;
            yi2 = xi / 3 + 2 * net[j + 1] / 3;
            fprintf(out, "%20.15lf %20.15lf %20.15lf %20.15lf \n", xi2, yi2, Calc2DFourier(Cmatrix, N, xi1, yi2), u(xi1, yi2));
        }
    }
}

int main(int argc, char *argv[])
{
    int N = 100;
    FILE *fp;
    FILE *sk;

    double *Umatrix;
    double *Dmatrix;
    double *Cmatrix;

    double *netmemory;
    double *fmemory;
    double *net;
    double *umemory;
    double *phimemory;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("N filename \n");
        return -1;
    }

    N = atoi(argv[1]);
    if ((fp = fopen(argv[2], "w")) == NULL) // имя файла, в который нужно записать ответ
    {
        printf("Не удалось открыть файл");
        return 0;
    }

    Umatrix = (double *)malloc((N) * (N) * sizeof(double));
    Dmatrix = (double *)malloc((N) * (N) * sizeof(double));
    Cmatrix = (double *)malloc((N) * (N) * sizeof(double));

    netmemory = (double *)malloc((N + 5) * sizeof(double));
    fmemory = (double *)malloc((N + 5) * sizeof(double));
    net = (double *)malloc((N + 5) * sizeof(double));
    umemory = (double *)malloc((N + 5) * sizeof(double));
    phimemory = (double *)malloc((N + 5) * sizeof(double));

    GenerateNet(net, N - 1);
//    printf("\n Umatrix: \n");
    FullUMatrix(Umatrix, N, net, u);
    // PrintMatrix(Umatrix, N);

//    printf("\n Dmatrix: \n");
    FullDMatrix(Dmatrix, Umatrix, N, umemory, phimemory);
//    PrintMatrix(Dmatrix, N);

//    printf("\n Cmatrix: \n");
    FullCMatrix(Dmatrix, Cmatrix, N, fmemory, umemory, phimemory);

    WriteResult(net, Cmatrix, N, u, fp);

    if ((sk = fopen("printAll.gpi", "w+")) == NULL)
        {
            printf("Не удалось открыть файл");
            
            fclose(fp);
            return 0;
        }

    WriteSkrypt(N, argv[2], sk);
    // PrintMatrix(Cmatrix, N);

    //    printf("\n Cmatrix: \n");
    // PrintMatrix(Cmatrix, N);

/*    printf("net:\n");

    for (int h = 0; h < N; ++h)
    {
        printf("%lf ", net[h]);
    }
    printf("\n");
    for (int h = 1; h < N; h++)
    {
        printf("%lf ", FourierCompute(Cmatrix + 2 * N, N, net[h]));
    }
    printf("\n"); */

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

    free(Umatrix);
    free(Dmatrix);
    free(Cmatrix);

    free(netmemory);
    free(fmemory);
    free(net);
    free(umemory);
    free(phimemory);

    fclose(fp);
    fclose(sk);
    return 0;
}