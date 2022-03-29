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

int main(int argc, char *argv[])
{
    int starting_mem = atoi(argv[1]);
    printf("Allocated %d bytes of memory\n", starting_mem);
    printf("command>");
    
    char command[128];
    fflush(stdout);
    read(0,command,128);

    while (strcmp(command,"Exit")!= 0)
    {
        printf("%s", cmd);
        sscanf(command, "%s %s %d %s", cmd, pid, &space_requested, sort_type);

        if (strcmp("RQ", cmd) == 0){
            printf("%s\n", cmd);
            printf("%s\n", pid);
            printf("%d\n", space_requested);
            printf("%s\n", sort_type);
        }
        else if (strcmp("RL", cmd) == 0){
            printf("%s\n", cmd);
            printf("%s\n", pid);
        }
        else if (strcmp("Status", cmd) == 0){ // Status report
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



