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

    
    int local_array[2]= {1,2};
    int buffer[2]={0,0}; // buffer to hold the reduced result

    // Print each process's array 
    for (int i = 0; i < size; i++) {
        if (i == rank) {
            cout << "process " << rank << " content: ";
            for (int j = 0; j < 2; j++) {
                cout << local_array[j] << ", ";
            }
            cout << endl;
        }
        MPI_Barrier(MPI_COMM_WORLD); // Ensure ordered printing
    }
    MPI_Allreduce(local_array, buffer, 2, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    cout << " reduced result = "<< buffer[0] << " , " << buffer[1] << endl;

    
    MPI_Finalize();
    return 0;
}
//mpic++  code.cpp -o a.out
//mpirun -np 2 ./a.out
//mpirun --oversubscribe -np 4 ./a.out