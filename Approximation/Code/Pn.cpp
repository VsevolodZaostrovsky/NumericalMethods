#include "Pn.hpp"
#include "GaussMethod.cpp"


Pn::Pn(int N, double * coefs) : _N(N), _coefs(new double[N])
{
	if (N <= 0)
	{
		throw "Pn::Pn - size <=0";
	}
	for (int k = 0; k < N; k++)
	{
		this->_coefs[k] = coefs[k];
	}
}

Pn::Pn(Pn &P) : _N(P._N)
{
	if (this == &P) return;

//    delete [] _coefs;
    _coefs = new double[_N];
	for (int k = 0; k < _N; k++)
	{
		this->_coefs[k] = P._coefs[k];
	}
}

Pn::~Pn()
{
	delete[] _coefs;
	_N = 0;
}

void Pn::print() const
{
	for (int k = 0; k < _N; k++)
	{
		std::cout << _coefs[k] << "x^" << k;
        if(k != _N - 1) std::cout << " + ";
        
	}
	std::cout << std::endl;
}

double Pn::calculate(double x) const
{
    double ans = 0;
    double m = 1;
	for (int k = 0; k < _N; k++)
	{
		ans += _coefs[k] * m;
        m *= x;
	}
	return ans;
}


Pn::Pn(int N, double * knots, double * meanings) : _N(N) 
{
	double * M = new double[_N * _N];
	int * memory = new int[_N * 2];
	this->_coefs = new double[_N];

	for(int i = 1; i < _N + 1; i++)
	{
		double m = 1;
		for(int j = 1; j < _N + 1; j++) 
		{
			M[e(i, j, _N)] = m;
			m *= knots[i - 1];
		}
		m = 1;
	}

	if(solve(_N, M, meanings, _coefs, memory) != 0) 
	{
//		throw "Pn::Pn(int N, double * knots, double * meanings) - something bed happend while solving system";
		std::cout << "something bed happend while solving system\n";
		for(int i = 0; i < _N; ++i)
		{
			_coefs[i] = 0;
		}
	}

	delete [] M;
	delete [] memory;
}