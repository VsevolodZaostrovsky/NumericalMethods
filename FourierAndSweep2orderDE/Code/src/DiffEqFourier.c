#include "FourierMethod.h"

double f(double x){ return 1; }

double full_b_f(double * b, double (*f)(double), int N){
    double delta = 0;
    double h = (double)(1 / N);
    for(int j = 0; j < N; j++) {
        b[j] = f(delta);
        delta += h;
    }
}

int main(int argc, char *argv[])
{
    int N = 6;
    double p = 0.;
    double *b;
    double *x;
    double *mem;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("N p \n");
        return -1;
    }

    N = atoi(argv[1]);
    p = atof(argv[2]); 

    b = (double *)malloc((N + 1) * sizeof(double));
    x = (double *)malloc((N + 1) * sizeof(double));
    mem = (double *)malloc((N + 1) * sizeof(double));
    
    full_b_f(b, f, N);
    FourierMethod(x, N, p, b);
    
    // printf("b: ");
    // print_vector(b, N + 1);
    // printf("ans: ");
    print_vector(x, N + 1);


    free(b);
    free(x);
    free(mem);

    return 0;
}
