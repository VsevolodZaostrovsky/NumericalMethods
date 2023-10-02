#include <stdio.h>
#include <stdlib.h>

#include "Solution.h"

double f1(double x) { return cos(100 * x); }

double f2(double x) { return exp(- 1000 * x); }

double f3(double x) { return 1 / sqrt(1 - x * x); }


int main(int argc, char *argv[])
{
    int N;

    if (argc < 2)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("N \n");
        return -1;
    }
    

    N = atoi(argv[1]);

    printf("Sympson 1: %20.15lf\n", IntegralQS(0, 3.1415926535, f1, N));
    printf("Gauss 1: %20.15lf\n", IntegralQG(0, 3.1415926535, f1, N));

    printf("Sympson 2: %20.15lf\n", IntegralQS(0, 1, f2, N));
    printf("Gauss 2: %20.15lf\n", IntegralQG(0, 1, f2, N));

    printf("Sympson 3: %20.15lf\n", IntegralQS(-0.99, 0.99, f3, N));
    printf("Gauss 3: %20.15lf\n", IntegralQG(-0.99, 0.99, f3, N));

}