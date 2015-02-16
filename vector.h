/**
 * @file vector.h
 * @brief Header file containing Vector template class definition and its
 * implementation.
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
#include <stdexcept>

// g++ compiler requires undermentioned declarations
// (http://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Making_New_Friends)

template <typename T>
class Vector;

template <typename T>
std::istream& operator>>(std::istream& is, Vector<T>& v);

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v);

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, Vector<T>& v);

template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const Vector<T>& v);

/**
 * @brief Template class meant to represent a vector of objects of user
 * specified type.
 */
template <typename T>
class Vector {
protected:
    /**
     * @brief Number of elements.
     */
    int num;

    /**
     * @brief Pointer to the data.
     */
    T* pdata;

    /**
     * @brief Private function since user should not call it.
     * @param Num Number of elements in new vector.
     *
     * Initialises data, called by the constructors.
     * It throws an exception when given negative index.
     */
    void Init(int Num);

public:
    // CONSTRUCTORS
    /**
     * @brief Default constructor.
     */
    Vector();

    /**
     * @brief Alternate constructor.
     * @param Num Number of elements in new vector.
     *
     * Construct Vector of given size. It is explicit since implicit type
     * conversion int to Vector doesn't make sense.
     */
    explicit Vector(int Num);

    /**
     * @brief Copy constructor.
     * @param v Vector.
     *
     * This constructor copies data from Vector v to newly allocated memory.
     */
    Vector(const Vector<T>& v);

    // DESTRUCTOR
    /**
     * @brief Destructor. Deletes allocated memory.
     *
     * Destructor is virtual since it is a good thing to have virtual destructor
     * in base class.
     */
    virtual ~Vector();

    // MEMBER FUNCTIONS
    /**
     * @brief Get number of elements in the vector.
     * @return Number of elements in the vector.
     *
     * It a is const member function since it does not modify object data.
     */
    int size() const;

    // OVERLOADED OPERATORS
    /**
     * @brief Overloaded assignment operator.
     * @param v Right-side operand vector.
     * @return Reference to left-side operand.
     *
     * It copies data from Vector v to newly allocated memory. Does nothing when
     * the same object is on its both sides.
     */
    Vector<T>& operator=(const Vector& v);

    /**
     * @brief Overloaded array access operator for writing.
     * @param i Vector element index.
     * @return Reference to left-side operand.
     *
     * It throws an exception when given out of range index.
     */
    T& operator[](int i);

    /**
     * @brief Overloaded array access operator for reading.
     * @param i Vector element index.
     * @return Left-side operand.
     *
     * It throws an exception when given out of range index.
     */
    T operator[](int i) const;

    /**
     * @brief Overloaded comparison operator.
     * @param v Right-side operand Vector reference.
     * @return True only if two vectors are the same.
     *
     * It returns false when vectors have different sizes.
     */
    bool operator==(const Vector& v) const;

    // KEYBOARD/SCREEN INPUT AND OUTPUT
    /**
     * @brief Overloaded stream input operator for keyboard input.
     * @param is Input stream reference (e.g. std::cin).
     * @param v Right-side operand Vector reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. std::cin >> v1 >> v2 >> v3;).
     */
    friend std::istream& operator>><>(std::istream& is, Vector<T>& v);

    /**
     * @brief Overloaded stream output operator for screen output.
     * @param os Output stream reference (e.g. std::cout).
     * @param v Right-side operand Vector reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. std::cout << v1 << v2 << v3;).
     */
    friend std::ostream& operator<<<>(std::ostream& os, const Vector<T>& v);

    // FILE INPUT AND OUTPUT
    /**
     * @brief Overloaded file input operator.
     * @param ifs Input file stream reference.
     * @param v Right-side operand Vector reference.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. ifs >> v1 >> v2 >> v3;).
     *
     * The file input operator is compatible with file output operator, ie.
     * everything written can be read later.
     */
    friend std::ifstream& operator>><>(std::ifstream& ifs, Vector<T>& v);

    /**
     * @brief Overloaded file output operator.
     * @param ofs Output file stream reference.
     * @param v Right-side operand Vector.
     * @return Reference to the left-side operand stream.
     *
     * Since this operator returns reference to its left-side operand, it can be
     * used multiple times in one statement (e.g. ofs << v1 << v2 << v3;).
     *
     * The file output operator is compatible with file input operator, ie.
     * everything written can be read later.
     */
    friend std::ofstream& operator<<<>(std::ofstream& ofs, const Vector<T>& v);
};

// CONSTRUCTORS
// default constructor (empty vector)
template <typename T>
Vector<T>::Vector()
    : num(0), pdata(0)
{
}

// initialise data, called by the constructors
template <typename T>
void Vector<T>::Init(int Num)
{
    // check input sanity
    if (Num < 0)
        throw std::invalid_argument("vector size negative");
    num = Num;
    if (num <= 0)
        pdata = 0;  // empty vector, nothing to allocate
    else {
        pdata = new T[num];  // allocate memory for vector
        for (int i = 0; i < num; i++)
            pdata[i] = 0.0;
    }
}

// alternate constructor
template <typename T>
Vector<T>::Vector(int Num)
{
    Init(Num);
}

// copy constructor
template <typename T>
Vector<T>::Vector(const Vector<T>& copy)
{
    Init(copy.size());  // allocate the memory

    // copy the data members (if vector is empty then pdata==0 and num==0)
    for (int i = 0; i < num; i++)
        pdata[i] = copy.pdata[i];
}

// DESTRUCTOR
template <typename T>
Vector<T>::~Vector()
{
    delete[] pdata;  // free the dynamic memory
}

// OVERLOADED OPERATORS
// assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& copy)
{
    // can't copy self to self (that is v = v in main is dealt with)
    if (this == &copy)
        return *this;

    delete[] pdata;     // delete existing memory
    Init(copy.size());  // create new memory then copy data
    for (int i = 0; i < num; i++)
        pdata[i] = copy.pdata[i];

    return *this;
}

// array access operator for assigning values
template <typename T>
T& Vector<T>::operator[](int i)
{
    // check the range, throw appropriate exception
    if (i < 0 || i >= num)
        throw std::out_of_range("vector access error");

    return pdata[i];
}

// array access operator for reading values
template <typename T>
T Vector<T>::operator[](int i) const
{
    // check the range, throw appropriate exception
    if (i < 0 || i >= num)
        throw std::out_of_range("vector access error");

    return pdata[i];
}

// SIZE
// return the size of the vector
template <typename T>
int Vector<T>::size() const
{
    return num;
}

// COMPARISON
template <typename T>
bool Vector<T>::operator==(const Vector& v) const
{
    if (num != v.num)
        return false;

    for (int i = 0; i < num; i++)
        if ((*this)[i] != v[i])
            return false;

    return true;
}

// INPUT AND OUTPUT
// keyboard input - user friendly
template <typename T>
std::istream& operator>>(std::istream& is, Vector<T>& v)
{
    if (!v.num) {
        int n;

        std::cout << "input the size for the vector" << std::endl;
        is >> n;
        // check input sanity
        if (n < 0)
            throw std::invalid_argument("read error - negative vector size");

        // prepare the vector to hold n elements
        v = Vector<T>(n);
    }
    // input the elements
    std::cout << "input " << v.num << " vector elements" << std::endl;
    for (int i = 0; i < v.num; i++)
        is >> v[i];

    // return the stream object
    return is;
}

// file input - raw data, compatible with file writing operator
template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, Vector<T>& v)
{
    int n;

    // read size from the file
    ifs >> n;
    // check input sanity
    if (n < 0)
        throw std::invalid_argument("file read error - negative vector size");

    // prepare the vector to hold n elements
    v = Vector<T>(n);

    // input the elements
    for (int i = 0; i < n; i++)
        ifs >> v[i];

    // return the stream object
    return ifs;
}

// screen output - user friendly
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
    if (v.pdata) {
        for (int i = 0; i < v.size(); i++)
            os << v[i] << " ";
        os << std::endl;
    }
    else {
        os << "Vector is empty." << std::endl;
    }

    return os;
}

// file output - raw data, comaptible with file reading operator
template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const Vector<T>& v)
{
    // put vector size in first line (even if it is zero)
    ofs << v.size() << std::endl;
    // put data in second line (if size==zero nothing will be put)
    for (int i = 0; i < v.size(); i++)
        ofs << v[i] << " ";
    ofs << std::endl;

    return ofs;
}

#endif
