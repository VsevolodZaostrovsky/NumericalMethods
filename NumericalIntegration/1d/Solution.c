#include "Solution.h"

double IntegralS (double a, double b, double (*f)(double)) 
{
    return (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b));
}


//метод Гаусса
double IntegralG (double a, double b, double (*f)(double)) 
{
    double x0 = (a + b) / 2;
    double xminus = x0 - (b - a) / 2 * sqrt(3 / 5);
    double xplus = x0 + (b - a) / 2 * sqrt(3 / 5);

    return (b - a) / 18 * (5 * f(xminus) + 8 * f(x0) + 5 * f(xplus));
}

// составная квадратура Симпсона и квадратуру Гаусса
double IntegralQS (double a, double b, double (*f)(double), int N) 
{
    double step = (b - a) / N;
    double ans = 0;

    for(int i = 0; i < N; i++) {
        ans += IntegralS(a + i * step, a + (i + 1) * step, f);
    } 

    return ans;
}

// составная квадратура Гаусса
double IntegralQG (double a, double b, double (*f)(double), int N) 
{
    double step = (b - a) / N;
    double ans = 0;

    for(int i = 0; i < N; i++) {
        ans += IntegralG(a + i * step, a + (i + 1) * step, f);
    } 

    return ans;
}
