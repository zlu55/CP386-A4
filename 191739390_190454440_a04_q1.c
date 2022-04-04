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

//Global resource variables
int *available = NULL;
int threadRan = 0;
int threadOrder[5] = {0, 0, 0, 0, 0};
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

pthread_mutex_t lock;
pthread_cond_t cond;

//Compares two arrays, returns 0 if arr1 > arr2, otherwise returns 0
int compareArray(int *arr1, int *arr2){
  for(int i = 0; i < 4; i++){
    if(arr1[i] > arr2[i]){
      return 0;
    }
  }
  return 1;
}

//Safety algorithm to determine if request is safe
int safetyAlgo(int customer, int needs[4]){
  int work[4] = {0, 0, 0, 0};
  for(int i = 0; i < 4; i++){
    work[i] = available[i];
  }
  int finish[5] = {0, 0, 0, 0, 0};

  for(int i = 0; i < 4; i++){
    work[i] += needs[i] + need[customer][i];
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

//Check if resources to release is less than amount allocated
int checkForResources(int customer, int needs[4]){
  for(int i = 0; i < 4; i++){
    if(allocated[customer][i] < needs[i]){
      return 0;
    }
  }
  return 1;
}

//Allocate resources according to request
void requestResources(int customer, int needs[4]){
  for(int i = 0; i < 4; i++){
    need[customer][i] -= needs[i];
    allocated[customer][i] += needs[i];
    available[i] -= needs[i];
  }
}

//Release resources according to request
void releaseResources(int customer, int release[4]){
  for(int i = 0; i < 4; i++){
    need[customer][i] += release[i];
    allocated[customer][i] -= release[i];
    available[i] += release[i];
  }
}

void printSafeSeq(){
  int tempAvail[4] = {0, 0, 0, 0};
  for(int i = 0; i < 4; i++){
    tempAvail[i] = available[i];
  }
  int tempAlloc[5][4] = {{0, 0, 0, 0},
			 {0, 0, 0, 0},
			 {0, 0, 0, 0},
			 {0, 0, 0, 0},
			 {0, 0, 0, 0}};
  int tempNeed[5][4] = {{6, 4, 7, 3},
			{4, 2, 3, 2},
			{2, 5, 3, 3},
			{6, 3, 3, 2},
			{5, 5, 7, 5}};
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 4; j++){
      tempAlloc[i][j] = allocated[i][j];
      tempNeed[i][j] = need[i][j];
    }
  }
  
  int c = 0;
  int t = 0;
  printf("Safe Sequence is: ");
  int safe[5] = {0, 0, 0, 0, 0};
  for(int i = 0; i < 5; i++){
    if(safe[i] == 0){
      c = 0;
      for(int j = 0; j < 4; j++){
	if(tempAvail[j] >= tempNeed[i][j]){
	  c++;
	}
      }
      if(c == 4){
	printf("%d ", i);
	int copyAlloc[4] = {tempAlloc[i][0], tempAlloc[i][1], tempAlloc[i][2], tempAlloc[i][3]};
	for(int k = 0; k < 4; k++){
	  tempNeed[i][k] += copyAlloc[k];
	  tempAlloc[i][k] -= copyAlloc[k];
	  tempAvail[k] += copyAlloc[k];
	}
	safe[i] = 1;
	threadOrder[t] = i;
	t++;
	i = -1;
      }
    }
  }
  printf("\n");
}

//Print out status update
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

void* runThread(void* arg){
  int c = *((int *) arg);

  //lock resources
  pthread_mutex_lock(&lock);

  //Check for proper order
  while(c != threadOrder[threadRan])
    pthread_cond_wait(&cond, &lock);

  printf("--> Customer/Thread %d\n", c);
  printf("    Allocated resources: ");
  for(int i = 0; i < 4; i++){
    printf("%d ", allocated[c][i]);
  }
  printf("\n");

  printf("    Needed: ");
  for(int i = 0; i < 4; i++){
    printf("%d ", need[c][i]);
  }
  printf("\n");
  printf("    Available: ");
  for(int i = 0; i < 4; i++){
    printf("%d ", available[i]);
  }
  printf("\n");
  sleep(1);
  
  printf("    Thread has started\n");
  
  for(int i = 0; i < 4; i++){
    available[i] += allocated[c][i];
    need[c][i] += allocated[c][i];
    allocated[c][i] = 0;
  }
  printf("    Thread has finished\n");
  printf("    Thread is releasing resources\n");
  printf("    New  Available: ");
  for(int i = 0; i < 4; i++){
    printf("%d ", available[i]);
  }
  printf("\n");

  sleep(1);
  threadRan++;

  //Unlock resources
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&lock);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  available = malloc((argc - 1) * sizeof(int));
  char command[20];
  int numCustomers = (int)(sizeof(max)/sizeof(max[0]));
  int numResources = argc - 1;
  int args[4] = {0, 0, 0, 0};
  int cust = 0, out = 0;
  char code[10];
  pthread_t threads[5];
  pthread_attr_t attr;
  pthread_attr_init(&attr);

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

  //Ask for input
  printf("(RQ RL Status Run Exit): ");
  fflush(stdout);
  read(0, command, 20);

  //Loop until user enters "Exit"
  while(strcmp(command, "Exit") != 0){
    //Get input from user
    sscanf(command, "%s %d %d %d %d %d", code, &cust, &args[0], &args[1], &args[2], &args[3]);

    //Perform actions based on command given (Turn user input into array of info)
    if(strcmp(code, "RQ") == 0){
      out = safetyAlgo(cust, args);
      if(out == 1){
	printf("State is safe, and request is satisfied\n");
	requestResources(cust, args);
      }else{
	printf("State is unsafe\n");
      }
    }else if(strcmp(code, "RL") == 0){
      out = checkForResources(cust, args);
      if(out == 1){
	printf("State is safe, and request is satisfied\n");
	releaseResources(cust, args);
      }else{
	printf("State is unsafe\n");
      }
    }else if(strcmp(code, "Status") == 0){
      statusUpdate();
    }else if(strcmp(code, "Run") == 0){
      printSafeSeq(); //Get safe sequence

      //Create and join threads
      for(int i = 0; i < 5; i++){
	pthread_create(&threads[i], &attr, runThread,(void *)(&threadOrder[i]));
      }
      for(int i = 0; i < 5; i++){
	pthread_join(threads[i], NULL);
      }
      
    }else if(strcmp(code, "Exit") == 0){
      exit(0);
    }else{
      printf("Invalid input, use one of RQ, RL, Status, Run, Exit.\n");
    }

    printf("(RQ RL Status Run Exit): ");
    fflush(stdout);
    read(0, command, 20);
  }
}
