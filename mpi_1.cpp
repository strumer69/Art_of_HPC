#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N =5;
    int A[N] = { 1, 2, 3, 4,5};
    int B[N] = {6,7,8,9,10};

    
      // Ensure the number of processes divides N evenly
    if (N % size != 0 && rank == 0) {
        std::cerr << "Error: Number of processes must divide 5 evenly." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
     // Each process computes a partial dot product
    int elements_per_proc = N / size;
    int start = rank * elements_per_proc;
    int end = start + elements_per_proc;
    int partial_sum = 0;

    for (int i = start; i < end; i++) {
        partial_sum += A[i] * B[i];
    }
     // Sum all partial sums into a global result on rank 0
    int global_sum;
    MPI_Reduce(&partial_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the result from rank 0
    if (rank == 0) {
        std::cout << "matrix A=" << A[0] << " " << A[1] << " " << A[2] << " " << A[3] << " " << A[4] << std::endl;
        std::cout << "matrix B=" << B[0] << " " << B[1] << " " << B[2] << " " << B[3] << " " << B[4] << std::endl;
    
        std::cout << "Dot product (result): " << global_sum << std::endl;
        std::cout << "(Expected: 1*6 + 2*7 + 3*8 + 4*9 + 5*10 = 6 + 14 + 24 + 36 + 50 = 130)" << std::endl;
    }
      MPI_Finalize();
    return 0;
}
// mpirun --oversubscribe -np  5 ./a.out