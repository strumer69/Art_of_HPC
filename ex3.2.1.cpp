#include <mpi.h>
#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int my_ints[5];          // Each process has 5 integers
    int local_sum = 0;       // Sum of this process's my_ints
    int global_sum = 0;      // Will store sum of all local_sums (via MPI_Allreduce)

    srand(time(NULL) + rank); // Seed differently for each process
    for (int i = 0; i < 5; i++) {
        my_ints[i] = rand() % 5; // Fill with random numbers (0-4)
        local_sum += my_ints[i]; // Compute local sum
    }

    // Print each process's array and its local sum
    for (int i = 0; i < size; i++) {
        if (i == rank) {
            cout << "process " << rank << " random vales: ";
            for (int j = 0; j < 5; j++) {
                cout << my_ints[j] << ", ";
            }
            cout << " --> the local sum = " << local_sum << endl;
        }
    MPI_Barrier(MPI_COMM_WORLD); // Ensure ordered printing
    }

    // Use MPI_Allreduce to compute the global sum (sum of all local_sums)
    MPI_Allreduce(
        &local_sum,         // Send buffer (local sum of this process)
        &global_sum,        // Receive buffer (will hold the global sum)
        1,                  // Number of elements to sum (just 1, since local_sum is a single int)
        MPI_INT,            // Data type
        MPI_SUM,            // Operation (MPI_SUM for summation)
        MPI_COMM_WORLD      // Communicator
    );

    // Print the global sum (same on all processes)
    if (rank == 0) {
        cout << "------------------------------" << endl;
        cout << "Global sum (sum of all local sums) = " << global_sum << endl;
    }
    // devide each number in my_ints by global_sum
     for (int i = 0; i < size; i++) {
        if (i == rank) {
            cout << "process " << rank << " content devided by global sum: ";
            for (int j = 0; j < 5; j++) {
                cout << (double (my_ints[j])/global_sum) << ", ";
            }
            cout << endl;
        }
    MPI_Barrier(MPI_COMM_WORLD); // Ensure ordered printing

    }
    MPI_Finalize();
    return 0;
}
//mpic++  code.cpp -o a.out
//mpirun -np 2 ./a.out
//mpirun --oversubscribe -np 4 ./a.out