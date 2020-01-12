
#include <stdio.h> //standard input and output library

int main(void)
{ //start of main

    //variables 
	int integerInput; //user input for the switch case of what initial conversion to perform
	char characterInput; //user input for which specific conversion to perform in each case
	float numberInput; //user input for which number to convert 
	float result; //the end result of the conversions in each case
	int run = 1; //controls run of the program

	while (run == 1) //loop which reruns the program until the user wants to quit by entering 5
	{
		//starting prompt asks user which conversion he would like to perform
		printf("\n\nWhat would you like to do?\n"
			"Enter 1 - conversion between Kilometer and Mile.\n"
			"Enter 2 - conversion between Meter and Feet.\n"
			"Enter 3 - conversion between Centimetre and Inch.\n"
			"Enter 4 - conversion between Celsius and Fahrenheit.\n"
			"Enter 5 - quit.\n\n");

		//scans what function the user wants to perform
		scanf("%d", &integerInput);
		printf("\n");

		//Checks for valid input
		while (integerInput != 1 && integerInput != 2 && integerInput != 3 && integerInput != 4 && integerInput != 5)
		{ //the user can only enter 1,2,3,4, or 5 and this function makes sure the user has inputted a valid value 
		  //if the user has not entered any of the valid entries, then the user will be prompted to re-enter their entry
			//prompt and re-scan
			printf("Your entry is invalid!\n"
				"Please enter a valid number: ");
			scanf("%d", &integerInput);
		}

		//this switch case manages all the different conversions 
		switch (integerInput)
		{ //start of switch 
		case 1: //case 1
			//prompt and scan
			printf("Enter K - for conversion from Kilometer to Mile.\n"
				"Enter M - for conversion from Mile to Kilometer.\n\n");
			scanf(" %c", &characterInput);

			//check for valid input
			while (characterInput != 'K' && characterInput != 'M')
			{
				//prompt and re-scan
				printf("\nYour entry is invalid!\n"
					"Please enter a valid character (Note - Entry is case sensitive): ");
				scanf(" %c", &characterInput);
			}

			//condition for K - prompts user to enter value in specified form and calculates and returns their converted value
			if (characterInput == 'K')
			{
				printf("\nEnter value in Kilometers: ");
				scanf("%f", &numberInput);
				result = numberInput / 1.609; //formula for km to miles
				printf("Your value in Miles: %f", result);
			}

			//condition for M - prompts user to enter value in specified form and calculates and returns their converted value
			if (characterInput == 'M')
			{
				printf("\nEnter value in Miles: ");
				scanf("%f", &numberInput);
				result = numberInput * 1.609; //formula for miles to km
				printf("Your value in Kilometers: %f", result);
			}
			break;

		case 2: //case 2
			//prompt and scan
			printf("Enter M - for conversion from Meter to Feet.\n"
				"Enter F - for conversion from Feet to Meter.\n\n");
			scanf(" %c", &characterInput);

			//check for valid input
			while (characterInput != 'M' && characterInput != 'F')
			{
				//prompt and re-scan
				printf("\nYour entry is invalid!\n"
					"Please enter a valid character (Note - Entry is case sensitive): ");
				scanf(" %c", &characterInput);
			}

			//condition for M - prompts user to enter value in specified form and calculates and returns their converted value
			if (characterInput == 'M')
			{
				printf("\nEnter value in Meters: ");
				scanf("%f", &numberInput);
				result = numberInput * 3.28084; //formula for meters to feet
				printf("Your value in Feet: %f", result);
			}

			//condition for F - prompts user to enter value in specified form and calculates and returns their converted value
			if (characterInput == 'F')
			{
				printf("\nEnter value in Feet: ");
				scanf("%f", &numberInput);
				result = numberInput / 3.28084; //formula for feet to meters
				printf("Your value in Meters: %f ", result);
			}
			break;

		case 3: //case 3
			printf("Enter C - for conversion from Centimetre to Inch.\n"
				"Enter I - for conversion from Inch to Centimetre.\n\n");
			scanf(" %c", &characterInput);

			//check for valid input
			while (characterInput != 'C' && characterInput != 'I')
			{
				//prompt and rescan
				printf("\nYour entry is invalid!\n"
					"Please enter a valid character (Note - Entry is case sensitive): ");
				scanf(" %c", &characterInput);
			}

			//condition for C - prompts user to enter value in specified form and calculates and returns their converted value
			if (characterInput == 'C')
			{
				printf("\nEnter value in Centimetres: ");
				scanf("%f", &numberInput);
				result = numberInput / 2.54; //formula for centimetres to inches
				printf("Your value in Inches: %f", result);
			}

			//condition for I - prompts user to enter value in specified form and calculates and returns their converted value
			if (characterInput == 'I')
			{
				printf("\nEnter value in Inches: ");
				scanf("%f", &numberInput);
				result = numberInput * 2.54; //formula for inches to centimetres
				printf("Your value in Centimetres: %f", result);
			}
			break;

		case 4: //case 4 
			//prompt and scan
			printf("Enter C - for conversion from Celsius to Fahrenheit.\n"
				"Enter F - for conversion from Fahrenheit to Celsius.\n\n");
			scanf(" %c", &characterInput);

			//check for valid input
			while (characterInput != 'C' && characterInput != 'F')
			{
				//prompt and rescan
				printf("\nYour entry is invalid!\n"
					"Please enter a valid character (Note - Entry is case sensitive): ");
				scanf(" %c", &characterInput);
			}

			//condition for C - prompts user to enter value in specified form and calculates and returns their converted value
			if (characterInput == 'C')
			{
				printf("\nEnter value in Celsius: ");
				scanf("%f", &numberInput);
				result = numberInput * 1.8 + 32; //formula for celcius to fahrenheit 
				printf("Your value in Fahrenheit: %f", result);
			}

			//condition for F - prompts user to enter value in specified form and calculates and returns their converted value
			if (characterInput == 'F')
			{
				printf("\nEnter value in Fahrenheit: ");
				scanf("%f", &numberInput);
				result = numberInput - 32;
				result = result * 0.5556; //formula for fahrenheit to celcius, includes the above code 
				printf("Your value in Celsius: %f", result);
			}
			break;

		case 5: //case 5
			run = 0; 
		} //end of switch
	}//end of run
printf("Quit!\n");
	return 0; //exits program 
} //end of main 


