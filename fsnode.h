#ifndef __FSNODE_H__
#define __FSNODE_H__

#include <string>
#include <cstdlib>

#include <sys/stat.h>

//**************************************
// cantopen()
//	Thinly disguised runtime_error throw
//	DOES NOT RETURN
void cantopen(const char * path);

//**************************************
// humansize()
//	Translates a size_t size in bytes into STL string with binary powers
std::string humansize(size_t size);

class FSNode{
public:
//**************************************
// Methods

//******************
// FSNode()
//	Zeroing default constructor
	FSNode();

//******************
// FSNode(const char * path)
//	Load node information
//	May throw runtime_error if path is unreachable
	FSNode(const char * path);

//******************
// FSNode(const std::string & path)
//	Wrap to cstring version
//	May throw runtime_error if path is unreachable
	FSNode(const std::string & path);

//******************
// load(const char *)
//	Load node information
//	May throw runtime_error if path is unreachable
	void load(const char * path);

//******************
// load(const std::string &)
//	Wrap to cstring version
//	May throw runtime_error if path is unreachable
	void load(const std::string & path);

//**************************
// Getters

//******************
// Filename
	const std::string &getname() const;
//******************
// File location
	const std::string &getpath() const;

//******************
// Full filename
	std::string getfullname() const;

//******************
// Node type
//	Devices show up as size 0 files
	bool getisDirectory() const;

//******************
// Unix time of last modification
	time_t getmodTimeRaw() const;

//******************
// Time of last modification as STL string
//	Www Mmm dd hh:mm:ss YYYY
	std::string getmodTime() const;

//******************
// Size
//	Sub(1)elements if directory, or size of the node in bytes if file
	size_t getsize() const;

//**************************************
// Members
protected:
//******************
// POSIX filestats
	struct stat filestats;
//******************
// Filename
	std::string name;
//******************
// File location
	std::string path;
//******************
// Full filename
	std::string fullname;

//**************************************
// Friends

//******************
// class FSModel
//	Will need access to protected members to be able to load them more quickly
//	(albeit less elegantly)
friend class FSModel;
};

#endif	// __FSNODE_H__
