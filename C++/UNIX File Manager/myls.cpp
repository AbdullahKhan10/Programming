//Author: Abdullah Khan
//Description: This file implements myls functions which is like the ls command in linux
//Date: 03/10/2019
#include "File.h"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc == 1) { //this is the case where the only arg is the object file
		File* filels;
		filels->ExpandCwd(1); //prints out all the files in the current directory using expandCWD with the function 1 for printing
		cout << endl;
		return 0;
	}
	else if (argc == 2) {
		if (strcmp(argv[1], "-l") == 0) { //this is the case where the only arg is the object file and -1 for the second arg
			File* filelsl;
			filelsl->ExpandCwd(2); //prints out all the files in the current directory using expandCWD with the function 2 for printing will print more useful stuff
			cout << endl;
			return 0;
		}
		else {
			File* filelsf = new File(argv[1]); //this is the case where the only arg is the object file and filename for the second arg
			if (filelsf->getType() == S_IFDIR) {
				filelsf->Expand(1); //use the expand func = 1 to print all the file in the given direntory
				cout << endl;
				return 0;
			}
			else {
				cout << filelsf->getName() << endl; //if the specified file is not a directory then just print the file name
				cout << endl;
				return 0;
			}
		}
	}
	else if (argc == 3) { //this is the case where we are using the -l functionality for the ls command
		if (strcmp(argv[1], "-l") == 0) { //checks if the second argument -1
			File* filelslf = new File(argv[2]);
			string tp; //change the type to a different string format for the given form
			if (filelslf->getType() == S_IFDIR)	{
				tp = "d";
			}
			else {
				tp = "-";
			}
			//print in ls -1 fashion
			cout << filelslf->getName() << "  " << tp << filelslf->getPermissions()<< " "
								  << filelslf->getOwnerUserName() << " " << filelslf->getGroupName()  << " "
								  << filelslf->getSize() << " " << filelslf->getModificationTime();
			return 0;
		}
		else {
			cerr << "Enter valid command" << endl;
		}

	}
	else { //if the user enters too many arguments
		cerr << "Too many arguments!" << endl;
	}

}
