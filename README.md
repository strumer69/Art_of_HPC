# Art_of_HPC
for practicing the excercises from the Book series "Art_of_HPC"
* you can find this valuable book from here: https://theartofhpc.com/

## Volum 1 : theoretical concepts
* https://github.com/VictorEijkhout/TheArtofHPC_pdfs/tree/main/vol1

## Volum 2 : practical
* https://github.com/VictorEijkhout/TheArtofHPC_pdfs/blob/main/vol2/EijkhoutParallelProgramming.pdf
* 
### excercise2.1 Write a ‘hello world’ program, without any MPI in it, and run it in parallel
with mpiexec or your local equivalent. Explain the output.
compile the code -->g++ ecercise2.1.cpp -o a.out
* then run it: -->mpiexec -n 2 ./a.out
*  what is the result and why?
*  - 1- It says that without communication (MPI), all processes behave identically.
*  - 2- Once we add MPI (like MPI_Comm_rank), we can differentiate behavior per process.



### excercise2.2 Add the commands MPI_Init and MPI_Finalize to your code. Put three different print statements in your code: one before the init, one between init and finalize, and one after the finalize. Again explain the output
* Compile: mpic++ excercise2.2.cpp -o a.out 
* Run: mpiexec -n 2 ./a.out
* result: we will see that again each of the MPI processes run the same program.

### Exercise 2.3. Use the command MPI_Get_processor_name. Confirm that you are able to run a program that uses two different nodes.
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
### exercise2.4_2 --> Write a second version of this program, where each process opens a unique file and writes to it. On some clusters this may not be advisable if you have large numbers of processors, since it can overload the file system.
  *  --> refer to the code ex2.4_2.cpp
### Exercise 2.5. Write a program where only the process with number zero reports on how many processes there are in total.
* --> refer to program cpp2.5.cpp

### Exercise 2.6. Is the number N = 2, 000, 000, 111 prime? Let each process test a disjoint set of integers, and print out any factor they find. You don’t have to test all integers < N : any factor is at most √N ≈ 45, 200.
* We want to check if: 𝑁=2,000,000,111 is a prime number.
* A number is not prime if it has any factor i such that: 2 ≤ 𝑖 ≤ sqrt(𝑁)= 44,721
* why? --> If N = a × b and both a and b are greater than √N, their product is greater than N. So one of them must be less than or equal to √N. --> So we only need to check the numbers 2 to 44721.

##### what does (long long ) mean? :
* long long N = 2000000111LL --> declare a 64-bit integer variable named N and assign it the value 2000000111.
* long long--> 	A data type in C++ for large integers, usually 64 bits (can store very large numbers).
* A normal int (typically 32 bits) can hold values only up to about 2.1 billion (2,147,483,647). 2000000111 is close to that limit. By using long long, we make sure the number fits safely.
* The LL suffix (or ll) ensures the compiler treats the number as a long long literal, not as an int.

##### int sqrtN = static_cast<int>(std::sqrt(N)); explanation:
  * std::sqrt(N)	Calls the square root function from the standard math library (<cmath>). It returns a double (e.g. 212.13).
  * static_cast<int>(...)	Converts the result from double to int (i.e., drops the decimal part). It's a safe and explicit type conversion in C++.
  * .
  * .
  * .
##### int end = (world_rank == world_size - 1) ? sqrt_N : start + chunk - 1; explanation:
* If this process is the last process, then set end = sqrt_N. Otherwise, set end = start + chunk - 1.

*   
*   
*   
### Exercise 2.7.  Allocate on each process an array: int my_ints[10]; and fill it so that process 0 has the integers 0 ⋯ 9, process 1 has 10 ⋯ 19, et cetera. It may be hard to print the output in a non-messy way.
* --> refer to ex2.7.cpp
* #### why MPI_Barrier? 
* In parallel programs, processes might run at different speeds. If one process finishes earlier, it might continue execution before others finish their work.Using MPI_Barrier, you can make sure that all processes reach a certain point before any of them continues. 
* Note--> if we run the code without the MPI_Barrier, we will see a bit of mess in printout!!!
* 
.
### Exercise 2.8. Argue that this strategy is not optimal. Can you come up with a better distribution? Load balancing is further discussed in HPC book, section-2.10. page 36/644
* This strategy (2.7 answer) assumes that every task takes the same time. But in many real-world problems (like prime testing or scientific simulations),
  - some parts of the data are more computationally expensive than others.
  - for example, testing numbers for primality: higher numbers usually take longer to test.
  - If all heavy data goes to the last process, that process becomes a **bottleneck**.
* For better distribution, we can use the following code:

```cpp
for (int i = 0; i < 10; i++) {
    my_ints[i] = world_rank + i * world_size;
}
```
### For all true/false questions, if you answer that a statement is false, give a one-line explanation.
### Exercise 2.9. * True or false: mpicc is a compiler.
*
* --> False – mpicc is not a compiler itself; it is a wrapper around a real compiler (like gcc) that adds the necessary MPI headers and libraries for compilation.
* .
* .
### Exercise 2.10. T/F? * 1. In C, the result of **MPI_Comm_rank** is a number from zero to number-of-processes-minus-one, inclusive.
* -->
* True
2. In **Fortran**, the result of MPI_Comm_rank is a number from one to number-of-processes, inclusive.
* -->
* True
### Exercise 2.11. What is the function of a hostfile?

* A hostfile specifies the list of nodes (computers) and optionally the number of processes to run on each when executing an MPI program using mpiexec or mpirun. It helps distribute tasks across multiple machines.

### Exercise 3.1. How would you realize the following scenarios with MPI collectives?
* 1-  Let each process compute a random number. You want to print the maximum of these numbers to your screen. 
* 2-  Each process computes a random number again. Now you want to scale these numbers by their maximum
* #### answer 1 --> refer to the program ex3.1.1.cpp
* MPI_Reduce(image ref: page 38/644 the book art of HPC - Vo,um 2):
* <img width="463" height="355" alt="image" src="https://github.com/user-attachments/assets/601c957e-c022-4403-ae06-4ed6c7307943" />

* explanation:
```cpp
  MPI_Reduce(&local_rand, &max_rand, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
```
* what is being reduced? --> The integer local_rand from each process being transfered to the root (usually rank 0)
* The reduction operation is **MPI_MAX**, so the maximum of all local_rand values is computed.


