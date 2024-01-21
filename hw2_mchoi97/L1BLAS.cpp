#include "L1BLAS.hpp"

template<typename T>
void axpy(T alpha, const std::vector<T> &x, std::vector<T> &y) 
{
    // Check if two vectors have same length
    if (x.size() != y.size())
    {
        std::cerr << "Error: vectors have different sizes" << std::endl;
        return;
    }

    // Perform the computation
    for (int i = 0; i < y.size(); ++i)
    {
        y[i] += alpha * x[i];
    }
}

template void axpy(int alpha, const std::vector<int> &x, std::vector<int> &y);
template void axpy(float alpha, const std::vector<float> &x, std::vector<float> &y);
template void axpy(double alpha, const std::vector<double> &x, std::vector<double> &y);
