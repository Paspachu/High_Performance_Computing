// exam 1
// write the methods for
// operator*
// operator+
// transpose
// infinityNorm

#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>

template <typename T>
class Matrix
{
public:
    Matrix(int numRows, int numCols)
        : num_rows(numRows), num_cols(numCols), data(numRows * numCols) {}

    T &operator()(int i, int j)
    {
        return data[i * num_cols + j];
    }

    const T &operator()(int i, int j) const
    {
        return data[i * num_cols + j];
    }

    Matrix<T> operator*(const Matrix<T> &other) const
    {
        if (num_cols != other.numRows())
        {
            throw std::invalid_argument("Dimensions do not match to perform multiplication.");
        }

        Matrix<T> result(num_rows, other.numCols());
    
        for (int i = 0; i < num_rows; ++i)
        {
            for (int j = 0; j < other.numCols(); ++j)
            {
                for (int k = 0; k < num_cols; ++k)
                {
                    result(i, j) += data[i * num_cols + k] * other(k, j);
                }
            }
        }

        return result;
    }

    Matrix<T> operator+(const Matrix<T> &other) const;

    Matrix<T> transpose() const
    {
        Matrix<T> result(num_cols, num_rows);
        for (int i = 0; i < num_rows; ++i)
        {
            for (int j = 0; j < num_cols; ++j)
            {
                result(j, i) = data[i * num_cols + j];
            }
        }
        return result;
    }

    int numRows() const
    {
        return num_rows;
    }

    int numCols() const
    {
        return num_cols;
    }

    T infinityNorm() const
    {
        T norm = 0;
        
        for (int i = 0; i < num_rows; ++i)
        {
            T sum = 0;
            for (int j = 0; j < num_cols; ++j)
            {
                sum += data[i * num_cols + j];
            }

            if (norm < sum)
            {
                norm = sum;
            }
        }

        return norm;
    }

private:
    int num_rows;
    int num_cols;
    std::vector<T> data;
};

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
{
    if (num_rows != other.numRows() || num_cols != other.numCols())
    {
        throw std::invalid_argument("Dimensions do not match to perform addition.");
    }

    Matrix<T> result(num_rows, num_cols);
    
    for (int i = 0; i < num_rows; ++i)
    {
        for (int j = 0; j < num_cols; ++j)
        {
            result(i, j) = data[i * num_cols + j] + other(i, j);
        }
    }

    return result;
}

int main()
{
    Matrix<double> A(2, 3);
    A(0, 0) = 1.0;
    A(0, 1) = 2.0;
    A(0, 2) = 3.0;
    A(1, 0) = 4.0;
    A(1, 1) = 5.0;
    A(1, 2) = 6.0;

    Matrix<double> B(3, 2);
    B(0, 0) = 7.0;
    B(0, 1) = 8.0;
    B(1, 0) = 9.0;
    B(1, 1) = 10.0;
    B(2, 0) = 11.0;
    B(2, 1) = 12.0;

    Matrix<double> C = A * B;

    std::cout << "Matrix product:\n";
    for (int i = 0; i < C.numRows(); i++)
    {
        for (int j = 0; j < C.numCols(); j++)
        {
            std::cout << C(i, j) << " ";
        }
        std::cout << "\n";
    }

    Matrix<double> CT = C.transpose();

    std::cout << "\nMatrix transpose:\n";
    for (int i = 0; i < CT.numRows(); i++)
    {
        for (int j = 0; j < CT.numCols(); j++)
        {
            std::cout << CT(i, j) << " ";
        }
        std::cout << "\n";
    }

    Matrix<double> D = C + CT;
    std::cout << std::endl
              << "Matrix sum:\n";
    for (int i = 0; i < D.numRows(); i++)
    {
        for (int j = 0; j < D.numCols(); j++)
        {
            std::cout << D(i, j) << " ";
        }
        std::cout << "\n";
    }

    double mat_norm = A.infinityNorm();

    std::cout << "\nMatrix infinity norm: " << mat_norm << "\n";

    return 0;
}
