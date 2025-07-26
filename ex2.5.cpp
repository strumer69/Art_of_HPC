#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int world_rank , world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // get rank
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // get size

    if (world_rank == 0){
        std::cout << "total number of processes: " << world_size << std::endl;
    }
    MPI_Finalize();
    return 0;
}
//mpic++  code.cpp -o a.out
//mpirun -np 2 ./a.out
//mpirun --oversubscribe -np 4 ./a.out