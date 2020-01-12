//Student: Abdullah Khan
//Number: 250907213
//Class: 3305
//Assignment: #2 part1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

//these are the global variables for x, y, and z set to as specified in the assignment
int x = 10; 
int y = 20; 
int z = 0;

void *threadAddsIntegers() { //this is the thread function
	z = x + y;
} 

int main () {

pthread_t thread_1; //creation of a thread variable
pid_t pid; //the id of the fork

pid = fork(); //fork which creates child

if (pid < 0) { //in case the fork is unsucessful
	printf("fork unsuccessful"); //print out appropriate message
	exit(1); //exit the program
}

if (pid > 0) { //for the parent
	wait(NULL); //wait for the child to complete
	printf("In Parent (after Child completion): z = %d\n", z); //print the z value from the parent
	pthread_create(&thread_1, NULL, threadAddsIntegers, NULL); //create a thread which adds integers
	pthread_join(thread_1, NULL); //join the thread to the parent
	printf("In Parent (after thread_1 termination): z = %d\n", z); //print the value of z after the termination of thread
}

if (pid == 0) { //for the child
	z = x + y; //set the data as required in the assignment
}
   return 0;    
}
