//Author: Abdullah Khan
//Description: This file implements mycat functions which is like the cat command in linux
//Date: 03/10/2019
#include "File.h"

using namespace std;

int main(int argc, char* argv[]) {
	for(unsigned int i = 1; i < argc; i++) { //start from the second argument and create a file object for every filename given as argument
		File* myCatFile = new File(argv[i]);
		//error handling if the file cannot be created
		if (myCatFile->getErrsv() == -1) {
			return 0;
		}
		if (myCatFile->getType() == S_IFDIR) {
			cout << "'" << myCatFile->getName() << "'" << " is a directory!" << endl;
			return 0;
		}
		fstream src,dest; //create a fstream for the src and dest which we need for the dump function
		//open both of the streams with the given arguments
		src.open(argv[i]);
		dest.open(argv[i]);

		if (myCatFile->Dump(src, dest, 1) == ENOTSUP) { //dump the contents of src to dest using the dump func and this function is using func = 1 so it will print the contents
			src.close();
			dest.close();
			return 0;
		}
		//close the streams
		src.close();
		dest.close();
	}
	cout << endl;
	return 0;
}
