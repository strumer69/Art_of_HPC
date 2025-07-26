#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int world_rank, world_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); //get number of processes


    cout << "hello from processor "  
         << ", rank " << world_rank   
         <<  " out of "  << world_size 
         << " processes " << endl;

    MPI_Finalize();
    return 0;

}
//mpic++ -o ex2.4 ex2.4.cpp
//mpirun -np 2 ./ex2.4
//mpirun --oversubscribe -np 4 ./ex2.4
