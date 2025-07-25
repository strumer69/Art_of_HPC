# Art_of_HPC
for practicing the excercises from the Book series "Art_of_HPC"
* you can find this valuable book from here: https://theartofhpc.com/

* excercise2.1 --> compile the code -->g++ ecercise2.1.cpp -o a.out
* then run it: -->mpiexec -n 2 ./a.out  --> what is the result and why? 1- It says that without communication (MPI), all processes behave identically. 2- Once we add MPI (like MPI_Comm_rank), we can differentiate behavior per process.



* 
