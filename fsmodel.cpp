#include "fsmodel.h"

#include <dirent.h>
#include <cstring>

#include <stdexcept>

//**************************************
// FSModel methods

//******************
// FSModel()
//	Empty default constructor
FSModel::FSModel(){
}

//******************
// FSModel(const std::string & path)
//	Set path and load tree
FSModel::FSModel(const std::string & path){
	this->path = path;
	this->load(path);
}

//******************
// load(const std::string &)
//	Load tree
//	Returns amount of nodes loaded
size_t FSModel::load(const std::string & path){
	size_t ret = 0;
	FSNode curnode;
	curnode.path = path;
	if (!path.length()){
		throw std::runtime_error("Empty dirname");
	}

	if (path[path.length()-1] != '/'){
		curnode.path.push_back('/');
	}

	if (DIR * dirp = opendir(path.c_str())){
		struct dirent *dp;
		while (dp = readdir(dirp)){
			ret++;
			curnode.name = dp->d_name;
			curnode.fullname = curnode.path + curnode.name;
			curnode.load(curnode.fullname);
			if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
				this->contents.push_back(curnode);
				if (curnode.isdir){
					ret += this->load(curnode.fullname);
				}
			}
		}
		closedir(dirp);
	}else{
		throw std::runtime_error(std::string(path) + " not a valid dir");
	}
	this->path = path;
	return ret;
}

//******************
// dump(std::ostream&)
//	Dump contents, unfiltered, to std::ostream out
void FSModel::dump(std::ostream & out){
	out
		<< "Contenido de " << this->path << std::endl
		<< "Tipo\tTamaño\tFecha                   \tNombre" << std::endl;
	for (
		container::const_iterator
			iterator = this->contents.begin(),
			end = this->contents.end();
		iterator != end;
		iterator++
	){
		out
			<< (iterator->isdir? "dir" : "file") << '\t';
		if (iterator->getisDirectory()){
			out << iterator->size << " E";
		}else{
			out << humansize(iterator->size);
		}
		out
			<< '\t' << iterator->getCmtime() << '\t'
			<< iterator->getfullname() << std::endl;
	}
}

#ifdef FSMODEL_DEBUG

#include <iostream>

using namespace std;

int main(int argc, char **argv){
	int ret = EXIT_SUCCESS;
	if (argc > 1){
		try{
			FSModel mymodel;
			mymodel.load(argv[1]);
			mymodel.dump(cout);
		}catch(std::runtime_error e){
			cerr << e.what() << endl << "Aborting" << endl;
			ret = EXIT_FAILURE;
		}catch(...){
			cerr << "Unhandled exception" << endl << "Aborting" << endl;
			ret = EXIT_FAILURE;
		}
	}else{
		cout << "Uso:\t" << argv[0] << " <path>" << endl;
	}
	return ret;
}

#endif	// FSMODEL_DEBUG
