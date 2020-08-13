#include <iostream>
#include "include/Iterator_Functions.h"

#include <omp.h>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/openmp/openmp.hpp>
#include <boost/numeric/odeint/external/mpi/mpi.hpp>
#include <mpi-ext.h>
int main(int argc, char* argv[])
{
    using namespace boost::multiprecision;
    mpz_int number;
    unsigned int thread_number;
    unsigned int* threads;

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        int value = 17;
        int result = MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        if (result == MPI_SUCCESS)
            std::cout << "Rank 0 OK!" << std::endl;
    } else if (rank == 1) {
        int value;
        int result = MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        if (result == MPI_SUCCESS && value == 17)
            std::cout << "Rank 1 OK!" << std::endl;
    } else if (rank == 2) {
        std::cout << "This is the 3rd thread" << std::endl;
    }
    std::cout << "This operation is done by thread " << rank << std::endl;
    int MPIX_Query_cuda_support(void);
    std::cout << "CUDA Support: " << MPIX_Query_cuda_support << std::endl;

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    std::cout << "Comm_size: " << world_size << std::endl;

    MPI_Finalize();



    return 0;

}
