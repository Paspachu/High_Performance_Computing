1. Information 
1.1 File Details
- L1BLAS: includes axpy function that computes the level 1 BLAS
- L2BLAS: includes gemv function that computes the level 2 BLAS
- L3BLAS: includes gemm function that computes the level 3 BLAS
- p1top4: includes all functions necessary to solve problems 1 to 4
    * daxpy
    * daxpy_unroll
    * daxpy_unroll_shortcut: this only works for n = 2048 and block_size = 1, 2, 4, 8, 16, 32, 64
    * dgemv
    * dgemm
    * dtest_L1_individual: tests performance of daxpy for one specific n size (in double)
    * dtest_L1: test the performance of daxpy with mutiple trials and for different n sizes (in double)
    * dtest_L1_unroll_individual: tests performance of daxpy_unroll for one specific n size and one specific block_size (in double)
    * dtest_L1_unroll: tests the performance of daxpy_unroll with mutiple trials for n = 2048 and block_size = 1, 2, 4, 8, 16, 32, 64 (in double)
    * dtest_L2_individual: tests performance of dgemv for one specific m and n sizes (in double)
    * dtest_L2: test the performance of dgemv with mutiple trials and for different m=n sizes (in double)
    * dtest_L3_individual: tests performance of dgemm for one specific m, n, and p sizes (in double)
    * dtest_L3: test the performance of dgemm with mutiple trials and for different m=n=p sizes (in double)
- printNdVector: includes functions to print vectors and matrices
- testFunctions: includes all functions necessary to solve problem 5
    * ftest_L1_individual: tests performance of axpy for one specific n size (in float)
    * ftest_L1: test the performance of axpy with mutiple trials and for different n sizes (in float)
    * ftest_L2_individual: tests performance of gemv for one specific m and n sizes (in float)
    * ftest_L2: test the performance of gemv with mutiple trials and for different m=n sizes (in float)
    * ftest_L3_individual: tests performance of gemm for one specific m, n, and p sizes (in float)
    * ftest_L3: test the performance of gemm with mutiple trials and for different m=n=p sizes (in float)
-saveVector: includes functions to save a vector to a txt file

1.2 Notes
- The number of trials are fixed to 10 for all the test (ntrials = 10)
- For Level 3 BLAS (both float and double), due too long processing time, only 74 different n sizes are tested (incremented by 14 from 2 to 1024); still takes more than 10 minutes
- The performance plots can be found in the pdf file
- (Mentioned in pdf) the values of MFLOPs are different when the codes are ran separately to when the codes are ran all in once

2. Instruction to run
- To compile the codes, please execute the following command in the terminal or bash: 'source hw2.cmpl'
- Then, to run the codes, simply execute the following command in the terminal or bash: './xmain'
- Enter the number that you want to test (in default running all tests will be ran)
- After the code finishes running, the performance will be printed out for different n sizes and the performance values are saved in a txt file
