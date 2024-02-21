// void f(double * x, double * y, double * ans, int n) 
// {
//     for(int k = 0; k < n; k++)
//         ans[k] = y[k];
    
//     return;
// }

void k1(double * x, double * y, double * ans, int n, 
    double h, void (*function)(double*, double*, double*, int)) 
{
    function(x, y, ans, n);
    for(int k = 0; k < n; k++)
    {
        ans[k] *= h;
    }
    return;
}

void k2(double * x, double * y, double * ans, int n, 
    double h, void (*function)(double*, double*, double*, int), 
    double * mem) 
{
    k1(x, y, ans, n, h, function);
    for(int k = 0; k < n; k++)
    {
        mem[k] = x[k] + h / 3;
        ans[k] = y[k] + ans[k] / 3;
    }
    function(mem, ans, ans, n);
    for(int k = 0; k < n; k++)
        ans[k] *= h;
    return;
}

void k3(double * x, double * y, double * ans, int n, 
    double h, void (*function)(double*, double*, double*, int), 
    double * mem, double * mem1) 
{
    k1(x, y, ans, n, h, function);
    k2(x, y, mem, n, h, function, mem1);
    for(int k = 0; k < n; k++)
    {
        mem1[k] = x[k] + h / 3;
        mem[k] = y[k] + (ans[k] + mem[k]) / 6;
    }

    function(mem1, mem, ans, n);
    for(int k = 0; k < n; k++)
        ans[k] *= h;
    return;
}

void k4(double * x, double * y, double * ans, int n, 
    double h, void (*function)(double*, double*, double*, int), 
    double * mem, double * mem1, double * mem2) 
{
    k3(x, y, mem, n, h, function, mem1, mem2);
    k1(x, y, mem1, n, h, function);
    for(int k = 0; k < n; k++)
    {
        mem1[k] = y[k] + (mem1[k] + 3 * mem[k]) / 8;
        mem[k] = x[k] + h / 2;
    }

    function(mem, mem1, ans, n);
    for(int k = 0; k < n; k++)
        ans[k] *= h;
    return;
}

void k5(double * x, double * y, double * ans, int n, 
    double h, void (*function)(double*, double*, double*, int), 
    double * mem, double * mem1, double * mem2) 
{
    k4(x, y, mem, n, h, function, mem1, mem2, ans);
    k3(x, y, mem1, n, h, function, ans, mem2);
    k1(x, y, mem2, n, h, function);
    for(int k = 0; k < n; k++)
    {
        mem1[k] = y[k] + 0.5 * mem2[k] -1.5 * mem1[k] + 2 * mem[k];
        mem[k] = x[k] + h;
    }

    function(mem, mem1, ans, n);
    for(int k = 0; k < n; k++)
        ans[k] *= h;
    return;
}

void yNext(double * x0, double * y0, double * ans, int n, 
    double h, void (*function)(double*, double*, double*, int), 
    double * mem, double * mem1, double * mem2, double * mem3) 
{
    k5(x0, y0, mem, n, h, function, mem1, mem2, ans);
    k4(x0, y0, mem1, n, h, function, mem2, mem3, ans);
    k1(x0, y0, mem2, n, h, function);

    for(int k = 0; k < n; k++)
    {
        ans[k] = y0[k] + (mem2[k] + 4 * mem1[k] + mem[k]) / 6;
    }

    return;
}