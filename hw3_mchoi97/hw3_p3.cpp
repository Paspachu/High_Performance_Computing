#include "hw3_p3.hpp"


int main()
{
    int ntrials = 5;
    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    
    std::vector<long double> mflops;
    for (int e = 1; e <= 9; ++e)
    {
        int NN = (int)pow(2, e);
        // Create Inputs
        std::vector<std::vector<double>> A(NN, std::vector<double>(NN));
        std::vector<std::vector<double>> B(NN, std::vector<double>(NN));
        // Initialize Inputs
        std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
        for (int i = 0; i < NN; ++i)
        {
            for (int j = 0; j < NN; j++)
            {
                A[i][j] = dist(gen);
            }
        }
        for (int i = 0; i < NN; ++i)
        {
            for (int j = 0; j < NN; j++)
            {
                B[i][j] = dist(gen);
            }
        }

        // Compute theoretical flop count
        long double flop_count = (long double)NN * (long double)NN *(4.5L + 1.75L * (long double)NN);
        // Run each trial
        long double nano_to_secondL = 1.e-9L;
        long double elapsed_time = 0;
        for (int t = 0; t < ntrials; ++t)
        {
            // Set up to measure the time of computation
            auto start = std::chrono::high_resolution_clock::now();
            // Run the computation
            strassen_mm(A, B);
            // Calculate the time spent in the computation
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double durationL = static_cast<long double>(duration.count());
            elapsed_time += (durationL * nano_to_secondL);
        }
        long double average_duration = elapsed_time / ntrials;
        long double flops = flop_count / average_duration;
        mflops.push_back(flops / (1.e6L));
    }

    saveVector(mflops, "Strassen");

    return 0;
}