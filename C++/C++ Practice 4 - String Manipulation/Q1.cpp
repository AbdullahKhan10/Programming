//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q1 - This program finds the longest common prefix bettwen 2 entered strings

//required libraries
#include <iostream> 
#include <string>

using namespace std;

//this function gives the longest prefix among two string valuess
void Stringprefix(const string s1, const string s2)
{
	//this variable gets the length of the bigger string
	int max;

	//This statements assigns the bigger string to max
	if (s1.length() > s2.length())
	{
		max = s1.length();
	}
	else
	{
		max = s2.length();
	}

	//This statement determines if there is no common prefix and tells the user that there is no common prefix
	if (s1.at(0) != s2.at(0))
	{
		cout << endl << "There is no common prefix between '" << s1 << "' and '" << s2 << "'";
	}

	else
	{
		//prompts the user
		cout << endl << "The longest common prefix is: ";

		//This loops prints out all the letters which are common between the two entered string
		for (int i = 0; i < max; i++)
		{
			if (s1.at(i) == s2.at(i))
			{
				cout << s1.at(i); //prints letters
			}
			else //once a prefix is finalized, the loop must end; this closes the loop
			{
				i = max;
			}
		}
	}

}

int main()

{ //start of program

	//variables for the first and second string values
	string first;
	string second;

	//Prompts user for what the program does
	cout << "Enter two string values - " << endl << "This program determines the longest common prefix." << endl;

	//prompts the user to enter the first and second word 
	cout << endl << "Enter first word: ";
	cin >> first;
	cout << "Enter second word: ";
	cin >> second;

	//Call the function
	Stringprefix(first, second);

	//pause
	int p;
	cin >> p;

	return 0;
} //end of program