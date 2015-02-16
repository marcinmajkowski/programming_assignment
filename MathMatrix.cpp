#include "MathMatrix.h"
#include <cmath>

// CONSTRUCTORS
MathMatrix::MathMatrix() : Matrix<double>(), n(0) {} // default constructor

MathMatrix::MathMatrix(int n) : Matrix<double>(n, n), n(n) {} // alternate constructor

// METHODS SPECIFIC FOR SQUARE MATRIX OF DOUBLES

int MathMatrix::get_size() const // return size of matrix
{
    return nrows;   
}

double MathMatrix::one_norm() const // 1-norm of a matrix
{
    // the maximum absolute column sum of the matrix
    int i, j;

    double res = 0;
    double sum = 0;
    
    for (j = 0; j < ncols; ++j) // for each columnn
    {
        sum = 0;
        for (i = 0; i < nrows; ++i)
            sum += fabs((*this)(i, j));

        if (sum > res) // store the biggest sum
            res = sum;
    }

    return res;
}

double MathMatrix::two_norm() const // 2-norm of a matrix
{
    // the Frobenius norm
    // the square root of the sum of the absolute squares of all matrix elements
    int i, j;

    double res = 0;

    for (i = 0; i < nrows; ++i)
        for (j = 0; j < ncols; ++j)
            res += (*this)(i, j) * (*this)(i, j);   // fabs() not necessary since
                                                    // there are only double values
    return sqrt(res);
}

double MathMatrix::uniform_norm() const // uniform norm of a matrix 
{
    // the maximum absolute row sum of the matrix
    int i, j;

    double res = 0;
    double sum = 0;
    
    for (i = 0; i < nrows; ++i) // for each row
    {
        sum = 0;
        for (j = 0; j < ncols; ++j)
            sum += fabs((*this)(i, j));

        if (sum > res) // store the biggest sum
            res = sum;
    }

    return res;
}

// overloaded matrix by matrix multiplication
MathMatrix MathMatrix::operator*(const MathMatrix& a) const
{
    if (nrows != a.nrows)
        throw std::invalid_argument("incompatible matrix sizes");

    int i, j, k;

    MathMatrix res(nrows);
    
    for (i = 0; i < nrows; ++i)
        for (j = 0; j < ncols; ++j)
            for (k = 0; k < ncols; ++k)
                res(i, j) += (*this)(i, k) * a(k, j);

    return res;
}

// overloaded multiplication of matrix by a vector
MathVector MathMatrix::operator*(const MathVector& v) const
{
    if (nrows != v.size())
        throw std::invalid_argument("incompatible matrix sizes");

    int i, j;

    MathVector res(nrows);

    for (i = 0; i < nrows; ++i)
        for (j = 0; j < ncols; ++j)
            res[i] += (*this)(i, j) * v[j];
    
    return res;
}

// compute the lower triangular form, L, in the LU 
// factorisation
MathMatrix MathMatrix::compute_lower() const
{
    MathMatrix l, u;

    lu_fact(*this, l, u, nrows);

    return l;
}

// compute the upper triangular form, U, in the LU 
// factorisation
MathMatrix MathMatrix::compute_upper() const
{
    MathMatrix l, u;

    lu_fact(*this, l, u, nrows);

    return u;
}

// compute the inverse matrix
MathMatrix MathMatrix::inverse() const
{
    // Finding the inverse of a matrix using LU factorisation

    int i, j, k;

    // call the function reorder to generate a pivoting (permutation) matrix P
    MathMatrix p;
    reorder(*this, nrows, p);

    // Find the LU factorisation of PA using the function lu_fact
    MathMatrix l, u;
    lu_fact(*this, l, u, nrows);

    // Finding inverse of L and U
    MathMatrix l_inv(nrows), u_inv(nrows);
    MathVector e(nrows), temp(nrows);
    for (k = 0; k < nrows; ++k)
    {
        // ek = (0 ... 0 1 0 ... 0) with 1 in the kth position and zero elsewhere.
        e[k] = 1;
        if (k > 0)
            e[k - 1] = 0;

        // the inverse of L and U are formed from the solution vectors as
        // successive columns of the inverse matrices

        // forward substitution for L y = e.
        // temp begins with a copy of e.
        temp = e;
        for (i = 1; i < nrows; ++i)
            for (j = 0; j < i; ++j)
                temp[i] -= l(i, j) * temp[j];

        for (i = 0; i < nrows; ++i)
            l_inv(i, k) = temp[i];

        // back substitution for U y = e.
        // temp begins with a copy of e.
        temp = e;
        for (i = nrows - 1; i >= 0; --i)
        {
            for (j = i + 1; j < nrows; ++j)
                temp[i] -= u(i, j) * temp[j];
            temp[i] /= u(i, i);
        }

        for (i = 0; i < nrows; ++i)
            u_inv(i, k) = temp[i];
    }

    return u_inv * l_inv * p;
}

// compute the condition number of the matrix 
double MathMatrix::condition_num() const
{
    // using one norm
    return (*this).inverse().one_norm() * (*this).one_norm();
}

// LU FACTORISATION ROUTINE
// Takes in a matrix a of size n and produces the lower (l) and
// upper (u) triangular matrices that factorise a 

void lu_fact(const MathMatrix& a, MathMatrix& l, MathMatrix& u, int n)
{
    double mult;
    MathMatrix temp = a; //copy a to temp
    int i, j, k;

    l = MathMatrix(n);
    u = MathMatrix(n);
    
	// LU (Doolittle's) decomposition without pivoting
	for (k = 0; k < n - 1; k++)
    {
		for (i = k + 1; i < n; i++)
        {
			if (temp(k,k) == 0)
			{ 
				printf("pivot is zero\n"); 
				exit(1);
			}
			mult = temp(i, k) / temp(k, k);
			temp(i, k) = mult;                      // entries of L are saved in temp
			for (j = k + 1; j < n; j++)
				temp(i, j) -= mult*temp(k, j);      // entries of U are saved in temp
		}
	}

	// create l and u from temp
	for (i = 0; i < n; i++)
        l(i, i) = 1.0;
	for (i = 1; i < n; i++) 
	  for (j = 0; j < i; j++)
        l(i, j) = temp(i, j);

	for (i = 0; i < n; i++)
		for (j = i; j < n; j++)
            u(i, j) = temp(i, j);
}

/*
* Solves the equation LUx = b by performing forward and backward
* substitution. Output is the solution vector x
*/
void lu_solve(const MathMatrix& l, const MathMatrix& u, const MathVector& b,
        int n, MathVector& x)
{
	int i,j; 
	MathVector temp = b; // copy b to temp
    
	// forward substitution for L y = b.
	for (i = 1; i < n; i++) 
		for (j = 0; j < i; j++) 
			temp[i] -= l(i, j)*temp[j];
  
	// back substitution for U x = y.  
	for (i = n - 1; i >= 0; i--)
    {
		for (j = i + 1; j < n; j++)
            temp[i] -= u(i, j) * temp[j];
		temp[i] /= u(i, i);
	}

	// copy solution into x
	x = temp;
}

void reorder(const MathMatrix& a, int n, MathMatrix& p)
{
// Note: pivoting information is stored in temperary vector pvt

	int i,j,k;
	MathVector pvt(n);
	int pvtk, pvti;
	MathVector scale(n);
	double aet, tmp, mult;
	MathMatrix temp = a; // copy a into temp
    p = MathMatrix(n);

	for (k = 0; k < n; k++)
        pvt[k] = k;

    // find scale vector
	for (k = 0; k < n; k++)
    {
		scale[k] = 0;
		for (j = 0; j < n; j++) 
			if (fabs(scale[k]) < fabs(temp(k, j))) 
                scale[k] = fabs(temp(k, j));
	} 

	for (k = 0; k < n - 1; k++)
    {            // main elimination loop

	// find the pivot in column k in rows pvt[k], pvt[k+1], ..., pvt[n-1]
		int pc = k; 
		aet = fabs(temp(pvt[k], k) / scale[k]);
		for (i = k + 1; i < n; i++)
        {
			tmp = fabs(temp(pvt[i], k) / scale[pvt[i]]); 
			if (tmp > aet)
            {
				aet = tmp; 
				pc = i;
			}
		}
		if (aet == 0) 
		{ 
			printf("pivot is zero\n"); 
			exit(1); 
		}
		if (pc != k)
        {                      // swap pvt[k] and pvt[pc]
			int ii = pvt[k];
			pvt[k] = pvt[pc];
			pvt[pc] = ii;
		}

		// now eliminate the column entries logically below mx[pvt[k]][k]
		pvtk = pvt[k];                           // pivot row
		for (i = k + 1; i < n; i++)
        {
			pvti = pvt[i];
			if (temp(pvti, k) != 0)
            {
				mult = temp(pvti, k) / temp(pvtk, k); 
				temp(pvti, k) = mult;
				for (j = k + 1; j < n; j++)
                    temp(pvti, j) -= mult * temp(pvtk, j);
			}
		}
	}
	for (i = 0; i < n; i++)
        p(i, pvt[i]) = 1.0;
}

// INPUT & OUTPUT 
std::istream& operator>>(std::istream& is, MathMatrix& m) // keyboard input
{
	if (!m.n)
	{
		std::cout << "input the size for the square matrix" << std::endl;
		int n;
		is >> n;

		if (n < 0) //check input 
			throw std::invalid_argument("read error - negative matrix size");

		m = MathMatrix(n); // prepare the matrix to hold n elements
	}

	// input the elements
	std::cout << "input " << m.n * m.n << " matrix elements" << std::endl;
	for (int i = 0; i < m.n*m.n; ++i)
		is >> m.v[i];

	return is; // return the stream object
}

//the file output operator is compatible with file input operator,
//ie. everything written can be read later.
std::ifstream& operator>>(std::ifstream& ifs, MathMatrix& m) // file input
{
	int n;
	ifs >> n; // read size from the file

	if (n < 0) //check input sanity
		throw std::invalid_argument("file read error - negative matrix size");

	m = MathMatrix(n); // prepare the matrix to hold n elements

	for (int i = 0; i < n * n; ++i) // input the elements
		ifs >> m.v[i];

	return ifs; // return the stream object
}

std::ofstream& operator<<(std::ofstream& ofs, const MathMatrix& m) // file output
{
	//put square matrix size in first line (even if it is zero)
	ofs << m.n << std::endl;
	//put data in second line (if size==zero nothing will be put)
	for (int i = 0; i < m.n; ++i) 
	{
		for (int j = 0; j < m.n; ++j) 
			ofs << m(i, j) << " ";
		ofs << std::endl;
	}
	return ofs;
}
