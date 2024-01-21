#ifndef L3BLAS_HPP
#define L3BLAS_HPP

#include <iostream>

template <typename T>
void gemm(T a, const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, T b, std::vector<std::vector<T>> &C);

#endif // L3BLAS_HPP