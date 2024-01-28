#include <chrono>
#include "QRRefl.hpp"


double sum(double *array, int len, int mode, int startindex)
{
    double s = 0;
    if (len <= 0 || mode < 1 || mode > 2 || startindex < 0 || startindex > 1) return -1;

    if (mode == 1) for (int k = startindex; k < len + startindex; ++k) s += array[k];

    if (mode == 2) for (int k = startindex; k < len + startindex; ++k) s += array[k] * array[k];

    return s;
}

int main(int nargs, char **args)
{
    
    if (nargs < 4)
    {
        std::cout << "4 or 5 args needed" << std::endl;
        return -1;
    }
    int n, m, k;
    double epsans;
    char *filename = new char[128];

    if (sscanf(args[1], "%d", &n) != 1 || sscanf(args[2], "%d", &m) != 1 ||
        sscanf(args[4], "%d", &k) != 1 || sscanf(args[3], "%lf", &epsans) != 1)
    {
        std::cout << "bad params" << std::endl;
        return -1;
    }

    if(n <= 0 || m <= 0 || epsans <= 0) 
    {
        std::cout << "bad params" << std::endl;
        return -1;
    }

    try
    {
        Matrix A(n);
        Matrix B(n);
        vector x(n);
        if (k == 0)
        {
            if (args[5] == nullptr || sscanf(args[5], "%s", filename) != 1)
            {
                std::cout << "No filename" << std::endl;
                return -1;
            }

            int res_code = A.fillFile(std::string(filename));
            B.fillFile(std::string(filename));

            if (res_code < 0)
            {
                std::cout << "Cant open file" << std::endl;
                return -2;
            }
        }

        if (k == 1 || k == 2 || k == 3 || k == 4)
        {
            A.fillFormula(k);
            B.fillFormula(k);
        }
        if (k < 0 || k > 4)
        {
            std::cout << "incorrect k\n";
        }

        print(n, B._value, m);

        double *memory1 = new double[2*n];
        double *memory2 = new double[2*n];
        double *memory3 = new double[2*n];
        double *answer = new double[2*n];

        auto start = std::chrono::high_resolution_clock::now();
        int res = Eignvalues(A._value, memory1, memory2, memory3, answer, n, epsans);
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "res: " << res << std::endl; 
        
        if (res < 0)
        {
            std::cout << "Something bad happend. We are not sure about values" << std::endl;
        }
        else
        {
            std::cout << "Norm 1: " << abs(sum(answer, n, 1, 1) - trace(B._value, B._N)) << std::endl;
            std::cout << "Norm 2: " << abs(sum(answer, n, 2, 1) - sqrt(sum(B._value, n*n, 2, 0))) << std::endl;
            std::cout << "Ans: ";
            for(int k = 1; k < n + 1; ++k) {
                std::cout << answer[k] << " ";
            }
            std::cout << std::endl;
        }

        std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Calculation time: " << int(duration.count() / 1000000) << "." << duration.count() % 1000000 << " seconds\n";
        delete[] memory1;
        delete[] memory2;
        delete[] memory3;
        delete[] answer;
        delete[] filename;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -3;
    }
    return 0;
}