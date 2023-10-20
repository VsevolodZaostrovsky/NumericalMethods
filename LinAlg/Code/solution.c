#include "solution.h"
// double Richardson(double *x, const double *A, const double *b, double tau, int n, double eps, int mIter);

// double psi(int k, int n, int N);

// double LambdaN(int n, int N, double p);

// double Cn(int n, double * f, double p, int N);

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

void FormBFromA(double *A, int N, double *b)
{
    b[0] = 0;
    for (int k = 1; k < N; k++)
    {
        b[k] = 0;
        for (int j = 0; j < N; j += 2)
        {
            b[k] += A[k * N + j];
        }
    }
}

void FormBFromA1(double *A, int N, double *b)
{
    for (int k = 0; k < N; k++)
    {
        b[k] = 0;
        for (int j = 0; j < N; j += 2)
        {
            b[k] += A[k * N + j];
        }
    }
}

double FindTau(const double *A, int n)
{
    double max = 0;
    double min = 0;
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += fabs(A[i * n + j]);
        }
        if (sum > max)
            max = sum;

        if (2 * A[i + i * n] - sum < min)
            min = 2 * A[i + i * n] - sum;
    }
    return 2 / (max + min);
}

double Findq(const double *A, int n)
{
    double max = 0;
    double min = 0;
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += fabs(A[i * n + j]);
        }
        if(i == 0) min = 2 * A[i + i * n] - sum;
        
        if (sum > max)
            max = sum;

        if (2 * A[i + i * n] - sum < min)
            min = 2 * A[i + i * n] - sum;
    }

    // printf("max = %20.15lf min = %20.15lf q = %20.15lf\n", max, min, (double)(max - min) / (double)(max + min));
    return (double)(max - min) / (double)(max + min);
}

double ErNorm(const double *A, const double *b, double *x, int N, double *mem)
{
    double ans = 0;

    multMatrixByVector(A, x, mem, N);

    for (int i = 0; i < N; i++)
    {
        ans += (b[i] - mem[i]) * (b[i] - mem[i]);
    }

    return sqrt(ans);
}

double ErNormInf(const double *A, const double *b, double *x, int N, double *mem)
{
    double ans = 0;

    multMatrixByVector(A, x, mem, N);

    for (int i = 0; i < N; i++)
    {
        if(fabs((b[i] - mem[i])) > ans) ans = fabs((b[i] - mem[i]));
    }

    return sqrt(ans);
}

void FourierMatrix(double p, int N, double *M)  // (N+1)^2 memory needed 
{
    for (int i = 0; i < N + 1; i++)
    {
        for (int j = 0; j < N + 1; j++)
        {
            if (i == j && i > 0 && j > 0 && i < N && j < N)
                M[i * (N + 1) + j] = p + 2.0 * ((double)(N) * (double)(N));
            else if ((i - j == 1 || i - j == -1) && i > 0 && j > 0 && i < N && j < N)
                M[i * (N + 1) + j] = -1.0 * ((double)(N) * (double)(N));
            else
                M[i * (N + 1) + j] = 0;
        }
    }
}

void FourierMatrixWithoutZeros(double p, int N, double *M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                M[i * N + j] = p + 2.0 * ((double)(N + 1) * (double)(N + 1));
            else if (i - j == 1 || i - j == -1)
                M[i * N + j] = -1.0 * ((double)(N + 1) * (double)(N + 1));
            else
                M[i * N + j] = 0;
        }
    }
}

double psi(int k, int n, int N)
{
    return sin(PI * n * k / (double)(N));
}

double Lambdan(int n, int N, double p)
{
    double l = p - 2 * N * N * (cos(PI * n / (double)(N)) - 1);
    return l;
}

double Dn(int n, double *f, double p, int N)
{
    double sp = 0;
    for (int i = 0; i < N; i++)
    {
        sp += 2 * f[i] * psi(i, n, N) / (double)(N);
    }

    return sp;
}

double FourierMethod(double *y, int N, double p, double *f)
{
    for (int k = 0; k < N + 1; k++)
    {
        y[k] = 0;
        for (int n = 1; n < N; n++)
        {
            y[k] += Dn(n, f, p, N) / Lambdan(n, N, p) * psi(k, n, N);
        }
    }

    return 0.;
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

    return ErNorm(A, b, x, n, mem);
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
        for (int j = 0; j < n; j++)
            mem[j] = b[j] - mem[j];

        multMatrixByVector(B, mem, mem1, n);

        for (int i = 0; i < n; i++)
        {
            // printf("x[%d]:\n", m);
            x[i] = x[i] + tau * mem1[i];
            // printf("%1.5lf = %1.5lf - %1.5lf * %1.5lf + %1.5lf * %1.5lf \n", x[i], mem[i], tau, mem[i], tau, b[i]);
        }
        // print_vector(x, n);
        // printf("\n");
    }

    return ErNormInf(A, b, x, n, mem);
}

int read_matrix(FILE *inp, double *matrix, int dim)
{
    for (int i = 0; i < dim * dim; ++i)
    {
        fscanf(inp, "%lf", &matrix[i]);
    }
    return 1;
}

void print_matrix(double * A, int N) 
{
    for(int i = 0; i < N * N; i++) {
        if(i % N == 0) printf("\n");
        printf("%20.15lf ", A[i]);
    }
    printf("\n");
}

void print_vector(double * A, int N) 
{
    for(int i = 0; i < N; i++) {
        printf("%20.15lf ", A[i]);
    }
    printf("\n");
}

void ReverseFourierMatrixWithoutZeros(double p, double * B, int N, double * mem1, double * mem2) 
{
    for(int i = 0; i < N + 1; i++) 
    {
        mem2[i] = 0;
    }
    for(int i = 1; i < N; i++) 
    {   
        mem2[i] = 1;
        FourierMethod(mem1, N, p, mem2);
        // printf("vectoe: ");
        // print_vector(mem1, N);
        // printf("vectoe[1]: %20.15lf \n", mem1[1]);
        mem2[i] = 0;

        for(int j = 0; j < N - 1; j++) 
        {
            B[j + (i - 1) * (N - 1)] = mem1[j + 1];
        }
    }
}

void Task3Matrix(double * A, int N) 
{
    double h = PI / (double)(N + 1);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                A[i * N + j] = 1. + sin(PI * (i + 1) * h) * sin(PI * (i + 1) * h) + 2.0 / h / h;
            else if (i - j == 1 || i - j == -1)
                A[i * N + j] = -1.0 / h / h;
            else
                A[i * N + j] = 0;
        }
    }
}