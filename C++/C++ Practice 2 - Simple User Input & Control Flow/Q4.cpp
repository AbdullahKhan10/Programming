//Name: Abdullah Khan
//Student ID: 200376500
//Purpose: For question 4, this program determines which letter in the alphabet corresponds with which number on the international telephone

#include <iostream> //library

using namespace std;
int main()
{ //Start of program

//This is the variable for the letter the person enters a-z
char letter;

//Prompts the user on what the program does
cout << "This program gives you the corresponding number for a letter on the telephone!" << endl;

//Prompts the user to enter the letter they desire
cout << endl << "Enter a letter (a-z) that you would like the number for: ";
cin >> letter;


//These are the statements that determine which letter corresponds with which number
//These display the number if the statement is true
if (letter == 'a' || letter == 'b' || letter == 'c')
{
	cout << "Number = 2" << endl; //Number is two if the entered letter is a, b, or c 
}

if (letter == 'd' || letter == 'e' || letter == 'f')
{
	cout << "Number = 3" << endl; //Number is two if the entered letter is d, e, or f 
}

if (letter == 'g' || letter == 'h' || letter == 'i')
{
	cout << "Number = 4" << endl; //Number is two if the entered letter is g, h, or i 
}

if (letter == 'j' || letter == 'k' || letter == 'l')
{
	cout << "Number = 5" << endl; //Number is two if the entered letter is j, k, or l 
}

if (letter == 'm' || letter == 'n' || letter == 'o')
{
	cout << "Number = 6" << endl; //Number is two if the entered letter is m, n, or o 
}

if (letter == 'p' || letter == 'q' || letter == 'r' || letter == 's')
{
	cout << "Number = 7" << endl; //Number is two if the entered letter is p, q, r, or s 
}

if (letter == 't' || letter == 'u' || letter == 'v')
{
	cout << "Number = 8" << endl; //Number is two if the entered letter is t, u, or v 
}

if (letter == 'w' || letter == 'x' || letter == 'y' || letter == 'z')
{
	cout << "Number = 9" << endl; //Number is two if the entered letter is w, x, y, or z
}



return 0;
}
