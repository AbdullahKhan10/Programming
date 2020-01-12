//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q4 - This program displays all the factors of a number that is given by the user

//Library
#include <iostream>

using namespace std;
int main()
{
	//Variables
	int input;
	int counter;

	//Prompts user to enter integer value they want factors for
	cout << "Write an integer number you would like the factors for: ";
	cin >> input;
	cout << endl;

		//Tells user that these are the factors of his number
		cout << "These are the factors for your entered number: " << endl;

	//This loop checks all values from 0 to that number
	for (int c = 1; c <= input; c++)
	{
		//This checks wether the number is a factor of the given number and pastes it
		if (input % c == 0)
		{
			cout << c << "\t";
		}
	}

	//Pause
	int p;
	cin >> p;

	return 0;
}
