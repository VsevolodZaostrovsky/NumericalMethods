#include "tests.h"


double u0(double x, double y)
{
    return 0;
}

double f( double t, double x, double y) 
{
    return exp(- M_PI * M_PI * 2 * t) * sin(M_PI * x) * sin(M_PI *y);
}

void printMatrix(double * matrix, int N){
    for(int i = 1; i < N + 1; i++){
            for(int j = 1; j < N + 1; j++){
                printf("%lf ", matrix[e(i, j, N)]);
            }
            printf("\n");
        }
        printf("\n");
}


int main(int argc, char *argv[]){
    double x = 0;
    double y = 0;
    double t = 0;
    int N_x = 5;
    int N = 5;
    double h = 1./(double)(N_x-1);
    double tau = 1./(double)N;
    int G = 1;

    double *Umatrix;
    double *Dmatrix;
    double *Cmatrix;
    double *LastLayer;

    double *netmemory;
    double *fmemory;
    double *net;
    double *umemory;
    double *phimemory;

    double *uijn;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\nN_x N\n");
        printf("N_x for x and y\n N for time\n");
        return -1;
    }

    N_x = atoi(argv[1]);
    N = atoi(argv[2]);

        if (N < 3 || N_x < 3)
    {
        printf("Wrong parameters, must be:\n");
        printf("N >= 3 M >= 3\n");
        return -1;
    }

    h = 1./(double)(N_x-1);
    tau = 1./(double)N;

    Umatrix   = (double *)malloc(N_x * N_x * sizeof(double));
    Dmatrix   = (double *)malloc(N_x * N_x * sizeof(double));
    Cmatrix   = (double *)malloc(N_x * N_x * sizeof(double));
    LastLayer = (double *)malloc(N_x * N_x * sizeof(double));
    uijn      = (double *)malloc(N_x * N_x * N * sizeof(double));

    for(int i = 0; i < N_x * N_x; i++){
        Umatrix[i] = 0; 
        Dmatrix[i] = 0; 
        Cmatrix[i] = 0; 
        LastLayer[i] = 0;
    }
    for(int i = 0; i < N * N_x * N_x; i++)
        uijn[i] = 0;
    

    netmemory = (double *)malloc((N_x + 5) * sizeof(double));
    fmemory   = (double *)malloc((N_x + 5) * sizeof(double));
    net       = (double *)malloc((N_x + 5) * sizeof(double));
    umemory   = (double *)malloc((N_x + 5) * sizeof(double));
    phimemory = (double *)malloc((N_x + 5) * sizeof(double));

    h = 1./(double)(N_x-1);
    tau = 1./(double)N;
    
    FindFourierCoefs(Umatrix, Dmatrix, uijn, N_x, fmemory, net, u0, netmemory, umemory, phimemory);
    
    
    for (int G = 1; G < N; G++)
    {
        // printf("D from f: \n");
        Dfromf(f, h, tau, G, Umatrix, Dmatrix, Cmatrix, fmemory, netmemory, umemory, phimemory);
        // printf("%lf ", Cmatrix[e(2, 2, N_x)]);
        // printf("Answer %d layer: \n", G);
        CFromDandLayer(uijn + G * N_x * N_x, Cmatrix, uijn + (G - 1) * N_x * N_x, h, tau);
        // printMatrix(uijn + G * N_x * N_x, N_x);

                }

    // printf("h=%lf tau=%lf\n\n", h, tau);
    // for(int n = 1; n < N ; n++){
    //     for(int i = 1; i < N_x + 1; i++){
    //         for(int j = 1; j < N_x + 1; j++){
    //             printf("%lf ", uijn[c(i, j, n, N_x)]);
    //             }
    //             printf("\n");
    //         }
    //         printf("\n");
    //     }
    // printf("\n");

    for(int n = 1; n < N ; n++){
            printf("%lf ", uijn[c(2, 2, n, N_x)]);
        }
    printf("\n");


    // for(int j = 0; j < N; j++)
    // {
    //     printf("%lf ", uijn[e(2, 3, N_x) + j * N_x * N_x]);
    // }
    // printf("\n");

    // for(int j = 0; j < N; j++)
    // {
    //     printf("%lf ", uijn[e(3, 2, N_x) + j * N_x * N_x]);
    // }
    // printf("\n");
    // for(int j = 0; j < N; j++)
    // {
    //     printf("%lf ", uijn[e(3, 3, N_x) + j * N_x * N_x]);
    // }
    // printf("\n");


    free(Umatrix);
    free(Dmatrix);
    free(Cmatrix);
    free(LastLayer);

    free(netmemory);
    free(fmemory);
    free(net);
    free(umemory);
    free(phimemory);

    free(uijn);

    return 0;
}
