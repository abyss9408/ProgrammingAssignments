// Provide file documentation header
// Don't include any C and C++ standard library headers!!!
// Remember, this file is incomplete and you must provide missing details/features.

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream> // std::ostream

namespace HLP3 {

// declare class template Polynomial
template <typename T, int N>
class Polynomial
{
public:
    Polynomial();

    template <typename U>
    Polynomial(const Polynomial<U, N>& rhs);

    template <typename U>
    Polynomial& operator=(const Polynomial<U, N>& rhs);

    T& operator[](int index);

    const T& operator[](int index) const;

    template <int J>
    Polynomial<T, N + J> operator*(const Polynomial<T, J>& rhs);

    T operator()(T val_x);
private:
    T data[N + 1];
};


}

#include "polynomial.tpp"

#endif
