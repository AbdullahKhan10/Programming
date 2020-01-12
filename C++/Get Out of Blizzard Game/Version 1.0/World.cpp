//
//  World.cpp
//

#include <cassert>
#include <string>
#include <iostream>
#include <fstream>

#include "World.h"

using namespace std;

const unsigned int INACCESSIBLE = 0;
const unsigned int DEATH        = 1;
const unsigned int START        = 2;
const unsigned int VICTORY      = 3;

const unsigned int DESCRIPTION_COUNT = 24;

string descriptions[DESCRIPTION_COUNT];
/*
string descriptions[DESCRIPTION_COUNT] =
{
	"Invalid node.\n",

	"You lose your footing on the ice and slide into the freezing\n"
	"water below.  It is brutally cold.  By the time you reach the\n"
	"bank, your fingers are too numb to climb onto the ice near the\n"
	"shore.  Not long later, the water stops feeling so cold and its\n"
	"gentle motion rocks you to sleep.  You know all will be well.\n"
	"Maybe they'll find your body downstream.\n",

	"You are at a bend on a steep mountain trail running along the\n"
	"top of a cliff.  The trail leads north and west from here. Icy\n"
	"cliffs to the east and south lead to a rushing river below.\n",

	"You are in a warm lodge in the mountains.  The cold wind cannot\n"
	"reach here, and a merry fire burns in the fireplace.  A blizzard\n"
	"rages outside the door to the west, but you're out of it now.\n",

	"You are at the west end of a trail at the top of an icy cliff.\n"
	"The trail once continued west, but it has been blocked by a huge\n"
	"snowdrift.  There is impenetrable forest to the north and a\n"
	"rushing river below you to the south.\n",

	"You are at a T-junction on a north/south mountain trail.  From\n"
	"here, a narrower trail leads east.  There is impenetrable forest\n"
	"to the west and the trial opens up to the north.\n",

	"You are near some picnic tables close to the top of a cliff.  A\n"
	"narrow trail leads west and there is a rushing river at the\n"
	"bottom of icy cliffs to the east and south.  You can see a\n"
	"steep, icy path leading down the cliff to a frozen portion of\n"
	"the river to the east.\n",

	"You are on a mountain slope, lost in the raging blizzard.\n"
	"Everything is white.\n",

	"You are on a massive snowdrift, packed hard by the driving wind.\n"
	"There is an open area to the west and broken rocks to the east.\n"
	"To the north and south are impenetrable forest.\n",

	"You are picking your way among large, irregular rocks.  Gusts of\n"
	"wind blow the falling snow this way and that.  Much of it ends\n"
	"up blowing to the west, where it piles onto a massive snowdrift.\n"
	"There are also gaps between the rocks leading east and south.\n",

	"You are in an area with smaller rocks.  There is a raw cliff to\n"
	"the north, but there are gaps between the rocks to the east,\n"
	"south, and west.\n",

	"You are clambering along the north shore of a rushing river.\n"
	"There is a raw cliff to the north and rocks continue to the\n"
	"east and west.  The lower rocks have been coated with ice by\n"
	"the spray from the water, so they are very slippery.\n"
	"Be careful!\n",

	"You are on the bank of a rushing river, among some large rocks.\n"
	"There are gaps between the rocks to the north and east, and\n"
	"open water bordered by ice to the east and south.\n",

	"You are on the north bank of a rushing river, at the edge of an\n"
	"area filled with large rocks.  There is a rusty iron footbridge\n"
	"to the south and an impenetrable forest to the east.  Gaps lead\n"
	"between the rocks to the north and east.\n",

	"You are on a rusty iron bridge over a rushing river.  Through\n"
	"the blowing snow, you can see large rocks on the north bank and\n"
	"a forest on the south one.  You could also climb down onto the\n"
	"ice bordering the river to the east and west.\n",

	"You are on the bank of a rushing river, just inside the edge of\n"
	"a forest.  There is a rusty iron bridge to the north and a path\n"
	"leads into the trees to the east.  To the west, the river has\n"
	"frozen over, forming an ice bridge.\n",

	"You are at a T-junction on a forest path.  The main path leads\n"
	"south and west, and a fainter trail leads down to a rushing\n"
	"river to the north.\n",

	"You are on a north/south path through the forest.  Stately\n"
	"lodgepole pines stand like pillars around you.  Little snow\n"
	"falls here, and the wind is calmer.\n",

	"You are at an open T-junction, where an east/west path meets\n"
	"one running north.  Around you, smaller aspen trees grow,\n"
	"taking advantage of the light.  Nestled on the ground between\n"
	"them are tiny evergreens.\n",

	"You are on a forest path.  To the west, a huge tree has blown\n"
	"down, blocking the path, and swirling snow is blowing in\n"
	"through the hole in the forest canopy.  The only way to go is\n"
	"east.\n",

	"You are on an east/west forest path.  Here, wooden boards have\n"
	"been laid across a small streambed.\n",

	"You are in a flat forest clearing at the bottom of a smooth,\n"
	"steep hill.  The top of the hill is to the east and there are\n"
	"paths into the forest to the north and west.\n",

	"You are at the top of the hill.  There is a smooth slope down\n"
	"to the west, and impenetrable forest to the north, east, and\n"
	"south.\n",

	"You are at the north end of a forest path.  To the east, you\n"
	"can see a large wooden building with light shining from the\n"
	"windows.\n",
};
*/


void worldLoadAll (World world, string game_name)
{
	worldLoadNodes       (world, game_name + "_grid.txt");
	worldLoadDescriptions(world, game_name + "_text.txt");
}

void worldLoadNodes (World world, string filename)
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
			fin >> world[r][c];
}

void worldLoadDescriptions (World world, string filename)
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

	unsigned int description_count;
	fin >> description_count;
	if(!fin)
	{
		cerr << "Error: Could not read description count in file \"" << filename << "\"" << endl;
		return;
	}
	assert(fin.good());
	if(description_count != DESCRIPTION_COUNT)
	{
		cerr << "Error: " << description_count << " descriptions in file \"" << filename << "\", DESCRIPTION_COUNT = " << DESCRIPTION_COUNT << endl;
		return;
	}
	assert(description_count == DESCRIPTION_COUNT);

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
	for(unsigned int d = 0; d < DESCRIPTION_COUNT; d++)
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
void worldDebugPrint (const World world)
{
	for(unsigned int r = 0; r < ROW_COUNT; r++)
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
		{
			cout << world[r][c];
			if(c + 1 < COLUMN_COUNT)
				cout << "\t";
			else
				cout << endl;
		}
}

void worldFindStart (const World world,
                     unsigned int& row, unsigned int& column)
{
	for(unsigned int r = 0; r < ROW_COUNT; r++)
		for(unsigned int c = 0; c < COLUMN_COUNT; c++)
			if(world[r][c] == START)
			{
				row    = r;
				column = c;
				return;  // no more searching needed
			}
}

bool worldIsValid (const World world,
                   unsigned int row, unsigned int column)
{
	if(row >= ROW_COUNT)    return false;
	if(row >= COLUMN_COUNT) return false;
	return true;
}

void worldPrintDescription (const World world,
                            unsigned int row, unsigned int column)
{
	assert(worldIsValid(world, row, column));

	unsigned int index = world[row][column];
	assert(index < DESCRIPTION_COUNT);
	cout << descriptions[index];
}

bool worldCanGoNorth (const World world,
                      unsigned int row, unsigned int column)
{
	if(row <= 0) return false;
	if(world[row - 1][column] == INACCESSIBLE) return false;
	return true;
}

bool worldCanGoSouth (const World world,
                      unsigned int row, unsigned int column)
{
	if(row + 1 >= ROW_COUNT) return false;
	if(world[row + 1][column] == INACCESSIBLE) return false;
	return true;
}

bool worldCanGoEast (const World world,
                     unsigned int row, unsigned int column)
{
	if(column + 1 >= COLUMN_COUNT) return false;
	if(world[row][column + 1] == INACCESSIBLE) return false;
	return true;
}

bool worldCanGoWest (const World world,
                     unsigned int row, unsigned int column)
{
	if(column <= 0) return false;
	if(world[row][column - 1] == INACCESSIBLE) return false;
	return true;
}

bool worldIsDeath (const World world,
                   unsigned int row, unsigned int column)
{
	return world[row][column] == DEATH;
}

bool worldIsVictory (const World world,
                     unsigned int row, unsigned int column)
{
	return world[row][column] == VICTORY;
}


