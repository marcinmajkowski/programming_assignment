#include "MathVector.h"
#include <cmath>

// CONSTRUCTORS
// default constructor (empty vector)
MathVector::MathVector() : Vector<double>() {}

// alternate constructor
MathVector::MathVector(int n) : Vector<double>(n) {}

double MathVector::one_norm() const
{
	if (!num) throw std::invalid_argument("incompatible vector size\n"); 

	double res = 0;

	for (int i = 0; i < num; ++i)
		res += fabs(pdata[i]);

	return res;
}

double MathVector::two_norm() const
{
	if (!num) throw std::invalid_argument("incompatible vector size\n"); 

	double res = 0;

	for (int i = 0; i < num; ++i)
		res += pdata[i] * pdata[i];

	return sqrt(res);
}

double MathVector::uniform_norm() const
{
	if (!num) throw std::invalid_argument("incompatible vector size\n"); 

	double res = fabs(pdata[0]);

	for (int i = 1; i < num; ++i)
		if (fabs(pdata[i]) > res) res = fabs(pdata[i]);

	return res;
}
