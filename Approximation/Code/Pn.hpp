#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>

class Pn {
    private:
        int _N;
        double * _coefs;


    public:
        Pn(int N, double * coefs);

        // Строит интерполяционный многочлен с помощью метода Гаусса по поданным узлам и значениям
        // Не эффективен по памяти (аллоцирует O(n^2)), имеет малую вычислительную устойчивость, требует внешний файл "GausMethod.cpp"
        Pn(int N, double * knots, double * meanings); 

        Pn(Pn &P);
        ~Pn();

        void print() const;
        double calculate(double x) const;
};