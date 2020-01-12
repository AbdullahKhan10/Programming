//Student: Abdullah Khan 
//Student ID: 200376500
//Purpose: The is a program for question one - this program asks user to enter 2 sets of 10 numbers and it finds the common numbers between the sets

//Library
#include <iostream>

using namespace std;
int main()
{ //Start of program

	//variable for array lenght 
	const int max = 10;

	//two arrays set for 10 values
	int a1 [max];
	int a2 [max];

	//Prompts the user for what the program does
	cout << "This program will find common numbers between two arrays of size 10: " << endl << endl;

	//This is for the input of the first array 
	for (int i = 0; i < max; i++) //loop allows indices from 0 to 9
	{
		cout << i + 1 << ". Enter value for array 1: ";
		cin >> a1[i]; //Prompts and allows user to enter values for the array
	}

	cout << endl;

	//This is for the input of the second array
	for (int j = 0; j < max; j++) //loop allows indices from 0 to 9
	{
		cout << j + 1 << ". Enter value for array 2: ";
		cin >> a2[j]; //Prompts and allows user to enter values for the array
	}

	//Now the program prompts the user for the common numbers between arrays
	cout << endl << "Common Numbers: ";
	

	//This nested for loop compares all the elements from each element of each array and tells the common 
	for (int o = 0; o < max; o++)
	{
		for (int p = 0; p < max; p++)
		{
			if (a1[o] == a2[p])
			{
				cout << a1[o] << "   ";
				p = max;
			}
		}
	}
	

	//pause
	int p;
	cin >> p;


	return 0;
} //end 
