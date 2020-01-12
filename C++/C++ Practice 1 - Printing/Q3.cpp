//Student: Abdullah Khan
//Student Number: 200376500
//Purpose: This program calculates and displays the perimeter and area of a circle with a radius of 5.5 for Q3

//This is the header
#include <iostream>

using namespace std;
int main()
{ //Start of program 

	//Here I declare and set my variables
	const double  PI = 3.14159; //PI is a constant 
	double radius = 5.5; //variable for radius set to 5.5 

	//The user is told what the program does and then displays the results 
	cout << "Area and Perimeter of circle with radius of 5.5: " << endl;
	cout << "Perimeter = " << 2 * radius * PI << endl; //Radius is multiplied by 2 and PI for perimeter 
	cout << "Area = " << radius * radius * PI << endl; //Radius is multiplied by radius and PI for area

	return 0; //End of program
}