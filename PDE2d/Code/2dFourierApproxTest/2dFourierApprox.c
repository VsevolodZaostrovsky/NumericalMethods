#include <math.h>

#define NET_GENERATION_ERROR -1
#define NET_GENERATED_WELL 0

#define M_PI 3.14159265358979323846
#define e(i, j, n) ((i - 1) * (n) + (j - 1))

double FourierCompute(double *coefs, int N, double x)
{
    double ans = 0;
    for (int m = 1; m < N; ++m)
    {
        ans += coefs[m] * sin(M_PI * m * x);
    }
    return ans;
}

// требует массив длины N+1, записывает в него сеть узлов, сгенерированных по правилам, описанным в репорте
int GenerateNet(double *net, int N)
{
    double x_k = 0;
    double h = 0;

    if (N <= 2)
        return NET_GENERATION_ERROR;
    h = 1 / ((double)N);
    x_k = h;
    net[0] = 0;
    net[N] = 1;

    for (int k = 1; k < N; k++)
    {
        net[k] = x_k;
        x_k += h;
    }
    return NET_GENERATED_WELL;
}

// функции, вычисляющие и записывающие базисный вектор
double Phi(int n, int i, int N)
{
    double h = 1 / ((double)N);
    return sin(M_PI * n * i * h);
}

void WritePhiTo(int m, int N, double *ph)
{
    for (int k = 1; k < N; ++k)
    {
        ph[k] = Phi(m, k, N);
    }
}

int WriteCNkTo(int N, double *cNks, double *u, double *umemory, double *phimemory)
{
    double h = 1 / ((double)N);

    /*    if (GenerateNet(netmemory, N) == NET_GENERATION_ERROR)
        {
            return NET_GENERATION_ERROR;
        } */

    for (int m = 1; m < N; ++m)
    {
        umemory[m] = u[m];
        //        printf("umemory %d: %lf ", m, u[m]);
    }
    //    printf("\n");
    umemory[0] = 0;

    for (int k = 1; k < N; ++k)
    {
        WritePhiTo(k, N, phimemory);
        double ans = 0;
        for (int j = 1; j < N; ++j)
            ans += phimemory[j] * umemory[j] * h;

        cNks[k] = 2 * ans;
    }

    return 0;
}

void FullUMatrix(double *Umatrix, int N, double *net, double (*u)(double, double))
{
    for (int i = 1; i < N + 1; ++i)
    {
        for (int j = 1; j < N + 1; ++j)
        {
            if (i == 1 || i == N || j == 1 || j == N)
                Umatrix[e(i, j, N)] = 0;
            else
                Umatrix[e(i, j, N)] = u(net[i - 1], net[j - 1]);
        }
    }
}

void FullDMatrix(double *Dmatrix, double *Umatrix, int N, double *umemory, double *phimemory)
{
    //    printf("\n");
    for (int j = 0; j < N; j += 1)
    {
        Dmatrix[j * N] = 0;
        Dmatrix[j * N + N - 1] = 0;
        WriteCNkTo(N - 1, Dmatrix + j * N, Umatrix + j * N, umemory, phimemory);
    }
}

void FullCMatrix(double *Dmatrix, double *Cmatrix, int N, double *fmemory, double *umemory, double *phimemory)
{
    for (int i = 0; i < N; i += 1)
    {
        Cmatrix[i * N] = 0;
        Cmatrix[i * N + N - 1] = 0;
        for (int h = 0; h < N; ++h)
        {
            fmemory[h] = Dmatrix[h * N + i];
        }
        WriteCNkTo(N - 1, Cmatrix + i * N, fmemory, umemory, phimemory);
    }
}

void FindFourierCoefs(double *Umatrix, double *Dmatrix, double *Cmatrix, int N,
                      double *fmemory, double *net, double (*u)(double, double),
                      double *netmemory, double *umemory, double *phimemory)
{
    GenerateNet(net, N-1);
    FullUMatrix(Umatrix, N, net, u);
    FullDMatrix(Dmatrix, Umatrix, N, umemory, phimemory);
    FullCMatrix(Dmatrix, Cmatrix, N, fmemory, umemory, phimemory);
}

double Calc2DFourier(double *Cmatrix, int N, double x, double y)
{
    double ans = 0;
    for (int m = 1; m < N + 1; ++m)
    {
        for (int n = 1; n < N + 1; ++n)
        {
            ans += Cmatrix[e(m, n, N)] * sin(M_PI * (m - 1) * x) * sin(M_PI * (n - 1) * y);
        }
    }
    return ans;
}


double FullFurierCompute(double x, double y,
                         double *Umatrix, double *Dmatrix, double *Cmatrix, int N,
                         double *fmemory, double *net, double (*u)(double, double),
                         double *netmemory, double *umemory, double *phimemory)
{
    FindFourierCoefs(Umatrix, Dmatrix, Cmatrix, N, fmemory, net, u, netmemory, umemory, phimemory);
    return Calc2DFourier(Cmatrix, N, x, y);
}