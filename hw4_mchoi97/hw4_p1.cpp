#include <iostream>
#include <fstream>
#include <random>


void writeMatrixToFile(std::vector<double> matrix, int dim, std::string filename) {
    std::ofstream outfile(filename, std::ios::out | std::ios::binary);
    outfile.write((char*)&dim, sizeof(dim));
    outfile.write((char*)&matrix[0], matrix.size()*sizeof(double));
    outfile.close();
}

void readMatrixFromFile(std::vector<double> matrix, int& dim, std::string filename) {
    std::ifstream infile(filename, std::ios::in | std::ios::binary);
    infile.read((char*)&dim, sizeof(dim));
    infile.read((char*)&matrix[0], matrix.size()*sizeof(double));
    infile.close();
}

void saveVector(const std::vector<double> &v, const std::string title)
{
    std::ofstream output_file("./" + title + ".txt");
    std::ostream_iterator<double> output_iterator(output_file, "\n");
    std::copy(std::begin(v), std::end(v), output_iterator);
}



int main() {
    std::cout << "Do you want to save the results in text files? (Press 0: no, 1: yes)" << std::endl;
    int input = 0;
    std::cin >> input;
    std::cout << "Running..." << std::endl;

    /* Note that dim=16 is added as a dummy variable, since I continuously got very low bandwidth for the first iteration in the for loop. */
    /* So, when plotting, dim=16 case is not included. */
    std::vector<int> dimensions = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    std::vector<double> write_times, read_times;
    static std::random_device rd;
    static std::mt19937 gen(rd()); 

    for (int dim : dimensions) {
        std::vector<double> matrix(dim*dim);
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        for (int i=0; i<dim*dim; i++) {
            matrix[i] = dist(gen);
        }

        // Write matrix to file
        auto start = std::chrono::high_resolution_clock::now();
        writeMatrixToFile(matrix, dim, "matrix.bin");
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> write_time = end - start;
        write_times.push_back(dim*dim*sizeof(double) / write_time.count());

        // Read matrix from file
        start = std::chrono::high_resolution_clock::now();
        readMatrixFromFile(matrix, dim, "matrix.bin");
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> read_time = end - start;
        read_times.push_back(dim*dim*sizeof(double) / read_time.count());
    }

    // Change the bandwidth unit to MB/s
    for (int i=0; i<dimensions.size(); i++)
    {
        write_times[i] = write_times[i]/(1024*1024);
        read_times[i] = read_times[i]/(1024*1024);
    }

    // Print results
    std::cout << "Dimension\tWrite Bandwidth\tRead Bandwidth\n";
    for (int i=0; i<dimensions.size(); i++) {
        std::cout << dimensions[i] << "\t\t" << write_times[i] << " MB/s\t\t" << read_times[i] << " MB/s\n";
    }

    // Save results
    if (input == 1)
    {
        saveVector(write_times, "write");
        saveVector(read_times, "read");
        std::cout << "Results saved in text files (unit in MB/s)" << std::endl;
    }

    return 0;
}