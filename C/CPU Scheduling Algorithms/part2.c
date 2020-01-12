//Student: Abdullah Khan
//Number: 250907213
//Class: 3305
//Assignment: #2 part2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//These are the constants we are going to use
#define maxLineLength 100000 //the maximum length of string
#define maxNumberOfProcesses 100 //the max number of processes
#define maxTurnaround 1000 //max number of times a process in swapped to

struct process { //create a type which represents a process
	char *name; //process name
	int timeCPU; //burst time
	int waitFCFS; //wait time of process for FCFS calculations
	int waitSJF; //wait time of process for sjf calculations
	int turnaroundRR; //time takes a process 
};

int getTurnaround(struct process processes[], char *processName, int num); //function to get the actual turnaround value for a specific process

int main(int argc, char *filename[]) { //program takes 2 arguments, 1 for the executable file and the input text file
	
	if (argc != 2) { //if the user have anything other than 2 arguments send an error 
		printf("Error! You must run the program in this form: ./part2.o [input file name]\n");
		exit(1);
	}
	
	//create a variable to read a file and write to a new file called output.txt
	FILE *readFile = fopen(filename[1], "r");
	FILE *writeFile = fopen("output.txt", "w");
	
	//if the file does not exist or something is spelled wrong
	if (readFile == NULL) {
		printf("Unable to read file! Please give a proper file name in the current directory.\n");
		exit(EXIT_FAILURE);
	}
	//if the file is not able to be created for whatever readon 
	if (writeFile == NULL) {
		printf("Unable to create file.\n");
		exit(EXIT_FAILURE);
	}
	
	int queueNumber = 1; //start with queue 1 and then move to next one
	int timeQuantum = 0; //holds the tq from the txt file
	char line[maxLineLength]; //holds the text of the line
	char *segment; //holds segments of the line
	struct process processes[maxNumberOfProcesses]; //for each process
	int processCounter; //number of processes in the line
	
	for (int i = 0; i < maxNumberOfProcesses; i++) { //initialize the processes array to NULL
		processes[i].name = NULL;
		processes[i].timeCPU = -1;
		processes[i].waitFCFS = -1;
		processes[i].waitSJF = -1;
		processes[i].turnaroundRR = -1;
	}
	//this loops get each line from input text file and sets the variables above appropriately
	while (fgets(line, maxLineLength, readFile) != NULL) {
		segment = strtok(line, " "); //get the first string seperated by space
		processCounter = 0; //initialize to zero 
		if (strcmp(segment, "q") == 0) { //checks if file is in correct form
			segment = strtok(NULL, " "); 
	
			if (atoi(segment) == queueNumber) {
				segment = strtok(NULL, " ");
				
				if (strcmp(segment, "tq") == 0) {
					segment = strtok(NULL, " ");
					timeQuantum = atoi(segment);
					segment = strtok(NULL, " ");
					while (segment != NULL) { //gets each process and stores into the processes array
						processes[processCounter].name = segment; //sets the name of process
						segment = strtok(NULL, " ");
						processes[processCounter].timeCPU = atoi(segment); //sets the burst time of process
						segment = strtok(NULL, " ");
						processCounter++; //increment process counter
					}
				}
			}	
		}
		
		int numProcesses = processCounter; //set a variable to the total number of processes
		int tq = timeQuantum; //set a variable to the time quantum
		
		//FCFS -----------------------------------------------------------------------------------------------------------
		//below is the code for the FCFS scheduling algorithm
		int processWaitCounterFCFS = 0;
		int totalWaitFCFS = 0;
		double avgWaitFCFS = 0;
		fprintf(writeFile, "Ready Queue %d Applying FCFS Scheduling:\n\n", queueNumber);
		fprintf(writeFile, "Order of selection by CPU:\n");
		for (int i = 0; i < numProcesses; i++) {
			fprintf(writeFile, "%s ", processes[i].name); //this prints the order the processes are coming in
		}
		fprintf(writeFile, "\n\nIndividual waiting times for each process:\n");		
		for (int i = 0; i < numProcesses; i++) {
			processes[i].waitFCFS = processWaitCounterFCFS;
			fprintf(writeFile, "%s = %d\n", processes[i].name, processes[i].waitFCFS); //this prints the waiting time of each process
			processWaitCounterFCFS = processWaitCounterFCFS + processes[i].timeCPU;
		}
		for (int i = 0; i < numProcesses; i++) {
			totalWaitFCFS = totalWaitFCFS + processes[i].waitFCFS; //adds all of the waiting times together
		}
		avgWaitFCFS = (double)totalWaitFCFS / (double)numProcesses; //find the avg of the waiting times
		fprintf(writeFile, "\nAverage waiting time = %.1f\n", avgWaitFCFS);  //prints out the average
		
		//SJF --------------------------------------------------------------------------------------------------------------
		//below is the code for the SJF scheduling algorithm
		int processWaitCounterSJF = 0;
		int totalWaitSJF = 0;
		double avgWaitSJF = 0;
		struct process processesSortedSJF[numProcesses]; //create a sorted array of processes so that the shortest job can be done first
		
		for (int i = 0; i < numProcesses; i++) { //duplicates the processes array to the sorted array
			processesSortedSJF[i].name = processes[i].name;
			processesSortedSJF[i].timeCPU = processes[i].timeCPU;
		}
		
		//below is the bubble sorting algorithm to sort the array we just duplicated
		for (int i = (numProcesses - 1); i >= 0; i--) {
			for (int j = 1; j <= i; j++) {
				if (processesSortedSJF[j-1].timeCPU > processesSortedSJF[j].timeCPU) {
					char *tempName = processesSortedSJF[j-1].name;
					int tempTimeCPU = processesSortedSJF[j-1].timeCPU;
					processesSortedSJF[j-1].name = processesSortedSJF[j].name;
					processesSortedSJF[j-1].timeCPU = processesSortedSJF[j].timeCPU;
					processesSortedSJF[j].name = tempName;
					processesSortedSJF[j].timeCPU = tempTimeCPU;
				}
			}
		}
		//now we can treat this like an FCFS because everything is sorted
		fprintf(writeFile, "\nReady Queue %d Applying SJF Scheduling:\n\n", queueNumber);
		fprintf(writeFile, "Order of selection by CPU:\n");
		for (int i = 0; i < numProcesses; i++) {
			fprintf(writeFile, "%s ", processesSortedSJF[i].name); //prints the processes in the order they come
		}
		fprintf(writeFile, "\n\nIndividual waiting times for each process:\n");
		for (int i = 0; i < numProcesses; i++) {
			processesSortedSJF[i].waitSJF = processWaitCounterSJF;
			fprintf(writeFile, "%s = %d\n", processesSortedSJF[i].name, processesSortedSJF[i].waitSJF); //sets the wait times and writes them to the file
			processWaitCounterSJF = processWaitCounterSJF + processesSortedSJF[i].timeCPU;
		}
		for (int i = 0; i < numProcesses; i++) {
			totalWaitSJF = totalWaitSJF + processesSortedSJF[i].waitSJF; 
		}
		avgWaitSJF = (double)totalWaitSJF / (double)numProcesses; //get the average of wait times
		fprintf(writeFile, "\nAverage waiting time = %.1f\n", avgWaitSJF); //prints the averages
		
		//RR --------------------------------------------------------------------------------------------------------------------
		//below is the code for the RR scheduling algorithm
		int timeRR = 0;
		int cRR = numProcesses;
		struct process processesRR[maxTurnaround]; //this is a huge array which contains the processes in the ready queue and the order they are dealth with
		int iterations = 0;
		int taRR = 0;
		struct process processesTurnaround[numProcesses]; //this is the array of processes which are completed first respectively and then their turnaround time
		
		for (int i = 0; i < maxTurnaround; i++) { //this initializes the array to its NULL
			processesRR[i].name = NULL;
			processesRR[i].timeCPU = -1;
			processesRR[i].waitFCFS = -1;
			processesRR[i].waitSJF = -1;
			processesRR[i].turnaroundRR = -1;
		}
		
		for (int i = 0; i < numProcesses; i++) { //this then sets the values of the processRR array to the actual processes array
			processesRR[i].name = processes[i].name;
			processesRR[i].timeCPU = processes[i].timeCPU;
		}
		
		fprintf(writeFile, "\nReady Queue %d Applying RR Scheduling:\n\n", queueNumber);
		fprintf(writeFile, "Order of selection by CPU:\n");
		
		for (int i = 0; i < maxTurnaround; i++) {
			if (processesRR[i].name == NULL) { //if that part of the array is not a process
				break;
			}
			else {
				fprintf(writeFile, "%s ", processesRR[i].name);
			
				if (processesRR[i].timeCPU > tq) { //if the time quantum is less than the burst time of the process then move the process to the back and decrease its burst time
					timeRR = timeRR + tq;
					processesRR[cRR].name = processesRR[i].name; 
					processesRR[cRR].timeCPU = processesRR[i].timeCPU - tq;
					processesRR[i].turnaroundRR = tq;
					cRR++;
				}
				else if (processesRR[i].timeCPU < tq) { //if the time quantum is more than the burst time then add it to processesTurnaround because it is now complete
					timeRR = timeRR + processesRR[i].timeCPU;
					processesTurnaround[taRR].name = processesRR[i].name;
					//processesTurnaround[taRR].turnaroundRR = timeRR;
					processesRR[i].turnaroundRR = processesRR[i].timeCPU;
					taRR++;
				}
				else if (processesRR[i].timeCPU == tq) { //if the time quantum is more than the burst time then add it to processesTurnaround because it is now complete
					timeRR = timeRR + tq;
					processesTurnaround[taRR].name = processesRR[i].name;
					//processesTurnaround[taRR].turnaroundRR = timeRR;
					processesRR[i].turnaroundRR = processesRR[i].timeCPU;
					taRR++;
				}
				iterations++; //calculates the number of times the process changes
			}
		}
		
		for (int i = 0; i < numProcesses; i++) { //use the getTurnaround function to find the actual values of the process and put them into the array
			int turnaroundValueForProcess = getTurnaround(processesRR, processesTurnaround[i].name, iterations);
			processesTurnaround[i].turnaroundRR = turnaroundValueForProcess;
		}
		
		fprintf(writeFile, "\n\nTurnaround times for each process:\n");
		for (int i = 0; i < numProcesses; i++) { //print all the processes in order and their respective turnaround times
			fprintf(writeFile, "%s = %d\n", processesTurnaround[i].name, processesTurnaround[i].turnaroundRR);
		}
		
		fprintf(writeFile, "\n");
		queueNumber++; //iterate the queue number
	}
	
	//close both the readFile and writeFile
	fclose(readFile);
	fclose(writeFile);
	
	//open the output.txt that was just created and print its contents line by line to the stream instead of a file
	FILE *outputFile = fopen("output.txt", "r");
	if (outputFile != NULL) {
		char ln[maxLineLength];
		while (fgets(ln, maxLineLength, outputFile) != NULL) {
			fputs(ln, stdout); //put in stdout
		}
		fclose(outputFile); //close the file
	}
	else {
		printf("Unable to read output.txt\n");
	}
	
	return 0; //done with the program
}

int getTurnaround(struct process processes[], char *processName, int num) { 
	int lside = 0; //this variable starts from the left side of the array
	int rside = num - 1; //this variable starts from the right side of the array
	int result = 0; //is the calculated turnaround time 
	
	for (int i = 0; i < num; i++) { //find when processName is first seen in the array from the left
		if (strcmp(processes[i].name, processName) == 0) {
			lside = i; //set it when found and break the loop
			break;
		}	
	}
	
	for (int j = num - 1; j >= 0; j--) { //find when processName is first seen in the array from the left
		if (strcmp(processes[j].name, processName) == 0) {
			rside = j; //set it when found and break the loop
			break;
		}	
	}
	
	while (lside <= rside) { //find out how much time it takes to go from the left to the right side and store into result
		result = result + processes[lside].turnaroundRR; 
		lside++;
	}
	return result; //this is the found turnaround value
}
