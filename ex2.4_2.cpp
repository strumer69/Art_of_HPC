#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int world_rank , world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // get rank
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // get size

    //generate uniq filename for each process
    std::string filename = "process_" +std::to_string(world_rank) + ".txt";

    //open the file and write the message
    std::ofstream outfile(filename);
    if (outfile.is_open()){
        outfile << "Hello from process " << world_rank 
                << " out of " << world_size << " processes."<<std::endl;
        outfile.close();
    }
    else{
        std::cerr << " process " << world_rank << "could not open file" << std::endl;
    }
    MPI_Finalize();
    return 0;
}
//mpic++  ex2.4_2.cpp -o ex2.4_2.out
//mpirun -np 2 ./ex2.4_2.out
//mpirun --oversubscribe -np 4 ./ex2.4_2.out