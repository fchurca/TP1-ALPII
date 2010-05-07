#ifndef __FSNODE_H__
#define __FSNODE_H__

#include <string>

/***************************************
* cantopen()
*	Thinly disguised runtime_error throw
*	DOES NOT RETURN
***************************************/
void cantopen(const char * path);

class FSNode{
public:
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

//**************************************
// Getters
	const char * getname() const;
	bool getisDirectory() const;
	time_t getmodTimeRaw() const;
	const char * getmodTime() const;
	size_t getsize() const;

protected:
	const char * name;
	bool isDirectory;
	time_t modTime;
	size_t size;
};

#endif	// __FSNODE_H__
