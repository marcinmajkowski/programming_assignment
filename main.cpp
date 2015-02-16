#include <iostream>
#include <exception>
#include "vector.h"
#include "matrix.h"
#include "MathVector.h"
#include "MathMatrix.h"
#include "Complex.h"

void error(std::exception& e);

int main()
{
    try {
        // 1) Test the Vector template by writing a main function that
        // declares a vector of 10 complex numbers, inputs the numbers
        // from the keyboard and outputs the vector to the screen.
        std::cout << "Vector part" << std::endl;
        Vector<Complex> vec(10);

        std::cout << "Input 10 complex numbers:" << std::endl;

        for (int i = 0; i < 10; ++i) {
            std::cout << "Input complex number " << i + 1 << std::endl;
            std::cin >> vec[i];
        }

        for (int i = 0; i < 10; ++i)
            std::cout << i + 1 << ".\t" << vec[i] << std::endl;

        // 2) Test the matrix template with a suitable main function
        // that declares a matrix of complex numbers, inputs from
        // keyboard/file and outputs to screen/file.
        std::cout << "Matrix part" << std::endl;
        std::cout << "Input number of rows of the complex numbers matrix:"
                  << std::endl;
        int nrows;
        std::cin >> nrows;
        std::cout << "Input number of columns of the complex numbers matrix:"
                  << std::endl;
        int ncols;
        std::cin >> ncols;
        Matrix<Complex> mat(nrows, ncols);
        std::cout << "Input complex numbers matrix elements:" << std::endl;

        for (int i = 0; i < nrows; ++i)
            for (int j = 0; j < ncols; ++j)
                std::cin >> mat(i, j);

        for (int i = 0; i < nrows; ++i) {
            for (int j = 0; j < ncols; ++j)
                std::cout << mat(i, j) << "\t";
            std::cout << std::endl;
        }

        // test MathVector constructors and methods:
        MathVector mv1, mv2(3);

        mv2[0] = 0.5;
        mv2[1] = 1.5;
        mv2[2] = 2.5;

        mv1 = mv2;

        std::cout << "mv1: " << mv1 << std::endl;
        std::cout << "mv2: " << mv2 << std::endl;
        std::cout << "mv1 one norm: " << mv1.one_norm() << std::endl;
        std::cout << "mv1 two norm: " << mv1.two_norm() << std::endl;
        std::cout << "mv1 uniform norm: " << mv1.uniform_norm() << std::endl;

        // test MathMatrix methods:
        MathMatrix mm;

        std::cin >> mm;

        std::cout << "Matrix A:" << std::endl;
        std::cout << mm;
        std::cout << "Matrix L:" << std::endl;
        std::cout << mm.compute_lower();
        std::cout << "Matrix U:" << std::endl;
        std::cout << mm.compute_upper();
        std::cout << "L * U:" << std::endl;
        std::cout << mm.compute_lower() * mm.compute_upper() << std::endl;
        std::cout << "A inverse:" << std::endl;
        std::cout << mm.inverse() << std::endl;
        std::cout << "A^-1 * A:" << std::endl;
        std::cout << mm.inverse() * mm << std::endl;
        std::cout << "Matrix A condition number:" << std::endl;
        std::cout << mm.condition_num() << std::endl;
    }
    catch (std::exception& e) {
        error(e);
    }

    return 0;
}

void error(std::exception& e)
{
    std::cerr << "std::exception caught" << std::endl;
    std::cerr << "Type: " << typeid(e).name() << std::endl;
    std::cerr << "What: " << e.what() << std::endl;
}
