#include "fsnode.h"
#include <sys/stat.h>

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
		this->size = filestats.st_size;
		this->modTime = filestats.st_mtime;
		this->isDirectory = S_ISDIR(filestats.st_mode);
	}else
		throw "AYEEEEEEE";
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

int main(int argc, char **argv){
	FSNode
		app(*argv),
		here;
	here.load(".");
	cout
		<< app.getname() << " ("
		<< (app.getisDirectory() ? "directory" : "file") << "): " << endl
		<< "Size: " << app.getsize() << " B"<< endl
		<< "Last mod time: " << app.getmodTime()
		<< here.getname() << " ("
		<< (here.getisDirectory() ? "directory" : "file") << "): " << endl
		<< "Size: " << app.getsize() << " B"<< endl
		<< "Last mod time: " << here.getmodTime();

	return EXIT_SUCCESS;
}

#endif
