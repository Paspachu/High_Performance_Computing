#ifndef SAVEVECTOR_HPP
#define SAVEVECTOR_HPP

#include <fstream>
#include <iterator>
#include <string>

template<typename T>
void saveVector(const std::vector<T> &v, const std::string title);

#endif // SAVEVECTOR_HPP