#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <mpi.h>


double df(double x)
{
    return (1 / x) - (x / 4);
}

double g(double x)
{
    return std::sqrt(1 + std::pow(df(x), 2));
}

double sequential_riemann_sum(double a, double b, int n)
{
    double h = (b - a) / n;
    double sum = 0.0;
    for (int i = 0; i < n; ++i)
    {
        double x = a + i * h;
        sum += g(x);
    }
    sum *= h;

    return sum;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, & argv);

    int ip, np;
    MPI_Comm_rank(MPI_COMM_WORLD, &ip);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    double a = 1.0, b = 6.0;
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " num_points" << std::endl;
        return 1;
    }
    int n = std::atoi(argv[1]);
    
    double local_a = a + ip * (b - a) / np;
    double local_b = a + (ip + 1) * (b-a) / np;
    int local_n = n / np;
    double global_sum;

    auto start = std::chrono::high_resolution_clock::now();
    double local_sum = sequential_riemann_sum(local_a, local_b, local_n);
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
    long double elapsed_time = (duration.count() * 1.e-9);

    const double exact_value = std::log(6.0) + (35.0 / 8.0);
    double error = std::log(std::abs(exact_value - global_sum));

    if (ip == 0)
    {
        std::cout << n << "\t" << exact_value << "\t" << global_sum << "\t" << elapsed_time << "\t" << error << std::endl;
    }

    MPI_Finalize();
    return 0;
}