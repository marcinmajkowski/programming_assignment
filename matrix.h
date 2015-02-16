/**
 * @file matrix.h
 * @brief Header file containing Matrix template class definition and its
 * implementation.
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "vector.h"  //we use Vector in Matrix implementation

// g++ compiler requires this approach
// (http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Making_New_Friends)

template <typename T>
class Matrix;

template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& m);

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, Matrix<T>& m);

template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const Matrix<T>& m);

/**
 * @brief Template class meant to represent a 2-dimensional matrix of objects of
 * user specified type.
 */
template <typename T>
class Matrix {
protected:
    /**
     * @brief Vector used to store the matrix elements.
     */
    Vector<T> v;

    /**
     * @brief Number of rows of the matrix.
     */
    int nrows;

    /**
     * @brief Number of columns of the matrix.
     */
    int ncols;

public:
    // CONSTRUCTORS
    /**
     * @brief Default constructor, uses default constructor for v.
     */
    Matrix();

    /**
     * @brief Alternate constructor.
     * @param Nrows Number of rows.
     * @param Ncols Number of columns.
     *
     * Constructs a Matrix of given size.
     * It throws an exception when given negative index.
     */
    Matrix(int Nrows, int Ncols);

    /**
     * @brief Build a matrix from a vector.
     * @param v Vector.
     *
     * Builded Matrix has one column and number of rows equal to the size of the
     * Vector.
     */
    Matrix(const Vector<T>& v);

    /**
     * @brief Copy constructor.
     * @param m Matrix.
     *
     * This constructor copies data from Matrix m to newly allocated memory.
     */
    Matrix(const Matrix<T>& m);

    // ACCESSOR METHODS
    /**
     * @brief Get the number of rows.
     * @return Number of rows.
     */
    int getNrows() const;

    /**
     * @brief Get the number of columns.
     * @return Number of columns.
     */
    int getNcols() const;

    // OVERLOADED FUNCTION CALL OPERATORS
    /**
     * @brief Function call overload (-,-) for assignment.
     * @param i Column.
     * @param j Row.
     * @return Value stored in row i and column j.
     *
     * It throws an exception when given out of range index.
     */
    T& operator()(int i, int j);

    /**
     * @brief Function call overload (-,-) for read.
     * @param i Column.
     * @param j Row.
     * @return Reference to value stored in row i and column j.
     *
     * It throws an exception when given out of range index.
     */
    T operator()(int i, int j) const;

    /**
     * @brief Overloaded assignment operator.
     * @param m Right-side operand matrix.
     * @return Left-side operand.
     */
    Matrix<T>& operator=(const Matrix<T>& m);

    /**
     * @brief Overloaded comparison operator.
     * @param m Right-side operand matrix.
     * @return True only if two matrices are the same.
     */
    bool operator==(const Matrix<T>& m) const;

    // KEYBOARD/SCREEN INPUT AND OUTPUT
    /**
     * @brief Overloaded stream input operator for keyboard input.
     * @param is Input stream reference (e.g. std::cin).
     * @param m Right-side operand Matrix reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. std::cin >> m1 >> m2 >> m3;).
     */
    friend std::istream& operator>><>(std::istream& is, Matrix<T>& m);

    /**
     * @brief Overloaded stream output operator for screen output.
     * @param os Output stream reference (e.g. std::cout).
     * @param m Right-side operand Matrix reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. std::cout << m1 << m2 << m3;).
     */
    friend std::ostream& operator<<<>(std::ostream& os, const Matrix<T>& m);

    // FILE INPUT AND OUTPUT
    /**
     * @brief Overloaded file input operator.
     * @param ifs Input file stream reference.
     * @param m Right-side operand Matrix reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. ifs >> m1 >> m2 >> m3;).
     *
     * The file input operator is compatible with file output operator,
     * ie. everything written can be read later.
     */
    friend std::ifstream& operator>><>(std::ifstream& ifs, Matrix<T>& m);

    /**
     * @brief Overloaded file output operator.
     * @param ofs Output file stream reference.
     * @param m Right-side operand Matrix reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. ofs << m1 << m2 << m3;).
     *
     * The file output operator is compatible with file input operator,
     * ie. everything written can be read later.
     */
    friend std::ofstream& operator<<<>(std::ofstream& ofs, const Matrix<T>& m);
};

// Note: There is no strict need for a copy constructor or
// assignment operator in the Matrix class since the
// compiler versions of these methods will work OK. It will copy/assign
// the values of nrows and ncols and call the Vector copy
// constructor/assignment operator automatically for the
// Vector part v inside the Matrix. However they are written
// for clarity and understanding

// CONSTRUCTORS
// Default constructor (empty matrix)
template <typename T>
Matrix<T>::Matrix()
    : v(0), nrows(0), ncols(0)
{
}

// Alternate constructor - creates a matrix with the given values
template <typename T>
Matrix<T>::Matrix(int Nrows, int Ncols)
{
    // check input
    if (Nrows < 0 || Ncols < 0)
        throw std::invalid_argument("matrix size negative");
    nrows = Nrows;
    ncols = Ncols;
    // if rownumber <= 0 or colnumber <= 0 then the program creates a 0-sized
    // vector
    if (nrows <= 0 || ncols <= 0)
        v = Vector<T>(0);  // empty matrix, nothing to allocate
    else
        v = Vector<T>(nrows * ncols);
}

// Alternate constructor - creates a matrix from a vector
template <typename T>
Matrix<T>::Matrix(const Vector<T>& x)
    : v(x), nrows(x.size()), ncols(1)
{
}

// Copy constructor
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m)
    : v(m.v), nrows(m.getNrows()), ncols(m.getNcols())
{
}

// ACCESSOR METHODS
// Get back matrix rows
template <typename T>
int Matrix<T>::getNrows() const
{
    return nrows;
}

// Get back matrix cols
template <typename T>
int Matrix<T>::getNcols() const
{
    return ncols;
}

// OVERLOADED FUNCTION CALL OPERATORS
// Operator() - returns with a specified value of matrix for write
template <typename T>
T& Matrix<T>::operator()(int i, int j)
{
    if (i > nrows - 1 || j > ncols - 1 || i < 0 || j < 0)
        throw std::out_of_range("matrix access error");
    return v[i * ncols + j];
}

// Operator() - returns with a specified value of matrix for read
template <typename T>
T Matrix<T>::operator()(int i, int j) const
{
    // if the given parameters (coordinates) are out of range
    if (i > nrows - 1 || j > ncols - 1 || i < 0 || j < 0)
        throw std::out_of_range("matrix access error");
    return v[i * ncols + j];
}

// Operator= - assignment
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m)
{
    nrows = m.nrows;
    ncols = m.ncols;

    v = m.v;

    return *this;
}

// equiv - comparison function, returns true if the given matrices are the same
template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& a) const
{
    // if the sizes do not match return false
    if ((nrows != a.nrows) || (ncols != a.ncols))
        return false;

    // compare all of the elements
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if ((*this)(i, j) != a(i, j))
                return false;
        }
    }

    return true;
}

// INPUT AND OUTPUT
// keyboard input , user friendly
template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& m)
{
    int nrows, ncols;
    if (!m.nrows) {
        std::cout << "input the number of rows for the matrix" << std::endl;
        is >> nrows;
        std::cout << "input the number of cols for the matrix" << std::endl;
        is >> ncols;
        // check input
        if (nrows < 0 || ncols < 0)
            throw std::invalid_argument("read error - negative matrix size");

        // prepare the matrix to hold n elements
        m = Matrix<T>(nrows, ncols);
    }
    // input the elements
    std::cout << "input " << m.nrows* m.ncols << " matrix elements"
              << std::endl;
    for (int i = 0; i < m.nrows * m.ncols; i++)
        is >> m.v[i];
    // return the stream object
    return is;
}

// screen output, user friendly
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
{
    if (&m.v) {
        os << "The matrix elements are" << std::endl;
        for (int i = 0; i < m.nrows; i++) {
            for (int j = 0; j < m.ncols; j++) {
                os << m(i, j) << " ";
            }
            os << "\n";
        }
        os << std::endl;
    }
    else {
        os << "Matrix is empty." << std::endl;
    }
    return os;
}

// file input - raw data, compatible with file writing operator
template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, Matrix<T>& m)
{
    int nrows, ncols;

    // read size from the file
    ifs >> nrows;
    ifs >> ncols;
    // check input sanity
    if (nrows < 0 || ncols < 0)
        throw std::invalid_argument("file read error - negative matrix size");

    // prepare the vector to hold n elements
    m = Matrix<T>(nrows, ncols);

    // input the elements
    for (int i = 0; i < nrows * ncols; i++)
        ifs >> m.v[i];

    // return the stream object
    return ifs;
}

// file output - raw data, comaptible with file reading operator
template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const Matrix<T>& m)
{
    // put matrix rownumber in first line (even if it is zero)
    ofs << m.nrows << std::endl;
    // put matrix columnnumber in second line (even if it is zero)
    ofs << m.ncols << std::endl;
    // put data in third line (if size==zero nothing will be put)
    for (int i = 0; i < m.nrows; i++) {
        for (int j = 0; j < m.ncols; j++)
            ofs << m(i, j) << " ";
        ofs << std::endl;
    }
    return ofs;
}

#endif /* MATRIX_H */
