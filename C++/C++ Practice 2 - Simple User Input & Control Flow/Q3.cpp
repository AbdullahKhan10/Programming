//Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For question 3, this program prompts the user to enter 3 cities and it puts them in ascending order


//Libraries
#include <iostream>
#include <string> //require the string class

using namespace std;
int main() //start program
{

//Declaring variables for the 3 cities
string c1;
string c2;
string c3;

//Prompts the user; tells them what to do; and tells them the limitations on the program
cout << "This program organizes 3 cities in alphabetical order!" << endl;
cout << "Make sure the cities are either all CAPITAL letters or all LOWERCASE letters." << endl << endl;
cout << "Make sure the cities don't start with the same letter " << endl << "or else you will get incorrect results." << endl;

//Asks the user the input for the first city
cout << endl << "Enter the name of the first city: ";
cin >> c1;
cout << endl;

//Asks the user the input for the second city
cout << "Enter the name of the second city: ";
cin >> c2;
cout << endl;

//Asks the user the input for the third city
cout << "Enter the name of the third city: ";
cin >> c3;
cout << endl;

//Prompts
cout << "Here are the cities in ascending order: " << endl;

//This group of if statements determines the first city (ie. the highest alpahbetically)
if (c1.at(0) <= c2.at(0) && c1.at(0) <= c3.at(0))
{
	cout << "1. " << c1 << endl; //Will display if statement above is true
}
else if (c2.at(0) <= c1.at(0) && c2.at(0) <= c3.at(0))
{
	cout << "1. " << c2 << endl; //Will display if statement above is true
}
else if (c3.at(0) <= c1.at(0) && c3.at(0) <= c2.at(0))
{
	cout << "1. " << c3 << endl; //Will display if statement above is true
}

//This group of if statements determines the second city (ie. the second highest alpahbetically)
if (c1.at(0) >= c2.at(0) && c1.at(0) <= c3.at(0))
{
	cout << "2. " << c1 << endl; //Will display if statement above is true
}
else if (c1.at(0) >= c3.at(0) && c1.at(0) <= c2.at(0))
{
	cout << "2. " << c1 << endl; //Will display if statement above is true
}

else if (c2.at(0) >= c1.at(0) && c2.at(0) <= c3.at(0))
{
	cout << "2. " << c2 << endl; //Will display if statement above is true
}

else if (c2.at(0) >= c3.at(0) && c2.at(0) <= c1.at(0))
{
	cout << "2. " << c2 << endl; //Will display if statement above is true
}

else if (c3.at(0) >= c1.at(0) && c3.at(0) <= c2.at(0))
{
	cout << "2. " << c3 << endl; //Will display if statement above is true
}

else if (c3.at(0) >= c2.at(0) && c3.at(0) <= c1.at(0))
{
	cout << "2. " << c3 << endl; //Will display if statement above is true
}

//This group of if statements determines the third city (ie. the lowest alpahbetically)
if (c1.at(0) >= c2.at(0) && c1.at(0) >= c3.at(0))
{
	cout << "3. " << c1 << endl; //Will display if statement above is true
}
else if (c2.at(0) >= c1.at(0) && c2.at(0) >= c3.at(0))
{
	cout << "3. " << c2 << endl; //Will display if statement above is true
}
else if (c3.at(0) >= c1.at(0) && c3.at(0) >= c2.at(0))
{
	cout << "3. " << c3 << endl; //Will display if statement above is true
}


return 0;
} //end of program
