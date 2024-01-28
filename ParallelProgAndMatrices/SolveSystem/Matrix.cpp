#include "Matrix.hpp"

double max(double a, double b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

double f(int k, int n, int i, int j)
{
	switch (k)
	{
	case 1:
		return (n - max(i, j) + 1);
		break;

	case 2:
		return max(i, j);
		break;

	case 3:
		return abs(i - j);
		break;

	case 4:
		return 1 / (1 + i + j);
		break;

	default:
		break;
	}
	return 0;
}

long double Matrix::norm()
{
	long double sum = 0;
	long double summax = 0;

	for (int i = 1; i <= _N; i++)
	{
		for (int j = 1; j <= _N; j++)
		{
			sum += abs(_value[e(i, j, _N)]);
		}
		if (sum > summax)
		{
			summax = sum;
		}
	}
	return summax;
}

Matrix::Matrix(int N) : _N(N), _value(new double[N * N])
{
	if (N <= 0)
	{
		throw "Matrix::Matrix - size <=0";
	}
	for (int k = 0; k < N * N; k++)
	{
		this->_value[k] = 0;
	}
}

Matrix::~Matrix()
{
	delete[] _value;
	_N = 0;
}

int Matrix::fillFile(std::string filename)
{

	std::ifstream in(filename);

	if (!in.is_open())
	{
		return -2;
	}

	for (int i = 0; i < _N * _N; i++)
	{
		if (!in.eof())
		{
			if (!(in >> _value[i]))
			{
				std::cout << "Matrix::fillFile - incorrect data in the file\n";
				return -1;
			}
		}
		else
		{
			std::cout << "Matrix::fillFile - incorrect data in the file\n";
			return -3;
		}
	}
	return 0;
}

void Matrix::print() const
{
	for (int k = 0; k < _N * _N; k++)
	{
		if (k % _N == 0)
		{
			std::cout << std::endl;
		}
		std::cout << _value[k] << " ";
	}
	std::cout << std::endl;
}

int Matrix::fillFormula(int k)
{
	if (k != 1 && k != 2 && k != 3 && k != 4)
	{
		throw "incorrect par for Matrix::fillFormula";
	}
	for (int i = 1; i <= _N; i++)
	{
		for (int j = 1; j <= _N; j++)
		{
			_value[e(i, j, _N)] = f(k, _N, i, j);
		}
	}
	return 0;
}

void print(int n, double *M, double *b, int m)
{
	for (int i = 1; i <= n; i++)
	{
		if (i < m + 1)
		{
			for (int j = 1; j <= n + 1; j++)
			{
				if (j < m + 1)
				{
					std::cout << M[e(i, j, n)] << " ";
				}
			}
			std::cout << "||    " << b[i - 1] << std::endl;
		}
	}
	std::cout << std::endl;
}