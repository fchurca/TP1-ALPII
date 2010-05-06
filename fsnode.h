#ifndef __FSNODE_H__
#define __FSNODE_H__

#include <string>

class FSnode{
	std::string name;
	bool isDirectory;
	time_t modTime;
	size_t size;
public:
// Constructors
	FSNode(const char * filename);
	FSNode(std::string filename);
	FSNode(); // No declaration forces using above constructors
// Getters
	const char * getname();
	const std::string & getname();
	bool getisDir();
	time_t getmodTime();
	const std::string & getmodTime();
	size_t getsize();
};

#endif
