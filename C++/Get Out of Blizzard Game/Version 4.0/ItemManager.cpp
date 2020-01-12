//
//  ItemManager.cpp
//

#include <cassert>
#include <string>
#include <iostream>

#include "Location.h"
#include "Item.h"
#include "ItemManager.h"

using namespace std;

static const unsigned int NO_SUCH_ITEM = 999999999;



ItemManager :: ItemManager (const string& game_name)
{
	items[0].init('s', Location(3), -5,
	              "There is a black scarab beetle (s) here.",
	              "A black scarab beetle (s) is crawling up your arm.");
	items[1].init('c', Location(7), 9,
	              "There is a silver candlestick (c) here.",
	              "You are carrying a silver candlestick (c).");
	items[2].init('k', Location(13), 3,
	              "There is an old iron key (k) here.",
	              "You have an old iron key (k) in your pocket.");
	items[3].init('t', Location(19), -8,
	              "There is a tarantula (t) here.",
	              "There is a tarantula (t) hanging on your shirt.");
	items[4].init('b', Location(22), 4,
	              "There is a book (b) here with an eye drawn on the cover.",
	              "You have a book (b) under your arm with an eye drawn on the cover.");
	items[5].init('m', Location(37), -2,
	              "There is a giant moth (m) sleeping here.",
	              "A giant moth (m) is perched on your shoulder.");
	items[6].init('a', Location(52), 7,
	              "There is a golden amulet (a) here.",
	              "You are wearing a golden amulet (a).");
	items[7].init('d', Location(53), 1,
	              "There is an rune-carved dagger (d) here.",
	              "You have an rune-carved dagger (d) stuck in your belt.");
	items[8].init('r', Location(58), 10,
	              "There is a diamond ring (r) here.",
	              "You are wearing a diamond ring (r).");

	assert(invariant());
}



int ItemManager :: getScore () const
{
	assert(invariant());

	int score = 0;
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		score += items[i].getPlayerPoints();
	return score;
}

void ItemManager :: printAtLocation (const Location& location) const
{
	assert(invariant());

	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		if(items[i].isAtLocation(location))
			items[i].printDescription();
}

void ItemManager :: printInventory () const
{
	assert(invariant());

	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		if(items[i].isInInventory())
			items[i].printDescription();
}

bool ItemManager :: isInInventory (char id)
{
	assert(invariant());

	unsigned int item_index = find(id);

	if(item_index == NO_SUCH_ITEM)
		return false;
	else
		return items[item_index].isInInventory();
}



void ItemManager :: reset ()
{
	assert(invariant());

	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		items[i].reset();

	assert(invariant());
}

void ItemManager :: take  (char id, const Location& player_location)
{
	assert(invariant());

	unsigned int item_index = find(id);

	if(item_index != NO_SUCH_ITEM &&
	   items[item_index].isAtLocation(player_location))
	{
		items[item_index].moveToInventory();
	}
	else
		cout << "Invalid item." << endl;

	assert(invariant());
}

void ItemManager :: leave (char id, const Location& player_location)
{
	assert(invariant());

	unsigned int item_index = find(id);

	if(item_index != NO_SUCH_ITEM &&
	   items[item_index].isInInventory())
	{
		items[item_index].moveToLocation(player_location);
	}
	else
		cout << "Invalid item." << endl;

	assert(invariant());
}



unsigned int ItemManager :: find (char id) const
{
	// linear search
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		if(items[i].getId() == id)
			return i;

	// found nothing
	return NO_SUCH_ITEM;
}


bool ItemManager :: invariant () const
{
	for(unsigned int i = 0; i < ITEM_COUNT; i++)
		if(!items[i].isInitialized())
			return false;
	return true;
}
