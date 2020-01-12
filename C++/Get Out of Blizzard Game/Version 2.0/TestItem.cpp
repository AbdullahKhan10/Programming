//
//  TestItem.cpp
//
//  A seperate program to test the Item module.
//

#include <cassert>
#include <string>
#include <iostream>

#include "Item.h"

using namespace std;

void printItem (const Item& item);



int main ()
{
	// create the apple
	Item apple;
	itemInit(apple, 'a', 4, 2, 5,
	         "There is an apple (a) here.",
	         "You are carrying an apple (a).");
	itemDebugPrint(apple);
	printItem(apple);

	// move the apple
	itemMoveToInventory(apple);
	printItem(apple);

	itemMoveToLocation(apple, 1, 7);
	printItem(apple);

	itemMoveToLocation(apple, 9, 0);
	printItem(apple);

	itemMoveToInventory(apple);
	printItem(apple);

	itemReset(apple);
	printItem(apple);

	// create the boat
	Item boat;
	itemInit(boat, 'b', 6, 3, -10,
	         "There is a boat (b) here.",
	         "You are in a boat (b).");
	itemDebugPrint(boat);
	printItem(boat);
	printItem(apple);

	// move the boat
	itemMoveToLocation(boat, 0, 0);
	printItem(boat);
	printItem(apple);

	itemMoveToInventory(boat);
	printItem(boat);
	printItem(apple);

	// create the cat - fails
	Item cat;
	//itemInit(cat, 'c', 8, 9, 0,
	//         "There is a cat (c) hiding somewhere near here.",
	//         "");

	return 0;
}

void printItem (const Item& item)
{
	cout << "Item id: \'" << itemGetId(item) << "\'" << endl;
	cout << "Is item in inventory:    " << itemIsInInventory(item) << endl;
	cout << "Is item at r = 0, c = 0: " << itemIsAtLocation(item, 0, 0) << endl;
	cout << "Is item at r = 4, c = 2: " << itemIsAtLocation(item, 4, 2) << endl;
	cout << "Is item at r = 1, c = 7: " << itemIsAtLocation(item, 1, 7) << endl;
	cout << "Is item at r = 9, c = 0: " << itemIsAtLocation(item, 9, 0) << endl;
	cout << "Is item at r = 6, c = 3: " << itemIsAtLocation(item, 6, 3) << endl;
	cout << "Player points: " << itemGetPlayerPoints(item) << endl;
	itemPrintDescription(item);
	cout << endl;
}

