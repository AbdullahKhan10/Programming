//
//  Main.cpp
//

#include <string>
#include <iostream>

#include "Location.h"
#include "World.h"
#include "Item.h"
#include "ItemManager.h"
#include "Game.h"
#include "HighScores.h"

using namespace std;

//
//  doEndScore
//
//  Purpose: To print the player score at the end of the game
//           and update the high scores table for the specified
//           Game.
//  Parameter(s):
//    <1> game: The Game to get the score for
//    <2> player_name: The player name to add to the high score
//                     table
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The current player score for Game game is
//               printed in the end-of-game format and added to
//               the high scores table.  The high scores table
//               data file is updated and the table is
//               displayed.
//
void doEndScore (const Game& game,
                 const string& player_name);

//static const string GAME_NAME = "blizzard";
//static const string GAME_NAME = "ghostwood";
static const string GAME_NAME = "jungle";
//static const string GAME_NAME = "hogwarts";



int main ()
{
	Game game(GAME_NAME);

/*
	cout << "Welcome to Blizzard Valley!" << endl;
	cout << "You and six children were hiking in the mountians when an" << endl;
	cout << "unexpected blizzard blew up.  Find the six children and get them" << endl;
	cout << "all back to the hiking lodge on the other side of the river." << endl;
*/
/*
	cout << "Welcome to Ghostwood Manor!" << endl;
	cout << "There are rumors of treasure in the old haunted house" << endl;
	cout << "but many who venture in never come out again." << endl;
*/
	cout << "Welcome to Jungle Quest!" << endl;
	cout << "You recently obtained an old treasure map in mysterious" << endl;
	cout << "circumstances.  It showed the location of the Lost Jewel of" << endl;
	cout << "Leopold II, evil king of the Congo Free State.  And since you" << endl;
	cout << "have always wanted to be more like Indiana Jones, you have" << endl;
	cout << "mounted an expedition to find it." << endl;
/*
	cout << "Welcome to the Hogwarts School of Witchcraft and Wizardry." << endl;
	cout << "Your goal is to find the treasure and escape with it." << endl;
*/

	string player_name;
	cout << "Enter your name: ";
	getline(cin, player_name);

	cout << endl;
	game.printDescription();

	bool is_quit = false;
	while(!is_quit && !game.isOver())
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
			game.moveNorth();
			break;
		case 's':
			game.moveSouth();
			break;
		case 'e':
			game.moveEast();
			break;
		case 'w':
			game.moveWest();
			break;

		case 't':
			cout << "Take what? ";
			getline(cin, line);

			if(line != "")
				game.takeItem(line[0]);
			else
				cout << "Invalid item." << endl;
			break;

		case 'l':
			cout << "Leave what? ";
			getline(cin, line);

			if(line != "")
				game.leaveItem(line[0]);
			else
				cout << "Invalid item." << endl;
			break;

		case 'i':
			game.printInventory();
			break;

		case 'r':
			cout << "Are you sure you want to restart? ";
			getline(cin, line);
			if(line != "" && line[0] == 'y')
			{
				doEndScore(game, player_name);
				game.reset();
				game.printDescription();
			}
			break;

		default:
			cout << "Invalid command!" << endl;
			break;
		}
	}

	doEndScore(game, player_name);

	//cout << "Thank you for playing Blizzard Valley!" << endl;
	//cout << "Thank you for playing Ghostwood Manor!" << endl;
	cout << "Thank you for playing Jungle Quest!" << endl;
	//cout << "Thank you for playing Hogwarts!" << endl;

	return 0;
}



void doEndScore (const Game& game,
                 const string& player_name)
{
	cout << endl;
	cout << "In this game you scored " << game.getScore() << " points." << endl;

	HighScores high_scores(GAME_NAME);
	high_scores.insert(game.getScore(), player_name);
	high_scores.save(GAME_NAME);
	high_scores.print();
	cout << endl;
}
