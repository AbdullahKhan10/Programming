//Author: Abdullah Khan
//Description: This file implements the header file function stored in File.h
//Date: 03/10/2019

#include "File.h" //includes the header file

using namespace std;

/*Function Name: Constructor
 * Description: This creates the file object of the class
 * Parameters: fileName - is the name of the file that the object is being created for
 * Return: n/a
 */
File::File(const char* fileName){
	struct stat sb; //buffer storing the values of the file
	if (stat(fileName, &sb) == -1) { //checks if file name is valid otherwise sets a null value for the attributes
		name = "";
		type = 0;
		size = 0;
		ownerUserId = 0;
		ownerUserName = "";
		groupId = 0;
		groupName = "";
		permissions = "";
		accessTime = "";
		modificationTime = "";
		statusChangeTime = "";
		blockSize = 0;
		children.clear();
		errsv = -1;
		cerr << "Cannot find the entered file name: " << fileName << endl;
	}
	else { //This uses the buffer to initialize all the attributes of the class
	name = fileName;
	//Below is the state to find the file type and set it to the attribute
	if (S_ISREG(sb.st_mode)) {
		type = S_IFREG;
	}
	else if (S_ISDIR(sb.st_mode)) {
		type = S_IFDIR;
	}
	else if (S_ISCHR(sb.st_mode)) {
		type = S_IFCHR;
	}
	else if (S_ISBLK(sb.st_mode)) {
		type = S_IFBLK;
	}
	else if (S_ISFIFO(sb.st_mode)) {
		type = S_IFIFO;
	}
	else if (S_ISLNK(sb.st_mode)) {
		type = S_IFLNK;
	}
	else if (S_ISSOCK(sb.st_mode)) {
		type = S_IFSOCK;
	}
	else { //otherwise tell the user that the type cannot be set
		errsv = -1;
		cerr << "Cannot set file type for '" << fileName << "'" << endl;
		return; //close the constructor
	}
	size = sb.st_size;
	ownerUserId = sb.st_uid;
	ownerUserName = getpwuid(ownerUserId)->pw_name;
	groupId = sb.st_gid;
	groupName = getgrgid(groupId)->gr_name;
	//finds the string value of permissions for the permissions attribute
	string s1 = (sb.st_mode & S_IRUSR) ? "r" : "-";
	string s2 = (sb.st_mode & S_IWUSR) ? "w" : "-";
	string s3 = (sb.st_mode & S_IXUSR) ? "x" : "-";
	string s4 = (sb.st_mode & S_IRGRP) ? "r" : "-";
	string s5 = (sb.st_mode & S_IWGRP) ? "w" : "-";
	string s6 = (sb.st_mode & S_IXGRP) ? "x" : "-";
	string s7 = (sb.st_mode & S_IROTH) ? "r" : "-";
	string s8 = (sb.st_mode & S_IWOTH) ? "w" : "-";
	string s9 = (sb.st_mode & S_IXOTH) ? "x" : "-";
	permissions = s1 + s2 + s3 + s4 + s5 + s6+ s7+ s8+ s9;
	//sets the time to the matching buffer values
	accessTime = ctime(&sb.st_atime);
	modificationTime = ctime(&sb.st_mtime);
	statusChangeTime = ctime(&sb.st_ctime);
	blockSize = sb.st_blksize;

	//checks which expand function to use and uses that one
	if (name.compare(".") == 0) {
		ExpandCwd(0); //uses the current working directory expand
	}
	else {
		Expand(0); //uses the regular expand
	}
	errsv = 0;
	}
}

/*Function Name: Destructor
 * Description: This is required to kill the program properly
 * Parameters: n/a
 * Return: n/a
 */
File::~File(){
	children.~vector(); //free the vector attribute
}

/*Function Name: Dump
 * Description: This dumps the contents of one stream to another stream
 * Parameters: src - this is the source of the dump
 * 			   dest - this stream is where its dumped
 * 			   func - you can you a function ie.print buffer if func = 1
 * Return: 0 is returned if this happens properly otherwise gives error. this doesnt work for directories
 */
int File::Dump(fstream &src, fstream &dest, int func){
	if (type == S_IFREG) { //checks if directory

		if (func == 1) { //if you want to print out the buffer
			cout << src.rdbuf();
			return 0;
		}

		//sets the buffer objects to read the parameters
		filebuf* inbuf = src.rdbuf();
		filebuf* outbuf = dest.rdbuf();

		char c = inbuf->sbumpc();
		while (c != EOF) { //loops through the entire file and puts the content of src to dest
			outbuf->sputc(c);
			c = inbuf->sbumpc();

		}
		return 0;
	}
	else { //otherwise return an error
		cerr << "This file is a directory!" << endl;
		return ENOTSUP;
	}
}

/*Function Name: Rename
 * Description: This renames the file object and the actual file
 * Parameters: oldFilename - this is old name
 * 			   newFileName - this is the new file name
 * Return: 0 if the function is successful otherwise returns an error
 */
int File::Rename(const char *oldFileName, const char *newFileName) {
	if (rename(oldFileName, newFileName) == -1) { //sets the name of the actual file
		errsv = errno; //sets an error
		cerr << strerror(errsv) << endl;
		return errsv; //returns error
	}
	else {
		name = newFileName; //sets the name of the file object
		return errsv;
	}
}

/*Function Name: Remove
 * Description: This removes a file object and the actual file
 * Parameters: fileName - name of the file
 * Return:  0 if the function is successful otherwise returns an error
 */
int File::Remove(const char *fileName) {
	if (unlink(fileName) == -1) { //this deletes the actual file if possible
		errsv = errno; //if not possible return an error
		cerr << "Cannot remove! " << strerror(errsv) << endl;
		return errsv;
	}
	//reset the object to its default
	name = "";
	type = 0;
	size = 0;
	ownerUserId = 0;
	ownerUserName = "";
	groupId = 0;
	groupName = "";
	permissions = "";
	accessTime = "";
	modificationTime = "";
	statusChangeTime = "";
	blockSize = 0;
	children.clear();
	errsv = errno;
	return errsv;
}

/*Function Name: Compare
 * Description: This compares this object and another object given as parameter
 * Parameters: destfile - name of the file
 * Return: true if they are the same false otherwise
 */
bool File::Compare(File *destfile) {
	//create a fstream for both of the file
	ifstream srcFile(name.c_str(), ifstream::in | ifstream::binary);
	ifstream destFile(destfile->name.c_str(), ifstream::in | ifstream::binary);
	if (!srcFile.is_open() || !destFile.is_open()) { //checker to see if they are opened properly
		cerr << "File not open in compare function!" << endl;
		errsv = -1;
		return false; //return an error if cannot open properly
	}

	if (type != destfile->type || size != destfile->size || blockSize != destfile->blockSize) { //check whether the sizes and the blocksizes are differrent first
		return false;
	}

	if (type == S_IFDIR && destfile->type == S_IFDIR) { //if its a directory compare that all the children are the same as well

		if (children.size() == destfile->children.size()) {

			for (unsigned int i = 0; i < children.size(); i++) { //loop through the children to see if they are the same
				if (children.at(i).name.compare(destfile->children.at(i).name) != 0) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	//create buffer for the src and dest to store the contents in each
	char *srcBuf = new char[blockSize]();
	char *destBuf = new char[blockSize]();
	do { //loop through the whole file to see if they are the same
		srcFile.read(srcBuf, blockSize);
		destFile.read(destBuf, blockSize);
		if (memcmp(srcBuf, destBuf, blockSize) != 0) {
			//delete both the buffers taking up memory
			delete[] srcBuf;
			delete[] destBuf;
			return false;
		}
	}while (srcFile.good() || destFile.good());
	delete[] srcBuf;
	delete[] destBuf;

	return true; //returns true if all checks
}

/*Function Name: ExpandCwd
 * Description: This expands current directory
 * Parameters: func - if you want to print set this to 1 or 2 if you want to print another way otherwise set it to anything else
 * Return: n/a
 */
void File::ExpandCwd(int func) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (".")) != NULL) { //open the CWD and iterate though it
	  while ((ent = readdir (dir)) != NULL) {
		  string temp = ent->d_name;
		  string firstCharacter = temp.substr(0,1);
		  if (firstCharacter.compare(".") != 0) {
			  if (func == 1) { //print the contents if the func is 1
				  cout << ent->d_name << "  ";
			  }
			  else {
				  string fileName = ent->d_name;
				  File *cwdFile = new File(fileName.c_str());
				  if (func == 2) { //print the contents in ls -1 fashion if func is 2
					  string tp = ConvertType(cwdFile->type);
					  cout  << cwdFile->name << "  "<< tp << cwdFile->permissions << " "
					  << cwdFile->ownerUserName << " " << cwdFile->groupName  << " "
					  << cwdFile->size << " " << cwdFile->modificationTime;
				  }
				  //children.push_back(*cwdFile);
			  }
		  }
	  }
	  closedir (dir);
	}
	else {
	  cerr << "Error expanding the current working directory" << endl;
	}
}

/*Function Name: Expand
 * Description: This expands a file if it is a directory
 * Parameters: func - if you want to print set this to 1 otherwise set it to anything else
 * Return: n/a
 */
void File::Expand(int func) {
	if (type == S_IFDIR) {
		DIR *dir; //the directory object
		struct dirent *sd; //the struct buffer
		dir = opendir(name.c_str());

		if (dir == NULL) { //error if you cant open the dir
			cerr << "Cannot open directory '" << name << "'" << endl;
			children.clear();
			return;
		}
		else {
			while ((sd=readdir(dir)) != NULL) { //iterate though the whole thing and add the files as children
				if (strcmp(sd->d_name,".") != 0 && strcmp(sd->d_name,"..") != 0) { //file objects created and send to the children attribute
				string pathName = name;
				pathName = pathName + "/";
				pathName = pathName + sd->d_name;

				if (func == 1) {
					cout << sd->d_name << "  ";
				}

				File childDir(pathName.c_str());
				children.push_back(childDir); //put the children into the vector
				}
			}
			closedir(dir); //close the dir
			errsv = errno;
			if (errsv != 0) {
				cout << strerror(errsv) << endl;
			}
		}
	}
}

/*Function Name: PrintStat
 * Description: This prints the attributes of the object in a personalized stat like manner
 * Parameters: n/a
 * Return: n/a
 */
void File::printStat() {
	//Normally prints all the attributes using the cout stream
	cout << "Name: " << name << endl;
	cout << "Type: "<< type << endl;
	cout << "Size: " << size << endl;
	cout << "Owner User Id: " << ownerUserId << endl;
	cout << "Owner User Name: " << ownerUserName << endl;
	cout << "Group Id: " << groupId << endl;
	cout << "Group Name: " << groupName << endl;
	cout << "Permissions: " << permissions << endl;
	cout << "Access Time: " << accessTime ;
	cout << "Modification Time: " << modificationTime ;
	cout << "Status Change Time: " << statusChangeTime ;
	cout << "Block Size: " << blockSize << endl;
	cout << "Children: " << endl;
	for (unsigned int i = 0; i < children.size(); i++) { //prints the children if its a directory as well
		cout << "/" << children.at(i).name << endl;
	}
}

/*Function Name: printsCat
 * Description: prints the contents of a file
 * Parameters: file - the file which you want to print
 * Return: error code if not supported
 */
int File::printCat(ifstream file) {
	if (type == S_IFREG) { //read the file into a buffer and print it
		cout << file.rdbuf();
		return 0;
	}
	else {
		return ENOTSUP;
	}
}

/*Function Name: ConvertType
 * Description: Checks if file is a directory and if it is set it to "d"
 * Parameters: type - is the current type
 * Return: either d if its a directory or - if its not
 */
string File::ConvertType(int &type) {
	if (type == S_IFDIR) {
		return "d";
	}
	else {
		return "-";
	}
}







