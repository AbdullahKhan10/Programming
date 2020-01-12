//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q2 - This program finds the number of occurrences of a given letter inside a given word.


#include <iostream> 
#include <string>

using namespace std;

//This function finds the number of occurences of the letter in the string
int count(const string &s, char a)
{
	int num = 0; //counter for the number of occurences

	for (int i = 0; i < s.length(); i++)
	{
		if (s.at(i) == a) //This statement counts the number of times the letter occurs
		{
			num++; //counter
		}
	}
	return num; //returns occurences of letter
}

int main()

{ //start of program

	//variables for the word and letter
	string word;
	char letter;

	//Prompts the user and tells them what the program does 
	cout << "This program finds the number of occurrences" << endl;
	cout << "of a given letter inside a given word." ;

	//ask user to enter the word they would like to test
	cout << endl << endl << "Enter the word you would like to test: ";
	cin >> word; 

	//ask user to enter they would like to test in the word
	cout << "Enter the letter you would like the number of occurrences for: ";
	cin >> letter;
	cout << endl;

	//Prompts the user of how many times the letter occurs using the count function created above
	cout << "The letter '" << letter << "' occurs '" << count(word, letter) << "' time(s) in the word '" << word << "'.";
	

	//pause
	int p;
	cin >> p;

	return 0;
} //end of program