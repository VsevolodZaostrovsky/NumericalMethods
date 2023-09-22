#include <math.h>

#define NET_GENERATION_ERROR -1
#define NET_GENERATED_WELL 0

# define M_PI           3.14159265358979323846

// требует массив длины N+1, записывает в него сеть узлов, сгенерированных по правилам, описанным в репорте
int GenerateNet(double *net, int N) 
{
    double x_k = 0;
    double h = 0;

    if (N <= 2)
        return NET_GENERATION_ERROR;
    h = 1 / ((double)N - 0.5);
    x_k = h / 2;
    net[0] = - h / 2;
    net[N] = 1;

    for (int k = 1; k < N; k++)
    {
        net[k] = x_k;
        x_k += h;
    }
    return NET_GENERATED_WELL;
}

// функции, вычисляющие и записывающие базисный вектор 
double Phi(int m, int k, int N) 
{
    double h = 1 / (N - 0.5);
    return sin( M_PI * m * ( - h / 2 + k * h) );
}

void WritePhiTo(int m, int N, double * ph) 
{
    for(int k = 1; k < N; ++k) 
    {
        ph[k] = Phi(m, k, N);
    }
}

int WriteCNkTo(int N, double * cNks, double (*u)(double), double * netmemory, double * umemory, double * phimemory)
{
    double h = 1 / (N - 0.5);

    if(GenerateNet(netmemory, N) == NET_GENERATION_ERROR) 
    {
        return NET_GENERATION_ERROR;
    }

    for(int m = 1; m < N; ++m)
    {
        umemory[m] = u(netmemory[m]);
    }

    for(int k = 1; k < N; ++k) 
    {
        WritePhiTo(k, N, phimemory);
        double ans = 0;
        for(int j = 1; j < N; ++j) ans += phimemory[j] * umemory[j] * h;

        cNks[k] = 2 * ans;
    }

    return 0;
}

double FourierCompute(double * coefs, int N, double x) 
{
    double ans = 0;
    for(int m = 1; m < N; ++m)
    {
        ans += coefs[m] * sin( M_PI * m * x );
    }
    return ans;
}

double FullCompute(double x, int N, double * cNks, double (*u)(double), double * netmemory, double * umemory, double * phimemory) 
{
    if(WriteCNkTo(N, cNks, u, netmemory, umemory, phimemory) == 0)
    {
        return FourierCompute(cNks, N, x);
    }
    printf("Error: Cannot write cNks \n\n\n");
    return 0;
}