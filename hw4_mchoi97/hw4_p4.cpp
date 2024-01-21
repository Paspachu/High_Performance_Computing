#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>
#include <mpi.h>


template<typename T>
void my_broadcast(T* data, int count, int root, MPI_Comm comm)
{
    int rank, size, tag = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    MPI_Datatype data_type;
    switch (sizeof(T))
    {
    case 1:
        data_type = MPI_CHAR;
        break;
    case 4:
        data_type = MPI_INT;
        break;
    case 8:
        data_type = MPI_DOUBLE;
        break;

    default:
        std::cerr << "Error: Invalid message to broadcast" << std::endl;
        break;
    }

    if (rank == root)
    {
        for (int i = 0; i < size; ++i)
        {
            if (i != root)
            {
                MPI_Send(data, count, data_type, i, tag, comm);
            }
        }
    }
    else 
    {
        MPI_Recv(data, count, data_type, root, tag, comm, &status);
    }
    MPI_Barrier(comm);
}



int main(int argc, char **argv)
{
    MPI_Init(&argc, & argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<double> Bcast_bandwidth, my_bandwidth;
    /* Note that e = 0 is a dummy variable, since the first process is always dramatically slowing than upcoming next processes. */
    /* So, when plotting, the case for e = 0 is excluded so we are examining the message of size 8 bytes to 128MB. */
    for (int e = 0; e < 26; ++e)
    {
        int count = static_cast<int>(std::pow(2, e));
        std::vector<int> buffer(count);
        for (int i = 0; i < buffer.size(); ++i)
        {
            buffer[i] = i;
        }

        // Time MPI_Bcast
        auto start = std::chrono::high_resolution_clock::now();
        MPI_Bcast(buffer.data(), count, MPI_INT, 0, MPI_COMM_WORLD);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;
        Bcast_bandwidth.push_back(count*sizeof(int) / elapsed_time.count());

        // Time my_broadcast
        start = std::chrono::high_resolution_clock::now();
        my_broadcast(buffer.data(), count, 0, MPI_COMM_WORLD);
        end = std::chrono::high_resolution_clock::now();
        elapsed_time = end - start;
        my_bandwidth.push_back(count*sizeof(int) / elapsed_time.count());
    }

    if (rank == 0)
    {
        for (int i = 0; i < Bcast_bandwidth.size(); ++i)
        {
            std::cout << std::fixed << Bcast_bandwidth[i] << "\t" << my_bandwidth[i] << std::endl;
        }
    }
    
    MPI_Finalize();
    return 0;
}