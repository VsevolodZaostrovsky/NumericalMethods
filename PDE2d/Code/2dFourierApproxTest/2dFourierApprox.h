int GenerateNet(double *net, int N);

void FullUMatrix(double *Umatrix, int N, double *net, double (*u)(double, double));

void FullDMatrix(double *Dmatrix, double *Umatrix, int N, double *umemory, double *phimemory);

void FullCMatrix(double *Dmatrix, double *Cmatrix, int N, double *fmemory, double *umemory, double *phimemory);

double Calc2DFourier(double *Cmatrix, int N, double x, double y);

double FourierCompute(double * coefs, int N, double x);

double Calc2DFourier(double *Cmatrix, int N, double x, double y);

double FullFurierCompute(double x, double y,
        double *Umatrix, double *Dmatrix, double *Cmatrix, int N,
            double *fmemory, double *net, double (*u)(double, double),
                double *netmemory, double *umemory, double *phimemory);

void FindFourierCoefs(double *Umatrix, double *Dmatrix, double *Cmatrix, int N,
                      double *fmemory, double *net, double (*u)(double, double),
                      double *netmemory, double *umemory, double *phimemory);