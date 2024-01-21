#ifndef L1BLAS_HPP
#define L1BLAS_HPP

#include <iostream>

template <typename T>
void axpy(T alpha, const std::vector<T> &x, std::vector<T> &y);

#endif // L1BLAS_HPP