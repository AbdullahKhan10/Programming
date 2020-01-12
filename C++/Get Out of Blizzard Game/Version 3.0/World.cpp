//
//  World.cpp
//

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

#include "Location.h"
#include "World.h"

using namespace std;

static const unsigned int INACCESSIBLE = 0;
static const unsigned int DEATH        = 1;
static const unsigned int START        = 2;
static const unsigned int VICTORY      = 3;



World :: World (const string& game_name)
{
	loadNodes       (game_name + "_grid.txt");
	loadDescriptions(game_name + "_text.txt");

	assert(invariant());
}



void World :: debugPrint () const
{
	cout << "Nodes:" << endl;
	cout << "------" << endl;
	for(unsigned int r = 0; r < ROW_COUNT; r++)
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
		{
			cout << nodes[r][c];
			if(c + 1 < COLUMN_COUNT)
				cout << "\t";
			else
				cout << endl;
		}
	cout << endl;

	cout << "Descriptions:" << endl;
	cout << "-------------" << endl;
	for(unsigned int d = 0; d < description_count; d++)
		cout << descriptions[d] << endl;
}

Location World :: getStart () const
{
	assert(invariant());

	for(unsigned int r = 0; r < ROW_COUNT; r++)
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
			if(nodes[r][c] == START)
				return Location(r, c);

	return Location(0, 0);  // should never happen
}

bool World :: isValid (const Location& location) const
{
	assert(invariant());

	if(location.row    >=    ROW_COUNT) return false;
	if(location.column >= COLUMN_COUNT) return false;
	return true;
}

void World :: printDescription (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	unsigned int index = nodes[location.row][location.column];
	assert(index < MAX_DESCRIPTION_COUNT);
	assert(index < description_count);
	cout << descriptions[index];
}

bool World :: canGoNorth (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	if(location.row <= 0) return false;
	if(nodes[location.row - 1][location.column] == INACCESSIBLE) return false;
	return true;
}

bool World :: canGoSouth (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	if(location.row + 1 >= ROW_COUNT) return false;
	if(nodes[location.row + 1][location.column] == INACCESSIBLE) return false;
	return true;
}

bool World :: canGoEast (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	if(location.column + 1 >= COLUMN_COUNT) return false;
	if(nodes[location.row][location.column + 1] == INACCESSIBLE) return false;
	return true;
}

bool World :: canGoWest (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	if(location.column <= 0) return false;
	if(nodes[location.row][location.column - 1] == INACCESSIBLE) return false;
	return true;
}

Location World :: getNorth (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));
	assert(canGoNorth(location));

	assert(location.row >= 1);
	return Location(location.row - 1, location.column);
}

Location World :: getSouth (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));
	assert(canGoSouth(location));

	return Location(location.row + 1, location.column);
}

Location World :: getEast (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));
	assert(canGoEast(location));

	return Location(location.row, location.column + 1);
}

Location World :: getWest (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));
	assert(canGoWest(location));

	assert(location.column >= 1);
	return Location(location.row, location.column - 1);
}

bool World :: isDeath (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	return nodes[location.row][location.column] == DEATH;
}

bool World :: isVictory (const Location& location) const
{
	assert(invariant());
	assert(isValid(location));

	return nodes[location.row][location.column] == VICTORY;
}



void World :: loadNodes (const string& filename)
{
	assert(filename != "");

	ifstream fin(filename.c_str());
	if(!fin)
	{
		cerr << "Error: Could not open file \"" << filename << "\"" << endl;
		return;
	}
	assert(fin.good());

	for(unsigned int r = 0; r < ROW_COUNT; r++)
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
			fin >> nodes[r][c];
}

void World :: loadDescriptions (const string& filename)
{
	assert(filename != "");

	ifstream fin(filename.c_str());
	if(!fin)
	{
		cerr << "Error: Could not open file \"" << filename << "\"" << endl;
		return;
	}
	assert(fin.good());

	// this error checking really shouldn't be done with asserts...

	fin >> description_count;
	if(!fin)
	{
		cerr << "Error: Could not read description count in file \"" << filename << "\"" << endl;
		return;
	}
	assert(fin.good());
	if(description_count > MAX_DESCRIPTION_COUNT)
	{
		cerr << "Error: Too many descriptions in file \"" << filename << "\", increase MAX_DESCRIPTION_COUNT" << endl;
		return;
	}
	assert(description_count <= MAX_DESCRIPTION_COUNT);

	// discard anything else on count line
	string line;
	getline(fin, line);
	if(!fin.good())
	{
		cerr << "Error: Could not discard endline after description count in file \"" << filename << "\"" << endl;
		return;
	}
	assert(fin.good());
	if(line != "")
	{
		cerr << "Error: Extra values after description count in file \"" << filename << "\"" << endl;
		return;
	}
	assert(line == "");

	// read blank line
	getline(fin, line);
	if(!fin.good())
	{
		cerr << "Error: Could not discard first blank line in file \"" << filename << "\"" << endl;
		return;
	}
	assert(fin.good());
	if(line != "")
	{
		cerr << "Error: First blank line in file \"" << filename << "\" was not blank" << endl;
		return;
	}
	assert(line == "");

	// read descriptions
	for(unsigned int d = 0; d < description_count; d++)
	{
		descriptions[d] = "";

		getline(fin, line);
		if(!fin)
		{
			cerr << "Error: Could not read first line of description " << d << " in file \"" << filename << "\"" << endl;
			return;
		}
		assert(fin.good());
		while(line != "")
		{
			descriptions[d] += line + "\n";
			getline(fin, line);
			if(!fin)
			{
				cerr << "Error: Could not read line of description " << d << " in file \"" << filename << "\"" << endl;
				return;
			}
			assert(fin.good());
		}
	}
}

bool World :: invariant () const
{
	if(description_count > MAX_DESCRIPTION_COUNT)
		return false;

	for(unsigned int r = 0; r < ROW_COUNT; r++)
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
			if(nodes[r][c] >= description_count)
				return false;

	for(unsigned int d = 0; d < description_count; d++)
			if(descriptions[d] == "")
				return false;

	return true;
}
