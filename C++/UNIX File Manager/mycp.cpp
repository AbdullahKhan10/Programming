//Author: Abdullah Khan
//Description: This file implements mycp functions which is like the cp command in linux
//Date: 03/10/2019
#include "File.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) { //make sure that the program has 3 arguments otherwise set an error to the user
		cerr << "This function has 3 arguments!" << endl;
		cerr << "Format: ./[objectname] [source] [destination]" << endl;
		return 0;
	}
	File *myCpFile = new File(argv[1]); //create a file object for the given file
	if (myCpFile->getErrsv() == -1) { //error if file cannot be found
		return 0;
	}
	fstream src,dest; //create a src and dest for the dump function
	src.open(argv[1]);
	dest.open(argv[2],fstream::out);
	if (myCpFile->Dump(src, dest, 0) == ENOTSUP) { //dump the contents of the src to dest and use the 0 function so it will just create a new file in the specified directory
		src.close();
		dest.close();
		return 0;
	}
	//close the streams
	src.close();
	dest.close();
	return 0;
}
