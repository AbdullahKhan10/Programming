//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q1 - is to create a program which creates three patterns with numbers as shown in question one

//Required libraries
#include <iostream> 
#include <iomanip>

using namespace std;

int main()

{ //Start of program

	//Prompts user that this is Pattern A
	cout << " Pattern A" << endl;
	//Below is the nested loop that creates the pattern one
	for (int count1 = 1; count1 <= 6; count1++) 
	{
        //The organization of the greater than and less than signs creates the distint pattern 
		for (int count2 = 1; count2 <= count1; count2++) 
		{
			cout << setw(2) << count2;
		}
		cout << endl;
	} //End of code for Pattern A

	//Prompts user that this is Pattern B
	cout << endl << " Pattern B" << endl;
	//Below is the nested loop that creates pattern two
	for (int count3 = 6; count3 >= 1; count3--)
	{
	    //The organization of the greater than and less than signs creates the distint pattern 
		for (int count4 = 1; count4 <= count3; count4++)
		{
			cout << setw(2) << count4;
		}
		cout << endl;
	} //End of code for Pattern B

	//Prompts user that this is Pattern C
	cout << endl << " Pattern C";
	//Below is the nested loop that creates pattern three
	for (int count5 = 1; count5 <= 7; count5++)
	{
		//The organization of the greater than and less than signs creates the distint pattern 
		for (int count6 = 1; count6 < count5; count6++)
		{
			cout << setw(2) << count5 - count6; //The minus statement allows to get the decreasing horzontal order
		}
		cout << endl;
	} //End of code for Pattern C

	//For pause
	int p; 
	cin >> p;

	return 0;
}