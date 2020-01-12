//Author: Abdullah Khan
//Description: This file implements myrm functions which is like the rm command in linux
//Date: 03/10/2019
#include "File.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {  //make sure that the program has 2 arguments otherwise set an error to the user
		cerr << "This function has 2 arguments!" << endl;
		cerr << "Format: ./[objectname] [filename]" << endl;
		return 0;
	}
	//create a new file and handle the error if cannot create
	File* myStatFile = new File(argv[1]);
	if (myStatFile->getErrsv() == -1) {
		return 0;
	}
	//use the remove function to remove the file after
	myStatFile->Remove(argv[1]);
	return 0;
}
