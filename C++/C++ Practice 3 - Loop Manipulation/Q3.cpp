//Student Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For Q3 - This program prompts the user to enter the names of any given number students and their grades, the output shows the names of the students who had the highest and second highest scores

//Libraries
#include <iostream>
#include <string>

using namespace std;
int main()
{ //Start of Program

	//Variable for # of students
	int students;

	//Variables for scores and names
	int studentscore;
	string studentname;

	//Variables for the highest student
	int max1 = 0;
	string max1name;

	//Variables for the second highest student
	int max2 = 0;
	string max2name;

	//Prompts the user to enter any number of students
	cout << "Enter the number of students you want to check: ";
	cin >> students;
	cout << endl;

	//The loop keeps running until all students are accounted for
	for (int i = 0; i < students; i++)
	{
		//Prompt user to enter student name 
		cout << "Enter a student name: ";
		cin >> studentname;

		//Prompt user to enter his score
		cout << "Enter a student score: ";
		cin >> studentscore;
		cout << endl;


	    //Use if statement to record the highest student and save the name and score into the max variables
		if (studentscore > max1)
		{
			max2 = max1;
			max2name = max1name;

			max1 = studentscore;
			max1name = studentname;

		} //Use if statement to record the second highest student and save the name and score into the max2 variables
		else if (studentscore > max2)
		{
			max2 = studentscore;
			max2name = studentname;
		}
	}

	//Print out the highest and lowest scores for the user
	cout << "1. '" << max1name << "' has the highest score and has a score of " << max1 << "." << endl;
	cout << "2. '" << max2name << "' has the second highest score and has a score of " << max2 << "." << endl;


	//Pause
	int p;
	cin >> p;


	return 0;
}
