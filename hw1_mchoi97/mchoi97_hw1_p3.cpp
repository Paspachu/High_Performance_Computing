#include <iostream>

int main() {
    // Using 32-bit integer
    int32_t sp_ans = (int32_t) 200 * 300 * 400 * 500;
    std::cout << "32-bit: " <<  sp_ans << std::endl; 

    // Using 64-bit integer
    int64_t dp_ans = (int64_t) 200 * 300 * 400 * 500;
    std::cout << "64-bit: " << dp_ans << std::endl; 

    return 0;
}