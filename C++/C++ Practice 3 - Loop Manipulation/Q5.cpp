//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q5 - finds the number of sales needed to make 30k for the given paremeters for question 5

//Libraries
#include <iostream>

using namespace std;
int main()
{
	//Declare variables for the moneymade and the saleamount
	double moneymade = 0;
	double saleamount = 0;
	double diff; //This is used to calculate the differences

	do
	{//Start of loop 

		//The If statements keep looping till a value is found that equals 30k
		//This occurs when the sale amount is in the 8% range 
		if (saleamount > 0.01 && saleamount < 5000)
		{
			moneymade = 0.08 * saleamount + 5000;
		}
		//This occurs when the sale amount is in the 10% range 
		if (saleamount > 5000.01 && saleamount < 10000)
		{
			diff = saleamount - 5000;
			moneymade = (0.08 * 5000) + (0.10 * diff) + 5000;
		}
		//This occurs when the sale amount is in the 12% range 
		if (saleamount > 10000.01)
		{
			diff = saleamount - 10000;
			moneymade = (0.08 * 5000) + (0.10 * 5000) + (0.12 * diff) + 5000;
		}

		//The system is looking for the right saleamount
		saleamount += 0.01; //Increment by 1 cent

	} while (moneymade <= 30000); //Keeps looping until a value for sale amount is given that makes the person 30000

	//Tells the user the amount of sales he needs to make to earn 30k 
	cout << "The minimum amount of money you would need to make from sales in" << endl << "order to make $30000 is: $" << saleamount << endl;

	//Pause
	int p;
	cin >> p;

	return 0;
}
