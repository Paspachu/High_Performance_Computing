#ifndef L2BLAS_HPP
#define L2BLAS_HPP

#include <iostream>

template <typename T>
void gemv(T a, const std::vector<std::vector<T>> &A, const std::vector<T> &x, T b, std::vector<T> &y);

#endif // L2BLAS_HPP