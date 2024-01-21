#include "strassen.hpp"


template<typename T>
std::vector<std::vector<T>> m_add(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B)
{
    if (A.size() != B.size() || A[0].size() != B[0].size())
    {
        throw std::invalid_argument("Invalid matrix dimensions");
    }

    int m = A.size();
    int n = A[0].size();
    std::vector<std::vector<T>> C(m, std::vector<T>(n));

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

template std::vector<std::vector<int>> m_add(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B);
template std::vector<std::vector<float>> m_add(const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B);
template std::vector<std::vector<double>> m_add(const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B);
template std::vector<std::vector<long double>> m_add(const std::vector<std::vector<long double>> &A, const std::vector<std::vector<long double>> &B);


template<typename T>
std::vector<std::vector<T>> m_sub(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B)
{
    if (A.size() != B.size() || A[0].size() != B[0].size())
    {
        throw std::invalid_argument("Invalid matrix dimensions");
    }

    int m = A.size();
    int n = A[0].size();
    std::vector<std::vector<T>> C(m, std::vector<T>(n));

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

template std::vector<std::vector<int>> m_sub(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B);
template std::vector<std::vector<float>> m_sub(const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B);
template std::vector<std::vector<double>> m_sub(const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B);
template std::vector<std::vector<long double>> m_sub(const std::vector<std::vector<long double>> &A, const std::vector<std::vector<long double>> &B);


template<typename T>
std::vector<std::vector<T>> strassen_mm(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B)
{
    // Check we can do the matrix multiplication
    if (A[0].size() != B.size())
    {
        throw std::invalid_argument("Invalid matrix dimensions");
    }

    int n = A.size();
    std::vector<std::vector<T>> C(n, std::vector<T>(n));

    // Base case
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Initialize required variables
    int new_n = n / 2;
    std::vector<T> z(new_n);
    std::vector<std::vector<T>> A11(new_n, z), A12(new_n, z), A21(new_n, z), A22(new_n, z),
                            B11(new_n, z), B12(new_n, z), B21(new_n, z), B22(new_n, z),
                            C11(new_n, z), C12(new_n, z), C21(new_n, z), C22(new_n, z),
                            P1(new_n, z), P2(new_n, z), P3(new_n, z), P4(new_n, z),
                            P5(new_n, z), P6(new_n, z), P7(new_n, z),
                            AResult(new_n, z), BResult(new_n, z);

    // Divide the matrices into sub-matrices:
    for (int i = 0; i < new_n; ++i)
    {
        for (int j = 0; j < new_n; ++j)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + new_n];
            A21[i][j] = A[i + new_n][j];
            A22[i][j] = A[i + new_n][j + new_n];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + new_n];
            B21[i][j] = B[i + new_n][j];
            B22[i][j] = B[i + new_n][j + new_n];
        }
    }

    // Calculate P1 to P7
    AResult = m_add(A11, A22);
    BResult = m_add(B11, B22);
    P1 = strassen_mm(AResult, BResult); 

    AResult = m_add(A21, A22);
    P2 = strassen_mm(AResult, B11);
    
    BResult = m_sub(B12, B22);
    P3 = strassen_mm(A11, BResult);

    BResult = m_sub(B21, B11);
    P4 = strassen_mm(A22, BResult); 

    AResult = m_add(A11, A12);
    P5 = strassen_mm(AResult, B22);

    AResult = m_sub(A21, A11);
    BResult = m_add(B11, B12);
    P6 = strassen_mm(AResult, BResult);

    AResult = m_sub(A12, A22);
    BResult = m_add(B21, B22);
    P7 = strassen_mm(AResult, BResult);

    // Calculate C11, C12, C21, C22:
    AResult = m_add(P1, P4);
    BResult = m_sub(AResult, P5);
    C11 = m_add(BResult, P7);
    
    C12 = m_add(P3, P5);
    C21 = m_add(P2, P4);

    AResult = m_add(P1, P3);
    BResult = m_sub(AResult, P2);
    C22 = m_add(BResult, P6);

    // Combine submatrices to one matrix
    for (int i = 0; i < new_n; ++i)
    {
        for (int j = 0; j < new_n; ++j)
        {
            C[i][j] = C11[i][j];
            C[i][j + new_n] = C12[i][j];
            C[i + new_n][j] = C21[i][j];
            C[i + new_n][j + new_n] = C22[i][j];
        }
    }

    return C;
}

template std::vector<std::vector<int>> strassen_mm(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B);
template std::vector<std::vector<float>> strassen_mm(const std::vector<std::vector<float>> &A, const std::vector<std::vector<float>> &B);
template std::vector<std::vector<double>> strassen_mm(const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B);
template std::vector<std::vector<long double>> strassen_mm(const std::vector<std::vector<long double>> &A, const std::vector<std::vector<long double>> &B);