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

void f3(double * x, double * y, double * ans, int n) 
{
    if (n != 2) 
    {
        printf("Total error! \n\n");
        return;
    }
    ans[0] = y[1];
    ans[1] = y[0];
    
    return;
}

void sol3(double * x, double * y, double * ans, int n) 
{
    if (n != 2) 
    {
        printf("Total error! \n\n");
        return;
    }
    ans[0] = exp(-x[0]);
    ans[1] = - exp(-x[0]);
    
    return;
}

void printArr(double * x, int n)
{
    for(int k = 0; k < n; k++)
        printf("%lf ", x[k]);
    printf("\n");
}

double L0norm(double *x, double *y, int len) {
    double max = fabs(x[0] - y[0]);
    for(int i = 1; i < len; i++) {
        if (fabs(x[i] - y[i]) > max) {
            max = fabs(x[i] - y[i]);
        }
    }
    return max;
}