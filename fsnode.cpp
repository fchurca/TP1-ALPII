#include "fsnode.h"
#include <sys/stat.h>
#include <stdexcept>

FSNode::FSNode(){}
FSNode::FSNode(const char * filename){
	this->load(filename);
}
FSNode::FSNode(std::string filename){
	this->load(filename.c_str());
}

void FSNode::load(const char * filename){
	struct stat filestats;
	if (stat(filename, &filestats) >= 0){
		this->name = filename;
		this->isDirectory = S_ISDIR(filestats.st_mode);
		this->modTime = filestats.st_mtime;
		if (this->isDirectory);
		else
			this->size = filestats.st_size;
	}else{
		std::string temp = "Could not open ";
		temp += filename;
		temp += " for stat()";
		throw std::runtime_error(temp);
	}
}

const char * FSNode::getname(){
	return this->name;
}
bool FSNode::getisDirectory(){
	return this->isDirectory;
}
time_t FSNode::getmodTimeRaw(){
	return this->modTime;
}
const char * FSNode::getmodTime(){
	return ctime(&this->modTime);
}
size_t FSNode::getsize(){
	 return this->size;
}

#ifdef FSNODE_DEBUG

#include <cstdlib>
#include <ctime>

#include <iostream>
using namespace std;

void FSNode::dump(){
	std::cout
		<< this->getname() << '\t' << (this->getisDirectory() ? " D " : " F ")
		<< '\t' << this->getsize() << " B "<< '\t' << this->getmodTime();
}

int main(int argc, char **argv){
	FSNode
		app(*argv),
		here;
	here.load(".");

	app.dump();
	here.dump();

	return EXIT_SUCCESS;
}

#endif	// FSNODE_DEBUG
