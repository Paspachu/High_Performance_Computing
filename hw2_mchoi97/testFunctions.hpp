#ifndef TESTFUNCTIONS_HPP
#define TESTFUNCTIONS_HPP

#include <iostream>
#include <chrono>
#include <random>
#include "L1BLAS.hpp"
#include "L2BLAS.hpp"
#include "L3BLAS.hpp"

void ftest_L1_individual(int NN);
std::vector<long double> ftest_L1(int ntrials);
void ftest_L2_individual(int MM, int NN);
std::vector<long double> ftest_L2(int ntrials);
void ftest_L3_individual(int MM, int NN, int PP);
std::vector<long double> ftest_L3(int ntrials);

#endif // TESTFUNCTIONS_HPP