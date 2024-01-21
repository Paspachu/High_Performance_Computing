#include "p1top4.hpp"


// For answering questions
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



// For testing
static std::random_device rd;
static std::mt19937 gen(rd()); 

void dtest_L1_individual(int NN)
{
    std::vector<double> x(NN);
    std::vector<double> y(NN);
    long double flop_count = 2 * (long double)NN;
    long double nano_to_secondL = 1.e-9L;

    // Set up a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
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

std::vector<long double> dtest_L1(int ntrials)
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


void dtest_L1_unroll_individual(int NN, int block_size)
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

std::vector<long double> dtest_L1_unroll(int ntrials)
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


void dtest_L2_individual(int MM, int NN)
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

std::vector<long double> dtest_L2(int ntrials)
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


void dtest_L3_individual(int MM, int NN, int PP)
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

std::vector<long double> dtest_L3(int ntrials)
{
    std::vector<long double> L3_mflops;
    for (int NN = 2; NN <= 1024; NN += 14)
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