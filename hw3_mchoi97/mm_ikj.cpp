#include "mm_ikj.hpp"


template<typename T>
void mm_ikj(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C, int m, int p, int n)
{
    // Check if each matrix is in the correct size
    if (A.size() != m * p)
    {
        throw std::invalid_argument("Matrix A is not m by p.");
        return;
    }
    if (B.size() != p * n)
    {
        throw std::invalid_argument("Matrix B is not p by n.");
        return;
    }
    if (C.size() != m * n)
    {
        throw std::invalid_argument("Matrix C is not m by n.");
        return;
    }

    // Perform the computation
    for (int i = 0; i < m; ++i) 
    {
        for (int k = 0; k < n; ++k) 
        {
            for (int j = 0; j < p; ++j) 
            {
                if (j == 0)
                {
                    C[i+k*m] = b * C[i+k*m];
                }
                C[i+k*m] += a * A[i+j*m] * B[j+k*p];
            }
        }
    }
}

template void mm_ikj(int a, const std::vector<int>& A, const std::vector<int>& B, int b, std::vector<int>& C, int m, int p, int n);
template void mm_ikj(float a, const std::vector<float>& A, const std::vector<float>& B, float b, std::vector<float>& C, int m, int p, int n);
template void mm_ikj(double a, const std::vector<double>& A, const std::vector<double>& B, double b, std::vector<double>& C, int m, int p, int n);
template void mm_ikj(long double a, const std::vector<long double>& A, const std::vector<long double>& B, long double b, std::vector<long double>& C, int m, int p, int n);

