//
//  Item.cpp
//

#include <cassert>
#include <string>
#include <iostream>

#include "Item.h"

using namespace std;

static const char ID_NOT_INITIALIZED = '\0';



Item :: Item ()
	: id(ID_NOT_INITIALIZED),
	  start(),
	  current(),
	  is_in_inventory(false),
	  points(0),
	  world_description    ("[Item not initialized]"),
	  inventory_description("[Item not initialized]")
{
	assert(invariant());
}



void Item :: debugPrint () const
{
	cout << "id: \'" << id << "\'" << endl;
	cout << "start:   " << start << endl;
	cout << "current: " << current << endl;
	cout << "is_in_inventory: " << is_in_inventory << endl;
	cout << "points: " << points << endl;
	cout << "world_description:     \"" << world_description     << "\"" << endl;
	cout << "inventory_description: \"" << inventory_description << "\"" << endl;
}

bool Item :: isInitialized () const
{
	assert(invariant());

	return id != ID_NOT_INITIALIZED;
}

char Item :: getId () const
{
	assert(invariant());
	assert(isInitialized());

	return id;
}

bool Item :: isInInventory () const
{
	assert(invariant());
	assert(isInitialized());

	return is_in_inventory;
}

bool Item :: isAtLocation (const Location& location) const
{
	assert(invariant());
	assert(isInitialized());

	return !is_in_inventory && current == location;
}

int Item :: getPlayerPoints () const
{
	assert(invariant());
	assert(isInitialized());

	if(is_in_inventory)
		return points;
	else
		return 0;
}

void Item :: printDescription () const
{
	assert(invariant());
	assert(isInitialized());

	if(is_in_inventory)
		cout << inventory_description << endl;
	else
		cout << world_description << endl;
}

bool Item :: operator< (const Item& other) const
{
	assert(invariant());
	assert(isInitialized());
	assert(other.isInitialized());

	return id < other.id;
}



void Item :: init (char id1,
                   const Location& start1,
                   int points1,
                   const string& world_description1,
                   const string& inventory_description1)
{
	assert(invariant());
	assert(id1 != ID_NOT_INITIALIZED);
	assert(world_description1 != "");
	assert(inventory_description1 != "");

	id = id1;
	start   = start1;
	current = start1;
	is_in_inventory = false;
	points = points1;
	world_description     = world_description1;
	inventory_description = inventory_description1;

	assert(isInitialized());
	assert(invariant());
}

void Item :: reset ()
{
	assert(invariant());
	assert(isInitialized());

	current = start;
	is_in_inventory = false;

	assert(invariant());
}

void Item :: moveToInventory ()
{
	assert(invariant());
	assert(isInitialized());

	is_in_inventory = true;

	assert(invariant());
}

void Item :: moveToLocation (const Location& location)
{
	assert(invariant());
	assert(isInitialized());

	current = location;
	is_in_inventory = false;

	assert(invariant());
}



bool Item :: invariant () const
{
	if(    world_description == "") return false;
	if(inventory_description == "") return false;
	return true;
}
