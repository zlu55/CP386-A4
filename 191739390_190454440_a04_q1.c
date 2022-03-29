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
#include <stdatomic.h>

//Global resource variables In textbook pdf pg432
int *available = NULL;
int max[5][4] = {{6, 4, 7, 3},
		 {4, 2, 3, 2},
		 {2, 5, 3, 3},
		 {6, 3, 3, 2},
		 {5, 5, 7, 5}};
int allocated[5][4] = {{0, 0, 0, 0},
		       {0, 0, 0, 0},
		       {0, 0, 0, 0},
		       {0, 0, 0, 0},
		       {0, 0, 0, 0}};
int need[5][4] = {{6, 4, 7, 3},
		  {4, 2, 3, 2},
		  {2, 5, 3, 3},
		  {6, 3, 3, 2},
		  {5, 5, 7, 5}};
 
typedef atomic_flag mut_t;
volatile mut_t mutex = ATOMIC_FLAG_INIT;

#define acquire(m) while (atomic_flag_test_and_set(m))
#define release(m) atomic_flag_clear(m)

int compareArray(int *arr1, int *arr2){
  for(int i = 0; i < 5; i++){
    if(arr1[i] > arr2[i]){
      return 0;
    }
  }
  return 1;
}

int safetyAlgo(int customer, int needs[4]){
  int work[4] = {0, 0, 0, 0};
  for(int i = 0; i < 4; i++){
    work[i] = available[i];
  }
  int finish[5] = {0, 0, 0, 0, 0};

  for(int i = 0; i < 4; i++){
    work[customer] += needs[i] + need[customer][i];
  }

  for(int i = 0; i < 5; i++){
    if(finish[i] == 0 && compareArray(needs, work) == 1){
      for(int j = 0; j < 4; j++){
	work[j] += allocated[i][j];
      }
      finish[i] = 1;
    }
  }

  for(int i = 0; i < 5; i++){
    if(finish[i] == 0){
      return 0;
    }
  }
  return 1;
}

void statusUpdate(){
  printf("Available: \n");
  for(int i = 0; i < 4; i++){
    printf("%d ", available[i]);
  }
  printf("\n");

  printf("Max: \n");
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 4; j++){
      printf("%d ", max[i][j]);
    }
    printf("\n");
  }

  printf("Allocated: \n");
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 4; j++){
      printf("%d ", allocated[i][j]);
    }
    printf("\n");
  }

  printf("Need: \n");
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 4; j++){
      printf("%d ", need[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]){
  available = malloc((argc - 1) * sizeof(int));
  char command[20];
  //char argsChar[10][10];
  //char *p;
  
  int numCustomers = (int)(sizeof(max)/sizeof(max[0]));
  int numResources = argc - 1;

  //Print the number of customers
  printf("Number of Customers: %d\n", numCustomers);

  //Print the available resources
  printf("Currently Available resources: ");
  for(int i = 1; i < argc; i++){
    available[i - 1] = atoi(argv[i]);
    printf("%d ", available[i - 1]);
  }
  printf("\n");

  //Print the customer resources
  printf("Maximum resources from file:\n");
  for(int i = 0; i < numCustomers; i++){
    for(int j = 0; j < numResources; j++){
      printf("%d ", max[i][j]);
    }
    printf("\n");
  }

  //Loop until user enters "Exit"
  while(1){
    //Get input from user
    printf("(RQ RL Status Run Exit): ");
    scanf("%s", command);
    while(getchar() != '\n'); //Empty input buffer

    //char *p = strtok(command, " ");
    /*
    p = strtok(command, " ");
    printf("%s\n", p);
    while(p){
      
      p = strtok(NULL, " ");
      printf("%d\n", atoi(p));
    }
    */
    /*j = 0, ctr = 0;
    for(int i = 0; i < strlen(command); i++){
      if(command[i] == ' ' || command[i] == '\0'){
	argsChar[ctr][j]='\0';
	ctr++;
	j = 0;
      }else{
	argsChar[ctr][j] = command[i];
	j++;
      }
      //argsChar[arg++] = p;
      //p = strtok(NULL, " ");
      }*/
    
    
    printf("ARGS COLLECTED");
    for(int i = 0; i < strlen(command); i++){
      //printf("%d ", atoi(argsChar[i]));
    }
    printf("ARGS SUCCESS");

    //Perform actions based on command given (Turn user input into array of info)
    if(strcmp(command, "RQ") == 0){
      printf("RQ select\n");
      
    }else if(strcmp(command, "RL") == 0){
      printf("RL select\n");
    }else if(strcmp(command, "Status") == 0){
      printf("Status select\n");
      statusUpdate();
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
