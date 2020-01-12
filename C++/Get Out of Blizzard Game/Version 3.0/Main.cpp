//
//  Main.cpp
//

#include <string>
#include <iostream>

#include "Location.h"
#include "World.h"
#include "Item.h"

using namespace std;

//
//  printItemsAtLocation
//
//  Purpose: To print all the items in the specified array that
//           are at the specified location.
//  Parameter(s):
//    <1> items: The items to print
//    <2> location: The location to print items at
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The description is printed for all Items in
//               items that are at location location.
//
void printItemsAtLocation(const Item items[],
                          const Location& location);

const unsigned int ITEM_COUNT = 9;
//static const string GAME_NAME = "blizzard";
static const string GAME_NAME = "ghostwood";



int main ()
{
	World world(GAME_NAME);
	Location player = world.getStart();

	Item items[ITEM_COUNT];
	items[0].init('s', Location(0, 3), -5,
	              "There is a black scarab beetle (s) here.",
	              "A black scarab beetle (s) is crawling up your arm.");
	items[1].init('c', Location(1, 1), 9,
	              "There is a silver candlestick (c) here.",
	              "You are carrying a silver candlestick (c).");
	items[2].init('k', Location(2, 0), 3,
	              "There is an old iron key (k) here.",
	              "You have an old iron key (k) in your pocket.");
	items[3].init('t', Location(2, 9), -8,
	              "There is a tarantula (t) here.",
	              "There is a tarantula (t) hanging on your shirt.");
	items[4].init('b', Location(3, 4), 4,
	              "There is a book (b) here with an eye drawn on the cover.",
	              "You have a book (b) under your arm with an eye drawn on the cover.");
	items[5].init('m', Location(5, 5), -2,
	              "There is a giant moth (m) sleeping here.",
	              "A giant moth (m) is perched on your shoulder.");
	items[6].init('a', Location(7, 9), 7,
	              "There is a golden amulet (a) here.",
	              "You are wearing a golden amulet (a).");
	items[7].init('d', Location(8, 0), 1,
	              "There is an rune-carved dagger (d) here.",
	              "You have an rune-carved dagger (d) stuck in your belt.");
	items[8].init('r', Location(9, 6), 10,
	              "There is a diamond ring (r) here.",
	              "You are wearing a diamond ring (r).");

/*
	cout << "Welcome to Blizzard Valley!" << endl;
	cout << "You and six children were hiking in the mountians when an" << endl;
	cout << "unexpected blizzard blew up.  Find the six children and get them" << endl;
	cout << "all back to the hiking lodge on the other side of the river." << endl;
*/
	cout << "Welcome to Ghostwood Manor!" << endl;
	cout << "There are rumors of treasure in the old haunted house" << endl;
	cout << "but many who venture in never come out again." << endl;
	cout << endl;

	world.printDescription(player);
	printItemsAtLocation(items, player);

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
			if(world.canGoNorth(player))
			{
				player = world.getNorth(player);
				world.printDescription(player);
				printItemsAtLocation(items, player);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 's':
			if(world.canGoSouth(player))
			{
				player = world.getSouth(player);
				world.printDescription(player);
				printItemsAtLocation(items, player);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 'e':
			if(world.canGoEast(player))
			{
				player = world.getEast(player);
				world.printDescription(player);
				printItemsAtLocation(items, player);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;

		case 'w':
			if(world.canGoWest(player))
			{
				player = world.getWest(player);
				world.printDescription(player);
				printItemsAtLocation(items, player);
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
						if(items[i].getId() == line[0] &&
						   items[i].isAtLocation(player))
						{
							items[i].moveToInventory();
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
						if(items[i].getId() == line[0] &&
						   items[i].isInInventory())
						{
							items[i].moveToLocation(player);
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
				if(items[i].isInInventory())
					items[i].printDescription();
			break;

		default:
			cout << "Invalid command!" << endl;
			break;
		}

		if(world.isDeath(player))
			is_quit = true;
		if(world.isVictory(player))
			is_quit = true;
	}

	int score = 0;
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		score += items[i].getPlayerPoints();

	cout << endl;
	cout << "In this game you scored " << score << " points." << endl;

	//cout << "Thank you for playing Blizzard Valley!" << endl;
	cout << "Thank you for playing Ghostwood Manor!" << endl;

	return 0;
}



void printItemsAtLocation(const Item items[],
                          const Location& location)
{
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		if(items[i].isAtLocation(location))
			items[i].printDescription();
}
