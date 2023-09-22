#include <stdio.h>
#include <stdlib.h>

#include "Solution.c"

double u(double x)
{
    return x * (1 - x) * cos(x * x);
}

void PrintTable(double *knots, int N, double *coefs, double (*u)(double))
{
    printf("   Knotes               Fourier              f\n");
    for (int i = 1; i < N - 1; ++i)
    {
        double xi = knots[i];
        printf("%20.15lf %20.15lf %20.15lf \n", xi, FourierCompute(coefs, N, xi), u(xi));
        double xi1 = 2 * xi / 3 + knots[i + 1] / 3;
        printf("%20.15lf %20.15lf %20.15lf \n", xi1, FourierCompute(coefs, N, xi1), u(xi1));
        double xi2 = xi / 3 + 2 * knots[i + 1] / 3;
        printf("%20.15lf %20.15lf %20.15lf \n", xi2, FourierCompute(coefs, N, xi2), u(xi2));
    }
    double xi = knots[N - 1];
    printf("%20.15lf %20.15lf %20.15lf \n", xi, FourierCompute(coefs, N, xi), u(xi));
}

void WriteResult(double *knots, int N, double *coefs, double (*f)(double), FILE *out)
{
    for (int i = 1; i < N - 1; ++i)
    {
        double xi = knots[i];
        fprintf(out, "%20.15lf %20.15lf %20.15lf \n", xi, FourierCompute(coefs, N, xi), f(xi));
        double xi1 = 2 * xi / 3 + knots[i + 1] / 3;
        fprintf(out, "%20.15lf %20.15lf %20.15lf \n", xi1, FourierCompute(coefs, N, xi1), f(xi1));
        double xi2 = xi / 3 + 2 * knots[i + 1] / 3;
        fprintf(out, "%20.15lf %20.15lf %20.15lf \n", xi2, FourierCompute(coefs, N, xi2), f(xi2));
    }
    double xi = knots[N - 1];
    fprintf(out, "%20.15lf %20.15lf %20.15lf \n", xi, FourierCompute(coefs, N, xi), f(xi));
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

    fprintf(out, "plot  \"%s\" using 1:2 ls 1 title \"Interpolation Fourier Row\" with lines, ", testfilename);
    fprintf(out, "\"%s\" using 1:3 ls 2 title \"Original function\", ", testfilename);
}

int main(int argc, char *argv[])
{
    int N; // число узлов
    FILE *fp;
    FILE *sk;

    double *netmemory;
    double *umemory;
    double *phimemory;
    double *cNks;

    int flag = 0;

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

    netmemory = (double *)malloc((N + 1) * sizeof(double));
    umemory = (double *)malloc((N + 1) * sizeof(double));
    phimemory = (double *)malloc((N + 1) * sizeof(double));
    cNks = (double *)malloc((N + 1) * sizeof(double));

    printf("memory allocated \n");

    if(WriteCNkTo(N, cNks, u, netmemory, umemory, phimemory) == NET_GENERATION_ERROR) 
    {
        printf("cNks not calculated - net generation error \n\n\n");
        return -1;
    }

 /*   printf(" \n N etmemory: \n"); for(int k = 0; k < N + 1; k ++)  printf("%20.15lf ", netmemory[k]); printf("\n umemory: \n");

    for(int k = 0; k < N + 1; k ++) 
    {
        printf("%20.15lf ", umemory[k]);
    }

            printf("\n cNks: \n");
//    GenerateNet(netmemory, N);
    for(int k = 0; k < N + 1; k ++) 
    {
        printf("%20.15lf ", cNks[k]);
    } */

    printf("cNks calculated \n");

    if (argv[2][0] == 'n' && argv[2][1] == 'o')
    {
        flag = 1;
    }

    printf("trying to open file %s \n", argv[2]);

    if (flag == 0 && (fp = fopen(argv[2], "w")) == NULL) // имя файла, в который нужно записать ответ
    {
        printf("Не удалось открыть файл");
        return 0;
    }



    printf("file opened \n");

    if (flag)
        PrintTable(netmemory, N, cNks, u);
    else
    {
        WriteResult(netmemory, N, cNks, u, fp);
        if ((sk = fopen("printAll.gpi", "w+")) == NULL)
        {
            printf("Не удалось открыть файл");
            
            fclose(fp);
            return 0;
        }
        WriteSkrypt(N, argv[2], sk);
        fclose(fp);
        fclose(sk);
    }

    printf("result written \n");


    free(netmemory);
    free(umemory);
    free(phimemory);
    free(cNks);

    return 0;
}