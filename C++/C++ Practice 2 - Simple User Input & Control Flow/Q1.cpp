//Student: Abdullah Khan
//Student ID: 200376500
//Purpose: For question one, this program compares which bag of rice is more worth it for its price

#include <iostream> //This is the library we need for the program

using namespace std;
int main() //Start of program
{ 

//These are the variables for the first package
	double pack1price; //Get the price of the package one from the user
	double pack1weight; //Get the weight of the package one from the user
	double worth1; //For the value of rice

//These are the variables for the second package
	double pack2price; //Get the price of the package two from the user
	double pack2weight; //Get the weight of the package two from the user
	double worth2; //For the value of rice

//Prompts the user of what the program does
	cout << "Check to see which bag of rice is worth more its price: " << endl;

//Prompts the user to enter his specifications for the two packages 
	cout <<endl << "Enter the PRICE of the first package of rice: $";
	cin >> pack1price;
	cout << endl << "Enter the WEIGHT of the first package of rice (in grams): ";
	cin >> pack1weight;
	cout << endl << "Enter the PRICE of the second package of rice: $";
	cin >> pack2price;
	cout << endl << "Enter the WEIGHT of the second package of rice (in grams): ";
	cin >> pack2weight;

//This checks the worth of the bags of rice by dividing the weight by the price
	worth1 =  pack1weight / pack1price; 
	worth2 = pack2weight / pack2price;

//These statements compare which worth is higher tells the user which bag of rice is more worth it
	if (worth1 > worth2)
	{
		cout << endl << "Package one is worth more than Package two!"; //This will execute if the above statement is true
	}

	if (worth2 > worth1)
	{
		cout << endl << "Package two is worth more than Package one!"; //This will execute if the above statement is true
	}


return 0;
}
