#include "testFunctions.hpp"


static std::random_device rd;
static std::mt19937 gen(rd()); 

void ftest_L1_individual(int NN)
{
    std::vector<float> x(NN);
    std::vector<float> y(NN);
    long double flop_count = 2 * (long double)NN;
    long double nano_to_secondL = 1.e-9L;

    // Set up a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0, 1.0); // range [0,1]
    float a = dist(gen);
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = dist(gen);
        y[i] = dist(gen);
    }

    // Set up to measure the time of computation
    auto start = std::chrono::high_resolution_clock::now();
    // Run the computation
    axpy(a, x, y);
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

std::vector<long double> ftest_L1(int ntrials)
{
    std::vector<long double> L1_mflops;
    for (int NN = 2; NN <= 1024; ++NN)
    {
        // Create inputs
        std::vector<float> x(NN);
        std::vector<float> y(NN);
        // Initialize inputs
        std::uniform_real_distribution<float> dist(0.0, 1.0); // range [0,1]
        float a = dist(gen);
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
            axpy(a, x, y);
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


void ftest_L2_individual(int MM, int NN)
{
    std::vector<std::vector<float>> A(MM, std::vector<float>(NN));
    std::vector<float> x(NN);
    std::vector<float> y(MM);
    long double flop_count = (long double)MM * (2 + 2 * (long double)NN);
    long double nano_to_secondL = 1.e-9L;

    // Set up a random number generator
    std::uniform_real_distribution<float> dist(0.0, 1.0); // range [0,1]
    float a = dist(gen);
    float b = dist(gen);
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
    gemv(a, A, x, b, y);
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

std::vector<long double> ftest_L2(int ntrials)
{
    std::vector<long double> L2_mflops;
    for (int NN = 2; NN <= 1024; ++NN)
    {
        // Create inputs
        std::vector<std::vector<float>> A(NN, std::vector<float>(NN));
        std::vector<float> x(NN);
        std::vector<float> y(NN);
        // Initialize inputs
        std::uniform_real_distribution<float> dist(0.0, 1.0); // range [0,1]
        float a = dist(gen);
        float b = dist(gen);
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
            gemv(a, A, x, b, y);
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


void ftest_L3_individual(int MM, int NN, int PP)
{
    std::vector<std::vector<float>> A(MM, std::vector<float>(PP));
    std::vector<std::vector<float>> B(PP, std::vector<float>(NN));
    std::vector<std::vector<float>> C(MM, std::vector<float>(NN));
    long double flop_count = (long double)MM * (long double)NN *(2 + 2 * (long double)PP);
    long double nano_to_secondL = 1.e-9L;

    // Set up a random number generator
    std::uniform_real_distribution<float> dist(0.0, 1.0); // range [0,1]
    float a = dist(gen);
    float b = dist(gen);
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
    gemm(a, A, B, b, C);
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

std::vector<long double> ftest_L3(int ntrials)
{
    std::vector<long double> L3_mflops;
    for (int NN = 2; NN <= 1024; NN += 14)
    {
        // Create Inputs
        std::vector<std::vector<float>> A(NN, std::vector<float>(NN));
        std::vector<std::vector<float>> B(NN, std::vector<float>(NN));
        std::vector<std::vector<float>> C(NN, std::vector<float>(NN));
        // Initialize Inputs
        std::uniform_real_distribution<float> dist(0.0, 1.0); // range [0,1]
        float a = dist(gen);
        float b = dist(gen);
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
            gemm(a, A, B, b, C);
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