/**
 * @file MathVector.h
 * @brief opis pliku
 */
#ifndef MATH_VECTOR_H  // include guard
#define MATH_VECTOR_H

#include "vector.h"

/**
 * @brief Class meant to represent a vector of double values.
 *
 * This class is dervied from Vector template class.
 */
class MathVector : public Vector<double> {
public:
    /**
     * @brief A default constructor.
     */
    MathVector();

    /**
     * @brief An alternate consturctor.
     * @param n Size of the vector.
     *
     * Constructs a vector of given size n. It is explicit since implicit
     * type conversion int to MathMatrix doesn't make sense.
     */
    MathVector(int n);

    /**
     * @brief Returns 1-norm of a vector.
     * @return 1-norm of a vector.
     */
    double one_norm() const;
    /**

     * @brief Returns 2-norm of a vector.
     * @return 2-norm of a vector.
     */
    double two_norm() const;

    /**
     * @brief Returns uniform norm of a vector.
     * @return Uniform norm of a vector.
     */
    double uniform_norm() const;
};

#endif /* MATH_VECTOR_H */
