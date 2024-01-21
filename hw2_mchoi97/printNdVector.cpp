#include "printNdVector.hpp"


template<typename T>
void print_vector(const std::vector<T> &v, const std::string name)
{
    std::cout << "Vector " + name + " is:" << std::endl;
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

template void print_vector(const std::vector<int> &v, const std::string name);
template void print_vector(const std::vector<float> &v, const std::string name);
template void print_vector(const std::vector<double> &v, const std::string name);
template void print_vector(const std::vector<long double> &v, const std::string name);


template<typename T>
void print_matrix(const std::vector<std::vector<T>> &M, const std::string name)
{
    std::cout << "Matrix " + name + " is:" << std::endl;
    for (int i = 0; i < M.size(); i++)
    {
        for (int j = 0; j < M[i].size(); j++)
        {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;    
    }
}

template void print_matrix(const std::vector<std::vector<int>> &M, const std::string name);
template void print_matrix(const std::vector<std::vector<float>> &M, const std::string name);
template void print_matrix(const std::vector<std::vector<double>> &M, const std::string name);
template void print_matrix(const std::vector<std::vector<long double>> &M, const std::string name);