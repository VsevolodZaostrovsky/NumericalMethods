double u(double x, double y);

void PrintMatrix(double *Matrix, int N);

void WriteSkrypt(int N, char *testfilename, FILE *out);

void WriteResult(double *net, double *Cmatrix, int N, double (*u)(double, double), FILE *out);