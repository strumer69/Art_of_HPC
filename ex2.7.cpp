#include <mpi.h>
#include <iostream>
using namespace std;
int main(int argc , char** argv){
    MPI_Init(&argc , &argv);

    int rank , size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); // get rank
    MPI_Comm_size(MPI_COMM_WORLD,&size); // get size

    int my_ints[10];
    //cout << my_ints << endl; // print address of my_ints array
    //cout <<*my_ints << endl; // print address of first element of my_ints array

    // cout << "rank= "<< rank << " size= " << size << endl;
    for (int i = 0 ; i<10 ; i++){
        my_ints[i] = rank * 10 + i; 
        cout << "process " << rank << ": my_ints[" << i << "] = " << my_ints[i] << endl;
    }
    cout <<"------------------------------" << endl;
    MPI_Barrier(MPI_COMM_WORLD); // synchronize all processes

    for (int i=0 ;i<size ; i++){
        if (i ==rank){
            cout << "process " << rank << " content: ";
            for (int j=0; j<10 ; j++){
                cout << my_ints[j] << ", " ;
            }
            cout << endl;
        }
        MPI_Barrier(MPI_COMM_WORLD); // wait for next processor
    }
    MPI_Finalize();
    return 0;
}

//mpic++  code.cpp -o a.out
//mpirun -np 2 ./a.out
//mpirun --oversubscribe -np 4 ./a.out