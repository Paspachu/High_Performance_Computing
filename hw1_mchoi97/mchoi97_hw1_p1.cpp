#include <iostream>
#include <cmath>

int main() {
    // Practical measure for Single Precision
    int i = 0;
    float sp_one = 1;
    float sp_approx_one = 1 + powf(0.5, i);
    while (sp_one - sp_approx_one != 0) {
        i++;
        sp_approx_one = 1 + powf(0.5, i);
    }
    std::cout << "Single Precision: " << i << std::endl;

    // Practical measure for Double Precision
    int j = 0;
    double dp_one = 1;
    double dp_approx_one = 1 + pow(0.5, j);
    while (dp_one - dp_approx_one != 0) {
        j++;
        dp_approx_one = 1 + pow(0.5, j);
    }
    std::cout << "Double Precision: " << j << std::endl;

    return 0;
}
