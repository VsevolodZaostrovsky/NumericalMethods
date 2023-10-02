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

    return (b - a) / 18 * (5 * f(xminus) + 8 * f(x0) + 5 * f(xminus));
}