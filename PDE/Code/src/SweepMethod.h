#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* На самом деле, система должна иметь размер N+1, здесь я следую обозначениям Чижонкова Бахвалова и Корнева*/
int sweep_method(double * a, double * b, double * c, double * f, double * y, double * alpha, double * beta, int N);