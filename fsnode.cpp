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
*	Zeroing default constructor
***************************************/
FSNode::FSNode(){
	this->size = this->modTime = this->isDirectory = 0;
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
	struct stat filestats;
// Load POSIX node info
	if (stat(path, &filestats) >= 0){
		this->name = path;
		this->modTime = filestats.st_mtime;
	// If node is a directory, count sub^1 elements and exclude self and parent
		if (this->isDirectory = S_ISDIR(filestats.st_mode)){
			DIR * dir;
			if (!(dir = opendir(path))){
				cantopen(path);
			}
			struct dirent *dp;
			this->size = 0;
			while(dp = readdir(dir)){
				if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
					this->size++;
				}
			}
			closedir(dir);
	// If node is a file, store filesize in bytes
		}else{
			this->size = filestats.st_size;
		}
	}else{
		this->size = this->modTime = this->isDirectory = 0;
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
const char * FSNode::getname() const{
	return this->name;
}
bool FSNode::getisDirectory() const{
	return this->isDirectory;
}
time_t FSNode::getmodTimeRaw() const{
	return this->modTime;
}
const char * FSNode::getmodTime() const{
	return ctime(&this->modTime);
}
size_t FSNode::getsize() const{
	return this->size;
}

std::string humansize(size_t size){
	const char pows[] = "BKMG";
	std::stringstream ss;
	size_t scale = 1;
	float humansize = size;
	while ((humansize > 1024) && (scale < sizeof(pows))){
		humansize /= 1024.0;
		scale++;
	}
	ss.precision(3);
	ss << humansize << ' ' << pows[scale - 1];
	return ss.str();
}

#ifdef FSNODE_DEBUG

#include <cstdlib>
#include <ctime>

#include <iostream>
using namespace std;

void FSNodeDump(FSNode & node){
	std::cout
		<< (node.getisDirectory()? "dir" : "file") << '\t'
		<< node.getname() << '\t';
	if (node.getisDirectory()){
		cout << node.getsize() << " elements";
	}else{
		cout << humansize(node.getsize());
	}
	cout << '\t' << node.getmodTime();
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
