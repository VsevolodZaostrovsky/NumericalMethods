#include "Ln.hpp"

#define EPS 1e-12

double mod(double x)
{
    return -x * (x < 0) + x * (x > 0);
}

Ln::Ln(int N, double * knots, double * meanings) : _N(N), _knots(new double[N]), _meanings(new double[N])
{
	if (N <= 0)
	{
		throw "Ln::Ln - size <= 0";
	}
	for (int k = 0; k < N; k++)
	{
		this->_knots[k] = knots[k];
        this->_meanings[k] = meanings[k];
	}
}

Ln::Ln(Ln &P) : _N(P._N)
{
	if (this == &P) return;

//    delete [] _coefs;
    _knots = new double[_N];
    _meanings = new double[_N];
	for (int k = 0; k < _N; k++)
	{
		this->_knots[k] = P._knots[k];
        this->_meanings[k] = P._meanings[k];
	}
}

Ln::~Ln()
{
	delete[] _knots;
    delete[] _meanings;
	_N = 0;
}

void Ln::print() const
{
	for (int k = 0; k < _N; k++)
	{
		std::cout << "(" << _knots[k] << "; " << _meanings[k] << ") ";
	}
	std::cout << std::endl;
}

double Ln::Phi(int i, double x) const
{
    double ans = 1;

	for (int j = 0; j < _N; j++) 
    {
		if(j != i) 
        {
            if(mod(_knots[i] - _knots[j]) < EPS) 
            {
                std::cout << _knots[i] << " == " << _knots[j] << " ap " << EPS << '\n';
                throw "bed knot";
            }
            else ans *= (x - _knots[j]) / (_knots[i] - _knots[j]);
        }
//        std::cout << i << "Phi done \n";
    }

	return ans;
}

double Ln::calculate(double x) const
{
    double ans = 0;

	for (int i = 0; i < _N; i++)
    {
		ans += _meanings[i] * this->Phi(i, x); 
//        std::cout << i << "done \n";
    }

	return ans;
}