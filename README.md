# Art_of_HPC
for practicing the excercises from the Book series "Art_of_HPC"
* you can find this valuable book from here: https://theartofhpc.com/

## Volum 1 : theoretical concepts
* https://github.com/VictorEijkhout/TheArtofHPC_pdfs/tree/main/vol1

## Volum 2 : practical
* https://github.com/VictorEijkhout/TheArtofHPC_pdfs/blob/main/vol2/EijkhoutParallelProgramming.pdf
* 
#### excercise2.1 Write a ‘hello world’ program, without any MPI in it, and run it in parallel
with mpiexec or your local equivalent. Explain the output.
compile the code -->g++ ecercise2.1.cpp -o a.out
* then run it: -->mpiexec -n 2 ./a.out
*  what is the result and why?
*  - 1- It says that without communication (MPI), all processes behave identically.
*  - 2- Once we add MPI (like MPI_Comm_rank), we can differentiate behavior per process.



#### excercise2.2 Add the commands MPI_Init and MPI_Finalize to your code. Put three different print statements in your code: one before the init, one between init and finalize, and one after the finalize. Again explain the output
* Compile: mpic++ excercise2.2.cpp -o a.out 
* Run: mpiexec -n 2 ./a.out
* result: we will see that again each of the MPI processes run the same program.

#### Exercise 2.3. Use the command MPI_Get_processor_name. Confirm that you are able to run a program that uses two different nodes.
*line--> char processor_name[MPI_MAX_PROCESSOR_NAME]; explanation:
* MPI_MAX_PROCESSOR_NAME is a constant defined by MPI. It tells you the maximum length a processor name can be (usually 256 characters). we can think to it as: char processor_name[256];
* -
* MPI_Get_processor_name(processor_name, &name_len);--> This MPI function:--> Fills the array processor_name with the name of the processor (like node01, lrz12, ubuntu, etc.)
* Sets name_len to the actual length of that name (number of characters).
#### why is it usefull to know the name of the processors?
* its usefull for the following tasks:
*  Debugging
*  Load balancing
*  Optimizing network performance
*  Making sure MPI processes are distributed as expected
*- 
  #### Exercise 2.4. Write a program where each process prints out a message reporting its number, and how many processes there are:
  * --> refer to the code ex2.4.cpp
#### exercise2.4_2 --> Write a second version of this program, where each process opens a unique file and writes to it. On some clusters this may not be advisable if you have large numbers of processors, since it can overload the file system.
  *  --> refer to the code ex2.4_2.cpp
#### Exercise 2.5. Write a program where only the process with number zero reports on how many processes there are in total.
