#include <math.h>

#define NET_GENERATION_ERROR -1
#define NET_GENERATED_WELL 0

#define M_PI 3.14159265358979323846
#define e(i, j, n) ((i - 1) * (n) + (j - 1))
// #define e(i, j, n, N_x, N) ((n - 1) * (n * n) + (j - 1))

double FourierCompute(double *coefs, int N, double x);

// требует массив длины N+1, записывает в него сеть узлов, сгенерированных по правилам, описанным в репорте
int GenerateNet(double *net, int N);

// функции, вычисляющие и записывающие базисный вектор
double Phi(int n, int i, int N);

void WritePhiTo(int m, int N, double *ph);

int WriteCNkTo(int N, double *cNks, double *u, double *umemory, double *phimemory);

void FullUMatrix(double *Umatrix, int N, double *net, double (*u)(double, double));

void FullDMatrix(double *Dmatrix, double *Umatrix, int N, double *umemory, double *phimemory);

void FullCMatrix(double *Dmatrix, double *Cmatrix, int N, double *fmemory, double *umemory, double *phimemory);

void FindFourierCoefs(double *Umatrix, double *Dmatrix, double *Cmatrix, int N,
                      double *fmemory, double *net, double (*u)(double, double),
                      double *netmemory, double *umemory, double *phimemory);

double Calc2DFourier(double *Cmatrix, int N, double x, double y);

double FullFurierCompute(double x, double y,
                         double *Umatrix, double *Dmatrix, double *Cmatrix, int N,
                         double *fmemory, double *net, double (*u)(double, double),
                         double *netmemory, double *umemory, double *phimemory);

void CalcFourierMatrix(double * ans, double *Cmatrix, int N);