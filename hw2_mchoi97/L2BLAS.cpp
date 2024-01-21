#include "L2BLAS.hpp"

template<typename T>
void gemv(T a , const std::vector<std::vector<T>> &A, const std::vector<T> &x, T b, std::vector<T> &y)
{
    // Check if matrix vector multiplication can be computed
    if (A[0].size() != x.size())
    {
        std::cerr << "Error: Ax can not be computed" << std::endl;
        return;
    }
    // Check if vector addition can be computed
    if (A.size() != y.size())
    {
        std::cerr << "Error: Ax + y can not be computed" << std::endl;
        return;
    }

    // Perform the computation
    for (int i = 0; i < A.size(); ++i)
    {
        T Ax = 0;
        for (int j = 0; j < A[0].size(); ++j)
        {
            Ax += A[i][j] * x[j];
        }

        y[i] = (a * Ax) + (b * y[i]);
    }
}

template void gemv(int a , const std::vector<std::vector<int>> &A, const std::vector<int> &x, int b, std::vector<int> &y);
template void gemv(float a , const std::vector<std::vector<float>> &A, const std::vector<float> &x, float b, std::vector<float> &y);
template void gemv(double a , const std::vector<std::vector<double>> &A, const std::vector<double> &x, double b, std::vector<double> &y);