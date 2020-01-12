//
//  Main.cpp
//

#include <string>
#include <iostream>

#include "World.h"

using namespace std;



int main ()
{
	World world;
	unsigned int player_row, player_column;

	worldLoadAll  (world, "blizzard");
	worldFindStart(world, player_row, player_column);

	cout << "Welcome to Blizzard Valley!" << endl;
	cout << "You and six children were hiking in the mountians when an" << endl;
	cout << "unexpected blizzard blew up.  Find the six children and get them" << endl;
	cout << "all back to the hiking lodge on the other side of the river." << endl;
	cout << endl;

	worldPrintDescription(world, player_row, player_column);

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
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;
		case 's':
			if(worldCanGoSouth(world, player_row, player_column))
			{
				player_row++;
				worldPrintDescription(world, player_row, player_column);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;
		case 'e':
			if(worldCanGoEast(world, player_row, player_column))
			{
				player_column++;
				worldPrintDescription(world, player_row, player_column);
			}
			else
				cout << "There is no way to go in that direction." << endl;
			break;
		case 'w':
			if(worldCanGoWest(world, player_row, player_column))
			{
				player_column--;
				worldPrintDescription(world, player_row, player_column);
			}
			else
				cout << "There is no way to go in that direction." << endl;
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

	cout << endl;
	cout << "Thank you for playing Blizzard Valley!" << endl;

	return 0;
}
