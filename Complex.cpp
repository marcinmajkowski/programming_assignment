
#include "complex.h"
#include <iomanip>
#include <cmath>

using namespace std;

// CONSTRUCTORS
//Default Constructor
Complex::Complex() : re(0.0), im(0.0) {}

//Constructor to create Complex from Real part
Complex::Complex(double re) {
	this->re = re;
	this->im = 0.0;
}

//Constructor to create Complex from Real part and Imaginary part
Complex::Complex(double re, double im) {
	this->re = re;
	this->im = im;	
}

//Copy constructor
Complex::Complex(const Complex& c) {
	this->re = c.re;
	this->im = c.im;
}

// ACCESSOR METHODS
//Returns with Real part
double Complex::getReal() const {
	return this->re;
}

//Returns with Imaginary part
double Complex::getImag() const {
	return this->im;
}

// MUTATOR METHODS
//Setter for Real part
Complex& Complex::setReal(double re) {
	this->re = re;
	return *this;
}

//Setter for Imaginary part
Complex& Complex::setImag(double im) {
	this->im = im;
	return *this;
}


// OPERATIONS, inverse, absolute value and conjugate
double Complex::cabs() const
{
	return sqrt(re*re+im*im);
}

Complex Complex::cinv() const
{
	Complex temp;

	temp.re = re/(re*re+im*im);
	temp.im = -im/(re*re+im*im);

	return temp;
}

Complex Complex::ccong() const
{
	return Complex(re,-im);
}

// OVERLOADED OPERATORS
//Oparation+ for Complex numbers
Complex Complex::operator+(const Complex& c) const {
	Complex temp;
	temp.re = this->re + c.re;
	temp.im = this->im + c.im;
	return temp;
}

//Operation* for Complex numbers
Complex Complex::operator*(const Complex& c) const {
	Complex temp;
	temp.re = (this->re*c.re) - (this->im*c.im);
	temp.im = (this->re*c.im) + (this->im*c.re);
	return temp;
}

//Operation/ for Complex numbers
Complex Complex::operator/(const Complex& c) const 
{
	// multiply 1/c by *this
	return (*this)*c.cinv();
}

//Comparison of two Complex numbers
bool Complex::operator==(const Complex& c) const {
	bool isEqual = false;
	if ((this->re == c.re) && (this->im == c.im)) {
		isEqual = true;
	}
	return isEqual;
}

//Comparison of two Complex numbers
bool Complex::operator!=(const Complex& c) const {
	bool isNotEqual = false;
	if ((this->re != c.re) || (this->im != c.im)) {
		isNotEqual = true;
	}
	return isNotEqual;
}

// Add a Complex number to the current one
Complex& Complex::operator+=(const Complex& c) {
	this->re += c.re; 
	this->im += c.im; 
	return *this;
}

//Assignment operator for Complex numbers
Complex& Complex::operator=(const Complex& c) {
	this->re=c.re;
	this->im=c.im;
	return *this;
}

// INPUT AND OUTPUT
//screen output
std::ostream& operator<<(std::ostream& os, const Complex& c) {
	/*
	os << "Real-part = " << c.re << std::endl
	<< "Imaginary-part = " << c.im << setiosflags(ios::showpos) << std::endl;
	os <<"z = "<< c.re << c.im << "i" << std::endl << resetiosflags(ios::showpos);
	*/
	// I decided to simplify the output.
	os << c.re << setiosflags(ios::showpos) << c.im << "i" << resetiosflags(ios::showpos);
	return os;
}

//keyboard input
std::istream& operator>>(std::istream& is, Complex& c)
{
	//int re, im; // this line was an error
	double re, im;
	//std::cout << "input the real-part of the complex" << std::endl;
	std::cout << "Input real-part:\t";
	while (!(is >> re))
	{
		//std::cout << "Please give me a double!  Try again: \n";
		std::cout << "Please give me a double!  Try again: ";
		is.clear();
		is.ignore(1000, '\n');
	}
	//std::cout << "input the imaginary-part of the complex" << std::endl;
	std::cout << "Input imaginary-part:\t";
	while (!(is >> im))
	{
		//std::cout << "Please give me a double!  Try again: \n";
		std::cout << "Please give me a double!  Try again: ";
		is.clear();
		is.ignore(1000, '\n');
	}
	c = Complex(re, im);
	return is;
}

//file output
std::ofstream& operator<<(std::ofstream& ofs, const Complex& c) {
	ofs << c.re << " ";
	ofs << c.im << std::endl;
    return ofs;
}

//file input
std::ifstream& operator>>(std::ifstream& ifs, Complex& c) {
	int re, im;
    ifs >> re; ifs>> im;
    c = Complex(re,im);
    return ifs;
}
