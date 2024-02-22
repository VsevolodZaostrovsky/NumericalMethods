#include "Useful.h"

void f1(double * x, double * y, double * ans, int n) 
{
    for(int k = 0; k < n; k++)
        ans[k] = y[k];
    
    return;
}

void f2(double * x, double * y, double * ans, int n) 
{
    for(int k = 0; k < n; k++)
        ans[k] = x[k];
    
    return;
}

void printArr(double * x, int n)
{
    for(int k = 0; k < n; k++)
        printf("%lf ", x[k]);
    printf("\n");
}