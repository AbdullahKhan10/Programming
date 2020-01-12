//Author: Abdullah Khan
//Description: This file implements mystat functions which is like the stat command in linux
//Date: 03/10/2019
#include "File.h"

using namespace std;

int main(int argc, char* argv[]) { //need to make this on directories, some issues with expand function
	if (argc != 2) {
		cerr << "This function has 2 arguments!" << endl;
		cerr << "Format: ./[objectname] [filename]" << endl;
		return 0;
	}
	//create a new file and handle the error if cannot create
	File* myStatFile = new File(argv[1]);
	if (myStatFile->getErrsv() == -1) {
		return 0;
	}
	//use the printStat function to print the contents of the file
	myStatFile->printStat();
	return 0;
}

