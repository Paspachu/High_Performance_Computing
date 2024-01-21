#ifndef MM_IJK_HPP
#define MM_IJK_HPP

#include <iostream>
#include <exception>

template<typename T>
void mm_ijk(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C, int m, int p, int n);

#endif // MM_IJK_HPP