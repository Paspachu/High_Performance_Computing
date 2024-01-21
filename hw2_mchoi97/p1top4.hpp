#ifndef P1TOP4_HPP
#define P1TOP4_HPP

#include <iostream>
#include <chrono>
#include <random>

// For answering questions
void daxpy(double a, const std::vector<double> &x, std::vector<double> &y);
void daxpy_unroll_shortcut(double a, const std::vector<double> &x, std::vector<double> &y, int block_size);
void daxpy_unroll(double a, const std::vector<double> &x, std::vector<double> &y, int block_size);
void dgemv(double a , const std::vector<std::vector<double>> &A, const std::vector<double> &x, double b, std::vector<double> &y);
void dgemm(double a, const std::vector<std::vector<double>> &A, const std::vector<std::vector<double>> &B, double b, std::vector<std::vector<double>> &C);

// For testing
void dtest_L1_individual(int NN);
std::vector<long double> dtest_L1(int ntrials);
void dtest_L1_unroll_individual(int NN, int block_size);
std::vector<long double> dtest_L1_unroll(int ntrials);
void dtest_L2_individual(int MM, int NN);
std::vector<long double> dtest_L2(int ntrials);
void dtest_L3_individual(int MM, int NN, int PP);
std::vector<long double> dtest_L3(int ntrials);

#endif // P1TOP4_HPP