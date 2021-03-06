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
size_t space;
size_t total_space = 0;
int status_flag = 0;

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

void request(char *pid, char *sort_type, size_t mem_size){
    // Search for smallest hole in memory by traversing
    // the linked list
    MemoryBlock *h = NULL;
    if (strcmp(sort_type,"B") == 0){
        MemoryBlock *iter = memory;
        size_t min = -1;
        while(iter){
            size_t hsize = (iter->end_mem - iter->start_mem + 1);
            if (iter->processid == NULL && mem_size<=hsize && hsize < min ){
                min = hsize;
                h = iter;
            }
            iter = iter->next;
        }
    }else{
        printf("Invalid Input\n");
        return;
    }
    if(!h || h->processid != NULL){
        printf("No hole of sufficient size\n");
        return;
    } else {
        total_space += mem_size;
    }
    h->processid = malloc(sizeof(char)*strlen(pid)+1);
    strcpy(h->processid,pid);
    if(h->end_mem - h->start_mem + 1 == mem_size){
        return; 
    }
    h->next = allocate("",h->start_mem + mem_size,h->end_mem,h,h->next);
    h->end_mem = h->start_mem + mem_size - 1;
    printf("Successfully allocated %ld to process %s\n",mem_size,pid);
    return;
}
int release(char *pid){
    printf("Releasing memory for process %s\n",pid);
    int flag = 1;
    MemoryBlock *iter = memory;
    while(iter){
        if(iter->processid && strcmp(iter->processid,pid) == 0){
            total_space -= (iter->end_mem - iter->start_mem); 
            free(iter->processid);
            iter->processid = NULL;
            flag = 0;
        }
        if(iter->processid == NULL && iter->prev && iter->prev->processid == NULL){
            MemoryBlock *t = iter->prev;
            iter->prev = t->prev;
            if(t->prev){
                t->prev->next = iter;
            }
            iter->start_mem = t->start_mem;
            free(t);
        }
        if(iter->prev == NULL){
            memory = iter;
        }
        iter = iter->next;
    }
    if(flag){
        printf("Nothing released\n");
    }
    printf("Successfully released memory for process %s\n",pid);
    return flag;
}

void status_report(){
    MemoryBlock *iter = memory;
    if (status_flag == 0){
        printf("Partitions [Allocated Memory = %06zu]\n",total_space-1);
        while(iter) {
            if(iter->processid) {
                printf("Address [%06zu : %06zu] ", iter->start_mem, iter->end_mem);
                printf("Process %s\n", iter->processid);
            }
            iter=iter->next;
        }
    }
    if (status_flag == 1){
        printf("Holes [Free Memory = %06zu]\n",(starting_mem - total_space + 1));
        while(iter) {
            if(!iter->processid) {
                printf("Address[%06zu : %06zu] len = %zu\n", iter->start_mem, iter->end_mem, (iter->end_mem - iter->start_mem + 1));
            }
            iter=iter->next;
        }
    }
}

int main(int argc, char *argv[])
{
    //int starting_mem = atoi(argv[1]);
    sscanf(argv[1], "%zu", &starting_mem);
    memory = allocate("",0,starting_mem-1,NULL,NULL);
    printf("Allocated %ld bytes of memory\n", starting_mem);
    printf("command>");
    
    char command[128];
    fflush(stdout);
    read(0,command,128);

    while (strcmp(command,"Exit")!= 0)
    {
        sscanf(command, "%s %s %ld %s", cmd, pid, &space, sort_type);

        if (strcmp("RQ", cmd) == 0){
            request(pid,sort_type,space);
        }
        else if (strcmp("RL", cmd) == 0){
            release(pid);
            // printf("%s\n", cmd);
            // printf("%s\n", pid);
        }
        else if (strcmp("Status", cmd) == 0){ // Status report
            // printf("Status Report Here\n");
            status_report();
            status_flag = 1;
            status_report();
            status_flag = 0;
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



