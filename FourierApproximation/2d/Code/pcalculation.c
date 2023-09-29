#include <stdio.h>
#include <stdlib.h>

#include "pcalculation.h"
#include "Solution.c"

double u(double x, double y)
{
    return x * (1 - x) * y * (1 - y) * cos(x * x) * cos(y * y);
}

double mod(double x) { return x * (x > 0) - x * (x < 0); }

double UniNorm01(double (*f)(double, double), double (*u)(double, double), int N)
{
    double h = 1 / (double)(N);
    double max = 0;
    for (double x = 0; x < 1; x += h)
    {
        for (double y = 0; y < 1; y += h)
        {
            if (mod(f(x, y) - u(x, y)) > max)
                max = mod(f(x, y) - u(x, y));
        }
    }
    return max;
}

void WriteSkrypt(int N, char *testfilename, FILE *out)
{

    fprintf(out, "#! /usr/bin/gnuplot -persist\n");
    fprintf(out, "set terminal png size 1000,1000 enhanced font \"Helvetica Bold, 20\"\n");
    fprintf(out, "set output \"Images/%s.png\"\n\n", testfilename);

    fprintf(out, "set style line 1 lt 1 linecolor rgb \"red\" lw 1 pt 1\n");

    fprintf(out, "set title \"%s - %d knots \"\n", testfilename, N);

    fprintf(out, "set grid\n\n");

    fprintf(out, "plot  \"%s\" using 1:2 ls 1 title \"Dependence -log(norm) of -log(h)\" with lines", testfilename);
}

void WriteNorm(double *lognorms, double *loghs, int N, FILE *out)
{
    for (int i = 0; i < N; ++i)
    {
        fprintf(out, "%20.15lf %20.15lf \n", loghs[i], lognorms[i]);
    }
}

int main(int argc, char *argv[])
{
    int N; // число узлов
    FILE *fp;
    FILE *sk;
    int NumKnots = 2;
    double FFC;

    double *Umatrix;
    double *Dmatrix;
    double *Cmatrix;

    double *netmemory;
    double *fmemory;
    double *net;
    double *umemory;
    double *phimemory;

    double *lognorms;
    double *loghs;

    double MaxForNorm;
    double hForNorm;
    double p = 0;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("N name \n");
        printf("where: \n N - number of knots \n name - name of the file with answer \n");
        return -1;
    }

    N = atoi(argv[1]); // число узлов

    if (N <= 2)
    {
        printf("Wrong N: it must be >= 2\n");
        return -1;
    }

    printf("N = %d \n", N);

    Umatrix = (double *)malloc((N) * (N) * (NumKnots + 2) * sizeof(double));
    Dmatrix = (double *)malloc((N) * (N) * (NumKnots + 2) * sizeof(double));
    Cmatrix = (double *)malloc((N) * (N) * (NumKnots + 2) * sizeof(double));

    netmemory = (double *)malloc((N + 5) * (NumKnots + 2) * sizeof(double));
    fmemory = (double *)malloc((N + 5) * (NumKnots + 2) * sizeof(double));
    net = (double *)malloc((N + 5) * (NumKnots + 2) * sizeof(double));
    umemory = (double *)malloc((N + 5) * (NumKnots + 2) * sizeof(double));
    phimemory = (double *)malloc((N + 5) * (NumKnots + 2) * sizeof(double));

    lognorms = (double *)malloc(NumKnots * sizeof(double));
    loghs = (double *)malloc(NumKnots * sizeof(double));

    printf("memory allocated \n");

    hForNorm = 1 / ((double)(N * 5));
    MaxForNorm = 1e-10;
    for (double x = 0; x < 1; x += hForNorm)
    {
        for (double y = 0; y < 1; y += hForNorm)
        {
            FFC = FullFurierCompute(x, y, Umatrix, Dmatrix, Cmatrix, N, fmemory, net, u, netmemory, umemory, phimemory);
            if (mod(FFC - u(x, y)) > MaxForNorm)
                MaxForNorm = mod(FFC - u(x, y));
        }
    }
    lognorms[0] = log(1 / MaxForNorm);
    loghs[0] = log(N);

    MaxForNorm = 1e-10;
    for (double x = 0; x < 1; x += hForNorm)
    {
        for (double y = 0; y < 1; y += hForNorm)
        {
            FFC = FullFurierCompute(x, y, Umatrix, Dmatrix, Cmatrix, N * 2, fmemory, net, u, netmemory, umemory, phimemory);
            if (mod(FFC - u(x, y)) > MaxForNorm)
                MaxForNorm = mod(FFC - u(x, y));
        }
    }
    lognorms[1] = log(1 / MaxForNorm);
    loghs[1] = log(N * 2);

    if ((fp = fopen(argv[2], "w")) == NULL) // имя файла, в который нужно записать ответ
    {
        printf("Не удалось открыть файл");
        return 0;
    }

    WriteNorm(lognorms, loghs, NumKnots, fp);
    if ((sk = fopen("printDependence.gpi", "w+")) == NULL)
    {
        printf("Не удалось открыть файл");

        fclose(fp);
        return 0;
    }
    WriteSkrypt(N, argv[2], sk);
    fclose(fp);
    fclose(sk);

    printf("result written \n");

    if (mod(loghs[0] - loghs[1]) > 1e-12)
    {
        p = (lognorms[1] - lognorms[0]) / (loghs[1] - loghs[0]);
    }
    printf("The answer: p = %20.15lf \n", p);

    free(Umatrix);
    free(Dmatrix);
    free(Cmatrix);

    free(netmemory);
    free(fmemory);
    free(net);
    free(umemory);
    free(phimemory);
    free(lognorms);
    free(loghs);

    return 0;
}