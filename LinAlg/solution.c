#include "solution.h"
#define M_PI  	3.14159265358979323
// double Richardson(double *x, const double *A, const double *b, double tau, int n, double eps, int mIter);

void multMatrixByVector(const double *A, double *x, double *ans, int N)
{
    for (int i = 0; i < N; i++)
    {
        ans[i] = 0;
        for (int j = 0; j < N; j++)
        {
            ans[i] += A[i * N + j] * x[j];
        }
    }
}

void FormBFromA(double *A, int N, double * b) 
{
    for(int k = 0; k < N; k++) 
    {
        b[k] = 0;
        for(int j = 0; j < N; j+=2) 
        {
            b[k] += A[k * N + j];
        }
    }
}

double FindTau(const double *A, int n) 
{
    double max = 0;
    double sum = 0;
    for (int i = 0; i < n; i++) 
    {
        sum = 0;
        for(int j = 0; j < n; j++)
        {
            sum += fabs(A[i * n + j]);
        }
        if(sum > max) max = sum;
    }
    if(max < 2) return 0.5;
    return 2 / max;
}

inline double psi(int k, int n, int N) 
{
    return sin(M_PI * (double)(n) * (double)(k) / (double)(N));
}

inline double LambdaN(int n, int N, double p) 
{
    return (double)(N) * (double)(N) * 2 * (cos(M_PI * (double)(n) / (double)(N)) - 1) + p;
}

inline double Cn(int n, double * f, double p, int N) 
{
    double sp = 0;
    for(int i = 0; i < N; i++) 
    {
        sp += 2 * f[i] * psi(i, n, N) / (double)(N);
    }
    return sp / LambdaN(n, N, p);
}

double FourierMethod(double * x, int N, double p, double * f) 
{
    for(int i = 0; i < N; i++) x[i] = 0;
    
}

double Richardson(double *x, const double *A, const double *b, double tau, int n, int mIter, double *mem)
{
    for (int k = 0; k < n; k++)
    {
        x[k] = 0;
        mem[k] = 0;
    }
    for (int m = 0; m < mIter; m++)
    {
        multMatrixByVector(A, x, mem, n);

        for (int i = 0; i < n; i++)
        {
            // printf("x[%d]:\n", m);
            x[i] = x[i] - tau * mem[i] + tau * b[i];
            // printf("%1.5lf = %1.5lf - %1.5lf * %1.5lf + %1.5lf * %1.5lf \n", x[i], mem[i], tau, mem[i], tau, b[i]);
        }
        // printf("\n");
    }
}

double BSolver(double *x, const double *A, const double *B, const double *b, double tau, int n, int mIter, double *mem, double *mem1) 
{
    for (int k = 0; k < n; k++)
    {
        x[k] = 0;
        mem[k] = 0;
    }
    for (int m = 0; m < mIter; m++)
    {
        multMatrixByVector(A, x, mem, n);
        for(int j = 0; j < n; j++) mem[j] = b[j] - mem[j];

        multMatrixByVector(B, mem, mem1, n);
        

        for (int i = 0; i < n; i++)
        {
            // printf("x[%d]:\n", m);
            x[i] = x[i] + tau * mem1[i];
            // printf("%1.5lf = %1.5lf - %1.5lf * %1.5lf + %1.5lf * %1.5lf \n", x[i], mem[i], tau, mem[i], tau, b[i]);
        }
        // printf("\n");
    }
}