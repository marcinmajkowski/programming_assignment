/**
 * @file MathMatrix.h
 * @brief Header file containing MathMatrix class definition.
 */
#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include "Matrix.h"
#include "MathVector.h"

/**
 * @brief Class meant to represent a square matrix of double values.
 *
 * This class is derived from Matrix template class.
 */
class MathMatrix : public Matrix<double> {
private:
    int n;  // Size of the square matrix.

public:
    /**
     * @brief A default constructor.
     */
    MathMatrix();

    /**
     * @brief An alternate consturctor.
     * @param n Size of the square matrix.
     *
     * Constructs a square matrix of given size n. It is explicit since implicit
     * type conversion int to MathMatrix doesn't make sense.
     */
    explicit MathMatrix(int n);

    /**
     * @brief Returns size of a matrix.
     * @return Size of a matrix.
     */
    int get_size() const;

    /**
     * @brief Returns 1-norm of a matrix.
     * @return 1-norm of a matrix.
     */
    double one_norm() const;

    /**
     * @brief Returns 2-norm of a matrix.
     * @return 2-norm of a matrix.
     */
    double two_norm() const;

    /**
     * @brief Returns uniform norm of a matrix.
     * @return Uniform norm of a matrix.
     */
    double uniform_norm() const;

    /**
     * @brief Overloaded matrix by matrix multiplication.
     * @param a Matrix to multiply object with.
     * @return Matrix by matrix multiplication result.
     *
     * This calculates a matrix product.
     */
    MathMatrix operator*(const MathMatrix& a) const;

    /**
     * @brief Overloaded matrix by vector multiplication.
     * @param v Vector to multiply object with.
     * @return Matrix by vector multiplication result.
     *
     * This calculates a matrix product.
     */
    MathVector operator*(const MathVector& v) const;

    /**
     * @brief Compute the lower triangular form, L, in the LU factorisation.
     * @return Lower triangular matrix L.
     *
     * If both L and U matrices are needed, better use lu_fact() function.
     */
    MathMatrix compute_lower() const;

    /**
     * @brief Compute the upper triangular form, U, in the LU factorisation.
     * @return Upper triangular matrix U.
     *
     * If both L and U matrices are needed, better use lu_fact() function.
     */
    MathMatrix compute_upper() const;

    /**
     * @brief Compute the inverse matrix.
     * @return Inverse matrix.
     */
    MathMatrix inverse() const;

    /**
     * @brief Compute the condition number of the matrix.
     * @return Condition number.
     *
     * Condition number is calculated using one-norm.
     */
    double condition_num() const;

    // KEYBOARD INPUT
    /**
     * @brief Overloaded stream input operator for keyboard input.
     * @param is Input stream reference (e.g. std::cin).
     * @param m Right-side operand MathMatrix reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. std::cin >> m1 >> m2 >> m3;).
     */
    friend std::istream& operator>>(std::istream& is, MathMatrix& m);

    // FILE INPUT AND OUTPUT
    /**
     * @brief Overloaded file input operator.
     * @param ifs Input file stream reference.
     * @param m Right-side operand MathMatrix reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. ifs >> m1 >> m2 >> m3;).
     *
     * The file input operator is compatible with file output operator,
     * ie. everything written can be read later.
     */
    friend std::ifstream& operator>>(std::ifstream& ifs, MathMatrix& m);

    /**
     * @brief Overloaded file output operator.
     * @param ofs Output file stream reference.
     * @param m Right-side operand MathMatrix reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. ofs << m1 << m2 << m3;).
     *
     * The file output operator is compatible with file input operator,
     * ie. everything written can be read later.
     */
    friend std::ofstream& operator<<(std::ofstream& ofs, const MathMatrix& m);
};

// Doolittle's factorisation (based on lu.c)
/**
 * @brief LU factorisation routine.
 * @param a Input matrix reference.
 * @param l Reference to MathMatrix for storing lower triangular matrix.
 * @param u Reference to MathMatrix for storing upper triangular matrix.
 * @param n Size of a matrix a.
 *
 * Takes in a matrix of a size n and produces the lower (l) and upper (u)
 * triangular matrices that factorise a.
 */
void lu_fact(const MathMatrix& a, MathMatrix& l, MathMatrix& u, int n);

/**
 * @brief Solves the equation LUx = b by performing forward and backward
 * substitution.
 * @param l Lower triangular matrix.
 * @param u Upper triangular matrix.
 * @param b Vector b.
 * @param n Size of a matrix a.
 * @param x Reference to MathVector for storing resultant vector x.
 *
 * Output is the solution vector x
 */
void lu_solve(const MathMatrix& l, const MathMatrix& u, const MathVector& b,
              int n, MathVector& x);

/**
 * @brief Computes the permutation matrix P.
 * @param a Input matrix reference.
 * @param n Size of a matrix a.
 * @param p Reference to MathMatrix for storing resultant matrix p.
 *
 * Matrix P is such that the matrix PA can be factorised into LU and the system
 * PA = Pb can be solved by forward and backward substitution. Output is the
 * permutation matrix P.
 */
void reorder(const MathMatrix& a, int n, MathMatrix& p);

#endif /* MATH_MATRIX_H */