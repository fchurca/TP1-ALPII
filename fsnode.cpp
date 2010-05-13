#include "fsnode.h"

#include <sys/stat.h>
#include <dirent.h>
#include <cstring>

#include <stdexcept>
#include <sstream>

/***************************************
* cantopen(const char *)
*	Thinly disguised runtime_error throw
*	DOES NOT RETURN
***************************************/
void cantopen(const char * path){
	std::string temp = "Can't open ";
	temp += path;
	throw std::runtime_error(temp);
}

/***************************************
* FSNode()
*	Empty default constructor
***************************************/
FSNode::FSNode(){
}

/***************************************
* FSNode(const char *)
*	Load node information
***************************************/
FSNode::FSNode(const char * path){
	this->load(path);
}

/***************************************
* FSNode(const std::string &)
*	Wrap to cstring version
***************************************/
FSNode::FSNode(const std::string & path){
	this->load(path.c_str());
}

/***************************************
* load(const char *)
*	Load node information
***************************************/
void FSNode::load(const char * path){
// Load POSIX node info
	if (stat(path, &(this->filestats)) >= 0){
		this->name = path;
	// If node is a directory, count sub^1 elements and exclude self and parent
		if (S_ISDIR(this->filestats.st_mode)){
			DIR * dir;
			this->filestats.st_size = 0;
			if (!(dir = opendir(path))){
				cantopen(path);
			}
			struct dirent *dp;
			struct stat tempstat;
			while(dp = readdir(dir)){
				stat(dp->d_name, &tempstat);
				if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
					this->filestats.st_size++;
				}
			}
			closedir(dir);
		}
	}else{
		cantopen(path);
	}
}

/***************************************
* load(const std::string &)
*	Wrap to cstring version
***************************************/
void FSNode::load(const std::string & path){
	this->load(path.c_str());
}

//**************************************
// Getters
const std::string & FSNode::getname() const{
	return this->name;
}
const std::string & FSNode::getpath() const{
	return this->path;
}
std::string FSNode::getfullname() const{
	return this->fullname;
}
bool FSNode::getisDirectory() const{
	return S_ISDIR(this->filestats.st_mode);
}
time_t FSNode::getmodTimeRaw() const{
	return this->filestats.st_mtime;
}
std::string FSNode::getmodTime() const{
	std::string aux = ctime(&this->filestats.st_mtime);
	aux.erase(aux.length() - 1);
	return aux;
}
size_t FSNode::getsize() const{
	return this->filestats.st_size;
}

std::string humansize(size_t size){
	const char pows[] = "BkMG";
	std::stringstream ss;
	size_t scale = 1;
	while ((size > 1024) && (scale < sizeof(pows))){
		size >>= 10;
		scale++;
	}
	ss << size << ' ' << pows[scale - 1];
	if (scale > 1){
		ss << 'i';
	}
	return ss.str();
}

#ifdef FSNODE_DEBUG

#include <cstdlib>
#include <ctime>

#include <iostream>
using namespace std;

void FSNodeDump(FSNode & node){
	std::cout
		<< (node.getisDirectory()? "dir" : "file") << '\t';
	if (node.getisDirectory()){
		std::cout << node.getsize() << " E";
	}else{
		std::cout << humansize(node.getsize());
	}
	std::cout
		<< '\t' << node.getmodTime() << '\t'
		<< node.getname() << endl;
}

int main(int argc, char **argv){
	for (size_t i = 0; i < argc; i++){
		try{
			FSNode node(argv[i]);
			FSNodeDump(node);
		}catch(runtime_error e){
			cerr << e.what() << endl;
		}
	}
	return EXIT_SUCCESS;
}

#endif	// FSNODE_DEBUG
