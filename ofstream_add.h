#ifndef OFSTREAM_WORKAROUND_H //include guard
#define OFSTREAM_WORKAROUND_H

#include <fstream>

// Short function to resolve the problem of implementing the
// friend ofstream operator of a class with a conversion
// constructor (ie. a non-explicit constructor with one parameter).
//
// Problem in detail:
// 1. The ofstream class does not have the operator<< implemented
// 2. The ofstream is  a derived class of the ostream,  which has
//    the operator<<(double) implemented
// 3. In order to call the base class operator, the implicit cast
//    must be done from ofstream& to ostream&
// 4. The standard conversion from Derived& to Base& has the same
//    priority  as some other  conversions (ex. double to int) in
//    the overloaded function ambiguity resolve mechanism.
// 5. Since the  priority is the same,  we end up  with ambiguous
//    call, compiler doesn't know what we want to call.
//
// Solution:
// We introduce  a generic  template function  which provides the
// explicit cast, and works as a 'proxy'. The calls are no longer
// ambigous,  because  if  no-match  exists  for the  specialized
// ofstream operator<<, then the function below is used.
// Ie. it resolves ambiguity of a call by  favouring the ofstream
// to ostream upcast  (and not permitting the implicit conversion
// of a T type if there is a proper ostream operator<<)
//

template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const T& val)
{
    static_cast<std::ostream&>(ofs) << val;
    return ofs;
}



#endif 