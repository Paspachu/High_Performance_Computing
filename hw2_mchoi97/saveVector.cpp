#include "saveVector.hpp"


template<typename T>
void saveVector(const std::vector<T> &v, const std::string title)
{
    // std::vector<std::string> example { "This", "is", "a", "test" };
    std::ofstream output_file("./" + title + ".txt");
    std::ostream_iterator<T> output_iterator(output_file, "\n");
    std::copy(std::begin(v), std::end(v), output_iterator);
}

template void saveVector(const std::vector<int> &v, const std::string title);
template void saveVector(const std::vector<float> &v, const std::string title);
template void saveVector(const std::vector<double> &v, const std::string title);
template void saveVector(const std::vector<long double> &v, const std::string title);