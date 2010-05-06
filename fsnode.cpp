#include "fsnode.h"

FSNode::FSNode(const char * filename){
	this->load(filename);
}

FSNode::FSNode(std::string filename){
	this->load(filename.c_str());
}

void FSNode::load(const char * filename){
	this->name = filename;
	this->isDirectory = this->modTime = this->size = 0;
}

#ifdef DEBUG_FSNODE

#include <cstdlib>
#include <ctime>

#include <iostream>
using namespace std;

int main(int argc, char **argv){
	FSNode
		app(*argv),
		here(".");
/*	cout
		<< app.getname() << " (" <<
		<< (app.getisDir() ? "directory" : "file") << "): " << endl
		<< "Size: " << app.getsize() <<
		<< "Last mod time: " << ctime(&app.getmodTime()) << endl;
*/	return EXIT_SUCCESS;
}

#endif
