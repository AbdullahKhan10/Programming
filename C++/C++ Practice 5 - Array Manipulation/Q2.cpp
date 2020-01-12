//Student: Abdullah Khan
//Student ID: 200376500
//Purpose: For this question, the program gets the smallest and largest number using functions and arrays

//Library
#include <iostream>

//Function for to find the minimum in array
double minimum(double array[], int size)
{
	//variable for min
	double x;
	x = array[0];

	//Loop finds min
	for (int k = 0; k < size; k++)
	{
		if (x > array[k])
		{
			x = array[k];
		}
	}
	return x; //returns the min
}

//Function for to find the minimum in array
double maximum(double array[], int size)
{
	//variable for max
	double y;
	y = array[0];

	//Loop finds max
	for (int j = 0; j < size; j++)
	{
		if (y < array[j])
		{
			y = array[j];
		}
	}
	return y; //returns the max
}


using namespace std;
int main()
{
	//variable for array
	const int max = 15;
	double a[max];

	//prompt the user of what the program does
	cout << "Enter 15 numbers and the get the largest and smallest number: " << endl << endl;

	//get values for arrays
	for (int i = 0; i < max; i++)
	{
		cout << i + 1 << ". Enter value: ";
		cin >> a[i];

	}
	//Print out the largest and smallest number while using the max and min function
	cout << endl << "Largest Number: " << maximum(a, max) << endl;
	cout << "Smallest Number: " << minimum(a, max);

	//for pause
	int p;
	cin >> p;

	return 0;
}