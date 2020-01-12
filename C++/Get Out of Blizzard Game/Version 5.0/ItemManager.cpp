//
//  ItemManager.cpp
//

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

#include "Location.h"
#include "Item.h"
#include "ItemManager.h"

using namespace std;

static const unsigned int NO_SUCH_ITEM = 999999999;



ItemManager :: ItemManager ()
		: items(new Item[0]),
		  item_count(0)
{
	assert(invariant());
}

ItemManager :: ItemManager (const string& game_name)
		: items(nullptr),
		  item_count(0)
{
	load(game_name + "_items.txt");
	sort();

	assert(invariant());
}

ItemManager :: ItemManager (const ItemManager& to_copy)
		: items(new Item[to_copy.item_count]),
		  item_count(to_copy.item_count)
{
	assert(to_copy.invariant());
	assert(invariant());
}

ItemManager :: ~ItemManager ()
{
	assert(invariant());

	delete[] items;
}

ItemManager& ItemManager :: operator= (const ItemManager& to_copy)
{
	assert(to_copy.invariant());
	assert(invariant());

	if(&to_copy != this)
	{
		// from destructor
		delete[] items;

		// from copy constructor
		items      = new Item[to_copy.item_count];
		item_count = to_copy.item_count;
	}

	assert(to_copy.invariant());
	assert(invariant());
	return *this;
}


int ItemManager :: getScore () const
{
	assert(invariant());

	int score = 0;
	for(unsigned int i = 0; i < item_count; i++)
		score += items[i].getPlayerPoints();
	return score;
}

void ItemManager :: printAtLocation (const Location& location) const
{
	assert(invariant());

	for(unsigned int i = 0; i < item_count; i++)
		if(items[i].isAtLocation(location))
			items[i].printDescription();
}

void ItemManager :: printInventory () const
{
	assert(invariant());

	for(unsigned int i = 0; i < item_count; i++)
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

	for(unsigned int i = 0; i < item_count; i++)
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



void ItemManager :: load (const string& filename)
{
	assert(filename != "");
	assert(items == nullptr);

	ifstream fin(filename.c_str());
	if(!fin)
	{
		cerr << "Error: Could not open file \"" << filename << "\"" << endl;
		return;
	}
	assert(fin.good());

	// this error checking really shouldn't be done with asserts...

	fin >> item_count;
	assert(fin.good());
	items = new Item[item_count];

	// discard anything else on start/victory line
	string line;
	getline(fin, line);
	assert(fin.good());
	assert(line == "");

	for(unsigned int i = 0; i < item_count; i++)
	{
		// read and discard a blank line
		getline(fin, line);
		assert(fin.good());
		assert(line == "");

		// read the values on the first line
		char id;
		fin >> id;
		assert(fin.good());

		unsigned int start;
		fin >> start;
		assert(fin.good());

		int points;
		fin >> points;
		assert(fin.good());

		// discard anything else on the line
		getline(fin, line);
		assert(fin.good());

		// read the descriptions
		string world_description;
		getline(fin, world_description);
		assert(fin.good());
		assert(world_description != "");

		string inventory_description;
		getline(fin, inventory_description);
		assert(fin.good());
		assert(inventory_description != "");

		// initialize the item
		items[i].init(id, Location(start), points,
		              world_description,
		              inventory_description);
	}
}

unsigned int ItemManager :: find (char id) const
{
	// binary search
	unsigned int low  = 0;
	unsigned int high = item_count;

	while(low < high)
	{
		assert(low != high);
		unsigned int middle = (low + high) / 2;
		assert(middle < item_count);

		char middle_id = items[middle].getId();
		if(id == middle_id)
			return middle;  // found it!
		else if(id < middle_id)
			high = middle;  // search low half
		else
		{
			assert(id > middle_id);
			low = middle + 1;  // search high half
		}
	}
/*
	// linear search
	for(unsigned int i = 0; i < item_count; i++)
		if(items[i].getId() == id)
			return i;
*/
	// found nothing
	return NO_SUCH_ITEM;
}

void ItemManager :: sort ()
{
/*
	// insertion sort
	for(unsigned int i = 1; i < item_count; i++)
	{
		Item temp_item = items[i];

		// shift items until we find the right spot
		assert(i >= 1);
		unsigned int spot = i - 1;
		while(i > 0 && items[i] < items[spot])
			items[spot + 1] = items[spot];

		// insert item into spot
		items[spot] = temp_item;
	}
*/
	// selection sort
	for(unsigned int i = 0; i < item_count; i++)
	{
		// find best remaining item
		unsigned int spot = i;
		for(unsigned int j = i + 1; j < item_count; j++)
			if(items[j] < items[spot])
				spot = j;

		// swap best item in
		Item temp_item = items[i];
		items[i] = items[spot];
		items[spot] = temp_item;
	}
}

bool ItemManager :: invariant () const
{
	if(items == nullptr)
		return false;
	for(unsigned int i = 0; i < item_count; i++)
		if(!items[i].isInitialized())
			return false;
	for(unsigned int i = 1; i < item_count; i++)
		if(items[i - 1].getId() > items[i].getId())
			return false;
	return true;
}
