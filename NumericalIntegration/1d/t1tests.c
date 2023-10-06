#include <stdio.h>
#include <stdlib.h>

#include "Solution.h"
double f0(double x);
double f1(double x);
double f2(double x);
double f3(double x);
double f5(double x);
double f9(double x);

double f0(double x) { return 1 + x * 0; }

double f1(double x) { return x; }

double f2(double x) { return x * x; }

double f3(double x) { return x * x * x; }

double f5(double x) { return x * x * x * x * x; }

double f9(double x) { return x * x * x * x * x * x * x * x * x; }


int main(int argc, char *argv[])
{
    double a, b;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("a b \n");
        return -1;
    }
    

    a = atof(argv[1]); // число узлов
    b = atof(argv[2]); 

    printf("Sympson 0: %20.15lf\n", IntegralS(a, b, f0));
    printf("Gauss 0: %20.15lf\n", IntegralG(a, b, f0));

    printf("Sympson 1: %20.15lf\n", IntegralS(a, b, f1));
    printf("Gauss 1: %20.15lf\n", IntegralG(a, b, f1));

    printf("Sympson 2: %20.15lf\n", IntegralS(a, b, f2));
    printf("Gauss 2: %20.15lf\n", IntegralG(a, b, f2));

    printf("Sympson 3: %20.15lf\n", IntegralS(a, b, f3));
    printf("Gauss 3: %20.15lf\n", IntegralG(a, b, f3));

    printf("Sympson 5: %20.15lf\n", IntegralS(a, b, f5));
    printf("Gauss 5: %20.15lf\n", IntegralG(a, b, f5));

    printf("Sympson 9: %20.15lf\n", IntegralS(a, b, f9));
    printf("Gauss 9: %20.15lf\n", IntegralG(a, b, f9));
}
