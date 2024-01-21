#ifndef PRINTNDVECTOR_HPP
#define PRINTNDVECTOR_HPP

#include <iostream>

template<typename T>
void print_vector(const std::vector<T> &v, const std::string name);
template<typename T>
void print_matrix(const std::vector<std::vector<T>> &M, const std::string name);

#endif // PRINTNDVECTOR_HPP

