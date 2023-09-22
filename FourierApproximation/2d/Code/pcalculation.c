#include <stdio.h>
#include <stdlib.h>

#include "Solution.c"

double u(double x)
{
    return x * (1 - x) * cos(x * x);
}

double mod(double x) { return x * (x > 0) - x * (x < 0); }

double UniNorm01(double (*f)(double), double (*u)(double), int N)
{
    double h = 1 / (double)(N);
    double max = 0;
    for (double x = 0; x < 1; x += h)
    {
        if (mod(f(x) - u(x)) > max)
            max = mod(f(x) - u(x));
    }
    return max;
}

void WriteSkrypt(int N, char *testfilename, FILE *out)
{

    fprintf(out, "#! /usr/bin/gnuplot -persist\n");
    fprintf(out, "set terminal png size 1000,1000 enhanced font \"Helvetica Bold, 20\"\n");
    fprintf(out, "set output \"%s.png\"\n\n", testfilename);

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
    int NumKnots = 4;

    double *netmemory;
    double *umemory;
    double *phimemory;
    double *cNks;

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

    netmemory = (double *)malloc(5 * (N + 1) * sizeof(double));
    umemory = (double *)malloc(5 * (N + 1) * sizeof(double));
    phimemory = (double *)malloc(5 * (N + 1) * sizeof(double));
    cNks = (double *)malloc(5 * (N + 1) * sizeof(double));

    lognorms = (double *)malloc(NumKnots * sizeof(double));
    loghs = (double *)malloc(NumKnots * sizeof(double));

    printf("memory allocated \n");

    for (int k = 1; k < NumKnots + 1; ++k)
    {
        if (WriteCNkTo(N * k, cNks, u, netmemory, umemory, phimemory) == NET_GENERATION_ERROR)
        {
            printf("cNks not calculated - net generation error \n\n\n");
            return -1;
        }
        hForNorm = 1 / ((double)(N * k));
        MaxForNorm = 1e-10;
        for (double x = 0; x < 1; x += hForNorm)
        {
            if (mod(FourierCompute(cNks, N * k, x) - u(x)) > MaxForNorm)
                MaxForNorm = mod(FourierCompute(cNks, N * k, x) - u(x));
        }
        lognorms[k - 1] = log(1 / MaxForNorm);
        loghs[k - 1] = log(1 / hForNorm);
    }

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

    if(mod(loghs[0] -loghs[1]) > 1e-12 && mod(loghs[2] -loghs[3]) > 1e-12)
    {
        p = 0.5 * ((lognorms[0] - lognorms[1]) / (loghs[0] -loghs[1]) + (lognorms[3] - lognorms[2]) / (loghs[3] -loghs[2]));
    } 
    printf("The answer: p = %20.15lf \n", p);

    free(netmemory);
    free(umemory);
    free(phimemory);
    free(cNks);
    free(lognorms);
    free(loghs);

    return 0;
}