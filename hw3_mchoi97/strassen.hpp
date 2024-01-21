#ifndef STRASSEN_HPP
#define STRASSEN_HPP

#include <iostream>
#include <exception>

template<typename T>
std::vector<std::vector<T>> m_add(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);
template<typename T>
std::vector<std::vector<T>> m_sub(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);
template<typename T>
std::vector<std::vector<T>> strassen_mm(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B);

#endif // STRASSEN_HPP