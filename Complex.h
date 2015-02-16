#ifndef COMPLEX_H //include guard
#define COMPLEX_H

#include <iostream> //Generic IO operations
#include <fstream>  //File IO operations
#include <stdexcept> //provides exceptions

//needed for ofstream output
//see inside this file for explanation
#include "ofstream_add.h"

// The complex number class,
// with some of the functions written inline

/**
 * A test class. A more elaborate class description.
 */
class Complex {
private:
    double re, im;
public:
	// CONSTRUCTORS
    Complex();                    
	Complex(double re);          
    Complex(double re, double im);
    Complex(const Complex& c);

	// GET ACCESSOR METHODS
	double getReal() const;
	double getImag() const;

	// SET MUTATOR METHODS
	Complex& setReal(double re); 
    Complex& setImag(double im); 

	// OPERATIONS inverse, cojugate and absolute value
	Complex cinv() const;
	Complex ccong() const;
	double cabs() const;

    // OVERLOADED OPERATORS +, *, \, ==, +=, =
    Complex operator+(const Complex& c) const;
    Complex operator*(const Complex& c) const;
	Complex operator/(const Complex& c) const;
    bool operator==(const Complex& c) const;
	bool operator!=(const Complex& c) const;
    Complex& operator+=(const Complex& c);
    Complex& operator=(const Complex& c); 

	// INPUT AND OUTPUT
    friend std::ostream& operator<<(std::ostream& os, const Complex& c); //screen output
    friend std::istream& operator>>(std::istream& is, Complex& c); //keyboard input

    //the file output operator should be compatible with file input operator,
    //ie. everything written can be read later.
    friend std::ofstream& operator<<(std::ofstream& ofs, const Complex& c); //file output
	friend std::ifstream& operator>>(std::ifstream& ifs, Complex& c); //file input
};

#endif