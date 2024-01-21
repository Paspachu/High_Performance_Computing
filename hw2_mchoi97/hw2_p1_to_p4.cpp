#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include "hw2_p1_to_p4.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());


void print_vector(const std::vector<double> &v, const std::string name)
{
    std::cout << "Vector " + name + " is:" << std::endl;
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void print_vector_long(const std::vector<long double> &v, const std::string name)
{
    std::cout << "Vector " + name + " is:" << std::endl;
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void print_matrix(const std::vector<std::vector<double>> &M, const std::string name)
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


void test_L1_individual(int NN)
{
    std::vector<double> x(NN);
    std::vector<double> y(NN);
    long double flop_count = 2 * (long double)NN;
    long double nano_to_secondL = 1.e-9L;

    // Set up a random number generator
    std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
    double a = dist(gen);
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = dist(gen);
        y[i] = dist(gen);
    }

    // Set up to measure the time of computation
    auto start = std::chrono::high_resolution_clock::now();
    // Run the computation
    daxpy(a, x, y);
    // Calculate the time spent in the computation
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by code segment: " << duration.count() << " nanoseconds" << std::endl;
    // Calculate the FLOPs
    long double durationL = static_cast<long double>(duration.count());
    long double flops = flop_count / (durationL * nano_to_secondL);
    long double mflops = flops / (1.e6L);
    std::cout << "daxpy performance (MFLOPs): " << mflops << std::endl;
}

std::vector<long double> test_L1(int ntrials)
{
    std::vector<long double> L1_mflops;
    for (int NN = 2; NN <= 1024; ++NN)
    {
        // Create inputs
        std::vector<double> x(NN);
        std::vector<double> y(NN);
        // Initialize inputs
        std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
        double a = dist(gen);
        for (int i = 0; i < x.size(); ++i)
        {
            x[i] = dist(gen);
            y[i] = dist(gen);
        }

        // Compute theoretical flop count
        long double flop_count = 2 * (long double)NN;
        // Run each trial
        long double nano_to_secondL = 1.e-9L;
        long double elapsed_time = 0;
        for (int t = 0; t < ntrials; ++t)
        {
            // Set up to measure the time of computation
            auto start = std::chrono::high_resolution_clock::now();
            // Run the computation
            daxpy(a, x, y);
            // Calculate the time spent in the computation
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double durationL = static_cast<long double>(duration.count());
            elapsed_time += (durationL * nano_to_secondL);
        }
        long double average_duration = elapsed_time / ntrials;
        long double flops = flop_count / average_duration;
        L1_mflops.push_back(flops / (1.e6L));
    }

    return L1_mflops;
}


void test_L1_unroll_individual(int NN, int block_size)
{
    std::vector<double> x(NN);
    std::vector<double> y(NN);
    long double flop_count = 2 * (long double)NN;
    long double nano_to_secondL = 1.e-9L;

    // Set up a random number generator
    std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
    double a = dist(gen);
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = dist(gen);
        y[i] = dist(gen);
    }
    
    // Set up to measure the time of computation
    auto start = std::chrono::high_resolution_clock::now();
    // Run the computation
    daxpy_unroll(a, x, y, block_size);
    // Calculate the time spent in the computation
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by code segment: " << duration.count() << " nanoseconds" << std::endl;
    // Calculate the FLOPs
    long double durationL = static_cast<long double>(duration.count());
    long double flops = flop_count / (durationL * nano_to_secondL);
    long double mflops = flops / (1.e6L);
    std::cout << "daxpy_unroll performance (MFLOPs): " << mflops << std::endl;
}

std::vector<long double> test_L1_unroll(int ntrials)
{
    int NN = 2048;
    std::vector<long double> L1_unroll_mflops;
    for (int e = 0; e <= 6; ++e)
    {
        // Create inputs
        int block_size = (int)pow(2, e);
        std::vector<double> x(NN);
        std::vector<double> y(NN);
        // Initialize inputs
        std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
        double a = dist(gen);
        for (int i = 0; i < x.size(); ++i)
        {
            x[i] = dist(gen);
            y[i] = dist(gen);
        }

        // Compute theoretical flop count
        long double flop_count = 2 * (long double)NN;
        // Run each trial
        long double nano_to_secondL = 1.e-9L;
        long double elapsed_time = 0;
        for (int t = 0; t < ntrials; ++t)
        {
            // Set up to measure the time of computation
            auto start = std::chrono::high_resolution_clock::now();
            // Run the computation
            daxpy_unroll(a, x, y, block_size);
            // Calculate the time spent in the computation
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double durationL = static_cast<long double>(duration.count());
            elapsed_time += (durationL * nano_to_secondL);
        }
        long double average_duration = elapsed_time / ntrials;
        long double flops = flop_count / average_duration;
        L1_unroll_mflops.push_back(flops / (1.e6L));
    }

    return L1_unroll_mflops;
}


void test_L2_individual(int MM, int NN)
{
    std::vector<std::vector<double>> A(MM, std::vector<double>(NN));
    std::vector<double> x(NN);
    std::vector<double> y(MM);
    long double flop_count = (long double)MM * (2 + 2 * (long double)NN);
    long double nano_to_secondL = 1.e-9L;

    // Set up a random number generator
    std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
    double a = dist(gen);
    double b = dist(gen);
    for (int i = 0; i < A.size(); ++i)
    {
        for (int j = 0; j < A[i].size(); ++j)
        {
            A[i][j] = dist(gen);
        }
    }
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = dist(gen);
    }
    for (int i = 0; i < y.size(); ++i)
    {
        y[i] = dist(gen);
    }

    // Set up to measure the time of computation
    auto start = std::chrono::high_resolution_clock::now();
    // Run the computation
    dgemv(a, A, x, b, y);
    // Calculate the time spent in the computation
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by code segment: " << duration.count() << " nanoseconds" << std::endl;
    // Calculate the FLOPs
    long double durationL = static_cast<long double>(duration.count());
    long double flops = flop_count / (durationL * nano_to_secondL);
    long double mflops = flops / (1.e6L);
    std::cout << "dgemv performance (MFLOPs): " << mflops << std::endl;
}

std::vector<long double> test_L2(int ntrials)
{
    std::vector<long double> L2_mflops;
    for (int NN = 2; NN <= 1024; ++NN)
    {
        // Create inputs
        std::vector<std::vector<double>> A(NN, std::vector<double>(NN));
        std::vector<double> x(NN);
        std::vector<double> y(NN);
        // Initialize inputs
        std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
        double a = dist(gen);
        double b = dist(gen);
        for (int i = 0; i < A.size(); ++i)
        {
            for (int j = 0; j < A[i].size(); ++j)
            {
                A[i][j] = dist(gen);
            }
        }
        for (int i = 0; i < x.size(); ++i)
        {
            x[i] = dist(gen);
        }
        for (int i = 0; i < y.size(); ++i)
        {
            y[i] = dist(gen);
        }

        // Compute theoretical flop count
        long double flop_count = (long double)NN * (2 + 2 * (long double)NN);
        // Run each trial
        long double nano_to_secondL = 1.e-9L;
        long double elapsed_time = 0;
        for (int t = 0; t < ntrials; ++t)
        {
            // Set up to measure the time of computation
            auto start = std::chrono::high_resolution_clock::now();
            // Run the computation
            dgemv(a, A, x, b, y);
            // Calculate the time spent in the computation
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double durationL = static_cast<long double>(duration.count());
            elapsed_time += (durationL * nano_to_secondL);
        }
        long double average_duration = elapsed_time / ntrials;
        long double flops = flop_count / average_duration;
        L2_mflops.push_back(flops / (1.e6L));
    }

    return L2_mflops;
}


void test_L3_individual(int MM, int NN, int PP)
{
    std::vector<std::vector<double>> A(MM, std::vector<double>(PP));
    std::vector<std::vector<double>> B(PP, std::vector<double>(NN));
    std::vector<std::vector<double>> C(MM, std::vector<double>(NN));
    long double flop_count = (long double)MM * (long double)NN *(2 + 2 * (long double)PP);
    long double nano_to_secondL = 1.e-9L;

    // Set up a random number generator
    std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
    double a = dist(gen);
    double b = dist(gen);
    for (int i = 0; i < A.size(); ++i)
    {
        for (int j = 0; j < A[i].size(); ++j)
        {
            A[i][j] = dist(gen);
        }
    }
    for (int i = 0; i < B.size(); ++i)
    {
        for (int j = 0; j < B[i].size(); ++j)
        {
            B[i][j] = dist(gen);
        }
    }
    for (int i = 0; i < C.size(); ++i)
    {
        for (int j = 0; j < C[i].size(); ++j)
        {
            C[i][j] = dist(gen);
        }
    }

    // Set up to measure the time of computation
    auto start = std::chrono::high_resolution_clock::now();
    // Run the computation
    dgemm(a, A, B, b, C);
    // Calculate the time spent in the computation
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    std::cout << "Time taken by code segment: " << duration.count() << " nanoseconds" << std::endl;
    // Calculate the FLOPs
    long double durationL = static_cast<long double>(duration.count());
    long double flops = flop_count / (durationL * nano_to_secondL);
    long double mflops = flops / (1.e6L);
    std::cout << "dgemm performance (MFLOPs): " << mflops << std::endl;
}

std::vector<long double> test_L3(int ntrials)
{
    std::vector<long double> L3_mflops;
    for (int NN = 2; NN <= 1024; NN += 4)
    {
        // Create Inputs
        std::vector<std::vector<double>> A(NN, std::vector<double>(NN));
        std::vector<std::vector<double>> B(NN, std::vector<double>(NN));
        std::vector<std::vector<double>> C(NN, std::vector<double>(NN));
        // Initialize Inputs
        std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
        double a = dist(gen);
        double b = dist(gen);
        for (int i = 0; i < A.size(); ++i)
        {
            for (int j = 0; j < A[i].size(); ++j)
            {
                A[i][j] = dist(gen);
            }
        }
        for (int i = 0; i < B.size(); ++i)
        {
            for (int j = 0; j < B[i].size(); ++j)
            {
                B[i][j] = dist(gen);
            }
        }
        for (int i = 0; i < C.size(); ++i)
        {
            for (int j = 0; j < C[i].size(); ++j)
            {
                C[i][j] = dist(gen);
            }
        }

        // Compute theoretical flop count
        long double flop_count = (long double)NN * (long double)NN *(2 + 2 * (long double)NN);
        // Run each trial
        long double nano_to_secondL = 1.e-9L;
        long double elapsed_time = 0;
        for (int t = 0; t < ntrials; ++t)
        {
            // Set up to measure the time of computation
            auto start = std::chrono::high_resolution_clock::now();
            // Run the computation
            dgemm(a, A, B, b, C);
            // Calculate the time spent in the computation
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double durationL = static_cast<long double>(duration.count());
            elapsed_time += (durationL * nano_to_secondL);
        }
        long double average_duration = elapsed_time / ntrials;
        long double flops = flop_count / average_duration;
        L3_mflops.push_back(flops / (1.e6L));
    }
    
    return L3_mflops;
}



int main()
{
    int ntrials = 10;

    // print_vector_long(test_L1(ntrials), "L1_performance");
    // print_vector_long(test_L1_unroll(ntrials), "L1_unroll_performance");
    // print_vector_long(test_L2(ntrials), "L2_performance");
    // print_vector_long(test_L3(ntrials), "L3_performance");
    // test_L3_individual(1024, 1024, 1024);

    return 0;
}