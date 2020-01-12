//Author: Abdullah Khan
//Description: This file implements mymv functions which is like the mv command in linux
//Date: 03/10/2019
#include "File.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) { //make sure that the program has 3 arguments otherwise set an error to the user
		cerr << "This function has 3 arguments!" << endl;
		cerr << "Format: ./[objectname] [source] [destination]" << endl;
		return 0;
	}
	File *myMvFile = new File(argv[1]); //create the file object and return an error if the path isn not found
	if (myMvFile->getErrsv() == -1) {
		return 0;
	}
	//create the streams for the dump function
	fstream src,dest; //this is implemented the same as the cp function except we are removing the file in the end
	src.open(argv[1]);
	dest.open(argv[2],fstream::out);
	if (myMvFile->Dump(src, dest, 0) == ENOTSUP) { //dump the content into the dest which is the new file
		src.close();
		dest.close();
		return 0;
	}
	src.close();
	dest.close();
	myMvFile->Remove(argv[1]); //remove the current file object and the current file and keep the new one
	return 0;
}
