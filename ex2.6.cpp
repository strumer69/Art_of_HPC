#include <mpi.h>
#include <iostream>
#include <cmath>



int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int world_rank , world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // get rank
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // get size
    
    long long N = 2000000111LL;
    int sqrtN = static_cast<int>(std::sqrt(N));

    //devide the range among the processes
    int range= sqrtN -1 ; //we startfrom 2
    int chunk = range / world_size; //size of each chunk (slice) 
    int start = world_rank *chunk +2 ;// start of each chunk
    int end = (world_rank == world_size -1) ? sqrtN : start +chunk -1;

    //find prime numbers in the range
    for (int i = start; i <= end ; ++i){
        if (i==0) continue; // avoid devide by zero
        if (N % i ==0 ){
            std::cout << "process " << world_rank << " found factor :" << i << std::endl;
        }
    }
    MPI_Finalize();
    return 0;
}
//mpic++  code.cpp -o a.out
//mpirun -np 2 ./a.out
//mpirun --oversubscribe -np 4 ./a.out