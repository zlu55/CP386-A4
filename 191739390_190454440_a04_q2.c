/*
Zachary Luloff
191739390
lulo9390@mylaurier.ca
zlu55

Adam Gerrish
190454440
gerr4440@mylaurier.ca
adamgerrish

CP386 Assignment 4 - Question 2
Date: 2022-03-24
Description: Uses Best-Fit algorithm for contiguous memory allocation. 
This project will involve managing a contiguous region of memory of 
size MAX where addresses may range from 0 ... MAX - 1.

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define MAX 10

char cmd[3];
char pid[3];
char sort_type[2];
int space;

// Create a struct similar to linked list to store memory blocks. ]
// Contains next, previous pointers, starting and ending memory addresses
// and the pid 
typedef struct MemoryBlock
{
    struct MemoryBlock *prev,*next;
    size_t start_mem, end_mem;
    char *processid;

} MemoryBlock;

//init memory block that will be used in main
MemoryBlock *memory;
// init memory size to zero
size_t starting_mem = 0;


void request(){
    //if first insert 
    //else best fit
}
void release(){
    //release code here
}

//Function to store user input into a memory block struct
MemoryBlock *allocate(char *pid, size_t start_mem, size_t end_mem, MemoryBlock *prev, MemoryBlock *next){
   
    // allocate memory, and store all data that we recieved from the user into the 
    // structure. Set up the linked list and insert accordingly.
    MemoryBlock *m = malloc(sizeof(MemoryBlock));
    m->start_mem = start_mem;
    m->end_mem = end_mem;
    if (strlen(pid) != 0){
        m->processid = malloc(sizeof(char)*(strlen(pid)+1));
        strcpy(m->processid,pid);
    } else {
        m->processid = NULL;
    }
    m->next = next;
    m->prev = prev;
    if (prev)
        prev->next = m;
    if (next)
        next->prev = m;
    return m;
}

int main(int argc, char *argv[])
{
    //temp for testing, will be initialized to a block structure
    int starting_mem = atoi(argv[1]);
    printf("Allocated %d bytes of memory\n", starting_mem);
    printf("command>");
    
    char command[128];
    fflush(stdout);
    read(0,command,128);

    while (strcmp(command,"Exit")!= 0)
    {
        printf("%s", cmd);
        sscanf(command, "%s %s %d %s", cmd, pid, &space, sort_type);

        if (strcmp("RQ", cmd) == 0){
            //testing
            printf("%s\n", cmd);
            printf("%s\n", pid);
            printf("%d\n", space);
            printf("%s\n", sort_type);
        }
        else if (strcmp("RL", cmd) == 0){
            //testing
            printf("%s\n", cmd);
            printf("%s\n", pid);
        }
        else if (strcmp("Status", cmd) == 0){ // Status report
            //testing
            printf("Status Report Here\n");
        }
        else if (strcmp("Exit", cmd) == 0){ // Status report
            printf("Exiting\n");
            break;
        }
        else{ //Invalid input
            printf("This command is invalid\n");
        }

        printf("command>");
        fflush(stdout);
        read(0, command, 128);
            
    }
}



