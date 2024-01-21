#include "refBLAS.hpp"


void run_dL1_test(int ntrials)
{
    std::vector<long double> dL1_performance = dtest_L1(ntrials);
    print_vector(dL1_performance, "L1 performance double");
    saveVector(dL1_performance, "L1_performance_double");
}

void run_dL1_unroll_test(int ntrials)
{
    std::vector<long double> dL1_unroll_performance = dtest_L1_unroll(ntrials);
    print_vector(dL1_unroll_performance, "L1 unroll performance double");
    saveVector(dL1_unroll_performance, "L1_unroll_performance_double");
}

void run_dL2_test(int ntrials)
{
    std::vector<long double> dL2_performance = dtest_L2(ntrials);
    print_vector(dL2_performance, "L2 performance double");
    saveVector(dL2_performance, "L2_performance_double");
}

void run_dL3_test(int ntrials)
{
    std::vector<long double> dL3_performance = dtest_L3(ntrials);
    print_vector(dL3_performance, "L3 performance double");
    saveVector(dL3_performance, "L3_performance_double");
}

void run_fL1_test(int ntrials)
{
    std::vector<long double> fL1_performance = ftest_L1(ntrials);
    print_vector(fL1_performance, "L1 performance float");
    saveVector(fL1_performance, "L1_performance_float");
}

void run_fL2_test(int ntrials)
{
    std::vector<long double> fL2_performance = ftest_L2(ntrials);
    print_vector(fL2_performance, "L2 performance float");
    saveVector(fL2_performance, "L2_performance_float");
}

void run_fL3_test(int ntrials)
{
    std::vector<long double> fL3_performance = ftest_L3(ntrials);
    print_vector(fL3_performance, "L3 performance float");
    saveVector(fL3_performance, "L3_performance_float");
}

int main()
{
    int ntrials = 10;
    int input = 0;

    std::cout << "Enter the number that you want to test:" << std::endl;
    std::cout << "1: Level 1 BLAS using double (Problem 1)" << std::endl;
    std::cout << "2: Level 1 Unrolled BLAS using double (Problem 2)" << std::endl;
    std::cout << "3: Level 2 BLAS using double (Problem 3)" << std::endl;
    std::cout << "4: Level 3 BLAS using double (Problem 4)" << std::endl;
    std::cout << "5: Level 1 BLAS using float (Problem 5)" << std::endl;
    std::cout << "6: Level 2 BLAS using float (Problem 5)" << std::endl;
    std::cout << "7: Level 3 BLAS using float (Problem 5)" << std::endl;
    std::cout << "0: Run everything!" << std::endl;
    std::cin >> input;
    std::cout << "Running started! Might take a while..." << std::endl; 

    switch (input)
    {
        case 1:
            // Level 1 BLAS using double
            run_dL1_test(ntrials);
            break;
        case 2:
            // Level 1 Unroll BLAS using double
            run_dL1_unroll_test(ntrials);
            break;
        case 3:
            // Level 2 BLAS using double
            run_dL2_test(ntrials);
            break;
        case 4:
            // Level 3 BLAS using double
            run_dL3_test(ntrials);
            break;
        case 5:
            // Level 1 BLAS using float
            run_fL1_test(ntrials);
            break;
        case 6:
            // Level 2 BLAS using float
            run_fL2_test(ntrials);
            break;
        case 7:
            // Level 3 BLAS using float
            run_fL3_test(ntrials);
            break;
        default:
            run_dL1_test(ntrials);
            run_dL1_unroll_test(ntrials);
            run_dL2_test(ntrials);
            run_dL3_test(ntrials);
            run_fL1_test(ntrials);
            run_fL2_test(ntrials);
            run_fL3_test(ntrials);
            break;
    }
    
    return 0;
}