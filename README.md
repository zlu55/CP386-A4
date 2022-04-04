# CP386-A4

## Breakdown

### Question 1

Question 1 is a multi-threaded program that implements the banker's algorithm.
Customers request and release resources from the bank. The banker will keep track of the resources. The
banker will grant a request if it satisfies the safety algorithm. If a request does not leave the system in a
safe state, the banker will deny it.

Go to [Question 1](191739390_190454440_a04_q1.c)

### Question 2

Question 2 uses a Best-Fit algorithm for contiguous memory allocation. This project manages a contiguous region of memory of size MAX where addresses may range from 0 ... MAX − 1. This program responds to three different requests:  
• Request for a contiguous block of memory (RQ)  
• Release of a contiguous block of memory (RL)  
• Report the regions of free and allocated memory (Status)  

Go to [Question 2](191739390_190454440_a04_q2.c)

## Makefile

The makefile is included in this repository and can be found under makefile in the repository.
[makefile](makefile)

## Individual Contibution

Each group member was assigned one question from the assignment each.
* Question 1: Zachary Luloff, user zlu55
* Question 2: Adam Gerrish, user adamgerrish

## Features and Examples

### Question 1
The banker's algorithm is used to properly manage resources in order to avoind a deadlock.  The program uses data structures to keep track of the resources, and updates them accordingly.  The program allows the user to request and release resources, only if it leaves the system in a safe state. It also allows the user to request a status update, run the system, or exit.

Below is a test case:
./Question1 10 5 7 8
Number of Customers: 5
Currently Available resources: 10 5 7 8 
Maximum resources from file:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 5 7 5 
(RQ RL Status Run Exit): RQ 0 1 0 0 1
State is safe, and request is satisfied
(RQ RL Status Run Exit): RQ 1 1 1 1 1
State is safe, and request is satisfied
(RQ RL Status Run Exit): RQ 2 2 2 2 2
State is safe, and request is satisfied
(RQ RL Status Run Exit): RQ 3 1 1 1 1
State is safe, and request is satisfied
(RQ RL Status Run Exit): RQ 4 1 0 0 0
State is safe, and request is satisfied
(RQ RL Status Run Exit): Status
Available: 
4 1 3 3 
Max: 
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 5 7 5 
Allocated: 
1 0 0 1 
1 1 1 1 
2 2 2 2 
1 1 1 1 
1 0 0 0 
Need: 
5 4 7 2 
3 1 2 1 
0 3 1 1 
5 2 2 1 
4 5 7 5 
(RQ RL Status Run Exit): Run
Safe Sequence is: 1 3 2 0 4 
--> Customer/Thread 1
    Allocated resources: 1 1 1 1 
    Needed: 3 1 2 1 
    Available: 4 1 3 3 
    Thread has started
    Thread has finished
    Thread is releasing resources
    New  Available: 5 2 4 4 
--> Customer/Thread 3
    Allocated resources: 1 1 1 1 
    Needed: 5 2 2 1 
    Available: 5 2 4 4 
    Thread has started
    Thread has finished
    Thread is releasing resources
    New  Available: 6 3 5 5 
--> Customer/Thread 2
    Allocated resources: 2 2 2 2 
    Needed: 0 3 1 1 
    Available: 6 3 5 5 
    Thread has started
    Thread has finished
    Thread is releasing resources
    New  Available: 8 5 7 7 
--> Customer/Thread 0
    Allocated resources: 1 0 0 1 
    Needed: 5 4 7 2 
    Available: 8 5 7 7 
    Thread has started
    Thread has finished
    Thread is releasing resources
    New  Available: 9 5 7 8 
--> Customer/Thread 4
    Allocated resources: 1 0 0 0 
    Needed: 4 5 7 5 
    Available: 9 5 7 8 
    Thread has started
    Thread has finished
    Thread is releasing resources
    New  Available: 10 5 7 8 
(RQ RL Status Run Exit): Exit

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

### Zachary Luloff
Fourth year computer science student at Wilfrid Laurier University.

## License

Distributed under the MIT License.

