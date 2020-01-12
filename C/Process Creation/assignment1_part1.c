//Author: Abdullah Khan
//Student Id: 250907213
//Description: This program is the part 1 of assignment 1 and it shows the creation of 2 childprocess a child of a child process being creating with the fork method
//Date: 04/10/2019

//these are the required libraries to run the program
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main () {
	pid_t pid1;
	pid1 = fork(); //the first fork creating the first child
	if (pid1 <0) { //if the fork is unsuccesful
		printf("fork unsuccessful\n");
		exit(1);
	}
	if (pid1>0) { //the parent process
		wait(NULL);
		pid_t pid3;
		pid3 = fork(); //child number 2 fork
		if (pid3 <0) {
			printf("fork unsuccessful\n");
			exit(1);
		}
		if (pid3>0) { //parent process
			wait(NULL);
			exit(1);
		}
		if (pid3==0) {
			printf("parent (PID %d) created child_2 (PID %d)\n", getppid(), getpid());
			printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2...\n", getpid());
			printf("From the external program: ");
			execl("external_program.out", "external_program.out", NULL); //call the external program
			exit(1);
		} 	
	}
	if (pid1==0) { //the first child created
		printf("parent process (PID %d) created child_1 (PID %d)\n", getppid(), getpid());
		printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", getppid(), getpid());
		pid_t pid2;
		pid2 = fork(); //second fork creating child of child
		if (pid2 <0) {
			printf("fork unsuccessful\n");
			exit(1);
		}
		if (pid2>0) { //child fork gets completed
			wait(NULL);
			printf("child_1 (PID %d) is now completed\n", getpid());
		}
		if (pid2==0) { //child's child fork
			printf("child_1 (PID %d) created child_1.1 (PID %d)\n", getppid(), getpid());
		}
		exit(1); 	
	}
	return 0;
}
