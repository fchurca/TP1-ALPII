#ifndef __FSNODE_H__
#define __FSNODE_H__

#include <sys/stat.h>

#include <string>
#include <cstdlib>

#include <ostream>

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

//******************
// dump(std::ostream&)
//	Dump contents to std::ostream out
	void dump(std::ostream & out) const;

//******************
// compare(FSNode&)
//	Determine which goes first in a list by path/type/name
	char compare(FSNode & other);

//**************************
// Getters

	const std::string &getname() const;
	const std::string &getpath() const;
	std::string getfullname() const;
	bool getisDirectory() const;
	time_t getmtime() const;
	std::string getCmtime() const;
	size_t getsize() const;

//**************************************
// Members
protected:
//******************
// Filename
	std::string name;

//******************
// File location
	std::string path;

//******************
// Full filename
	std::string fullname;
	
//******************
// Node type
//	true if directory, false if file or device
	bool isdir;

//******************
// Sub(1)elements if directory, or size of the node in bytes if file
	size_t size;

//******************
// Unix time of last modification
	time_t mtime;

//**************************************
// Friends

//******************
// class FSModel
//	Will need access to protected members to be able to load them more quickly
//	(albeit less elegantly)
friend class FSModel;
};

#endif	// __FSNODE_H__
