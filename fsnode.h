#ifndef __FSNODE_H__
#define __FSNODE_H__

#include <string>

class FSNode{
	std::string name;
	bool isDirectory;
	time_t modTime;
	size_t size;
	void load(const char * filename);
public:
// Constructors
	FSNode(const char * filename);
	FSNode(std::string filename);
	FSNode(); // No declaration forces using above constructors
// Getters
	const char * getname();
	bool getisDir();
	time_t getmodTime();
	size_t getsize();
};

#endif
