# CP386-A4

## Breakdown

### Question 1

Question 1 is a multi-threaded program that implements the banker's algorithm.
Customers request and release resources from the bank. The banker will keep track of the resources. The
banker will grant a request if it satisfies the safety algorithm. If a request does not leave the system in a
safe state, the banker will deny it.

### Question 2

Question 2 uses a Best-Fit algorithm for contiguous memory allocation. This project manages a contiguous region of memory of size MAX where addresses may range from 0 ... MAX − 1. This program responds to three different requests:
• Request for a contiguous block of memory (RQ)
• Release of a contiguous block of memory (RL)
• Report the regions of free and allocated memory (Status)

## Makefile

The makefile is included in this repository and can be found under makefile in the repository.
[makefile](CP386-A4/makefile)

## Individual Contibution

Each group member was assigned one question from the assignment each.
* Question 1: 
* Question 2: Adam Gerrish, user adamgerrish

## Features and Examples

### Question 1 

### Question 2 
The contiguous memory allocation uses memory partitions to allocate memory. These partitions could be fixed or variable size partitions allocated according to the best fit method. The memory fragmentation is a common problem that affects these partition memory allocation system.

The program allows the user to input a total memory size, and continously asks for a command between RQ, RL, Status, or Exit

* RQ - Request memory   
command>RQ P0 200000 B  
Successfully allocated 200000 to process P0  
command>RQ P1 350000 B  
Successfully allocated 350000 to process P1  
command>RQ P2 300000 B  
Successfully allocated 300000 to process P2  

If the memory is full, it will give a message and ask for a new command   
command>RQ P5 80000 B  
No hole of sufficient size

* RL - Release Memory  
command>RL P0  
Releasing memory for process P0  
Successfully released memory for process P0  

* Status - Status Report  
Partitions [Allocated Memory = 770000]  
Address [200000 : 549999] Process P1  
Address [550000 : 849999] Process P2  
Address [850000 : 969999] Process P3  
Holes [Free Memory = 230000]  
Address[000000 : 199999] len = 200000  
Address[970000 : 999999] len = 30000  

* Exit  
Terminates the program

## About Developers

### Adam Gerrish
Third year computer science student at Wilfrid Laurier University.

## License

Distributed under the MIT License.

