//Author: Abdullah Khan
//Student Id: 250907213
//Description: This program is the part 2 of assignment 1 and it adds 2 numbers together which takes number 1 (x) from parent process and number 2 (y) from the child process through the pipe and then the parent process outputs the required sum
//Date: 04/10/2019

//these are the required libraries to run the program
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	int x, y; //variable for the values
	pid_t pid; //id of the fork
	int fd[2]; //buffer for the pipe
	if (pipe(fd) < 0) { //if the pipe fails return a pipe error 
		perror("pipe error\n");
		exit(0);
	}
	printf("A pipe is created for communication between parent (PID %d) and child\n", getpid()); //tell the user the pipe is created
	pid = fork();
	if (pid < 0) { //if the fork returns and error and ent the program
		printf("fork error\n");
		exit(0);
	}
	if (pid > 0) { //this is the parent process
		printf("parent (PID %d) created a child (PID %d)\n", getpid(), pid);
		x = atoi(argv[1]); //read the x value from the arg 
		printf("parent (PID %d) Reading X = %d from the user\n", getpid(), x);
		wait(NULL);
		read(fd[0], &y, sizeof(y)); //read the y value from the pipe and store it in the y variable in the parent process
		printf("parent (PID %d) Reading Y from the pipe (Y = %d)\n", getpid(), y, y);
		int sum = x + y; //add both the numbers together 
		printf("parent (PID %d) adding X + Y = %d\n", getpid(), sum); //print the sum
	}
	if (pid == 0) { //this is the child process
		y = atoi(argv[2]); //read the arg and store into y
		printf("child (PID %d) Reading Y = %d from the user\n", getpid(), y);
		write(fd[1], &y, sizeof(y)); //write the y value to the pipe
		printf("child (PID %d) Writing Y into the pipe\n", getpid());
		exit(0);
	}
	return 0;
}
