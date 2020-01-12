//
//  ItemManager.h
//
//  A module to keep track of all the items in the game.
//

#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include <string>

#include "Location.h"
#include "Item.h"



//
//  ItemManager
//
//  A class to keep track of all the items in the game.
//
//  Class Invariant:
//    <1> items != nullptr
//    <1> items[i].isInitialized()
//                                     WHERE 0 <= i < item_count
//    <2> items[i - 1].getId() < items[i].getId()
//                                     WHERE 1 <= i < item_count
//

class ItemManager
{
public:
//
//  Default Constructor
//
//  Purpose: To create an ItemManager with no items.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new ItemManager is created containing no
//               items.
//
	ItemManager ();

//
//  Constructor
//
//  Purpose: To create an ItemManager for a game with the
//           specified name.
//  Parameter(s):
//    <1> game_name: The game name
//  Precondition(s):
//    <1> game_name != ""
//  Returns: N/A
//  Side Effect: A new ItemManager is created with the items for
//               the game with name game_name.  All the items
//               are placed at their respective starting
//               locations.
//
	ItemManager (const std::string& game_name);

//
//  Copy Constructor
//
//  Purpose: To create an ItemManager as a copy of another
//           ItemManager.
//  Parameter(s):
//    <1> to_copy: The ItemManager to copy
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new ItemManager is created with copies of the
//               items in to_copy.
//
	ItemManager (const ItemManager& to_copy);

//
//  Destructor
//
//  Purpose: To safely destroy an ItemManager without memory
//           leaks.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: All dynamically allocated memeory associated
//               with this ItemManager is freed.
//
	~ItemManager ();

//
//  Assignment Operator
//
//  Purpose: To modify this ItemManager to be a copy of another
//           ItemManager.
//  Parameter(s):
//    <1> to_copy: The ItemManager to copy
//  Precondition(s): N/A
//  Returns: A reference to this ItemManager.
//  Side Effect: The items in this ItemManager are removed and
//               replaced with copies of the items in to_copy.
//
	ItemManager& operator= (const ItemManager& to_copy);

//
//  getScore
//
//  Purpose: To determine if the player score.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The current player score.
//  Side Effect: N/A
//
	int getScore () const;

//
//  printInventory
//
//  Purpose: To print all items at the specified node.
//  Parameter(s):
//    <1> location: The location
//  Precondition(s): N/A
//  Returns: N/A
//  Returns: The description for each item at node location is
//           printed.
//
	void printAtLocation (const Location& location) const;

//
//  printInventory
//
//  Purpose: To print all items in the player invenrtory.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Returns: The description for each item in the player
//           inventory is printed.
//
	void printInventory () const;

//
//  isInInventory
//
//  Purpose: To determine if the item with the specified id is
//           in the player invenrtory.
//  Parameter(s):
//    <1> id: The item id
//  Precondition(s): N/A
//  Returns: Whether the item with id id is in the player
//           inventory.  If there is no such item, false is
//           returned.
//  Side Effect: N/A
//
	bool isInInventory (char id);

//
//  reset
//
//  Purpose: To reset all items.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: All items are moved to their respective
//               starting locations.
//
	void reset ();

//
//  take
//
//  Purpose: To attempt to take the item with the specified id,
//           assuming that the player is at the specified
//           location.
//  Parameter(s):
//    <1> id: The item id
//    <2> player_location: The player location
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: If there is an item with id id location
//               player_location, that item is moved to the
//               player inventory.  Otherwise, a message is
//               printed.
//
	void take  (char id, const Location& player_location);

//
//  leave
//
//  Purpose: To attempt to leave the item with the specified id,
//           assuming that the player is at the specified
//           location.
//  Parameter(s):
//    <1> id: The item id
//    <2> player_location: The player location
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: If there is an item with id id in the player
//               inventory, that item is moved to location
//               player_location.  Otherwise, a message is
//               printed.
//
	void leave (char id, const Location& player_location);

private:
//
//  load
//
//  Purpose: To load the items for this ItemManager from the
//           specified file.
//  Parameter(s):
//    <1> filename: The file name
//  Precondition(s):
//    <1> filename != ""
//    <2> items == nullptr
//  Returns: N/A
//  Side Effect: The items in file filename are loaded into this
//               ItemManager.
//
	void load (const std::string& filename);

//
//  find
//
//  Purpose: To determine the index of the item with the
//           specified id.
//  Parameter(s):
//    <1> id: The item id
//  Precondition(s): N/A
//  Returns: The index of the item with id id.  If there is no
//           such item, NO_SUCH_ITEM (a hidden constant) is
//           returned.  If there is more than one such item, the
//           index of any one of them might be returned.
//  Side Effect: N/A
//
	unsigned int find (char id) const;

//
//  sort
//
//  Purpose: To sort the items in this ItemManager.
//           specified id.
//  Parameter(s): N/A
//  Precondition(s):
//    <1> items == nullptr
//  Returns: N/A
//  Side Effect: The items in this ItemManager are sorted.
//
	void sort ();

//
//  invariant
//
//  Purpose: To determine if the class invariant is true.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: Whether the class invariant is true.
//  Side Effect: N/A
//
	bool invariant () const;

private:
	Item* items;
	unsigned int item_count;
};



#endif

