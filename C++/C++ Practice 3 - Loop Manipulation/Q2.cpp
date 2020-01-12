//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q2 - paste all the numbers which are divisable by 5 and 6 but not both and seperate them into 10 numbers per line

//Libraries
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{//Start of program

	//Starts at 100
	int i = 100;

	//Prompts the user of what the numbers are
	cout << "This is a list of numbers which are divisable by 5 or 6 but not both: " << endl << endl;

	//Starts at 100 and ends at 200; checks all the values in between
	while (i <= 200)
	{
		//This statement checks if the value is divisable by 5 or 6 but not both
		if ((i % 5 == 0 || i % 6 == 0) && !(i % 5 == 0 && i % 6 == 0))
		{
			
			//This seperates the numbers into lines of 10 with one space between numbers
			if (i == 130) 
			{
				cout << i << endl;
			}
			else if (i == 162)
			{
				cout << i << endl;
			}
			else if (i == 195)
			{
				cout << i << endl;
			}
			else
			{
				cout << i << " "; //lists all the values which apply to the if statement
			}
		
		}

		i++;
	} //End of loop

	//Pause
	int p;
	cin >> p;

	return 0;
}
