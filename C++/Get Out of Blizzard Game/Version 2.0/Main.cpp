//
//  Main.cpp
//

#include <string>
#include <iostream>

#include "World.h"
#include "Item.h"

using namespace std;

const unsigned int ITEM_COUNT = 5;

//
//  printItemsAtLocation
//
//  Purpose: To print all the items in the specified array that
//           are at the specified row and column.
//  Parameter(s):
//    <1> items: The items to print
//    <2> row: The row to print items at
//    <2> column: The column to print items at
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The description is printed for all Items in
//               items that are at location (row, column).
//
void printItemsAtLocation(const Item items[],
                          unsigned int row, unsigned int column);



int main ()
{
	World world;
	unsigned int player_row, player_column;
	Item items[ITEM_COUNT];

	worldLoadAll  (world, "blizzard");
	worldFindStart(world, player_row, player_column);

	itemInit(items[0], 'a', 0, 6, 1,
	         "You see Alice (a) trying to read a very small compass.",
			 "Somewhere nearby, you hear Alice (a) jabbering about directions.");
	itemInit(items[1], 'c', 0, 6, 1,
	         "You see Charlie (c) lying half-buried in the drifting snow.",
			 "Behind you, Charlie (c) is dragging himself through the snow.");
	itemInit(items[2], 'e', 3, 5, 1,
	         "Young Emma (e) is crouched down, out of the wind.",
			 "Young Emma (e) is trying to use you to block the wind.");
	itemInit(items[3], 'd', 4, 1, 1,
	         "David (d) is using a stick to write in the snow here.",
			 "David (d) is dashing this way and that, despite the weather.");
	itemInit(items[4], 'b', 5, 8, 2,
	         "The twins, Benny and Bobby (b), are huddled together here.",
			 "The twins, Benny and Bobby (b), are huddled behind you.");

	cout << "Welcome to Blizzard Valley!" << endl;
	cout << "You and six children were hiking in the mountians when an" << endl;
	cout << "unexpected blizzard blew up.  Find the six children and get them" << endl;
	cout << "all back to the hiking lodge on the other side of the river." << endl;
	cout << endl;

	worldPrintDescription(world, player_row, player_column);
	printItemsAtLocation(items, player_row, player_column);

	bool is_quit = false;
	while(!is_quit)
	{
		cout << "Next? ";

		string line;
		do  // must get some input!
		{
			getline(cin, line);
		}
		while(line == "");

		char command = line[0];
		switch(command)
		{
		case 'q':
			cout << "Are you sure you want to quit? ";
			getline(cin, line);
			if(line != "" && line[0] == 'y')
				is_quit = true;
			break;

		case 'n':
			if(worldCanGoNorth(world, player_row, player_column))
			{
				player_row--;
				worldPrintDescription(world, player_row, player_column);
				printItemsAtLocation(items, player_row, player_column);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 's':
			if(worldCanGoSouth(world, player_row, player_column))
			{
				player_row++;
				worldPrintDescription(world, player_row, player_column);
				printItemsAtLocation(items, player_row, player_column);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 'e':
			if(worldCanGoEast(world, player_row, player_column))
			{
				player_column++;
				worldPrintDescription(world, player_row, player_column);
				printItemsAtLocation(items, player_row, player_column);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 'w':
			if(worldCanGoWest(world, player_row, player_column))
			{
				player_column--;
				worldPrintDescription(world, player_row, player_column);
				printItemsAtLocation(items, player_row, player_column);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 't':
			{
				cout << "Take what? ";
				getline(cin, line);

				bool found_it = false;
				if(line != "")
				{
					for(unsigned int i = 0; i < ITEM_COUNT; i++)
					{
						if(itemGetId(items[i]) == line[0] &&
						   itemIsAtLocation(items[i], player_row, player_column))
						{
							itemMoveToInventory(items[i]);
							found_it = true;
							break;  // stop searching for item
						}
					}
				}
				if(!found_it)
					cout << "Invalid item." << endl;
			}
			break;

		case 'l':
			{
				cout << "Leave what? ";
				getline(cin, line);

				bool found_it = false;
				if(line != "")
				{
					for(unsigned int i = 0; i < ITEM_COUNT; i++)
					{
						if(itemGetId(items[i]) == line[0] &&
						   itemIsInInventory(items[i]))
						{
							itemMoveToLocation(items[i], player_row, player_column);
							found_it = true;
							break;  // stop searching for item
						}
					}
				}
				if(!found_it)
					cout << "Invalid item." << endl;
			}
			break;

		case 'i':
			for(unsigned int i = 0; i < ITEM_COUNT; i++)
				if(itemIsInInventory(items[i]))
					itemPrintDescription(items[i]);
			break;

		default:
			cout << "Invalid command!" << endl;
			break;
		}

		if(worldIsDeath(world, player_row, player_column))
			is_quit = true;
		if(worldIsVictory(world, player_row, player_column))
			is_quit = true;
	}

	unsigned int score = 0;
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		score += itemGetPlayerPoints(items[i]);

	cout << endl;
	cout << "In this game you scored " << score << " points." << endl;
	cout << "Thank you for playing Blizzard Valley!" << endl;

	return 0;
}



void printItemsAtLocation(const Item items[],
                          unsigned int row, unsigned int column)
{
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		if(itemIsAtLocation(items[i], row, column))
			itemPrintDescription(items[i]);
}
