#ifndef __FSNODE_H__
#define __FSNODE_H__

#include <string>

class FSNode{
	const char * name;
	bool isDirectory;
	time_t modTime;
	size_t size;
public:
// Constructors
	FSNode();
	FSNode(const char * filename);
	FSNode(std::string filename);
	void load(const char * filename);
// Getters
	const char * getname();
	bool getisDirectory();
	time_t getmodTimeRaw();
	const char * getmodTime();
	size_t getsize();
};

#endif	// __FSNODE_H__
