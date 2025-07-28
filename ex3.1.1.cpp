#include <mpi.h>
#include <iostream>
#include <cstdlib> //for rand()
#include <ctime> //for time()

using namespace std;
int main(int argc , char** argv){
    MPI_Init(&argc , &argv);

    int rank , size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); // get rank
    MPI_Comm_size(MPI_COMM_WORLD,&size); // get size

    srand(time(NULL)+rank); // seed random number generator with time and rank
    int local_rand = rand () % 100; // generate a random number between 0 and 99

    int max_rand;
    MPI_Reduce(&local_rand, &max_rand, 1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD); // reduce to find the maximum random number
    if (rank ==0) {
        std::cout << "max number is:" << max_rand << std::endl;
    }
    MPI_Finalize();
    return 0;
}

//mpic++  code.cpp -o a.out
//mpirun -np 2 ./a.out
//mpirun --oversubscribe -np 4 ./a.out