//
//  Item.cpp
//

#include <cassert>
#include <string>
#include <iostream>

#include "Item.h"

using namespace std;

static const char ID_NOT_INITIALIZED = '\0';



void itemInit (Item& item,
               char id1,
               unsigned int row1, unsigned int column1,
               int points1,
               const string& world_description1,
               const string& inventory_description1)
{
	assert(id1 != ID_NOT_INITIALIZED);
	assert(world_description1 != "");
	assert(inventory_description1 != "");

	item.id = id1;
	item.start_row    = row1;
	item.start_column = column1;
	item.current_row    = row1;
	item.current_column = column1;
	item.is_in_inventory = false;
	item.points = points1;
	item.world_description     = world_description1;
	item.inventory_description = inventory_description1;
}

void itemDebugPrint (const Item& item)
{
	cout << "id: \'" << item.id << "\'" << endl;
	cout << "start_row:    " << item.start_row    << endl;
	cout << "start_column: " << item.start_column << endl;
	cout << "current_row:    " << item.current_row    << endl;
	cout << "current_column: " << item.current_column << endl;
	cout << "is_in_inventory: " << item.is_in_inventory << endl;
	cout << "points: " << item.points << endl;
	cout << "world_description:     \"" << item.world_description     << "\"" << endl;
	cout << "inventory_description: \"" << item.inventory_description << "\"" << endl;
}

char itemGetId (const Item& item)
{
	return item.id;
}

bool itemIsInInventory (const Item& item)
{
	return item.is_in_inventory;
}

bool itemIsAtLocation (const Item& item,
                       unsigned int row, unsigned int column)
{
	if(item.is_in_inventory)          return false;
	if(item.current_row    != row)    return false;
	if(item.current_column != column) return false;
	return true;
}

int itemGetPlayerPoints (const Item& item)
{
	if(item.is_in_inventory)
		return item.points;
	else
		return 0;
}

void itemPrintDescription (const Item& item)
{
	if(item.is_in_inventory)
		cout << item.inventory_description << endl;
	else
		cout << item.world_description << endl;
}

void itemReset (Item& item)
{
	item.current_row    = item.start_row;
	item.current_column = item.start_column;
	item.is_in_inventory = false;
}

void itemMoveToInventory (Item& item)
{
	item.is_in_inventory = true;
}

void itemMoveToLocation (Item& item,
                         unsigned int row, unsigned int column)
{
	item.current_row    = row;
	item.current_column = column;
	item.is_in_inventory = false;
}

