//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q3 - This program prompts the user to enter 3 numbers and the program sorts them in increasing order

//required library
#include <iostream> 

using namespace std;

//This function sets the entered values in increasing order
void sort(double &a, double &b, double &c)
{
	if (a > b) //parameters set if first number is greater than second number
	{
		double i = a;
		a = b;
		b = i;
	}
	if (a > c) //parameters set if first number is greater than third number
	{
		double i = a;
		a = c;
		c = i;
	}
	if (b > c) //parameters set if second number is greater than third number
	{
		double i = b;
		b = c;
		c = i;
	}
}

int main()

{ //start of program

	//variables for all three numbers
	double num1;
	double num2;
	double num3;

	//Initial prompt; tells user what the program does
	cout << "Enter three numbers - ";
	cout << "This program will sort your numbers in increasing order." << endl << endl;

	//The code below tells the user to enter the three numbers and sets the varibles
	cout << "Enter the first number: ";
	cin >> num1;
	cout << "Enter the second number: ";
	cin >> num2;
	cout << "Enter the third number: ";
	cin >> num3;

	//This reinstates the numbers which were inputted by the user
	cout << endl << "The numbers you have entered are: " << num1 << ", " << num2 << ", " << num3 << endl;

	//Function sort from above is called and it sorts and sets the numbers into an increasing increment. num3 being the highes and num2 being the second highest and num1 being the lowest
	sort(num1, num2, num3); 

	//This displays the numbers in increasing order
	cout << "Sorted in increasing order: " << num1 << ", " << num2 << ", " << num3 << endl;

	//pause
	int p;
	cin >> p;

	return 0;
}