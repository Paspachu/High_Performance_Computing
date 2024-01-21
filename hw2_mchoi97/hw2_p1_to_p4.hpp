#include <iostream>


void daxpy(double a, const std::vector<double> &x, std::vector<double> &y) 
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
        y[i] += a * x[i];
    }
}


void daxpy_unroll_shortcut(double a, const std::vector<double> &x, std::vector<double> &y, int block_size) 
{
    // Check if two vectors have same length
    if (x.size() != y.size())
    {
        std::cerr << "Error: vectors have different sizes" << std::endl;
        return;
    }

    // If the block_size is less than our depth 4, than perform daxpy computation
    if (block_size < 4)
    {
        daxpy(a, x, y);
        return;
    }

    // Perform the computation
    int i = 0;
    for (; i < y.size(); i += block_size)
    {
        int j = 0;
        int k = 0;
        for (; j < block_size; j += 4)
        {
            y[i + j] += a * x[i + j];
            y[i + j + 1] += a * x[i + j + 1];
            y[i + j + 2] += a * x[i + j + 2];
            y[i + j + 3] += a * x[i + j + 3];
        }
    }
}


void daxpy_unroll(double a, const std::vector<double> &x, std::vector<double> &y, int block_size) 
{
    // Check if two vectors have same length
    if (x.size() != y.size())
    {
        std::cerr << "Error: vectors have different sizes" << std::endl;
        return;
    }

    // If the block_size is less than our depth 4, than perform daxpy computation
    if (block_size < 4)
    {
        daxpy(a, x, y);
        return;
    }

    // Perform the computation using loop unrolling technique
    int i = 0;
    int i_index = 0;
    for (; i < y.size() / block_size; ++i)
    {
        int j = 0;
        int j_index = 0;
        for (; j < block_size / 4; ++j)
        {
            y[i_index + j_index] += a * x[i_index + j_index];
            y[i_index + j_index + 1] += a * x[i_index + j_index + 1];
            y[i_index + j_index + 2] += a * x[i_index + j_index + 2];
            y[i_index + j_index + 3] += a * x[i_index + j_index + 3];
            j_index += 4;
        }
        for (; j_index < block_size; j_index++)
        {
            y[i_index + j_index] += a * x[i_index + j_index];
        }
        i_index += block_size;
    }
    for (; i_index < y.size(); i_index++)
    {
        y[i_index] += a * x[i_index];
    }
}

void dgemv(double a , const std::vector<std::vector<double>> &A, const std::vector<double> &x, double b, std::vector<double> &y)
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
        double Ax = 0;
        for (int j = 0; j < A[0].size(); ++j)
        {
            Ax += A[i][j] * x[j];
        }

        y[i] = (a * Ax) + (b * y[i]);
    }
}


void dgemm(double a, const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B, double b, std::vector<std::vector<double>> &C)
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
            double AB = 0;
            for (int k = 0; k < B.size(); ++k)
            {
                AB += A[i][k] * B[k][j]; 
            }
            C[i][j] = (a * AB) + (b * C[i][j]);
        }
    }
}