//
//  Item.h
//
//  A module to represent a single item in the game.
//

#ifndef ITEM_H
#define ITEM_H

#include <string>


//
//  Item
//
//  A record to represent an item.
//

struct Item 
{
	char id;
	unsigned int start_row;
	unsigned int start_column;
	unsigned int current_row;
	unsigned int current_column;
	bool is_in_inventory;
	int points;
	std::string world_description;
	std::string inventory_description;
};



//
//  itemInit
//
//  Purpose: To initialize the specified Item with the specified
//           values.
//  Parameter(s):
//    <1> item: A reference to the item to initialize
//    <2> id1: The id for the item
//    <3> row1: The starting row
//    <4> column1: The starting column
//    <5> points1: How many points the item is worth
//    <6> world_description1: The description of the item when
//                            it is at a location in the world
//    <7> inventory_description1: The description of the item
//                                when it is in the player
//                                inventory
//  Precondition(s):
//    <1> id1 != ID_NOT_INITIALIZED
//    <2> world_description1 != ""
//    <3> inventory_description1 != ""
//  Returns: N/A
//  Side Effect: Item item is initialized.
//
void itemInit (Item& item,
               char id1,
               unsigned int row1, unsigned int column1,
               int points1,
               const std::string& world_description1,
               const std::string& inventory_description1);

//
//  itemDebugPrint
//
//  Purpose: To display the state of the specified Item.
//  Parameter(s):
//    <1> item: The item to display
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The values for Item item are printed.
//
void itemDebugPrint (const Item& item);

//
//  itemGetId
//
//  Purpose: To determine the id of an Item.
//  Parameter(s):
//    <1> item: The item to query
//  Precondition(s): N/A
//  Returns: The id of Item item.
//  Side Effect: N/A
//
char itemGetId (const Item& item);

//
//  itemIsInInventory
//
//  Purpose: To determine whether the specified Item is in the
//           player inventory.
//  Parameter(s):
//    <1> item: The item to query
//  Precondition(s): N/A
//  Returns: Whether Item item is in the player inventory.
//  Side Effect: N/A
//
bool itemIsInInventory (const Item& item);

//
//  itemIsAtLocation
//
//  Purpose: To determine whether the specified Item is at the
//           specified location.
//  Parameter(s):
//    <1> item: The item to query
//    <2> row: The row of the location to check
//    <3> column: The column of the location to check
//  Precondition(s): N/A
//  Returns: Whether Item item is in at location (row, column).
//  Side Effect: N/A
//
bool itemIsAtLocation (const Item& item,
                       unsigned int row, unsigned int column);

//
//  itemGetPlayerPoints
//
//  Purpose: To determine how many points the specified Item is
//           currently worth to the player.
//  Parameter(s):
//    <1> item: The item to query
//  Precondition(s): N/A
//  Returns: How many points Item item is worth to the player at
//           present.
//  Side Effect: N/A
//
int itemGetPlayerPoints (const Item& item);

//
//  itemPrintDescription
//
//  Purpose: To print the current description for the specified
//           Item.
//  Parameter(s):
//    <1> item: The item to print
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The current description for Item item is
//               printed.
//
void itemPrintDescription (const Item& item);

//
//  itemReset
//
//  Purpose: To reset the specified Item.
//  Parameter(s):
//    <1> item: A reference to the item to reset
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: Item item is moved to its starting location.
//
void itemReset (Item& item);

//
//  itemMoveToInventory
//
//  Purpose: To move the specified Item to the player inventory.
//  Parameter(s):
//    <1> item: A reference to the item to move
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: Item item is moved to the player inventory.
//
void itemMoveToInventory (Item& item);

//
//  itemMoveToLocation
//
//  Purpose: To move the specified Item to the specified
//           location.
//  Parameter(s):
//    <1> item: A reference to the item to move
//    <2> row: The new row
//    <3> column: The new column
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: Item item is moved to location (row, column).
//
void itemMoveToLocation (Item& item,
                         unsigned int row, unsigned int column);



#endif
