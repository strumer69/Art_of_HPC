#include <mpi.h>
#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <algorithm>  // Required for std::max_element


using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int my_ints[5];          // Each process has 5 integers
    
    srand(time(NULL) + rank); // Seed differently for each process
    for (int i = 0; i < 5; i++) {
        my_ints[i] = rand() % 21; // Fill with random numbers (0-20)
        
    }

    // Print each process's array 
    for (int i = 0; i < size; i++) {
        if (i == rank) {
            cout << "process " << rank << " content: ";
            for (int j = 0; j < 5; j++) {
                cout << my_ints[j] << ", ";
            }
            cout << endl;
        }
        MPI_Barrier(MPI_COMM_WORLD); // Ensure ordered printing
    }
    int local_max = *std::max_element(my_ints , my_ints+5); // find local max value

    //Use MPI_reduce to transfer the max value to the rank 0 process
    int global_max;
    MPI_Reduce(&local_max, &global_max, 1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD); // reduce to find the maximum random number
    if (rank ==0) {
        std::cout << "max number is:" << global_max << std::endl;
    }
    MPI_Finalize();
    return 0;
}
//mpic++  code.cpp -o a.out
//mpirun -np 2 ./a.out
//mpirun --oversubscribe -np 4 ./a.out