//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q5 - This program takes user inputted scores, finds the average of those scores, and tells user how many were above average and how many are below average


//stream library
#include <iostream> 


using namespace std;
int main()

{ //start of program

	//variables for the array
	const int max = 100;
	double scores[max];

	//variables for the sum and average for the values set in the arrays
	double sum = 0;
	double average;

	//counters that will count the number of inputs, number of scores above 
	double count = 0;
	int highercount = 0;
	int lowercount = 0;
	

	//this prompts the user and tells the user what the program does
	cout << "Enter any number of scores (max 100) and receive the average.";
	cout << endl << endl << "Also, this program will tell you how many scores are below the average and " 
		<< endl << "how many scores are above the average." << endl << endl;

	//this loop allows the user to enter scores into the array
	for (int i = 0; i < max; i++)
	{
		cout << i + 1 << ". Enter score (enter negative number to stop): ";
		cin >> scores[i];

		//this if statement controls when the loop will stop 
		if (scores[i] < 0) 
		{
			i = 100;
		}
		else //count holds number of inputs
		{
			count++;
		}
	}

	//this loop calculates the the sum of all the numbers in the array
	for (int j = 0; j < count; j++)
	{
		sum = sum + scores[j];
	}

	//this gets the average of the numbers in the array
	average = sum / count;

	//This loop counts how many scores are above average
	for (int x = 0; x < count; x++)
	{
		if (scores[x] >= average)
		{
			highercount++; //counter for above average
		}
	}

	//This loop counts how many scores are below average
	for (int y = 0; y < count; y++)
	{
		if (scores[y] < average)
		{
			lowercount++; //counter for below average
		}
	}

	//This displays all the recoreded data
	cout << endl;
	cout << "Numbers of inputs: " << count << endl;
	cout << "Average of scores: " << average << endl;
	cout << "Number of scores above or equal to average: " << highercount << endl;
	cout << "Number of scores below average: " << lowercount << endl;


	//pause
	int p;
	cin >> p;

	return 0;
}