#include <iostream>
#include <fstream>
#include <thread>


double df(double x)
{
    return (1 / x) - (x / 4);
}

double g(double x)
{
    return std::sqrt(1 + std::pow(df(x), 2));
}

void compute_partial_sum(double &sum, std::mutex &sum_mutex, double a, double h, int n, int num_threads, int i)
{
    double partial_sum = 0.0;
    int start = (n / num_threads) * i;
    int end = (i == num_threads - 1) ? n: (n / num_threads) * (i + 1);
    for (int j = start; j < end; ++j)
    {
        double x = a + j * h;
        partial_sum += g(x);
    }
    partial_sum *= h;

    sum_mutex.lock();
    sum += partial_sum;
    sum_mutex.unlock();
}

double parellel_riemann_sum(double a, double b, int n, int num_threads)
{
    double h = (b - a) / n;
    double sum = 0.0;
    std::vector<std::thread> threads(num_threads);
    std::mutex sum_mutex;

    for (int i = 0; i < num_threads; ++i)
    {
        threads[i] = std::thread(compute_partial_sum, std::ref(sum), std::ref(sum_mutex), a, h, n, num_threads, i);
    }

    for (int i = 0; i < num_threads; ++i)
    {
        threads[i].join();
    }

    return sum;
}

void test_strong_scaling_efficiency(const double a, const double b, const int n, const int num_threads)
{
    auto start = std::chrono::high_resolution_clock::now();
    double par_sum = parellel_riemann_sum(a, b, n, num_threads);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);
    long double elapsed_time = (duration.count() * 1.e-9);
    std::cout << "Parallel: " << par_sum << "\ttime: " << elapsed_time << std::endl;
    
    std::ofstream outfile;
    outfile.open("time.txt", std::ios_base::app);
    outfile << n << "\t" << num_threads << "\t" << par_sum << "\t" << elapsed_time << std::endl;
    outfile.close();
}

void test_numerical_error(const double a, const double b, const int n, const int num_threads)
{
    const double exact_value = std::log(6.0) + (35.0 / 8.0);
    double par_sum = parellel_riemann_sum(a, b, n, num_threads);
    double error = std::log(std::abs(exact_value - par_sum));
    std::cout << "Exact: " << std::setprecision(16) << exact_value << "\tComputed: " << par_sum << "\t Error: " << error << std::endl;

    std::ofstream outfile;
    outfile.open("error.txt", std::ios_base::app);
    outfile << n << "\t" << num_threads << "\t" << std::setprecision(16) << exact_value << "\t" << par_sum << "\t" << error << std::endl;
    outfile.close();
}



int main(int argc, char *argv[]) 
{
    const double a = 1.0;
    const double b = 6.0;

    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " num_points nthreads" << std::endl;
        return 1;
    }
    const int n = std::atoi(argv[1]);
    const int num_threads = std::atoi(argv[2]);

    test_strong_scaling_efficiency(a, b, n, num_threads);
    test_numerical_error(a, b, n, num_threads);
    
    return 0;
}