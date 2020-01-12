//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q4 - This program prompts the user to enter an integer value and it returns the number of digits the value has

//required libraries
#include <iostream> 
#include <string>

//declare namspace
using namespace std;

//This function returns the size
int getSize(int n)
{
	
	string x; //this value gets converted to string
	int a; //this value gets set to the length using string functions

	//string functions
	x = to_string(n);
	a = x.length();

	return a; //returns length
}


int main()

{ //start of program

	int numdigit; //variable for the user entered number

    //prompts the user to enter his integer
	cout << "Enter a number you would like the number of digits for: ";
	cin >> numdigit; 

	//the displays the size of the integer
	cout << "The number you have entered has '" << getSize(numdigit) << "' digits." << endl;
	

	//pause
	int p;
	cin >> p;

	return 0;
}