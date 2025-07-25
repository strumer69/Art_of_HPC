#include <mpi.h>
#include <iostream>


int main(int argc, char** argv) {
    std::cout << "Hello,  before !" << std::endl;
    MPI_Init(&argc, &argv);
    std::cout << "     Hello,   beween !" << std::endl;
    MPI_Finalize();
    std::cout << "Hello,  after!" << std::endl;

    return 0;
}

