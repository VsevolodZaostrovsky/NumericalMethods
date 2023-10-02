#include <math.h>

// метод Симпсона
double IntegralS (double a, double b, double (*f)(double));

// метод Гаусса
double IntegralG (double a, double b, double (*f)(double));

// составная квадратура Симпсона и квадратуру Гаусса
double IntegralQS (double a, double b, double (*f)(double), int N);

// составная квадратура Гаусса
double IntegralQG (double a, double b, double (*f)(double), int N);