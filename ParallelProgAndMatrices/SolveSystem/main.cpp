#include <chrono>

#include "vector.hpp"
#include "GausMethod.hpp"

int main(int nargs, char **args)
{
    
    if (nargs < 4)
    {
        std::cout << "3 or 4 args needed" << std::endl;
        return -1;
    }
    int n, m, k;
    char *filename = new char[128];

    if (sscanf(args[1], "%d", &n) != 1 || sscanf(args[2], "%d", &m) != 1 ||
        sscanf(args[3], "%d", &k) != 1)
    {
        std::cout << "bad params" << std::endl;
        delete [] filename;
        return -1;
    }

    if(n <= 0 || m <= 0) 
    {
        delete [] filename;
        std::cout << "bad params" << std::endl;
        return -1;
    }

    try
    {
        Matrix A(n);
        vector x(n);
        if (k == 0)
        {
            if (args[4] == nullptr || sscanf(args[4], "%s", filename) != 1)
            {
                delete [] filename;
                std::cout << "No filename" << std::endl;
                return -1;
            }

            int res_code = A.fillFile(std::string(filename));

            if (res_code < 0)
            {
                delete [] filename;
                std::cout << "Cant open file" << std::endl;
                return -2;
            }
        }

        if (k == 1 || k == 2 || k == 3 || k == 4)
        {
            A.fillFormula(k);
        }
        if (k < 0 || k > 4)
        {
            std::cout << "incorrect k\n";
            delete [] filename;
            return -1;
        }
        vector b(A);

        print(n, A._value, b.vector_, m);

        int *memory = new int[n];
        vector One(n);
        for (int k = 0; k < n; ++k)
        {
            One.vector_[k] = (k + 1) % 2;
        }
        auto start = std::chrono::high_resolution_clock::now();
        int res = solve(n, A._value, b.vector_, x.vector_, memory);
        auto stop = std::chrono::high_resolution_clock::now();
        if (res == -1)
        {
            std::cout << "det A = 0" << std::endl;
        }
        else
        {
            std::cout << "Norm: " << ((A * x) - One).norm() / b.norm() << std::endl;
            std::cout << "Norm(Ans-x): " << (x - One).norm() << std::endl;
            std::cout << "Answer: ";
            x.print(m);
        }

        std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Calculation time: " << int(duration.count() / 1000000) << "." << duration.count() % 1000000 << " seconds\n";
        delete[] memory;
        delete[] filename;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -3;
    }
    
    return 0;
}