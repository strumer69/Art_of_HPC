#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    //  int name_len-->  hold the lenght of the processor name
    //  MPI sets this value when we call MPI_Get_processor_name()
    int name_len;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Get_processor_name(processor_name, &name_len);

    cout << "hello from processor " << processor_name
            << ", rank " << world_rank 
            <<  " out of "  << world_size << " processes " << endl;

    MPI_Finalize();
    return 0;

}
