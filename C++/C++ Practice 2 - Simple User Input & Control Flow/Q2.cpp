//Student: Abdullah Khan
//Student ID: 200376500
//Purpose: For question two, this program gives you the number of days in a particular year and month that is entered

#include <iostream>
#include <string> //Using the string library

using namespace std;
int main() //start of progarm
{ 


//variables for year and month
int year; //is an integer
string month; //is a word

//promts user to enter the year and month they desire and promts the user what the program does
cout << "Type in a year and month and recieve the number of days in that month." << endl;

//promts user to enter year
cout << endl << "Enter the year: ";
cin >> year;
cout << endl;

//promts user to enter month
cout << "Enter the month (only the first letter may have a capital): ";
cin >> month;
cout << endl;

//Statement tells the months which have 31 days; can type them in lower and upper case (for first letter)
if (month == "January" || month == "March" || month == "May" || month == "July" || month == "August" || month == "October" || month == "December" || month == "january" || month == "march" || month == "may" || month == "july" || month == "august" || month == "october" || month == "december")
{
	cout << month << " " << year << " has 31 days." << endl;
}

//Statement tells the months which have 30 days; can type them in lower and upper case (for first letter)
if (month == "April" || month == "June" || month == "September"  || month == "November" || month == "april" || month == "june" || month == "september" || month == "november")
{
	cout << month << " " << year << " has 30 days." << endl;
}

//February has a leap year exception and must have its own condition
if (((month == "February") || (month == "february"))) 
{
	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) //If this statement is true, then that year is a leap year and february will have 29 days
	{
		cout << month << " " << year << " has 29 days and is a leap year." << endl; //There is a leap year when the above statement is true
	}
	else
	{
		cout << month << " " << year << " has 28 days and is not a leap year." << endl; //If the boolean statement is false then its not a leap year
    }
} //end of program


return 0;
}
