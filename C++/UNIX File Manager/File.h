//Author: Abdullah Khan
//Description: This file is the header file of the file objects which we need for the functionality of the program
//Date: 03/10/2019

//define the header
#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

//include all the required libraries
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <errno.h>

//this is the class that is being declared for each file object is going to be implemented in the File.cpp file
class File {
private: //all the attributes are going to private
	//all the attributes which are going to set in the constructor
	std::string name;
	int type;
	int size;
	int ownerUserId;
	std::string ownerUserName;
	int groupId;
	std::string groupName;
	std::string permissions;
	std::string accessTime;
	std::string modificationTime;
	std::string statusChangeTime;
	int blockSize;
	std::vector<File> children; //files children files for directories
	int errsv;
public: //these are all the functions which the class is going to have which are implemented in the file.cpp file
	File(const char* fileName);
	~File();
	int Dump(std::fstream &src, std::fstream &dest, int func);
	int Rename(const char *oldFileName, const char *newFileName);
	int Remove(const char *fileName);
	bool Compare(File *cfile);
	void Expand(int func);
	void ExpandCwd(int func);
	void printStat();
	std::string ConvertType(int &type);
	int printCat(std::ifstream file);
	void printChildren();

	//below are all the getters and setters for all the attributes of the class
	const std::string& getAccessTime() const {
		return accessTime;
	}

	void setAccessTime(const std::string& accessTime) {
		this->accessTime = accessTime;
	}

	int getBlockSize() const {
		return blockSize;
	}

	void setBlockSize(int blockSize) {
		this->blockSize = blockSize;
	}

	const std::vector<File>& getChildren() const {
		return children;
	}

	void setChildren(const std::vector<File>& children) {
		this->children = children;
	}

	int getErrsv() const {
		return errsv;
	}

	void setErrsv(int errsv) {
		this->errsv = errsv;
	}

	int getGroupId() const {
		return groupId;
	}

	void setGroupId(int groupId) {
		this->groupId = groupId;
	}

	const std::string& getGroupName() const {
		return groupName;
	}

	void setGroupName(const std::string& groupName) {
		this->groupName = groupName;
	}

	const std::string& getModificationTime() const {
		return modificationTime;
	}

	void setModificationTime(const std::string& modificationTime) {
		this->modificationTime = modificationTime;
	}

	const std::string& getName() const {
		return name;
	}

	void setName(const std::string& name) {
		this->name = name;
	}

	int getOwnerUserId() const {
		return ownerUserId;
	}

	void setOwnerUserId(int ownerUserId) {
		this->ownerUserId = ownerUserId;
	}

	const std::string& getOwnerUserName() const {
		return ownerUserName;
	}

	void setOwnerUserName(const std::string& ownerUserName) {
		this->ownerUserName = ownerUserName;
	}

	const std::string& getPermissions() const {
		return permissions;
	}

	void setPermissions(const std::string& permissions) {
		this->permissions = permissions;
	}

	int getSize() const {
		return size;
	}

	void setSize(int size) {
		this->size = size;
	}

	const std::string& getStatusChangeTime() const {
		return statusChangeTime;
	}

	void setStatusChangeTime(const std::string& statusChangeTime) {
		this->statusChangeTime = statusChangeTime;
	}

	int getType() const {
		return type;
	}

	void setType(int type) {
		this->type = type;
	}
};

#endif
