/*
Zachary Luloff
191739390
lulo9390@mylaurier.ca
zlu55

Adam Gerrish
190454440
gerr4440@mylaurier.ca
adamgerrish
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>


//Global resource variables In textbook pdf pg432
int available[];
int max[][];
int allocated[][];
int need[][];

void safetyAlgo(){

}

int main(int argc, char *argv[]){
  int availableResources[argc];
  char command[10];
  int customerResources[5][4] = {{6, 4, 7, 3},
				 {4, 2, 3, 2},
				 {2, 5, 3, 3},
				 {6, 3, 3, 2},
				 {5, 5, 7, 5}};
  int numCustomers = (int)(sizeof(customerResources)/sizeof(customerResources[0]));
  int numResources = argc - 1;

  //Print the number of customers
  printf("Number of Customers: %d\n", numCustomers);

  //Print the available resources
  printf("Currently Available resources: ");
  for(int i = 1; i < argc; i++){
    availableResources[i] = atoi(argv[i]);
    printf("%d ", availableResources[i]);
  }
  printf("\n");

  //Print the customer resources
  printf("Maximum resources from file:\n");
  for(int i = 0; i < numCustomers; i++){
    for(int j = 0; j < numResources; j++){
      printf("%d ", customerResources[i][j]);
    }
    printf("\n");
  }

  //Loop until user enters "Exit"
  while(1){
    //Get input from user
    printf("(RQ RL Status Run Exit): ");
    scanf("%s", command);
    while(getchar() != '\n'); //Empty input buffer

    //Perform actions based on command given (Turn user input into array of info)
    if(strcmp(command, "RQ") == 0){
      printf("RQ select\n");
    }else if(strcmp(command, "RL") == 0){
      printf("RL select\n");
    }else if(strcmp(command, "Status") == 0){
      printf("Status select\n");
    }else if(strcmp(command, "Run") == 0){
      printf("Run select\n");
    }else if(strcmp(command, "Exit") == 0){
      printf("Exit select");
      exit(0);
    }else{
      printf("Invalid input, use one of RQ, RL, Status, Run, Exit.\n");
    }
    
  }
}
