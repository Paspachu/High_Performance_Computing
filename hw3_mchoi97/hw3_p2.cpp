#include "hw3_p2.hpp"


static std::random_device rd;
static std::mt19937 gen(rd()); 

std::vector<long double> ftest_kij(int ntrials)
{
    std::vector<long double> mflops_kij;
    for (int NN = 2; NN <= 512; ++NN)
    {
        // Create Inputs
        std::vector<float> A(NN * NN);
        std::vector<float> B(NN * NN);
        std::vector<float> C(NN * NN);
        // Initialize Inputs
        std::uniform_real_distribution<float> dist(0.0, 1.0); // range [0,1]
        float a = dist(gen);
        float b = dist(gen);
        for (int i = 0; i < NN * NN; ++i)
        {
            A[i]= dist(gen);
        }
        for (int i = 0; i < NN * NN; ++i)
        {
            B[i]= dist(gen);
        }
        for (int i = 0; i < NN * NN; ++i)
        {
            C[i]= dist(gen);
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
            mm_kij(a, A, B, b, C, NN, NN, NN);
            // Calculate the time spent in the computation
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double durationL = static_cast<long double>(duration.count());
            elapsed_time += (durationL * nano_to_secondL);
        }
        long double average_duration = elapsed_time / ntrials;
        long double flops = flop_count / average_duration;
        mflops_kij.push_back(flops / (1.e6L));
    }
    
    return mflops_kij;
}


std::vector<long double> dtest_kij(int ntrials)
{
    std::vector<long double> mflops_kij;
    for (int NN = 2; NN <= 512; ++NN)
    {
        // Create Inputs
        std::vector<double> A(NN * NN);
        std::vector<double> B(NN * NN);
        std::vector<double> C(NN * NN);
        // Initialize Inputs
        std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
        double a = dist(gen);
        double b = dist(gen);
        for (int i = 0; i < NN * NN; ++i)
        {
            A[i]= dist(gen);
        }
        for (int i = 0; i < NN * NN; ++i)
        {
            B[i]= dist(gen);
        }
        for (int i = 0; i < NN * NN; ++i)
        {
            C[i]= dist(gen);
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
            mm_kij(a, A, B, b, C, NN, NN, NN);
            // Calculate the time spent in the computation
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double durationL = static_cast<long double>(duration.count());
            elapsed_time += (durationL * nano_to_secondL);
        }
        long double average_duration = elapsed_time / ntrials;
        long double flops = flop_count / average_duration;
        mflops_kij.push_back(flops / (1.e6L));
    }
    
    return mflops_kij;
}


std::vector<long double> ftest_jki(int ntrials)
{
    std::vector<long double> mflops_jki;
    for (int NN = 2; NN <= 512; ++NN)
    {
        // Create Inputs
        std::vector<float> A(NN * NN);
        std::vector<float> B(NN * NN);
        std::vector<float> C(NN * NN);
        // Initialize Inputs
        std::uniform_real_distribution<float> dist(0.0, 1.0); // range [0,1]
        float a = dist(gen);
        float b = dist(gen);
        for (int i = 0; i < NN * NN; ++i)
        {
            A[i]= dist(gen);
        }
        for (int i = 0; i < NN * NN; ++i)
        {
            B[i]= dist(gen);
        }
        for (int i = 0; i < NN * NN; ++i)
        {
            C[i]= dist(gen);
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
            mm_jki(a, A, B, b, C, NN, NN, NN);
            // Calculate the time spent in the computation
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double durationL = static_cast<long double>(duration.count());
            elapsed_time += (durationL * nano_to_secondL);
        }
        long double average_duration = elapsed_time / ntrials;
        long double flops = flop_count / average_duration;
        mflops_jki.push_back(flops / (1.e6L));
    }
    
    return mflops_jki;
}


std::vector<long double> dtest_jki(int ntrials)
{
    std::vector<long double> mflops_jki;
    for (int NN = 2; NN <= 512; ++NN)
    {
        // Create Inputs
        std::vector<double> A(NN * NN);
        std::vector<double> B(NN * NN);
        std::vector<double> C(NN * NN);
        // Initialize Inputs
        std::uniform_real_distribution<double> dist(0.0, 1.0); // range [0,1]
        double a = dist(gen);
        double b = dist(gen);
        for (int i = 0; i < NN * NN; ++i)
        {
            A[i]= dist(gen);
        }
        for (int i = 0; i < NN * NN; ++i)
        {
            B[i]= dist(gen);
        }
        for (int i = 0; i < NN * NN; ++i)
        {
            C[i]= dist(gen);
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
            mm_jki(a, A, B, b, C, NN, NN, NN);
            // Calculate the time spent in the computation
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            long double durationL = static_cast<long double>(duration.count());
            elapsed_time += (durationL * nano_to_secondL);
        }
        long double average_duration = elapsed_time / ntrials;
        long double flops = flop_count / average_duration;
        mflops_jki.push_back(flops / (1.e6L));
    }
    
    return mflops_jki;
}


int main(int argc, char* argv[])
{
    int ntrials = 5;
    std::string input = "";

    if (argc > 1)
    {
        input = argv[1];
    }

    if (input.compare("fkij") == 0)
    {
        std::cout << "Running mm_kij (float)..." << std::endl;
        saveVector(ftest_kij(ntrials), "mm_kij_float");
    } 
    else if (input.compare("fjki") == 0)
    {
        std::cout << "Running mm_jki (float)..." << std::endl;
        saveVector(ftest_jki(ntrials), "mm_jki_float");
    }
    else if (input.compare("dkij") == 0)
    {
        std::cout << "Running mm_kij (double)..." << std::endl;
        saveVector(dtest_kij(ntrials), "mm_kij_double");
    }
    else if (input.compare("djki") == 0)
    {
        std::cout << "Running mm_jki (double)..." << std::endl;
        saveVector(dtest_jki(ntrials), "mm_jki_double");
    }
    else
    {
        std::cout << "Running everything..." << std::endl;
        saveVector(ftest_kij(ntrials), "mm_kij_float");
        saveVector(ftest_jki(ntrials), "mm_jki_float");
        saveVector(dtest_kij(ntrials), "mm_kij_double");
        saveVector(dtest_jki(ntrials), "mm_jki_double");
    }

    return 0;
}