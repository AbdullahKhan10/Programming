
//Author: Abdullah Khan
//Description: This file implements mydiff functions which is like the diff command in linux
//Date: 03/10/2019#include "File.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {  //make sure that the program has 3 arguments otherwise set an error to the user
		cerr << "This function has 3 arguments!" << endl;
		cerr << "Format: ./[objectname] [filename1] [filename2]" << endl;
		return 0;
	}
	File* myDiffFile1 = new File(argv[1]); //create a file object for the given file number 1
	if (myDiffFile1->getErrsv() == -1) { //error if file not found
		return 0;
	}
	File* myDiffFile2 = new File(argv[2]); //create a file object for the given file number 2
	if (myDiffFile1->getErrsv() == -1) { //error if file not found
		return 0;
	}
	bool cmp = myDiffFile1->Compare(myDiffFile2); //use the compare function to compare the files and output where they are the same or not
	if (cmp) {
		cout << "The files are the same!" << endl;
	}
	else {
		cout << "The files are different!" << endl;
	}
	return 0;
}
