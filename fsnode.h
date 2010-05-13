#ifndef __FSNODE_H__
#define __FSNODE_H__

#include <string>
#include <cstdlib>

/***************************************
* cantopen()
*	Thinly disguised runtime_error throw
*	DOES NOT RETURN
***************************************/
void cantopen(const char * path);

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
//	Wrapper for using cstring version without calling std::string::c_str()
//	May throw runtime_error if path is unreachable
	FSNode(const std::string & path);

//******************
// load(const char *)
//	Load node information
//	May throw runtime_error if path is unreachable
	void load(const char * path);

//******************
// load(const std::string &)
//	Wrapper for using cstring version without calling std::string::c_str()
//	May throw runtime_error if path is unreachable
	void load(const std::string & path);

//**************************
// Getters

//******************
//	Get local name of the file
	const std::string &getname() const;

//******************
//	Get file location
	const std::string &getpath() const;

//******************
//	Get full filename
	std::string getfullname() const;

//******************
//	Get node type
	bool getisDirectory() const;

//******************
//	Get Unix time of last modification
	time_t getmodTimeRaw() const;

//******************
//	Get time of last modification as C string
//		FOR dmr , KEN AND KERNIGHAN'S SAKE COPY CONTENTS, DON'T USE AS POINTER
	const char * getmodTime() const;

//******************
//	Get sub(1)elements of the directory, or size of the node in bytes if file
	size_t getsize() const;

//**************************************
// Members
protected:
//******************
//	Filename
	std::string name;
//******************
//	File location
	std::string path;
//******************
//	Full filename
	std::string fullname;
//******************
//	Whether the node is a directory (true) or a file (false)
//		Devices show up as size 0 files
	bool isDirectory;
//******************
//	Unix time of last modification
	time_t modTime;
//******************
//	Sub(1)elements of the directory, or size of the node in bytes if file
	size_t size;

friend class FSModel;	//	Let FSModel have direct access to members
						//		
};

std::string humansize(size_t size);

#endif	// __FSNODE_H__
