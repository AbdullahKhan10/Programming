
#include <stdio.h> //standard library for input and output

int main(void)
{ //start of program
	
	//variables
	float base; //the user inputted base is stored here
	int exponent; //the user inputted exponenet of the base is stored here 
	float result = 1; //after calculation the result of the power is stored in here

	//prompt and scans the user inputted base and stores into the variable
	printf("Enter a positive base: ");
	scanf("%f", &base);
	
	//incase the user enters a negetive base, they will be prompted to re-enter
	while (base < 0) //will run if base is negetive
	{
		//prompts and re-scans user input for base
		printf("Your entry is invalid! Please enter a positive base: ");
		scanf("%f", &base);
	}

	//prompts and scnas the user inputted exponenet ans stores into the variable
	printf("Enter the exponent (Note - the absolute value of your entry will be taken: ");
	scanf("%d", &exponent);

	//this function will calculate the result of the power
	while (exponent != 0) //this will dictate the end of the counter 
	{
		//the base will be multipled by the resultant recursively until the end of counter is met
		result = result * base; 

		//wether the exponent is negetive or positive, it will be a counter which will approach zero until the result if calculated
		if (exponent > 0) 
		{
			exponent--; //the exponent will approach zero from the positive side in case of a positive exponent
		}
		else
		{
			exponent++; //the exponenet will approach zero from the negetive side in case of a negetive exponent
		}
	} //this loop will continue unil the exponent is equal to zero and the final result is calculated

	//this will prompt and return the users answer
	printf("\nYour result is: %f \n", result);

	return 0; //exit program

} //end of program
