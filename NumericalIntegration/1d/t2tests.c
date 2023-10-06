#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Solution.h"

double f1(double x) { return cos(100 * x); }

double f2(double x) { return exp(-1000 * x); }

double f3(double x) { return 1 / sqrt(1 - x * x); }

int main(int argc, char *argv[])
{
    int N, ON;
    FILE *fp;
    double LS1, LG1, LS2, LG2, LS3, LG3;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("N filename\n");
        return -1;
    }

    if ((fp = fopen(argv[2], "w")) == NULL) // имя файла, в который нужно записать ответ
    {
        printf("Не удалось открыть файл\n");
        return 0;
    }

    N = atoi(argv[1]);

    LS1 = log(fabs(IntegralQS(0, 3.14159265358979323846, f1, N)));
    LG1 = log(fabs(IntegralQG(0, 3.14159265358979323846, f1, N)));
    LS2 = log(fabs(IntegralQS(0, 1, f2, N) - 0.001));
    LG2 = log(fabs(IntegralQG(0, 1, f2, N) - 0.001));
    LS3 = log(fabs(IntegralQS(-0.99, 0.99, f3, N) - 2.23954));
    LG3 = log(fabs(IntegralQG(-0.99, 0.99, f3, N) - 2.23954));

    printf("Sympson 1: %20.15lf\n logR = %20.15lf\n", IntegralQS(0, 3.14159265358979323846, f1, N), LS1);
    printf("Gauss 1: %20.15lf\n logR = %20.15lf\n", IntegralQG(0, 3.14159265358979323846, f1, N), LG1);

    printf("Sympson 2: %20.15lf\n logR = %20.15lf\n", IntegralQS(0, 1, f2, N), LS2);
    printf("Gauss 2: %20.15lf\n logR = %20.15lf\n", IntegralQG(0, 1, f2, N), LG2);

    printf("Sympson 3: %20.15lf\n logR = %20.15lf\n", IntegralQS(-0.9, 0.9, f3, N), LS3);
    printf("Gauss 3: %20.15lf\n logR = %20.15lf\n", IntegralQG(-0.9, 0.9, f3, N), LG3);

//    fprintf(fp, "%20.15lf %20.15lf %20.15lf %20.15lf %20.15lf %20.15lf %20.15lf\n", log(1 / (double)(N)), LS1, LG1, LS2, LG2, LS3, LG3);

    ON = N;
    for (int k = 1; k < 50; ++k)
    {
        N = ON + k;
        LS1 = log(fabs(IntegralQS(0, 3.14159265358979323846, f1, N)));
        LG1 = log(fabs(IntegralQG(0, 3.14159265358979323846, f1, N)));
        LS2 = log(fabs(IntegralQS(0, 1, f2, N) - 0.001));
        LG2 = log(fabs(IntegralQG(0, 1, f2, N) - 0.001));
        LS3 = log(fabs(IntegralQS(-0.9, 0.9, f3, N) - 2.23954));
        LG3 = log(fabs(IntegralQG(-0.9, 0.9, f3, N) - 2.23954));
        fprintf(fp, "%20.15lf %20.15lf %20.15lf %20.15lf %20.15lf %20.15lf %20.15lf\n", log((double)(N)), LS1, LG1, LS2, LG2, LS3, LG3);
    }
}