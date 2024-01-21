** Problem 1 **
- Each function is separated into two files (one .cpp file and one .hpp file)
- All header files are included into hw3_p1_header.hpp file
- For plots, please check the pdf file

** Problem 2 **
- hw3_p2.cpp saves the performance of each case in a txt file
- To run please follow:
    1. in terminal or bash enter: "source hw3_p2.cmpl"
    2. to run all cases in default optimization enter: "./xprob2"
        * to run {jik} using float in default optimization enter: "./xprob2 fjki"
        * to run {jik} using double in default optimization enter: "./xprob2 djki"
        * to run {kij} using float in default optimization enter: "./xprob2 fkij"
        * to run {kij} using double in default optimization enter: "./xprob2 dkij"
    3. to run all cases in O3 optimization change line 8 in hw3_p2.cmpl to:
        "g++ -std=c++14 -O3 -o xprob2 -I. hw3_p2.cpp -L. -lhw3_p2;"
    4. then repeat process 2
    5. to run all cases in fastmath optimization change line 8 in hw3_p2.cmpl to:
        "g++ -std=c++14 -ffast-math -o xprob2 -I. hw3_p2.cpp -L. -lhw3_p2;"
    6. then repeat process 2

** Problem 3 **
- hw3_p3.cpp saves the performance of strassen_mm function for different sizes n (there are 9 sizes total)
- To run please follow:
    1. in terminal or bash enter: "source hw3_p3.cmpl"
    2. in terminal or bash enter: "./xprob3"