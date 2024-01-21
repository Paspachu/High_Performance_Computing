#include "L3BLAS.hpp"

template<typename T>
void gemm(T a, const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B, T b, std::vector<std::vector<T>> &C)
{
    // Check if matrix multiplication can be computed
    if (A[0].size() != B.size())
    {
        std::cerr << "Error: AB can not be computed" << std::endl;
        return;
    }
    // Check if matrix addition can be computed
    if (A.size() != C.size() || B[0].size() != C[0].size())
    {
        std::cerr << "Error: AB + C can not be computed" << std::endl;
        return;
    }

    // Perform the computation
    for (int i = 0; i < A.size(); ++i)
    {   
        for (int j = 0; j < B[0].size(); ++j)
        {
            T AB = 0;
            for (int k = 0; k < B.size(); ++k)
            {
                AB += A[i][k] * B[k][j]; 
            }
            C[i][j] = (a * AB) + (b * C[i][j]);
        }
    }
}

template void gemm(int a, const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B, int b, std::vector<std::vector<int>> &C);
template void gemm(float a, const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B, float b, std::vector<std::vector<float>> &C);
template void gemm(double a, const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B, double b, std::vector<std::vector<double>> &C);