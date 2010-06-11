#include "FModel.h"

#include <sys/stat.h>
#include <dirent.h>
#include <cstring>

#include <stdexcept>
#include <sstream>

//**************************************
// FModel methods

//******************
// FModel()
//	Zeroing default constructor
FModel::FModel(){
	this->isdir = false;
	this-> size = 0;
	this-> mtime = 0;
}

//******************
// FModel(const char * path)
//	Load node information
FModel::FModel(const char * path){
	this->load(path);
}

//******************
// FModel(const std::string & path)
//	Wrap to cstring version
FModel::FModel(const std::string & path){
	this->load(path.c_str());
}

//******************
// load(const char *)
//	Load node information
void FModel::load(const char * path){
// Set full name
	this->fullname = path;
// Load POSIX node info
	struct stat rootstat;	
	if (stat(path, &rootstat) >= 0){
		this->mtime = rootstat.st_mtime;
	// If node is a directory, count sub^1 elements and exclude self and parent
		if (this->isdir = S_ISDIR(rootstat.st_mode)){
			this->size = 0;
			DIR * dir = opendir(path);
			if (!dir){
				throw std::runtime_error(std::string(path) + " not a valid dir");
			}
			struct dirent *dp;
			struct stat tempstat;
			while(dp = readdir(dir)){
				stat(dp->d_name, &tempstat);
				if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
					this->size++;
				}
			}
			closedir(dir);
		}else{
			this->size = rootstat.st_size;
		}
	}else{
			throw std::runtime_error(std::string("Can't open ") + path);
	}
}

//******************
// load(const std::string &)
//	Wrap to cstring version
void FModel::load(const std::string & path){
	this->load(path.c_str());
}

//******************
// dump(std::ostream&)
//	Dump contents, to std::ostream out
void FModel::dump(std::ostream & out) const{
	out
		<< (this->isdir? "dir  " : "file ");
	if (this->getisDirectory()){
		out << this->size << " #";
	}else{
		out << humansize(this->size);
	}
	out
		<< '\t' << this->getCmtime() << ' '
		<< this->fullname << std::endl;
}

//**************************
// Getters
const std::string & FModel::getname() const{
	return this->name;
}
const std::string & FModel::getpath() const{
	return this->path;
}
std::string FModel::getfullname() const{
	return this->fullname;
}
bool FModel::getisDirectory() const{
	return this->isdir;
}
time_t FModel::getmtime() const{
	return this->mtime;
}
std::string FModel::getCmtime() const{
	std::string aux = ctime(&this->mtime);
	aux.erase(aux.length() - 1);
	return aux;
}
unsigned long FModel::getsize() const{
	return this->size;
}

std::string humansize(unsigned long size){
	const char pows[] = "BKMGTPEZY";
	std::stringstream ss;
	unsigned long scale = 1;
	while ((size > 1024) && (scale < sizeof(pows))){
		size >>= 10;
		scale++;
	}
	ss << size << ' ' << pows[scale - 1];
	if (scale > 1){
		ss << "iB";
	}
	return ss.str();
}

#ifdef FModel_DEBUG

#include <iostream>
using namespace std;

int main(int argc, char **argv){
	int ret = EXIT_SUCCESS;
	if (argc > 1){
		for (unsigned long i = 1; i < argc; i++){
			try{
				FModel node(argv[i]);
				node.dump(cout);
			}catch(runtime_error e){
				cerr << e.what() << endl;
			}
		}
	}else{
		cout << "Usage: " << *argv << " file1[file2[...]]" << endl;
	}
	return ret;
}

#endif	// FModel_DEBUG
