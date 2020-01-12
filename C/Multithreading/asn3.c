//Author: Abdullah Khan
//Course: Cs3305 Asn3

//these are all the required libraries
#include <stdio.h> //for std input and output operation
#include <stdlib.h>
#include <string.h> //for string functions
#include <unistd.h>
#include <pthread.h> //for the threading of functions

#define maxLineLength 100 //max length of a line
#define maxAccounts 50 //max number of accounts
#define maxDeposits 150 //max number of deposits
#define maxClientFunctions 100 //max num of client function
#define maxStringLength 10 //max length of string

pthread_mutex_t lock; //gloabl lock variable for the mutex

//Account struct holds all account information
typedef struct {
	int name;
	char *type;
	int balance;
	int depositFee;
	int withdrawFee;
	int transferFee;
	int transactions;
	int transactionFee;
	int overdraftFee;
	int odi;
} Account;

//array of accounts holding all the accounts 
Account accounts[maxAccounts];

//holding all the deposits 
typedef struct {
	int accountName;
	int depositAmount;
} Deposit;

//holding all the client functions
typedef struct {
	char func;
	int arg1;
	int arg2;
	int arg3;
} Client;

//used for passing to thread functions
typedef struct {
	char a;
	int b;
	int c;
	int d;
} Quad;

//the deposit function which adds money to specified account
void *deposit(void *input) {
	Quad *dp = input; //get the quad input
	int account = dp->b; //get param 1
	account--;
	int amount = dp->c; //get param 2

	pthread_mutex_lock(&lock); //start critical region
	
	accounts[account].balance += amount; //add the specified balance
	accounts[account].balance -= accounts[account].depositFee; //minus the fees
	if (accounts[account].transactions < 1) { 
		accounts[account].balance -= accounts[account].transactionFee; //minus the fees
	}
	accounts[account].transactions--; //decrement the num of free transtions
	
	if(accounts[account].balance > 0) {
		accounts[account].odi = 0;
	}
	else {
		int o = -500; //overdraft 
		int o2 = -1;
		for (int i = 1; i <= 10; i++) {
			if (accounts[account].balance >= o && accounts[account].balance <= o2) { //if the balances are less than a certain point
				accounts[account].odi = i; //then charge overdraft
			}
			
			o = o -500;
			o2 = o2 - 500;
		}
	}
	
	pthread_mutex_unlock(&lock); //critical regions done
	pthread_exit(NULL); //exit the thread
}

void *withdraw(void *input) { //function with withdraws from the accounts
	Quad *dp = input; //get the parameters
	int account = dp->b; //get param 1
	account--;
	int amount = dp->c; //get param 2
	
	pthread_mutex_lock(&lock); //start the critical region
	
	if (accounts[account].balance - amount < -5000) { //if withdraw it too high 
		//accounts[account].balance -= accounts[account].overdraftFee; //charge overdraft
		pthread_mutex_unlock(&lock); //end crit region
		pthread_exit(NULL); //terminate the thread
	}
	
	accounts[account].balance -= amount; //decrease the balance by the specified amount
	accounts[account].balance -= accounts[account].withdrawFee; //charge withdraw fees
	
	if (accounts[account].transactions < 1) {
		accounts[account].balance -= accounts[account].transactionFee; //charge transaction fees
	}
	accounts[account].transactions--; //decrement the transtions 
	
	int todi = accounts[account].odi;
	
	if (accounts[account].balance < 0) //if the balance is less than 0
	{
		int o = -500; //overdraft 
		int o2 = -1;
		for (int i = 1; i <= 10; i++) {
			if (accounts[account].balance >= o && accounts[account].balance <= o2) { //if the balances are less than a certain point
				accounts[account].odi = i; //then charge overdraft
			}
			
			o = o -500;
			o2 = o2 - 500;
		}
		if (todi != accounts[account].odi) {
			accounts[account].balance -= (accounts[account].odi - todi)*accounts[account].overdraftFee;
			accounts[account].odi = accounts[account].odi;
		}
	}
	
	pthread_mutex_unlock(&lock); //end crit region
	pthread_exit(NULL); //terminate thread
}

void *transfer(void *input) { //this functions processes the trasfers
	Quad *dp = input; //get all the parameters like for the other functions
	int account1 = dp->b;
	account1--;
	int account2 = dp->c;
	account2--;
	int amount = dp->d;
	
	pthread_mutex_lock(&lock); //start the crit region
	
	if (accounts[account1].balance - amount < -5000) { //if the transfer is too high
		//accounts[account1].balance -= accounts[account1].overdraftFee;
		pthread_mutex_unlock(&lock);
		pthread_exit(NULL); //terminate the thread
	}
	
	accounts[account1].balance -= amount; //charge fees to the person transferring
	accounts[account1].balance -= accounts[account1].transferFee;
	
	if (accounts[account1].transactions < 1) {
		accounts[account1].balance -= accounts[account1].transactionFee;
	}
	accounts[account1].transactions--;
	
	int todi = accounts[account1].odi;
	
	if (accounts[account1].balance < 0) //if the balance of the sender is a certain point
	{
		int o = -1;
		int o2 = -500; //charge them overdraft depending
		for (int i = 1; i <= 10; i++) {
			if (accounts[account1].balance >= o2 && accounts[account1].balance <= o) {
				accounts[account1].odi = i; //decrease their balance
			}
			o2 = o2 - 500;
			o = o - 500;
		}	
		
		if (todi != accounts[account1].odi) {
			accounts[account1].balance -= (accounts[account1].odi - todi)*accounts[account1].overdraftFee;
			accounts[account1].odi = accounts[account1].odi;
		}
	}
	
	accounts[account2].balance += amount; //add the balances to the other account
	accounts[account2].balance -= accounts[account2].transferFee; //charge fees
	
	if (accounts[account2].transactions < 1) {
		accounts[account2].balance -= accounts[account2].transactionFee;
	}
	accounts[account2].transactions--;
	
	if (accounts[account2].balance > 0) {
		accounts[account2].odi = 0;
	}
	else {
		int o = -500; //overdraft 
		int o2 = -1;
		for (int i = 1; i <= 10; i++) {
			if (accounts[account2].balance >= o && accounts[account2].balance <= o2) { //if the balances are less than a certain point
				accounts[account2].odi = i; //then charge overdraft
			}
			
			o = o -500;
			o2 = o2 - 500;
		}
	}
	
	pthread_mutex_unlock(&lock); //end crit region
	pthread_exit(NULL); //terminate thread
}

int main() {
		
	FILE *readFile = fopen("assignment_3_input_file.txt", "r"); //for the input file
	FILE *writeFile = fopen("assignment_3_output_file.txt", "w"); //for the output file
	
	if (readFile == NULL) { //failure conditions
		printf("Unable to read file!\n");
		exit(EXIT_FAILURE);
	}
	
	if (writeFile == NULL) { //failure conditions
		printf("Unable to create file.\n");
		exit(EXIT_FAILURE);
	}
	
	//the variables for the counters and the deposits and clients
	Deposit deposits[maxDeposits];
	Client clients[maxClientFunctions];
	int accountCounter = 0;
	int depositCounter = 0;
	int clientCounter = 0;
	
	//each line and segment of the fileinput
	char line[maxLineLength];
	char *segment;
	
	//nullify the accounts initailly
	for (int i = 0; i < maxAccounts; i++) { 
		accounts[i].name = -1;
		accounts[i].type = NULL;
		accounts[i].balance = -1;
		accounts[i].depositFee = -1;
		accounts[i].withdrawFee = -1;
		accounts[i].transferFee = -1;
		accounts[i].transactions = -1;
		accounts[i].transactionFee = -1;
		accounts[i].overdraftFee = -1;
		accounts[i].odi = 0;
	}
	
	//nullify the deposits initially
	for (int i = 0; i < maxDeposits; i++) { 
		deposits[i].accountName = -1;
		deposits[i].depositAmount = -1;
	}
	
	//nullify the client functions initially
	for (int i = 0; i < maxClientFunctions; i++) { 
		clients[i].func = ' ';
		clients[i].arg1 = -1;
		clients[i].arg2 = -1;
		clients[i].arg3 = -1;
	}
	
	//gets the file input
	while (fgets(line, maxLineLength, readFile) != NULL) {
		segment = strtok(line, " ");
		
		if (*segment == 'a') { //if the sement is an account
			accounts[accountCounter].name = accountCounter + 1;
			accounts[accountCounter].balance = 0; 
			//get all the info and create an account 
			segment = strtok(NULL, " ");
			if (strcmp(segment, "type") == 0) {
				segment = strtok(NULL, " ");
				if (*segment == 'b') {
					accounts[accountCounter].type = "business";
				}
				else if (*segment == 'p') {
					accounts[accountCounter].type = "personal";
				}
			}
			
			segment = strtok(NULL, " ");
			if (strcmp(segment, "d") == 0) {
				segment = strtok(NULL, " ");
				accounts[accountCounter].depositFee = atoi(segment);
			}
			
			segment = strtok(NULL, " ");
			if (strcmp(segment, "w") == 0) {
				segment = strtok(NULL, " ");
				accounts[accountCounter].withdrawFee = atoi(segment);
			}
			
			segment = strtok(NULL, " ");
			if (strcmp(segment, "t") == 0) {
				segment = strtok(NULL, " ");
				accounts[accountCounter].transferFee = atoi(segment);
			}
			
			segment = strtok(NULL, " ");
			if (strcmp(segment, "transactions") == 0) {
				segment = strtok(NULL, " ");
				accounts[accountCounter].transactions = atoi(segment);
				segment = strtok(NULL, " ");
				accounts[accountCounter].transactionFee = atoi(segment);
			}
			
			segment = strtok(NULL, " ");
			if (strcmp(segment, "overdraft") == 0) {
				segment = strtok(NULL, " ");
				if (strcmp(segment, "Y") == 0) {
					segment = strtok(NULL, " ");
					accounts[accountCounter].overdraftFee = atoi(segment);
				}
			}
			accountCounter++; //increment to the next account
		}
		
		else if (*segment == 'd') { //in case if the line is deposit
			segment = strtok(NULL, " ");
			while (strcmp(segment, "d") == 0) {
				segment = strtok(NULL, " ");
				//gets all the information from the deposit line
				segment = segment + 1;
				deposits[depositCounter].accountName = atoi(segment);
				
				segment = strtok(NULL, " ");
				deposits[depositCounter].depositAmount = atoi(segment);
				
				depositCounter = depositCounter + 1;
				segment = strtok(NULL, " ");
				
				if (segment == NULL) {
					break;
				}
			}
		}
		
		else if (*segment == 'c') { //incase the line is a client and their functions
			segment = strtok(NULL, " ");
			//gets all the information of client line
			while (strcmp(segment, "d") == 0 || strcmp(segment, "w") == 0 || strcmp(segment, "t") == 0) {
				if (strcmp(segment, "d") == 0) {
					clients[clientCounter].func = 'd';
					segment = strtok(NULL, " ");
					segment = segment + 1;
					clients[clientCounter].arg1 = atoi(segment);
					segment = strtok(NULL, " ");
					clients[clientCounter].arg2 = atoi(segment);
					clients[clientCounter].arg3 = -1;
				}
			
				else if (strcmp(segment, "w") == 0) {
					clients[clientCounter].func = 'w';
					segment = strtok(NULL, " ");
					segment = segment + 1;
					clients[clientCounter].arg1 = atoi(segment);
					segment = strtok(NULL, " ");
					clients[clientCounter].arg2 = atoi(segment);
					clients[clientCounter].arg3 = -1;
				}
			
				else if (strcmp(segment, "t") == 0) {
					clients[clientCounter].func = 't';
					segment = strtok(NULL, " ");
					segment = segment + 1;
					clients[clientCounter].arg1 = atoi(segment);
					segment = strtok(NULL, " ");
					segment = segment + 1;
					clients[clientCounter].arg2 = atoi(segment);
					segment = strtok(NULL, " ");
					clients[clientCounter].arg3 = atoi(segment);
				}
				
				clientCounter = clientCounter + 1;
				segment = strtok(NULL, " ");
				
				if (segment == NULL) {
					break;
				}	
			}
		}
	}
		
	int num_threads = 1000; //max num of threads
	pthread_t threads[num_threads]; //c
	
	Quad dI[depositCounter]; //create a smaller cleaner array for deposits
	
	for (int i = 0; i < depositCounter; i++) { //initlize it
		dI[i].b = deposits[i].accountName;
		dI[i].c = deposits[i].depositAmount;
	}
	
	if (pthread_mutex_init(&lock, NULL) != 0) { //init the mutex lock
		printf("mutex init failed!\n");
		return 0;
	}
	
	//create all the threads for inital deposits
	for (int i = 0; i < depositCounter; i++) {
		pthread_create(&threads[i], NULL, deposit, &dI[i]);	
	}
	
	//join them together at the end
	for (int i = 0; i < depositCounter; i++) {
		pthread_join(threads[i], NULL);
	}
	
	//destroy the lock after
	pthread_mutex_destroy(&lock);
	
	Quad c[clientCounter]; //create a cleaner client function array
	
	for (int i = 0; i < clientCounter; i++) { //initialize array
		c[i].a = clients[i].func;
		c[i].b = clients[i].arg1;
		c[i].c = clients[i].arg2;
		c[i].d = clients[i].arg3;
	}
	
	if (pthread_mutex_init(&lock, NULL) != 0) { //init the mutex lock
		printf("mutex init failed!\n");
		return 0;
	}
	
	for (int i = 0; i < clientCounter; i++) { //runs all the functions of the client
		if (c[i].a == 'd')
		{
			pthread_create(&threads[i], NULL, deposit, &c[i]);
		}
		if (c[i].a == 'w')
		{
			pthread_create(&threads[i], NULL, withdraw, &c[i]);
		}
		if (c[i].a == 't')
		{
			pthread_create(&threads[i], NULL, transfer, &c[i]);
		}
		pthread_join(threads[i], NULL);
	}
	
	for (int i = 0; i < accountCounter; i++) {  //ouput to the file all the final information
		fprintf(writeFile, "a%d ", accounts[i].name);
		fprintf(writeFile, "type %s ", accounts[i].type);
		fprintf(writeFile, "%d\n", accounts[i].balance);
	}
	
	pthread_mutex_destroy(&lock); //destroy the lock
	//close the files
	fclose(readFile);
	fclose(writeFile);
	

	return 0; //exit program
}
